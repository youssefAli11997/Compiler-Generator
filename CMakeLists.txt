cmake_minimum_required(VERSION 3.10)
project(Compilers)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)
include_directories(lexerGenerator/DFA)
include_directories(lexerGenerator/NFA)
include_directories(lexerGenerator/Utilities)

add_executable(Compilers
        lexerGenerator/DFA/DFABuilder.cpp
        lexerGenerator/DFA/DFABuilder.h
        lexerGenerator/DFA/DFAGraph.cpp
        lexerGenerator/DFA/DFAGraph.h
        lexerGenerator/DFA/DFAState.cpp
        lexerGenerator/DFA/DFAState.h
        "lexerGenerator/DFA/NFA Example.txt"
        lexerGenerator/DFA/NFAToDFAParser.cpp
        lexerGenerator/DFA/NFAToDFAParser.h
        lexerGenerator/NFA/NFABuilder.cpp
        lexerGenerator/NFA/NFABuilder.h
        lexerGenerator/NFA/NFAFragment.cpp
        lexerGenerator/NFA/NFAFragment.h
        lexerGenerator/NFA/NFAState.cpp
        lexerGenerator/NFA/NFAState.h
        lexerGenerator/Utilities/InfixToPostfixConverter.cpp
        lexerGenerator/Utilities/InfixToPostfixConverter.h
        lexerGenerator/Utilities/LexicalContract.h
        lexerGenerator/DFAOptimizer.cpp
        lexerGenerator/DFAOptimizer.h
        lexerGenerator/InputToRegexParser.cpp
        lexerGenerator/InputToRegexParser.h
        lexerGenerator/Lexer.cpp
        lexerGenerator/Lexer.h
        lexerGenerator/lexer_input
        lexerGenerator/lexer_output
        lexerGenerator/lexerMain.cpp
        lexerGenerator/RegularExpression.cpp
        lexerGenerator/RegularExpression.h
        lexerGenerator/rules_input
        lexerGenerator/simple_lexical_input
        lexerGenerator/SymbolTable.cpp
        lexerGenerator/SymbolTable.h
        lexerGenerator/Token.cpp
        lexerGenerator/Token.h parserGenerator/GrammarScanner.cpp parserGenerator/GrammarScanner.h parserGenerator/LL1Parser.cpp parserGenerator/LL1Parser.h parserGenerator/NonTerminal.cpp parserGenerator/NonTerminal.h parserGenerator/ParserContract.h parserGenerator/ParseTable.cpp parserGenerator/ParseTable.h parserGenerator/ParseTableBuilder.cpp parserGenerator/ParseTableBuilder.h parserGenerator/Production.cpp parserGenerator/Production.h parserGenerator/Symbol.cpp parserGenerator/Symbol.h parserGenerator/Terminal.cpp parserGenerator/Terminal.h parserGenerator/parserMain.cpp)
