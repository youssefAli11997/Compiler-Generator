//
// Created by youss on 3/25/2019.
//

#include <string>
#include <vector>
#include <fstream>
#include <DFA/DFAGraph.h>

#ifndef COMPILERS_LEXER_H
#define COMPILERS_LEXER_H

using namespace std;

class Lexer {

public:
    static void readFile(string path);
    static void runLexicalAnalysis(DFAGraph graph);

private:
    static vector<string> lexemes;
    static void parseLine(string line);
    static void parseWord(string word);
    static bool lexemeHasNoPunctuation(string lexeme);
};


#endif //COMPILERS_LEXER_H
