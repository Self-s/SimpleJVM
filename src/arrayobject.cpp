#include "arrayobject.h"

#include <cassert>
#include <iostream>
#include <cstdlib>

ArrayObject::ArrayObject(ValueType type) : _arrayType(type) {
    
}

ArrayObject::~ArrayObject() {
    
}

ObjectType ArrayObject::objectType() {
    return ObjectType::ARRAY;
}

ValueType ArrayObject::arrayContentType() {
    return _arrayType;
}

void ArrayObject::pushValue(Value value) {
    assert(value.type == _arrayType);
    
    _elements.push_back(value);
}

Value ArrayObject::removeAt(uint32_t index) {
    assert(_elements.size() > 0);
    assert(index < _elements.size());
    
    Value value = _elements[index];
    _elements.erase(_elements.begin() + index);
    return value;
}

Value ArrayObject::removeLast() {
    assert(_elements.size() > 0);
    
    Value value = _elements.back();
    _elements.pop_back();
    return value;
}

Value ArrayObject::removeFirst() {
    assert(_elements.size() > 0);
    
    Value value = _elements.front();
    _elements.erase(_elements.begin());
    return value;
}

uint32_t ArrayObject::getSize() {
    return _elements.size();
}

Value ArrayObject::getValue(uint32_t index) {
    assert(_elements.size() > 0);
//    assert(index < _elements.size());
    
    if (index >= _elements.size()) {
        cerr << "ArrayIndexOutOfBoundsException" << endl;
        exit(1);
    }
    
    return _elements[index];
}

void ArrayObject::changeValueAt(uint32_t index, Value value) {
    _elements[index] = value;
}
