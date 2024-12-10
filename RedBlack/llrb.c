#include <stdio.h>
#include <stdlib.h>
#include "llrb.h"

typedef struct no_{
    struct no_ *esq;
    struct no_ *dir;
    bool cor;
    ITEM *item;
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
        llrb_apagar_no(&(*raiz)->esq);
        llrb_apagar_no(&(*raiz)->dir);
        item_apagar(&(*raiz)->item);
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
        printf("%d", item_get_chave(raiz->item));

        if(raiz->cor)
            printf("V ");
        else
            printf("P ");

        llrb_printar_no(raiz->esq);
        llrb_printar_no(raiz->dir);
    }

    return;
}

void llrb_printar(LLRB *T){
    if(T != NULL)
        llrb_printar_no(T->raiz);
    
    return;
}

NO *llrb_cria_no(ITEM *item){
    NO *novo = (NO *) malloc(sizeof(NO));
    if(novo != NULL){
        novo->esq = NULL;
        novo->dir = NULL;
        novo->cor = RED;
        novo->item = item;
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

NO *rodar_direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = RED;

    return b;
}

NO *rodar_esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = RED;

    return b;
}

NO *balanceia(NO *raiz){
    if(raiz != NULL){
        if(Vermelho(raiz->dir) && !Vermelho(raiz->esq))
            raiz = rodar_esquerda(raiz);
        if((raiz->esq != NULL && Vermelho(raiz->dir)) && Vermelho(raiz->esq->esq) )
            raiz = rodar_direita(raiz);
        if(Vermelho(raiz->esq) && Vermelho(raiz->dir))
            inverte(raiz);
    }

    return raiz;
}

NO *llrb_inserir_no(NO *raiz, NO *novo){
    if(raiz == NULL)
        return novo;
    else if(item_get_chave(raiz->item) > item_get_chave(novo->item))
        raiz->esq = llrb_inserir_no(raiz->esq, novo);
    else if(item_get_chave(raiz->item) < item_get_chave(novo->item))
        raiz->dir = llrb_inserir_no(raiz->dir, novo);
    else
        return NULL;

    if(Vermelho(raiz->dir) && !Vermelho(raiz->esq))
        raiz = rodar_esquerda(raiz);
    if(Vermelho(raiz->esq) && Vermelho(raiz->esq->esq))
        raiz = rodar_direita(raiz);
    if(Vermelho(raiz->esq) && Vermelho(raiz->dir))
        inverte(raiz);

    return raiz;
}

bool llrb_inserir(LLRB *T, ITEM *item){
    if(T != NULL){
        NO *novo = llrb_cria_no(item);
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
        raiz->dir = rodar_direita(raiz->dir);
        raiz = rodar_esquerda(raiz);
        inverte(raiz);
    }

    return raiz;
}

NO *move_red_dir(NO *raiz) {
    inverte(raiz);
    if(Vermelho(raiz->esq->esq)){
        raiz = rodar_direita(raiz);
        inverte(raiz);
    }
    return raiz;
}

NO *min(NO *raiz){
    NO *aux = raiz;
    NO *tmp = raiz->esq;

    while(tmp != NULL){
        aux = tmp;
        tmp = tmp->esq;
    }

    return aux;
}

NO *removeMin(NO *raiz){
    if(raiz->esq == NULL){
        item_apagar(&raiz->item);
        free(raiz);
        raiz = NULL;
        return NULL;
    }
    
    if(!Vermelho(raiz->esq) && !Vermelho(raiz->esq->esq))
        raiz = move_red_esq(raiz);

    raiz->esq = removeMin(raiz->esq);
    return balanceia(raiz);
}

NO *llrb_remover_no(NO *raiz, int chave) {
    if(raiz == NULL)
        return NULL;
    
    if(chave < item_get_chave(raiz->item)){
        if(!Vermelho(raiz->esq) && (raiz->esq != NULL && !Vermelho(raiz->esq->esq)))
            raiz = move_red_esq(raiz);

        raiz->esq = llrb_remover_no(raiz->esq, chave);
    }
    else{
        if(Vermelho(raiz->esq))
            raiz = rodar_direita(raiz);
        
        if(item_get_chave(raiz->item) == chave && raiz->dir == NULL){
            item_apagar(&raiz->item);
            free(raiz);
            raiz = NULL;
            return NULL;
        }

        if(!Vermelho(raiz->dir) && (raiz->dir != NULL && !Vermelho(raiz->dir->esq)))
            raiz = move_red_dir(raiz);

        if(item_get_chave(raiz->item) == chave){
            NO *p = min(raiz->dir);
            raiz->item = p->item;
            raiz->dir = removeMin(raiz->dir);
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