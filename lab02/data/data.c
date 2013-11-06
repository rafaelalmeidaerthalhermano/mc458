#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char randomChar () {
    int range = ((int) 'z') - ((int) 'a');

    return (char) (rand() % range) + ((int) 'a');
}

char randomBasis () {
    int random = rand() % 4;
    if (random == 0) return 'a';
    if (random == 1) return 't';
    if (random == 2) return 'g';
    if (random == 3) return 'c';
}

int main (void) {
    int s;
    int m, n;
    int k, i;
    FILE* file;
    char fileName [80];
    char loopString [80];

    srand(time(NULL));

    for (s = 50; s <= 5000; s += 50) {
        strcpy(fileName, "ins.");
        sprintf(loopString, "%d", s);
        strcat(fileName, loopString);
        strcat(fileName, ".1.txt");
        file = fopen(fileName, "wb");
        m = s;
        for (k = 0; k < 5; k++) {
            m = m / 2;
            n = s - m;
            fprintf(file, "%d %d\n", m, n);
            for (i = 0; i < m; i++) {
                fprintf(file, "%c", randomChar());
            }
            fprintf(file, "\n");
            for (i = 0; i < n; i++) {
                fprintf(file, "%c", randomChar());
            }
            fprintf(file, "\n1 1 1 1 1 1\n");
        }
        fclose(file);
    }

    for (s = 50; s <= 5000; s += 50) {
        strcpy(fileName, "ins.");
        sprintf(loopString, "%d", s);
        strcat(fileName, loopString);
        strcat(fileName, ".2.txt");
        file = fopen(fileName, "wb");
        m = s;
        for (k = 0; k < 5; k++) {
            m = m / 2;
            n = s - m;
            fprintf(file, "%d %d\n", m, n);
            for (i = 0; i < m; i++) {
                fprintf(file, "%c", randomBasis());
            }
            fprintf(file, "\n");
            for (i = 0; i < n; i++) {
                fprintf(file, "%c", randomBasis());
            }
            fprintf(file, "\n-1 1 2 2 99999999 99999999\n");
        }
        fclose(file);
    }
}
