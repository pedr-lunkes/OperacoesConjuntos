#include "AVL/avl.h" 
#include "RedBlack/llrb.h" 

#include <stdio.h>
#include <stdlib.h>

typedef struct set {
    void *estrutura;
    int tipo;   
}SET;


SET *set_criar(int tipo){
    if(tipo){
        // Inicia AVL
    }else{
        // Inicia RB
    }
}

bool set_pertence(SET *A, int elemento){
    // busca
}

bool set_inserir (SET *s, int elemento){
    // já existe
}

bool set_remover(SET *s, int elemento){
    // já existe
}

void set_apagar(SET **s){
    // já existe + apagar o set
}

void set_imprimir(SET *s){
    // já existe
}

SET *set_uniao(SET *A, SET *B){
    // manipulação direta dos SETs
}

SET *set_interseccao(SET *A, SET *B){
    // manipulação direta dos SETs
}
