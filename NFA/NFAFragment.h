//
// Created by hp on 23/03/02019.
//

#ifndef COMPILERS_NFAFRAGMENT_H
#define COMPILERS_NFAFRAGMENT_H

#include "bits/stdc++.h"
#include "NFAState.h"
using namespace std;

class NFAFragment {
public:

    NFAState* startState;
    vector< pair<char,NFAState*>> outStates;

    NFAFragment();
    NFAFragment(NFAState* start, vector< pair<char,NFAState*>> out);

};


#endif //COMPILERS_NFAFRAGMENT_H
