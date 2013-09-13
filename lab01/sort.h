#ifndef MAX_LENGHT
    #define MAX_LENGHT 1000
#endif

int * Bubble (int vector [MAX_LENGHT], int size);
int * Insertion (int vector [MAX_LENGHT], int size);
int * Merge (int vector [MAX_LENGHT], int size);
int * Quick (int vector [MAX_LENGHT], int size);
int * Heap (int vector [MAX_LENGHT], int size);

int * BubblePrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int));
int * InsertionPrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int));
int * MergePrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int));
int * QuickPrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int));
int * HeapPrivate (int vector [MAX_LENGHT], int size, int (*Comparator) (int, int));
