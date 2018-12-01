#include <iostream>
#include <vector>
#include "tsp.h"

using namespace std;

int main(int argc, char const *argv[])
{
    //read file

    //compute greedy on multiple threads

    //find best result

    string f, o;
	f = o = argv[1];
	o.append(".tour");

	// Create new tsp object
	TSP tsp(f, o);
    tsp.readFile();
    // tsp.printAdjList();
    clock_t t = clock();
    tsp.greedyTSP(2);
    cout<<"\nTime: "<<((float) (clock() - t)) / CLOCKS_PER_SEC << "s\n";
    tsp.printResult();
    return 0;
}
