//
// Created by youss on 3/25/2019.
//

#include "Token.h"

Token::Token(string givenName, RegularExpression re, int pri){
    this->name = givenName;
    this->regularExpression = re;
    this->priority = pri;
}

const string Token::getName() const {
    return name;
}

const RegularExpression Token::getRegularExpression() const {
    return regularExpression;
}

int Token::getPriority() const {
    return priority;
}

string Token::toString(){
    return this->name + " val: " + this->regularExpression.toString();
}
