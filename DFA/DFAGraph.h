//
// Created by Shazly on 3/24/2019.
//

#ifndef COMPILERS_DFAGRAPH_H
#define COMPILERS_DFAGRAPH_H


#include <DFAState.h>

class DFAGraph {
public:
    DFAState startState;
    map<DFAState, vector<pair<DFAState, char> > > graph;


};


#endif //COMPILERS_DFAGRAPH_H
