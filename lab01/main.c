#include <stdio.h>
#include <stdlib.h>
#include "sort.h"

int * RandomVector () {
    int * result;
    int i;

    result = malloc(sizeof(int) * MAX_LENGHT);
    srand(time(NULL));

    for (i = 0; i < MAX_LENGHT; i++) {
        result[i] = rand() % 100;
    }

    return result;
}

void printVector (int * vector, int size) {
    int i;

    printf("[");

    for (i = 0; i < size; i++) {
        printf("%d", vector[i]);
        if (i < size - 1) {
            printf(", ");
        }
    }

    printf("]\n");
}

int main (void) {
    int * vector = RandomVector();
    int size = 10;

    printf("original vector : ");
    printVector(vector, size);

    printf("bubble sorted   : ");
    printVector(Bubble(vector, size), size);

    printf("insertion sorted: ");
    printVector(Insertion(vector, size), size);

    printf("merge sorted    : ");
    printVector(Merge(vector, size), size);

    printf("quick sorted    : ");
    printVector(Quick(vector, size), size);

    printf("heap sorted     : ");
    printVector(Heap(vector, size), size);

    return 0;
}
