//
// Created by Shazly on 3/24/2019.
//

#ifndef COMPILERS_DFAGRAPH_H
#define COMPILERS_DFAGRAPH_H


#include <DFAState.h>

class DFAGraph {
public:
    DFAGraph(){

    }
    DFAGraph(map<DFAState, vector<pair<DFAState, char> > > graph, DFAState startState) {
        this->graph = graph;
        this->startState = startState;
    }
    DFAState startState;
    map<DFAState, vector<pair<DFAState, char> > > graph;
/*    DFAGraph(DFAState startState, map<DFAState, vector<pair<DFAState, char> > > graph) {
        this->graph = graph;
        this->startState = startState;
    }*/
    DFAState getNextState(DFAState currentState, char input);
    bool isMatching(DFAState state1, DFAState state2);
};


#endif //COMPILERS_DFAGRAPH_H
