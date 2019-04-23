//
// Created by hp on 20/04/02019.
//

#include "ParseTable.h"

ParseTable::Key::Key(string x, string y) {
    this->x = x;
    this->y = y;
}

ParseTable::Entry::Entry(int type) {
    this->type = type;
}

ParseTable::Entry::Entry(int type, Production* prod) {
    this->type = type;
    this->production = prod;
}

NonTerminal* ParseTable::getStartSymbolPtr() {
    return this->startSymbolPtr;
}

void ParseTable::addSyncEntry(NonTerminal x, Terminal y) {
    Key key(x.getName(),y.getName());
    Entry entry(SYNC_ENTRY);
    table.insert(make_pair(key,entry));
}

int ParseTable::getEntryType(NonTerminal x, Terminal y) {
    Key key(x.getName(),y.getName());
    map<Key,Entry>::iterator it;
    it = table.find(key);
    if(it != table.end()){
        return it->second.type;
    }
    return EMPTY_ENTRY;
    // check INVALID_ENTRY
}

Production* ParseTable::getProduction(NonTerminal x, Terminal y) {
    // TODO
}