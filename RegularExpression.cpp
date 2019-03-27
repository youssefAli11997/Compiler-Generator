//
// Created by youss on 3/15/2019.
//

#include "RegularExpression.h"

string RegularExpression::toString() {
    string re = "";
    for(int i=0; i<value.size(); i++)
        re += value[i] + " ";
    re += "\n";

    return re;
}
