#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include "Terminal.h"
#include "Symbol.h"
#include "Production.h"
#include "NonTerminal.h"
#include "ParseTableBuilder.h"
#include "ParserContract.h"
#include "GrammarScanner.h"

#define PARSER

#ifdef PARSER

int main() {
    GrammarScanner::parseInput("../parserGenerator/parser_input");
    return 0;
}

#endif