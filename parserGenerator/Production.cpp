//
// Created by hp on 20/04/02019.
//

#include "Production.h"
#include "Symbol.h"
#include "Terminal.h"
#include "ParserContract.h"

vector<Symbol> Production::getSymbols() {
    return symbols;
}

set<Terminal> Production::getFirstSet() {
    set<Terminal> res;
    for(Symbol symbol:symbols){
        if(symbol.getFirstSet().size() == 1){
            vector<Terminal*> vt(symbol.getFirstSet().begin(),symbol.getFirstSet().end());
            if(vt[0]->getName() == to_string(EPSILON)){
                continue;
            }
        }
        for(Terminal* t:symbol.getFirstSet()) {
            Terminal tt = *t;
            res.insert(tt);
        }
        break;
    }
    if(res.size() == 0)
        res.insert(Terminal(to_string(EPSILON)));
    return res;
}