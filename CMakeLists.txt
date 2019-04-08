cmake_minimum_required(VERSION 3.13)
project(Compiler_Generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(DFA)
include_directories(NFA)
include_directories(Utilities)

add_executable(Compiler_Generator
        DFA/DFABuilder.cpp
        DFA/DFABuilder.h
        DFA/DFAGraph.cpp
        DFA/DFAGraph.h
        DFA/DFAState.cpp
        DFA/DFAState.h
        DFA/NFAToDFAParser.cpp
        DFA/NFAToDFAParser.h
        NFA/NFABuilder.cpp
        NFA/NFABuilder.h
        NFA/NFAFragment.cpp
        NFA/NFAFragment.h
        NFA/NFAState.cpp
        NFA/NFAState.h
        Utilities/InfixToPostfixConverter.cpp
        Utilities/InfixToPostfixConverter.h
        Utilities/LexicalContract.h
        DFAOptimizer.cpp
        DFAOptimizer.h
        InputToRegexParser.cpp
        InputToRegexParser.h
        main.cpp
        RegularExpression.cpp
        RegularExpression.h
        Token.cpp
        Token.h)
