//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_NONTERMINAL_H
#define COMPILERS_NONTERMINAL_H

#include <set>
#include <vector>
#include <string>
#include "Symbol.h"
#include "Production.h"
using namespace std;

class Terminal;

class NonTerminal: public Symbol{
private:
    set<Terminal*> followSet;


public:
    vector<Production*> productions;
    NonTerminal(): Symbol(){};
    NonTerminal(string name): Symbol(name){};
    set<Terminal*> getFollowSet();
    void addToFollowSet(Terminal* t);
    void addToFollowSet(set<Terminal*> s);
    string toString();
    bool operator ==(const NonTerminal & obj) const
    {
        if (name == obj.name)
            return true;
        else
            return false;
    }
    bool operator< (const NonTerminal & obj) const
    {
        return (name < obj.name);
    }
};


#endif //COMPILERS_NONTERMINAL_H
