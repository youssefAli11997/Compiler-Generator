//
// Created by youss on 3/15/2019.
//

#include "DFAState.h"

inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}

bool DFAState::isNullState() {
    if(this->id == NULL_STATE)
        return true;
    return false;
}