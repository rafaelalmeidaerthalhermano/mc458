#include <string.h>
#include "sort.h"

int * current;

int MergeComparator (int a, int b) {
    return current[a] > current[b];
}

int * MergePrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int)) {
    return vector;
}

int * Merge (int vector [MAX_LENGHT], int size) {
    int result [MAX_LENGHT];

    if (size > MAX_LENGHT) { return 0; }
    memcpy(result, vector, size * sizeof(int));
    current = result;

    return MergePrivate(result, size, &MergeComparator);
}
