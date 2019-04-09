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

int main() {
    //input parsing and tokens identification code
    InputToRegexParser::readFile("../rules_input");
    InputToRegexParser::finalizeTokens();

    Lexer::readFile("../lexer_input");
    return 0;

    cout<<"begin!!! tarek\n";
    vector<Token> tokens = InputToRegexParser::getTokens();
    NFABuilder builder;
    NFAState nfaStartState = builder.build(tokens);
    cout<<"end!!! tarek\n";

    cout<<"begin!!! shazly\n";
    DFABuilder dfaBuilder(nfaStartState);
    DFAGraph dfaGraph = dfaBuilder.buildDFA();
    cout<<"end!!! shazly\n";

    cout<<"begin!!! mashaal\n";
    DFAOptimizer optimizer;
    DFAGraph optimized = optimizer.getOptimizedGraph(dfaGraph);
    cout<<"end!!! mashaal\n";

    Lexer::readFile("../lexer_input");
    Lexer::runLexicalAnalysis(optimized);

    return 0;
}