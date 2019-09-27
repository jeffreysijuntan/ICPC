#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <complex>

using namespace std;
static const int MAX = 100000;
static const int NIL = -1;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;

using namespace std;

vector<vector<int> > G;
int color[MAX];
int n;


void dfsUtil(int v, bool visited[], vector<vector<int> > &G, vector<int> &zones, int c) 
{ 
    // Mark the current node as visited and print it 
    visited[v] = true; 
    zones[v] = c; 
  
    // Recur for all the vertices adjacent to this vertex 
    for (int i = 0; i < n; ++i) {
    	if (G[v][i] == 1)
    		if (!visited[i])
    			dfsUtil(i, visited, G, zones, c);
    }
}

void fillOrder(int v, bool visited[], stack<int> &S) { 
    // Mark the current node as visited and print it 
    visited[v] = true; 

    for (int i = 0; i < n; ++i) {
    	if (G[v][i] == 1)
    		if (!visited[i])
    			fillOrder(i, visited, S);
    }
    // All vertices reachable from v are processed by now, push v  
    S.push(v); 
} 

vector<vector<int> > getTranspose() {
	vector<vector<int> > trAdjM(n);
	for (int i = 0; i < n; ++i)
		trAdjM[i].resize(n, 0);

    for (int v = 0; v < n; v++) { 
        // Recur for all the vertices adjacent to this vertex 
    	for (int i = 0; i < n; ++i) {
	    	if (G[v][i] == 1)
	    		trAdjM[i][v] = 1;
    	}
    }
    return trAdjM; 
}

vector<int> findSCCs() 
{ 
    stack<int> S;
  
    // Mark all the vertices as not visited (For first DFS) 
    bool *visited = new bool[n]; 
    for(int i = 0; i < n; i++) 
        visited[i] = false; 
  
    // Fill vertices in stack according to their finishing times 
    for(int i = 0; i < n; i++) 
        if(visited[i] == false) 
            fillOrder(i, visited, S); 
  
    // Create a reversed graph 
    auto trAdjM = getTranspose();
  
    // Mark all the vertices as not visited (For second DFS) 
    for(int i = 0; i < n; i++) 
        visited[i] = false; 
  
    // Now process all vertices in order defined by Stack 

    vector<int> zones(n, 0);
    int c = 0;
    while (!S.empty()) 
    { 
        // Pop a vertex from stack 
        int v = S.top(); S.pop(); 
        // Print Strongly connected component of the popped vertex 
        if (visited[v] == false) 
        { 
            dfsUtil(v, visited, trAdjM, zones, c); 
            c++;
        }
    }
    return zones; 
} 

unordered_map<int, int> countEdges(vector<int>&zones, vector<vector<int> > &adjM) {
	unordered_map<int, int> map;
	for (int i = 0; i < zones.size(); ++i) {
		int root = zones[i];
		if (!map.count(root)) {
			map[root] = 0;
		}
		for (int neighbor : adjM[i]) {
			map[root] += neighbor;
		}

	}
	return map;
}


void count(vector<int> &zones) {
	int res = 0;
	auto edgeMap = countEdges(zones, G);

	int max = *std::max_element(zones.begin(), zones.end());
	for (int i = 0; i <= max; ++i) {
		int zi = zones[i];
		int ziSize = count(zones.begin(), zones.end(), i);
		res += ziSize*(ziSize-1) - edgeMap[i]; 
		for (int j = i+1; j <= max; ++j) {
			int zjSize = count(zones.begin(), zones.end(), j);
			res += ziSize * zjSize;
		}
	}
	cout << res << endl;
}

int main() {
	cin >> n;
	// load adjM
	G.resize(n);
	for (int i = 0; i < n; ++i) {
		G[i].resize(n, 0);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> G[i][j];
		}
	}

	auto zones = findSCCs();
	count(zones);

}