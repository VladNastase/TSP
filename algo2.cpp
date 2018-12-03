#include "algo.h"
//#define no_threads 8

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
void algo(TSP* tsp, int no_threads) {
    pthread_t threads[no_threads];
    struct thread_data* data = new struct thread_data[no_threads];

    // for (int j = 0; j < no_runs; j++) {    
        int inc = tsp->get_size()/no_threads;
        int start = 0;

        for (int i = 0; i < no_threads; i++) {
            // preapre data
            data[i].tsp = tsp;
            data[i].start = start;
            // run threads
            pthread_create(&threads[i], NULL, func, (void*)&data[i]);
            start += inc;
        }
        // join threads
        for (int i = 0; i < no_threads; i++) {
            pthread_join(threads[i], NULL);
        }
    // }
}
