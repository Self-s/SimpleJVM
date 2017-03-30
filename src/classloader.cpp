#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cstdbool>
#include <cstdlib>

#include <iostream>

#include "classloader.h"
#include "utils.h"

using namespace std;

ClassLoader::ClassLoader() {
    isLittleEndian = testEndianess();
};

ClassLoader::~ClassLoader() {
    
}

bool ClassLoader::testEndianess() {
    int n = 1;
    return (*(char*)&n == 1);
}

ClassFile* ClassLoader::readClassFile(FILE *fp) {    
    ClassFile *classFile = (ClassFile*) malloc(sizeof(ClassFile));
    
    // magic
    setMagic(fp, classFile);
    if (isMagicValid(classFile) == false) {
        printf("ClassFormatError\n");
        exit(3);
    }
    
    // version
    setVersion(fp, classFile);
    if (isVersionValid(classFile, 46) == false) {
        double friendlyVersion = Utils::generateFriendlyVersionNumber(classFile);
        if (friendlyVersion == 0) {
            printf("UnsupportedClassVersionError\n");
        } else {
            printf("UnsupportedClassVersionError: %.1f\n", friendlyVersion);
        }
        exit(4);
    }
    
    // pool de constantes
    setConstantPoolSize(fp, classFile);
    setConstantPool(fp, classFile);
    
    // access flags
    setAccessFlags(fp, classFile);
    
    // this class
    setThisClass(fp, classFile);
    
    // superclass
    setSuperClass(fp, classFile);
    
    // interfaces
    setInterfacesCount(fp, classFile);
    setInterfaces(fp, classFile);
    
    // fields
    setFieldsCount(fp, classFile);
    setFields(fp, classFile);
    
    // methods
    setMethodsCount(fp, classFile);
    setMethods(fp, classFile);
    
    // attributes
    setAttributesCount(fp, classFile);
    setAttributes(fp, classFile);
    
    return classFile;
}

u1 ClassLoader::readU1(FILE *fp) {
    u1 result = 0;
    fread(&result, sizeof(u1), 1, fp);
    return result;
}

u2 ClassLoader::readU2(FILE *fp) {
    u2 result = 0;
    
    if (isLittleEndian) {
        for (int i = 0; i < 2; i++) {
            result += readU1(fp) << (8 - 8*i);
        }
    } else {
        fread(&result, sizeof(u2), 1, fp);
    }
    
    return result;
}

u4 ClassLoader::readU4(FILE *fp) {
    u4 result = 0;
    
    if (isLittleEndian) {
        for (int i = 0; i < 4; i++) {
            result += readU1(fp) << (24 - 8*i);
        }
    } else {
        fread(&result, sizeof(u4), 1, fp);
    }
    
    return result;
}

void ClassLoader::setMagic(FILE *fp, ClassFile *classFile) {
    classFile->magic = readU4(fp);
}

bool ClassLoader::isMagicValid(ClassFile *classFile) {
    return classFile->magic == 0xCAFEBABE ? true : false;
}

void ClassLoader::setVersion(FILE *fp, ClassFile *classFile) {
    classFile->minor_version = readU2(fp);
    classFile->major_version = readU2(fp);
}

bool ClassLoader::isVersionValid(ClassFile *classFile, uint16_t major) {
    return classFile->major_version <= major;
}

void ClassLoader::setConstantPoolSize(FILE *fp, ClassFile *classFile) {
    classFile->constant_pool_count = readU2(fp);
}

void ClassLoader::setConstantPool(FILE *fp, ClassFile *classFile) {
    u2 poolSize = classFile->constant_pool_count - 1;
    classFile->constant_pool = (cp_info*) malloc(sizeof(cp_info) * poolSize);
    
    cp_info *constant_pool = classFile->constant_pool;
    for (u2 i = 0; i < poolSize; i++) {
        u1 tag = readU1(fp);
        constant_pool[i].tag = tag;
        
        switch (tag) {
            case CONSTANT_Class:
                constant_pool[i].info.class_info = getConstantClassInfo(fp);
            break;
            case CONSTANT_Fieldref:
                constant_pool[i].info.fieldref_info = getConstantFieldRefInfo(fp);
            break;
            case CONSTANT_Methodref:
                constant_pool[i].info.methodref_info = getConstantMethodRefInfo(fp);
            break;
            case CONSTANT_InterfaceMethodref:
                constant_pool[i].info.interfaceMethodref_info = getConstantInterfaceMethodRefInfo(fp);
            break;
            case CONSTANT_String:
                constant_pool[i].info.string_info = getConstantStringInfo(fp);
            break;
            case CONSTANT_Integer:
                constant_pool[i].info.integer_info = getConstantIntegerInfo(fp);
            break;
            case CONSTANT_Float:
                constant_pool[i].info.float_info = getConstantFloatInfo(fp);
            break;
            case CONSTANT_Long:
                constant_pool[i].info.long_info = getConstantLongInfo(fp);
                constant_pool[++i].tag = CONSTANT_NULL;
            break;
            case CONSTANT_Double:
                constant_pool[i].info.double_info = getConstantDoubleInfo(fp);
                constant_pool[++i].tag = CONSTANT_NULL;
            break;
            case CONSTANT_NameAndType:
                constant_pool[i].info.nameAndType_info = getConstantNameAndTypeInfo(fp);
            break;
            case CONSTANT_Utf8:
                constant_pool[i].info.utf8_info = getConstantUtf8Info(fp);
            break;
            default:
                cerr << "Arquivo .class possui uma tag invalida no pool de constantes";
                exit(5);
        }
    }
}

