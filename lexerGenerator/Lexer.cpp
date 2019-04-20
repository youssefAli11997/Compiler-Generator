//
// Created by youss on 3/25/2019.
//

#include "Lexer.h"
#include "InputToRegexParser.h"
#include "SymbolTable.h"
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
    for(int i=0; i<InputToRegexParser::modifiedPunctuationSymbols.size(); i++){
        if(word == InputToRegexParser::modifiedPunctuationSymbols[i]){
            lexemes.push_back(word);
            return;
        }
        string delimiter = InputToRegexParser::modifiedPunctuationSymbols[i];
        //if(delimiter == ",")cout<<"delimiter: "<<delimiter<<endl;
        //cout<<";"<<endl;
        string lexeme;
        int pos = 0;
        while((pos = word.find(delimiter)) != string::npos){
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

            if(lexemeHasNoPunctuation(lexeme))
                lexemes.push_back(lexeme);
            if(pos > 0) {
                lexemes.push_back(delimiter);
                word.erase(0, pos + delimiter.length());
            }

        }
        if(lexemes.empty() || (lexemes[lexemes.size()-1] != word && ok)) {
            if(lexemeHasNoPunctuation(word))
                lexemes.push_back(word);
            ok = true;
        }
    }
    if(!splitted && !ok)
        lexemes.push_back(word);
}
string getStringFromIndexXToEnd(string str, int x){
    string answer = "";
    for(int i = x+1; i < str.size(); i++)
        answer += str[i];
    return answer;
}
bool Lexer::lexemeHasNoPunctuation(string lexeme) {
    for(int i=0; i<InputToRegexParser::modifiedPunctuationSymbols.size(); i++){
        if(lexeme.find(InputToRegexParser::modifiedPunctuationSymbols[i]) != string::npos){
            return false;
        }
    }
    return true;
}

void Lexer::runLexicalAnalysis(DFAGraph graph) {
    ofstream file_output ("../lexerGenerator/lexer_output");
    int lastAcceptedIndex = -1;
    Token* lastAcceptedToken;
    for(int i=0; i<lexemes.size(); i++){
        lastAcceptedIndex = -1;
        cout<<"lx:  "<<lexemes[i]<<endl;
        if(lexemes[i] == "" || lexemes[i] == " ")continue;
        DFAState currentState = graph.startState;
        for(int j=0; j<lexemes[i].length(); j++){
            currentState = graph.getNextState(currentState, lexemes[i][j]);
            if(currentState.end){
                Token temp = (currentState.getHighestPriorityToken());
                lastAcceptedToken = &temp;
                lastAcceptedIndex = j;
            }
        }
        if(currentState.end == true){
            Token token = currentState.getHighestPriorityToken();
            if(token.getPriority() == 0){
                file_output<<token.getName()<<endl;
            }
            else{
                file_output<<token.getName()<<endl;
                if(token.getName() == "id")
                    SymbolTable::addIdentifier(lexemes[i]);
            }
        }
        else{
            if(lastAcceptedIndex == -1)
                file_output<<"ERROR("<<lexemes[i]<<" cannot be matched with any token)"<<endl;
            else{
                string restString = getStringFromIndexXToEnd(lexemes[i], lastAcceptedIndex);
                lexemes.insert(lexemes.begin() + i + 1, restString);
                if(lastAcceptedToken->getPriority() == 0){
                    file_output<<lastAcceptedToken->getName()<<endl;
                }
                else{
                    file_output<<lastAcceptedToken->getName()<<endl;
                    if(lastAcceptedToken->getName() == "id")
                        SymbolTable::addIdentifier(lexemes[i].substr(0, lexemes[i].length() - restString.length()));
                }
                lastAcceptedIndex = -1;
            }
        }
    }

    file_output.close();
}
