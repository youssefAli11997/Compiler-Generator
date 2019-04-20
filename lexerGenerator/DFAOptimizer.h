//
// Created by youss on 3/15/2019.
//

#ifndef COMPILER_GENERATOR_DFAOPTIMIZER_H
#define COMPILER_GENERATOR_DFAOPTIMIZER_H


#include <lexerGenerator/DFA/DFAGraph.h>

class DFAOptimizer {
    public:
        DFAGraph getOptimizedGraph(DFAGraph graph);
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
        DFAGraph turnIntoDFAGraph();
        DFAState getRepresentative(DFAState state);
        bool matchingTokens(vector<Token> tokens1, vector<Token> tokens2);
};


#endif //COMPILER_GENERATOR_DFAOPTIMIZER_H
