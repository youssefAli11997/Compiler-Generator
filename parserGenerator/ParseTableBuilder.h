//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PARSETABLEBUILDER_H
#define COMPILERS_PARSETABLEBUILDER_H

#include "ParseTable.h"

class ParseTableBuilder {
private:
    NonTerminal startSymbol;
    set<NonTerminal> nonTerminals;
    set<Terminal> Terminals;
    set<Symbol> allSymbols;
    void extractAllSymbols();
    void initComputedFlag();
    set<Terminal*> computeNonTerminalFirst(NonTerminal nonTerminal);
    void computeFirstSets();
    void computerFollowSets();
    ParseTable buildParseTable();
public:
    ParseTable getParseTable(NonTerminal startSymbolPtr, set<NonTerminal> nonTerminals, set<Terminal> Terminals);
};


#endif //COMPILERS_PARSETABLEBUILDER_H
