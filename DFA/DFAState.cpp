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

Token DFAState::getHighestPriorityToken() {
    int maxPri = tokens[0].getPriority(), idx = 0;
    for(int i=0; i<tokens.size(); i++){
        if(tokens[i].getPriority() < maxPri){
            maxPri = tokens[i].getPriority();
            idx = i;
        }
    }
    return tokens[idx];
}
