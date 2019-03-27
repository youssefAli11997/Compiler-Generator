//
// Created by Shazly on 3/24/2019.
//

#ifndef COMPILERS_DFABUILDER_H
#define COMPILERS_DFABUILDER_H

#include <DFAState.h>
#include "NFA/NFAState.h"
#include "DFAGraph.h"

class DFABuilder {
public:

    DFABuilder(NFAState s){
        startState = s;
    }
    DFAGraph buildDFA();

private:
    NFAState startState;
    map<DFAState, vector< pair<DFAState, char> > > graph;
    void convertInputToGraph(NFAState state);
    };


#endif //COMPILERS_DFABUILDER_H
