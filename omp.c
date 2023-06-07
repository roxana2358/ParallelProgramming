#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"
#include "functions.h"
#include <time.h>
#include "timer.h"
#include <math.h>
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

    int local_patterns = (int) ceil(((double)patterns_num/(double)THREADS_NUMBER));
    double max_time = 0;
    # pragma omp parallel num_threads(THREADS_NUMBER)
    {
        int cont, my_rank = omp_get_thread_num();

        // take timings
        double start_t = 0, end_t = 0;
        start_t = omp_get_wtime();

        for (int i = 0; i < local_patterns; i++) {
            if (my_rank*local_patterns + i >= patterns_num) break;
            cont = KMPmatch(pack, patt[my_rank*local_patterns + i]);
            // print result
            printf("%s was found %d times by thread %d.\n", patt[my_rank*local_patterns + i], cont, my_rank);
        }

        // stop timer
        end_t = omp_get_wtime();
        double my_time = end_t-start_t;
        # pragma omp critical(time)
        max_time = ((max_time > my_time) ? max_time : my_time);
    }

    // max time
    printf("\nTime: %f seconds", max_time);

    // free memory
    for (int i=0; i<patterns_num; i++) free(patt[i]);
    free(patt);
    free(pack);
    fclose(packetsFile);
    fclose(patternsFile);
}