#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"
#include "functions.h"
#include <time.h>
#include "timer.h"

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
        printf("Patterns opening failure.\n");
        exit(EXIT_FAILURE);
    }

    // fuse all packets in one string
    char *pack = fusePackets(packetsFile);
    if (pack==NULL) {
        printf("Errors with the packets.\n");
        exit(EXIT_FAILURE);
    }

    // separate patterns in an array
    int patterns_num;
    char **patt = splitPatterns(patternsFile, &patterns_num);
    if (patt==NULL || patterns_num == 0) {
        printf("Errors with the patterns.\n");
        exit(EXIT_FAILURE);
    }

    // take timings
    double start_t = 0, end_t = 0;
    GET_TIME(start_t);

    int cont = 0;
    // for each pattern apply the algorithm
    for (int i=0; i<patterns_num; i++) {
        // apply KNM algorithm to all lines/packets
        cont = KMPmatch(pack, patt[i]);
        // print result
        printf("%s was found %d times.\n", patt[i], cont);
    }

    // stop timer
    GET_TIME(end_t)
    printf("\nTime: %f seconds", (end_t - start_t));

    // free memory
    for (int i=0; i<patterns_num; i++) free(patt[i]);
    free(patt);
    free(pack);
    fclose(packetsFile);
    fclose(patternsFile);
}