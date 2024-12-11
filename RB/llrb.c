#include <stdio.h>
#include <stdlib.h>
#include "llrb.h"

typedef struct no_{
    struct no_ *esq;
    struct no_ *dir;
    struct no_ *pai;
    bool cor;
    int dado;
} NO;

typedef struct llrb_{
    NO *raiz;
} LLRB;

LLRB *llrb_criar(void){
    LLRB *T = (LLRB *) malloc(sizeof(LLRB));
    if(T != NULL)
        T->raiz = NULL;
    
    return T;
}

void llrb_apagar_no(NO **raiz){
    if(*raiz != NULL){
        llrb_apagar_no(&((*raiz)->esq));
        llrb_apagar_no(&((*raiz)->dir));
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

void llrb_apagar(LLRB **T){
    if(T != NULL){
        llrb_apagar_no(&(*T)->raiz);
        free(*T);
        *T = NULL;
    }

    return;
}

void llrb_printar_no(NO *raiz){
    if(raiz != NULL){
        printf("%d", raiz->dado);

        if(raiz->cor)
            printf("V ");
        else
            printf("P ");

        llrb_printar_no(raiz->esq);
        llrb_printar_no(raiz->dir);
    }

    return;
}

void llrb_imprimir(LLRB *T){
    if(T != NULL)
        llrb_printar_no(T->raiz);
    
    return;
}

NO *llrb_cria_no(int dado){
    NO *novo = (NO *) malloc(sizeof(NO));
    if(novo != NULL){
        novo->esq = NULL;
        novo->dir = NULL;
        novo->pai = NULL;
        novo->cor = RED;
        novo->dado = dado;
    }

    return novo;
}

bool Vermelho(NO *raiz){
    if(raiz != NULL)
        return raiz->cor;

    return BLACK;   
}

void inverte(NO *raiz){
    if(raiz != NULL){
        raiz->cor = !raiz->cor;
        if(raiz->esq)
            raiz->esq->cor = !raiz->esq->cor;
        if(raiz->dir)
            raiz->dir->cor = !raiz->dir->cor;
    }

    return;
}

NO *llrb_rodar_direita(NO *a){
    NO *b = a->esq;

    if(b->dir){
        b->dir->pai = a;
    }

    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = RED;

    b->pai = a->pai;
    a->pai = b;

    return b;
}

NO *llrb_rodar_esquerda(NO *a){
    NO *b = a->dir;

    if(b->esq){
        b->esq->pai = a;
    }

    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = RED;

    b->pai = a->pai;
    a->pai = b;

    return b;
}

NO *balanceia(NO *raiz){
    if(raiz != NULL){
        if(Vermelho(raiz->dir) && !Vermelho(raiz->esq))
            raiz = llrb_rodar_esquerda(raiz);
        if((raiz->esq != NULL && Vermelho(raiz->dir)) && Vermelho(raiz->esq->esq) )
            raiz = llrb_rodar_direita(raiz);
        if(Vermelho(raiz->esq) && Vermelho(raiz->dir))
            inverte(raiz);
    }

    return raiz;
}

NO *llrb_inserir_no(NO *raiz, NO *novo){
    if(raiz == NULL)
        return novo;
    else if(raiz->dado > novo->dado){
        raiz->esq = llrb_inserir_no(raiz->esq, novo);
        raiz->esq->pai = raiz;
    }
    else if(raiz->dado < novo->dado){
        raiz->dir = llrb_inserir_no(raiz->dir, novo);
        raiz->dir->pai = raiz;
    }
    else
        return NULL;

    if(Vermelho(raiz->dir) && !Vermelho(raiz->esq))
        raiz = llrb_rodar_esquerda(raiz);
    if(Vermelho(raiz->esq) && Vermelho(raiz->esq->esq))
        raiz = llrb_rodar_direita(raiz);
    if(Vermelho(raiz->esq) && Vermelho(raiz->dir))
        inverte(raiz);

    return raiz;
}

bool llrb_inserir(LLRB *T, int dado){
    if(T != NULL){
        NO *novo = llrb_cria_no(dado);
        if(novo != NULL){
            T->raiz = llrb_inserir_no(T->raiz, novo);
            T->raiz->cor = BLACK;
            return true;
        }
    }
    
    return false;
}

NO *move_red_esq(NO *raiz) {
    inverte(raiz);
    if(Vermelho(raiz->dir->esq)){
        raiz->dir = llrb_rodar_direita(raiz->dir);
        raiz = llrb_rodar_esquerda(raiz);
        inverte(raiz);
    }

    return raiz;
}

NO *move_red_dir(NO *raiz) {
    inverte(raiz);
    if(Vermelho(raiz->esq->esq)){
        raiz = llrb_rodar_direita(raiz);
        inverte(raiz);
    }
    return raiz;
}

NO *llrb_min(NO *raiz){
    NO *aux = raiz;
    NO *tmp = raiz->esq;

    while(tmp != NULL){
        aux = tmp;
        tmp = tmp->esq;
    }

    return aux;
}

NO *llrb_remove_min(NO *raiz){
    if(raiz->esq == NULL){
        free(raiz);
        raiz = NULL;
        return NULL;
    }
    
    if(!Vermelho(raiz->esq) && !Vermelho(raiz->esq->esq))
        raiz = move_red_esq(raiz);

    raiz->esq = llrb_remove_min(raiz->esq);
    return balanceia(raiz);
}

NO *llrb_remover_no(NO *raiz, int chave) {
    if(raiz == NULL)
        return NULL;
    
    if(chave < raiz->dado){
        if(!Vermelho(raiz->esq) && (raiz->esq != NULL && !Vermelho(raiz->esq->esq)))
            raiz = move_red_esq(raiz);

        raiz->esq = llrb_remover_no(raiz->esq, chave);
    }
    else{
        if(Vermelho(raiz->esq))
            raiz = llrb_rodar_direita(raiz);
        
        if(raiz->dado == chave && raiz->dir == NULL){
            free(raiz);
            raiz = NULL;
            return NULL;
        }

        if(!Vermelho(raiz->dir) && (raiz->dir != NULL && !Vermelho(raiz->dir->esq)))
            raiz = move_red_dir(raiz);

        if(raiz->dado == chave){
            NO *p = llrb_min(raiz->dir);
            raiz->dado = p->dado;
            raiz->dir = llrb_remove_min(raiz->dir);
        }
        else
            raiz->dir = llrb_remover_no(raiz->dir, chave);
    }
    return balanceia(raiz);
}

bool llrb_remover(LLRB *T, int chave){
    if(T != NULL){
        NO *res = llrb_remover_no(T->raiz, chave);
        if(res != NULL){
            T->raiz = res;
            T->raiz->cor = BLACK;
            return true;
        }
    }

    return false;
}

NO* llrb_busca(NO* raiz, int chave){
    if(raiz == NULL) return NULL;

    if(raiz->dado == chave) return raiz;

    if(chave < raiz->dado) return llrb_busca(raiz->esq, chave);
    if(chave > raiz->dado) return llrb_busca(raiz->dir, chave);

    return NULL;
}

bool llrb_pertence(LLRB *T, int dado){
    if(T == NULL) return false;

    return llrb_busca(T->raiz, dado);
}

bool llrb_vazia(LLRB *T){
    if(T == NULL || T->raiz == NULL) return false;
    return true;
}

NO *llrb_menor_no(NO* raiz){
    if(raiz == NULL) return NULL;

    while(raiz->esq != NULL){
        raiz = raiz->esq;
    }

    return raiz;
}

NO* llrb_prox_no(NO* raiz){
    if(raiz == NULL) return NULL;
    if(raiz->dir != NULL) return llrb_menor_no(raiz->dir);

    NO* pai = raiz->pai;

    while(pai != NULL && raiz == pai->dir){
        raiz = pai;
        pai = pai->pai;
    }

    return pai;
}


LLRB *llrb_uniao(LLRB* rb1, LLRB* rb2){
    NO* atual1 = llrb_menor_no(rb1->raiz);
    NO* atual2 = llrb_menor_no(rb2->raiz);

    LLRB* arvore3 = llrb_criar();

    while(atual1 != NULL && atual2 != NULL){
        if(atual1->dado == atual2->dado){
            llrb_inserir(arvore3, atual1->dado);
            atual1 = llrb_prox_no(atual1);
            atual2 = llrb_prox_no(atual2);
        }else if(atual1->dado < atual2->dado){
            llrb_inserir(arvore3, atual1->dado);
            atual1 = llrb_prox_no(atual1);
        }else{
            llrb_inserir(arvore3, atual2->dado);
            atual2 = llrb_prox_no(atual2);
        }
    }

    while(atual1 != NULL){
        llrb_inserir(arvore3, atual1->dado);
        atual1 = llrb_prox_no(atual1);
    }

    while(atual2 != NULL){
        llrb_inserir(arvore3, atual2->dado);
        atual2 = llrb_prox_no(atual2);
    }

    return arvore3;
}

LLRB *llrb_interseccao(LLRB* rb1, LLRB* rb2){
    NO* atual1 = llrb_menor_no(rb1->raiz);
    NO* atual2 = llrb_menor_no(rb2->raiz);

    LLRB* arvore3 = llrb_criar();

    while(atual1 != NULL && atual2 != NULL){
        if(atual1->dado == atual2->dado){
            llrb_inserir(arvore3, atual1->dado);
            atual1 = llrb_prox_no(atual1);
            atual2 = llrb_prox_no(atual2);
        }else if(atual1->dado < atual2->dado){
            atual1 = llrb_prox_no(atual1);
        }else{
            atual2 = llrb_prox_no(atual2);
        }
    }

    return arvore3;
}
