#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <cmath>

#include <iostream>
#include <sstream>
#include <cstdlib>

#include "classviewer.h"
#include "utils.h"

using namespace std;

FILE *out; // variável global para armazenar o local de saída.

void printClassFile (ClassFile *classFile, FILE *output) {
	
	out = output;
	
    fprintf(out,"General Information\n{\n");
    print_GeneralInformation (classFile);
    fprintf(out, "}\n\n");
    fprintf(out,"Constant Pool (Member count: %d)\n{\n", classFile->constant_pool_count);
    print_ConstantPool (classFile);
    fprintf(out, "}\n\n");
    fprintf(out,"Interfaces (Member count: %d) \n{\n", classFile->interfaces_count);
    print_Interfaces (classFile);
    fprintf(out, "}\n\n");
    fprintf(out,"Fields (Member count: %d)\n{\n", classFile->fields_count);
    print_Fields (classFile);
    fprintf(out, "}\n\n");
    fprintf(out,"Methods (Member count: %d)\n{\n", classFile->methods_count);
    print_Methods (classFile);
    fprintf(out, "}\n\n");
    fprintf(out,"Attributes (Member count: %d)\n{\n", classFile->attributes_count);
    print_Attributes (classFile);
    fprintf(out,"}\n\n");
}


void print_GeneralInformation (ClassFile *classFile) {
    
    fprintf(out,"\t Minor Version: \t\t %hu\n", classFile->minor_version);
    fprintf(out,"\t Major Version: \t\t %hu [%.1f]\n", classFile->major_version, Utils::generateFriendlyVersionNumber(classFile));
    fprintf(out,"\t Constant pool count: \t\t %hu\n", classFile->constant_pool_count);
    fprintf(out,"\t Access Flags: \t\t\t 0x%.4X [%s]\n", classFile->access_flags, getAccessFlags(classFile->access_flags));
    fprintf(out,"\t This class: \t\t\t cp_info #%hu <%s>\n", classFile->this_class, getFormattedConstant(classFile->constant_pool, classFile->this_class));
    
    if (classFile->super_class == 0) {
        fprintf(out,"\t Super class: \t\t\t none\n");
    } else {
        fprintf(out,"\t Super class: \t\t\t cp_info #%hu <%s>\n", classFile->super_class, getFormattedConstant(classFile->constant_pool, classFile->super_class));
    }
    
    fprintf(out,"\t Interfaces count: \t\t %hu\n", classFile->interfaces_count);
    fprintf(out,"\t Fields count: \t\t\t %hu\n", classFile->fields_count);
    fprintf(out,"\t Methods pool count: \t\t %hu\n", classFile->methods_count);
    fprintf(out,"\t Attributes pool count: \t %hu\n", classFile->attributes_count);
}


