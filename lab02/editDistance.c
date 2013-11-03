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
#define MAX_SIZE 100

struct Operation {
    int cost;
    char * name;
};

struct Operation INSERT;
struct Operation REMOVE;
struct Operation REPLACE;
struct Operation COPY;
struct Operation TWIDDLE;
struct Operation KILL;

struct Change {
    struct Operation * type;
    struct Change * previous;
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
 * Creates a new change object
 *
 * param {int} i Line of the change in the table
 * param {int} j Column of the change in the table
 *
 * returns {struct Change *} The change object
 */
struct Change * NewChange (int i, int j) {
    struct Change * change;

    change               = malloc(sizeof(struct Change));
    change->i            = i;
    change->j            = j;
    change->cost         = INFINITY;
    change->character[0] = '\0';
    change->character[1] = '\0';
    change->character[2] = '\0';
    change->type         = NULL;
    change->previous     = NULL;

    return change;
}

/*
 * Prints the decision stack for the edit distance
 *
 * param {struct Change *} change The top of the stack
 */
void PrintChanges (struct Change * change) {
    if (change == NULL || change->type == NULL) { return; }
    PrintChanges(change->previous);
    printf("%d %d %s %s\n", change->i, change->j, change->type->name, change->character);
}

/*
 * Prints the decision matrix
 *
 * param {struct Change * [MAX_SIZE][MAX_SIZE]} costs Decision matrix
 * param {int} size1 Size of string1
 * param {int} size2 Size of string2
 */
void PrintMatrix (struct Change * costs [MAX_SIZE][MAX_SIZE], int size1, int size2) {
    int i, j;

    for (i = 0; i < size1; i++) {
        for (j = 0; j < size2; j++) {
            if (i == 0 && j == 0) {
                printf("n %2d      ", costs[i][j]->cost);
            } else {
                printf("%c %2d %c    ", costs[i][j]->type->name[0], costs[i][j]->cost, costs[i][j]->character[0]);
            }
        }
        printf("\n");
    }
}

/*
 * Returns the operations to transform the correctString into wrongString
 *
 * param {char *} correctString String source
 * param {char *} wrongString String destiny
 *
 * returns {struct Change *} The top of the changes stack
 */
struct Change * Distance (char * wrongString, char * correctString) {
    int lines, columns;
    int i, j;
    int cost;
    struct Change * costs [MAX_SIZE][MAX_SIZE];

    lines = stringSize(correctString) + 1;
    columns = stringSize(wrongString) + 1;

    costs[0][0]       = NewChange(0,0);
    costs[0][0]->cost = 0;

    /* CREATING FROM NULL STRING */
    j = 0;
    for (i = 1; i < lines; i++) {
        costs[i][j]               = NewChange(i,j);
        costs[i][j]->cost         = i * INSERT.cost;
        costs[i][j]->type         = &INSERT;
        costs[i][j]->character[0] = correctString[i-1];
        costs[i][j]->previous     = costs[i-1][j];
    }
    /* CONVERTING TO NULL STRING */
    i = 0;
    for (j = 1; j < columns; j++) {
        costs[i][j]               = NewChange(i,j);
        costs[i][j]->cost         = j * REMOVE.cost;
        costs[i][j]->type         = &REMOVE;
        costs[i][j]->character[0] = '_';
        costs[i][j]->previous     = costs[i][j-1];
    }
    for (i = 1; i < lines; i++) {
        for (j = 1; j < columns; j++) {
            costs[i][j] = NewChange(i,j);
            /* COPY OPERATION */
            cost = costs[i-1][j-1]->cost + COPY.cost;
            if (cost < costs[i][j]->cost && correctString[i-1] == wrongString[j-1]) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &COPY;
                costs[i][j]->character[0] = correctString[i-1];
                costs[i][j]->character[1] = '\0';
                costs[i][j]->character[2] = '\0';
                costs[i][j]->previous     = costs[i-1][j-1];
            }
            /* REPLACE OPERATION */
            cost = costs[i-1][j-1]->cost + REPLACE.cost;
            if (cost < costs[i][j]->cost) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &REPLACE;
                costs[i][j]->character[0] = correctString[i-1];
                costs[i][j]->character[1] = '\0';
                costs[i][j]->character[2] = '\0';
                costs[i][j]->previous     = costs[i-1][j-1];
            }
            /* REMOVE OPERATION */
            cost = costs[i][j-1]->cost + REMOVE.cost;
            if (cost < costs[i][j]->cost) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &REMOVE;
                costs[i][j]->character[0] = '_';
                costs[i][j]->character[1] = '\0';
                costs[i][j]->character[2] = '\0';
                costs[i][j]->previous     = costs[i][j-1];
            }
            /* INSERT OPERATION */
            cost = costs[i-1][j]->cost + INSERT.cost;
            if (cost < costs[i][j]->cost) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &INSERT;
                costs[i][j]->character[0] = correctString[i-1];
                costs[i][j]->character[1] = '\0';
                costs[i][j]->character[2] = '\0';
                costs[i][j]->previous     = costs[i-1][j];
            }
            /* TWIDDLE OPERATION */
            if (i > 1 && j > 1) {
                cost = costs[i-2][j-2]->cost + TWIDDLE.cost;
                if (cost < costs[i][j]->cost && correctString[i-1] == wrongString[j-2] && correctString[i-2] == wrongString[j-1]) {
                    costs[i][j]->cost         = cost;
                    costs[i][j]->type         = &TWIDDLE;
                    costs[i][j]->character[0] = correctString[i-2];
                    costs[i][j]->character[1] = correctString[i-1];
                    costs[i][j]->character[2] = '\0';
                    costs[i][j]->previous     = costs[i-2][j-2];
                }
            }
        }
    }
    /* KILL OPERATION */
    i = lines - 1;
    for (j = 1; j < columns; j++) {
        cost = costs[i][j]->cost + KILL.cost;
        if (cost < costs[lines - 1][columns - 1]->cost) {
            costs[lines - 1][columns - 1]->cost         = cost;
            costs[lines - 1][columns - 1]->type         = &KILL;
            costs[lines - 1][columns - 1]->character[0] = '*';
            costs[lines - 1][columns - 1]->character[1] = '\0';
            costs[lines - 1][columns - 1]->character[2] = '\0';
            costs[lines - 1][columns - 1]->previous     = costs[i][j];
        }
    }

    return costs[lines-1][columns-1];
}

int main (void) {
    int i, j;
    struct Change * changes;

    COPY.name    = "Copy";
    COPY.cost    = 2;

    REPLACE.name = "Replace";
    REPLACE.cost = 2;

    REMOVE.name  = "Delete";
    REMOVE.cost  = 1;

    INSERT.name  = "Insert";
    INSERT.cost  = 3;

    TWIDDLE.name = "TWIDDLE";
    TWIDDLE.cost = 1;

    KILL.name    = "KILL";
    KILL.cost    = 1;

    changes = Distance("algorithm", "altruistic");

    printf("%d\n" , changes->cost);
    PrintChanges(changes);

    return 0;
}
