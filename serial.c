#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"
#include "functions.h"
#include <time.h>

int main(int argc, char *argv[]) {
    // check for correct input
    if (argc!=4) {
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
        printf("Patterns opening failure.\n");
        exit(EXIT_FAILURE);
    }

    // get the number of patterns
    int const NUMBER_OF_PATTERNS = atoi(argv[3]);
    if (NUMBER_OF_PATTERNS<1) {
        printf("No patterns to find!\n");
        exit(EXIT_FAILURE);
    }

    // fuse all packets in one string
    char *pack = fusePackets(packetsFile);
    if (pack==NULL) {
        printf("Errors with the packets.\n");
        exit(EXIT_FAILURE);
    }

    // separate patterns in an array
    char **patt = splitPatterns(patternsFile, NUMBER_OF_PATTERNS);
    if (patt==NULL) {
        printf("Errors with the patterns.\n");
        exit(EXIT_FAILURE);
    }

    // take timings
    clock_t start_t, end_t;
    start_t = clock();

    int cont = 0;
    // for each pattern apply the algorithm
    for (int i=0; i<NUMBER_OF_PATTERNS; i++) {
        // apply KNM algorithm to all lines/packets
        cont = KMPmatch(pack, patt[i]);
        // print result
        printf("%s was found %d times.\n", patt[i], cont);
    }

    // stop timer
    end_t = clock();
    printf("\nTime: %f seconds", (((double)(end_t - start_t))/CLOCKS_PER_SEC));

    // free memory
    for (int i=0; i<NUMBER_OF_PATTERNS; i++) free(patt[i]);
    free(patt);
    free(pack);
    fclose(packetsFile);
    fclose(patternsFile);
}