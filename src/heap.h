#ifndef Heap_h
#define Heap_h

#include <vector>

#include "object.h"

using namespace std;

/**
 * Heap (i.e. vetor de objetos).
 *
 * Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
 */
class Heap {
public:
    /**
     * @brief Obter a única instância da Heap.
     * @return A instância da Heap.
     */
    static Heap& getInstance() {
        static Heap instance;
        return instance;
    }
    
    /**
     * @brief Destrutor padrão.
     */
    ~Heap();
    
    /**
     * @brief Adiciona um objeto à heap.
     */
    void addObject(Object *object);
    
private:
    /**
     * Construtor padrão.
     */
    Heap();
    
    Heap(Heap const&); // não permitir implementação do construtor de cópia
    void operator=(Heap const&); // não permitir implementação do operador de igual
    
    /**
     * Vetor interno que armazena todos os objetos.
     */
    vector<Object*> _objectVector;
};

#endif // Heap_h
