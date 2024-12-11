#ifndef _LLRB_H_
    #define _LLRB_H_
    #include <stdbool.h>

    #define BLACK false
    #define RED true

    typedef struct llrb_ LLRB;
    typedef struct no_ NO;

    LLRB *llrb_criar(void);
    void llrb_apagar(LLRB **T);

    void llrb_imprimir(LLRB *T);

    bool llrb_inserir(LLRB *T, int dado);
    bool llrb_remover(LLRB *T, int chave);

    bool llrb_pertence(LLRB *T, int dado);
    bool llrb_vazia(LLRB *T);

    LLRB *llrb_uniao(LLRB* rb1, LLRB* rb2);
    LLRB *llrb_interseccao(LLRB* rb1, LLRB* rb2);
#endif