void print_ConstantPool(ClassFile *classFile) {
    cp_info *constantPool = classFile->constant_pool;
    
    for (int i = 0; i < classFile->constant_pool_count-1; i++) {
        cp_info element = constantPool[i];
        
        if (element.tag == CONSTANT_Class) {
            CONSTANT_Class_info classInfo = element.info.class_info;
            fprintf(out,"\t [%d] CONSTANT_Class_info\n", i+1);
            fprintf(out,"\t\t Class name: \t\t\t cp_info #%hu <%s>\n", classInfo.name_index, getFormattedConstant(constantPool, classInfo.name_index));
        } else if (element.tag == CONSTANT_Fieldref) {
            CONSTANT_Fieldref_info fieldRefInfo = element.info.fieldref_info;
            fprintf(out,"\t [%d] CONSTANT_Fieldref_info\n", i+1);
            fprintf(out,"\t\t Class name: \t\t\t cp_info #%hu <%s>\n ", fieldRefInfo.class_index, getFormattedConstant(constantPool, fieldRefInfo.class_index));
            fprintf(out,"\t\t Name and type: \t\t cp_info #%hu <%s>\n", fieldRefInfo.name_and_type_index, getFormattedConstant(constantPool, fieldRefInfo.name_and_type_index));
        } else if (element.tag == CONSTANT_Methodref) {
            CONSTANT_Methodref_info methodInfo = element.info.methodref_info;
            fprintf(out,"\t [%d] CONSTANT_Methodref_info\n", i+1);
            fprintf(out,"\t\t Class name: \t\t\t cp_info #%hu <%s>\n ", methodInfo.class_index, getFormattedConstant(constantPool, methodInfo.class_index));
            fprintf(out,"\t\t Name and type: \t\t cp_info #%hu <%s>\n", methodInfo.name_and_type_index, getFormattedConstant(constantPool, methodInfo.name_and_type_index));
        } else if (element.tag == CONSTANT_InterfaceMethodref) {
            CONSTANT_InterfaceMethodref_info interfaceMethodInfo = element.info.interfaceMethodref_info;
            fprintf(out,"\t [%d] CONSTANT_InterfaceMethodref_info\n", i+1);
            fprintf(out,"\t\t Class name: \t\t\t cp_info #%hu <%s>\n ", interfaceMethodInfo.class_index, getFormattedConstant(constantPool, interfaceMethodInfo.class_index));
            fprintf(out,"\t\t Name and type: \t\t cp_info #%hu <%s>\n", interfaceMethodInfo.name_and_type_index, getFormattedConstant(constantPool, interfaceMethodInfo.name_and_type_index));
        } else if (element.tag == CONSTANT_String) {
            CONSTANT_String_info stringInfo = element.info.string_info;
            fprintf(out,"\t [%d] CONSTANT_String_info\n", i+1);
            fprintf(out,"\t String: \t\t\t\t cp_info #%hu <%s>\n", stringInfo.string_index, getFormattedConstant(constantPool, stringInfo.string_index));
        } else if (element.tag == CONSTANT_Integer) {
            CONSTANT_Integer_info intInfo = element.info.integer_info;
            fprintf(out,"\t [%d] CONSTANT_Integer_info\n", i+1);
            fprintf(out,"\t Bytes: \t\t\t\t 0x%.8X\n", intInfo.bytes);
            fprintf(out,"\t Integer: \t\t\t\t %s\n", getFormattedConstant(constantPool, i+1));
        } else if (element.tag == CONSTANT_Float) {
            CONSTANT_Float_info floatInfo = element.info.float_info;
            fprintf(out,"\t [%d] CONSTANT_Float_info\n", i+1);
            fprintf(out,"\t\t Bytes: \t\t\t 0x%.8X\n", floatInfo.bytes);
            fprintf(out,"\t\t Float: \t\t\t 0x%s\n", getFormattedConstant(constantPool, i+1));
        } else if (element.tag == CONSTANT_Long) {
            CONSTANT_Long_info longInfo = element.info.long_info;
            fprintf(out,"\t [%d] CONSTANT_Long_info\n", i+1);
            fprintf(out,"\t\t High Bytes: \t\t\t 0x%.8X\n", longInfo.high_bytes);
            fprintf(out,"\t\t Low Bytes: \t\t\t 0x%.8X\n", longInfo.low_bytes);
            fprintf(out,"\t\t Long: \t\t\t\t %s\n", getFormattedConstant(constantPool, i+1));
        } else if (element.tag == CONSTANT_Double) {
            CONSTANT_Double_info doubleInfo = element.info.double_info;
            fprintf(out,"\t [%d] CONSTANT_Double_info\n", i+1);
            fprintf(out,"\t\t High Bytes: \t\t\t 0x%.8X\n", doubleInfo.high_bytes);
            fprintf(out,"\t\t Low Bytes: \t\t\t 0x%.8X\n", doubleInfo.low_bytes);
            fprintf(out,"\t\t Double: \t\t\t %s\n", getFormattedConstant(constantPool, i+1));
        } else if (element.tag == CONSTANT_NameAndType) {
            CONSTANT_NameAndType_info nameAndTypeInfo = element.info.nameAndType_info;
            fprintf(out,"\t [%d] CONSTANT_NameAndType_info\n", i+1);
            fprintf(out,"\t\t Name: \t\t\t\t cp_info #%hu <%s>\n", nameAndTypeInfo.name_index, getFormattedConstant(constantPool, nameAndTypeInfo.name_index));
            fprintf(out,"\t\t Descriptor: \t\t\t cp_info #%hu <%s>\n", nameAndTypeInfo.descriptor_index, getFormattedConstant(constantPool, nameAndTypeInfo.descriptor_index));
        } else if (element.tag == CONSTANT_Utf8) {
            CONSTANT_Utf8_info utf8Info = element.info.utf8_info;
            const char *str = getFormattedConstant(constantPool, i+1);
            
            fprintf(out,"\t [%d] CONSTANT_Utf8_info\n", i+1);
            fprintf(out,"\t\t Length of byte array: \t\t %hu\n", utf8Info.length);
            fprintf(out,"\t\t Length of string: \t\t %lu\n", strlen(str)); // MUDAR ISSO
            fprintf(out,"\t\t String: \t\t\t %s\n", str);
        } else if (element.tag == CONSTANT_NULL) {
            fprintf(out,"\t [%d] (large numeric continued)\n", i+1);
        } else {
            cerr << "Arquivo .class possui uma tag invalida no pool de constantes.." << endl;
            exit(5);
        }
        fprintf(out, "\n");
    }
}


