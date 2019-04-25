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

#define DRIVER

#ifdef DRIVER

int main(){

    cout << "Reading lexer rules ..." << endl;
    InputToRegexParser::readFile("../lexerGenerator/rules_input");
    InputToRegexParser::finalizeTokens();

    cout<<"Begin building NFA ..\n";
    vector<Token> tokens = InputToRegexParser::getTokens();
    NFABuilder builder;
    NFAState nfaStartState = builder.build(tokens);
    cout<<"Finish Building NFA\n";

    cout<<"Begin Building DFA ..\n";
    DFABuilder dfaBuilder(nfaStartState);
    DFAGraph dfaGraph = dfaBuilder.buildDFA();
    cout<<"Finish Building DFA\n";

    cout<<"Begin optimizing DFA ..\n";
    DFAOptimizer optimizer;
    DFAGraph optimized = optimizer.getOptimizedGraph(dfaGraph);
    cout<<"Finish optimizing DFA\n";

    cout << "Running lexical analysis ..." << endl;
    Lexer::readFile("../lexerGenerator/lexer_input");
    vector<string> input = Lexer::runLexicalAnalysis(optimized);

    vector<string> pdf_ex{"int","id",";","id","=","num",";","if","(","id",
                          "relop","num",")","{","id","=","num",";","}",to_string(END_MARKER)};

    vector<string> prog1{"int","id",";","while","(","id","relop","num",")","{","id","=","id","addop","num",";",
                         "}","if","(","id","relop","num",")","{","id","=","id","addop","num",";","}","else",
                         "{","id","=","id","addop","id",";","}",to_string(END_MARKER)};

    vector<string> prog2{"int","id",";","while","(","id","relop","num",")","{","id","=","id","addop","num",";",
                         "if","(","id","relop","num",")",")","{","id","=","id","addop","num",";","}","else",
                         "{","id","=","id","addop","id",";","}",to_string(END_MARKER)};

/*
    cout << "\n----------- BEGIN of lexer output tokens ------" << endl;
    for(int i=0;i<input.size();i++){
        cout << i << ": " << input[i] << endl;
    }
    cout << "----------- END of lexer output tokens ------\n" << endl;
*/
    input.push_back(to_string(END_MARKER));

    InputBuffer buff(input);

    GrammarScanner::parseInput("../parserGenerator/parser_input");
    NonTerminal* start = GrammarScanner::getStartSymbolPtr();
    set<Terminal*> terminalsSet = GrammarScanner::getTerminals();
    set<NonTerminal*> nonTerminalsSet = GrammarScanner::getNonTerminals();
    vector<Terminal*> terminals;
    for(Terminal* t: terminalsSet){
        terminals.push_back(t);
    }
    vector<NonTerminal*> nonTerminals;
    for(NonTerminal* t: nonTerminalsSet){
        nonTerminals.push_back(t);
    }

    ParseTableBuilder pr;
    ParseTable table = pr.getParseTable(start, nonTerminals, terminals);
    // To merge my bouns  make the previos line : ParseTable table = pr.getParseTable(leftFactoringElimination.Newstart, NOLRAndNoLF, terminals);
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