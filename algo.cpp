#include "algo.h"
#define C_THREADS 32

void *cfunc(void* struc) {
    struct thread_data *data = (struct thread_data*) struc;
    TSP *tsp = data->tsp;
    int start = data->start;
    tsp->find_path(start);
    pthread_exit(NULL);
}

void cristi(TSP *tsp) {
    tsp->findMST();
    tsp->perfect_matching();

    pthread_t threads[C_THREADS];
    struct thread_data* data = new struct thread_data[C_THREADS];
    int inc = tsp->get_size()/C_THREADS - 1;
    int start = 0;

    for (int i = 0; i < C_THREADS; i++) {
        data[i].tsp = tsp;
        data[i].start = start;
        pthread_create(&threads[i], NULL, cfunc, (void*)&data[i]);
        start += inc;
    }

    for (int i = 0; i < C_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
}