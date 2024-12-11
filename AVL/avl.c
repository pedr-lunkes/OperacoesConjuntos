#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

typedef struct no_{
    struct no_ *esq;
    struct no_ *dir;
    struct no_ *pai;
    int dado;
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
        printf("%d ", raiz->dado);
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

NO *avl_cria_no(int dado){
    NO *no = (NO *) malloc(sizeof(NO));

    if(no != NULL){
        no->esq = NULL;
        no->dir = NULL;
        no->dado = dado;
        no->FB = 0;
        no->pai = NULL;
        no->altura = 0;
    }

    return no;
}

NO *avl_rodar_direita(NO *a){
    NO *b = a->esq;

    if(b->dir){
        b->dir->pai = a;
    }

    a->esq = b->dir;
    b->dir = a;

    b->pai = a->pai;
    a->pai = b;

    // a->FB = 0;
    // b->FB = 0;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;

    return b;
}

NO *avl_rodar_esquerda(NO *a){
    NO *b = a->dir;

    if(b->esq){
        b->esq->pai = a;
    }

    a->dir = b->esq;
    b->esq = a;

    b->pai = a->pai;
    a->pai = b;

    // a->FB = 0;
    // b->FB = 0;

    a->altura = max(avl_altura_no(a->esq), avl_altura_no(a->dir)) + 1;
    b->altura = max(avl_altura_no(b->esq), avl_altura_no(b->dir)) + 1;

    return b;
}

NO *avl_rodar_esquerda_direita(NO *a){
    a->esq = avl_rodar_esquerda(a->esq);
    return avl_rodar_direita(a);
}

NO *avl_rodar_direita_esquerda(NO *a){
    a->dir = avl_rodar_direita(a->dir);
    return avl_rodar_esquerda(a);
}

NO *avl_inserir_no(NO *raiz, int dado){
    if(raiz == NULL){
        NO *novo = avl_cria_no(dado);
        return novo;
    }

    else if(raiz->dado > dado){
        raiz->esq = avl_inserir_no(raiz->esq, dado);
        raiz->esq->pai = raiz;
    }
    else if(raiz->dado < dado){
        raiz->dir = avl_inserir_no(raiz->dir, dado);
        raiz->dir->pai = raiz;
    }
    else
        return raiz;

    raiz->altura = max(avl_altura_no(raiz->esq), avl_altura_no(raiz->dir)) + 1;
    raiz->FB = avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);

    if(raiz->FB == -2)
        if(raiz->dir->FB <= 0)
            raiz = avl_rodar_esquerda(raiz);
        else
            raiz = avl_rodar_direita_esquerda(raiz);
    else if(raiz->FB == 2)
        if(raiz->esq->FB >= 0)
            raiz = avl_rodar_direita(raiz);
        else
            raiz = avl_rodar_esquerda_direita(raiz);

    return raiz;
}

bool avl_inserir(AVL *T, int dado){
    if(T != NULL){
        NO *aux = avl_inserir_no(T->raiz, dado);
        if(aux != NULL){
            T->raiz = aux;
            return true;
        }
    }

    return false;
}

NO *avl_min(NO *raiz){
    NO *aux = raiz;
    NO *tmp = raiz->esq;

    while(tmp != NULL){
        aux = tmp;
        tmp = tmp->esq;
    }

    return aux;
}

NO *avl_remove_min(NO *raiz){
    if(raiz->esq == NULL){
        NO *aux = raiz->dir;
        free(raiz);
        raiz = NULL;
        return aux;
    }

    raiz->esq = avl_remove_min(raiz->esq);

    if(raiz->FB == -2)
        if(raiz->dir->FB <= 0)
            raiz = avl_rodar_esquerda(raiz);
        else
            raiz = avl_rodar_direita_esquerda(raiz);
    else if(raiz->FB == 2)
        if(raiz->esq->FB >= 0)
            raiz = avl_rodar_direita(raiz);
        else
            raiz = avl_rodar_esquerda_direita(raiz);

    return raiz;
}


