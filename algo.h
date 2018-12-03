#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <pthread.h>
#include <stack>
#include <string>
#include <stdio.h>
#include <vector>

using namespace std;

class TSP
{
private:
	// Filename supplied on command line to read from
	string inFile;

	// Utility functions
	bool isVisited(bool* arr);
	int findIdx(int a, int b);
	void findOdds();
	int getMinIndex(double key[], bool mst[]);

	// Graph functions
	void euler(int pos, vector<int> &path);
	void hamilton(vector<int> &path, double &path_dist);
protected:


public:
	// Number of nodes
	int n;

	// The minimum length of the path corresponding to each starting node
	// Set to DBL_MAX if the algorithm didn't start in that node
    double *minpath;

	// Adjacency list
	// Array of n vectors holding adjacent nodes and the cost to reach them
	vector<pair<int, double>> *adjlist;
	// Multigraph resulted after combining MST with Perfect Matching
	vector<pair<int, double>> *multigraph;
	// vector of nodes with odd degrees
	vector<int> odds;

	// Constructor
	TSP(string in);

	// Destructor
	~TSP();

	// Initialization functions
	void readFile();

    // Greedy function
    void greedyTSP(int start);

	// Graph functions
	void findMST();
	void perfect_matching();
	double find_path(int pos);

	// Debugging functions
	void printAdjList();
	void printPrim();
	void printResult();

	// Get node count
	int get_size() {return n;};
};

struct thread_data {
    TSP *tsp;
    int start;
};

void algo(TSP* tsp, int no_threads);