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

#include "../Driver.h"

#ifdef LEXER

int main() {

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
    Lexer::runLexicalAnalysis(optimized);

    return 0;
}

#endif