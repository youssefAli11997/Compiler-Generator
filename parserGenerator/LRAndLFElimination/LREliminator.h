//
// Created by Shazly on 4/21/2019.
//

#ifndef COMPILERS_LRELIMINATOR_H
#define COMPILERS_LRELIMINATOR_H

#include "bits/stdc++.h"
#include "NonTerminal.h"
class LREliminator {
public:
    void EliminateLR(vector<NonTerminal> nonTerminals, vector<NonTerminal> &answer, NonTerminal* start);

    NonTerminal* Newstart;
private:
    void eliminateLRFromOneRule(NonTerminal nonTerminal, vector<NonTerminal> &answer);

};


#endif //COMPILERS_LRELIMINATOR_H
