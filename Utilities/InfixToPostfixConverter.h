//
// Created by hp on 25/03/02019.
//

#ifndef COMPILERS_REGEXCONVERTER_H
#define COMPILERS_REGEXCONVERTER_H

#include "bits/stdc++.h"
#include "LexicalContract.h"

using namespace std;

#define MAX_PRECEDENCE 100

class InfixToPostfixConverter {
public:
    static string convert(string infix);

private:
    static string addExplicitConcatOp(string regex);
    static map<char, int> precedence;
    static int getPrecedence(char op);
    static bool isRegexOperator(char c);
    static bool isBinaryOperator(char c);
    static string removeBlanks(string s);
};


#endif //COMPILERS_REGEXCONVERTER_H
