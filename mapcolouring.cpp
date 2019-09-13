#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

class Graph {
public:
	vector<vector<int>> adjList;

	Graph(vector<std::pair<int, int>>& edges, int N) {
		N = N;
		adjList.resize(N);
		for (auto edge : edges) {
			int u = edge.first;
			int v = edge.second;
			adjList[u].push_back(v);
			adjList[v].push_back(u);
		}
	}

	vector<int> getNeighbors(int u) {
		return adjList[u];
	}
};

void genColors(vector<vector<int>>& res, vector<int>& colors, int N) {
	if (N == 0) {
		res.push_back(colors);
		return;
	}
	for (int i = 1; i <= 4; ++i) {
		colors[N-1] = i;
		genColors(res, colors, N-1);
	}
}

vector<int> genColor(long long order, int N) {
	vector<int> colors(N, 0);
	for (int i = 0; i < N; ++i) {
		int col = order / pow(4, N-i-1) + 1;
		order %= (long long) pow(4, N-i-1);
		colors[i] = col;
	}

	/*
	for (auto color : colors) {
		cout << color << " ";
	}
	cout << endl; 
	*/
	return colors;
}

bool dfs(int node, Graph& G, vector<int>& colors, vector<bool>& visited) {
	visited[node] = true;
	// Check that node's color is different than all its neighbors
	for (int next : G.getNeighbors(node)) {
		if (colors[next] == colors[node]) {
			return false;
		}
	}
	// Check on all neighboring nodes
	bool res = true;
	for (int next : G.getNeighbors(node)) {
		if (!visited[next]) {
			if (!dfs(next, G, colors, visited)) {
				res = false;
				break;
			}
		}
	}
	return res;
}

bool isValid(Graph& G, vector<int>& colors) {
	int n = colors.size();
	vector<bool> visited(n, false);
	for (int i = 0; i < n; ++i) {
		if (visited[i]) continue;
		if(!dfs(i, G, colors, visited)) {
			return false;
		}
	}
	return true;
}

int main() {
	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int c, b;
		cin >> c >> b;
		vector<std::pair<int, int>> edges;
		for (int j = 0; j < b; ++j) {
			int u, v;
			cin >> u >> v;
			edges.push_back(std::make_pair(u, v));
		}
		Graph G(edges, c);

		vector<int> colors(c, 1);
		if (isValid(G, colors)) {
			cout << 1 << endl;
			continue;
		}

		bool flag = false;
		long long order = 0;
		while (order < pow(4, c) - 1) {
			order++;
			vector<int> color = genColor(order, c);
			if (isValid(G, colors)) {
				cout << *std::max_element(colors.begin(), colors.end()) << endl;
				flag = true;
				break;
			}
		}

		if (!flag) {
			cout << "many" << endl;
		}
	}
}