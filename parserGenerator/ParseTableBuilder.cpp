//
// Created by hp on 20/04/02019.
//

#include <iostream>
#include "ParseTableBuilder.h"
#include "ParserContract.h"
#include "Terminal.h"

ParseTableBuilder::ParseTableBuilder() {}

ParseTable ParseTableBuilder::getParseTable(NonTerminal* startSymbolPtr, vector<NonTerminal*> nonTerminals,
                                            vector<Terminal*> terminals) {
    this->startSymbol = *startSymbolPtr;
    this->nonTerminals = nonTerminals;
    this->terminals = terminals;
    getAllSymbols();
    initiateAllSets();
    computeFirstSets();
    computerFollowSets();
    return buildParseTable();
}

void ParseTableBuilder::getAllSymbols() {
    for(int i = 0 ; i < terminals.size() ; i ++){
        allSymbols.push_back(terminals[i]);
    }
    for(int i = 0 ; i < nonTerminals.size() ; i ++){
        allSymbols.push_back(nonTerminals[i]);
    }
}

void ParseTableBuilder::initiateAllSets() {
    for(int i = 0 ; i < allSymbols.size() ; i++){
        set<Terminal> empty;
        allFirstSets[*allSymbols[i]] = empty;
    }
    for(int i = 0 ; i < nonTerminals.size() ; i++){
        set<Terminal> empty;
        followSets[*nonTerminals[i]] = empty;
    }
}

ParseTable ParseTableBuilder::buildParseTable() {
    ParseTable table;
    table.setStartSymbolPtr(&startSymbol);
    for(NonTerminal* nonTerminal:nonTerminals){
        for(Production *prd:nonTerminal->productions){
            for(Terminal t:prd->getFirstSet(allFirstSets)){
                table.addProductionEntry(*nonTerminal,t,prd);
                if(t.getName() == to_string(EPSILON)){
                    for(Terminal t :followSets[*nonTerminal]){
                        table.addProductionEntry(*nonTerminal,t,prd);
                        if(t.getName() == to_string(END_MARKER)){
                            table.addProductionEntry(*nonTerminal,Terminal(to_string(END_MARKER)),prd);
                        }
                    }
                }
            }
        }
    }
    for(NonTerminal* nonTerminal: nonTerminals){
        for(Terminal t : followSets[*nonTerminal]){
            if(table.getEntryType(*nonTerminal,t) == EMPTY_ENTRY){
                table.addSyncEntry(*nonTerminal,t);
            }
        }
    }
    return table;
}

void ParseTableBuilder::computerFollowSets() {
    // start symbol
    for(int i = 0 ; i < nonTerminals.size() ; i++) {
        if (nonTerminals[i]->getName() == startSymbol.getName()) {
            Terminal t = Terminal(to_string(END_MARKER));
            followSets[*nonTerminals[i]].insert(t);
        }
    }

    for(NonTerminal* nonTerminal: nonTerminals){
        for(NonTerminal* loop: nonTerminals) {
            for (Production * prod: loop->productions) {
                for (int i = 0; i < prod->symbols.size(); i++) {
                    if (prod->symbols[i]->getName() == nonTerminal->getName()){
                        if((i+1) < prod->symbols.size()){
                            for(Terminal t:allFirstSets[*prod->symbols[i+1]]){
                                if(t.getName() == to_string(EPSILON)){
                                    continue;
                                }
                                followSets[*nonTerminal].insert(t);
                            }
                        }
                    }
                }
            }
        }
    }
    for(NonTerminal* nonTerminal: nonTerminals){
        for(NonTerminal* loop: nonTerminals) {
            for (Production * prod: loop->productions) {
                for (int i = 0; i < prod->symbols.size(); i++) {
                    if (prod->symbols[i]->getName() == nonTerminal->getName()){
                        if((i+1) == prod->symbols.size()){
                            for(Terminal t:followSets[*loop]){
                                followSets[*nonTerminal].insert(t);
                            }
                        }
                        else if((i+1) < prod->symbols.size()){
                            bool containEp = false;
                            for(Terminal t : allFirstSets[*prod->symbols[i+1]]){
                                if(t.getName() == to_string(EPSILON)){
                                    containEp = true;
                                    break;
                                }
                            }
                            if(containEp){
                                for(Terminal t:followSets[*loop]){
                                    followSets[*nonTerminal].insert(t);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void ParseTableBuilder::computeFirstSets() {
    for(int i  = 0 ; i < terminals.size() ; i++){
        allFirstSets[*terminals[i]].insert(*terminals[i]);
    }
    for(int i  = 0 ; i < nonTerminals.size() ; i++){
        if(allFirstSets[*nonTerminals[i]].empty()){
            allFirstSets[*nonTerminals[i]] = computeNonTerminalFirst(*nonTerminals[i]);
            firstSets[*nonTerminals[i]] = allFirstSets[*nonTerminals[i]];
        }
    }
    for(NonTerminal* nonTerminal:nonTerminals){
        for(Production * prd:nonTerminal->productions){
            string name = "";
            for(Symbol* symbol:prd->symbols){
                name += symbol->getName();
            }
            Symbol sym(name);
            firstSets[sym] = prd->getFirstSet(allFirstSets);
        }
    }
}


set<Terminal> ParseTableBuilder::computeNonTerminalFirst(NonTerminal nonTerminal){
    set<Terminal> first;
    for(int i = 0 ; i < nonTerminal.productions.size() ; i ++){
        set<Terminal> terRes;
        for(int j = 0 ; j < nonTerminal.productions[i]->symbols.size() ; j++){
            Symbol * symbol = nonTerminal.productions[i]->symbols[j];
            if(Terminal* d = dynamic_cast<Terminal*>(symbol)){
                terRes.insert(*d);
                break;
            }
            else if(NonTerminal* d = dynamic_cast<NonTerminal*>(symbol)){
                NonTerminal nonTer = *d;
                set<Terminal> terminals;
                if(allFirstSets[nonTer].empty()) {
                    terminals = computeNonTerminalFirst(nonTer);
                    allFirstSets[nonTer] = terminals;
                    firstSets[nonTer] = terminals;
                }
                else{
                    terminals = allFirstSets[nonTer];
                }
                if(terminals.size() == 1){
                    vector<Terminal> vt(terminals.begin(),terminals.end());
                    if(vt[0].getName() == to_string(EPSILON))
                        continue;
                }
                for(Terminal t: terminals)
                    terRes.insert(t);
                break;
            }else{
                cout << "can't cast in computeNonTerminalFirst()\n" << endl;
            }
        }
        if(terRes.size() ==  0){
            Terminal terminal = Terminal(to_string(EPSILON));
            terRes.insert(terminal);
        }
        for(Terminal terSym: terRes)
            first.insert(terSym);
    }
    return first;
}