CONSTANT_Class_info ClassLoader::getConstantClassInfo(FILE *fp) {
    CONSTANT_Class_info result;
    result.name_index = readU2(fp);
    return result;
}

CONSTANT_Fieldref_info ClassLoader::getConstantFieldRefInfo(FILE *fp) {
    CONSTANT_Fieldref_info result;
    result.class_index = readU2(fp);
    result.name_and_type_index = readU2(fp);
    return result;
}

CONSTANT_Methodref_info ClassLoader::getConstantMethodRefInfo(FILE *fp) {
    CONSTANT_Methodref_info result;
    result.class_index = readU2(fp);
    result.name_and_type_index = readU2(fp);
    return result;
}

CONSTANT_InterfaceMethodref_info ClassLoader::getConstantInterfaceMethodRefInfo(FILE *fp) {
    CONSTANT_InterfaceMethodref_info result;
    result.class_index = readU2(fp);
    result.name_and_type_index = readU2(fp);
    return result;
}

CONSTANT_String_info ClassLoader::getConstantStringInfo(FILE *fp) {
    CONSTANT_String_info result;
    result.string_index = readU2(fp);
    return result;
}

CONSTANT_Integer_info ClassLoader::getConstantIntegerInfo(FILE *fp) {
    CONSTANT_Integer_info result;
    result.bytes = readU4(fp);
    return result;
}

CONSTANT_Float_info ClassLoader::getConstantFloatInfo(FILE *fp) {
    CONSTANT_Float_info result;
    result.bytes = readU4(fp);
    return result;
}

CONSTANT_Long_info ClassLoader::getConstantLongInfo(FILE *fp) {
    CONSTANT_Long_info result;
    result.high_bytes = readU4(fp);
    result.low_bytes = readU4(fp);
    return result;
}

CONSTANT_Double_info ClassLoader::getConstantDoubleInfo(FILE *fp) {
    CONSTANT_Double_info result;
    result.high_bytes = readU4(fp);
    result.low_bytes = readU4(fp);
    return result;
}

CONSTANT_NameAndType_info ClassLoader::getConstantNameAndTypeInfo(FILE *fp) {
    CONSTANT_NameAndType_info result;
    result.name_index = readU2(fp);
    result.descriptor_index = readU2(fp);
    
    return result;
}

CONSTANT_Utf8_info ClassLoader::getConstantUtf8Info(FILE *fp) {
    CONSTANT_Utf8_info result;
    result.length = readU2(fp);
    result.bytes = (u1*) malloc(sizeof(u1) * result.length);
    
    for (u2 i = 0; i < result.length; i++) {
        result.bytes[i] = readU1(fp);
    }
    
    return result;
}

void ClassLoader::setAccessFlags(FILE *fp, ClassFile *classFile) {
    classFile->access_flags = readU2(fp);
}

void ClassLoader::setThisClass(FILE *fp, ClassFile *classFile) {
    classFile->this_class = readU2(fp);
}

void ClassLoader::setSuperClass(FILE *fp, ClassFile *classFile) {
    classFile->super_class = readU2(fp);
}

void ClassLoader::setInterfacesCount(FILE *fp, ClassFile *classFile) {
    classFile->interfaces_count = readU2(fp);
}

void ClassLoader::setInterfaces(FILE *fp, ClassFile *classFile) {
    classFile->interfaces = (u2*) malloc(sizeof(u2) * classFile->interfaces_count);
    for (u2 i = 0; i < classFile->interfaces_count; i++) {
        classFile->interfaces[i] = readU2(fp);
    }
}

