//
// Created by youss on 3/25/2019.
//

#include "Lexer.h"
#include "InputToRegexParser.h"
#include <iostream>
#include <fstream>

vector<string> Lexer::lexemes;

void Lexer::readFile(string path) {
    ifstream file_input (path);
    string line;

    while(getline(file_input, line)){
        parseLine(line);
        cout<<line<<endl;
    }

    file_input.close();

    cout<<"size: "<<lexemes.size()<<endl;
    for(int i=0; i<lexemes.size(); i++){
        cout<<lexemes[i]<<"\n";
    }
}

void Lexer::parseLine(string line) {
    vector<string> words;
    string delimiter = " ";
    string word = "";
    int pos = 0;
    while((pos = line.find(delimiter)) != string::npos){
        word = line.substr(0, pos);
        if(word.length() > 0 && word != " ")
            words.push_back(word);
        line.erase(0, pos + delimiter.length());
    }
    words.push_back(line);

    for(int i=0; i<words.size(); i++){
        parseWord(words[i]);
    }
}

void Lexer::parseWord(string word) {
    cout<<"word: "<<word<<endl;
    bool splitted = false;
    for(int i=0; i<InputToRegexParser::punctuationSymbols.size(); i++){
        if(word == InputToRegexParser::punctuationSymbols[i]){
            lexemes.push_back(word);
            return;
        }
        string delimiter = InputToRegexParser::punctuationSymbols[i];
        string lexeme;
        int pos = 0;
        bool ok = false;
        while((pos = word.find(delimiter)) != string::npos){
            lexeme = word.substr(0, (unsigned int)pos);
            if(lexeme.length() > 0 && lexeme != " ") {
                ok = true;
                splitted = true;
                lexemes.push_back(lexeme);
                lexemes.push_back(delimiter);
            }
            word.erase(0, pos + delimiter.length());

        }
        if(lexemes.size() == 0 || (lexemes[lexemes.size()-1] != word && ok)) {
            lexemes.push_back(word);
            ok = false;
        }
    }
    if(!splitted)
        lexemes.push_back(word);
}