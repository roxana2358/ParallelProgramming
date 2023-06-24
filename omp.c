#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"
#include "functions.h"
#include <time.h>
#include "timer.h"
#include <omp.h>

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

    // get number of threads
    int const THREADS_NUMBER = atoi(argv[3]);

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
    double start_t, end_t;
    start_t = omp_get_wtime();

    int cont;
    # pragma omp parallel for num_threads(THREADS_NUMBER) private(cont)
    for (int i = 0; i < patterns_num; i++) {
        // apply algorithm
        cont = KMPmatch(pack, patt[i]);
        // print result
        printf("%s was found %d times by thread %d of %d.\n", patt[i], cont, omp_get_thread_num()+1, omp_get_num_threads());
    }

    // stop timer
    end_t = omp_get_wtime();
    double time = end_t-start_t;
    printf("\nTime: %f seconds", time);

    // free memory
    for (int i=0; i<patterns_num; i++) free(patt[i]);
    free(patt);
    free(pack);
    fclose(packetsFile);
    fclose(patternsFile);
}