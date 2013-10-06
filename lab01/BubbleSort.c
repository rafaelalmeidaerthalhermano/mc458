/*
 * Implements bubble sort
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
int BubbleComparator (int, int, int []);
void BubblePrivate (int [], int, int (*) (int, int, int []));
int * BubbleSort (int [], int);
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
            printVector(BubbleSort(vector, n), n);
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
int BubbleComparator (int a, int b, int v []) {
    comparisons++;
    return v[a] > v[b];
}

/*
 * Executes bubble sort in one vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * param {int (*) (int, int, int [])} Comparator Function that compares to elements in the vector
 */
void BubblePrivate (int vector [], int size, int (*Comparator) (int, int, int [])) {
    int temp;
    int swapped;
    int i, j;

    i = size;
    do {
        swapped = 0;
        for (j = 1; j < i; j++) {
            if (Comparator(j - 1, j, vector)) {
                temp = vector[j];
                vector[j] = vector[j - 1];
                vector[j - 1] = temp;
                swapped = 1;
            }
        }
        i--;
    } while (swapped);
}

/*
 * Executes bubble sort and returns in a new vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * returns {int} Sorted vector
 */
int * BubbleSort (int vector [], int size) {
    int * current;
    int i;

    /* Creates a new copy of the vector to sort */
    current = (int *) malloc(size * sizeof(int));
    for (i = 0; i < size; i ++) {
        current[i] = vector[i];
    }

    /* Sort the copy */
    BubblePrivate(current, size, &BubbleComparator);
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
