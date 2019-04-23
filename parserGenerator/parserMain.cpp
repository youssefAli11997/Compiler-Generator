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

    /*std::cout << "Hello, Phase 2!" << std::endl;

    stack<Symbol*> stack;
    Terminal t("t");
    NonTerminal nt("nt");

    // implicit upcasting
    Symbol* s1;
    s1 = &t;
    stack.push(s1);
    cout << s1->toString() << endl;
    s1 = &nt;
    stack.push(s1);
    cout << s1->toString() << endl;

    // explicit downcasting
    Symbol* s2;
    while(!stack.empty()){
        s2 = stack.top();
        stack.pop();
        if(Terminal* d = dynamic_cast<Terminal*>(s2)){
            cout << d->toString() << endl;
        }else if(NonTerminal* d = dynamic_cast<NonTerminal*>(s2)){
            cout << d->toString() << endl;
        }
    }

    return 0;*/
    /*NonTerminal e("E");
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
    e.productions = {te_};
    e_.productions = {te__, epp};
    t.productions = {ft_};
    t_.productions = {ft__, epp};
    f.productions = {e__, id_};
    vector<NonTerminal> non = {e, e_, t, t_, f};
    vector<Terminal> term = {ep, id, p1, p2, plus, ast};
    ParseTableBuilder pr;
    pr.getParseTable(e, non, term);*/

    cout<<"hereeeeee!!\n";
    GrammarScanner::parseInput("../parserGenerator/parser_input");

    return 0;
}

#endif