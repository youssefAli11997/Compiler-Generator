//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_GRAMMARSCANNER_H
#define COMPILERS_GRAMMARSCANNER_H

#include "Terminal.h"
#include "NonTerminal.h"
#include "ParserContract.h"
#include <vector>
#include <fstream>
#include <iostream>

class GrammarScanner {
private:
    static NonTerminal* startSymbolPtr;
    static set<NonTerminal *> nonTerminals;
    static set<Terminal *> Terminals;
    static void parseIntoLines(string path);
public:
    static NonTerminal* getStartSymbolPtr();
    static set<NonTerminal *> getNonTerminals();
    static set<Terminal *> getTerminals();
    static void parseInput(string path);

    static void parseIntoLineWords();

    static void parseProductions(NonTerminal *pTerminal, vector<string> vector);

    static void parseRule(NonTerminal *pTerminal, vector<string> vector);
};

#endif //COMPILERS_GRAMMARSCANNER_H