void print_Interfaces (ClassFile *classFile) {	
	for (int i = 0; i < classFile->interfaces_count; i++) {
		const char *className = getFormattedConstant(classFile->constant_pool, classFile->interfaces[i]);
		
		fprintf(out,"\t Interface %d \n", i);
		fprintf(out,"\t\t Interface: \t\t cp_info #%hu <%s>\n ", classFile->interfaces[i], className);
	}
}


void print_Fields(ClassFile *classFile) {
	for (u2 i = 0; i < classFile->fields_count; i++) {
        field_info field = classFile->fields[i];
        
		fprintf(out,"\t[%hu] %s\n", i, getFormattedConstant(classFile->constant_pool, field.name_index));
		fprintf(out, "\t{\n");
		
		fprintf(out,"\t\tName: \t\t\t cp_info #%hu <%s>\n ", field.name_index, getFormattedConstant(classFile->constant_pool, field.name_index));
		fprintf(out,"\t\tDescriptor: \t cp_info #%hu <%s>\n ", field.descriptor_index, getFormattedConstant(classFile->constant_pool, field.descriptor_index));
		fprintf(out,"\t\tAccess flags: \t %x [%s]\n", field.access_flags, getAccessFlags(field.access_flags));
        
        fprintf(out,"\t\tAttributes:\n");
        
		for (u2 j = 0; j < field.attributes_count; j++) {
            print_AttributeInfo(field.attributes[j], j, classFile->constant_pool, 3);
		}
        
		fprintf(out, "\t}\n");
	}
}


void print_Methods(ClassFile *classFile) {
    
    for (int i = 0; i < classFile->methods_count; i++) {
        method_info method = classFile->methods[i];
        const char *methodName = getFormattedConstant(classFile->constant_pool, method.name_index);
        const char *descriptor = getFormattedConstant(classFile->constant_pool, method.descriptor_index);
        const char *accessFlags = getAccessFlags(method.access_flags);
        
        fprintf(out,"\t[%d] %s\n", i, methodName);
        
        fprintf(out, "\t{\n");
        
        fprintf(out,"\t\tName: \t\t cp_info #%d <%s>\n", method.name_index, methodName);
        fprintf(out,"\t\tDescriptor: \t cp_info #%d <%s>\n", method.descriptor_index, descriptor);
        fprintf(out,"\t\tAccess flags: \t 0x%.4X [%s]\n", method.access_flags, accessFlags);
        
        fprintf(out,"\t\tAttributes:\n");
        
        for (int j = 0; j < method.attributes_count; j++) {
            print_AttributeInfo(method.attributes[j], j, classFile->constant_pool, 3);
        }
        
        fprintf(out, "\t}\n");
    }
}


void print_Attributes (ClassFile *classFile) {    
    for (uint16_t i = 0; i < classFile->attributes_count; i++) {
        print_AttributeInfo(classFile->attributes[i], i, classFile->constant_pool, 1);
    }
}


