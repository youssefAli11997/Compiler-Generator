//
// Created by hp on 25/03/02019.
//

#include "InfixToPostfixConverter.h"

// greater has higher precedence
map<char, int> InfixToPostfixConverter::precedence = {{'(',1}, {'|',2}, {DOT_OPERATOR,3}, {'*',4}, {'+',5}};


string InfixToPostfixConverter::convert(string infix){
    string postfix = "";
    string formattedInfix = addExplicitConcatOp(removeBlanks(infix));
    stack<char> stack;
    char ch;
    bool escaped = false;
    for(int i=0;i<formattedInfix.size();i++){
        ch = formattedInfix[i];
        if(ch == ESCAPE){
            if(!escaped)
                escaped = true;
            stack.push(ch);
        }
        else if(ch == '(' && !escaped){
            stack.push(ch);
        }else if(ch == ')' && !escaped){
            while(stack.top()!='('){
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        }else{
            if(escaped)
                escaped = false;
            while(!stack.empty()){
                char top = stack.top();
                if(getPrecedence(top) >= getPrecedence(ch)){
                    postfix += stack.top();
                    stack.pop();
                } else
                    break;
            }
            stack.push(ch);
        }
    }
    while(!stack.empty()){
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

string InfixToPostfixConverter::addExplicitConcatOp(string regex){
    string newRegex = "";
    char current, next;
    int i;
    for(i=0;i<regex.size()-1;i++){
        current = regex[i];
        next = regex[i+1];
        newRegex += current;
        if(current!='(' && next!=')' && !isRegexOperator(next) && !isBinaryOperator(current) && current!=ESCAPE){
            newRegex += DOT_OPERATOR;
        }
    }
    newRegex += regex[i];   // last char
    return newRegex;
}

int InfixToPostfixConverter::getPrecedence(char op){
    if(precedence.find(op) != precedence.end())
        return precedence[op];
    return MAX_PRECEDENCE;
}

bool InfixToPostfixConverter::isRegexOperator(char c){
    return (c=='|') || (c=='*') || (c=='+');
}

bool InfixToPostfixConverter::isBinaryOperator(char c){
    return c == '|';
}

string InfixToPostfixConverter::removeBlanks(string s){
    string newstring = "";
    for(int i=0;i<s.size();i++){
        if(!BLANK(s[i])){
            newstring += s[i];
        }
    }
    return newstring;
}