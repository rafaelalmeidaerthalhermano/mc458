#include <string.h>
#include "sort.h"

int * current;

int HeapComparator (int a, int b) {
    return current[a] > current[b];
}

int * HeapPrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int)) {
   int i = size/2, pai, filho, t;

    while (1) {
        if (i > 0) {
            i--;
            t = vector[i];
        } else {
            size--;
            if (size == 0) { return vector; }
            t = vector[size];
            vector[size] = vector[0];
        }

        pai = i;
        filho = i*2;

        while (filho < size) {
            if ((filho + 1 < size) && Comparator(filho + 1, filho)) {
                filho++;
            }
            if (vector[filho] > t) {
                vector[pai] = vector[filho];
                pai = filho;
                filho = pai*2 + 1;
            } else {
                break;
            }
        }
        vector[pai] = t;
    }

    return vector;
}

int * Heap (int vector [MAX_LENGHT], int size) {
    int result [MAX_LENGHT];

    if (size > MAX_LENGHT) { return 0; }
    memcpy(result, vector, size * sizeof(int));
    current = result;

    return HeapPrivate(result, size, &HeapComparator);
}
