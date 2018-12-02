#include "algo.h"

bool TSP::isVisited(bool *arr) {
    for(int i =0 ;i < n; i++) {
        if (arr[i] == false) return false;
    }
    return true;
}

// Basic binary search. Disadvantage of adjacency list over matrix
int TSP::findIdx(int a, int val) {
    int start = 0;
    int end = adjlist[a].size() - 1;
    int mid;

    while (start <= end) {
        mid = start + (end-start)/2;
        if (adjlist[a][mid].first == val) return mid;
        if (adjlist[a][mid].first < val) {
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }

    return -1;
}

void TSP::findOdds() {
    for (int r = 0; r < n; r++) {
        if ((multigraph[r].size() % 2) != 0 ) {
            odds.push_back(r);
        }
    }
}

int TSP::getMinIndex(double weight[], bool mst[]) {
    double min = std::numeric_limits<double>::max();
    int min_index = -1;

    for (int i = 0; i < n; i++) {
        if (mst[i] == false && weight[i] < min) {
            min = weight[i];
            min_index = i;
        }
    }

    return min_index;
}