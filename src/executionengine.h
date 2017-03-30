#ifndef executionengine_h
#define executionengine_h

#include "tipos.h"

#include "classinstance.h"
#include "arrayobject.h"

#include <string>
#include <queue>
#include <stack>

using namespace std;

class ExecutionEngine;
typedef void (ExecutionEngine::*FunctionPointer)();

/**
 * É responsável por realizar a execução do .class.
 *
 * Essa classe é um singleton, ou seja, somente existe no máximo 1 instância dela para cada instância da JVM.
 */
class ExecutionEngine {
public:
    /**
     * @brief Obter a única instância da Execution Engine.
     * @return A instância da Execution Engine.
     */
    static ExecutionEngine& getInstance() {
        static ExecutionEngine instance;
        return instance;
    }
    
    /**
     * @brief Destrutor padrão.
     */
    ~ExecutionEngine();
    
    /**
     * @brief Inicia a Execution Engine com a classe passada.
     *
     * Esse método irá iniciar execução através do método estático main.
     * @param
     */
    void startExecutionEngine(ClassRuntime *classRuntime);
    
    /**
     * @brief Verifica se o método informado existe na classe atual.
     * @param classRuntime A classe que a pesquisa irá ser realizada.
     * @param name O nome do método.
     * @param descriptor O descritor do método.
     * @return Retorna \c true caso o método exista, ou \c false caso contrário.
     */
    bool doesMethodExist(ClassRuntime *classRuntime, string name, string descriptor);

    /**
     * @brief Popula os vetores de um multiarray
     * @param array Cada array que representa uma dimansão
     * @param value Referência à uma classe 
     * @param count Número de elementos em um array
     */
    void populateMultiarray(ArrayObject *array, ValueType value, stack<int> count);
    
private:
    /**
     * @brief Construtor padrão.
     */
    ExecutionEngine();
    
    ExecutionEngine(ExecutionEngine const&); // não permitir implementação do construtor de cópia
    void operator=(ExecutionEngine const&); // não permitir implementação do operador de igual
    
    /**
     * Armazena \c true se a última instrução foi um wide, e \c false caso contrário.
     */
    bool _isWide;
    
    /**
     * @brief Implementa a funcionalidade da instrução nop.
     */
    void i_nop();
    
    /**
     * @brief Implementa a funcionalidade da instrução aconst_null.
     */
    void i_aconst_null();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_m1.
     */
    void i_iconst_m1();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_0.
     */
    void i_iconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_1.
     */
    void i_iconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_2.
     */
    void i_iconst_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_3.
     */
    void i_iconst_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_4.
     */
    void i_iconst_4();
    
    /**
     * @brief Implementa a funcionalidade da instrução iconst_5.
     */
    void i_iconst_5();
    
    /**
     * @brief Implementa a funcionalidade da instrução lconst_0.
     */
    void i_lconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução lconst_1.
     */
    void i_lconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fconst_0.
     */
    void i_fconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução fconst_1.
     */
    void i_fconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fconst_2.
     */
    void i_fconst_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dconst_0.
     */
    void i_dconst_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução dconst_1.
     */
    void i_dconst_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução bipush.
     */
    void i_bipush();
    
    /**
     * @brief Implementa a funcionalidade da instrução sipush.
     */
    void i_sipush();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldc.
     */
    void i_ldc();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldc_w.
     */
    void i_ldc_w();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldc2_w.
     */
    void i_ldc2_w();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload.
     */
    void i_iload();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload.
     */
    void i_lload();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload.
     */
    void i_fload();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload.
     */
    void i_dload();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload.
     */
    void i_aload();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_0.
     */
    void i_iload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_1.
     */
    void i_iload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_2.
     */
    void i_iload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução iload_3.
     */
    void i_iload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_0.
     */
    void i_lload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_1.
     */
    void i_lload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_2.
     */
    void i_lload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução lload_3.
     */
    void i_lload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_0.
     */
    void i_fload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_1.
     */
    void i_fload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_2.
     */
    void i_fload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução fload_3.
     */
    void i_fload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_0.
     */
    void i_dload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_1.
     */
    void i_dload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_2.
     */
    void i_dload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dload_3.
     */
    void i_dload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_0.
     */
    void i_aload_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_1.
     */
    void i_aload_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_2.
     */
    void i_aload_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução aload_3.
     */
    void i_aload_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução iaload.
     */
    void i_iaload();
    
