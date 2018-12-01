#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <queue>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

class TSP
{
private:
	// Filename supplied on command line to read from
	string inFname;

	// Program-generated filename to output to
	string outFname;

	// Initialization function
	void getNodeCount();

    //void addNode(vector<pair<int, int>> *adjList, int next, int cost);


    int nearestNeighbour();

	bool isVisited(bool* arr);
protected:


public:
	// Number of nodes
	int n;

    int minpath;

	void readFile();
	// Current shortest path length
	//int pathLength;

	// Adjacency list
	// Array of n dynamic arrays, each holding a list of nodes it's index is attached to
	vector<pair<int, int>> *adjlist;

	//int start_idx[THREADS];

	//int end_idx[THREADS];

	// Constructor
	TSP(string in, string out);

	// Destructor
	~TSP();

	// Initialization functions


    // Greedy function
    void greedyTSP(int start);

	// Debugging functions
	//void printCities();
	void printAdjList();
	void printResult();

	// Get node count
	int get_size() {return n;};

    // void init(string in, string out);
};