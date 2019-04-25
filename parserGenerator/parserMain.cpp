#include <DFA/NFAToDFAParser.h>
#include <DFA/DFABuilder.h>
#include <LRAndLFElimination/LeftFactoringEliminator.h>
#include <LRAndLFElimination/LREliminator.h>
#include "InputToRegexParser.h"
#include "NFA/NFABuilder.h"
#include "bits/stdc++.h"
#include "DFA/DFAState.h"
#include "Utilities/InfixToPostfixConverter.h"
#include "DFA/DFAGraph.h"
#include "DFAOptimizer.h"
#include "Lexer.h"

#include "Terminal.h"
#include "Symbol.h"
#include "Production.h"
#include "NonTerminal.h"
#include "ParseTableBuilder.h"
#include "ParserContract.h"
#include "GrammarScanner.h"
#include "InputBuffer.h"
#include "LL1Parser.h"

#include "../Driver.h"

#ifdef PARSER

int main() {
    string line;
    ifstream lexer_file("../lexerGenerator/lexer_output");
    vector<string> input;
    while ( getline (lexer_file,line) )
    {
        input.push_back(line);
    }
    lexer_file.close();

    input.push_back(to_string(END_MARKER));

    InputBuffer buff(input);

    GrammarScanner::parseInput("../parserGenerator/eliminator_output");
    NonTerminal* start = GrammarScanner::getStartSymbolPtr();
    set<Terminal*> terminalsSet = GrammarScanner::getTerminals();
    set<NonTerminal*> nonTerminalsSet = GrammarScanner::getNonTerminals();
    vector<Terminal*> terminals;
    cout << "----------------- Terminals --------------"<< endl;
    for(Terminal* t: terminalsSet){
        terminals.push_back(t);
        cout << t->getName() << endl;
    }
    cout << endl;
    cout << "----------------- Non Terminals --------------"<< endl;
    vector<NonTerminal*> nonTerminals;
    for(NonTerminal* t: nonTerminalsSet){
        nonTerminals.push_back(t);
        cout << t->getName() << " --> ";
        for (Production* prod: t->productions) {
            cout << prod->toString()  << "|" << endl;
        }
    }
    cout << endl;

    ParseTableBuilder pr;
    ParseTable table = pr.getParseTable(start, nonTerminals, terminals);
    table.printTable();

    cout << "first --------------------" << "\n";
    for(pair<Symbol*,set<Terminal*>> keyVal:pr.allFirstSets){
        cout << "("+keyVal.first->getName() + "): {";
        for(Terminal* t :keyVal.second){
            cout << t->getName() + " ";
        }
        cout <<"}\n";
    }
    cout << "follow --------------------" << "\n";
    for(pair<NonTerminal*,set<Terminal*>> keyVal:pr.followSets){
        cout << "("+keyVal.first->getName() + "): {";
        for(Terminal* t :keyVal.second){
            cout << t->getName() + " ";
        }
        cout <<"}\n";
    }

    cout << endl;

    LL1Parser parser(buff, table);
    parser.parseGrammar();

    return 0;
}

#endif