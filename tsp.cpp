#include "algo.h"

using namespace std;

#ifndef SYMMETRICAL
#define SYMMETRICAL 0
#else
#define SYMMETRICAL 1
#endif

#ifndef DEBUG
#define DEBUG 0
#else
#define DEBUG 1
#endif

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Constructor
TSP::TSP(string in) {
    inFile = in;
}

// Destructor
TSP::~TSP() {
    delete [] adjlist;
    delete [] multigraph;
}

void TSP::readFile() {
    ifstream in;
    in.open(inFile.c_str(), ios::in);

    in >> n;
    adjlist = new vector<pair<int, double>> [n];
    multigraph = new vector<pair<int, double>> [n];
    minpath = new double[n];
    std::fill_n(minpath, n, std::numeric_limits<double>::max());

    int current, next;
    double cost;
    while (!in.eof()) {
        in >> current >> next >> cost;
        
        adjlist[current - 1].push_back(make_pair(next - 1, cost));
        if (SYMMETRICAL) {
            adjlist[next - 1].push_back(make_pair(current - 1, cost));
        }
    }
}

void TSP::greedyTSP(int start) {
    // Array to see if node is visited. Initially no node is visted
    bool visited[n];
    memset(visited, 0, sizeof(visited[0]));
    // Set value of path to 0; set starting node to visited and remember it

            pthread_mutex_lock(&mutex);
    minpath[start] = 0;
    pthread_mutex_unlock(&mutex);
    visited[start] = true;
    int startt = start;
    //cout<<startt<<"\n";

    while (!isVisited(visited)) {
        double min = std::numeric_limits<double>::max();
        int minidx = -1;
        // Search for the closest neighbour of the current vertex
        for (int i = 0; i < (int)adjlist[start].size(); i++) {
            //if (i == start) continue;
            if (adjlist[start][i].second < min 
                    && !visited[adjlist[start][i].first]) {
                        
                min = adjlist[start][i].second;
                minidx = adjlist[start][i].first;
            }
        }
        //cout<<"Node "<<minidx<<"; cost "<<min<<"\n";
        // Visit it, add it to the path length and search his neighbours next
            pthread_mutex_lock(&mutex);
        minpath[startt] += min;
    pthread_mutex_unlock(&mutex);

        start = minidx;
        visited[start] = true;
    }
    // Add the distance from the last node to the first one
        pthread_mutex_lock(&mutex);
    minpath[startt] += adjlist[start][findIdx(start, startt)].second;
    pthread_mutex_unlock(&mutex);

}

void TSP::findMST() {
    pthread_mutex_lock(&mutex);
    std::fill_n(minpath, n, std::numeric_limits<double>::max());
    pthread_mutex_unlock(&mutex);
    double weight[n];
    bool visited[n];
    int parent[n];

    // Set all weights to DBL_MAX and all nodes to unvisited
    for (int i = 0; i < n; i++) {
        weight[i] = std::numeric_limits<double>::max();
        visited[i] = false;
    }

    weight[0] = 0;
    parent[0] = -1;

    for (int i = 0; i < n - 1; i++) {
        // Find closest vertex not in MST and set visited
        int k = getMinIndex(weight, visited);
        visited[k] = true;

        // Check all unvisited negihbours of k
        for (int j = 0; j < (int) adjlist[k].size(); j++) {
            // If smaller weight, update
            if (adjlist[k][j].first != k 
                    && visited[adjlist[k][j].first] == false 
                    && adjlist[k][j].second < weight[adjlist[k][j].first]) {
                parent[adjlist[k][j].first] = k;
                weight[adjlist[k][j].first] = adjlist[k][j].second;
            }
        }
    }

    // Put MST together; store in multigraph
    for (int i = 0; i < n; i++) {
        int j = parent[i];
        double h = weight[i];

        if (j != -1) {
            multigraph[i].push_back(make_pair(j, h));
            multigraph[j].push_back(make_pair(i, h));
        }
    }
}

// Finds a minimum-weight perfect matching;
// Greedy (not optimal)
void TSP::perfect_matching() {
    int closest;
    double length;

    vector<int>::iterator tmp, first;

    // Find nodes with odd degrees
    findOdds();

    // For each odd node find closest
    while (!odds.empty()) {
        first = odds.begin();
        vector<int>::iterator i = odds.begin() + 1;
        vector<int>::iterator end = odds.end();
        length = std::numeric_limits<double>::max();
        for (; i != end; ++i) {
            int a= findIdx(*first, *i);
            if (adjlist[*first][a].second < length) {
                length = adjlist[*first][a].second;
                closest = *i;
                tmp = i;
            }
        }

        multigraph[*first].push_back(make_pair(closest, length));
        multigraph[closest].push_back(make_pair(*first, length));

        tmp = odds.erase(tmp);
        first = odds.erase(first);
    }
} 

void TSP::euler (int pos, vector<int> &path) {
    // Copy multigraph
    // Uses more memory but does not break anything when multi-threaded
    vector<pair<int, double>> *temp = new vector<pair<int, double>> [n];
    for (int i = 0; i < n; i++) {
    	temp[i].resize(multigraph[i].size());
    	temp[i] = multigraph[i];
    }

    path.clear();

    // Repeat until the current vertex has no more neighbours and the stack is empty.
    stack<int> stk;
    while (!stk.empty() || temp[pos].size() > 0 ) {
        // If current vertex has no neighbours
        if (temp[pos].size() == 0) {
            // Add to path
            path.push_back(pos);
            // remove the last vertex from the stack and set it as the current one.
            int last = stk.top();
            stk.pop();
            pos = last;
        } else {
            // Add to stack,
            stk.push(pos);
            // take any of its neighbours,
            int neighbour = temp[pos].back().first;
            // remove the edge,
            temp[pos].pop_back();
            for (unsigned int i = 0; i < temp[neighbour].size(); i++)
                if (temp[neighbour][i].first == pos) {
                    // remove the neighbour
                    temp[neighbour].erase (temp[neighbour].begin() + i);
                    break;
                }
            // and set as current vertex.
            pos = neighbour;
        }
    }
    path.push_back(pos);
}

// Removes doubles from euler path
void TSP::hamilton(vector<int> &path, double &path_dist) {
    bool visited[n];
    memset(visited, 0, n * sizeof(bool));

    path_dist = 0;

    int root = path.front();
    vector<int>::iterator curr = path.begin();
    vector<int>::iterator next = path.begin() + 1;
    visited[root] = true;

    while (next != path.end()) {
        if (!visited[*next]) {
            path_dist += adjlist[*curr][findIdx(*curr, *next)].second;
            curr = next;
            visited[*curr] = true;
            next = curr + 1;
        } else {
            next = path.erase(next);
        }
    }

    // Add the distance back to start
    path_dist += adjlist[*curr][findIdx(*curr, *next)].second;
}


// Uses euler and hamilton to determine a path
double TSP::find_path (int pos) {
    vector<int>path;
    euler(pos, path);
    double length;
    hamilton(path, length);

    pthread_mutex_lock(&mutex);
    minpath[pos] = length;
    pthread_mutex_unlock(&mutex);
    return length;
}
