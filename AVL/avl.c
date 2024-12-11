#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

/* A função lista possui os seguintes campos:
 * esq - Filho esquerdo do nó na árvore.
 * dir - Filho direito do nó na árvore.
 * pai - Pai do nó na árvore.
 * dado - dado correspondente ao nó.
 * FB - Fator de balanceamento usado para realizar as rotações na AVL
 * altura - Altura do nó na árvore.
 */
typedef struct no_{
    struct no_ *esq;
    struct no_ *dir;
    struct no_ *pai;
    int dado;
    int FB;
    int altura;
} NO;

// A estrutura AVL é simples e possui somente um nó para acessar sua raiz.
typedef struct avl_{
    NO *raiz;
} AVL;

// Cria uma árvore AVL alocando memória para a estrutura de dados.
AVL *avl_criar(void){
    AVL *T = (AVL *) malloc(sizeof(AVL));

    if(T != NULL)
        T->raiz = NULL;

    return T;
}

// Apaga recursivamente os nós da árvore percorrendo as sub-árvores esquerda e direita.
void avl_apagar_no(NO **raiz){
    if(*raiz != NULL){
        avl_apagar_no(&(*raiz)->esq);
        avl_apagar_no(&(*raiz)->dir);
        free(*raiz);
        *raiz = NULL;
    }

    return;
}

// Recebe o endereço da AVL e chama a função apagar_no para depois apagar a árvore em si.
void avl_apagar(AVL **T){
    if(*T != NULL){
        avl_apagar_no(&(*T)->raiz);
        free(*T);
        *T = NULL;
    }

    return;
}

// Fornece altura de um nó de forma que o raiz->altura não seja acessado de um nó NULL.
int avl_altura_no(NO *raiz){
    if(raiz != NULL)
        return raiz->altura;

    return -1;
}

// Fornece a altura da árvore retornando a altura da raiz da árvore.
int avl_altura(AVL *T){
    if(T != NULL)
        return avl_altura_no(T->raiz);

    return ERRO;
}

// Imprime o conteúdo da árvore em pré-ordem percorrendo recursivamente as sub-árvores esquerda e direita do nó.
void avl_imprimir_no(NO *raiz){
    // Pre-Ordem
    if(raiz != NULL){
        printf("%d ", raiz->dado);
        avl_imprimir_no(raiz->esq);
        avl_imprimir_no(raiz->dir);
    }

    return;
}

// Função de interface para o usuário imprimir o conteúdo da árvore usando a função auxiliar imprimir_no.
void avl_imprimir(AVL *T){
    if(T != NULL)
        avl_imprimir_no(T->raiz);
    return;
}

// Função utilizada para alocar memória para um nó e inicializar os seus campos.
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

// Utiliza a lógica de rotação direita em uma AVL.
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

// Utiliza a lógica de rotação esquerda em uma AVL.
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

// Utiliza a lógica de rotação esquerda-direita em uma AVL chamando as funções de rotação esquerda e direita.
NO *avl_rodar_esquerda_direita(NO *a){
    a->esq = avl_rodar_esquerda(a->esq);
    return avl_rodar_direita(a);
}

// Utiliza a lógica de rotação direita-esquerda em uma AVL chamando as funções de rotação direita e esquerda.
NO *avl_rodar_direita_esquerda(NO *a){
    a->dir = avl_rodar_direita(a->dir);
    return avl_rodar_esquerda(a);
}

// Insere em um AVL fazendo a busca usando a lógica de uma ABB de forma recursiva e faz o rebalanceamento na volta da recursão.
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

// Função interface do usuário para inserir um dado na AVL, retorna o booleano indicando se foi bem-sucedido.
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

// Usa a lógica de busca para encontrar o menor elemento de uma sub-árvore para a troca no caso de remoção de nó com duas sub-árvores.
NO *avl_min(NO *raiz){
    NO *aux = raiz;
    NO *tmp = raiz->esq;

    while(tmp != NULL){
        aux = tmp;
        tmp = tmp->esq;
    }

    return aux;
}

// Remove o menor elemento de uma sub-árvore para a troca no caso de remoção de nó com duas sub-árvores, faz o rebalanceamento na volta da recursão.
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

// Função que faz a busca na árvore a faz a remoção do nó de chave fornecida.
// Trata os casos de remoção da AVL manipulando os ponteiros de nó, reduz os casos de um e dois sub-árvores ao mesmo e
// usa o min e remove_min para casos de duas sub-árvores, rebalanceia a árvore na volta da recursão.
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

// Função de interface para o usuário remover um nó da árvore dada uma chave fornecida, retorna se a operação foi bem-sucedida.
bool avl_remover(AVL *T, int chave){
    if(T != NULL)
        return avl_remover_no(&(T->raiz), chave) != NULL;
    return false;
}

// Busca um nó na árvore dada uma chave utilizando a lógica de busca em uma ABB e de maneira recursiva.
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

// Função de interface para que o usuário possa realizar a busca em uma AVL fornecendo uma chave, retorna o nó em questão.
NO *avl_pertence(AVL *T, int chave){
    if(T != NULL)
        return avl_busca_no(T->raiz, chave);
    return false;
}


// Função que verifica se a raiz da AVL possui algum conteúdo, implicando que ela está vazia.
bool avl_vazia(AVL *T){
    if(T != NULL)
        return T->raiz == NULL;

    return true;
}

// Função que retorna o menor nó de uma sub-árvore utilizada para as operações de conjunto.
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

