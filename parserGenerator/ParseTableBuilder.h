//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PARSETABLEBUILDER_H
#define COMPILERS_PARSETABLEBUILDER_H

#include <map>
#include "ParseTable.h"
#include "Terminal.h"
#include "NonTerminal.h"

class ParseTableBuilder {
private:
    NonTerminal* startSymbol;
    vector<NonTerminal*> nonTerminals;
    vector<Terminal*> terminals;
    vector<Symbol*> allSymbols;
    set<Terminal*> computeNonTerminalFirst(NonTerminal* nonTerminal);
    void computeFirstSets();
    void computerFollowSets();
    ParseTable buildParseTable();
    void initiateAllSets();
    void getAllSymbols();
public:
    map<Symbol*, set<Terminal*>> allFirstSets; // nonTerminals and terminals used to compute first of productions
    map<Symbol*, set<Terminal*>> firstSets; // nonTerminal and production( a symbol representing the vector of symbols)
    map<NonTerminal*, set<Terminal*>> followSets;
    ParseTableBuilder();
    ParseTable getParseTable(NonTerminal* startSymbolPtr, vector<NonTerminal*> nonTerminals, vector<Terminal*> terminals);
};


#endif //COMPILERS_PARSETABLEBUILDER_H
