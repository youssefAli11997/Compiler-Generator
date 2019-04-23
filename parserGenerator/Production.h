//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PRODUCTION_H
#define COMPILERS_PRODUCTION_H

#include <vector>
#include <map>
#include "Symbol.h"

using namespace std;

// the RHS of a production rule; consisting of symbols.
class Production {
private:

public:
    vector<Symbol*> symbols;
    vector<Symbol*> getSymbols();
    set<Terminal> getFirstSet(map<Symbol,set<Terminal>> firstSet);
};


#endif //COMPILERS_PRODUCTION_H
