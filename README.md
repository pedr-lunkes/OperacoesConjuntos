# Operações sobre conjuntos (Sets)
## Trabalho 2 - Algoritmos e Estruturas de Dados 1

**Autores**:
- **Pedro Henrique de Sousa Prestes** - 15507819
- **Pedro Lunkes Villela** - 15484287

## Introdução

O projeto proposto consiste em implementar um TAD set, em C, que permite a escolha da estrutura de dados base em tempo de execução, durante a inicialização do conjunto. O conjunto deveria oferecer as seguintes operações:
- **Operações básicas**: criar, inserir, remover e excluir;
- **Operações específica**: pertence, união e intersecção.

Para a nossa implementação, foram escolhidas a AVL e a Lista Sequencial Ordenada. 

Para rodar os códigos, basta utilizar o arquivo Makefile:
```
make
make run
make clean
```


## AVL
Uma Árvore AVL é uma árvore binária de busca que mantém seu equilíbrio estrutural por meio de rotações. Desssa forma suas operações se tornam mais eficientes, por misturar aspectos de uma estrutura sequêncial com busca binária.

### Operações Básicas
#### *Criar*
Essa operação tem como objetivo criar um ponteiro para a estrutura (que será retornado) e inicializar a estrutura. A operação de criar a árvore binária tem complexidade constante de *O(3)*, já que realiza apenas duas operações, e tem uma comparação.
#### *Inserir*
Essa operação visa adicionar novos elementos na estrutura, o que consiste da procura da posição de inserção e do rebalancemanento da árvore, realizado por meio de rotações de nós para a esquerda ou direita. A operação de inserir na AVL pode ser modelada pela função de recorrência *T(n) = T(n/2) + C*, sendo *C* a constante referênte as rotações de rebalancemanto. Utilizando a técnica de Árvore de recorrência, levando em conta que a altura máxima de uma ALV é 1,44log(n), é possível determinar uma complexidade de *O(1,44log(n))* para o algoritmo.
#### *Remover*
Nessa operação, elementos já presentes na árvore são excluidos. Para isso, é necessário procurar o elemento na estrutura e rebalancear a árvore. Por essa razão, a operação pode ser modelada pela função de recorrência *T(n) = T(n/2) + C*, sendo *C* a constante referênte as rotações de rebalancemanto. Utilizando a técnica de Árvore de recorrência, levando em conta que a altura máxima de uma ALV é 1,44log(n), é possível determinar uma complexidade de *O(1,44log(n))* para o algoritmo.
#### *Excluir*
Nessa operação, todos os elementos da árvore são excluidos, e a memória utilizada na árvore é liberada. Para isso, é necessário realizar *n* operações, referêntes a percorrer todos os nós e utilizar a função free() neles. Além disso, ainda é necessário excluir a estrutura de dados. Assim, a complexidade total é *O(n+1)*, que é equivalente a *O(n)*, na análise assintótica.

### Operações Específicas
#### *Pertence*
A operação pertence equivale a buscar um elemento na estrutura de dados. A função de busca pode ser modelada por T(n) = T(n/2) + C, sendo C a constante relacionada às verificações realizadas na função. Por meio do Teorema Mestre, é possível encontrar a complexidade de *O(log(n))* para o algoritmo.
#### *União*
A operação de união percorre as árvores em ordem de forma iterativa e compara os elementos, de forma a evitar inserções duplas. Como o algoritmo percorre todos os nós de ambas as árvores, ele possui uma complexidade de *O(1,44(n + m)log(n + m))*, onde *n* e *m* são os números de nós das árvores, já que realiza *n + m* visitas e inserções, que como demostrado anteriormente possui complexidade *O(1,44log(n))*.
Essa operação requer a utilização de ponteiros pai, na struct nó. Apesar do maior gasto de memória, esse método é mais rápido do que uma busca e inserção, por exemplo, que teria complexidade *O(1,44(n + m)log²(n + m))*.
#### *Intersecção*
A operação de união percorre as árvores em ordem de forma iterativa e compara os elementos, de forma a inserir apenas os que estão presentes nas duas. Como o algoritmo percorre todos os nós de ambas as árvores, ele possui uma complexidade de *O(1,44(n + m)log(n + m))*, onde *n* e *m* são os números de nós das árvores, já que realiza *n + m* visitas e inserções, que como demostrado anteriormente possui complexidade *O(1,44log(n))*.
Essa operação requer a utilização de ponteiros pai, na struct nó. Apesar do maior gasto de memória, esse método é mais rápido do que uma busca e inserção, por exemplo, que teria complexidade *O(1,44(n + m)log²(n + m))*.

