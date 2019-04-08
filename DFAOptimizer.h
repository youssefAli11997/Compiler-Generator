//
// Created by youss on 3/15/2019.
//

#ifndef COMPILER_GENERATOR_DFAOPTIMIZER_H
#define COMPILER_GENERATOR_DFAOPTIMIZER_H


#include <DFA/DFAGraph.h>

class DFAOptimizer {
    public:
        vector<vector<DFAState>> getOptimizedGraph(DFAGraph graph);
    private:
        DFAGraph currentWorkingGraph;
        vector<DFAState> acceptanceStates;
        vector<DFAState> nonAcceptanceStates;
        void splitStates();
        void getEquivalentStates();
        void getAllPossibleInputsInDFA();
        set<char> possibleInputs;
        bool matchEqu(DFAState state1, DFAState state2, vector<vector<DFAState>> sets);
        bool checkMatchingEquivalence(vector<vector<DFAState>> set1, vector<vector<DFAState>> set2);
        vector<vector<DFAState>> equivalenceSets;
};


#endif //COMPILER_GENERATOR_DFAOPTIMIZER_H
