//
// Created by youss on 3/15/2019.
//

#include "RegularExpression.h"
#include "InputToRegexParser.h"

void RegularExpression::normalize() {
    for(int i=0; i<value.size(); i++){
        //ranges
        if(value[i] == "-" && i > 0 && i < value.size()-1){
            char left = value[i-1][0];
            char right = value[i+1][0];
            string s = " ";
            s[0] = left;

            for(char c=left+1; c<=right; c++){
                s += "| ";
                s[s.length()-1] = c;
            }

            vector<string> temp = vector<string>(value.begin(), value.begin()+i-1);
            temp.push_back(s);
            cout<<i+1<<" "<<value.size()<<endl;
            for(int j=i+2; j<value.size(); j++){
                cout<<'!'<<value[j]<<'!';
                temp.push_back(value[j]);
            }
            cout<<"\n";
            value = temp;
        }

        else if(value[i].find('-') != string::npos){
            size_t index = value[i].find('-');
            if(index > 0 && index < value[i].size()-1){
                char left = value[i][index-1];
                char right = value[i][index+1];
                string s = " ";
                s[0] = left;

                for(char c=left+1; c<=right; c++){
                    s += "| ";
                    s[s.length()-1] = c;
                }

                vector<string> temp;
                if(i>0)
                    temp = vector<string>(value.begin(), value.begin()+i-1);
                temp.push_back(s);
                cout<<i+1<<" "<<value.size()<<endl;
                for(int j=i+1; j<value.size(); j++){
                    cout<<'!'<<value[j]<<'!';
                    temp.push_back(value[j]);
                }
                cout<<"\n";
                value = temp;
            }
        }

        //regular definitions
        map<string, RegularExpression>::iterator it;
        for(it = InputToRegexParser::regularDefinitions.begin(); it != InputToRegexParser::regularDefinitions.end(); it++){
            size_t startingIndex = value[i].find(it->first);
            char checkChar = value[i][startingIndex + it->first.size()];
            if(startingIndex != string::npos
            && !((checkChar >= 'a' && checkChar <= 'z') || (checkChar >= 'A' && checkChar <= 'Z'))){
                string s = value[i].substr(0, startingIndex);
                s += "(";
                string rdv;
                for(int k=0; k<it->second.value.size(); k++){
                    if(k>0)
                        rdv += " ";
                    rdv += it->second.value[k];
                }
                s += rdv + ")";
                s+= value[i].substr(startingIndex + it->first.size(), value[i].size());
                value[i] = s;
            }
        }
    }
}

string RegularExpression::toString() {
    string re = "";
    for(int i=0; i<value.size(); i++)
        re += value[i] + " ";
    re += "\n";

    return re;
}
