#ifndef TIPOS_H
#define TIPOS_H

#include <stdint.h>

// Tipos de representação de dados da classe
typedef uint8_t u1;
typedef uint16_t u2;
typedef uint32_t u4;

enum ObjectType {
    CLASS_INSTANCE,
    STRING_INSTANCE,
    ARRAY
};
typedef enum ObjectType ObjectType;

enum ValueType {
    BOOLEAN,
    BYTE,
    CHAR,
    SHORT,
    INT,
    FLOAT,
    LONG,
    DOUBLE,
    RETURN_ADDR,
    REFERENCE,
    PADDING // usado quando o Value anterior (em uma lista) ou o Value abaixo (em uma pilha) é um long/double
};
typedef enum ValueType ValueType;

class Object;

struct Value {
    ValueType printType; // usado para printar o valor de maneira correta (somente para int, short, byte, boolean)
    ValueType type;
    union {
        bool booleanValue;
        int8_t byteValue;
        uint8_t charValue;
        int16_t shortValue;
        int32_t intValue;
        float floatValue;
        int64_t longValue;
        double doubleValue;
        u4 returnAddress;
        Object *object;
    } data;
};
typedef struct Value Value;

// Typedefs das estruturas de classe

// ClassFile
typedef struct ClassFile ClassFile;

// Pool de Constantes
typedef struct cp_info cp_info;
typedef struct CONSTANT_Class_info CONSTANT_Class_info;
typedef struct CONSTANT_Fieldref_info CONSTANT_Fieldref_info;
typedef struct CONSTANT_Methodref_info CONSTANT_Methodref_info;
typedef struct CONSTANT_InterfaceMethodref_info CONSTANT_InterfaceMethodref_info;
typedef struct CONSTANT_String_info CONSTANT_String_info;
typedef struct CONSTANT_Integer_info CONSTANT_Integer_info;
typedef struct CONSTANT_Float_info CONSTANT_Float_info;
typedef struct CONSTANT_Long_info CONSTANT_Long_info;
typedef struct CONSTANT_Double_info CONSTANT_Double_info;
typedef struct CONSTANT_NameAndType_info CONSTANT_NameAndType_info;
typedef struct CONSTANT_Utf8_info CONSTANT_Utf8_info;

// field_info
typedef struct field_info field_info;

// attribute_info
typedef struct attribute_info attribute_info;
typedef struct ConstantValue_attribute ConstantValue_attribute;
typedef struct ExceptionTable ExceptionTable;
typedef struct Code_attribute Code_attribute;
typedef struct Exceptions_attribute Exceptions_attribute;
typedef struct Class Class;
typedef struct InnerClasses_attribute InnerClasses_attribute;
typedef struct Synthetic_attribute Synthetic_attribute;
typedef struct SourceFile_attribute SourceFile_attribute;
typedef struct LineNumberTable LineNumberTable;
typedef struct LineNumberTable_attribute LineNumberTable_attribute;
typedef struct LocalVariableTable LocalVariableTable;
typedef struct LocalVariableTable_attribute LocalVariableTable_attribute;
typedef struct Deprecated_attribute Deprecated_attribute;

// method_info
typedef struct method_info method_info;

// Definição das estruturas de classe

struct ClassFile {
    u4 magic;
    u2 minor_version;
    u2 major_version;
    u2 constant_pool_count;
    cp_info *constant_pool;
    u2 access_flags;
    u2 this_class;
    u2 super_class;
    u2 interfaces_count;
    u2 *interfaces;
    u2 fields_count;
    field_info *fields;
    u2 methods_count;
    method_info *methods;
    u2 attributes_count; 
    attribute_info *attributes;
};

struct field_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
};

struct method_info {
    u2 access_flags;
    u2 name_index;
    u2 descriptor_index;
    u2 attributes_count;
    attribute_info *attributes;
};

typedef enum CONSTANT_Type {
    CONSTANT_Class = 7,
    CONSTANT_Fieldref = 9,
    CONSTANT_Methodref = 10,
    CONSTANT_InterfaceMethodref = 11,
    CONSTANT_String = 8,
    CONSTANT_Integer = 3,
    CONSTANT_Float = 4,
    CONSTANT_Long = 5,
    CONSTANT_Double = 6,
    CONSTANT_NameAndType = 12,
    CONSTANT_Utf8 = 1,
    CONSTANT_NULL = 0
} CONSTANT_Type;

struct CONSTANT_Class_info {
	u2 name_index;
};

struct CONSTANT_Fieldref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_Methodref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_InterfaceMethodref_info {
    u2 class_index;
    u2 name_and_type_index;
};

struct CONSTANT_String_info {
    u2 string_index;
};

struct CONSTANT_Integer_info {
    u4 bytes;
};

struct CONSTANT_Float_info {
    u4 bytes;
};

struct CONSTANT_Long_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_Double_info {
    u4 high_bytes;
    u4 low_bytes;
};

struct CONSTANT_NameAndType_info {
	u2 name_index;
	u2 descriptor_index;
};

struct CONSTANT_Utf8_info {
    u2 length;
    u1 *bytes;
};

struct cp_info {
    u1 tag;
    union {
        CONSTANT_Class_info class_info;
        CONSTANT_Fieldref_info fieldref_info;
        CONSTANT_Methodref_info methodref_info;
        CONSTANT_InterfaceMethodref_info interfaceMethodref_info;
        CONSTANT_String_info string_info;
        CONSTANT_Integer_info integer_info;
        CONSTANT_Float_info float_info;
        CONSTANT_Long_info long_info;
        CONSTANT_Double_info double_info;
        CONSTANT_NameAndType_info nameAndType_info;
        CONSTANT_Utf8_info utf8_info;
    } info;
};

struct ConstantValue_attribute {
    u2 constantvalue_index;
};

struct ExceptionTable {
    u2 start_pc;
    u2 end_pc;
    u2 handler_pc;
    u2 catch_type;
};

struct Code_attribute {
	u2 max_stack;
	u2 max_locals;
	u4 code_length;
	u1 *code;
	u2 exception_table_length;
    ExceptionTable *exception_table;
	u2 attributes_count;
	attribute_info *attributes;
};

struct Exceptions_attribute {
	u2 number_of_exceptions;
	u2 *exception_index_table;
};

struct Class {
    u2 inner_class_info_index;	     
    u2 outer_class_info_index;	     
    u2 inner_name_index;	     
    u2 inner_class_access_flags;	
};

struct InnerClasses_attribute {
	u2 number_of_classes;
	Class *classes;
};

struct Synthetic_attribute {
	// vazio
};

struct SourceFile_attribute {
  	u2 sourcefile_index;
};

struct LineNumberTable {
    u2 start_pc;	     
    u2 line_number;
};

struct LineNumberTable_attribute {
	u2 line_number_table_length;
	LineNumberTable *line_number_table;
};

struct LocalVariableTable {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
};

struct LocalVariableTable_attribute {
    u2 local_variable_table_length;
    LocalVariableTable *localVariableTable;
};

struct Deprecated_attribute {
    // vazio
};

struct attribute_info {
    u2 attribute_name_index;
    u4 attribute_length;
    union {
        ConstantValue_attribute constantValue_info;
        Code_attribute code_info;
        Exceptions_attribute exceptions_info;
        InnerClasses_attribute innerClasses_info;
        Synthetic_attribute synthetic_info;
        SourceFile_attribute sourceFile_info;
        LineNumberTable_attribute lineNumberTable_info;
        LocalVariableTable_attribute localVariableTable_info;
        Deprecated_attribute deprecated_info;
    } info;
};

#endif