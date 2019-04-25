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
    ofstream fdout ("../parserGenerator/parser_debugging");
    int errorsCount = 0;
    stack<Symbol *> stack;
    stack.push(new Terminal(to_string(END_MARKER)));
    stack.push(parseTable.getStartSymbolPtr());
    Symbol *top;
    string token;
    while (inputBuffer.hasNextToken()) {
        token = inputBuffer.getNextToken();
        fdout << "Next token is (" << token  << ")." << endl;
        top = stack.top();
        fdout << "Top of stack token is (" << top->getName() << ")." << endl;
        if (Terminal *d = dynamic_cast<Terminal *>(top)) {
            if (token == top->getName()) {
                if (token == to_string(END_MARKER)) {
                    // completed successfully
                    cout << "matching (" << top->getName() << "), with token (" << token  << ")." << endl;
                    fout << "matching (" << top->getName() << "), with token (" << token  << ")." << endl;
                    fdout << "matching (" << top->getName() << "), with token (" << token  << ")." << endl;
                    cout << "parsing completed."<< endl;
                    fout << "parsing completed."<< endl;
                    fdout << "parsing completed."<< endl;
                    break;
                }
                cout << "matching (" << top->getName() << "), with token (" << token  << ")." << endl;
                fout << "matching (" << top->getName() << "), with token (" << token  << ")." << endl;
                fdout << "matching (" << top->getName() << "), with token (" << token  << ")." << endl;
                inputBuffer.matchCurrentToken();
                stack.pop();
                fdout << "Popping (" << top->getName() << ") from stack." << endl;
            } else if(top->getName() == to_string(EPSILON)) {
                stack.pop();
                fdout << "Popping (EPSILON) from stack." << endl;
            }else{
                stack.pop();
                // error no matching
                cout << "ERROR: missing token (" << top->getName() << "), inserted." << endl;
                fout << "ERROR: missing token (" << top->getName() << "), inserted." << endl;
                fdout << "ERROR: missing token (" << top->getName() << "), inserted." << endl;
                errorsCount++;
                fdout << "Popping (" << top->getName() << ") from stack." << endl;
            }
        } else if (NonTerminal *d = dynamic_cast<NonTerminal *>(top)) {
            int entryType = parseTable.getEntryType(*d, Terminal(token));
            if (entryType == EMPTY_ENTRY) {
                cout << "ERROR: illegal (" << top->getName() << "), discard token (" << token  << ")." << endl;
                fout << "ERROR: illegal (" << top->getName() << "), discard token (" << token  << ")." << endl;
                fdout << "ERROR: illegal (" << top->getName() << "), discard token (" << token  << ")." << endl;
                errorsCount++;
                inputBuffer.matchCurrentToken();
            } else if (entryType == PRODUCTION_ENTRY) {
                Production *prod = parseTable.getProduction(*d, Terminal(token));
                stack.pop();
                cout << d->getName() << " --> " << prod->toString() << endl;
                fout << d->getName() << " --> " << prod->toString() << endl;
                fdout << d->getName() << " --> " << prod->toString() << endl;
                fdout << "Popping (" << top->getName() << ") from stack." << endl;
                for (int i = prod->getSymbols().size() - 1; i >= 0; i--) {
                    stack.push(prod->getSymbols()[i]);
                    fdout << "Pushing (" << prod->getSymbols()[i]->getName() << ") to stack." << endl;
                }
            } else if (entryType == SYNC_ENTRY) {
                stack.pop();
                fdout << "Found SYNC entry. Popping (" << top->getName() << ") from stack." << endl;
            } else if (entryType == INVALID) {
                // error
                fdout << "Found INVALID entry" << endl;
            }
        }else{
            cout << "Can't cast in parseGrammar()" << endl;
            fout << "Can't cast in parseGrammar()" << endl;
            fdout << "Can't cast in parseGrammar()" << endl;
        }
    }
    cout << "Number of errors: " << errorsCount << endl;
    fout << "Number of errors: " << errorsCount << endl;
    fdout << "Number of errors: " << errorsCount << endl;

    fout.close();
    fdout.close();

}