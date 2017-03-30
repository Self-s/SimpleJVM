#ifndef CLASSVIEWER_H
#define CLASSVIEWER_H

#include "tipos.h"

using namespace std;

/**
 * Imprime os elementos do Leitor/Exibidor de classe
 * em ordem: Informações gerais, pool de constantes,
 * interfaces, campos, métodos e atributos.
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 * @param output é o arquivo exibidor da JVM.
 */
void printClassFile (ClassFile *classFile, FILE *output);

/**
 * Imprime informações gerais do arquivo .class
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 */
void print_GeneralInformation (ClassFile *classFile);

/**
 * Imprime pool de constantes e identidifica referências à elementos
 * da própria pool de contantes (cp_info)
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 */
void print_ConstantPool(ClassFile *classFile);

/**
 * Imprime elementos de interface e suas referẽncias à pool de constantes
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 */
void print_Interfaces(ClassFile *classFile);

/**
 * Imprime elementos de field, suas referências à pool de constantes e
 * decodifica o valor das flags de acesso, utilizando a seguinte tabela de referência:
 *
 *  ACC_PUBLIC: 0x0001
 *
 *  ACC_SUPER: 0x0020
 *
 *  ACC_PRIVATE: 0x0002
 *
 *  ACC_INTERFACE: 0x0200
 *
 *  ACC_ABSTRACT: 0x0400
 *
 * 	ACC_PROTECTED: 0x0004
 *
 * 	ACC_STATIC: 0x0008
 *
 * 	ACC_FINAL: 0x0010
 *
 * 	ACC_VOLATILE: 0x0040
 *
 * 	ACC_TRANSIENT	: 0x0080
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 */
void print_Fields(ClassFile *classFile);

/**
 * Imprime elementos de método, suas referências à pool de constantes e
 * chama função para imprimir os atributos relacionados aos métodos.
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 */
void print_Methods(ClassFile *classFile);

/**
 * Imprime elementos de atributo, chamando função print_AttributeInfo para 
 * cada um deles
 * @param classFile é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 */
void print_Attributes (ClassFile *classFile);

/**
 * Encapsula decriptação das flags de acesso
 * @param accessFlags é o hexadecimal lido referente à flag de acesso
 * @return flags de acesso em forma de string
 */
const char* getAccessFlags(u2 accessFlags);

/**
 * Função recursiva que busca um valor em bytes a partir de um índice que 
 * faz referência à qualquer elemento da pool de constantes. Esse valor
 * pode ser tanto numérico (inteiro, long, float ou double) ou string (Utf-8)
 * @param constantPool é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 * @param index é o índice do elemento
 * @return constante formatada de acordo com o seu tipo
 */
const char* getFormattedConstant(cp_info* constantPool, u2 index);

/**
 * Imprime informações básicas dos atributos e as específicas de um dos 
 * 9 elementos da unios, onde Synthetic e Deprecated são ignorados por
 * não possuirem informações extras.
 * @param attributeInfo sctruct do atributo
 * @param index é o índice do atributo
 * @param constantPool é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 * @param indentation é o número de tabs que deve ser imprimido na linha
 */
void print_AttributeInfo(attribute_info attributeInfo, uint32_t index, cp_info *constantPool, uint8_t indentation);

/**
 * Imprime strings que representam instruções através da variável de código 
 * do atributo. O valor do código em hexa é decriptado na função getFormattedConstant().
 * A lista de instruções está armazenada em "instructions[]" e o que faz acesso
 * à elas é "code[i]", ou seja, o vetor de códigos de cada atributo.
 * @param codeAttribute struct do código de atributos
 * @param constantPool é um ponteiro para uma instância de struct ClassFile, que descreve toda a estrutura de um arquivo .class
 * @param indentation é o número de tabs que deve ser imprimido na linha
 */
void printByteCode(Code_attribute codeAttribute, cp_info *constantPool, uint8_t indentation);

/**
 * Vetor contendo os mnemônicos de todas as instruções do bytecode Java.
 */
