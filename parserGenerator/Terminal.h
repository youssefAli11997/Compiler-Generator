//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_TERMINAL_H
#define COMPILERS_TERMINAL_H

#include <set>
#include <string>
#include "Symbol.h"
using namespace std;

class Terminal: public Symbol {

public:
    Terminal(string name): Symbol(name){};
    string toString();



};



#endif //COMPILERS_TERMINAL_Hg
