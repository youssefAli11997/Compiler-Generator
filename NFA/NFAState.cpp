//
// Created by hp on 22/03/02019.
//

#include "NFAState.h"

int NFAState::numstates = 2;

NFAState::NFAState(){
    id = numstates++;
}

NFAState::NFAState(int id){
    this->id = id;
}

string NFAState::getToken() const{
    return token;
}

bool NFAState::isMatching() const{
    return matching;
}

vector< pair<char,NFAState*>> NFAState::getNextStates() const{
    return nextStates;
}

int NFAState::getID() const{
    return id;
}

void NFAState::setToken(string token){
    this->token = token;
}

void NFAState::addNextState(char c, NFAState* stateptr){
    this->nextStates.push_back(make_pair(c,stateptr));
}

void NFAState::setNextStates(vector< pair<char,NFAState*>> nextStates){
    this->nextStates = nextStates;
}

void NFAState::setMatching(bool matching){
    this->matching = matching;
}