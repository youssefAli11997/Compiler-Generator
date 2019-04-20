//
// Created by youss on 3/15/2019.
//

#ifndef COMPILER_GENERATOR_NFATODFAPARSER_H
#define COMPILER_GENERATOR_NFATODFAPARSER_H

#include "DFAState.h"
#include "bits/stdc++.h"
using namespace std;
class NFAToDFAParser {
public:
    void transferNFAToDFA(map<DFAState, vector<pair<DFAState, char> > > graph, DFAState startState);
    map<DFAState, vector<pair<DFAState, char> > > getDFA();
    DFAState getStartState();
    set<pair<DFAState, Token>> getEndStates();
private:
    set<DFAState> makeEpsilonClousre(DFAState state, map<DFAState, vector<pair<DFAState, char>>> graph, set<DFAState> &epsilonSet);
    void generateGraph(map<set<DFAState>, vector<pair<set<DFAState>, char> > > tempGraph, DFAState startState);
    void putInTempGraph(map<char, set<DFAState>>edges, map<set<DFAState>, vector<pair<set<DFAState>, char> > >& tempGraph, set<DFAState> newState);
    DFAState getCombninedState(set<DFAState> state, map<set<DFAState>, int > ids, DFAState startState);

    };


#endif //COMPILER_GENERATOR_NFATODFAPARSER_H
