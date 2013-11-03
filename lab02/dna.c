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

struct Change {
    struct Operation * type;
    struct Change * previous;
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
 * Creates a new change object
 *
 * returns {struct Change *} The change object
 */
struct Change * NewChange () {
    struct Change * change;

    change               = malloc(sizeof(struct Change));
    change->cost         = INFINITY;
    change->type         = NULL;
    change->previous     = NULL;

    return change;
}

void printOperations (struct Change * change) {
    if (change == NULL || change->type == NULL) { return; }
    printOperations(change->previous);
    printf("%c", change->type->name[0]);
}

void printFirstString (struct Change * change) {
    if (change == NULL || change->type == NULL) { return; }
    printFirstString(change->previous);
    printf("%c", change->firstString);
}

void printSecondString (struct Change * change) {
    if (change == NULL || change->type == NULL) { return; }
    printSecondString(change->previous);
    printf("%c", change->secondString);
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
        costs[i][j]               = NewChange();
        costs[i][j]->cost         = i * INSERT.cost;
        costs[i][j]->type         = &INSERT;
        costs[i][j]->previous     = costs[i-1][j];
        costs[i][j]->firstString  = ' ';
        costs[i][j]->secondString = correctString[i-1];
    }
    /* CONVERTING TO NULL STRING */
    i = 0;
    for (j = 1; j < columns; j++) {
        costs[i][j]               = NewChange();
        costs[i][j]->cost         = j * REMOVE.cost;
        costs[i][j]->type         = &REMOVE;
        costs[i][j]->previous     = costs[i][j-1];
        costs[i][j]->firstString  = wrongString[j-1];
        costs[i][j]->secondString = ' ';
    }
    for (i = 1; i < lines; i++) {
        for (j = 1; j < columns; j++) {
            costs[i][j] = NewChange();
            /* COPY OPERATION */
            cost = costs[i-1][j-1]->cost + COPY.cost;
            if (cost < costs[i][j]->cost && correctString[i-1] == wrongString[j-1]) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &COPY;
                costs[i][j]->previous     = costs[i-1][j-1];
                costs[i][j]->firstString  = wrongString[j-1];
                costs[i][j]->secondString = correctString[i-1];
            }
            /* REPLACE OPERATION */
            cost = costs[i-1][j-1]->cost + REPLACE.cost;
            if (cost < costs[i][j]->cost) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &REPLACE;
                costs[i][j]->previous     = costs[i-1][j-1];
                costs[i][j]->firstString  = wrongString[j-1];
                costs[i][j]->secondString = correctString[i-1];
            }
            /* REMOVE OPERATION */
            cost = costs[i][j-1]->cost + REMOVE.cost;
            if (cost < costs[i][j]->cost) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &REMOVE;
                costs[i][j]->previous     = costs[i][j-1];
                costs[i][j]->firstString  = wrongString[j-1];
                costs[i][j]->secondString = ' ';
            }
            /* INSERT OPERATION */
            cost = costs[i-1][j]->cost + INSERT.cost;
            if (cost < costs[i][j]->cost) {
                costs[i][j]->cost         = cost;
                costs[i][j]->type         = &INSERT;
                costs[i][j]->previous     = costs[i-1][j];
                costs[i][j]->firstString  = ' ';
                costs[i][j]->secondString = correctString[i-1];
            }
        }
    }

    return costs[lines-1][columns-1];
}

int main (void) {
    int i, j;
    struct Change * changes;

    COPY.name    = "+";
    COPY.cost    = -1;

    REPLACE.name = "-";
    REPLACE.cost = 1;

    REMOVE.name  = "*";
    REMOVE.cost  = 2;

    INSERT.name  = "*";
    INSERT.cost  = 2;

    changes = Distance("GATCGGCAT", "CAATGAATC");

    printFirstString(changes);
    printf("\n");
    printSecondString(changes);
    printf("\n");
    printOperations(changes);
    printf("\n");

    //na primeira string copy e replace e delete repito o char, insert char em branco
    //na segunda string copy e replace e insert repito o char, delete char em branco
    return 0;
}
