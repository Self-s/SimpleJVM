#ifndef arrayobject_h
#define arrayobject_h

#include "tipos.h"
#include "object.h"

#include <vector>

using namespace std;

/**
 * Representa um objeto do tipo array.
 */
class ArrayObject : public Object {
    
public:
    /**
     * @brief Construtor padrão.
     * @param type O tipo de dado que o array irá armazenar.
     */
    ArrayObject(ValueType type);
    
    /**
     * @brief Destrutor padrão.
     */
    ~ArrayObject();
    
    /**
     * @brief Representa o tipo de objeto (ObjectType::ARRAY).
     * @return O tipo de objeto.
     */
    ObjectType objectType();
    
    /**
     * @brief Obtém o tipo de conteúdo do array.
     * @return O tipo que o array armazena.
     */
    ValueType arrayContentType();
    
    /**
     * @brief Realiza a adição de um valor no array.
     * @param value O valor que será inserido no array.
     */
    void pushValue(Value value);
    
    /**
     * @brief Remove um elemento do array dado o seu índice.
     * @param O índice do elemento que será removido.
     * @return O valor removido.
     */
    Value removeAt(uint32_t index);
    
    /**
     * @brief Remove o último elemento do array.
     * @return O valor removido.
     */
    Value removeLast();
    
    /**
     * @brief Remove o primeiro elemento do array.
     * @return O valor removido.
     */
    Value removeFirst();
    
    /**
     * @brief Obtém o tamanho atual do array.
     * @return O tamanho atual do array.
     */
    uint32_t getSize();

    /**
     * @brief Obtém o elemento dado o seu índice.
     * @param index O índice do elemento.
     * @return O elemento do array de índice index.
     */
    Value getValue(uint32_t index);
    
    /**
     * @brief Substitui um elemento do array.
     * @param index O índice do elemento que será substituído.
     * @param value O novo valor que será colocado.
     */
    void changeValueAt(uint32_t index, Value value);
    
private:
    /**
     * O tipo de valor que o array armazena.
     */
    ValueType _arrayType;
    
    /**
     * O vetor interno que armazena os elementos.
     */
    vector<Value> _elements;
};

#endif /* arrayobject_h */
