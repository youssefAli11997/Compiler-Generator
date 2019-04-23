//
// Created by hp on 20/04/02019.
//

#include <stack>
#include <iostream>
#include "LL1Parser.h"
#include "ParserContract.h"
#include "Terminal.h"

LL1Parser::LL1Parser(InputBuffer input, ParseTable table): inputBuffer(input), parseTable(table) {}

void LL1Parser::parseGrammar() {
/*
    stack<Symbol *> stack;
    stack.push(new Terminal(to_string(END_MARKER)));
    stack.push(parseTable.getStartSymbolPtr());
    Symbol *top;
    string token;
    while (inputBuffer.hasNextToken()) {
        token = inputBuffer.getNextToken();
        top = stack.top();
        if (Terminal *d = dynamic_cast<Terminal *>(top)) {
            if (token == top->getName()) {
                if (token == to_string(END_MARKER)) {
                    // completed successfully
                    return;
                }
                stack.pop();
            } else {
                // error no matching
            }
        } else if (NonTerminal *d = dynamic_cast<NonTerminal *>(top)) {
            int entryType = parseTable.getEntryType(*d, Terminal(token));
            if (entryType == EMPTY_ENTRY) {
                continue;
            } else if (entryType == PRODUCTION_ENTRY) {
                Production *prod = parseTable.getProduction(*d, Terminal(token));
                stack.pop();
                cout << "out: " + prod.toString() << endl;
                for (int i = prod->getSymbols().size() - 1; i >= 0; i--) {
                    stack.push(prod->getSymbols()[i]);
                }
            } else if (entryType == SYNC_ENTRY) {
                stack.pop();
            } else if (entryType == INVALID) {
                // error
            }
        }else{
            cout << "can't cast in parseGrammar()\n" << endl;
        }
    }
    */
}