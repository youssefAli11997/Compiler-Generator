//
// Created by Shazly on 3/24/2019.
//

#include "DFABuilder.h"
int visited[1000000];
inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}
DFAGraph DFABuilder::buildDFA() {
    return DFAGraph();
}
void DFABuilder::convertInputToGraph(NFAState state){

    visited[state.getID()] = 1;
    vector< pair<DFAState, char> >  destinations;
    for(int i = 0; i < state.getNextStates().size(); i++){

        NFAState *s = state.getNextStates()[i].second;
          char input = state.getNextStates()[i].first;
         /* prio<Tokens> tokens;
          // TO DO Complete

         DFAState x(s->id, s->matchingState, NULL, NULL);
        destinations.push_back(make_pair(x, input);
        if(visited[state.nextStates[i].second->id] == 1)
            continue;
        */



    }
    /*
    DFAState source(state.id, state.matchingState, state.token);
    graph[source] = destinations;

     */

}
