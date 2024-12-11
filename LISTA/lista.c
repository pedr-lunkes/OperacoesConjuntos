#include "lista.h"

#include <stdio.h>
#include <stdlib.h>

/* A função lista possui os seguintes campos:
 * lista - Elementos inteiros dentro da lista.
 * tamanho - Número de elementos na lista.
 * max - Número máximo de elementos que é possível inserir na lista.
 */
typedef struct lista_{
    int *lista;
    int tamanho;
    int max;
} LISTA;

// Cria uma lista alocando memória para a estrutura de dados.
LISTA *lista_criar(){
    LISTA *l = (LISTA *) malloc(sizeof(LISTA));
    if(l != NULL){
        if((l->lista = (int *) malloc(sizeof(int) * MAX)) == NULL){
            free(l); 
            return NULL;
        }

        l->tamanho = 0;
        l->max = MAX;
    }

    return l;
}

// Recebe o endereço da lista e apaga os itens e a estrutura em si.
void lista_apagar(LISTA **lista){
    if(*lista != NULL){     
        free((*lista)->lista);   
        free(*lista);
        *lista = NULL;
    }

    return;
}

// Utiliza o campo tamanho e compara com o campo max da lista para saber se ela está completamente cheia.
bool lista_cheia(LISTA *lista){
    if(lista == NULL) return false;
    if(lista->max == lista->tamanho) return true;
    return false;
}

// Utiliza o campo tamanho da lista e verifica se ele é igual a zero, indicando que não há elementos na lista.
bool lista_vazia(LISTA *lista){
    if(lista != NULL)
        return lista->tamanho == 0;

    return true;
}

// Utiliza busca binária para achar um valor na lista (pertence) ou encontrar a posição de inserção (inserir).
int lista_busca(LISTA *lista, int val){
    int inf = 0;
    int sup = lista->tamanho;
    int meio;

    while (inf < sup) {
        meio = (inf + sup) / 2;

        if (lista->lista[meio] == val) {
            return meio;
        }

        else if (lista->lista[meio] > val) {
            sup = meio;
        }

        else {
            inf = meio + 1;
        }
    }

    if(inf == 0) inf = -1;
    if(inf == lista->tamanho) inf = -2;
    return inf;
}

// Função que percorre a lista em busca do elemento e faz os deslocamentos necessários
bool lista_inserir_posicao(LISTA *lista, int pos, int item){
    if(pos == -1) pos = 0;
    if(pos == -2) pos = lista->tamanho;

    for(int i = lista->tamanho; i > pos; i--){
        lista->lista[i] = lista->lista[i-1];
    }

    lista->lista[pos] = item;
    lista->tamanho++;
    return true;
}

// Realoca o tamanho da lista caso chegue ao limite de memória previamente alocado.
void lista_realoc(LISTA *lista){
    if(lista_cheia(lista)){
        if((lista->lista = (int *) realloc(lista->lista, sizeof(int) * (lista->max + REALOC))) == NULL){
            free(lista); 
            return;
        }

        lista->max += REALOC;
    }
}

// Função de interface para o usuário inserir na lista, chama a busca para verificar a posição e insere na posição com a inserir_posição.
bool lista_inserir(LISTA *lista, int item){
    lista_realoc(lista);
    int x = lista_busca(lista, item);

    return(lista_inserir_posicao(lista, x, item));
}

// Retorna o campo tamanho da lista que representa os números de itens inseridos.
int lista_tamanho(LISTA *lista){
    if(lista != NULL)
        return lista->tamanho;
    
    return 0;
}

// Percorre a lista utilizando o printf para printar o conteúdo da lista no terminal.
void lista_imprimir(LISTA *lista){
    if(lista != NULL){
        for(int i = 0; i < lista->tamanho; i++){
            printf("%d ", lista->lista[i]);
        }
    }

    return;
}

// Função auxiliar que remove o item da lista e faz o shift dos demais para não ter buracos.
bool lista_remover_posicao(LISTA *lista, int pos){
    if(pos >= 0){
        for(int i = pos; i < lista->tamanho - 1; i++){
            lista->lista[i] = lista->lista[i+1];
        }

        lista->tamanho--;
        return true;
    }

    return false;
}

// Função de interface para o usuário requisitar a remoção de um item da lista.
bool lista_remover(LISTA *lista, int item){
    int x = lista_busca(lista, item);
    return(lista_remover_posicao(lista, x));
}

// Cria uma terceira lista e percorre as duas listas passadas para a função de forma intercalada produzindo uma nova lista com todos os elementos de ambas.
LISTA* lista_uniao(LISTA* A, LISTA* B){
    int indA = 0;
    int indB = 0;

    LISTA* C = lista_criar();
    int indC = 0;

    while(indA < A->tamanho && indB < B->tamanho){
        if(indC >= C->tamanho) lista_realoc(C);

        if(A->lista[indA] == B->lista[indB]){
            C->lista[indC] = A->lista[indA];
            indA++;
            indB++;
        }else if(A->lista[indA] < B->lista[indB]){
            C->lista[indC] = A->lista[indA];
            indA++;
        }else{
            C->lista[indC] = B->lista[indB];
            indB++;
        }

        indC++;
        C->tamanho++;
    }

    while(indA < A->tamanho){
        if(indC >= C->tamanho) lista_realoc(C);

        C->lista[indC] = A->lista[indA];
        indA++;
        indC++;

        C->tamanho++;
    }

    while(indB < B->tamanho){
        if(indC >= C->tamanho) lista_realoc(C);

        C->lista[indC] = B->lista[indB];
        indB++;
        indC++;

        C->tamanho++;
    }

    return C;
}

// Cria uma terceira lista e percorre as duas listas passadas para a função de forma intercalada produzindo uma nova lista com os elementos em comum de ambas.
LISTA* lista_interseccao(LISTA* A, LISTA* B){
    int indA = 0;
    int indB = 0;

    LISTA* C = lista_criar(A->tamanho + B->tamanho);
    int indC = 0;

    while(indA < A->tamanho && indB < B->tamanho){
        if(indC >= C->tamanho) lista_realoc(C);

        if(A->lista[indA] == B->lista[indB]){
            C->lista[indC] = A->lista[indA];
            indA++;
            indB++;

            indC++;
            C->tamanho++;
        }else if(A->lista[indA] < B->lista[indB]){
            indA++;
        }else{
            indB++;
        }
    }

    return C;
}

// Função de interface para o usuário que busca o item na lista com a função busca.
bool lista_pertence(LISTA *A, int item){
    int x = lista_busca(A, item);

    if(x > 0) return true;
    return false;
}
