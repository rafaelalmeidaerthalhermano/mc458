/*
 * Implements edit distance
 *
 * Rafael Almeida Erthal Hermano
 * ra: 121286
 *
 * MC458 - Projeto e análise de algoritmos
 * turma: B
 */
#include <stdio.h>
#include <stdlib.h>
#define INFINITY 99999999

struct OperationType {
    int cost;
    char * name;
};

struct OperationType INSERT;
struct OperationType REMOVE;
struct OperationType REPLACE;
struct OperationType COPY;

struct Operation {
    struct OperationType * type;
    struct Operation * previous;
    char firstString, secondString;
    int cost;
};

/*
 * Returns the size of a string
 *
 * param {int *} string Pointer to the string
 *
 * returns {int} The string size
 */
int stringSize (char * string) {
    int size;

    size = 0;
    while (string[size] != '\0') {
        size++;
    }

    return size;
}

/*
 * Creates a new operation object
 *
 * returns {struct Operation *} The operation object
 */
struct Operation * NewOperation () {
    struct Operation * operation;

    operation               = malloc(sizeof(struct Operation));
    operation->cost         = INFINITY;
    operation->type         = NULL;
    operation->previous     = NULL;

    return operation;
}

/*
 * Prints the operations stack for the edit distance
 *
 * param {struct Operation *} operation The top of the stack
 */
void printOperationTypes (struct Operation * operation) {
    if (operation == NULL || operation->type == NULL) { return; }
    printOperationTypes(operation->previous);
    printf("%c", operation->type->name[0]);
}

/*
 * Prints the first string after the edit
 *
 * param {struct Operation *} operation The top of the stack
 */
void printFirstString (struct Operation * operation) {
    if (operation == NULL || operation->type == NULL) { return; }
    printFirstString(operation->previous);
    printf("%c", operation->firstString);
}

/*
 * Prints the second string after the edit
 *
 * param {struct Operation *} operation The top of the stack
 */
void printSecondString (struct Operation * operation) {
    if (operation == NULL || operation->type == NULL) { return; }
    printSecondString(operation->previous);
    printf("%c", operation->secondString);
}

/*
 * Returns the operations to transform the correctString into wrongString
 *
 * param {char *} correctString String source
 * param {char *} wrongString String destiny
 *
 * returns {struct Operation *} The top of the operations stack
 */
struct Operation * Distance (char * wrongString, char * correctString) {
    int lines, columns;
    int i, j;
    int cost;
    struct Operation *** operations;

    lines = stringSize(correctString) + 1;
    columns = stringSize(wrongString) + 1;

    operations = (struct Operation ***) malloc(sizeof(struct Operation **) * lines);

    for (i = 0; i < lines; i++) {
        operations[i] = (struct Operation **) malloc(sizeof(struct Operation) * columns);
    }

    operations[0][0]       = NewOperation(0,0);
    operations[0][0]->cost = 0;

    /* CREATING FROM NULL STRING */
    j = 0;
    for (i = 1; i < lines; i++) {
        operations[i][j]               = NewOperation();
        operations[i][j]->cost         = i * INSERT.cost;
        operations[i][j]->type         = &INSERT;
        operations[i][j]->previous     = operations[i-1][j];
        operations[i][j]->firstString  = ' ';
        operations[i][j]->secondString = correctString[i-1];
    }
    /* CONVERTING TO NULL STRING */
    i = 0;
    for (j = 1; j < columns; j++) {
        operations[i][j]               = NewOperation();
        operations[i][j]->cost         = j * REMOVE.cost;
        operations[i][j]->type         = &REMOVE;
        operations[i][j]->previous     = operations[i][j-1];
        operations[i][j]->firstString  = wrongString[j-1];
        operations[i][j]->secondString = ' ';
    }
    for (i = 1; i < lines; i++) {
        for (j = 1; j < columns; j++) {
            operations[i][j] = NewOperation();
            /* COPY OPERATION */
            cost = operations[i-1][j-1]->cost + COPY.cost;
            if (cost < operations[i][j]->cost && correctString[i-1] == wrongString[j-1]) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &COPY;
                operations[i][j]->previous     = operations[i-1][j-1];
                operations[i][j]->firstString  = wrongString[j-1];
                operations[i][j]->secondString = correctString[i-1];
            }
            /* REPLACE OPERATION */
            cost = operations[i-1][j-1]->cost + REPLACE.cost;
            if (cost < operations[i][j]->cost) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &REPLACE;
                operations[i][j]->previous     = operations[i-1][j-1];
                operations[i][j]->firstString  = wrongString[j-1];
                operations[i][j]->secondString = correctString[i-1];
            }
            /* REMOVE OPERATION */
            cost = operations[i][j-1]->cost + REMOVE.cost;
            if (cost < operations[i][j]->cost) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &REMOVE;
                operations[i][j]->previous     = operations[i][j-1];
                operations[i][j]->firstString  = wrongString[j-1];
                operations[i][j]->secondString = ' ';
            }
            /* INSERT OPERATION */
            cost = operations[i-1][j]->cost + INSERT.cost;
            if (cost < operations[i][j]->cost) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &INSERT;
                operations[i][j]->previous     = operations[i-1][j];
                operations[i][j]->firstString  = ' ';
                operations[i][j]->secondString = correctString[i-1];
            }
        }
    }

    return operations[lines-1][columns-1];
}

int main (void) {
    struct Operation * operations;
    char *string1, *string2;
    int size1, size2;

    scanf("%d", &size1);
    scanf("%d", &size2);

    string1 = (char *) malloc(sizeof(char) * size1);
    string2 = (char *) malloc(sizeof(char) * size2);

    scanf("%s", string1);
    scanf("%s", string2);

    COPY.name    = "+";
    COPY.cost    = -1;

    REPLACE.name = "-";
    REPLACE.cost = 1;

    REMOVE.name  = "*";
    REMOVE.cost  = 2;

    INSERT.name  = "*";
    INSERT.cost  = 2;

    operations = Distance(string1, string2);

    printf("%d\n", operations->cost);
    printFirstString(operations);
    printf("\n");
    printSecondString(operations);
    printf("\n");
    printOperationTypes(operations);
    printf("\n");

    return 0;
}
