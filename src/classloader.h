#ifndef CLASSLOADER_H
#define CLASSLOADER_H

#include "tipos.h"

using namespace std;

/**
 * Carregador de classes (.class)
 *
 * Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
 */
class ClassLoader {

public:
    /**
     * @brief Obter a única instância do ClassLoader.
     * @return A instância do ClassLoader.
     */
    static ClassLoader& getInstance() {
        static ClassLoader instance;
        return instance;
    }
    
    /**
     * @brief Destrutor padrão.
     */
    ~ClassLoader();

/**
 * Lê o arquivo .class, verifica seus campos magic e version e carrega todas as estruturas descritas por este arquivo.
 * @param *fp Ponteiro para o arquivo .class a ser carregado.
 */
ClassFile* readClassFile(FILE *file);
    
private:
    /**
     * @brief Construtor padrão.
     */
    ClassLoader();
    
    ClassLoader(ClassLoader const&); // não permitir implementação do construtor de cópia
    void operator=(ClassLoader const&); // não permitir implementação do operador de igual
    
    /**
     * @brief Armazena \c true caso o computador seja little endian, e \c false caso contrário
     */
    bool isLittleEndian;
    
    /**
     * retorna TRUE se o sistema é Little Endian e FALSE caso contrario.
     * obtido de: http://stackoverflow.com/a/4181991/351527
     */
    bool testEndianess();

    /**
     * Lê 1 byte do arquivo .class.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return O byte lido.
     */
    u1 readU1(FILE *file);

    /**
     * Lê 2 bytes do arquivo .class, verificando se o sistema é Big Endian ou Little Endian para armazenamento adequado.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Os 2 bytes lidos.
     */
    u2 readU2(FILE *file);

    /**
     * Lê 4 bytes do arquivo .class, verificando se o sistema é Big Endian ou Little Endian para armazenamento adequado.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Os 4 bytes lidos.
     */
    u4 readU4(FILE *file);

    /**
     * Lê o campo magic no arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setMagic(FILE *fp, ClassFile *classFile);

    /**
     * Avalia se campo magic de uma struct ClassFile é válido.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     * @return Verdadeiro ou Falso.
     */
    bool isMagicValid(ClassFile *classFile);

    /**
     * Lê a versão de um arquivo .class e a armazena em uma estrutura ClassFile. A versão é dada por major_version.minor_version.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setVersion(FILE *fp, ClassFile *classFile);

    /**
     * Verifica a validade da versão de uma estrutura ClassFile; devendo esta ser igual ou anterior à versão explicitada em major.
     * O campo major_version da estrutura ClassFile é usado nessa avaliação.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     * @param major Versão a se comparar.
     * @return Verdadeiro de a versão é no máximo major ou Falso caso contrário
     */
    bool isVersionValid(ClassFile *classFile, uint16_t major);

