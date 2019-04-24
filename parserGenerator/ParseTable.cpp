//
// Created by hp on 20/04/02019.
//

#include <iostream>
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

void ParseTable::addProductionEntry(NonTerminal x, Terminal y, Production * prod) {
    Key key(x.getName(),y.getName());
    Entry entry(PRODUCTION_ENTRY,prod);
    table.insert(make_pair(key,entry));
}

Production* ParseTable::getProduction(NonTerminal x, Terminal y) {
    Key key(x.getName(),y.getName());
    map<Key,Entry>::iterator it;
    it = table.find(key);
    if(it != table.end()){
        return it->second.production;
    }
    return nullptr;
}

void ParseTable::printTable() {
    cout << "start symbol: " + startSymbolPtr->getName() << endl;
    map<Key, Entry>::iterator it;
    for ( it = table.begin(); it != table.end(); it++ ){
        if(it->second.type == PRODUCTION_ENTRY){
            cout << it->first.x + ", " + it->first.y + ": " + it->second.production->toString() << endl;
        }else if(it ->second.type== SYNC_ENTRY){
            cout << it->first.x + ", " + it->first.y + ": " + "SYNC" << endl;
        }else{
            cout << it->first.x + ", " + it->first.y + ": " + "EMPTY or INVALID" << endl;
        }
    }
}

void ParseTable::setStartSymbolPtr(NonTerminal * ptr) {
    startSymbolPtr = ptr;
}