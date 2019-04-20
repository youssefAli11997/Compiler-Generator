//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PARSETABLEBUILDER_H
#define COMPILERS_PARSETABLEBUILDER_H

#include "ParseTable.h"

class ParseTableBuilder {
private:
    set<NonTerminal> nonTerminals;
    set<Terminal> Terminals;
    void computeFirstSets();
    void computerFollowSets();
public:
    ParseTable getParseTable();
};


#endif //COMPILERS_PARSETABLEBUILDER_H
