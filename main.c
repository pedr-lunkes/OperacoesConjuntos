/*
AUTORIA:
    # Pedro Henrique de Sousa Prestes - 15507819
    # Pedro Lunkes Villela - 15484287
*/


#include "SET/set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
    {
    SET *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo); /*0 -> ED1, 1 -> ED2*/

    A = set_criar(tipo);
    B = set_criar(tipo);

    scanf("%d %d", &n_a, &n_b);

    for(int i=0; i<n_a; i++){
        scanf("%d",&x);
        set_inserir(A, x);
    }

    for(int i=0; i<n_b; i++){
        scanf("%d",&x);
        set_inserir(B, x);
    }

    scanf("%d", &op);

    switch(op){
        case 1: { // Pertence
            int busca;
            scanf("%d", &busca);

            if(set_pertence(A, busca)) printf("Pertence\n");
            else printf("Não pertence");

            break;
        }
        case 2: {  // União
            SET* U = set_uniao(A, B);
            set_imprimir(U);

            set_apagar(&U);
            break;
        }
        case 3: { // Intersecção
            SET* I = set_interseccao(A, B);
            set_imprimir(I);

            set_apagar(&I);
            break;
        }
        case 4: { // Remoção
            int remove;
            scanf("%d", &remove);

            set_remover(A, remove);
            set_imprimir(A);

            break;
            }
    }

    set_apagar(&A);
    set_apagar(&B);

    return 0;
}
