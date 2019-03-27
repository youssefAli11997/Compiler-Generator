//
// Created by hp on 22/03/02019.
//

#ifndef COMPILERS_NFABUILDER_H
#define COMPILERS_NFABUILDER_H

#include "bits/stdc++.h"
#include "NFAState.h"
#include "NFAFragment.h"
using namespace std;

#define EPSILON_CHAR '@'

class NFABuilder {
    public:
        NFAState build(vector<string>);

    private:
        void connect(vector<pair<char,NFAState*> > &, NFAState* &);
        vector<pair<char,NFAState*> > concatVectors(vector<pair<char,NFAState*> >, vector<pair<char,NFAState*> >);
        NFAFragment positiveClosure(NFAFragment &e);
        NFAFragment alternate(NFAFragment &e1, NFAFragment &e2);
        NFAFragment kleeneClosure(NFAFragment &e);
        NFAState alternateAll(vector<NFAFragment> &);
};


#endif //COMPILERS_NFABUILDER_H
