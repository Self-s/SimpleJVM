#ifndef stringobject_h
#define stringobject_h

#include "object.h"

#include <string>

using namespace std;

/**
 * Representa um objeto do tipo String.
 */
class StringObject : public Object {
    
public:
    /**
     * @brief Construtor padrão.
     * @param s O valor inicial da string.
     */
    StringObject(string s = "");
    
    /**
     * @brief Destrutor padrão.
     */
    ~StringObject();
    
    /**
     * @brief Obtém o tipo do objeto (string).
     * @return O tipo do objeto.
     */
    ObjectType objectType();
    
    /**
     * @brief Obtém a sequência de caracteres presente na string.
     * @return Retorna a string como uma std::string.
     */
    string getString();

    /**
     * @brief Substitui o valor da string.
     * @param s O novo valor da string.
     */
    void setString(string s);
    
private:
    /**
     * A string interna.
     */
    string _internalString;
    
};

#endif /* stringobject_h */
