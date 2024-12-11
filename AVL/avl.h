#ifndef _AVL_H
    #define _AVL_H

    #define max(a,b) ((a > b) ? a : b)
    #define ERRO -32000

    #include <stdbool.h>

    typedef struct avl_ AVL;
    typedef struct no_ NO;

    /// @brief A função "avl_criar" aloca a memória para a AVL.
    /// @return AVL *, o ponteiro para a AVL criada.
    AVL *avl_criar(void);

    /// @brief A função "avl_apagar" desaloca a memória utilizada para a criação da estrutura.
    /// @param T 
    void avl_apagar(AVL **T);

    /// @brief A função "avl_altura" retorna a altura da AVL.
    /// @param T 
    /// @return 
    int avl_altura(AVL *T);

    /// @brief A função "avl_imprimir imprime o conteúdo da AVL.
    /// @param T 
    void avl_imprimir(AVL *T);

    /// @brief A função "avl_inserir" insere um nó na AVL e balanceia a árvore automaticamente.
    /// @param T 
    /// @param dado 
    /// @return Booleano que retorna se a operação foi bem-sucedida ou não.
    bool avl_inserir(AVL *T, int dado);

    /// @brief A função "avl_remover" remove um nó na AVL e balanceia a árvore automaticamente.
    /// @param T 
    /// @param chave 
    /// @return Booleano que retorna se a operação foi bem-sucedida ou não.
    bool avl_remover(AVL *T, int chave);
    
    /// @brief A função "avl_pertence" verifica se um nó dado uma chave está presente na AVL.
    /// @param T 
    /// @param chave 
    /// @return NO *, retorna o nó em questão
    NO *avl_pertence(AVL *T, int chave);

    /// @brief A função "avl_vazia" verifica se a árvore está vazia ou não.
    /// @param T 
    /// @return Booleano, retorna true caso esteja vazia e false caso contrário.
    bool avl_vazia(AVL *T);

    /// @brief Unifica duas AVLs diferentes e retorna uma única.
    /// @param rb1 
    /// @param rb2 
    /// @return Ponteiro para uma lista resultante da união.
    AVL *avl_uniao(AVL* rb1, AVL* rb2);

    /// @brief Faz a intersecção de duas AVLs diferentes e retorna uma única.
    /// @param rb1 
    /// @param rb2 
    /// @return Ponteiro para uma AVL resultante da intersecção.
    AVL *avl_interseccao(AVL* rb1, AVL* rb2);
#endif