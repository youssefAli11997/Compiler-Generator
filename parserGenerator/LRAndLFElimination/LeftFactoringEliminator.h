//
// Created by Shazly on 4/23/2019.
//

#ifndef COMPILERS_LEFTFACTORINGELIMINATION_H
#define COMPILERS_LEFTFACTORINGELIMINATION_H

#include "NonTerminal.h"

class LeftFactoringElimination {
public:
    vector<NonTerminal> EliminateLF(vector<NonTerminal> nonTerminals, NonTerminal* start);
    NonTerminal* Newstart;
private:
    vector<NonTerminal> eliminateLFFromOneRule(NonTerminal nonTerminal);

};


#endif //COMPILERS_LEFTFACTORINGELIMINATION_H
