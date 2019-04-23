//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PARSETABLE_H
#define COMPILERS_PARSETABLE_H

#include "Production.h"
#include "NonTerminal.h"


#define MAX_SIZE 200

class ParseTable {
private:
    Production table[MAX_SIZE][MAX_SIZE];
    // mapping Nonterminals to row indices
    // mapping Terminals to column indices
public:
    Production getProduction(NonTerminal,Terminal);
};



#endif //COMPILERS_PARSETABLE_H
