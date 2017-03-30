#ifndef classinstance_h
#define classinstance_h

#include "tipos.h"
#include "object.h"
#include "classruntime.h"

#include <map>
#include <string>

using namespace std;

/**
 * Representa uma instância de classe.
 */
class ClassInstance : public Object {
    
public:
    /**
     * @brief Construtor padrão.
     * @param classRuntime A classe correspondente ao objeto.
     */
    ClassInstance(ClassRuntime *classRuntime);
    
    /**
     * @brief Destrutor padrão.
     */
    ~ClassInstance();
    
    /**
     * @brief Método utilizado para declaração do tipo de objeto.
     * @return O tipo de objeto.
     */
    ObjectType objectType();
    
    /**
     * @brief Obtém a classe correspondente ao objeto.
     * @return Retorna a classe do objeto.
     */
    ClassRuntime* getClassRuntime();
    
    /**
     * @brief Adiciona um valor no field de índice informado.
     *
     * Caso o índice do field (i.e. não exista na CP da classe atual seja inválido), um erro será emitido.
     * @param value O valor que será inserido no field.
     * @param fieldName O nome do field que será alterado.
     */
    void putValueIntoField(Value value, string fieldName);
    
    /**
     * @brief Obtém o valor contido em um field informado.
     *
     * Caso o nome do field seja inválido, um erro será emitido.
     * @param index O índice do field.
     * @return O valor correspondente ao field.
     */
    Value getValueFromField(string fieldName);
    
    /**
     * @brief Verifica se existe um field com o nome dado.
     * @param string O nome do field.
     * @return Retorna \c true caso o field existir, e \c false caso contrário.
     */
    bool fieldExists(string fieldName);
    
private:
    /**
     * Armazena a classe correspondente ao objeto.
     */
    ClassRuntime *_classRuntime;
    
    /**
     * Armazena os fields do objeto (de instância).
     */
    map<string, Value> _fields;
    
};

#endif /* classinstance_h */
