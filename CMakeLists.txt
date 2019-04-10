cmake_minimum_required(VERSION 3.10)
project(Compilers)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(DFA)
include_directories(NFA)
include_directories(Utilities)

add_executable(Compilers
        DFA/DFABuilder.cpp
        DFA/DFABuilder.h
        DFA/DFAGraph.cpp
        DFA/DFAGraph.h
        DFA/DFAState.cpp
        DFA/DFAState.h
        "DFA/NFA Example.txt"
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
        Lexer.cpp
        Lexer.h
        lexer_input
        lexer_output
        main.cpp
        RegularExpression.cpp
        RegularExpression.h
        rules_input
        simple_lexical_input
        SymbolTable.cpp
        SymbolTable.h
        Token.cpp
        Token.h)
