#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <queue>
#include <stack>

using namespace std;

struct City{
	double x;
	double y;
};

double get_distance(struct City c1, struct City c2){
	double dx = c1.x - c2.x;
	double dy = c1.y - c2.y;
	double d  = sqrt(dx*dx + dy*dy);
	return (double) d;
}

string iFile;
string oFile;
double **graph;
vector<City> cities;

int main(int argc, char** argv) {
	if(argc < 2){
		exit(-1);
	}

	// Read file names from input
	string input;
	input = argv[1];

	iFile = input;

	ifstream inStream;
	inStream.open(iFile.c_str(), ios::in);

	if(!inStream){
		cerr << "Can't open input file " << iFile << endl;
		exit(1);
	}
	
	//READ DATA
	int c; double x, y;
	int count = 0;
	while(!inStream.eof()){
		inStream >> c >> x >> y;
		count++;
		struct City newCity = {x,y};
		cities.push_back(newCity);
	}
	count--;
	inStream.close();

	int n = count;
	graph = new double*[n];
	for(int i = 0; i < n; i++){
		graph[i] = new double[n];
		for(int j = 0; j < n; j++){
			graph[i][j] = 0;
		}
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			graph[i][j] = graph[j][i] = get_distance(cities[i],cities[j]);
		}
	}

	cout<<n<<"\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i==j) continue;
			cout<<i<< " "<<j<<" "<<graph[i][j]<<"\n";
		}
	}
}