void ClassLoader::setFieldsCount(FILE *fp, ClassFile *classFile) {
    classFile->fields_count = readU2(fp);
}

void ClassLoader::setFields(FILE *fp, ClassFile *classFile) {
    classFile->fields = (field_info*) malloc(sizeof(field_info) * classFile->fields_count);
    for (u2 i = 0; i < classFile->fields_count; i++) {
        field_info field;
        
        field.access_flags = readU2(fp);
        field.name_index = readU2(fp);
        field.descriptor_index = readU2(fp);
        field.attributes_count = readU2(fp);
        
        field.attributes = (attribute_info*) malloc(sizeof(attribute_info) * field.attributes_count);
        
        for (u2 j = 0; j < field.attributes_count; j++) {
            field.attributes[j] = getAttributeInfo(fp, classFile);
        }
        
        classFile->fields[i] = field;
    }
}

CONSTANT_Utf8_info ClassLoader::getUtf8FromConstantPool(u2 index, ClassFile *classFile) {
    cp_info constant = classFile->constant_pool[index-1];
    assert(constant.tag == CONSTANT_Utf8);
    return constant.info.utf8_info;
}

ConstantValue_attribute ClassLoader::getAttributeConstantValue(FILE *fp) {
    ConstantValue_attribute result;
    result.constantvalue_index = readU2(fp);
    return result;
}

ExceptionTable ClassLoader::getExceptionTable(FILE *fp) {
    ExceptionTable result;
    result.start_pc = readU2(fp);
    result.end_pc = readU2(fp);
    result.handler_pc = readU2(fp);
    result.catch_type = readU2(fp);
    return result;
}

Code_attribute ClassLoader::getAttributeCode(FILE *fp, ClassFile *classFile) {
    Code_attribute result;
    result.max_stack = readU2(fp);
    result.max_locals = readU2(fp);
    
    result.code_length = readU4(fp);
    
    result.code = (u1*) malloc(sizeof(u1) * result.code_length);
    for (u4 i = 0; i < result.code_length; i++) {
        result.code[i] = readU1(fp);
    }
    
    result.exception_table_length = readU2(fp);
    result.exception_table = (ExceptionTable*) malloc(sizeof(ExceptionTable) * result.exception_table_length);
    for (u2 i = 0; i < result.exception_table_length; i++) {
        result.exception_table[i] = getExceptionTable(fp);
    }
    
    result.attributes_count = readU2(fp);
    result.attributes = (attribute_info*) malloc(sizeof(attribute_info) * result.attributes_count);
    for (u2 i = 0; i < result.attributes_count; i++) {
        result.attributes[i] = getAttributeInfo(fp, classFile);
    }
    
    return result;
}

Exceptions_attribute ClassLoader::getAttributeExceptions(FILE *fp) {
    Exceptions_attribute result;
    result.number_of_exceptions = readU2(fp);
    result.exception_index_table = (u2*) malloc(sizeof(u2) * result.number_of_exceptions);
    for (u2 i = 0; i < result.number_of_exceptions; i++) {
        result.exception_index_table[i] = readU2(fp);
    }
    return result;
}

Class ClassLoader::getClass(FILE *fp) {
    Class result;
    result.inner_class_info_index = readU2(fp);
    result.outer_class_info_index = readU2(fp);
    result.inner_name_index = readU2(fp);
    result.inner_class_access_flags = readU2(fp);
    return result;
}

InnerClasses_attribute ClassLoader::getAttributeInnerClasses(FILE *fp) {
    InnerClasses_attribute result;
    result.number_of_classes = readU2(fp);
    result.classes = (Class*) malloc(sizeof(Class) * result.number_of_classes);
    for (u2 i = 0; i < result.number_of_classes; i++) {
        result.classes[i] = getClass(fp);
    }
    return result;
}

Synthetic_attribute ClassLoader::getAttributeSynthetic(FILE *fp) {
    Synthetic_attribute result;
    return result;
}

SourceFile_attribute ClassLoader::getAttributeSourceFile(FILE *fp) {
    SourceFile_attribute result;
    result.sourcefile_index = readU2(fp);
    return result;
}

LineNumberTable ClassLoader::getLineNumberTable(FILE *fp) {
    LineNumberTable result;
    result.start_pc = readU2(fp);
    result.line_number = readU2(fp);
    return result;
}

