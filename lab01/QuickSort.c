/*
 * Implements quick sort
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
int QuickComparator (int, int, int []);
void QuickPrivate (int [], int, int, int (*) (int, int, int []));
int * QuickSort (int [], int);
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
            QuickSort(vector, n);
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
int QuickComparator (int a, int b, int v []) {
    comparisons++;
    return v[a] < v[b];
}

/*
 * Executes quick sort in one vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} start First position in the vector to execute the quick sort
 * param {int} end Last position in the vector to execute the quick sort
 * param {int (*) (int, int, int [])} Comparator Function that compares to elements in the vector
 */
void QuickPrivate (int vector [], int start, int end, int (*Comparator) (int, int, int [])) {
    int temp, i, j;

    i = start;
    j = end;

    /* Separets the vector elements by the pivot */
    while (i < j) {
        while (QuickComparator(i, (start + end) / 2, vector)) i++;
        while (QuickComparator((start + end) / 2, j, vector)) j--;
        if (i <= j) {
            temp = vector[i];
            vector[i] = vector[j];
            vector[j] = temp;
            i++;
            j--;
        }
    }

    /* Applies the Quick sort for each sector */
    if (j > start) QuickPrivate(vector, start, j, Comparator);
    if (i < end) QuickPrivate(vector, i, end, Comparator);
}

/*
 * Executes quick sort and returns in a new vector
 *
 * param {int *} vector Vector to be sorted
 * param {int} size Size of the vector to be sorted
 * returns {int} Sorted vector
 */
int * QuickSort (int vector [], int size) {
    int * current;
    int i;

    /* Creates a new copy of the vector to sort */
    current = (int *) malloc(size * sizeof(int));
    for (i = 0; i < size; i ++) {
        current[i] = vector[i];
    }

    /* Sort the copy */
    QuickPrivate(current, 0, size - 1, &QuickComparator);
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
