#include <iostream>
#include <DFA/NFAToDFAParser.h>
#include <DFA/DFABuilder.h>
#include "InputToRegexParser.h"
#include "NFA/NFABuilder.h"
#include "bits/stdc++.h"
#include "DFAState.h"
#include "Utilities/InfixToPostfixConverter.h"
#include "DFAGraph.h"
#include "DFAOptimizer.h"
#include "Lexer.h"

using namespace std;

inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}

//#define LEXER

#ifdef LEXER

int main() {

/*
   InputToRegexParser::readFile("../simple_lexical_input");
   InputToRegexParser::finalizeTokens();
   vector<Token> tokens = InputToRegexParser::getTokens();
   cout<<"begin\n";
   NFABuilder builder;
   NFAState nfaStartState = builder.build(tokens);
   cout<<"end\n";
   cout << nfaStartState.getID() << endl;
*/

/*
   InfixToPostfixConverter::convert("\\(");
   InfixToPostfixConverter::convert("\\)");
   cout << endl;
*/
    /*
   InfixToPostfixConverter::convert("\\=\\=");
   cout << endl;
*/



    //input parsing and tokens identification code
    InputToRegexParser::readFile("../lexerGenerator/rules_input");
    InputToRegexParser::finalizeTokens();

    cout<<"begin!!! tarek\n";
    vector<Token> tokens = InputToRegexParser::getTokens();
    NFABuilder builder;
    NFAState nfaStartState = builder.build(tokens);
    cout<<"end!!! tarek\n";

    cout<<"tokens list: \n";
    for(int i=0; i<tokens.size(); i++){
        cout<<tokens[i].toString()<<endl;
    }

    cout<<"begin!!! shazly\n";
    DFABuilder dfaBuilder(nfaStartState);
    DFAGraph dfaGraph = dfaBuilder.buildDFA();
    cout << "Graph ------------------------------\n";
    for(pair<DFAState, vector<pair<DFAState, char>>> entry: dfaGraph.graph){
        cout << "State: " << entry.first.id << "\n";
        for(pair<DFAState, char> trans: entry.second){
            cout << "   Next :" << trans.first.id << " on: " << trans.second << "\n";
        }
    }
    cout << "-------------------------------";
    cout<<"end!!! shazly\n";

    cout<<"begin!!! mashaal\n";
    DFAOptimizer optimizer;
    DFAGraph optimized = optimizer.getOptimizedGraph(dfaGraph);
    cout << "Optimized Graph ------------------------------\n";
    for(pair<DFAState, vector<pair<DFAState, char>>> entry: optimized.graph){
        cout << "State: " << entry.first.id << "\n";
        for(pair<DFAState, char> trans: entry.second){
            cout << "   Next :" << trans.first.id << " on: " << trans.second << "\n";
        }
    }
    cout << "-------------------------------";
    cout<<"end!!! mashaal\n";

    Lexer::readFile("../lexerGenerator/lexer_input");
    Lexer::runLexicalAnalysis(optimized);

    return 0;

}

#endif