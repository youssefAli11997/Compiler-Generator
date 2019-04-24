//
// Created by Shazly on 4/21/2019.
//
#include <Utilities/LexicalContract.h>
#include <Terminal.h>
#include "Production.h"
#include "LREliminator.h"
Symbol LREliminator::available[100000];
int LREliminator::counter = 0;
bool epslon = false;
bool LRExist(NonTerminal nonTerminal){
    string name = nonTerminal.getName();
    vector<Production> productions = nonTerminal.productions;
    bool lrExist = false;
    for(int i = 0; i < productions.size(); i++){
        if(productions[i].symbols[0]->getName() == name){
            lrExist = true;
        }
    }
    return  lrExist;
}

pair<vector<Production>,vector<Production> > getNonLRAndLR(NonTerminal nonTerminal){
    string name = nonTerminal.getName();
    vector<Production> productions = nonTerminal.productions;
    vector<Production> nonLR, LR;
    for(int i = 0; i < productions.size(); i++){
        if(productions[i].symbols[0]->getName() != name){
            if(productions[i].symbols[0]->getName() != to_string(EPSILON))
                nonLR.push_back(productions[i]);
            else
                epslon = true;
        }
        else{
            productions[i].symbols.erase(productions[i].symbols.begin());
            LR.push_back(productions[i]);
        }
    }
    return make_pair(nonLR, LR);
}

void LREliminator::eliminateLRFromOneRule(NonTerminal nonTerminal, vector<NonTerminal> &answer){
    string name = nonTerminal.getName();
    vector<Production> production = nonTerminal.productions;
    epslon = false;
    if(!LRExist(nonTerminal)){
        answer.push_back(nonTerminal);
        return;
    }
    pair<vector<Production>,vector<Production> > nonLRPoductionAndLRProduction = getNonLRAndLR(nonTerminal);
    vector<Production> LRProduction = nonLRPoductionAndLRProduction.second, nonLRProduction = nonLRPoductionAndLRProduction.first;
    string newName = name + "_LRdash";
    NonTerminal newNonTerminal(newName);
    int aa = counter;
    available[counter++] = newNonTerminal;
    nonTerminal.productions.clear();
    for(int i = 0; i < LRProduction.size(); i++){
        LRProduction[i].symbols.push_back(&available[aa]);
        newNonTerminal.productions.push_back(LRProduction[i]);
    }
    if(nonLRProduction.size() != 0 || epslon){ // Add epsilon production to new Non terminal
        Terminal epsilonTerminal(to_string(EPSILON) );
        Production epsilonproduction;
        available[counter++] = epsilonTerminal;
        epsilonproduction.symbols.push_back(&available[counter - 1]);
        newNonTerminal.productions.push_back(epsilonproduction);
    }
    for(int i = 0; i < nonLRProduction.size(); i++){
        nonLRProduction[i].symbols.push_back(&available[aa]);
        nonTerminal.productions.push_back(nonLRProduction[i]);
    }
    if(nonLRProduction.size() == 0){ // All Productions have LR.
        Production temp;
        temp.symbols.push_back(&available[aa]);
        nonTerminal.productions.push_back(temp);
    }

    answer.push_back(nonTerminal);
    answer.push_back(newNonTerminal);

}
void LREliminator::EliminateLR(vector<NonTerminal> nonTerminals, vector<NonTerminal> &answer){
    for(int i = 0; i < nonTerminals.size(); i++){
        eliminateLRFromOneRule(nonTerminals[i], answer);
      /*  for(int j = 0; j < answer.size(); j++){
            if(answer[j].getName() == "Edash") {
                cout << &answer[j] << endl;
                cout << answer[j].productions[0].symbols[1] << endl;
            }
        }*/
       // cout<< &answer[answer.size() - 1]<<endl;
        /*for(int j = 0; j < nonLR.size(); j++){
                 answer.push_back(nonLR[j]);
             }*/
        }

}
