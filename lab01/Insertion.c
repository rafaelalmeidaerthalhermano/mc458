#include <string.h>
#include "sort.h"

int * current;

int InsertionComparator (int a, int b) {
    return current[a] < current[b];
}

void InsertionSwap (int a, int b) {
    int temp;

    temp = current[a];
    current[a] = current[b];
    current[b] = temp;
}

int * InsertionPrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int)) {
    int i;

    for(i = 1; i < size; i++){
        while((i != 0) && Comparator(i, i - 1)) {
            InsertionSwap(i, i - 1);
            i--;
        }
    }

    return vector;
}

int * Insertion (int vector [MAX_LENGHT], int size) {
    int result [MAX_LENGHT];

    if (size > MAX_LENGHT) { return 0; }
    memcpy(result, vector, size * sizeof(int));
    current = result;

    return InsertionPrivate(result, size, &InsertionComparator);
}