    /**
     * Lê o tamanho da pool de constantes de um arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setConstantPoolSize(FILE *fp, ClassFile *classFile);

    /**
     * Preenche a pool de constantes de uma estrutura ClassFile a partir de um arquivo .class.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setConstantPool(FILE *fp, ClassFile *classFile);

    /**
     * Lê 2 bytes de um arquivo .class e os atribui a uma estrutura CONSTANT_Class_info.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Class_info preenchida com os 2 bytes lidos.
    */
    CONSTANT_Class_info getConstantClassInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Fieldref_info, preenchendo seus campos class_index e name_and_type_index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Fieldref_info preenchida.
     */
    CONSTANT_Fieldref_info getConstantFieldRefInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Methodref_info, preenchendo seus campos class_index e name_and_type_index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Methodref_info preenchida.
     */
    CONSTANT_Methodref_info getConstantMethodRefInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_InterfaceMethodref_info, preenchendo seus campos class_index e name_and_type_index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_InterfaceMethodref_info preenchida.
     */
    CONSTANT_InterfaceMethodref_info getConstantInterfaceMethodRefInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_String_info, preenchendo seu campo string_index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_String_info preenchida.
     */
    CONSTANT_String_info getConstantStringInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Integer_info, preenchendo seu campo bytes.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Integer_info preenchida.
     */
    CONSTANT_Integer_info getConstantIntegerInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Float_info, preenchendo seu campo bytes.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Float_info preenchida.
     */
    CONSTANT_Float_info getConstantFloatInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Long_info, preenchendo seus campos high_bytes e low_bytes.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Long_info preenchida.
     */
    CONSTANT_Long_info getConstantLongInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Double_info, preenchendo seus campos high_bytes e low_bytes.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Double_info preenchida.
     */
    CONSTANT_Double_info getConstantDoubleInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_NameAndType_info, preenchendo seus campos name_index e descriptor_index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_NameAndType_info preenchida.
     */
    CONSTANT_NameAndType_info getConstantNameAndTypeInfo(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura CONSTANT_Utf8_info, preenchendo seus campos length e bytes.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura CONSTANT_Utf8_info preenchida.
     */
    CONSTANT_Utf8_info getConstantUtf8Info(FILE *fp);

    /**
     * Lê as flags de acesso de um arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setAccessFlags(FILE *fp, ClassFile *classFile);

    /**
     * Lê o índice this_class de um arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setThisClass(FILE *fp, ClassFile *classFile);

    /**
     * Lê o índice super_class de um arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setSuperClass(FILE *fp, ClassFile *classFile);

    /**
     * Lê o índice interfaces_count de um arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setInterfacesCount(FILE *fp, ClassFile *classFile);

    /**
     * Aloca em ClassFile um vetor de interfaces, referenciado pelo ponteiro interfaces, e o preenche com os dados de um arquivo .class.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setInterfaces(FILE *fp, ClassFile *classFile);

    /**
     * Lê o índice fields_count de um arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setFieldsCount(FILE *fp, ClassFile *classFile);

    /**
     * Aloca em ClassFile um vetor de estruturas field_info, o qual é referenciado pelo ponteiro fields, e o preenche com os dados de um arquivo .class.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setFields(FILE *fp, ClassFile *classFile);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura attribute_info, preenchendo seus campos attribute_name_index, attribute_length e info.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     * @return Uma estrutura attribute_info preenchida.
     */
    attribute_info getAttributeInfo(FILE *fp, ClassFile *classFile);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura ConstantValue_attribute, preenchendo seu campo index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura ConstantValue_attribute preenchida.
     */
    ConstantValue_attribute getAttributeConstantValue(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura ExceptionTable, preenchendo seus campos start_pc, end_pc, handler_pc e catch_type.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura ExceptionTable preenchida.
     */
    ExceptionTable getExceptionTable(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura Code_attribute, preenchendo seus campos max_stack, max_locals, code_length, code, exception_table_length, exception_table, attributes_count e attributes.
    * @param *fp Ponteiro para o arquivo .class a ser carregado.
    * @return Uma estrutura Code_attribute preenchida.
    */
    Code_attribute getAttributeCode(FILE *fp, ClassFile *classFile);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura Exceptions_attribute, preenchendo seus campos number_of_exceptions e exception_index_table.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura Exceptions_attribute preenchida.
     */
    Exceptions_attribute getAttributeExceptions(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura Class, preenchendo seus campos inner_class_info_index, outer_class_info_index, inner_name_index e inner_class_access_flags.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura Exceptions_attribute preenchida.
    */
    Class getClass(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura InnerClasses_attribute, preenchendo seus campos number_of_classes e classes.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura InnerClasses_attribute preenchida.
     */
    InnerClasses_attribute getAttributeInnerClasses(FILE *fp);

    /**
     * Fornece uma estrutura Synthetic_attribute.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura Synthetic_attribute.
     */
    Synthetic_attribute getAttributeSynthetic(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura SourceFile_attribute, preenchendo seu campo sourcefile_index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura SourceFile_attribute preenchida.
     */
    SourceFile_attribute getAttributeSourceFile(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura LineNumberTable, preenchendo seus campos start_pc e line_number.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura LineNumberTable preenchida.
     */
    LineNumberTable getLineNumberTable(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura LineNumberTable_attribute, preenchendo seus campos line_number_table_length e line_number_table.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura LineNumberTable_attribute preenchida.
     */
    LineNumberTable_attribute getAttributeLineNumberTable(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura LocalVariableTable, preenchendo seus campos start_pc, length, name_index, descriptor_index e index.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura LocalVariableTable preenchida.
     */
    LocalVariableTable getLocalVariableTable(FILE *fp);

    /**
     * Extrai de um arquivo .class informações relativas a uma estrutura LocalVariableTable_attribute, preenchendo seus campos local_variable_table_length e local_variable_table.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura LocalVariableTable_attribute preenchida.
     */
    LocalVariableTable_attribute getAttributeLocalVariable(FILE *fp);

    /**
     * Fornece uma estrutura Deprecated_attribute.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @return Uma estrutura Deprecated_attribute.
     */
    Deprecated_attribute getAttributeDeprecated(FILE *fp);

    /**
     * Fornece a estrutura CONSTANT_Utf8_info contida no índice index da pool de constantes de uma estrutura ClassFile.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     * @param index índice da pool de constantes.
     * @return Uma estrutura CONSTANT_Utf8_info com os dados constantes no índice index da pool de constantes de uma estrutura ClassFile.
     */
    CONSTANT_Utf8_info getUtf8FromConstantPool(u2 index, ClassFile *classFile);

    /**
     * Lê o campo methods_count no arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setMethodsCount(FILE *fp, ClassFile *classFile);

    /**
     * Aloca em ClassFile um vetor de métodos, referenciado pelo ponteiro methods, e o preenche com os dados de um arquivo .class.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setMethods(FILE *fp, ClassFile *classFile);

    /**
     * Lê o campo attributes_count no arquivo .class e o armazena em uma estrutura ClassFile.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setAttributesCount(FILE *fp, ClassFile *classFile);

    /**
     * Aloca em ClassFile um vetor de atributos, referenciado pelo ponteiro attributes, e o preenche com os dados de um arquivo .class.
     * @param *fp Ponteiro para o arquivo .class a ser carregado.
     * @param *classFile Ponteiro para uma instância de struct ClassFile, que descreve a estrutura (parcial, no momento) de um arquivo .class.
     */
    void setAttributes(FILE *fp, ClassFile *classFile);
};

#endif