LineNumberTable_attribute ClassLoader::getAttributeLineNumberTable(FILE *fp) {
    LineNumberTable_attribute result;
    result.line_number_table_length = readU2(fp);
    result.line_number_table = (LineNumberTable*) malloc(sizeof(LineNumberTable) * result.line_number_table_length);
    for (u2 i = 0; i < result.line_number_table_length; i++) {
        result.line_number_table[i] = getLineNumberTable(fp);
    }
    return result;
}

LocalVariableTable ClassLoader::getLocalVariableTable(FILE *fp) {
    LocalVariableTable result;
    result.start_pc = readU2(fp);
    result.length = readU2(fp);
    result.name_index = readU2(fp);
    result.descriptor_index = readU2(fp);
    result.index = readU2(fp);
    return result;
}

LocalVariableTable_attribute ClassLoader::getAttributeLocalVariable(FILE *fp) {
    LocalVariableTable_attribute result;
    result.local_variable_table_length = readU2(fp);
    result.localVariableTable = (LocalVariableTable*) malloc(sizeof(LocalVariableTable) * result.local_variable_table_length);
    for (u2 i = 0; i < result.local_variable_table_length; i++) {
        result.localVariableTable[i] = getLocalVariableTable(fp);
    }
    return result;
}

Deprecated_attribute ClassLoader::getAttributeDeprecated(FILE *fp) {
    Deprecated_attribute result;
    return result;
}

attribute_info ClassLoader::getAttributeInfo(FILE *fp, ClassFile *classFile) {
    attribute_info result;
    result.attribute_name_index = readU2(fp);
    result.attribute_length = readU4(fp);
    
    CONSTANT_Utf8_info name = getUtf8FromConstantPool(result.attribute_name_index, classFile);
    if (Utils::compareUtf8WithString(name, "ConstantValue")) {
        result.info.constantValue_info = getAttributeConstantValue(fp);
    } else if (Utils::compareUtf8WithString(name, "Code")) {
        result.info.code_info = getAttributeCode(fp, classFile);
    } else if (Utils::compareUtf8WithString(name, "Exceptions")) {
        result.info.exceptions_info = getAttributeExceptions(fp);
    } else if (Utils::compareUtf8WithString(name, "InnerClasses")) {
        result.info.innerClasses_info = getAttributeInnerClasses(fp);
    } else if(Utils::compareUtf8WithString(name, "Synthetic")) {
        result.info.synthetic_info = getAttributeSynthetic(fp);
    } else if (Utils::compareUtf8WithString(name, "SourceFile")) {
        result.info.sourceFile_info = getAttributeSourceFile(fp);
    } else if (Utils::compareUtf8WithString(name, "LineNumberTable")) {
        result.info.lineNumberTable_info = getAttributeLineNumberTable(fp);
    } else if (Utils::compareUtf8WithString(name, "LocalVariableTable")) {
        result.info.localVariableTable_info = getAttributeLocalVariable(fp);
    } else if(Utils::compareUtf8WithString(name, "Deprecated")) {
        result.info.deprecated_info = getAttributeDeprecated(fp);
    } else {
        cerr << "Arquivo .class possui uma um atributo invalido." << endl;
        exit(6);
    }
    
    return result;
}

void ClassLoader::setMethodsCount(FILE *fp, ClassFile *classFile) {
    classFile->methods_count = readU2(fp);
}

void ClassLoader::setMethods(FILE *fp, ClassFile *classFile) {
    classFile->methods = (method_info*) malloc(sizeof(method_info) * classFile->methods_count);
    for (u2 i = 0; i < classFile->methods_count; i++) {
        classFile->methods[i].access_flags = readU2(fp);
        classFile->methods[i].name_index = readU2(fp);
        classFile->methods[i].descriptor_index = readU2(fp);
        classFile->methods[i].attributes_count = readU2(fp);
        
        classFile->methods[i].attributes = (attribute_info*) malloc(sizeof(attribute_info) * classFile->methods[i].attributes_count);
        for (u2 j = 0; j < classFile->methods[i].attributes_count; j++) {
            classFile->methods[i].attributes[j] = getAttributeInfo(fp, classFile);
        }
    }
}

void ClassLoader::setAttributesCount(FILE *fp, ClassFile *classFile) {
    classFile->attributes_count = readU2(fp);
}

void ClassLoader::setAttributes(FILE *fp, ClassFile *classFile) {
    classFile->attributes = (attribute_info*) malloc(sizeof(attribute_info) * classFile->attributes_count);
    for (u2 i = 0; i < classFile->attributes_count; i++) {
        classFile->attributes[i] = getAttributeInfo(fp, classFile);
    }
}
