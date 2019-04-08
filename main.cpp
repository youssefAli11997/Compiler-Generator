#include <iostream>
#include <DFA/NFAToDFAParser.h>
#include "InputToRegexParser.h"
#include "NFA/NFABuilder.h"
#include "bits/stdc++.h"
#include "DFAState.h"
#include "Utilities/InfixToPostfixConverter.h"
#include "DFAGraph.h"
#include "DFAOptimizer.h"

using namespace std;

inline bool operator<(DFAState a, DFAState b)
{
    return a.id > b.id;
}

int main() {
    //input parsing and tokens identification code

    /*InputToRegexParser::readFile("../simple_lexical_input");
    InputToRegexParser::finalizeTokens();
    vector<Token> tokens = InputToRegexParser::getTokens();
    NFABuilder builder;
    NFAState nfaStartState = builder.build(tokens);
    cout << nfaStartState.getID() << endl;*/
    /*
    InfixToPostfixConverter::convert("a(bb)+a");
    cout << endl;
     */
/*
=======

>>>>>>> e35ce108ca55384b16d3fa0acd392bf3bebdaa91
    //InputToRegexParser::readFile("../lexical_input");
    DFAState a;
    a.id = 1;
    DFAState b;
    b.id = 1;
    DFAState c;
    c.id = 3;
    DFAState d;
    d.id = 4;
    DFAState e;
    e.id = 5;
    DFAState f;
    f.id = 6;
    f.end = true;
/*
    f.tokens.push_back("id");
    map<DFAState, vector<pair<DFAState, char> > > x, y;
    vector<pair<DFAState, char> >aa;
    aa.push_back(make_pair(f, '@'));
    aa.push_back(make_pair(b, '@'));
    x[a] = aa;
    vector<pair<DFAState, char> >bb;
    bb.push_back(make_pair(c, '1'));
    x[b] = bb;
    vector<pair<DFAState, char> >cc;
    cc.push_back(make_pair(d, '@'));
    x[c] = cc;
    vector<pair<DFAState, char> >dd;
    dd.push_back(make_pair(e, '0'));
    x[d] = dd;
    vector<pair<DFAState, char> >ee;
    ee.push_back(make_pair(f, '@'));
    ee.push_back(make_pair(b, '@'));
    x[e] = ee;
*/
    DFAState a;
    a.id = 1;
    DFAState b;
    b.id = 2;
    DFAState c;
    c.id = 3;
    DFAState d;
    d.id = 4;
    DFAState e;
    e.id = 5;
    e.end = true;
    map<DFAState, vector<pair<DFAState, char> > > x;
    vector<pair<DFAState, char> >aa;
    aa.push_back(make_pair(b, 'a'));
    aa.push_back(make_pair(c, 'b'));
    x[a] = aa;
    vector<pair<DFAState, char> >bb;
    bb.push_back(make_pair(d, 'b'));
    bb.push_back(make_pair(b, 'a'));
    x[b] = bb;
    vector<pair<DFAState, char> >cc;
    cc.push_back(make_pair(c, 'b'));
    cc.push_back(make_pair(b, 'a'));
    x[c] = cc;
    vector<pair<DFAState, char> >dd;
    dd.push_back(make_pair(b, 'a'));
    dd.push_back(make_pair(e, 'b'));
    x[d] = dd;
    vector<pair<DFAState, char> >ee;
    ee.push_back(make_pair(b, 'a'));
    ee.push_back(make_pair(c, 'b'));
    x[e] = ee;
    DFAGraph graph = DFAGraph();
    graph.graph = x;
    DFAOptimizer optimizer;
    vector<vector<DFAState>> sets = optimizer.getOptimizedGraph(graph);
    for(vector<DFAState> set:sets){
        cout << "{ ";
        for(DFAState state:set){
            cout<< state.id << " ";
        }
        cout << "} ";
    }
/*
    NFAToDFAParser *parser;
    vector<pair<DFAState, string>> ggg;
    parser->transferNFAToDFA(x, a, ggg);

    y = parser->getDFA();
    DFAState hh = parser->getStartState();
    for(auto i = y.begin(); i != y.end(); i++){
        cout<<(*i).first.id<<"  "<<endl;
        for(int j = 0; j < (*i).second.size(); j++){
            cout<<(*i).second[j].first.id<<" With Char "<<(*i).second[j].second;
            cout<<endl;
        }
        if((*i).first.id == hh.id)
            cout<<"Start DFAState"<<endl;
        cout<<endl;
    }
*/
/*
map<DFAState, int>z;
    z[a] = 1;
    z[b] = 1;
    cout<<z.size();
    */

     /*
          //          Testing NFA Builder
     NFABuilder builder;
     vector<Token> tokens;
     NFAState nfaStartState = builder.build(tokens);
     cout << nfaStartState.getID() << endl;
     cout << EPSILON << endl;
     */

    return 0;
}