    /**
     * @brief Implementa a funcionalidade da instrução laload.
     */
    void i_laload();
    
    /**
     * @brief Implementa a funcionalidade da instrução faload.
     */
    void i_faload();
    
    /**
     * @brief Implementa a funcionalidade da instrução daload.
     */
    void i_daload();
    
    /**
     * @brief Implementa a funcionalidade da instrução aaload.
     */
    void i_aaload();
    
    /**
     * @brief Implementa a funcionalidade da instrução baload.
     */
    void i_baload();
    
    /**
     * @brief Implementa a funcionalidade da instrução caload.
     */
    void i_caload();
    
    /**
     * @brief Implementa a funcionalidade da instrução saload.
     */
    void i_saload();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore.
     */
    void i_istore();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore.
     */
    void i_lstore();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore.
     */
    void i_fstore();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore.
     */
    void i_dstore();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore.
     */
    void i_astore();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_0.
     */
    void i_istore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_1.
     */
    void i_istore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_2.
     */
    void i_istore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução istore_3.
     */
    void i_istore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_0.
     */
    void i_lstore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_1.
     */
    void i_lstore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_2.
     */
    void i_lstore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução lstore_3.
     */
    void i_lstore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_0.
     */
    void i_fstore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_1.
     */
    void i_fstore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_2.
     */
    void i_fstore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução fstore_3.
     */
    void i_fstore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_0.
     */
    void i_dstore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_1.
     */
    void i_dstore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_2.
     */
    void i_dstore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dstore_3.
     */
    void i_dstore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_0.
     */
    void i_astore_0();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_1.
     */
    void i_astore_1();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_2.
     */
    void i_astore_2();
    
    /**
     * @brief Implementa a funcionalidade da instrução astore_3.
     */
    void i_astore_3();
    
    /**
     * @brief Implementa a funcionalidade da instrução iastore.
     */
    void i_iastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução lastore.
     */
    void i_lastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução fastore.
     */
    void i_fastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução dastore.
     */
    void i_dastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução aastore.
     */
    void i_aastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução bastore.
     */
    void i_bastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução castore.
     */
    void i_castore();
    
    /**
     * @brief Implementa a funcionalidade da instrução sastore.
     */
    void i_sastore();
    
    /**
     * @brief Implementa a funcionalidade da instrução pop.
     */
    void i_pop();
    
    /**
     * @brief Implementa a funcionalidade da instrução pop2.
     */
    void i_pop2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup.
     */
    void i_dup();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup_x1.
     */
    void i_dup_x1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup_x2.
     */
    void i_dup_x2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup2.
     */
    void i_dup2();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup2_x1.
     */
    void i_dup2_x1();
    
    /**
     * @brief Implementa a funcionalidade da instrução dup2_x2.
     */
    void i_dup2_x2();
    
    /**
     * @brief Implementa a funcionalidade da instrução swap.
     */
    void i_swap();
    
    /**
     * @brief Implementa a funcionalidade da instrução iadd.
     */
    void i_iadd();
    
    /**
     * @brief Implementa a funcionalidade da instrução ladd.
     */
    void i_ladd();
    
    /**
     * @brief Implementa a funcionalidade da instrução fadd.
     */
    void i_fadd();
    
    /**
     * @brief Implementa a funcionalidade da instrução dadd.
     */
    void i_dadd();
    
    /**
     * @brief Implementa a funcionalidade da instrução isub.
     */
    void i_isub();
    
    /**
     * @brief Implementa a funcionalidade da instrução lsub.
     */
    void i_lsub();
    
    /**
     * @brief Implementa a funcionalidade da instrução fsub.
     */
    void i_fsub();
    
    /**
     * @brief Implementa a funcionalidade da instrução dsub.
     */
    void i_dsub();
    
    /**
     * @brief Implementa a funcionalidade da instrução imul.
     */
    void i_imul();
    
    /**
     * @brief Implementa a funcionalidade da instrução lmul.
     */
    void i_lmul();
    
    /**
     * @brief Implementa a funcionalidade da instrução fmul.
     */
    void i_fmul();
    
    /**
     * @brief Implementa a funcionalidade da instrução dmul.
     */
    void i_dmul();
    
