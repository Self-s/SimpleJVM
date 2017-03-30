#include <iostream>
#include <cstdlib>

#include "heap.h"

using namespace std;

Heap::Heap() {
    
}

Heap::~Heap() {
    
}

void Heap::addObject(Object *object) {    
	_objectVector.push_back(object);
}
