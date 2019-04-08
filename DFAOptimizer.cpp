//
// Created by youss on 3/15/2019.
//

#include "DFAOptimizer.h"

inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}

DFAGraph DFAOptimizer::getOptimizedGraph(DFAGraph graph) {
    this->currentWorkingGraph = graph;
    getAllPossibleInputsInDFA();
    splitStates();
    getEquivalentStates();
    return turnIntoDFAGraph();
}

bool compareTokens(Token a, Token b) {
    return a.getName() < b.getName();
}

DFAGraph DFAOptimizer::turnIntoDFAGraph() {
    map<DFAState, vector<pair<DFAState, char> > > graph;
    for(vector<DFAState> currentSet:equivalenceSets){
        DFAState representativeState = currentSet[0];
        vector<pair<DFAState,char>> transitions;
        for(pair<DFAState,char> transition:currentWorkingGraph.graph[representativeState]){
            DFAState nextRep = getRepresentative(transition.first);
            transitions.push_back(make_pair(nextRep, transition.second));
        }
        if(representativeState.end == true){
            set<Token, decltype(&compareTokens)> tokens(&compareTokens);
            for(DFAState state: currentSet){
                for(Token token:state.tokens){
                    tokens.insert(token);
                }
            }
            representativeState.tokens = vector<Token>(tokens.begin(),tokens.end());
        }
        graph[representativeState] = transitions;
    }
    DFAState startState = getRepresentative(currentWorkingGraph.startState);
    return DFAGraph(graph, startState);
}

DFAState DFAOptimizer::getRepresentative(DFAState state) {
    for(vector<DFAState> set:equivalenceSets){
        for(DFAState currentState:set){
            if(currentWorkingGraph.isMatching(currentState,state)){
                return set[0];
            }
        }
    }
    return DFAState(DFAState::NULL_STATE);
}

void DFAOptimizer::splitStates() {
    for(const auto &state : currentWorkingGraph.graph){
        if(state.first.end){
            acceptanceStates.push_back(state.first);
        }
        else{
            nonAcceptanceStates.push_back(state.first);
        }
    }
}

void DFAOptimizer::getAllPossibleInputsInDFA()  {
    for(pair<DFAState, vector<pair<DFAState, char>>> transitions: currentWorkingGraph.graph){
        for(pair<DFAState,char> transition: transitions.second){
            possibleInputs.insert(transition.second);
        }
    }
}

void DFAOptimizer::getEquivalentStates() {
    vector<vector<DFAState>> lastEquivalence;
    lastEquivalence.push_back(nonAcceptanceStates);
    lastEquivalence.push_back(acceptanceStates);
    bool changed = true;
    while(changed){
        vector<vector<DFAState>> newEquivalence;
        for(vector<DFAState> group : lastEquivalence){
            vector<vector<DFAState>> newGroups;
            vector<DFAState> newGroup;
            newGroup.push_back(group.front());
            newGroups.push_back(newGroup);
            for(int i = 1 ; i < group.size() ; i ++){
                bool matchesGroup = false;
                DFAState currentState = group[i];
                for(int j = 0 ; j < newGroups.size() ; j ++){
                    if(matchEqu(currentState,newGroups[j][0],lastEquivalence)){
                        newGroups[j].push_back(currentState);
                        matchesGroup = true;
                        break;
                    }
                }
                if(!matchesGroup){
                    vector<DFAState> groupToBeAdded;
                    groupToBeAdded.push_back(group[i]);
                    newGroups.push_back(groupToBeAdded);
                }
            }
            for(vector<DFAState> group: newGroups){
                newEquivalence.push_back(group);
            }
        }
        changed = !checkMatchingEquivalence(lastEquivalence,newEquivalence);
        lastEquivalence = newEquivalence;
    }
    equivalenceSets = lastEquivalence;
}

bool DFAOptimizer::checkMatchingEquivalence(vector<vector<DFAState>> set1, vector<vector<DFAState>> set2) {
    if(set1.size() != set2.size())
        return false;
    else{
        return true;
        // not checking every set contents
    }
}

bool DFAOptimizer::matchEqu(DFAState state1, DFAState state2, vector<vector<DFAState>> sets) {
    bool match = true;
    for(char input: possibleInputs){
        DFAState nextState1 = currentWorkingGraph.getNextState(state1, input);
        DFAState nextState2 = currentWorkingGraph.getNextState(state2, input);
        if(nextState1.isNullState() && nextState2.isNullState()){
            continue;
        }
        else if(nextState1.isNullState() || nextState2.isNullState()){
            return false;
        }
        else{
            int index1 = 0;
            int index2 = 0;
            bool loop1 = false;
            bool loop2 = false;
            for(int i = 0 ; i < sets.size() ; i ++){
                for(DFAState state: sets[i]){
                    if(currentWorkingGraph.isMatching(state, nextState1)) {
                        index1 = i;
                        loop1 = true;
                    }
                    if(currentWorkingGraph.isMatching(state, nextState2)) {
                        index2 = i;
                        loop2 = true;
                    }
                    if(loop1 && loop2)
                        break;
                }
                if(loop1 && loop2)
                    break;
            }
            if(index1 != index2)
                return false;
        }
    }
    return match;
}

