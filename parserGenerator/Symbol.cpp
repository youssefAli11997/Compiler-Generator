//
// Created by hp on 20/04/02019.
//


#include "Symbol.h"
#include "Terminal.h"

Symbol::Symbol() {}

Symbol::Symbol(string name){
    this->name = name;
}

string Symbol::getName() {
    return name;
}

set<Terminal*> Symbol::getFirstSet() {
    return firstSet;
}

void Symbol::addToFirstSet(Terminal* t) {
    firstSet.insert(t);
}

void Symbol::addToFirstSet(set<Terminal*> s) {
    for(auto elem: s){
        firstSet.insert(elem);
    }
}

string Symbol::toString() {
    return "Symbol: " + name;
}

void Symbol::setName(string nm) {
    name = nm;
}
