#include <string.h>
#include "sort.h"

int * current;

int QuickComparator (int a, int b) {
    return current[a] > current[b];
}

int * QuickPrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int)) {
    return vector;
}

int * Quick (int vector [MAX_LENGHT], int size) {
    int result [MAX_LENGHT];

    if (size > MAX_LENGHT) { return 0; }
    memcpy(result, vector, size * sizeof(int));
    current = result;

    return QuickPrivate(result, size, &QuickComparator);
}
