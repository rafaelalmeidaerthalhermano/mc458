/*
 * Implements insertion sort
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
int InsertionComparator (int, int, int []);
void InsertionPrivate (int [], int, int (*) (int, int, int []));
int * InsertionSort (int [], int);
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
            InsertionSort(vector, n);
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
int InsertionComparator (int a, int b, int v []) {
    comparisons++;
    return v[a] < v[b];
}

/*
 * Executes insertion sort in one vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * param {int (*) (int, int, int [])} Comparator Function that compares to elements in the vector
 */
void InsertionPrivate (int vector [], int size, int (*Comparator) (int, int, int [])) {
    int i, j, temp;

    for(i = 1; i < size; i++){
        j = i;
        while((j >= 0) && Comparator(j, j - 1, vector)) {
            temp = vector[j - 1];
            vector[j - 1] = vector[j];
            vector[j] = temp;
            j--;
        }
    }
}

/*
 * Executes insertion sort and returns in a new vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * returns {int} Sorted vector
 */
int * InsertionSort (int vector [], int size) {
    int * current;
    int i;

    /* Creates a new copy of the vector to sort */
    current = (int *) malloc(size * sizeof(int));
    for (i = 0; i < size; i ++) {
        current[i] = vector[i];
    }

    /* Sort the copy */
    InsertionPrivate(current, size, &InsertionComparator);
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
