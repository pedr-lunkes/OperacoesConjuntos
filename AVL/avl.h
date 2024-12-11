#ifndef _AVL_H
    #define _AVL_H

    #define max(a,b) ((a > b) ? a : b)
    #define ERRO -32000

    #include <stdbool.h>

    typedef struct avl_ AVL;
    typedef struct no_ NO;

    AVL *avl_criar(void);
    void avl_apagar(AVL **T);
    int avl_altura(AVL *T);
    void avl_imprimir(AVL *T);

    bool avl_inserir(AVL *T, int dado);
    bool avl_remover(AVL *T, int chave);
    
    NO *avl_pertence(AVL *T, int chave);
    bool avl_vazia(AVL *T);

    AVL *avl_uniao(AVL* rb1, AVL* rb2);
    AVL *avl_interseccao(AVL* rb1, AVL* rb2);
#endif