//
// Created by youss on 4/9/2019.
//

#include <string>
#include <vector>

using namespace std;

#ifndef COMPILER_GENERATOR_SYMBOLTABLE_H
#define COMPILER_GENERATOR_SYMBOLTABLE_H


class SymbolTable {

public:
    static void addIdentifier(string name); // To be edited (add more arguments) later

private:
    static vector<string> ids;
};


#endif //COMPILER_GENERATOR_SYMBOLTABLE_H
