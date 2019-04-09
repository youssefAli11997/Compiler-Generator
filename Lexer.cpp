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
    bool ok = false;
    for(int i=0; i<InputToRegexParser::punctuationSymbols.size(); i++){
        if(word == InputToRegexParser::punctuationSymbols[i]){
            lexemes.push_back(word);
            return;
        }
        string delimiter = InputToRegexParser::punctuationSymbols[i];
        //if(delimiter == ",")cout<<"delimiter: "<<delimiter<<endl;
        //cout<<";"<<endl;
        string lexeme;
        int pos = 0;
        while((pos = word.find(delimiter)) != string::npos){
            if(delimiter == "(")cout<<"posssssssss:  --> "<<pos<<endl;
            if(pos > 0)
                lexeme = word.substr(0, (unsigned int)pos);
            else
                lexeme = word.substr((unsigned int)pos+1, word.length());

            int pos2 = 0, count = 0;
            while((pos2 = lexeme.find(delimiter)) == 0){
                lexemes.push_back(delimiter);
                lexeme = lexeme.substr((unsigned int)pos2+1, lexeme.length());
                count++;
            }

            cout<<"lexeme: "<<lexeme<<endl;
            splitted = true;
            if(pos == 0){
                lexemes.push_back(delimiter);
                word.erase(0, pos + count + delimiter.length());
            }
            if(word == "(())sum" || word == "))sum" || word == "((int")cout<<"here!!a\n";

            if(lexeme == "sum")cout<<"okkkkkkkkkk!!!\n";
            if(lexemeHasNoPunctuation(lexeme))
                lexemes.push_back(lexeme);
            if(pos > 0) {
                lexemes.push_back(delimiter);
                word.erase(0, pos + delimiter.length());
            }

        }
        if(lexemes.empty() || (lexemes[lexemes.size()-1] != word && ok)) {
            if(word == "(())sum" || word == "))sum" || word == "((int")cout<<"here!!b\n";
            if(lexemeHasNoPunctuation(word))
                lexemes.push_back(word);
            ok = true;
        }
    }
    if(word == "(())sum" || word == "))sum" || word == "((int")cout<<"here!! "<<splitted<<"\n";
    if(!splitted && !ok)
        lexemes.push_back(word);
}

bool Lexer::lexemeHasNoPunctuation(string lexeme) {
    for(int i=0; i<InputToRegexParser::punctuationSymbols.size(); i++){
        if(lexeme.find(InputToRegexParser::punctuationSymbols[i]) != string::npos){
            return false;
        }
    }
    return true;
}
