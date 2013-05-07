/* Projeto 1
 * Switch de testes de algoritmos
 *
 * MC458
 * ra: 121286
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 1000000

int comparissons;
int swaps;

/* Compare
 * Função de comparação de elementos do vetor
 */
int Compare(int a, int b) {
	comparissons++;

	return a < b;
}

/* Swap
 * Função de troca de elementos do vetor
 */
void Swap(int *a, int *b) {
	swaps++;

	int aux = *a;
	*a = *b;
	*b = aux;
}

/* Start
 * Inicia um teste
 */
int Start() {
	comparissons = 0;
	swaps = 0;
}

/* Test
 * Função genérica de testes
 */
void Test(int vector [], int size, void (*Sorter) (int [], int)) {
	int i;
	Start();
	Sorter(vector, size);
	for (i = 0; i < size; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n");
	printf("Comparações: %d\n", comparissons);
	printf("Trocas     : %d\n", swaps);
}

/* Insertion
 * Testes do insertion sort
 */
void Insertion(int vector [], int size) {
	int i,j;

	for (i = 1; i < size; i++) {
		j = i;
		while (
			(j != 0) &&
			Compare(vector[j], vector[j - 1])
		) {
			Swap(&vector[j], &vector[j - 1]);
			j--;
		}
	}
}

/* Selection
 * Testes do insertion sort
 */
void Selection(int vector [], int size) {
	int i, j, min;

	for (i = 0; i < (size - 1); i++) {
		min = i;
		for (j = (i + 1); j < size; j++) {
			if (Compare(vector[j], vector[min])) {
				min = j;
			}
		}
		if (i != min) {
			Swap(&vector[i], &vector[min]);
		}
	}
}

/* Bubble
 * Testes do insertion sort
 */
void Bubble(int vector [], int size) {
	int i,j,k;

	k = size - 1;
	for (i = 1; i < size; i++) {
		j = 1;
		while (j <= k) {
			if (Compare(vector[j+1], vector[j])) {
				Swap(&vector[j+1], &vector[j]);
			}
			j++;
		}
	}
}

/* Merge
 * Testes do insertion sort
 */
void Merge(int vector [], int size) {
	int mid;

	if (size > 1) {
		/* divisão */
		mid = size / 2;
		Merge(vector, mid);
		Merge(vector + mid, size - mid);

		/* conquista */
		int i,j,k;
		int *tmp;

		tmp = malloc(sizeof(int) * size);
		if (tmp == NULL) {
			exit(1);
		}

		i = 0;
		j = mid;
		k = 0;

		while(
			i < mid &&
			j < size
		) {
			if (Compare(vector[i], vector[j])) {
				tmp[k] = vector[i++];
			} else {
				tmp[k] = vector[j++];
			}
			k++;
		}

		if (i == mid) {
			while(j < size) {
				tmp[k++] = vector[j++];
			}
		} else {
			while(i < mid) {
				tmp[k++] = vector[i++];
			}
		}

		for (i = 0; i < size; i++) {
			vector[i] = tmp[i];
		}
		free(tmp);
	}
}

/* Quick
 * pivot randômico
 * Testes do insertion sort
 */
void Quick_rand(int vector [], int size) {

}

/* Quick
 * pivot fixo(1º elemento)
 * Testes do insertion sort
 */
void Quick_fixed(int vector [], int size) {
	int pivot, i, j;

	i = 0;
	j = size;
	pivot = vector[0];

	do {
		while (Compare(vector[i], pivot)) i++;
		while (Compare(pivot, vector[j])) j--;

		if (i <= j) {
			Swap(&vector[i], &vector[j]);
			i++;
			j--;
		}
	} while (j > i);

	if (j > 0) Quick_fixed(vector, j);
	if (i < size) Quick_fixed(vector + i, size - i);
}

/* Quick
 * pivot fixo(pivot mediana)
 * Testes do insertion sort
 */
void Quick_mean(int vector [], int size) {
	int pivot, i, j;

	i = 0;
	j = size;
	pivot = vector[size / 2];

	do {
		while (Compare(vector[i], pivot)) i++;
		while (Compare(pivot, vector[j])) j--;

		if (i <= j) {
			Swap(&vector[i], &vector[j]);
			i++;
			j--;
		}
	} while (j > i);

	if (j > 0) Quick_mean(vector, j);
	if (i < size) Quick_mean(vector + i, size - i);
}

int main (void) {
	int vector [] 			  = {1,9,4,6,8,32,324,767,4534,3,12321,2,6},
		vector_merge []       = {1,9,4,6,8,32,324,767,4534,3,12321,2,6},
		vector_selection []   = {1,9,4,6,8,32,324,767,4534,3,12321,2,6},
		vector_insertion []   = {1,9,4,6,8,32,324,767,4534,3,12321,2,6},
		vector_bubble []      = {1,9,4,6,8,32,324,767,4534,3,12321,2,6},
		vector_quick_fixed [] = {1,9,4,6,8,32,324,767,4534,3,12321,2,6},
		vector_quick_mean []  = {1,9,4,6,8,32,324,767,4534,3,12321,2,6};

	int i;

	printf("Original:\n");
	for (i = 0; i < 13; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n\n");

	printf("Insertion:\n");
	Test(vector_insertion,13, &Insertion);

	printf("\n");

	printf("Selection:\n");
	Test(vector_selection,13, &Selection);

	printf("\n");

	printf("Bubble:\n");
	Test(vector_bubble,13, &Bubble);

	printf("\n");

	printf("Merge:\n");
	Test(vector_merge,13, &Merge);

	printf("\n");

	printf("Quick primeiro elemento:\n");
	Test(vector_quick_fixed,13, &Quick_fixed);

	printf("\n");

	printf("Quick elemento central:\n");
	Test(vector_quick_mean,13, &Quick_mean);

	return 0;
}