all:
	gcc AVL/avl.c LISTA/lista.c SET/set.c main.c -o main

clean:
	rm main CASOS_TESTE/c