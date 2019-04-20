//
// Created by hp on 22/03/02019.
//

#ifndef COMPILERS_NFASTATE_H
#define COMPILERS_NFASTATE_H

#include "bits/stdc++.h"
#include "lexerGenerator/Token.h"
using namespace std;

class NFAState {

private:
    static int numstates;   // number of created states
    int id;
    bool matching = false;
    vector< pair<char,NFAState*>> nextStates;
    Token token = Token("",RegularExpression(),0);    // dummy Token will be edited

public:
    NFAState();
    NFAState(int id);
    Token getToken() const;
    bool isMatching() const;
    vector< pair<char,NFAState*>> getNextStates() const;
    int getID() const;
    void setToken(Token);
    void addNextState(char, NFAState*);
    void setNextStates(vector< pair<char,NFAState*>>);
    void setMatching(bool matching);

};


#endif //COMPILERS_NFASTATE_H
