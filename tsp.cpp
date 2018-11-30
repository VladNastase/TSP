#include "tsp.h"

using namespace std;

#define SYMMETRICAL 0

// Constructor
TSP::TSP(string in, string out) {
    inFname = in;
    outFname = out;
}

TSP::~TSP() {

}

// void TSP::init(string in, string out) {
//         inFname = in;
//     outFname = out;

//     readFile();
// }

void TSP::readFile() {
    ifstream in;
    in.open(inFname.c_str(), ios::in);

    in >> n;
    adjlist = new vector<pair<int, int>> [n];

    int current, next, cost;
    while (!in.eof()) {
        in >> current >> next >>cost;
        
        adjlist[current].push_back(make_pair(next, cost));
        if (SYMMETRICAL) {
            adjlist[next].push_back(make_pair(current, cost));     
        }
    }
}

void TSP::printAdjList() {
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < (int)adjlist[i].size(); j++) {
            cout << "{ " << adjlist[i][j].first << ", " << adjlist[i][j].second << " } ";
        }
        cout<<"\n";
    }
}