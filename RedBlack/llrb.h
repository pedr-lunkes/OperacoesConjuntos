#ifndef _LLRB_H_
    #define _LLRB_H_
    #include "item.h"
    #include <stdbool.h>

    typedef struct llrb_ LLRB;

    LLRB *llrb_criar(void);
    void llrb_apagar(LLRB **T);

    void llrb_printar(LLRB *T);

    bool llrb_inserir(LLRB *T, ITEM *item);
    bool llrb_remover(LLRB *T, int chave);

    ITEM llrb_busca(LLRB *T, ITEM *item);
    bool llrb_vazia(LLRB *T);
#endif