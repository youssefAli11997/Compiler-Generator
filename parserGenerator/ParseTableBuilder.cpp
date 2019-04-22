//
// Created by hp on 20/04/02019.
//

#include "ParseTableBuilder.h"
#include "ParserContract.h"
#include "Terminal.h"

ParseTable ParseTableBuilder::getParseTable(NonTerminal startSymbolPtr, set<NonTerminal> nonTerminals,
                                            set<Terminal> Terminals) {
    this->startSymbol = startSymbolPtr;
    this->nonTerminals = nonTerminals;
    this->Terminals = Terminals;
    extractAllSymbols();
    computeFirstSets();
    //computerFollowSets();
    return ParseTable();
}

void ParseTableBuilder::computeFirstSets() {
    initComputedFlag();
    for(Terminal ter :Terminals){
        ter.addToFirstSet(&ter);
        ter.firComputed = true;
    }
    for(NonTerminal nTer: nonTerminals){
        if(!nTer.firComputed){
            nTer.addToFirstSet(computeNonTerminalFirst(nTer));
            nTer.firComputed = true;
        }
    }

}

void ParseTableBuilder::extractAllSymbols() {
    for(NonTerminal nTer: nonTerminals){
        for(Production prod : nTer.productions){
            for(Symbol sym: prod.getSymbols()){
                allSymbols.insert(sym);
            }
        }
    }
    for(Terminal ter: Terminals)
        allSymbols.insert(ter);
}

void ParseTableBuilder::initComputedFlag(){
    for(Symbol sym: allSymbols){
        sym.firComputed = false;
    }
}

set<Terminal*> ParseTableBuilder::computeNonTerminalFirst(NonTerminal nonTerminal){
    set<Terminal*> first;
    for(Production prd:nonTerminal.productions){
        set<Terminal*> terRes;
        for(Symbol sym:prd.getSymbols()){
            Symbol * symbol = &sym;
            if(dynamic_cast<Terminal*>(symbol) == nullptr){
                Terminal* terPtr = dynamic_cast<Terminal*> (symbol);
                terRes.insert(terPtr);
                break;
            }
            else{
                NonTerminal* nonTerPtr = dynamic_cast<NonTerminal*> (symbol);
                NonTerminal nonTer = *nonTerPtr;
                set<Terminal*> terminals;
                if(!nonTer.firComputed) {
                    terminals = computeNonTerminalFirst(nonTer);
                    nonTer.firComputed = true;
                    nonTer.addToFirstSet(terminals);
                }
                else{
                    terminals = nonTer.getFirstSet();
                }
                if(terminals.size() == 1){
                    vector<Terminal*> vt(terminals.begin(),terminals.end());
                    if(vt[0]->getName() == to_string(EPSILON))
                        continue;
                }
                for(Terminal* t: terminals)
                    terRes.insert(t);
                break;
            }
        }
        if(terRes.size() ==  0){
            Terminal terminal = Terminal(to_string(EPSILON));
            terRes.insert(&terminal);
        }
        for(Terminal* terSym: terRes)
            first.insert(terSym);
    }
    return first;
}