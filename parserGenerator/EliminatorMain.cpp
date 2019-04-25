
#include "GrammarScanner.h"
#include "LREliminator.h"
#include "LeftFactoringEliminator.h"

#include "../Driver.h"

#ifdef ELIMINATOR

int main(){

    GrammarScanner::parseInput("../parserGenerator/parser_input");
    NonTerminal* start = GrammarScanner::getStartSymbolPtr();
    set<Terminal*> terminalsSet = GrammarScanner::getTerminals();
    set<NonTerminal*> nonTerminalsSet = GrammarScanner::getNonTerminals();
    vector<Terminal*> terminals;
    cout << "----------------- Terminals --------------"<< endl;
    for(Terminal* t: terminalsSet){
        terminals.push_back(t);
        cout << t->getName() << endl;
    }
    cout << endl;
    cout << "----------------- Non Terminals --------------"<< endl;
    vector<NonTerminal*> nonTerminals;
    for(NonTerminal* t: nonTerminalsSet){
        nonTerminals.push_back(t);
        cout << t->getName() << " --> ";
        for (Production* prod: t->productions) {
            cout << prod->toString()  << "|" << endl;
        }
    }
    cout << endl;


    vector<NonTerminal>NotPointerVecotr,Results1, Result2;
    for(NonTerminal* t: nonTerminals){
        NotPointerVecotr.push_back(*t);
    }

    vector<NonTerminal*>NOLRAndNoLF;
    LREliminator lrEliminator;
    lrEliminator.EliminateLR(NotPointerVecotr ,Results1, start);
    LeftFactoringElimination leftFactoringElimination;
    Result2 = leftFactoringElimination.EliminateLF(Results1, lrEliminator.Newstart);
    for(int i = 0; i < Result2.size(); i++){
        NOLRAndNoLF.push_back(&Result2[i]);
    }
    cout<<"LR And LF Results!!!"<<endl;
    ofstream fout("../parserGenerator/eliminator_output");
    for(int i = 0; i < Result2.size(); i++){
        cout << "# " << Result2[i].getName() << " = ";
        fout << "# " << Result2[i].getName() << " = ";
        for(int j = 0; j < Result2[i].productions.size(); j++){
            for(int u = 0; u < Result2[i].productions[j]->symbols.size(); u++) {
                Symbol* s =  Result2[i].productions[j]->symbols[u];
                if(Terminal* d = dynamic_cast<Terminal*>(s)){
                    if(d->getName() == to_string(EPSILON)){
                        cout << "'\\L' " << endl;
                        fout << "'\\L' " << endl;
                    }else{
                        cout << "'" << d->getName() << "' ";
                        fout << "'" << d->getName() << "' ";
                    }
                }
                else if(NonTerminal* d = dynamic_cast<NonTerminal*>(s)){
                    cout << d->getName() << " ";
                    fout << d->getName() << " ";
                }else{
                    cout << "can't cast the symbol (" << s->getName() << ")." << endl;
                }
            }
            if(j!=Result2[i].productions.size() - 1){
                cout<<" | ";
                fout<<" | ";
            }
        }
        cout<<endl;
        fout<<endl;
    }
    fout.close();
    cout<<"///////////////////////////////End of Bouns//////////////////////////////"<<endl;
}

#endif