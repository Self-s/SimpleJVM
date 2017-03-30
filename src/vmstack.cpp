#include "vmstack.h"

#include <iostream>
#include <cstdlib>

VMStack::VMStack() {
    
}

VMStack::~VMStack() {
    
}

void VMStack::addFrame(Frame *frame) {
    // Verifica se a stack está cheia
//    if (_frameStack.size() >= FRAME_MAX_SIZE) {
//        cerr << "StackOverflowError" << endl;
//        exit(1);
//    }
    
    _frameStack.push(frame);
}

Frame* VMStack::getTopFrame() {
    if (_frameStack.size() == 0) {
        return NULL;
    }
    
    return _frameStack.top();
}

bool VMStack::destroyTopFrame() {
    if (_frameStack.size() == 0) {
        return false;
    }
    
    Frame *frame = _frameStack.top();
    _frameStack.pop();
    delete frame;
    
    return true;
}

uint32_t VMStack::size() {
    return _frameStack.size();
}