    /**
     * @brief Implementa a funcionalidade da instrução idiv.
     */
    void i_idiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução ldiv.
     */
    void i_ldiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução fdiv.
     */
    void i_fdiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução ddiv.
     */
    void i_ddiv();
    
    /**
     * @brief Implementa a funcionalidade da instrução irem.
     */
    void i_irem();
    
    /**
     * @brief Implementa a funcionalidade da instrução lrem.
     */
    void i_lrem();
    
    /**
     * @brief Implementa a funcionalidade da instrução frem.
     */
    void i_frem();
    
    /**
     * @brief Implementa a funcionalidade da instrução drem.
     */
    void i_drem();
    
    /**
     * @brief Implementa a funcionalidade da instrução ineg.
     */
    void i_ineg();
    
    /**
     * @brief Implementa a funcionalidade da instrução lneg.
     */
    void i_lneg();
    
    /**
     * @brief Implementa a funcionalidade da instrução fneg.
     */
    void i_fneg();
    
    /**
     * @brief Implementa a funcionalidade da instrução dneg.
     */
    void i_dneg();
    
    /**
     * @brief Implementa a funcionalidade da instrução ishl.
     */
    void i_ishl();
    
    /**
     * @brief Implementa a funcionalidade da instrução lshl.
     */
    void i_lshl();
    
    /**
     * @brief Implementa a funcionalidade da instrução ishr.
     */
    void i_ishr();
    
    /**
     * @brief Implementa a funcionalidade da instrução lshr.
     */
    void i_lshr();
    
    /**
     * @brief Implementa a funcionalidade da instrução iushr.
     */
    void i_iushr();
    
    /**
     * @brief Implementa a funcionalidade da instrução lushr.
     */
    void i_lushr();
    
    /**
     * @brief Implementa a funcionalidade da instrução iand.
     */
    void i_iand();
    
    /**
     * @brief Implementa a funcionalidade da instrução land.
     */
    void i_land();
    
    /**
     * @brief Implementa a funcionalidade da instrução ior.
     */
    void i_ior();
    
    /**
     * @brief Implementa a funcionalidade da instrução lor.
     */
    void i_lor();
    
    /**
     * @brief Implementa a funcionalidade da instrução ixor.
     */
    void i_ixor();
    
    /**
     * @brief Implementa a funcionalidade da instrução lxor.
     */
    void i_lxor();
    
    /**
     * @brief Implementa a funcionalidade da instrução iinc.
     */
    void i_iinc();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2l.
     */
    void i_i2l();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2f.
     */
    void i_i2f();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2d.
     */
    void i_i2d();
    
    /**
     * @brief Implementa a funcionalidade da instrução l2i.
     */
    void i_l2i();
    
    /**
     * @brief Implementa a funcionalidade da instrução l2f.
     */
    void i_l2f();
    
    /**
     * @brief Implementa a funcionalidade da instrução l2d.
     */
    void i_l2d();
    
    /**
     * @brief Implementa a funcionalidade da instrução f2i.
     */
    void i_f2i();
    
    /**
     * @brief Implementa a funcionalidade da instrução f2l.
     */
    void i_f2l();
    
    /**
     * @brief Implementa a funcionalidade da instrução f2d.
     */
    void i_f2d();
    
    /**
     * @brief Implementa a funcionalidade da instrução d2i.
     */
    void i_d2i();
    
    /**
     * @brief Implementa a funcionalidade da instrução d2l.
     */
    void i_d2l();
    
    /**
     * @brief Implementa a funcionalidade da instrução d2f.
     */
    void i_d2f();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2b.
     */
    void i_i2b();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2c.
     */
    void i_i2c();
    
    /**
     * @brief Implementa a funcionalidade da instrução i2s.
     */
    void i_i2s();
    
    /**
     * @brief Implementa a funcionalidade da instrução lcmp.
     */
    void i_lcmp();
    
    /**
     * @brief Implementa a funcionalidade da instrução fcmpl.
     */
    void i_fcmpl();
    
    /**
     * @brief Implementa a funcionalidade da instrução fcmpg.
     */
    void i_fcmpg();
    
    /**
     * @brief Implementa a funcionalidade da instrução dcmpl.
     */
    void i_dcmpl();
    
    /**
     * @brief Implementa a funcionalidade da instrução dcmpg.
     */
    void i_dcmpg();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifeq.
     */
    void i_ifeq();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifne.
     */
    void i_ifne();
    