NO *avl_remover_no(NO **raiz, int chave){
    if(*raiz == NULL)
        return NULL;

    if((*raiz)->dado == chave){
        if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
            NO *p = *raiz;
            if((*raiz)->esq == NULL)
                *raiz = (*raiz)->dir;
            else
                *raiz = (*raiz)->esq;
            
            free(p);
            p = NULL;
        } else{
            NO *p = avl_min((*raiz)->dir);
            (*raiz)->dado = p->dado;
            (*raiz)->dir = avl_remove_min((*raiz)->dir);
        }
    }

    else if((*raiz)->dado > chave)
        (*raiz)->esq = avl_remover_no(&(*raiz)->esq, chave);
    else
        (*raiz)->dir = avl_remover_no(&(*raiz)->dir, chave);
    
    if(*raiz != NULL){
        (*raiz)->FB = avl_altura_no((*raiz)->esq) - avl_altura_no((*raiz)->dir);
        (*raiz)->altura = max(avl_altura_no((*raiz)->esq), avl_altura_no((*raiz)->dir)) + 1;

        if((*raiz)->FB == -2)
            if((*raiz)->dir->FB <= 0)
                (*raiz) = avl_rodar_esquerda(*raiz);
            else
                (*raiz) = avl_rodar_direita_esquerda(*raiz);
        
        else if((*raiz)->FB == 2)
            if((*raiz)->esq->FB >= 0)
                (*raiz) = avl_rodar_direita(*raiz);
            else
                (*raiz) = avl_rodar_esquerda_direita(*raiz);
    }

    return *raiz;
}

bool avl_remover(AVL *T, int chave){
    if(T != NULL)
        return avl_remover_no(&(T->raiz), chave) != NULL;
    return false;
}

NO *avl_busca_no(NO *raiz, int chave){
    if(raiz == NULL)
        return NULL;
        
    if(raiz->dado > chave)
        return avl_busca_no(raiz->esq, chave);
    else if(raiz->dado < chave)
        return avl_busca_no(raiz->dir, chave);
    else
        return raiz;
}

NO *avl_pertence(AVL *T, int chave){
    if(T != NULL)
        return avl_busca_no(T->raiz, chave);
    return false;
}

bool avl_vazia(AVL *T){
    if(T != NULL)
        return T->raiz == NULL;

    return true;
}


NO *avl_menor_no(NO* raiz){
    if(raiz == NULL) return NULL;

    while(raiz->esq != NULL){
        raiz = raiz->esq;
    }

    return raiz;
}

NO* avl_prox_no(NO* raiz){
    if(raiz == NULL) return NULL;
    if(raiz->dir != NULL) return avl_menor_no(raiz->dir);

    NO* pai = raiz->pai;

    while(pai != NULL && raiz == pai->dir){
        raiz = pai;
        pai = pai->pai;
    }

    return pai;
}

AVL *avl_uniao(AVL* rb1, AVL* rb2){
    NO* atual1 = avl_menor_no(rb1->raiz);
    NO* atual2 = avl_menor_no(rb2->raiz);

    AVL* arvore3 = avl_criar();

    while(atual1 != NULL && atual2 != NULL){
        if(atual1->dado == atual2->dado){
            avl_inserir(arvore3, atual1->dado);
            atual1 = avl_prox_no(atual1);
            atual2 = avl_prox_no(atual2);
        }else if(atual1->dado < atual2->dado){
            avl_inserir(arvore3, atual1->dado);
            atual1 = avl_prox_no(atual1);
        }else{
            avl_inserir(arvore3, atual2->dado);
            atual2 = avl_prox_no(atual2);
        }
    }

    while(atual1 != NULL){
        avl_inserir(arvore3, atual1->dado);
        atual1 = avl_prox_no(atual1);
    }

    while(atual2 != NULL){
        avl_inserir(arvore3, atual2->dado);
        atual2 = avl_prox_no(atual2);
    }
    
    return arvore3;
}

AVL *avl_interseccao(AVL* rb1, AVL* rb2){
    NO* atual1 = avl_menor_no(rb1->raiz);
    NO* atual2 = avl_menor_no(rb2->raiz);

    AVL* arvore3 = avl_criar();

    while(atual1 != NULL && atual2 != NULL){
        if(atual1->dado == atual2->dado){
            avl_inserir(arvore3, atual1->dado);
            atual1 = avl_prox_no(atual1);
            atual2 = avl_prox_no(atual2);
        }else if(atual1->dado < atual2->dado){
            atual1 = avl_prox_no(atual1);
        }else{
            atual2 = avl_prox_no(atual2);
        }
    }

    return arvore3;
}

