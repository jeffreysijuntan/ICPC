#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <climits>
using namespace std;

// A utility function to find the subset of an element i  
int find(vector<int> &parent, int i)  
{  
    if (parent[i] == -1)  
        return i;  
    return find(parent, parent[i]);  
}  
  
// A utility function to do union of two subsets  
void Union(vector<int> &parent, int x, int y)  
{  
    int xset = find(parent, x);  
    int yset = find(parent, y);  
    if(xset != yset) 
    {  
        parent[xset] = yset;  
    }  
}  

void dfs(vector<int> bt , int curr, vector<vector<int> > &adjM, vector<vector<int> >& res, unordered_set<int> &visited) {
	visited.insert(curr);
	bt.push_back(curr);

	for (int i = 0; i < adjM.size(); ++i) {
		if (adjM[curr][i] == 1) {
			for (auto e : bt) {
				res[e][i] = 1;
			}
			if (visited.count(i)) {
				continue;
			}
			dfs(bt, i, adjM, res, visited);
		}
	}
}

vector<vector<int> > floydWarshall (vector<vector<int> > &graph)  
{  
	int V = graph.size();
	vector<vector<int> > dist(V);
	for (int i = 0; i < V; ++i) {
		dist[i].resize(V, 0);
	}

    int i, j, k;  
  
    for (i = 0; i < V; i++)  {
        for (j = 0; j < V; j++)  {
        	if (graph[i][j] == 0)
        		dist[i][j] = 999999;
        	else
            	dist[i][j] = graph[i][j];  
        }
  	}
    for (k = 0; k < V; k++)  
    {  
        // Pick all vertices as source one by one  
        for (i = 0; i < V; i++)  
        {  
            // Pick all vertices as destination for the  
            // above picked source  
            for (j = 0; j < V; j++)  
            {  
                // If vertex k is on the shortest path from  
                // i to j, then update the value of dist[i][j]  
                if (dist[i][k] + dist[k][j] < dist[i][j])  
                    dist[i][j] = dist[i][k] + dist[k][j];  
            }  
        }  
    }  

    for (i = 0; i < V; i++)  {
        for (j = 0; j < V; j++)  {
        	if (dist[i][j] < 999999)
        		dist[i][j] = 1;
        	else
        		dist[i][j] = 0;
        }
    }
 	return dist;
}  


// union find
vector<int> findZone(vector<vector<int> >& connected, vector<int>& parent) {
	int N = connected.size();

	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (connected[i][j] && connected[j][i]) {
				Union(parent, i, j);
			}
		}
	}

	unordered_set<int> set;
	for (int i = 0; i < N; ++i) {
		int root = find(parent, i);
		set.insert(root);
	}
	vector<int> group(set.begin(), set.end());
	return group;
}

unordered_map<int, int> getGroupSize(vector<int>&parent) {
	unordered_map<int, int> map;
	for (int i = 0; i < parent.size(); ++i) {
		int root = find(parent, i);
		if (!map.count(root)) {
			map[root] = 1;
		} else {
			map[root]++;
		}
	}
	return map;
}

unordered_map<int, int> countEdges(vector<int>&parent, vector<vector<int> > &adjM) {
	unordered_map<int, int> map;
	for (int i = 0; i < parent.size(); ++i) {
		int root = find(parent, i);

		if (!map.count(root)) {
			map[root] = 0;
		}
		for (int neighbor : adjM[i]) {
			map[root] += neighbor;
		}
	}
	return map;
}


//form another graph between groups. If group a reach group b, then every element in A can form a path to every element in B, adding |A||B| to the result
int count(vector<vector<int> > &connected, vector<vector<int> > &adjM) {
	int res = 0;
	int N = connected.size();
	
	vector<int> parent(N, -1);
	auto group = findZone(connected, parent);

	auto groupSize = getGroupSize(parent);
	auto edgeMap = countEdges(parent, adjM);

	for (int i = 0; i < group.size(); ++i) {
		int v1 = group[i];
		int n = groupSize[v1];
		res += n*(n-1) - edgeMap[v1]; 
		for (int j = i+1; j < group.size(); ++j) {
			int v2 = group[j];
			res += groupSize[v1] * groupSize[v2];
		}
	}
	return res;
}


int main() {
	int n;
	cin >> n;

	// load adjM
	vector<vector<int> > adjM;
	adjM.resize(n);
	for (int i = 0; i < n; ++i) {
		adjM[i].resize(n, 0);
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> adjM[i][j];
		}
	}

	vector<vector<int> > connected(n);
	for (int i = 0; i < n; ++i) {
		connected[i].resize(n, 0);
	}

	// Get connected
	/*
	unordered_set<int> visited;
	for (int i = 0; i < n; ++i) {
		vector<int> bt;
		if (!visited.count(i))
			dfs(bt, i, adjM, connected, visited);
	}
	*/
	connected = floydWarshall(adjM);

	
	/*for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cout << connected[i][j];
		}
		cout << endl;
	}
	*/

	cout << count(connected, adjM) << endl;
}