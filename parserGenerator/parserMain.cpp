#include <lexerGenerator/DFA/NFAToDFAParser.h>
#include <lexerGenerator/DFA/DFABuilder.h>
#include "lexerGenerator/InputToRegexParser.h"
#include "lexerGenerator/NFA/NFABuilder.h"
#include "bits/stdc++.h"
#include "lexerGenerator/DFA/DFAState.h"
#include "lexerGenerator/Utilities/InfixToPostfixConverter.h"
#include "lexerGenerator/DFA/DFAGraph.h"
#include "lexerGenerator/DFAOptimizer.h"
#include "lexerGenerator/Lexer.h"

#include "Terminal.h"
#include "Symbol.h"
#include "Production.h"
#include "NonTerminal.h"
#include "ParseTableBuilder.h"
#include "ParserContract.h"
#include "GrammarScanner.h"
#include "InputBuffer.h"
#include "LL1Parser.h"

#define PARSER

#ifdef PARSER

int main() {

    /************ Lexer *****************/

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
    vector<string> input = Lexer::runLexicalAnalysis(optimized);


    /************ Parser *****************/


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

    cout << "first --------------------" << "\n";
    for(pair<Symbol,set<Terminal>> keyVal:pr.firstSets){
        cout << "("+keyVal.first.getName() + "): {";
        for(Terminal t :keyVal.second){
            cout << t.getName() + " ";
        }
        cout <<"}\n";
    }
    cout << "follow --------------------" << "\n";
    for(pair<NonTerminal,set<Terminal>> keyVal:pr.followSets){
        cout << "("+keyVal.first.getName() + "): {";
        for(Terminal t :keyVal.second){
            cout << t.getName() + " ";
        }
        cout <<"}\n";
    }

    table.printTable();
    cout << endl;

    LL1Parser parser(input, table);
    parser.parseGrammar();


    /*
    NonTerminal e("E");
    NonTerminal e_("E-");
    NonTerminal t("T");
    NonTerminal t_("T-");
    NonTerminal f("F");
    Terminal p1 ("(");
    Terminal p2 (")");
    Terminal id("id");
    Terminal plus("+");
    Terminal ast("*");
    Terminal ep(to_string(EPSILON));
    Production te_;
    Production te__;
    Production epp;
    Production id_;
    Production ft_;
    Production ft__;
    Production e__;
    te_.symbols = {&t, &e_};
    te__.symbols = {&plus, &t, &e_};
    epp.symbols = {&ep};
    ft_.symbols = {&f, &t_};
    ft__.symbols = {&ast, &f, &t_};
    e__.symbols = {&p1, &e, &p2};
    id_.symbols = {&id};
    e.productions = {&te_};
    e_.productions = {&te__, &epp};
    t.productions = {&ft_};
    t_.productions = {&ft__, &epp};
    f.productions = {&e__, &id_};
    vector<NonTerminal> non = {e, e_, t, t_, f};
    vector<Terminal> term = {ep, id, p1, p2, plus, ast};
    ParseTableBuilder pr;
    pr.getParseTable(e, non, term);

    */
    /*
    NonTerminal S("S");
    NonTerminal A("A");

    Terminal b("b");
    Terminal e("e");
    Terminal a("a");
    Terminal c("c");
    Terminal d("d");
    Terminal ep(to_string(EPSILON));

    Production AbS_;
    Production e_;
    Production epp_;
    Production a_;
    Production cAd_;


    AbS_.symbols = {&A, &b, &S};
    e_.symbols = {&e};
    epp_.symbols = {&ep};
    a_.symbols = {&a};
    cAd_.symbols = {&c, &A, &d};

    S.productions = {&AbS_, &e_, &epp_};
    A.productions = {&a_, &cAd_};

    vector<NonTerminal*> non = {&S, &A};
    vector<Terminal*> term = {&b, &e, &a, &c, &d, &ep};
    ParseTableBuilder pr;
    ParseTable table = pr.getParseTable(&S, non, term);

    cout << "first --------------------" << "\n";
    for(pair<Symbol,set<Terminal>> keyVal:pr.firstSets){
        cout << "("+keyVal.first.getName() + "): {";
        for(Terminal t :keyVal.second){
            cout << t.getName() + " ";
        }
        cout <<"}\n";
    }
    cout << "follow --------------------" << "\n";
    for(pair<NonTerminal,set<Terminal>> keyVal:pr.followSets){
        cout << "("+keyVal.first.getName() + "): {";
        for(Terminal t :keyVal.second){
            cout << t.getName() + " ";
        }
        cout <<"}\n";
    }

    table.printTable();
    cout << endl;

    InputBuffer input(vector<string>{"c","e","a","d","b",to_string(END_MARKER)});
    LL1Parser parser(input, table);
    parser.parseGrammar();
    */
     return 0;
}

#endif