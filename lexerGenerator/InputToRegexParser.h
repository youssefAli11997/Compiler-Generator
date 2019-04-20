//
// Created by youss on 3/15/2019.
//

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "RegularExpression.h"
#include "Token.h"

#ifndef COMPILER_GENERATOR_INPUTTOREGEXPARSER_H
#define COMPILER_GENERATOR_INPUTTOREGEXPARSER_H

using namespace std;

class InputToRegexParser {

public:
    static void readFile(string path);
    static map<string, RegularExpression> regularDefinitions;
    static void finalizeTokens();
    static vector<Token> getTokens();
    static vector<string> punctuationSymbols;
    static vector<string> modifiedPunctuationSymbols;

private:
    static vector<Token> tokens;
    static vector<string> keywords;
    static int regExCounter;

    static void parseLine(string line);
};


#endif //COMPILER_GENERATOR_INPUTTOREGEXPARSER_H
