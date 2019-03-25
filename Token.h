//
// Created by youss on 3/25/2019.
//

#include <string>
#include "RegularExpression.h"

#ifndef COMPILER_GENERATOR_TOKEN_H
#define COMPILER_GENERATOR_TOKEN_H

using namespace std;

class Token {

private:
    string name;
    RegularExpression regularExpression;
    int priority;
    string intToString(int x);

public:
    Token(string givenName, RegularExpression re, int pri);
    const string getName() const;
    const RegularExpression getRegularExpression() const;
    int getPriority() const;
    string toString();

};


#endif //COMPILER_GENERATOR_TOKEN_H
