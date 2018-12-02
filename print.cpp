#include "algo.h"

void TSP::printAdjList() {
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < (int)adjlist[i].size(); j++) {
            cout << "{ " << adjlist[i][j].first << ", " << adjlist[i][j].second << " }, ";
        }
        cout<<"\n";
    }
}

void TSP::printPrim() {
    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        for (int j = 0; j < (int)multigraph[i].size(); j++) {
            cout << "{ " << multigraph[i][j].first << ", " << multigraph[i][j].second << " } ";
        }
        cout<<"\n";
    }
}

void TSP::printResult() {
    double min = std::numeric_limits<double>::max();
    for (int i =0 ;i < n;i++) {
        if (minpath[i] < min) min = minpath[i];
    }
    cout<<min<<"\n";
}
