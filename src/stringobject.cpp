#include "stringobject.h"
#include <cstdlib>

StringObject::StringObject(string s) : _internalString(s) {
    
}

StringObject::~StringObject() {
    
}

ObjectType StringObject::objectType() {
    return ObjectType::STRING_INSTANCE;
}

string StringObject::getString() {
    return _internalString;
}

void StringObject::setString(string s) {
    _internalString = s;
}
