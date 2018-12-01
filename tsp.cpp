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

long minpath;

void TSP::greedyTSP(int start) {
    int number = adjlist[start].size();
    bool visited[n];
    memset(visited, 0, sizeof(visited[0]));
    minpath = 0;
    visited[start] = true;
    int startt = start;
    while (!isVisited(visited)) {

        int min = INT32_MAX;
        int minidx;
        number = adjlist[start].size();
        //cout<<start;
        for (int i = 0; i < number; i++) {
            if (i == start) continue;
            if (adjlist[start][i].second < min && !visited[adjlist[start][i].first]) {
                min = adjlist[start][i].second;
                minidx = adjlist[start][i].first;
            }
            // cout <<".";
        }
        // cout<<"\n";
        // cout<<min<<"\n";
        minpath += min;
        // cout<<minpath<<"\n";
        start = minidx;
        visited[start] = true;
    }
    minpath += adjlist[start][startt].second;
}

bool TSP::isVisited(bool* arr) {
    for(int i = 0; i < n; i++) {
        if (arr[i] == false) return false;
    }
    return true;
}

void TSP::printResult() {
    cout<<minpath<<"\n";
}
