#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include "Terminal.h"
#include "Symbol.h"
#include "Production.h"
#include "NonTerminal.h"

#define PARSER

#ifdef PARSER

int main() {

    std::cout << "Hello, Phase 2!" << std::endl;

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

    return 0;
}

#endif