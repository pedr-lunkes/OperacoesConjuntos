#include "../AVL/avl.h" 
#include "../LISTA/lista.h" 

#include <stdio.h>
#include <stdlib.h>

typedef struct set {
    void *estrutura;
    int tipo; // 1 para AVL, 0 para LISTA
}SET;


SET *set_criar(int tipo){
    SET* set = (SET *) malloc(sizeof(SET));
    set->tipo = tipo;

    if(set->tipo){
        set->estrutura = avl_criar();
    }else{
        set->estrutura = lista_criar();
    }

    return set;
}

bool set_pertence(SET *A, int elemento){
    if(A->tipo) return avl_pertence(A->estrutura, elemento);
    else return lista_pertence(A->estrutura, elemento);
}

bool set_inserir (SET *s, int elemento){
    if(s->tipo) return avl_inserir(s->estrutura, elemento);
    else return lista_inserir(s->estrutura, elemento);
}

bool set_remover(SET *s, int elemento){
    if(s->tipo) return avl_remover(s->estrutura, elemento);
    else return lista_remover(s->estrutura, elemento);
}

void set_apagar(SET **s){
    if(s == NULL) return;

    if((*s)->tipo) avl_apagar((AVL **) &(*s)->estrutura);
    else lista_apagar((LISTA**) &(*s)->estrutura);

    free(*s);

    return;
}

void set_imprimir(SET *s){
    if(s->tipo) avl_imprimir(s->estrutura);
    else lista_imprimir(s->estrutura);
}

SET *set_uniao(SET *A, SET *B){
    SET* C = (SET *) malloc(sizeof(SET));

    if(A->tipo) C->estrutura = (AVL *) avl_uniao(A->estrutura, B->estrutura);
    else C->estrutura = (LISTA *) lista_uniao(A->estrutura, B->estrutura);

    C->tipo = A->tipo;

    return C;
}

SET *set_interseccao(SET *A, SET *B){
    SET* C = (SET *) malloc(sizeof(SET));

    if(A->tipo) C->estrutura = avl_interseccao(A->estrutura, B->estrutura);
    else C->estrutura = lista_interseccao(A->estrutura, B->estrutura);

    C->tipo = A->tipo;

    return C;
}
