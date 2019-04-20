//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PRODUCTION_H
#define COMPILERS_PRODUCTION_H

#include <vector>
#include "Symbol.h"

using namespace std;

// the RHS of a production rule; consisting of symbols.
class Production {
private:
    vector<Symbol> symbols;
public:
    vector<Symbol> getSymbols();
};


#endif //COMPILERS_PRODUCTION_H
