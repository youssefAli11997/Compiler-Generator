//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_SYMBOL_H
#define COMPILERS_SYMBOL_H

#include <string>
#include <set>
#include <vector>

using namespace std;

class Terminal; // forward declaration
class Production;

// can be terminal or non-terminal
class Symbol {
protected:
    string name;
    set<Terminal*> firstSet;

public:
    Symbol();
    Symbol(string name);
    string getName();
    void setName(string nm);
    set<Terminal*> getFirstSet();
    void addToFirstSet(Terminal* t);
    void addToFirstSet(set<Terminal*> s);
    virtual string toString();
    bool operator ==(const Symbol & obj) const
    {
        if (name == obj.name)
            return true;
        else
            return false;
    }
    bool operator< (const Symbol & obj) const
    {
        return (name < obj.name);
    }

};




#endif //COMPILERS_SYMBOL_H