    /**
     * @brief Implementa a funcionalidade da instrução iflt.
     */
    void i_iflt();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifge.
     */
    void i_ifge();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifgt.
     */
    void i_ifgt();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifle.
     */
    void i_ifle();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpeq.
     */
    void i_if_icmpeq();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpne.
     */
    void i_if_icmpne();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmplt.
     */
    void i_if_icmplt();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpge.
     */
    void i_if_icmpge();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmpgt.
     */
    void i_if_icmpgt();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_icmple.
     */
    void i_if_icmple();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_acmpeq.
     */
    void i_if_acmpeq();
    
    /**
     * @brief Implementa a funcionalidade da instrução if_acmpne.
     */
    void i_if_acmpne();
    
    /**
     * @brief Implementa a funcionalidade da instrução goto.
     */
    void i_goto();
    
    /**
     * @brief Implementa a funcionalidade da instrução jsr.
     */
    void i_jsr();
    
    /**
     * @brief Implementa a funcionalidade da instrução ret.
     */
    void i_ret();
    
    /**
     * @brief Implementa a funcionalidade da instrução tableswitch.
     */
    void i_tableswitch();
    
    /**
     * @brief Implementa a funcionalidade da instrução lookupswitch.
     */
    void i_lookupswitch();
    
    /**
     * @brief Implementa a funcionalidade da instrução ireturn.
     */
    void i_ireturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução lreturn.
     */
    void i_lreturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução freturn.
     */
    void i_freturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução dreturn.
     */
    void i_dreturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução areturn.
     */
    void i_areturn();
    
    /**
     * @brief Implementa a funcionalidade da instrução return.
     */
    void i_return();
    
    /**
     * @brief Implementa a funcionalidade da instrução getstatic.
     */
    void i_getstatic();
    
    /**
     * @brief Implementa a funcionalidade da instrução putstatic.
     */
    void i_putstatic();
    
    /**
     * @brief Implementa a funcionalidade da instrução getfield.
     */
    void i_getfield();
    
    /**
     * @brief Implementa a funcionalidade da instrução putfield.
     */
    void i_putfield();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokevirtual.
     */
    void i_invokevirtual();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokespecial.
     */
    void i_invokespecial();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokestatic.
     */
    void i_invokestatic();
    
    /**
     * @brief Implementa a funcionalidade da instrução invokeinterface.
     */
    void i_invokeinterface();
    
    /**
     * @brief Implementa a funcionalidade da instrução new.
     */
    void i_new();
    
    /**
     * @brief Implementa a funcionalidade da instrução newarray.
     */
    void i_newarray();
    
    /**
     * @brief Implementa a funcionalidade da instrução anewarray.
     */
    void i_anewarray();
    
    /**
     * @brief Implementa a funcionalidade da instrução arraylength.
     */
    void i_arraylength();
    
    /**
     * @brief Implementa a funcionalidade da instrução athrow.
     */
    void i_athrow();
    
    /**
     * @brief Implementa a funcionalidade da instrução checkcast.
     */
    void i_checkcast();
    
    /**
     * @brief Implementa a funcionalidade da instrução instanceof.
     */
    void i_instanceof();
    
    /**
     * @brief Implementa a funcionalidade da instrução monitorenter.
     */
    void i_monitorenter();
    
    /**
     * @brief Implementa a funcionalidade da instrução monitorexit.
     */
    void i_monitorexit();
    
    /**
     * @brief Implementa a funcionalidade da instrução wide.
     */
    void i_wide();
    
    /**
     * @brief Implementa a funcionalidade da instrução multianewarray.
     */
    void i_multianewarray();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifnull.
     */
    void i_ifnull();
    
    /**
     * @brief Implementa a funcionalidade da instrução ifnonnull.
     */
    void i_ifnonnull();
    
    /**
     * @brief Implementa a funcionalidade da instrução goto_w.
     */
    void i_goto_w();
    
    /**
     * @brief Implementa a funcionalidade da instrução jsr_w.
     */
    void i_jsr_w();
    
    /**
     * @brief Inicializa o vetor de ponteiros de funções.
     */
    void initInstructions();
    
    /**
     * O vetor de ponteiros de funções.
     */
    FunctionPointer _instructionFunctions[202];
};

#endif /* executionengine_h */
