#include <iostream>
#include <vector>
#include "algo.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string in;
	in = argv[1];

	TSP tsp(in);
    tsp.readFile();

    clock_t t = clock();

    greedy(&tsp);

    cout<<"\nTime: "<<((float) (clock() - t)) / CLOCKS_PER_SEC << "s\n";
    tsp.printResult();
    
    
    clock_t t2 = clock();

    cristi(&tsp);

    cout<<"\nTime: "<<((float) (clock() - t2)) / CLOCKS_PER_SEC << "s\n";
    tsp.printResult();
    return 0;
}
