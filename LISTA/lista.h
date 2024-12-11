
#ifndef LISTA_H
	#define LISTA_H

	#define MAX 50
	#define REALOC 20

	#include <stdbool.h>

	typedef struct lista_ LISTA;

	LISTA *lista_criar();
    void lista_apagar(LISTA **lista);

    bool lista_vazia(LISTA *lista);

	bool lista_inserir(LISTA *lista, int item);
	bool lista_remover(LISTA *lista, int item);

	int lista_tamanho(LISTA *lista);
	void lista_imprimir(LISTA *lista);

	LISTA* lista_uniao(LISTA* A, LISTA* B);
	LISTA* lista_interseccao(LISTA* A, LISTA* B);
	bool lista_pertence(LISTA *A, int item);
#endif
