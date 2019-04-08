//
// Created by Shazly on 3/24/2019.
//

#include "DFAGraph.h"

inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}

DFAState DFAGraph::getNextState(DFAState currentState, char input) {
    vector<pair<DFAState,char>> transitions = graph[currentState];
    for(pair<DFAState,char> transition: transitions){
        if(transition.second == input)
            return transition.first;
    }
    return DFAState(DFAState::NULL_STATE);
}

bool DFAGraph::isMatching(DFAState state1, DFAState state2) {
    if(state1.id == state2.id){
        return true;
    }
    return false;
}