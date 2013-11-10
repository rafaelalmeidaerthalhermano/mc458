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
struct OperationType TWIDDLE;
struct OperationType KILL;

struct Operation {
    struct OperationType * type;
    struct Operation * previous;
    int i, j;
    char character [3];
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
 * Prints the decision stack for the edit distance
 *
 * param {struct Operation *} operation The top of the stack
 */
void PrintOperations (struct Operation * operation) {
    if (operation == NULL || operation->type == NULL) { return; }
    PrintOperations(operation->previous);
    printf("%d %d %s %s\n", operation->i, operation->j, operation->type->name, operation->character);
}

/*
 * Creates a new operation object
 *
 * param {int} i Line of the operation in the table
 * param {int} j Column of the operation in the table
 *
 * returns {struct Operation *} The operation object
 */
struct Operation * NewOperation (int i, int j) {
    struct Operation * operation;

    operation               = (struct Operation *) malloc(sizeof(struct Operation));
    operation->i            = i;
    operation->j            = j;
    operation->cost         = INFINITY;
    operation->character[0] = '\0';
    operation->character[1] = '\0';
    operation->character[2] = '\0';
    operation->type         = NULL;
    operation->previous     = NULL;

    return operation;
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
        operations[i][j]               = NewOperation(i,j);
        operations[i][j]->cost         = i * INSERT.cost;
        operations[i][j]->type         = &INSERT;
        operations[i][j]->character[0] = correctString[i-1];
        operations[i][j]->previous     = operations[i-1][j];
    }
    /* CONVERTING TO NULL STRING */
    i = 0;
    for (j = 1; j < columns; j++) {
        operations[i][j]               = NewOperation(i,j);
        operations[i][j]->cost         = j * REMOVE.cost;
        operations[i][j]->type         = &REMOVE;
        operations[i][j]->character[0] = '_';
        operations[i][j]->previous     = operations[i][j-1];
    }
    for (i = 1; i < lines; i++) {
        for (j = 1; j < columns; j++) {
            operations[i][j] = NewOperation(i,j);
            /* COPY OPERATION */
            cost = operations[i-1][j-1]->cost + COPY.cost;
            if (cost < operations[i][j]->cost && correctString[i-1] == wrongString[j-1]) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &COPY;
                operations[i][j]->character[0] = correctString[i-1];
                operations[i][j]->character[1] = '\0';
                operations[i][j]->character[2] = '\0';
                operations[i][j]->previous     = operations[i-1][j-1];
            }
            /* REPLACE OPERATION */
            cost = operations[i-1][j-1]->cost + REPLACE.cost;
            if (cost < operations[i][j]->cost) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &REPLACE;
                operations[i][j]->character[0] = correctString[i-1];
                operations[i][j]->character[1] = '\0';
                operations[i][j]->character[2] = '\0';
                operations[i][j]->previous     = operations[i-1][j-1];
            }
            /* REMOVE OPERATION */
            cost = operations[i][j-1]->cost + REMOVE.cost;
            if (cost < operations[i][j]->cost) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &REMOVE;
                operations[i][j]->character[0] = '_';
                operations[i][j]->character[1] = '\0';
                operations[i][j]->character[2] = '\0';
                operations[i][j]->previous     = operations[i][j-1];
            }
            /* INSERT OPERATION */
            cost = operations[i-1][j]->cost + INSERT.cost;
            if (cost < operations[i][j]->cost) {
                operations[i][j]->cost         = cost;
                operations[i][j]->type         = &INSERT;
                operations[i][j]->character[0] = correctString[i-1];
                operations[i][j]->character[1] = '\0';
                operations[i][j]->character[2] = '\0';
                operations[i][j]->previous     = operations[i-1][j];
            }
            /* TWIDDLE OPERATION */
            if (i > 1 && j > 1) {
                cost = operations[i-2][j-2]->cost + TWIDDLE.cost;
                if (cost < operations[i][j]->cost && correctString[i-1] == wrongString[j-2] && correctString[i-2] == wrongString[j-1]) {
                    operations[i][j]->cost         = cost;
                    operations[i][j]->type         = &TWIDDLE;
                    operations[i][j]->character[0] = correctString[i-2];
                    operations[i][j]->character[1] = correctString[i-1];
                    operations[i][j]->character[2] = '\0';
                    operations[i][j]->previous     = operations[i-2][j-2];
                }
            }
        }
    }
    /* KILL OPERATION */
    i = lines - 1;
    for (j = 0; j < columns; j++) {
        cost = operations[i][j]->cost + KILL.cost;
        if (cost < operations[lines - 1][columns - 1]->cost) {
            operations[lines - 1][columns - 1]->cost         = cost;
            operations[lines - 1][columns - 1]->type         = &KILL;
            operations[lines - 1][columns - 1]->character[0] = '*';
            operations[lines - 1][columns - 1]->character[1] = '\0';
            operations[lines - 1][columns - 1]->character[2] = '\0';
            operations[lines - 1][columns - 1]->previous     = operations[i][j];
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

    COPY.name = "Copy";
    scanf("%d", &COPY.cost);

    REPLACE.name = "Replace";
    scanf("%d", &REPLACE.cost);

    REMOVE.name = "Delete";
    scanf("%d", &REMOVE.cost);

    INSERT.name = "Insert";
    scanf("%d", &INSERT.cost);

    TWIDDLE.name = "Twiddle";
    scanf("%d", &TWIDDLE.cost);

    KILL.name = "Kill";
    scanf("%d", &KILL.cost);

    operations = Distance(string1, string2);

    printf("%d\n", operations->cost);
    PrintOperations(operations);

    return 0;
}
