cmake_minimum_required(VERSION 3.10)
project(Compilers)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(NFA)
include_directories("DFA")

add_executable(Compilers
        NFA/NFABuilder.cpp
        NFA/NFABuilder.h
        NFA/NFAFragment.cpp
        NFA/NFAFragment.h
        NFA/NFAState.cpp
        NFA/NFAState.h
        "DFA/DFABuilder.cpp"
        "DFA/DFABuilder.h"
        "DFA/DFAGraph.cpp"
        "DFA/DFAGraph.h"
        "DFA/NFAToDFAParser.cpp"
        "DFA/NFAToDFAParser.h"
        CMakeLists.txt
        DFAOptimizer.cpp
        DFAOptimizer.h
        FiniteAutomata.cpp
        FiniteAutomata.h
        InputToRegexParser.cpp
        InputToRegexParser.h
        main.cpp
        RegexToNFAParser.cpp
        RegexToNFAParser.h
        RegularExpression.cpp
        RegularExpression.h
        DFA/DFAState.cpp
        DFA/DFAState.h
        Token.h
        Token.cpp)