const char* getAccessFlags(u2 accessFlags) {
    const char* flags[] = {"public ", "final ", "super ", "interface ", "abstract ", "private ", "protected ", "static ", "volatile ", "transient "};
    uint16_t masks[] = {0x0001, 0x0010, 0x0020, 0x0200, 0x0400, 0x0002, 0x0004, 0x0008, 0x0040, 0x0080};
    
    stringstream ss;
    for (uint8_t i = 0; i < 10; i++) {
        if ((accessFlags & masks[i]) != 0) {
            ss << flags[i];
        }
    }
    
    return Utils::streamToCString(ss);
}

const char* getFormattedConstant(cp_info* constantPool, u2 index) {
    cp_info constant = constantPool[index-1];
    
    if (constant.tag == CONSTANT_Class) {
        CONSTANT_Class_info classInfo = constant.info.class_info;
        return getFormattedConstant(constantPool, classInfo.name_index);
    } else if (constant.tag == CONSTANT_Fieldref) {
        CONSTANT_Fieldref_info fieldRefInfo = constant.info.fieldref_info;
        CONSTANT_NameAndType_info nameAndTypeInfo = constantPool[fieldRefInfo.name_and_type_index-1].info.nameAndType_info;
        
        const char *className = getFormattedConstant(constantPool, fieldRefInfo.class_index);
        const char *name = getFormattedConstant(constantPool, nameAndTypeInfo.name_index);
        
        stringstream ss;
        ss << className << "." << name;
        return Utils::streamToCString(ss);
    } else if (constant.tag == CONSTANT_Methodref) {
        CONSTANT_Methodref_info methodRefInfo = constant.info.methodref_info;
        CONSTANT_NameAndType_info nameAndTypeInfo = constantPool[methodRefInfo.name_and_type_index-1].info.nameAndType_info;
        
        const char *className = getFormattedConstant(constantPool, methodRefInfo.class_index);
        const char *name = getFormattedConstant(constantPool, nameAndTypeInfo.name_index);
        
        stringstream ss;
        ss << className << "." << name;
        return Utils::streamToCString(ss);
    } else if (constant.tag == CONSTANT_InterfaceMethodref) {
        CONSTANT_InterfaceMethodref_info interfaceMethodRefInfo = constant.info.interfaceMethodref_info;
        CONSTANT_NameAndType_info nameAndTypeInfo = constantPool[interfaceMethodRefInfo.name_and_type_index-1].info.nameAndType_info;
        
        const char *className = getFormattedConstant(constantPool, interfaceMethodRefInfo.class_index);
        const char *name = getFormattedConstant(constantPool, nameAndTypeInfo.name_index);
        
        stringstream ss;
        ss << className << "." << name;
        return Utils::streamToCString(ss);
    } else if (constant.tag == CONSTANT_String) {
        CONSTANT_String_info stringInfo = constant.info.string_info;
        return getFormattedConstant(constantPool, stringInfo.string_index);
    } else if (constant.tag == CONSTANT_Integer) {
        CONSTANT_Integer_info intInfo = constant.info.integer_info;
        int32_t number = intInfo.bytes;
        char *s = (char*) malloc(sizeof(char)*100);
        sprintf(s, "%d", number);
        return s;
    } else if (constant.tag == CONSTANT_Float) {
        CONSTANT_Float_info floatInfo = constant.info.float_info;
        
        int32_t s = ((floatInfo.bytes >> 31) == 0) ? 1 : -1;
        int32_t e = ((floatInfo.bytes >> 23) & 0xff);
        int32_t m = (e == 0) ? (floatInfo.bytes & 0x7fffff) << 1 : (floatInfo.bytes & 0x7fffff) | 0x800000;
        float number = s * m * pow(2, e-150);
        
        char *str = (char*) malloc(sizeof(char)*100);
        sprintf(str, "%f", number);
        return str;
    } else if (constant.tag == CONSTANT_Long) {
        CONSTANT_Long_info longInfo = constant.info.long_info;
        int64_t number = ((int64_t) longInfo.high_bytes << 32) + longInfo.low_bytes;
        
        char *str = (char*) malloc(sizeof(char)*100);
        sprintf(str, "%lld", number);
        return str;
    } else if (constant.tag == CONSTANT_Double) {
        CONSTANT_Double_info doubleInfo = constant.info.double_info;
        int64_t bytes = ((int64_t) doubleInfo.high_bytes << 32) + doubleInfo.low_bytes;
        
        int32_t s = ((bytes >> 63) == 0) ? 1 : -1;
        int32_t e = (int32_t)((bytes >> 52) & 0x7ffL);
        int64_t m = (e == 0) ? (bytes & 0xfffffffffffffL) << 1 : (bytes & 0xfffffffffffffL) | 0x10000000000000L;
        double number = s * m * pow(2, e-1075);
        
        char *str = (char*) malloc(sizeof(char)*100);
        sprintf(str, "%f", number);
        return str;
    } else if (constant.tag == CONSTANT_NameAndType) {
        CONSTANT_NameAndType_info nameAndTypeInfo = constant.info.nameAndType_info;
        
        const char *name = getFormattedConstant(constantPool, nameAndTypeInfo.name_index);
        const char *descriptor = getFormattedConstant(constantPool, nameAndTypeInfo.descriptor_index);
        
        char *result = (char*) malloc(sizeof(char)*(strlen(name)+strlen(descriptor)) + 1);
        strcpy(result, name);
        strcat(result, descriptor);
        
        return result;
    } else if (constant.tag == CONSTANT_Utf8) {
        CONSTANT_Utf8_info utf8_info = constant.info.utf8_info;
        char *str = (char*) malloc((utf8_info.length + 1) * sizeof(char));
        
        uint16_t j = 0;
        for (uint16_t i = 0; i < utf8_info.length; i++) {
            if (isprint(utf8_info.bytes[i])) str[j++] = utf8_info.bytes[i];
        }
        str[j] = '\0';
        
        return str;
    } else {
        cerr << "Arquivo .class possui uma tag " << constant.tag << " invalida no pool de constantes." << endl;
        exit(5);
    }
    
    return NULL;
}

