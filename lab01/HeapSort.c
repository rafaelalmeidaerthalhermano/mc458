/*
 * Implements heap sort
 *
 * Rafael Almeida Erthal Hermano
 * ra: 121286
 *
 * MC458 - Projeto e análise de algoritmos
 * turma: B
 */
#include <stdio.h>
#include <stdlib.h>

int comparisons;
int HeapComparator (int, int, int []);
void HeapPrivate (int [], int, int (*) (int, int, int []));
int * HeapSort (int [], int);
int * readVector (int);
void printVector (int *, int);

int main (void) {
    int n;
    int * vector;
    int i;

    while (scanf("%d", &n) != EOF) {
        vector = readVector(n);

        comparisons = 0;
        for (i = 0; i < 100; i++) {
            HeapSort(vector, n);
        }
        printf("(%d, %d) ", n, comparisons/1000);
    }

    return 0;
}

/*
 * Compare to elements of the vector
 *
 * param {int} a First element position to be compared
 * param {int} a Second element position to be compared
 * param {int *} v Vector with the elements
 * returns {int} The comparisson result
 */
int HeapComparator (int a, int b, int v []) {
    comparisons++;
    return v[a] < v[b];
}

/*
 * Executes heap sort in one vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * param {int (*) (int, int, int [])} Comparator Function that compares to elements in the vector
 */
void HeapPrivate (int vector [], int size, int (*Comparator) (int, int, int [])) {
    int i, child, parent, temp;

    /* Build the heap in the vector */
    for (i = 1; i < size; i++) {
        child = i;
        /* Push up the child */
        while (child > 0) {
            parent = (child - 1) / 2;
            if (HeapComparator(parent, child, vector)) {
                temp = vector[parent];
                vector[parent] = vector[child];
                vector[child] = temp;
            }
            child = parent;
        }
    }

    /* Gets the vector elements */
    for (i = size - 1; i > 0; i--) {
        parent = 0;

        temp = vector[i];
        vector[i] = vector[parent];
        vector[parent] = temp;

        /* Push down the parent */
        while (parent * 2 + 1 <= i - 1) {
            if (parent * 2 + 2 <= i - 1 && vector[parent * 2 + 1] < vector[parent * 2 + 2]) {
                child = parent * 2 + 2;
            } else {
                child = parent * 2 + 1;
            }
            if (HeapComparator(parent, child, vector)) {
                temp = vector[parent];
                vector[parent] = vector[child];
                vector[child] = temp;
            }
            parent = child;
        }
    }
}

/*
 * Executes heap sort and returns in a new vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * returns {int} Sorted vector
 */
int * HeapSort (int vector [], int size) {
    int * current;
    int i;

    /* Creates a new copy of the vector to sort */
    current = (int *) malloc(size * sizeof(int));
    for (i = 0; i < size; i ++) {
        current[i] = vector[i];
    }

    /* Sort the copy */
    HeapPrivate(current, size, &HeapComparator);
    return current;
}

/*
 * Reads a vector from the input
 *
 * param {int} size Size of the vector to be read
 * returns {int *} Read vector
 */
int * readVector (int size) {
    int * result;
    int i;

    result = (int *) malloc(sizeof(int) * size);

    for (i = 0; i < size; i++) {
        scanf(",%d", &result[i]);
    }

    return result;
}

/*
 * Prints a vector in the outpu
 *
 * param {int *} vector Vector to be printed
 * param {int} size Size of the vector to be printed
 */
void printVector (int * vector, int size) {
    int i;

    for (i = 0; i < size; i++) {
        printf("%d", vector[i]);
        if (i < size - 1) {
            printf(",");
        }
    }

    printf("\n");
}
