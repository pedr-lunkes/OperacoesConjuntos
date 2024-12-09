#ifndef _AVL_H
    #define _AVL_H

    #define max(a,b) ((a > b) ? a : b)
    #define ERRO -32000

    #include <stdbool.h>
    #include "item.h"

    typedef struct avl_ AVL;

    AVL *avl_criar(void);
    void avl_apagar(AVL **T);
    int avl_altura(AVL *T);
    void avl_imprimir(AVL *T);

    bool avl_inserir(AVL *T, ITEM *item);
    bool avl_remover(AVL *T, int chave);
    
    ITEM *avl_busca(AVL *T, int chave);
    bool avl_vazia(AVL *T);
#endif