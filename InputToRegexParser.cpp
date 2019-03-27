//
// Created by youss on 3/15/2019.
//
#include "InputToRegexParser.h"

map<string, RegularExpression> InputToRegexParser::regularDefinitions;
vector<Token> InputToRegexParser::tokens;
vector<string> InputToRegexParser::keywords;
vector<string> InputToRegexParser::punctuationSymbols;
int InputToRegexParser::regExCounter = 0;

void InputToRegexParser::readFile(string path){
    //InputToRegexParser::regularDefinitions = map<string, RegularExpression>();
    ifstream file_input (path);
    string line;

    while(getline(file_input, line)){
        parseLine(line);
    }

    file_input.close();
}

void InputToRegexParser::parseLine(string line) {
    vector<string> words;
    string delimiter = " ";
    string word = "";
    int pos = 0;
    while((pos = line.find(delimiter)) != string::npos){
        word = line.substr(0, pos);
        if(word.length() > 0 && word != " ")
            words.push_back(word);
        line.erase(0, pos + delimiter.length());
        //cout<<"'"<<line<<"'\n";
    }
    words.push_back(line);

    //for(int i=0; i<words.size(); i++)
    //    cout<<words[i]<<endl;

    cout<<"------------------------------\n";

    // Regular Definition
    if((words[0][words[0].length()-1] == '=' && words.size() > 1)
        ||(words[1] == "=" && words.size() > 2)){

        RegularExpression RE;
        string name;
        if(words[0][words[0].length()-1] == '='){
            RE.value = vector<string>(words.begin()+1, words.end());
            RE.normalize();
            name = words[0].substr(0, words[0].length()-1);
        }
        else if(words[1] == "="){
            RE.value = vector<string>(words.begin()+2, words.end());
            RE.normalize();
            name = words[0];
        }

        regularDefinitions.insert(make_pair(name, RE));
        cout<<"RD detected!!\n\t"<<name<<endl;
        cout<<RE.toString()<<endl;
    }

    // Regular Expression
    if((words[0][words[0].length()-1] == ':' && words.size() > 1)
       ||(words[1] == ":" && words.size() > 2)){

        regExCounter++;
        RegularExpression RE;
        string name;
        if(words[0][words[0].length()-1] == ':'){
            RE.value = vector<string>(words.begin()+1, words.end());
            RE.normalize();
            name = words[0].substr(0, words[0].length()-1);
        }
        else if(words[1] == ":"){
            RE.value = vector<string>(words.begin()+2, words.end());
            RE.normalize();
            name = words[0];
        }

        Token token = Token(name, RE, regExCounter);

        tokens.push_back(token);
        cout<<"RE detected!!\n\t"<<name<<endl;
        cout<<RE.toString()<<endl;
    }

    // Keyword
    if(words[0][0] == '{'){

        if(words[0][0] == '{' && words[0].length() > 1){
             keywords.push_back(words[0].substr(1, words[0].length()-1));
             for(int i=1; i<words.size(); i++){
                 if(i == words.size()-1){
                     keywords.push_back(words[i].substr(0, words[i].length()-1));
                 } else keywords.push_back(words[i]);
             }
        }
        else if(words[0] == "{"){
            for(int i=1; i<words.size(); i++) {
                if(i == words.size()-1){
                    keywords.push_back(words[i].substr(0, words[i].length()-1));
                } else keywords.push_back(words[i]);
            }
        }

        cout<<"Keywords detected!!\n";
        for(int i=0; i<keywords.size(); i++)
            cout<<keywords[i]<<endl;
    }

    // Punctuation
    if(words[0][0] == '['){

        if(words[0][0] == '[' && words[0].length() > 1){
            punctuationSymbols.push_back(words[0].substr(1, words[0].length()-1));
            for(int i=1; i<words.size(); i++){
                if(i == words.size()-1){
                    punctuationSymbols.push_back(words[i].substr(0, words[i].length()-1));
                } else punctuationSymbols.push_back(words[i]);
            }
        }
        else if(words[0] == "["){
            for(int i=1; i<words.size(); i++) {
                if(i == words.size()-1){
                    punctuationSymbols.push_back(words[i].substr(0, words[i].length()-1));
                } else punctuationSymbols.push_back(words[i]);
            }
        }

        cout<<"Punctuations detected!!\n";
        for(int i=0; i<punctuationSymbols.size(); i++)
            cout<<punctuationSymbols[i]<<endl;
    }
}

void InputToRegexParser::finalizeTokens() {
    //keywords
    for(int i=0; i<keywords.size(); i++){
        vector<string> v;
        v.push_back(keywords[i]);
        RegularExpression re;
        re.value = v;
        tokens.push_back(Token(keywords[i], re, 0));
    }

    //punctuation
    for(int i=0; i<punctuationSymbols.size(); i++){
        vector<string> v;
        v.push_back(punctuationSymbols[i]);
        RegularExpression re;
        re.value = v;
        tokens.push_back(Token(punctuationSymbols[i], re, 0));
    }

    cout<<"********************************\n";
    for(int i=0; i<tokens.size(); i++){
        cout<<tokens[i].toString()<<endl;
    }


}

vector<Token> InputToRegexParser::getTokens(){
    return tokens;
}
