//
// Created by hp on 20/04/02019.
//

#include "NonTerminal.h"
#include "Terminal.h"
#include "Symbol.h"
#include "Production.h"

set<Terminal*> NonTerminal::getFollowSet() {
    return followSet;
}

void NonTerminal::addToFollowSet(Terminal* t) {
    followSet.insert(t);
}

void NonTerminal::addToFollowSet(set<Terminal*> s) {
    for(auto elem: s){
        followSet.insert(elem);
    }
}

string NonTerminal::toString() {
    return "NonTerminal: " + name;
}