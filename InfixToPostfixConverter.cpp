//
// Created by hp on 25/03/02019.
//

#include "InfixToPostfixConverter.h"

map<char, int> InfixToPostfixConverter::precedence = {{'(',1}, {'|',2}, {'.',3}, {'*',4}, {'+',5}};  // greater has higher precedence


string InfixToPostfixConverter::infixToPostfix(string infix){
    string postfix = "";
    string newInfix = addExplicitConcatOp(infix);
    stack<char> stack;
    char ch;
    for(int i=0;i<newInfix.size();i++){
        ch = newInfix[i];
        if(ch == '('){
            stack.push(ch);
        }else if(ch == ')'){
            while(stack.top() == '('){
                postfix += stack.top();
                stack.pop();
            }
            stack.pop();
        }else{
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
        if(current!='(' && next!=')' && !isRegexOperator(next) && !isBinaryOperator(current)){
            newRegex += '.';
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