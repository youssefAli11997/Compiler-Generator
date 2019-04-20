//
// Created by hp on 22/03/02019.
//

#include "NFABuilder.h"

NFAState NFABuilder::build(vector<Token> tokens){

    vector<NFAFragment> tokensFragments;
    for(int i=0; i<tokens.size();i++){

        string infixRegex = tokens[i].getRegularExpression().toString();
        string postfixRegex = InfixToPostfixConverter::convert(infixRegex);
        stack<NFAFragment> stack;
        char c;
        bool escaped = false;
        for (int j = 0; j < postfixRegex.size(); j++) {
            c = postfixRegex[j];
            if(c==ESCAPE){
                if(!escaped)
                    escaped = true;
            }else{
                if(escaped){
                    if(c=='L'){
                        c = EPSILON;
                    }
                    NFAState* stateptr = new NFAState();
                    stateptr->addNextState(c, new NFAState());
                    stack.push(NFAFragment(stateptr,stateptr->getNextStates()));
                    escaped = false;
                }else{
                    if(c==DOT_OPERATOR){
                        NFAFragment e2 = stack.top();
                        stack.pop();
                        NFAFragment e1 = stack.top();
                        stack.pop();
                        connect(e1.outStates,e2.startState);
                        stack.push(NFAFragment(e1.startState,e2.outStates));
                    }else if(c=='|'){
                        NFAFragment e2 = stack.top();
                        stack.pop();
                        NFAFragment e1 = stack.top();
                        stack.pop();
                        NFAFragment frag = alternate(e1,e2);
                        stack.push(frag);
                    }else if(c=='*'){
                        NFAFragment e = stack.top();
                        stack.pop();
                        NFAFragment frag = kleeneClosure(e);
                        stack.push(frag);
                    }else if(c=='+'){
                        NFAFragment e = stack.top();
                        stack.pop();
                        NFAFragment frag = positiveClosure(e);
                        stack.push(frag);
                    }else{
                        NFAState* stateptr = new NFAState();
                        stateptr->addNextState(c, new NFAState());
                        stack.push(NFAFragment(stateptr,stateptr->getNextStates()));
                    }
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
    stateptr->addNextState(EPSILON, e1.startState);
    stateptr->addNextState(EPSILON, e2.startState);
    vector<pair<char,NFAState*> > out = concatVectors(e1.outStates, e2.outStates);
    return NFAFragment(stateptr,out);
}

NFAFragment NFABuilder::kleeneClosure(NFAFragment &e){
    NFAState* state = new NFAState();
    state->addNextState(EPSILON, e.startState);
    NFAState* dummyState = new NFAState();
    state->addNextState(EPSILON, dummyState);
    connect(e.outStates, state);
    vector<pair<char,NFAState*> > v;
    v.push_back(make_pair(EPSILON,dummyState));
    return NFAFragment(state, v);
}

NFAFragment NFABuilder::positiveClosure(NFAFragment &e){
    NFAState* state = new NFAState();
    state->addNextState(EPSILON, e.startState);
    NFAState* dummyState = new NFAState();
    state->addNextState(EPSILON, dummyState);
    connect(e.outStates, state);
    vector<pair<char,NFAState*> > v;
    v.push_back(make_pair(EPSILON,dummyState));
    return NFAFragment(e.startState, v);
}

NFAState NFABuilder::alternateAll(vector<NFAFragment> &fragments){
    NFAState state(0);   // NFA start state has id = 0
    for(int i=0;i<fragments.size();i++){
        state.addNextState(EPSILON,fragments[i].startState);
    }
    return state;
}