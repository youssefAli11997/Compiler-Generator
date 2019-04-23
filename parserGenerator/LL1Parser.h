//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_LL1PARSER_H
#define COMPILERS_LL1PARSER_H

#include "InputBuffer.h"
#include "ParseTable.h"

using namespace std;

class LL1Parser {
private:
    ParseTable parseTable;
    InputBuffer inputBuffer;
public:
    LL1Parser(InputBuffer input, ParseTable table);
    void parseGrammar();
};

#endif //COMPILERS_LL1PARSER_H
