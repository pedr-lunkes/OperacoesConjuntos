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

    /// @brief A função "AVL_apagar" desaloca a memória utilizada para a criação da estrutura.
    /// @param T 
    void avl_apagar(AVL **T);

    /// @brief 
    /// @param T 
    /// @return 
    int avl_altura(AVL *T);

    /// @brief 
    /// @param T 
    void avl_imprimir(AVL *T);

    /// @brief 
    /// @param T 
    /// @param dado 
    /// @return 
    bool avl_inserir(AVL *T, int dado);

    /// @brief 
    /// @param T 
    /// @param chave 
    /// @return 
    bool avl_remover(AVL *T, int chave);
    
    /// @brief 
    /// @param T 
    /// @param chave 
    /// @return 
    NO *avl_pertence(AVL *T, int chave);

    /// @brief 
    /// @param T 
    /// @return 
    bool avl_vazia(AVL *T);

    /// @brief 
    /// @param rb1 
    /// @param rb2 
    /// @return 
    AVL *avl_uniao(AVL* rb1, AVL* rb2);

    /// @brief 
    /// @param rb1 
    /// @param rb2 
    /// @return 
    AVL *avl_interseccao(AVL* rb1, AVL* rb2);
#endif