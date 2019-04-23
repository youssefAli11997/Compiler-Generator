//
// Created by hp on 23/04/02019.
//

#ifndef COMPILERS_INPUTBUFFER_H
#define COMPILERS_INPUTBUFFER_H

#include <string>
#include <vector>

using namespace std;

class InputBuffer {
private:
    vector<string> buffer;
    int nextIndex = 0;
public:
    InputBuffer(vector<string> input);
    bool hasNextToken();
    string getNextToken();
};


#endif //COMPILERS_INPUTBUFFER_H
