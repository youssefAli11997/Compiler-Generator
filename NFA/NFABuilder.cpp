//
// Created by hp on 22/03/02019.
//

#include "NFABuilder.h"

NFAState NFABuilder::build(vector<Token> tokens){

    vector<NFAFragment> tokensFragments;
    vector<string> dummyTokens;
    dummyTokens.push_back("abb.+.a.");
    dummyTokens.push_back("aa.b.");
    dummyTokens.push_back("ab|");

    for(int i=0; i<tokens.size();i++){
        string str = dummyTokens[i]; //= InfixToPostfix.getPostfix(tokens[i].pattern);
        stack<NFAFragment> stack;
        char c;
        for (int j = 0; j < str.size(); j++) {
            c = str[j];
            switch(c){
                case '.':{
                    NFAFragment e2 = stack.top();
                    stack.pop();
                    NFAFragment e1 = stack.top();
                    stack.pop();
                    connect(e1.outStates,e2.startState);
                    stack.push(NFAFragment(e1.startState,e2.outStates));
                    break;
                }
                case '|':{
                    NFAFragment e2 = stack.top();
                    stack.pop();
                    NFAFragment e1 = stack.top();
                    stack.pop();
                    NFAFragment frag = alternate(e1,e2);
                    stack.push(frag);
                    break;
                }
                case '*':{
                    NFAFragment e = stack.top();
                    stack.pop();
                    NFAFragment frag = kleeneClosure(e);
                    stack.push(frag);
                    break;
                }
                case '+':{
                    NFAFragment e = stack.top();
                    stack.pop();
                    NFAFragment frag = positiveClosure(e);
                    stack.push(frag);
                    break;
                }
                default:{
                    NFAState* stateptr = new NFAState();
                    stateptr->addNextState(c, new NFAState());
                    stack.push(NFAFragment(stateptr,stateptr->getNextStates()));
                    break;
                }
            }
        }
        NFAFragment frag = stack.top();
        stack.pop();
        NFAState* matchState = new NFAState();
        matchState->setMatching(true);
        matchState->setToken(tokens[i]);
        connect(frag.outStates,matchState);
        tokensFragments.push_back(frag);
    }
    // compile the tokens together (Alternating them)
    NFAState nfaStartState = alternateAll(tokensFragments);
    return nfaStartState;
}

void NFABuilder::connect(vector<pair<char,NFAState*> > &v, NFAState* &s){
    for(int i=0;i<v.size();i++){
        *v[i].second = *s;
    }
}

vector<pair<char,NFAState*> > NFABuilder::concatVectors(vector<pair<char,NFAState*> > v1, vector<pair<char,NFAState*> > v2){
    vector< pair<char,NFAState*>> v;
    v.insert(v.begin(),v1.begin(),v1.end());
    v.insert(v.end(),v2.begin(),v2.end());
    return v;
}

NFAFragment NFABuilder::alternate(NFAFragment &e1, NFAFragment &e2){
    NFAState* stateptr = new NFAState();
    stateptr->addNextState(EPSILON_CHAR, e1.startState);
    stateptr->addNextState(EPSILON_CHAR, e2.startState);
    vector<pair<char,NFAState*> > out = concatVectors(e1.outStates, e2.outStates);
    return NFAFragment(stateptr,out);
}

NFAFragment NFABuilder::kleeneClosure(NFAFragment &e){
    NFAState* state = new NFAState();
    state->addNextState(EPSILON_CHAR, e.startState);
    NFAState* dummyState = new NFAState();
    state->addNextState(EPSILON_CHAR, dummyState);
    connect(e.outStates, state);
    vector<pair<char,NFAState*> > v;
    v.push_back(make_pair(EPSILON_CHAR,dummyState));
    return NFAFragment(state, v);
}

NFAFragment NFABuilder::positiveClosure(NFAFragment &e){
    NFAState* state = new NFAState();
    state->addNextState(EPSILON_CHAR, e.startState);
    NFAState* dummyState = new NFAState();
    state->addNextState(EPSILON_CHAR, dummyState);
    connect(e.outStates, state);
    vector<pair<char,NFAState*> > v;
    v.push_back(make_pair(EPSILON_CHAR,dummyState));
    return NFAFragment(e.startState, v);
}

NFAState NFABuilder::alternateAll(vector<NFAFragment> &fragments){
    NFAState state(0);   // NFA start state has id = 0
    for(int i=0;i<fragments.size();i++){
        state.addNextState(EPSILON_CHAR,fragments[i].startState);
    }
    return state;
}