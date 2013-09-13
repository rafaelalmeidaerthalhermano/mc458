#include <string.h>
#include "sort.h"

int * current;

int BubbleComparator (int a, int b) {
    return current[a] > current[b];
}

void BubbleSwap (int a, int b) {
    int temp;

    temp = current[a];
    current[a] = current[b];
    current[b] = temp;
}

int * BubblePrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int)) {
    int i, j, k;

    k = size - 1;
    for (i = 0; i < size; i++) {
        for (j = 0; j < k; j++) {
            if (Comparator(j, j + 1)) {
                BubbleSwap(j, j + 1);
            }
        }
        k--;
    }

    return vector;
}

int * Bubble (int vector [MAX_LENGHT], int size) {
    int result [MAX_LENGHT];

    if (size > MAX_LENGHT) { return 0; }
    memcpy(result, vector, size * sizeof(int));
    current = result;

    return BubblePrivate(result, size, &BubbleComparator);
}
