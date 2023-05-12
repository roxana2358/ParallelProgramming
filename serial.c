#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithm.c"
#include <time.h>

int main(int argc, char *argv[]) {
    // check for correct input
    if (argc!=3) {
        printf("Seems like your input is incorrect!\n");
        exit(EXIT_FAILURE);
    }

    // open file with packets
    FILE *packetsFile;
    packetsFile = fopen(argv[1], "r");
    if (packetsFile==NULL) {
        printf("Packets opening failure.\n");
        exit(EXIT_FAILURE);
    }

    // open file with patterns
    FILE *patternsFile;
    patternsFile = fopen(argv[2], "r");
    if (patternsFile==NULL) {
        printf("Packets opening failure.\n");
        exit(EXIT_FAILURE);
    }

    // separate patterns in an array and get their number
    int pattLength = 0;
    char **patt = splitFile(patternsFile, &pattLength, MAX_PATTERN_LENGTH);
    if (pattLength == 0) {
        printf("Not enough patterns!\n");
        exit(EXIT_FAILURE);
    }

    // separate lines (packets) and get their number
    int packLength = 0;
    char **pack = splitFile(packetsFile, &packLength, MAX_LINE_LENGTH);
    if (packLength == 0) {
        printf("Not enough packets!\n");
        exit(EXIT_FAILURE);
    }

    // take timings
    clock_t start_t, end_t;
    start_t = clock();

    // for each pattern apply the algorithm
    for (int i=0; i<pattLength; i++) {
        int cont = 0;
        // apply algorithm to all lines/packets
        for (int j=0; j<packLength; j++) {
            // apply KNM
            cont += KMPmatch(pack[j], patt[i]);
        }
        // print result
        printf("%s was found %d times.\n", patt[i], cont);
    }

    end_t = clock();
    printf("\nTime: %f s\n", (((double)(end_t - start_t))/CLOCKS_PER_SEC));

    // free memory
    // for (int i=0; i<pattLength; i++) free(patt[i]);
    free(patt);
    // for (int i=0; i<packLength; i++) free(pack[i]);
    free(pack);
}