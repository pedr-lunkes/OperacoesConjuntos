#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(void){
    AVL *T = avl_criar();
    avl_inserir(T, item_criar(30, NULL));
    avl_inserir(T, item_criar(25, NULL));
    avl_inserir(T, item_criar(45, NULL));
    avl_inserir(T, item_criar(15, NULL));
    avl_inserir(T, item_criar(41, NULL));
    avl_inserir(T, item_criar(35, NULL));
    avl_inserir(T, item_criar(43, NULL));
    avl_inserir(T, item_criar(56, NULL));
    avl_inserir(T, item_criar(50, NULL));
    avl_inserir(T, item_criar(49, NULL));
    avl_inserir(T, item_criar(60, NULL));
    avl_inserir(T, item_criar(65, NULL));

    // avl_inserir(T, item_criar(0, NULL));

    // avl_remover(T, 45);
    // avl_remover(T, 41);
    avl_imprimir(T);
    printf("%d", avl_altura(T));

    avl_apagar(&T);
    return 0;
}