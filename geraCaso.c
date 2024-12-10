#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX 100
#define MAX_CONJ 8
#define OP 4
#define OP_QUANT 4


int superRand(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void generate_list(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = superRand(1, MAX);
    }
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    if(argc > 2)
        return 1;

    int n = atoi(argv[1]);

    for (int i = 0; i < n; ++i) {
        char filename[50];
        sprintf(filename, "casos_teste/%d.in", i + 1);
        
        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Failed to open file");
            return 1;
        }

        int tamA = superRand(2, MAX_CONJ);
        int tamB = superRand(2, MAX_CONJ);

        fprintf(file, "%d\n", tamA);
        fprintf(file, "%d\n", tamB);


        int *conjA = (int *) malloc(tamA * sizeof(int));
        generate_list(conjA, tamA);

        for (int j = 0; j < tamA; ++j) {
            fprintf(file, "%d ", conjA[j]);
        }
        fprintf(file, "\n");


        int *conjB = (int *) malloc(tamB * sizeof(int));
        generate_list(conjB, tamB);

        for (int j = 0; j < tamB; ++j) {
            fprintf(file, "%d ", conjB[j]);
        }
        fprintf(file, "\n");


        for(int j = 0;j < OP_QUANT;j++){
            fprintf(file, "%d\n", superRand(0, OP));
        }

        fclose(file);
    }
}