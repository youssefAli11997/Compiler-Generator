//
// Created by hp on 20/04/02019.
//

#include "Production.h"
#include "Symbol.h"
#include "Terminal.h"
#include "ParserContract.h"

vector<Symbol*> Production::getSymbols() {
    return symbols;
}


set<Terminal> Production::getFirstSet(map <Symbol, set<Terminal>> firstSet) {
    set<Terminal> res;
    for(int i = 0 ; i < symbols.size() ; i ++){
        Symbol sym = *symbols[i];
        if(firstSet[sym].size() == 1){
            vector<Terminal> vt(firstSet[sym].begin(),firstSet[sym].end());
            if(vt[0].getName() == to_string(EPSILON)){
                continue;
            }
        }
        for(Terminal t:firstSet[sym]) {
            res.insert(t);
        }
        break;
    }
    if(res.size() == 0)
        res.insert(Terminal(to_string(EPSILON)));
    return res;
}
