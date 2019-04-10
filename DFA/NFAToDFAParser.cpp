//
// Created by youss on 3/15/2019.
//
#include "DFAState.h"
#include "NFAToDFAParser.h"
#include "bits/stdc++.h"
#include "Utilities/LexicalContract.h"
using namespace std;
map<DFAState, vector<pair<DFAState, char>> > newGraph;
set<pair<DFAState, Token>> newEndStates;
DFAState newStartState;
set<DFAState> dp[1000000];
inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}
inline bool operator<(Token a, Token b)
{
    return a.getPriority() > b.getPriority();
}


set<DFAState> NFAToDFAParser:: makeEpsilonClousre(DFAState state, map<DFAState, vector< pair<DFAState, char> > > graph, set<DFAState>& epsilonSet){
    epsilonSet.insert(state);
    vector<pair<DFAState, char>> destination;
    destination = graph[state];
    for(auto i = 0; i < destination.size(); i++){
        if(epsilonSet.find(destination[i].first) == epsilonSet.end() && destination[i].second == EPSILON){
            makeEpsilonClousre(destination[i].first, graph, (epsilonSet));
        }
    }
    return epsilonSet;
}

void NFAToDFAParser:: transferNFAToDFA(map<DFAState, vector< pair<DFAState, char> > > graph, DFAState startState){

    set<DFAState> epsiolonSet;
    makeEpsilonClousre(startState, graph, epsiolonSet);
    map<set<DFAState>, vector<pair<set<DFAState>, char> > > tempGraph;
    set<set<DFAState> > visited, newStates;
    newStates.insert((epsiolonSet));
    while(!newStates.empty()) {
        if(visited.find(*(newStates.begin())) != visited.end()) {
            newStates.erase(*(newStates.begin()));
            continue;
        }
        set<DFAState> newState;
        newState = (*(newStates.begin()));
        visited.insert(*(newStates.begin()));
        map<char, set<DFAState>> edges;
        for (auto i = newState.begin(); i != newState.end(); i++) {
            vector<pair<DFAState, char>> destination;
            destination = graph[*i];
            for (int j = 0; j < destination.size(); j++) {
                set<DFAState> temp;
                if(destination[j].second == EPSILON)
                    continue;
                temp = edges[destination[j].second];
                if(dp[destination[j].first.id].size() != 0){
                 //   fill(dp[]);
                }

                makeEpsilonClousre(destination[j].first, graph, temp);
                edges[destination[j].second] = temp;
            }
        }
        putInTempGraph(edges, tempGraph, newState);
        vector<pair<set<DFAState>, char> > edge;
        for (auto i = edges.begin(); i != edges.end(); i++) {
            set<DFAState> temp;
            temp = ((*i).second);
            edge.push_back(make_pair(temp, (*i).first));
        }
        tempGraph[(newState)] = edge;
        newStates.erase(*(newStates.begin()));
        for(int i = 0; i < edge.size(); i++){
            newStates.insert(edge[i].first);
        }
    }
    generateGraph(tempGraph, startState);

}
void NFAToDFAParser::putInTempGraph(map<char, set<DFAState>>edges, map<set<DFAState>, vector<pair<set<DFAState>, char> > >& tempGraph, set<DFAState> newState){
    vector<pair<set<DFAState>, char> > transition;
    for (auto i = edges.begin(); i != edges.end(); i++) {
        set<DFAState> temp;
        temp = ((*i).second);
        transition.push_back(make_pair(temp, (*i).first));
    }
    tempGraph[(newState)] = transition;

}

void NFAToDFAParser::generateGraph(map<set<DFAState>, vector<pair<set<DFAState>, char> > > tempGraph, DFAState startState){
    map<set<DFAState>, int> ids;
    int counter = 1;
    for(auto i = tempGraph.begin(); i != tempGraph.end(); i++)  // Hash States To New ID.
        if(!ids[(*i).first])
            ids[(*i).first] = counter++;


    for(auto i = tempGraph.begin(); i !=tempGraph.end(); i++){
        vector<pair<DFAState, char>> temp;
        for(int j = 0; j < (*i).second.size(); j++){

            temp.push_back(make_pair(getCombninedState((*i).second[j].first, ids, startState), ((*i)).second[j].second));
        }
        newGraph[getCombninedState((*i).first, ids, startState)] = temp;

    }
}

DFAState NFAToDFAParser::getCombninedState(set<DFAState> states, map<set<DFAState>, int > ids, DFAState startState){
    DFAState newState(ids[states]);
    bool endState = false;
    for(auto i = states.begin(); i != states.end(); i++){
        endState |= (*i).end;
        if((*i).end) // We Will have one end DFAState So We will push one token to the new DFAState.
            newState.tokens.push_back((*i).tokens[0]);
        if((*i).id == startState.id)
            newStartState = newState;
    }
    if(newState.end) {
        for (int j = 0; j < newState.tokens.size(); j++) {
            newEndStates.insert(make_pair(newState, newState.tokens[j]));
        }
    }
    newState.end = endState;
    return newState;
}




map<DFAState, vector<pair<DFAState, char> > > NFAToDFAParser:: getDFA(){
    return newGraph;
};

set<pair<DFAState, Token>> NFAToDFAParser::getEndStates(){
    return newEndStates;
};

DFAState NFAToDFAParser::getStartState(){
    return newStartState;
};
