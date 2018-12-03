#include "algo.h"

void *cfunc(void* struc) {
    struct thread_data *data = (struct thread_data*) struc;
    TSP *tsp = data->tsp;
    int start = data->start;
    tsp->find_path(start);
    pthread_exit(NULL);
}

void algo(TSP *tsp, int no_threads) {
    tsp->findMST();
    tsp->perfect_matching();

    pthread_t threads[no_threads];
    struct thread_data* data = new struct thread_data[no_threads];
    int inc = tsp->get_size()/no_threads;
    int start = 0;

    for (int i = 0; i < no_threads; i++) {
        data[i].tsp = tsp;
        data[i].start = start;
        pthread_create(&threads[i], NULL, cfunc, (void*)&data[i]);
        start += inc;
    }

    for (int i = 0; i < no_threads; i++) {
        pthread_join(threads[i], NULL);
    }
}
