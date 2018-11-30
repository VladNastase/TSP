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
    tsp.printAdjList();
    return 0;
}