void print_AttributeInfo(attribute_info attributeInfo, uint32_t index, cp_info *constantPool, uint8_t indentation) {    
    const char *attributeName = getFormattedConstant(constantPool, attributeInfo.attribute_name_index);
    Utils::printTabs(out, indentation);
    fprintf(out,"[%d] %s\n", index, attributeName);
    Utils::printTabs(out, indentation+1);
    fprintf(out,"Attribute name index:\t cp_info #%d\n", attributeInfo.attribute_name_index);
    Utils::printTabs(out, indentation+1);
    fprintf(out,"Attribute length:\t %d\n", attributeInfo.attribute_length);
    
    CONSTANT_Utf8_info attributeUtf8 = constantPool[attributeInfo.attribute_name_index-1].info.utf8_info;
    if (Utils::compareUtf8WithString(attributeUtf8, "ConstantValue")) {
        ConstantValue_attribute constantValue = attributeInfo.info.constantValue_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Constant value index:\t cp_info #%d <%s>\n", constantValue.constantvalue_index, getFormattedConstant(constantPool, constantValue.constantvalue_index));
    } else if (Utils::compareUtf8WithString(attributeUtf8, "Code")) {
        Code_attribute code = attributeInfo.info.code_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Maximum stack depth:\t %d\n", code.max_stack);
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Maximum local variables: %d\n", code.max_locals);
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Code length:\t\t %u\n", code.code_length);
        
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Exception table:\n");
        Utils::printTabs(out, indentation+2);
        if (code.exception_table_length > 0) {
            fprintf(out,"Nr.\t start_pc\t end_pc\t handler_pc\t catch_type\t verbose\n");
            for (uint16_t i = 0; i < code.exception_table_length; i++) {
                ExceptionTable exceptionTable = code.exception_table[i];
                Utils::printTabs(out, indentation+2);
                fprintf(out,"%d\t ", i);
                fprintf(out,"%d\t ", exceptionTable.start_pc);
                fprintf(out,"%d\t ", exceptionTable.end_pc);
                fprintf(out,"%d\t ", exceptionTable.handler_pc);
                if (exceptionTable.catch_type == 0) {
                    fprintf(out,"0\n");
                } else {
                    fprintf(out,"cp_info #%d\t ", exceptionTable.catch_type);
                    fprintf(out,"%s\n", getFormattedConstant(constantPool, exceptionTable.catch_type));
                }
            }
        } else {
            fprintf(out,"Exception table is empty.\n");
        }
        
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Bytecode:\n");
        printByteCode(code, constantPool, indentation+2);
        
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Attributes:\n");
        for (uint16_t i = 0; i < code.attributes_count; i++) {
            print_AttributeInfo(code.attributes[i], i, constantPool, indentation+2);
        }
    } else if (Utils::compareUtf8WithString(attributeUtf8, "Exceptions")) {
        Exceptions_attribute exceptionsAttr = attributeInfo.info.exceptions_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Nr.\t exception\t verbose\n");
        for (uint16_t i = 0; i < exceptionsAttr.number_of_exceptions; i++) {
            Utils::printTabs(out, indentation+1);
            fprintf(out,"%d\t ", i);
            fprintf(out,"cp_info #%d\t ", exceptionsAttr.exception_index_table[i]);
            fprintf(out,"%s\n", getFormattedConstant(constantPool, exceptionsAttr.exception_index_table[i]));
        }
    } else if (Utils::compareUtf8WithString(attributeUtf8, "InnerClasses")) {
        InnerClasses_attribute innerClassAttr = attributeInfo.info.innerClasses_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Nr.\t inner_class\t outer_class\t inner_name\t access flags\n");
        for (uint16_t i = 0; i < innerClassAttr.number_of_classes; i++) {
            Class innerClass = innerClassAttr.classes[i];
            Utils::printTabs(out, indentation+1);
            fprintf(out,"%d\t ", i);
            fprintf(out,"cp_info #%d <%s>\t ", innerClass.inner_class_info_index, getFormattedConstant(constantPool, innerClass.inner_class_info_index));
            fprintf(out,"cp_info #%d <%s>\t ", innerClass.outer_class_info_index, getFormattedConstant(constantPool, innerClass.outer_class_info_index));
            fprintf(out,"cp_info #%d <%s>\t ", innerClass.inner_name_index, getFormattedConstant(constantPool, innerClass.inner_name_index));
            fprintf(out,"0x%.4X [%s]\n", innerClass.inner_class_access_flags, getAccessFlags(innerClass.inner_class_access_flags));
        }
    } else if (Utils::compareUtf8WithString(attributeUtf8, "Synthetic")) {
        // vazio
    } else if (Utils::compareUtf8WithString(attributeUtf8, "SourceFile")) {
        SourceFile_attribute sourceFile = attributeInfo.info.sourceFile_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Constant value index:\t cp_info #%d <%s>\n", sourceFile.sourcefile_index, getFormattedConstant(constantPool, sourceFile.sourcefile_index));
    } else if (Utils::compareUtf8WithString(attributeUtf8, "LineNumberTable")) {
        LineNumberTable_attribute lineNumberTable = attributeInfo.info.lineNumberTable_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Nr.\t start_pc\t line_number\n");
        for (uint16_t i = 0; i < lineNumberTable.line_number_table_length; i++) {
            LineNumberTable table = lineNumberTable.line_number_table[i];
            Utils::printTabs(out, indentation+1);
            fprintf(out,"%d\t ", i);
            fprintf(out,"%d\t ", table.start_pc);
            fprintf(out,"%d\n", table.line_number);
        }
    } else if (Utils::compareUtf8WithString(attributeUtf8, "LocalVariableTable")) {
        LocalVariableTable_attribute localVariable = attributeInfo.info.localVariableTable_info;
        Utils::printTabs(out, indentation+1);
        fprintf(out,"Nr.\t start_pc\t length\t index\t name\t descriptor\n");
        for (uint16_t i = 0; i < localVariable.local_variable_table_length; i++) {
            LocalVariableTable variable = localVariable.localVariableTable[i];
            Utils::printTabs(out, indentation+1);
            fprintf(out,"%d\t ", i);
            fprintf(out,"%d\t ", variable.start_pc);
            fprintf(out,"%d\t ", variable.length);
            fprintf(out,"%d\t ", variable.index);
            fprintf(out,"cp_info #%d <%s>\t ", variable.name_index, getFormattedConstant(constantPool, variable.name_index));
            fprintf(out,"cp_info #%d <%s>\n", variable.descriptor_index, getFormattedConstant(constantPool, variable.descriptor_index));
        }
    } else if (Utils::compareUtf8WithString(attributeUtf8, "Deprecated")) {
        // vazio
    } else {
        cerr << "Arquivo .class possui uma um atributo invalido." << endl;
        exit(6);
    }
    fprintf(out, "\n");
}

