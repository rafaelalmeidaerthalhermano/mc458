#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct Decision;

struct Decision * DecisionTree (int, void (*) (int vector [], int size, void * status, int (*Comparator) (int, int, int [], void **)));
void PrintDecisionTree (struct Decision *);

struct Decision{
    int i;
    int j;
    struct Decision * T;
    struct Decision * F;

    int * answers;
    int depth;
    int call;
} Decision;

int Comparator (int i, int j, int v [], void ** decision) {
    int k;
    ((struct Decision *) *decision)->i = i;
    ((struct Decision *) *decision)->j = j;
    ((struct Decision *) *decision)->T = (struct Decision *) malloc(sizeof(struct Decision));
    ((struct Decision *) *decision)->F = (struct Decision *) malloc(sizeof(struct Decision));

    if (fork() == 0) {
        *decision = (void *) ((struct Decision *) *decision)->T;
        return 1;
    } else {
        *decision = (void *) ((struct Decision *) *decision)->F;
        return 0;
    }
}

struct Decision * DecisionTree (int size, void (*Sorter) (int [], int, void *, int (*) (int, int, int [], void **))) {
    struct Decision * decision = (struct Decision *) malloc(sizeof(struct Decision));

    Sorter(malloc(sizeof(int) * 1000), size, &decision, &Comparator);
    return decision;
}

void PrintDecisionTreePrivate (struct Decision * decisionTree, int indent) {
    int i;

    if (decisionTree == NULL) {return;}

    for (i = 0; i < indent; i++) {printf("  ");}
    printf("decision %d %d\n", decisionTree->i, decisionTree->j);
    PrintDecisionTreePrivate(decisionTree->T, indent+1);
    PrintDecisionTreePrivate(decisionTree->F, indent+1);
}

void PrintDecisionTree (struct Decision * decisionTree) {
    PrintDecisionTreePrivate(decisionTree, 0);
}


/*
#include "DecisionTree.h"

struct Decision{
    int i;
    int j;
    struct Decision * T;
    struct Decision * F;

    int * answers;
    int depth;
    int call;
} Decision;

int size;
void (* Sorter) (int vector [], int size, void * status, int (*Comparator) (int, int, int [], void *));
int dummy [1000];

int Comparator (int i, int j, int v [], void * curDecision) {
    int k;
    struct Decision * decision;

    decision = (struct Decision *) curDecision;

    if (decision->call < decision->depth) {
        decision->call++;
        return decision->answers[decision->call - 1];
    } else if (decision->call == decision->depth) {
        decision->i = i;
        decision->j = j;

        decision->T = (struct Decision *) malloc(sizeof(struct Decision));
        decision->T->i = -1;
        decision->T->j = -1;
        decision->T->answers = (int *) malloc(sizeof(int) * (decision->depth + 1));
        decision->T->depth = decision->depth + 1;
        decision->T->call = 0;
        for (k = 0; k < decision->depth; k++) {
            decision->T->answers[k] = decision->answers[k];
        }
        decision->T->answers[decision->depth] = 1;
        Sorter(dummy, size, (void *) decision->T, &Comparator);
        if (decision->T->i == -1) {
            free(decision->T);
            decision->T = NULL;
        }

        decision->F = (struct Decision *) malloc(sizeof(struct Decision));
        decision->F->i = -1;
        decision->F->j = -1;
        decision->F->answers = (int *) malloc(sizeof(int) * (decision->depth + 1));
        decision->F->depth = decision->depth + 1;
        decision->F->call = 0;
        for (k = 0; k < decision->depth; k++) {
            decision->F->answers[k] = decision->answers[k];
        }
        decision->F->answers[decision->depth] = 0;
        Sorter(dummy, size, (void *) decision->F, &Comparator);
        if (decision->F->i == -1) {
            free(decision->F);
            decision->F = NULL;
        }
    }

    decision->call++;
    return 0;
}

struct Decision * DecisionTree (int probSize, void (* probSorter) (int [], int, void *, int (*) (int, int, int [], void *))) {
    struct Decision * decision;

    decision = (struct Decision *) malloc(sizeof(struct Decision));

    size   = probSize;
    Sorter = probSorter;

    decision->answers = NULL;
    decision->depth   = 0;
    decision->call    = 0;

    Sorter(dummy, size, decision, &Comparator);
    return decision;
}

*/
