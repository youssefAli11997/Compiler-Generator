//
// Created by youss on 4/9/2019.
//

#include "SymbolTable.h"

vector<string> SymbolTable::ids;

void SymbolTable::addIdentifier(string name) {
    ids.push_back(name);
}
