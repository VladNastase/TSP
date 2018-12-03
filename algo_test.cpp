#include <iostream>
#include <vector>
#include "algo.h"

#ifndef BEST
#define BEST 0
#else
#define BEST 1
#endif

using namespace std;

int main(int argc, char const *argv[])
{
    string in;
	in = argv[1];

	TSP tsp(in);
    tsp.readFile();

    //clock_t t = clock();
    int n = tsp.get_size();
    if (!BEST) {
        if (n < 128) {
            algo(&tsp, n);
        } else if (n < 512) {
            algo(&tsp, 128);
        } else {
            algo(&tsp, 64);
        }
    } else {
        if (n < 256) {
            algo(&tsp, n);
        } else if (n < 2048) {
            algo(&tsp, 512);
        } else {
            algo(&tsp, 256);
        }
    }
    cout.precision(10);
    //cout<<"\nTime: "<<((float) (clock() - t)) / CLOCKS_PER_SEC << "s\n";
    tsp.printResult();
    
    return 0;
}
