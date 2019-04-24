//
// Created by Shazly on 4/23/2019.
//

#include <Utilities/LexicalContract.h>
#include <Terminal.h>
#include "LeftFactoringEliminator.h"
Symbol LeftFactoringElimination::available[100000];
int LeftFactoringElimination::counter = 0;
bool isMAtch(Symbol* s, Symbol* x){
    return s->toString() == x->toString();
}
int getMAxMatchSymbols(Production a, Production b){
    int i = 0;
    for(; i < min(a.symbols.size(), b.symbols.size()); i++)
        if(!isMAtch(a.symbols[i], b.symbols[i]))
            break;
    return i;
}
vector<NonTerminal> LeftFactoringElimination::eliminateLFFromOneRule(NonTerminal nonTerminal){
    vector<Production> productions = nonTerminal.productions;
    int counterOfNewProducion = 1;
    vector<NonTerminal> answer;
    for(int i = 0; i < productions.size(); i++){
        vector<Production> match;
        int minLenghtOfMatching = 1000000;
        for(int j = i + 1; j < productions.size(); j++){
            int maxMatchingLength = getMAxMatchSymbols(productions[i], productions[j]);
            if(maxMatchingLength == 0)
                continue;
            if(minLenghtOfMatching > maxMatchingLength){
                minLenghtOfMatching = maxMatchingLength;
            }
            match.push_back(productions[j]);
            productions.erase(productions.begin() + j);  // erase it if it natch
            j = i; // return from first again
        }
        match.push_back(productions[i]);
        if(match.size() == 1)  // No Left Factoring
            continue;
        Production common;
        for(int j = 0; j < minLenghtOfMatching; j++)   // To get Common Symbols (I use first production I take)
            common.symbols.push_back(productions[i].symbols[j]);

        NonTerminal newNonTerminal(nonTerminal.getName() + "_LFdash");  // New Terminal.

        for(int j = 0; j < match.size(); j++){ // Loop on matching productions
            for(int u = 0; u < minLenghtOfMatching; u++) // get the part which isnot common from it
                match[j].symbols.erase(match[j].symbols.begin());
            if(match[j].symbols.size() == 0){
                Terminal epsilonTerminal(to_string(EPSILON) );
                Production epsilonproduction;
                available[counter++] = epsilonTerminal;
                match[j].symbols.push_back(&available[counter - 1]);
            }
        }
        newNonTerminal.productions = match; // make this as new production for new non terminal
        available[counter++] = newNonTerminal;
        common.symbols.push_back(&available[counter - 1]); // add new non terminal to become: common match  + new non terminal.
        answer.push_back(newNonTerminal);
        productions.erase(productions.begin() + i);
        productions.push_back(common);
        counterOfNewProducion++;
        i = -1;
    }
    nonTerminal.productions.clear();
    nonTerminal.productions = productions;
   answer.push_back(nonTerminal);

    return answer;
}
vector<NonTerminal> LeftFactoringElimination::EliminateLF(vector<NonTerminal> nonTerminals){

    for(int i = 0; i < nonTerminals.size(); i++){
        vector<NonTerminal> newNonTerminals = eliminateLFFromOneRule(nonTerminals[i]);
        if(newNonTerminals.size() == 1)
            continue;
        nonTerminals.erase(nonTerminals.begin() + i);
        for(int j = 0; j < newNonTerminals.size(); j++)
            nonTerminals.push_back(newNonTerminals[j]);

        i = -1;
    }

    return nonTerminals;
}

