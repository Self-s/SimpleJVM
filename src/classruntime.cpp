#include "classruntime.h"
#include "classviewer.h"

#include <iostream>
#include <cstdlib>

ClassRuntime::ClassRuntime(ClassFile *classFile) : _classFile(classFile) {
    field_info *fields = classFile->fields;
    for (int i = 0; i < classFile->fields_count; i++) {
        field_info field = fields[i];
        u2 staticFlag = 0x0008;
        u2 finalFlag = 0x0010;
        
        if ((field.access_flags & staticFlag) != 0 && (field.access_flags & finalFlag) == 0) { // estática e não final
            string fieldName = getFormattedConstant(classFile->constant_pool, field.name_index);
            string fieldDescriptor = getFormattedConstant(classFile->constant_pool, field.descriptor_index);
            
            char fieldType = fieldDescriptor[0];
            Value value;
            
            switch (fieldType) {
                case 'B':
                    value.type = ValueType::BYTE;
                    value.data.byteValue = 0;
                    break;
                case 'C':
                    value.type = ValueType::CHAR;
                    value.data.charValue = 0;
                    break;
                case 'D':
                    value.type = ValueType::DOUBLE;
                    value.data.doubleValue = 0;
                    break;
                case 'F':
                    value.type = ValueType::FLOAT;
                    value.data.floatValue = 0;
                    break;
                case 'I':
                    value.type = ValueType::INT;
                    value.data.intValue = 0;
                    break;
                case 'J':
                    value.type = ValueType::LONG;
                    value.data.longValue = 0;
                    break;
                case 'S':
                    value.type = ValueType::SHORT;
                    value.data.shortValue = 0;
                    break;
                case 'Z':
                    value.type = ValueType::BOOLEAN;
                    value.data.charValue = false;
                    break;
                default:
                    value.type = ValueType::REFERENCE;
                    value.data.object = NULL;
            }
            
            putValueIntoField(value, fieldName);
        }
    }
}

ClassFile* ClassRuntime::getClassFile() {
    return _classFile;
}

void ClassRuntime::putValueIntoField(Value value, string fieldName) {
    _staticFields[fieldName] = value;
}

Value ClassRuntime::getValueFromField(string fieldName) {
    if (_staticFields.count(fieldName) ==  0) {
        cerr << "NoSuchFieldError" << endl;
        exit(1);
    }
    
    return _staticFields[fieldName];
}


bool ClassRuntime::fieldExists(string fieldName) {
    return _staticFields.count(fieldName) > 0;
}