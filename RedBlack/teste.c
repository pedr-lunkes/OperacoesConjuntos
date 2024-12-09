#include <stdio.h>
#include <stdlib.h>
#include "llrb.h"

int main(void){
    LLRB *T = llrb_criar();
    llrb_inserir(T, item_criar(20, NULL));
    llrb_inserir(T, item_criar(10, NULL));
    llrb_inserir(T, item_criar(30, NULL));
    llrb_inserir(T, item_criar(5, NULL));
    llrb_inserir(T, item_criar(15, NULL));
    llrb_inserir(T, item_criar(25, NULL));
    // llrb_inserir(T, item_criar(40, NULL));
    llrb_inserir(T, item_criar(3, NULL));
    llrb_inserir(T, item_criar(7, NULL));
    llrb_inserir(T, item_criar(13, NULL));
    llrb_inserir(T, item_criar(18, NULL));
    llrb_inserir(T, item_criar(23, NULL));
    llrb_inserir(T, item_criar(28, NULL));

    llrb_remover(T, 30);

    llrb_printar(T);
    llrb_apagar(&T);

    return 0;
}