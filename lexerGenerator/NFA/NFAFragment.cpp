//
// Created by hp on 23/03/02019.
//

#include "NFAFragment.h"

NFAFragment::NFAFragment() {}
NFAFragment::NFAFragment(NFAState* start, vector< pair<char,NFAState*>> out){
    this->startState = start;
    this->outStates = out;
}
