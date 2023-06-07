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
    int local_patterns = (int) ceil(((double)patterns_num/(double)comm_sz));

    // take timings
    double start_t, end_t, my_time, max_time = 0;
    start_t = MPI_Wtime();

    int cont = 0;
    char msg[45];
    // if process 0 apply algorithm to batch of patterns and wait for others
    if (my_rank == 0) {
        for (int i = 0; i < local_patterns; i++) {
            cont = KMPmatch(pack, patt[my_rank*local_patterns + i]);
            // print result
            printf("%s was found %d times by proc %d.\n", patt[my_rank*local_patterns + i], cont, my_rank);
        }

        // stop my timer
        end_t = MPI_Wtime();
        my_time = end_t - start_t;
        MPI_Reduce(&my_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

        // receive results
        for (int p = local_patterns; p < patterns_num; p++) {
            MPI_Recv(msg, sizeof(msg), MPI_CHAR, p/local_patterns, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("%s", msg);
        }

        // print longest time
        printf("\nTime: %f seconds for the longest process.", max_time);

    } else { // if other process, apply algorithm and send response
        for (int i = 0; i < local_patterns; i++) {
            // too many processes for the patterns
            if (my_rank*local_patterns + i >= patterns_num) break;
            // compute
            cont = KMPmatch(pack, patt[my_rank*local_patterns + i]);
            // send result
            sprintf(msg, "%s was found %d times by proc %d.\n", patt[my_rank*local_patterns + i], cont, my_rank);
            MPI_Send(msg, sizeof(msg), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }

        // stop my timer
        end_t = MPI_Wtime();
        my_time = end_t - start_t;
        MPI_Reduce(&my_time, &max_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
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