## Lista Sequencial Ordenada
Uma lista sequencial é uma estrutura de dados usada para armazenar um conjunto de elementos em uma sequência linear. Ela foi implementada com memória dinâmica, com a utilização de uma constante MAX, de valor 50. Caso a árvore ultrapasse esse tamanho máximo, mais 10 blocos de memória são alocados (constante REALLOC), com a função realloc(). A ordenação da lista foi mantida pelas inserções e exclusões.

### Operações Básicas
#### *Criar*
Essa operação tem como objetivo criar um ponteiro para a estrutura (que será retornado) e inicializar a estrutura. A operação de criar a lista sequencial tem complexidade constante de *O(5)*, já que realiza apenas três operações, e tem duas comparações.
#### *Inserir*
Essa operação visa adicionar novos elementos na estrutura, o que consiste da procura da posição de inserção e da movimentação dos elementos fora da ordenação . A busca utilizada é a binária, que possui complexidade *O(log(n))*; já o conserto do vetor terá complexidade *O(n)*, pois, no pior caso, tem que mover todos os elementos do vetor. A operação de inserir na lista sequencial ordenada será, dessa forma, *O(log(n) + n)*, que é equivalente a *O(n)*.
#### *Remover*
Nessa operação, é realizada a exclusão de elementos da lista, o que consiste da procura do elemento a ser removido e da movimentação dos elementos fora da ordenação . A busca utilizada é a binária, que possui complexidade *O(log(n))*; já o conserto do vetor terá complexidade *O(n)*, pois, no pior caso, tem que mover todos os elementos do vetor. De forma similar a inserção, a operação de remoção na lista sequencial ordenada será, dessa forma, *O(log(n) + n)*, que é equivalente a *O(n)*.
#### *Excluir*
Por conta do caráter sequêncial dessa implementação de lista, a exclusão consiste apenas da liberação da memória alocada para o vetor e para o ponteiro da estrutura. Dessa forma, esse algoritmo tem complexidade *O(4)*, pois possui tres operações, e uma comparação.

### Operações Específicas
#### *Pertence*
Como a lista é ordenada, a operação de pertencimento consiste de uma busca binária, que tem complexidade *O(log(n))*.
#### *União*
Na operação de união, os dois vetores são percorridos de forma iterativa, e seus elementos são comparados a fim de evitar inserções duplas, para depois serem inseridos. Percorrer os vetores acarreta em complexidade *O(n + m)*, onde *n* e *m* são os números de elementos dos vetores. Diferentemente das árvores, a inserção nesse novo vetor será *O(1)*, porque os elementos já são adicionados respeitando a ordenação. Logo, a complexidade total é *O(n + m)*.
#### *Intersecção*
Na operação de união, os dois vetores são percorridos de forma iterativa, e seus elementos são comparados, de forma a inserir apenas os elementos presentes nos dois vetores, para depois serem inseridos. Percorrer os vetores acarreta em complexidade *O(n + m)*, onde *n* e *m* são os números de elementos dos vetores. Diferentemente das árvores, a inserção nesse novo vetor será *O(1)*, porque os elementos já são adicionados respeitando a ordenação. Logo, a complexidade total é *O(n + m)*.
    

## Conclusão
As estruturas escolhidas foram selecionadas para modelar um conjunto por conta das suas baixas complexidades, quanto tratamos de operações específicas para os SETs. Primeiramente, a AVL, por ser muito eficiente em busca, é muito vantajosa na implementação dos conjuntos, já que todas suas operações específicas estão relacionadas as busca. Além disso, as operações básicas da estrutura são, simultanêamente, muito eficientes, em memória, por ser encadeada, e tempo, por usar busca binária. Concomitantemente, a lista sequencial, apesar de mais lenta nas operações básicas, é ainda mais eficiente nas operações específicas, além de possuir uma implementação muito mais simples. Por esses motivos, essas estruturas de dados se mostraram as melhores para o problema apresentado.

## Comentários
Além da AVL, as árvores Rubro-Negras também seriam muito eficiêntes na modelagem de um conjunto, por motivos similares aos da AVL. Porém, elas tendem a ser um pouco menos eficiêntes, o que não compensa sua implementação mais simples.
Foi criado um gerador de casos teste, que pode ser utilizado com os scripts bash dentro da pasta CASOS_TESTE. Para rodar eles, basta torná-los executáveis com o comando:

```
chmod +x geraCaso.sh
chmod +x rodaCaso.sh
```

Depois, basta informar quantos casos serão criados/testados
```
./geraCaso.sh 50  // exemplo de utilização
```
