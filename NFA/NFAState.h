//
// Created by hp on 22/03/02019.
//

#ifndef COMPILERS_NFASTATE_H
#define COMPILERS_NFASTATE_H

#include "bits/stdc++.h"
using namespace std;

class NFAState {

private:
    static int numstates;   // number of created states
    int id;
    bool matching = false;
    vector< pair<char,NFAState*>> nextStates;
    string token;

public:
    NFAState();
    NFAState(int id);
    string getToken() const;
    bool isMatching() const;
    vector< pair<char,NFAState*>> getNextStates() const;
    int getID() const;
    void setToken(string);
    void addNextState(char, NFAState*);
    void setNextStates(vector< pair<char,NFAState*>>);
    void setMatching(bool matching);

};


#endif //COMPILERS_NFASTATE_H
