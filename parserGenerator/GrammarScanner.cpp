//
// Created by hp on 20/04/02019.
//

#include "GrammarScanner.h"

NonTerminal* GrammarScanner::startSymbolPtr;
set<NonTerminal *> GrammarScanner::nonTerminals;
set<Terminal *> GrammarScanner::Terminals;

vector<string> lines;
vector<vector<string>> lineWords;

void GrammarScanner::parseInput(string path) {
    parseIntoLines(path);
    parseIntoLineWords();

    // identifying non terminals
    for(int i=0; i<lineWords.size(); i++){
        NonTerminal* nonTerminal = new NonTerminal();
        nonTerminal->setName(lineWords[i][0]);
        nonTerminals.insert(nonTerminal);
    }

    set<NonTerminal*>::iterator it;
    cout<<"******\n";
    for(it = nonTerminals.begin(); it!=nonTerminals.end();it++){
        cout<<(*it)->getName()<<endl;
        for(int i=0; i<lineWords.size(); i++){
            if(lineWords[i][0] == (*it)->getName()){
                parseProductions(*it, lineWords[i]);
                break;
            }
        }
    }
    cout<<"*******\n";

    // set start non terminal ptr
    for(it = nonTerminals.begin(); it!=nonTerminals.end();it++){
        if((*it)->getName() == lineWords[0][0]){
            startSymbolPtr = (*it);
        }
    }

    cout<<"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
    for(it = nonTerminals.begin(); it!=nonTerminals.end();it++){
        cout<<(*it)->getName()<<endl;
        vector<Production*> vec = (*it)->productions;
        for(int i=0; i<vec.size(); i++){
            for(int j=0; j<vec[i]->symbols.size(); j++){
                cout<<vec[i]->symbols[j]->toString()<<endl;
            }
            cout<<"0000000000000000000\n";
        }
        cout<<"11111111111111111111\n";
    }
    cout<<"+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n";
}

void GrammarScanner::parseIntoLines(string path) {
    ifstream file(path);

    string line = "";
    string temp = "";

    while(getline(file, temp)){
        if(temp[0] == '#'){
            if(line != "" && line != " ")
                lines.push_back(line);
            line = temp.substr(2);
        }
        else{
            line += " " + temp;
        }
    }
    lines.push_back(line);

    file.close();
}

void GrammarScanner::parseIntoLineWords() {
    for(int i=0; i<lines.size(); i++){
        lineWords.push_back(vector<string>());

        cout<<lines[i]<<endl;

        string delimiter = " ";
        string word = "";
        int pos = 0;
        while((pos = lines[i].find(delimiter)) != string::npos){
            word = lines[i].substr(0, pos);
            if(word.length() > 0 && word != " ")
                lineWords[i].push_back(word);
            lines[i].erase(0, pos + delimiter.length());
        }
        if(!(lines[i].empty()) && lines[i] != " ")lineWords[i].push_back(lines[i]);
    }
}

void GrammarScanner::parseProductions(NonTerminal *nonTerminal, vector<string> words) {
    vector<string> rule;
    bool ok = false;
    for(int i=2; i<words.size(); i++){
        if(words[i] == "|"){
            parseRule(nonTerminal, rule);
            rule = vector<string>();
        }
        else{
            rule.push_back(words[i]);
        }
    }
    if(!(rule.empty())){
        parseRule(nonTerminal, rule);
    }
}

void GrammarScanner::parseRule(NonTerminal *nonTerminal, vector<string> words) {
    Production* production = new Production();
    for(int i=0; i<words.size(); i++){
        if(words[i][0] == '\''){
            string name = words[i].substr(1, words[i].size()-2);
            if(name == "\\L"){
                name = to_string(EPSILON);
            }
            Terminal* terminal = new Terminal(name);
            Terminals.insert(terminal);
            production->symbols.push_back(terminal);
        }
        else{
            set<NonTerminal*>::iterator it;
            for(it = nonTerminals.begin(); it!=nonTerminals.end();it++){
                if((*it)->getName() == words[i]) {
                    production->symbols.push_back((*it));
                    break;
                }
            }
        }
    }
    nonTerminal->productions.push_back(production);
}

set<NonTerminal*> GrammarScanner::getNonTerminals() {
    return nonTerminals;
}

NonTerminal* GrammarScanner::getStartSymbolPtr() {
    return startSymbolPtr;
}

set<Terminal*> GrammarScanner::getTerminals() {
    return Terminals;
}
