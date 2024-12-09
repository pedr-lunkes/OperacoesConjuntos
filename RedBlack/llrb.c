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
        novo->cor = true; // true - Vermelho / false - preto
        novo->item = item;
    }

    return novo;
}

bool Vermelho(NO *raiz){
    if(raiz != NULL)
        return raiz->cor;

    return false;   
}

void inverte(NO *raiz){
    raiz->cor = !raiz->cor;
    if(raiz->esq)
        raiz->esq->cor = !raiz->esq->cor;
    if(raiz->dir)
        raiz->dir->cor = !raiz->dir->cor;

    return;
}

NO *rodar_direita(NO *a){
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;
    b->cor = a->cor;
    a->cor = true;

    return b;
}

NO *rodar_esquerda(NO *a){
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;
    b->cor = a->cor;
    a->cor = true;

    return b;
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
    if(Vermelho(raiz->esq->esq) && Vermelho(raiz->esq))
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
            T->raiz->cor = false;
            return true;
        }
    }
    
    return false;
}

NO *troca_max_esq(NO *raiz, NO *ant, NO *troca){
    if(troca->dir != NULL)
        troca_max_esq(raiz, troca, troca->dir);

    if(ant == raiz)
        ant->esq = troca->esq;
    else
        ant->dir = troca->esq;

    item_apagar(&raiz->item);
    raiz->item = troca->item;
    free(troca);
    troca = NULL;
}

NO *move_red_esq(NO *raiz) {
    inverte(raiz);
    
    if (Vermelho(raiz->dir->esq)) {
        raiz->dir = rodar_direita(raiz->dir);
        raiz = rodar_esquerda(raiz);
        inverte(raiz);
    }

    return raiz;
}

NO *move_red_dir(NO *raiz) {
    inverte(raiz);

    if (Vermelho(raiz->esq->esq)) {
        raiz = rodar_direita(raiz);
        inverte(raiz);
    }

    return raiz;
}

NO *llrb_remover_no(NO **raiz, int chave){
    if (*raiz == NULL)
        return NULL;

    if(item_get_chave((*raiz)->item) > chave){
        if (!Vermelho((*raiz)->esq) && !Vermelho((*raiz)->esq ? (*raiz)->esq->esq : NULL)) 
            *raiz = move_red_esq(*raiz);

        (*raiz)->esq = llrb_remover_no(&(*raiz)->esq, chave);
    } else{
        if(Vermelho((*raiz)->esq))
            *raiz = rodar_direita(*raiz);

        if(item_get_chave((*raiz)->item) == chave && (*raiz)->dir == NULL){
            NO *p = *raiz;
            *raiz = (*raiz)->esq;
            item_apagar(&(p->item));
            free(p);
            p = NULL;
            return *raiz;
        }

        if(!Vermelho((*raiz)->dir) && !Vermelho((*raiz)->dir ? (*raiz)->dir->esq : NULL))
            *raiz = move_red_dir(*raiz);

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
        else
            (*raiz)->dir = llrb_remover_no(&(*raiz)->dir, chave);
    }

    if(*raiz != NULL){
        if(Vermelho((*raiz)->dir) && !Vermelho((*raiz)->esq))
            *raiz = rodar_esquerda(*raiz);
        if(Vermelho((*raiz)->esq) && Vermelho((*raiz)->esq->esq))
            *raiz = rodar_direita(*raiz);
        if(Vermelho((*raiz)->esq) && Vermelho((*raiz)->dir))
            inverte(*raiz);
    }

    return *raiz;
}

// NO *llrb_remover_no(NO **raiz, int chave) {
//     if (*raiz == NULL)
//         return NULL;

//     if(chave == item_get_chave((*raiz)->item)) {
//         NO *p = *raiz;
//         if((*raiz)->esq == NULL || (*raiz)->dir == NULL){
//             if((*raiz)->esq == NULL)
//                 *raiz = (*raiz)->dir;
//             else
//                 *raiz = (*raiz)->esq;
            
//             item_apagar(&(p->item));
//             free(p);
//             p = NULL;
//         } else
//             troca_max_esq(*raiz, *raiz, (*raiz)->esq);
//     }

//     else if (item_get_chave((*raiz)->item) > chave){
//         if (!Vermelho((*raiz)->esq) && !Vermelho((*raiz)->esq ? (*raiz)->esq->esq : NULL)) 
//             *raiz = move_red_esq(*raiz);

//         (*raiz)->esq = llrb_remover_no(&(*raiz)->esq, chave);

//     } else{
//         if(Vermelho((*raiz)->esq))
//             raiz = rodar_esquerda(raiz);

//         if (!Vermelho((*raiz)->dir) && !Vermelho((*raiz)->dir ? (*raiz)->dir->esq : NULL))
//             *raiz = move_red_dir(*raiz);
        
//         (*raiz)->dir = llrb_remover_no(&(*raiz)->dir, chave);
//     }

//     if(*raiz != NULL){
//         if(Vermelho((*raiz)->dir) && !Vermelho((*raiz)->esq))
//             *raiz = rodar_esquerda(*raiz);
//         if(Vermelho((*raiz)->esq->esq) && Vermelho((*raiz)->esq))
//             *raiz = rodar_direita(*raiz);
//         if(Vermelho((*raiz)->esq) && Vermelho((*raiz)->dir))
//             inverte(*raiz);
//     }

//     return *raiz;
// }

bool llrb_remover(LLRB *T, int chave){
    if(T != NULL){
        NO *res = llrb_remover_no(&T->raiz, chave);
        if(res != NULL){
            T->raiz->cor = false;
            return true;
        }
    }

    return false;
}