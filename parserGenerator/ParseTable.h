//
// Created by hp on 20/04/02019.
//

#ifndef COMPILERS_PARSETABLE_H
#define COMPILERS_PARSETABLE_H

#include <map>
#include "Terminal.h"
#include "Production.h"
#include "NonTerminal.h"
#include "ParserContract.h"

class ParseTable {

    class Entry {
    public:
        int type;
        Production* production;
        Entry(int type);
        Entry(int type, Production* prod);
    };

    class Key {
    public:
        string x;
        string y;
        Key(string x, string y);
        bool operator<(const Key& k) const
        {
            if(x == k.x){
                return y.compare(k.y) < 0;
            }
            return x.compare(k.x) < 0;
        }
    };

private:
    map<Key, Entry> table; // should be a vector not a single entry
    NonTerminal* startSymbolPtr;

public:
    NonTerminal* getStartSymbolPtr();
    int getEntryType(NonTerminal,Terminal);
    Production* getProduction(NonTerminal,Terminal);
    void addSyncEntry(NonTerminal,Terminal);
    void addProductionEntry(NonTerminal,Terminal,Production*);
};



#endif //COMPILERS_PARSETABLE_H