static const char* instructions[] = {
    "nop",
    "aconst_null",
    "iconst_m1",
    "iconst_0",
    "iconst_1",
    "iconst_2",
    "iconst_3",
    "iconst_4",
    "iconst_5",
    "lconst_0",
    "lconst_1",
    "fconst_0",
    "fconst_1",
    "fconst_2",
    "dconst_0",
    "dconst_1",
    "bipush",
    "sipush",
    "ldc",
    "ldc_w",
    "ldc2_w",
    "iload",
    "lload",
    "fload",
    "dload",
    "aload",
    "iload_0",
    "iload_1",
    "iload_2",
    "iload_3",
    "lload_0",
    "lload_1",
    "lload_2",
    "lload_3",
    "fload_0",
    "fload_1",
    "fload_2",
    "fload_3",
    "dload_0",
    "dload_1",
    "dload_2",
    "dload_3",
    "aload_0",
    "aload_1",
    "aload_2",
    "aload_3",
    "iaload",
    "laload",
    "faload",
    "daload",
    "aaload",
    "baload",
    "caload",
    "saload",
    "istore",
    "lstore",
    "fstore",
    "dstore",
    "astore",
    "istore_0",
    "istore_1",
    "istore_2",
    "istore_3",
    "lstore_0",
    "lstore_1",
    "lstore_2",
    "lstore_3",
    "fstore_0",
    "fstore_1",
    "fstore_2",
    "fstore_3",
    "dstore_0",
    "dstore_1",
    "dstore_2",
    "dstore_3",
    "astore_0",
    "astore_1",
    "astore_2",
    "astore_3",
    "iastore",
    "lastore",
    "fastore",
    "dastore",
    "aastore",
    "bastore",
    "castore",
    "sastore",
    "pop",
    "pop2",
    "dup",
    "dup_x1",
    "dup_x2",
    "dup2",
    "dup2_x1",
    "dup2_x2",
    "swap",
    "iadd",
    "ladd",
    "fadd",
    "dadd",
    "isub",
    "lsub",
    "fsub",
    "dsub",
    "imul",
    "lmul",
    "fmul",
    "dmul",
    "idiv",
    "ldiv",
    "fdiv",
    "ddiv",
    "irem",
    "lrem",
    "frem",
    "drem",
    "ineg",
    "lneg",
    "fneg",
    "dneg",
    "ishl",
    "lshl",
    "ishr",
    "lshr",
    "iushr",
    "lushr",
    "iand",
    "land",
    "ior",
    "lor",
    "ixor",
    "lxor",
    "iinc",
    "i2l",
    "i2f",
    "i2d",
    "l2i",
    "l2f",
    "l2d",
    "f2i",
    "f2l",
    "f2d",
    "d2i",
    "d2l",
    "d2f",
    "i2b",
    "i2c",
    "i2s",
    "lcmp",
    "fcmpl",
    "fcmpg",
    "dcmpl",
    "dcmpg",
    "ifeq",
    "ifne",
    "iflt",
    "ifge",
    "ifgt",
    "ifle",
    "if_icmpeq",
    "if_icmpne",
    "if_icmplt",
    "if_icmpge",
    "if_icmpgt",
    "if_icmple",
    "if_acmpeq",
    "if_acmpne",
    "goto",
    "jsr",
    "ret",
    "tableswitch",
    "lookupswitch",
    "ireturn",
    "lreturn",
    "freturn",
    "dreturn",
    "areturn",
    "return",
    "getstatic",
    "putstatic",
    "getfield",
    "putfield",
    "invokevirtual",
    "invokespecial",
    "invokestatic",
    "invokeinterface",
    "UNUSED",
    "new",
    "newarray",
    "anewarray",
    "arraylength",
    "athrow",
    "checkcast",
    "instanceof",
    "monitorenter",
    "monitorexit",
    "wide",
    "multianewarray",
    "ifnull",
    "ifnonnull",
    "goto_w",
    "jsr_w"
};

#endif
