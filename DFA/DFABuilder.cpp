//
// Created by Shazly on 3/24/2019.
//

#include "DFABuilder.h"
#include "NFAToDFAParser.h"

int visited[1000000];

inline bool operator<(DFAState a, DFAState b) {
    return a.id > b.id;
}

DFAGraph DFABuilder::buildDFA() {
    DFAState dfaStartState = convertInputToGraph(startState);
    NFAToDFAParser nfaToDFAParser;
    nfaToDFAParser.transferNFAToDFA(graph, dfaStartState);
    DFAGraph dfaGraph;
    dfaGraph.graph = nfaToDFAParser.getDFA();
    dfaGraph.startState = nfaToDFAParser.getStartState();
    return dfaGraph;
}

DFAState DFABuilder::convertInputToGraph(NFAState state) {

    visited[state.getID()] = 1;
    vector<pair<DFAState, char> > destinations;
    for (int i = 0; i < state.getNextStates().size(); i++) {

        NFAState *s = state.getNextStates()[i].second;
        char input = state.getNextStates()[i].first;
        vector<Token> tokens;
        tokens.push_back(s->getToken());
        DFAState dfaState(s->getID(), s->isMatching(), tokens);
        destinations.push_back(make_pair(dfaState, input));
        if (visited[s->getID()] == 1)
            continue;
        convertInputToGraph(*s);
    }
    vector<Token> tokens;
    tokens.push_back(state.getToken());
    DFAState source(state.getID(), state.isMatching(), tokens);
    graph[source] = destinations;

    return source;

}