void printByteCode(Code_attribute codeAttribute, cp_info *constantPool, uint8_t indentation) {
    u4 code_length = codeAttribute.code_length;
    u1 *code = codeAttribute.code;
    
    uint32_t lineNumber = 1;
    u4 i = 0;
    while (i < code_length) {
        Utils::printTabs(out, indentation);
        fprintf(out,"%d\t%d\t%s", lineNumber++, i, instructions[code[i]]);
        
        if (code[i] <= 0x0f || (code[i] >= 0x1a && code[i] <= 0x35) || (code[i] >= 0x3b && code[i] <= 0x83) || (code[i] >= 0x85 && code[i] <= 0x98) ||
            (code[i] >= 0xac && code[i] <= 0xb1) || code[i] == 0xbe || code[i] == 0xbf || code[i] == 0xc2 || code[i] == 0xc3) {
            fprintf(out,"\n");
            i += 1;
        } else if (code[i] == 0x12) { // usa CP
            fprintf(out," #%d <%s>\n", code[i+1], getFormattedConstant(constantPool, code[i+1]));
            i += 2;
        } else if (code[i] == 0xbc) { // newarray
            u1 atype = code[i+1];
            const char* types[] = {"boolean", "char", "float", "double", "byte", "short", "int", "long"};
            fprintf(out," %d (%s)\n", atype, types[atype-4]);
            i += 2;
        } else if (code[i] == 0x10 || (code[i] >= 0x15 && code[i] <= 0x19) || (code[i] >= 0x36 && code[i] <= 0x3a) || code[i] == 0xa9) {
            fprintf(out," %d\n", code[i+1]);
            i += 2;
        } else if (code[i] == 0x11) { // sipush
            int16_t number = (code[i+1] << 8) | code[i+2];
            fprintf(out," %d\n", number);
            i += 3;
        } else if (code[i] == 0x84) { // iinc
            fprintf(out," %d by %d\n", code[i+1], code[i+2]);
            i += 3;
        } else if (code[i] == 0x13 || code[i] == 0x14 || (code[i] >= 0xb2 && code[i] <= 0xb8) ||
                   code[i] == 0xbb || code[i] == 0xbd || code[i] == 0xc0 || code[i] == 0xc1) { // usa CP
            u2 number = (code[i+1] << 8) | code[i+2];
            fprintf(out," #%d <%s>\n", number, getFormattedConstant(constantPool, number));
            i += 3;
        } else if ((code[i] >= 0x99 && code[i] <= 0xa8) || code[i] == 0xc6 || code[i] == 0xc7) {
            int16_t number = (code[i+1] << 8) | code[i+2];
            fprintf(out," %d (%+d)\n", i+number, number);
            i += 3;
        } else if (code[i] == 0xc5) { // multianewarray - usa CP
            u2 number = (code[i+1] << 8) | code[i+2];
            fprintf(out," #%d <%s> dim %d\n", number, getFormattedConstant(constantPool, number), code[i+3]);
            i += 4;
        } else if (code[i] == 0xb9) { // invokeinterface - usa CP
            u2 number = (code[i+1] << 8) | code[i+2];
            fprintf(out," #%d <%s> count %d\n", number, getFormattedConstant(constantPool, number), code[i+3]);
            assert(code[i+4] == 0);
            i += 5;
        } else if (code[i] == 0xc8 || code[i] == 0xc9) { // goto_w e jsr_w
            int32_t number = (code[i+1] << 24) | (code[i+2] << 16) | (code[i+3] << 8) | code[i+4];
            fprintf(out," %d (%+d)\n", i+number, number);
            i += 5;
        } else if (code[i] == 0xc4) { // wide
            u2 indexbyte = (code[i+2] << 8) | code[i+3];
            
            fprintf(out,"\n");
            Utils::printTabs(out, indentation);
            fprintf(out,"%d\t%d\t%s %d", lineNumber++, i+1, instructions[code[i+1]], indexbyte);
            
            if (code[i+1] == 0x84) { // format 2 (iinc)
                int16_t constbyte = (code[i+4] << 8) | code[i+5];
                fprintf(out," by %d", constbyte);
                i += 6;
            } else {
                i += 4;
            }
            
            fprintf(out,"\n");
        } else if (code[i] == 0xaa) { // tableswitch
            u1 padding = (i+1) % 4;
            int32_t defaultbytes = (code[padding+i+1] << 24) | (code[padding+i+2] << 16) | (code[padding+i+3] << 8) | code[padding+i+4];
            int32_t lowbytes = (code[padding+i+5] << 24) | (code[padding+i+6] << 16) | (code[padding+i+7] << 8) | code[padding+i+8];
            int32_t highbytes = (code[padding+i+9] << 24) | (code[padding+i+10] << 16) | (code[padding+i+11] << 8) | code[padding+i+12];
            
            fprintf(out," %d to %d\n", lowbytes, highbytes);
            
            u4 howManyBytes = 1 + padding + 12; // 1 (instruction) + padding + 12 (the 12 bytes above)
            int32_t offsets = highbytes - lowbytes + 1;
            
            for (u4 n = 0; n < offsets; n++) {
                int32_t offset = (code[i+howManyBytes] << 24) | (code[i+howManyBytes+1] << 16) | (code[i+howManyBytes+2] << 8) | code[i+howManyBytes+3];
                Utils::printTabs(out, indentation);
                fprintf(out,"%d\t\t\t%d: %d (%+d)\n", lineNumber++, lowbytes, i + offset, offset);
                
                lowbytes++;
                howManyBytes += 4;
            }
            Utils::printTabs(out, indentation);
            fprintf(out,"%d\t\t\tdefault: %d (%+d)\n", lineNumber++, i + defaultbytes, defaultbytes);
            
            i += howManyBytes;
        } else if (code[i] == 0xab) { // lookupswitch
            u1 padding = (i+1) % 4;
            int32_t defaultbytes = (code[padding+i+1] << 24) | (code[padding+i+2] << 16) | (code[padding+i+3] << 8) | code[padding+i+4];
            int32_t npairs = (code[padding+i+5] << 24) | (code[padding+i+6] << 16) | (code[padding+i+7] << 8) | code[padding+i+8];
            
            u4 howManyBytes = 1 + padding + 8; // 1 (instruction) + padding + 8 (the 8 bytes above)
            
            fprintf(out," %d\n", npairs);
            
            for (u4 n = 0; n < npairs; n++) {
                int32_t match = (code[i+howManyBytes] << 24) | (code[i+howManyBytes+1] << 16) | (code[i+howManyBytes+2] << 8) | code[i+howManyBytes+3];
                int32_t offset = (code[i+howManyBytes+4] << 24) | (code[i+howManyBytes+5] << 16) | (code[i+howManyBytes+6] << 8) | code[i+howManyBytes+7];
                Utils::printTabs(out, indentation);
                fprintf(out,"%d\t\t\t%d: %d (%+d)\n", lineNumber++, match, i + offset, offset);
                howManyBytes += 8;
            }
            Utils::printTabs(out, indentation);
            fprintf(out,"%d\t\t\tdefault: %d (%+d)\n", lineNumber++, i + defaultbytes, defaultbytes);
            
            i += howManyBytes;
        } else {
            fprintf(out,"Invalid instruction opcode.\n");
            exit(7);
        }
    }
}
