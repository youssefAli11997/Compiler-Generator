//
// Created by youss on 3/15/2019.
//

#ifndef COMPILER_GENERATOR_STATE_H
#define COMPILER_GENERATOR_STATE_H

#include "bits/stdc++.h"
using namespace std;
class DFAState {
    public:
    int id = 0; // Id of this DFAState.
    bool end = false;  // To indicate if this acceptable state.
    vector<string> tokens; // Vector to store all tokens if this state is accepted.

    DFAState() {
        id = 0;
    }

    DFAState(int x) {
        id = x;
    }

    DFAState(int id, bool end, vector<string> tokens) {
        this->id = id;
        this->end = end;
        this->tokens  = tokens;
    }

    // set<int> groupOfId;
};


#endif //COMPILER_GENERATOR_STATE_H
