
//
// Created by Shazly on 4/21/2019.
//
#include <Utilities/LexicalContract.h>
#include <Terminal.h>
#include "Production.h"
#include "LREliminator.h"

bool epslon = false;
bool LRExist(NonTerminal nonTerminal){
    string name = nonTerminal.getName();
    vector<Production*> productions = nonTerminal.productions;
    bool lrExist = false;
    for(int i = 0; i < productions.size(); i++){
        if((*productions[i]).symbols[0]->getName() == name){
            lrExist = true;
        }
    }
    return  lrExist;
}

pair<vector<Production*>,vector<Production*> > getNonLRAndLR(NonTerminal nonTerminal){
    string name = nonTerminal.getName();
    vector<Production*> productions = nonTerminal.productions;
    vector<Production*> nonLR, LR;
    for(int i = 0; i < productions.size(); i++){
        if((*productions[i]).symbols[0]->getName() != name){
            if((*productions[i]).symbols[0]->getName() != to_string(EPSILON))
                nonLR.push_back(productions[i]);
            else
                epslon = true;
        }
        else{
            (*productions[i]).symbols.erase((*productions[i]).symbols.begin());
            LR.push_back(productions[i]);
        }
    }
    return make_pair(nonLR, LR);
}

void LREliminator::eliminateLRFromOneRule(NonTerminal nonTerminal, vector<NonTerminal> &answer){
    string name = nonTerminal.getName();
    vector<Production*> production = nonTerminal.productions;
    epslon = false;
    if(!LRExist(nonTerminal)){
        answer.push_back(nonTerminal);
        return;
    }
    pair<vector<Production*>,vector<Production*> > nonLRPoductionAndLRProduction = getNonLRAndLR(nonTerminal);
    vector<Production*> LRProduction = nonLRPoductionAndLRProduction.second, nonLRProduction = nonLRPoductionAndLRProduction.first;
    string newName = name + "_LRdash";
    NonTerminal* newNonTerminal = new NonTerminal(newName);
    nonTerminal.productions.clear();
    for(int i = 0; i < LRProduction.size(); i++){
        (*LRProduction[i]).symbols.push_back(newNonTerminal);
        newNonTerminal->productions.push_back(LRProduction[i]);
    }
    if(nonLRProduction.size() != 0 || epslon){ // Add epsilon production to new Non terminal
        Terminal* epsilonTerminal = new Terminal(to_string(EPSILON) );
        Production* epsilonproduction = new Production;
        epsilonproduction->symbols.push_back(epsilonTerminal);
        newNonTerminal->productions.push_back(epsilonproduction);
    }
    for(int i = 0; i < nonLRProduction.size(); i++){
        (*nonLRProduction[i]).symbols.push_back(newNonTerminal);
        nonTerminal.productions.push_back(nonLRProduction[i]);
    }
    if(nonLRProduction.size() == 0){ // All Productions have LR.
        Production* temp = new Production;
        temp->symbols.push_back(newNonTerminal);
        nonTerminal.productions.push_back(temp);
    }

    answer.push_back(nonTerminal);
    answer.push_back(*newNonTerminal);

}
void LREliminator::EliminateLR(vector<NonTerminal> nonTerminals, vector<NonTerminal> &answer , NonTerminal* start){
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
    for(int i = 0; i <answer.size(); i++)
        if(answer[i].getName() == start->getName())
            Newstart = start;

}
