#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

typedef struct no_{
    struct no_ *esq;
    struct no_ *dir;
    ITEM *item;
    int FB;
    int altura;
} NO;

typedef struct avl_{
    NO *raiz;
} AVL;

AVL *avl_criar(void){
    AVL *T = (AVL *) malloc(sizeof(AVL));

    if(T != NULL)
        T->raiz = NULL;

    return T;
}

void avl_apagar_no(NO **raiz){
    if(*raiz != NULL){
        avl_apagar_no(&(*raiz)->esq);
        avl_apagar_no(&(*raiz)->dir);
        item_apagar(&(*raiz)->item);
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

void avl_apagar(AVL **T){
    if(*T != NULL){
        avl_apagar_no(&(*T)->raiz);
        free(*T);
        *T = NULL;
    }

    return;
}

int avl_altura_no(NO *raiz){
    if(raiz != NULL)
        return raiz->altura;

    return -1;
}

int avl_altura(AVL *T){
    if(T != NULL)
        return avl_altura_no(T->raiz);

    return ERRO;
}

void avl_imprimir_no(NO *raiz){
    // Pre-Ordem
    if(raiz != NULL){
        printf("%d ", item_get_chave(raiz->item));
        avl_imprimir_no(raiz->esq);
        avl_imprimir_no(raiz->dir);
    }

    return;
}

void avl_imprimir(AVL *T){
    if(T != NULL)
        avl_imprimir_no(T->raiz);
    return;
}

NO *avl_cria_no(ITEM *item){
    NO *no = (NO *) malloc(sizeof(NO));

    if(no != NULL){
        no->esq = NULL;
        no->dir = NULL;
        no->item = item;
        no->FB = 0;
        no->altura = 0;
    }

    return no;
}

NO *rodar_direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    // a->FB = 0;
    // b->FB = 0;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;

    return b;
}

NO *rodar_esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    // a->FB = 0;
    // b->FB = 0;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;

    return b;
}

NO *rodar_esquerda_direita(NO *a){
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

NO *rodar_direita_esquerda(NO *a){
    a->dir = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

NO *avl_inserir_no(NO *raiz, NO *novo){
    if(raiz == NULL)
        raiz = novo;

    else if(item_get_chave(raiz->item) > item_get_chave(novo->item))
        raiz->esq = avl_inserir_no(raiz->esq, novo);
    else if(item_get_chave(raiz->item) < item_get_chave(novo->item))
        raiz->dir = avl_inserir_no(raiz->dir, novo);
    else
        return NULL;

    raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
    raiz->FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

    if(raiz->FB == -2)
        if(raiz->dir->FB <= 0)
            raiz = rodar_esquerda(raiz);
        else
            raiz = rodar_direita_esquerda(raiz);
    else if(raiz->FB == 2)
        if(raiz->esq->FB >= 0)
            raiz = rodar_direita(raiz);
        else
            raiz = rodar_esquerda_direita(raiz);

    return raiz;
}

bool avl_inserir(AVL *T, ITEM *item){
    if(T != NULL){
        NO *novo = avl_cria_no(item);
        if(novo != NULL){
            T->raiz = avl_inserir_no(T->raiz, novo);
            return true;
        }
    }

    return false;
}

void troca_max_esq(NO *raiz, NO *ant, NO *troca){
    if(troca->dir != NULL){
        troca_max_esq(raiz, troca, troca->dir);
        return;
    }
    
    if(ant == raiz)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;
    
    item_apagar(&(raiz->item));
    raiz->item = troca->item;
    free(troca);
    troca = NULL;
    return;
}

NO *avl_remover_no(NO **raiz, int chave){
    if(*raiz == NULL)
        return NULL;

    if(item_get_chave((*raiz)->item) == chave){
        NO *p = *raiz;
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else
                *raiz = (*raiz)->esq;
            
            item_apagar(&(p->item));
            free(p);
            p = NULL;
        } else
            troca_max_esq(*raiz, *raiz, (*raiz)->esq);
    }

    else if(item_get_chave((*raiz)->item) > chave)
        (*raiz)->esq = avl_remover_no(&(*raiz)->esq, chave);
    else
        (*raiz)->dir = avl_remover_no(&(*raiz)->dir, chave);
    
    if(*raiz != NULL){
        (*raiz)->FB = avl_altura_no((*raiz)->esq) - avl_altura_no((*raiz)->dir);
        (*raiz)->altura = max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir)) + 1;

        if((*raiz)->FB == -2)
            if((*raiz)->dir->FB <= 0)
                (*raiz) = rodar_esquerda(*raiz);
            else
                (*raiz) = rodar_direita_esquerda(*raiz);
        
        else if((*raiz)->FB == 2)
            if((*raiz)->esq->FB >= 0)
                (*raiz) = rodar_direita(*raiz);
            else
                (*raiz) = rodar_esquerda_direita(*raiz);
    }

    return *raiz;
}

bool avl_remover(AVL *T, int chave){
    if(T != NULL)
        return avl_remover_no(&(T->raiz), chave) != NULL;
    return false;
}

ITEM *avl_busca_no(NO *raiz, int chave){
    if(raiz == NULL)
        return NULL;
        
    if(item_get_chave(raiz->item) > chave)
        return avl_busca_no(raiz->esq, chave);
    else if(item_get_chave(raiz->item) < chave)
        return avl_busca_no(raiz->dir, chave);
    else
        return raiz->item;
}

ITEM *avl_busca(AVL *T, int chave){
    if(T != NULL)
        return avl_busca_no(T->raiz, chave);
    return false;
}

bool avl_vazia(AVL *T){
    if(T != NULL)
        return T->raiz == NULL;

    return true;
}