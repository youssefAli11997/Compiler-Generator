//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_LL1PARSER_H
#define COMPILERS_LL1PARSER_H

#include "ParseTable.h"

class LL1Parser {
private:
    ParseTable parseTable;
public:
    void parseGrammar();
};

#endif //COMPILERS_LL1PARSER_H
