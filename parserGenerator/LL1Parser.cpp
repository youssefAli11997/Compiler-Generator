//
// Created by hp on 20/04/02019.
//

#include <stack>
#include <iostream>
#include <fstream>
#include "LL1Parser.h"
#include "ParserContract.h"
#include "Terminal.h"

LL1Parser::LL1Parser(InputBuffer input, ParseTable table): inputBuffer(input), parseTable(table) {}

void LL1Parser::parseGrammar() {
    ofstream fout ("../parserGenerator/parser_output");
    int errorsCount = 0;
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
                    cout << "parsing completed."<< endl;
                    fout << "parsing completed."<< endl;
                    break;
                }
                inputBuffer.matchCurrentToken();
                stack.pop();
            } else if(top->getName() == to_string(EPSILON)) {
                stack.pop();
            }else{
                stack.pop();
                // error no matching
                cout << "ERROR: missing token (" << top->getName() << "), inserted." << endl;
                fout << "ERROR: missing token (" << top->getName() << "), inserted." << endl;
                errorsCount++;
            }
        } else if (NonTerminal *d = dynamic_cast<NonTerminal *>(top)) {
            int entryType = parseTable.getEntryType(*d, Terminal(token));
            if (entryType == EMPTY_ENTRY) {
                cout << "ERROR: illegal (" << top->getName() << "), discard token (" << token  << ")." << endl;
                fout << "ERROR: illegal (" << top->getName() << "), discard token (" << token  << ")." << endl;
                errorsCount++;
                inputBuffer.matchCurrentToken();
            } else if (entryType == PRODUCTION_ENTRY) {
                Production *prod = parseTable.getProduction(*d, Terminal(token));
                stack.pop();
                cout << d->getName() << " --> " << prod->toString() << endl;
                fout << d->getName() << " --> " << prod->toString() << endl;
                for (int i = prod->getSymbols().size() - 1; i >= 0; i--) {
                    stack.push(prod->getSymbols()[i]);
                }
            } else if (entryType == SYNC_ENTRY) {
                stack.pop();
            } else if (entryType == INVALID) {
                // error
            }
        }else{
            cout << "Can't cast in parseGrammar()" << endl;
            fout << "Can't cast in parseGrammar()" << endl;
        }
    }
    cout << "Number of errors: " << errorsCount << endl;
    fout << "Number of errors: " << errorsCount << endl;

    fout.close();

}