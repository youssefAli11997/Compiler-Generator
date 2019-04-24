//
// Created by hp on 23/04/02019.
//

#include "InputBuffer.h"

InputBuffer::InputBuffer(vector<string> input) {
    this->buffer = input;
}
string InputBuffer::getNextToken() {
    return buffer[nextIndex];
}

void InputBuffer::matchCurrentToken() {
    nextIndex++;
}

bool InputBuffer::hasNextToken() {
    return nextIndex < buffer.size();
}