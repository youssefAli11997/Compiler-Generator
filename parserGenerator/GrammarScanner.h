//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_GRAMMARSCANNER_H
#define COMPILERS_GRAMMARSCANNER_H

#include "Terminal.h"
#include "NonTerminal.h"

class GrammarScanner {
private:
    NonTerminal* startSymbolPtr;
    set<NonTerminal> nonTerminals;
    set<Terminal> Terminals;
public:
    NonTerminal* getStartSymbolPtr();
    set<NonTerminal> getNonTerminals;
    set<Terminal> getTerminals;
    void parseInput(string path);
};

#endif //COMPILERS_GRAMMARSCANNER_H
