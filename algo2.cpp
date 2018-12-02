#include "algo.h"
#define G_THREADS 8

void *func(void* struc) {
    struct thread_data *data = (struct thread_data*) struc;
    TSP *tsp = data->tsp;
    int start = data->start;

    tsp->greedyTSP(start);

    pthread_exit(NULL);
}

// results of this function are stored in the minpath variable at the
// same position with the starting node, the best path being determined
// by the printResult function
void greedy(TSP* tsp) {
    pthread_t threads[G_THREADS];
    struct thread_data* data = new struct thread_data[G_THREADS];

    int inc = tsp->get_size()/G_THREADS;
    int start = 0;

    for (int i = 0; i < G_THREADS; i++) {
        // preapre data
        data[i].tsp = tsp;
        data[i].start = start;
        // run threads
        pthread_create(&threads[i], NULL, func, (void*)&data[i]);
        start += inc;
    }
    // join threads
    for (int i = 0; i < G_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}