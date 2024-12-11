
#ifndef LISTA_H
	#define LISTA_H

	#define MAX 50
	#define REALOC 20

	#include <stdbool.h>

	typedef struct lista_ LISTA;

	/// @brief A função "lista_criar" aloca a memória para a lista.
	/// @return LISTA *, o ponteiro para a lista criada
	LISTA *lista_criar();

    /// @brief A função "lista_apagar" desaloca a memória utilizada para a criação da estrutura.
    /// @param lista 
    void lista_apagar(LISTA **lista);

    /// @brief A função "lista_vazia" verifica se a lista está vazia.
    /// @param lista 
    /// @return Booleano: True se estiver vazia e False se não estiver.
    bool lista_vazia(LISTA *lista);

	/// @brief A função "lista_inserir" insere um item à lista.
	/// @param lista 
	/// @param item 
	/// @return Booleano: True se for bem-sucedido e False se não.
	bool lista_inserir(LISTA *lista, int item);

	/// @brief A função "lista_remover" remove um item da lista.
	/// @param lista 
	/// @param item 
	/// @return Booleano: True se for bem-sucedido e False se não.
	bool lista_remover(LISTA *lista, int item);

	/// @brief A função "lista_tamanho" retorna o número de itens atualmente na lista.
	/// @param lista 
	/// @return Inteiro que representa o número de itens.
	int lista_tamanho(LISTA *lista);

	/// @brief Imprime o conteúdo da lista no terminal (inteiros).
	/// @param lista 
	void lista_imprimir(LISTA *lista);

	/// @brief Unifica duas listas diferentes e retorna uma única.
	/// @param A 
	/// @param B 
	/// @return Ponteiro para uma lista resultante da união.
	LISTA* lista_uniao(LISTA* A, LISTA* B);

	/// @brief Faz a intersecção de duas listas diferentes e retorna uma única.
	/// @param A 
	/// @param B 
	/// @return Ponteiro para uma lista resultante da intersecção.
	LISTA* lista_interseccao(LISTA* A, LISTA* B);

	/// @brief Verifica se um item pertence à lista.
	/// @param A 
	/// @param item 
	/// @return True se o item fornecido pertence e False se não.
	bool lista_pertence(LISTA *A, int item);

#endif
