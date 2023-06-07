#include <mpi.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "algorithm.h"
#include "functions.h"
#include <time.h>
#include <math.h>

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

    // initialize MPI
    int comm_sz;
    int my_rank;
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    // prepare individual data
    int cont, local_patterns = (int) ceil(((double)patterns_num/(double)comm_sz));

    // take timings
    double start_t, end_t, my_time, max_time = 0;
    start_t = MPI_Wtime();

    // apply algorithm for each assigned batch of patterns
    for (int i = 0; i < local_patterns; i++) {
        if (my_rank*local_patterns + i >= patterns_num) break;
        cont = KMPmatch(pack, patt[my_rank*local_patterns + i]);
        // print result
        printf("%s was found %d times by process %d.\n", patt[my_rank*local_patterns + i], cont, my_rank);
    }

    // stop my timer
    end_t = MPI_Wtime();
    my_time = end_t - start_t;
    MPI_Reduce(&my_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

    // print longest time
    if (my_rank == 0) {
        printf("\nTime: %f seconds for the longest process.", max_time);
    }

    // finalize MPI
    MPI_Finalize();

    // free memory
    for (int i=0; i<patterns_num; i++) free(patt[i]);
    free(patt);
    free(pack);
    fclose(packetsFile);
    fclose(patternsFile);
}