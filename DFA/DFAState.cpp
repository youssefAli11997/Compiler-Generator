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
    cout<<"here: \n";
    for(int i=1; i<tokens.size(); i++){
        cout<<tokens[i].getName()<<" "<<tokens[i].getPriority()<<endl;
        if(tokens[i].getPriority() < maxPri){
            maxPri = tokens[i].getPriority();
            idx = i;
        }
    }
    cout<<tokens[idx].getName()<<endl;
    return tokens[idx];
}
