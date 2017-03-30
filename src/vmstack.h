#ifndef vmstack_h
#define vmstack_h

#include <stack>

#include "frame.h"

using namespace std;

#define FRAME_MAX_SIZE 50

/**
 * Classe para representar a pilha da JVM. Uma pilha é responsável por conter frames. O seu limite é dado por \c FRAME_MAX_SIZE
 *
 * Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
 */
class VMStack {
    
public:
    /**
     * @brief Obter a única instância da pilha.
     * @return A instância da pilha.
     */
    static VMStack& getInstance() {
        static VMStack instance;
        return instance;
    }

    /**
     * @brief Destrutor padrão.
     */
    ~VMStack();
    
    /**
     * @brief Adiciona um frame na pilha da JVM.
     * @param frame Um ponteiro para o frame que será adicionado na pilha.
     */
    void addFrame(Frame *frame);
    
    /**
     * @brief Obtém o frame no topo da pilha da JVM.
     * @return Retorna o frame no topo da pilha. Caso a pilha esteja vazia, é retornado \c NULL.
     */
    Frame* getTopFrame();
    
    /**
     * @brief Remove o frame do topo da pilha e o libera da memória.
     * @return Retorna \c true caso o frame foi deletado, e \c false caso contrário.
     */
    bool destroyTopFrame();
    
    /**
     * @brief Obtém o tamanho da pilha da JVM.
     * @return Obtém o número de frames contidos na pilha da JVM.
     */
    uint32_t size();
    
private:
    /**
     * @brief Construtor padrão.
     */
    VMStack();
    
    VMStack(VMStack const&); // não permitir implementação do construtor de cópia
    void operator=(VMStack const&); // não permitir implementação do operador de igual
    
    /**
     * Armazena a pilha da JVM, que contém frames.
     */
    stack<Frame*> _frameStack;
};

#endif /* vmstack_h */
