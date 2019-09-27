#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
	// adjM is the flight capacity
	std::vector<vector<int> > adjM;
	std::vector<int> vertices;
	int s; //num of vertices

	Graph(int N) {
		s = N;
		adjM.resize(N);
		vertices.resize(N);
		for (auto& row : adjM) {
			row.resize(N);
		}
		for (int i = 0; i < N; ++i) {
			vertices[i] = 0;
			for (int j = 0; j < N; ++j) {
				adjM[i][j] = 0;
			}
		}
	}

	void clearEdges() {
		for (int i = 0; i < s; ++i) {
			for (int j = 0; j < s; ++j) {
				adjM[i][j] = 0;
			}
		}
	}

	int getOutEdgeSum(int u) {
		int sum = 0;
		for (int i = 0; i < s; ++i) {
			auto edge = adjM[u][i];
			sum += edge;
		}
		return sum;
	}

	int getInEdgeSum(int u) {
		int sum = 0;
		for (int i = 0; i < s; ++i) {
			auto edge = adjM[i][u];
			sum += edge;
		}
		return sum;
	}

	int getVertex(int v) {
		return vertices[v];
	}

	void updateEdge(int u, int v, int cap) {
		adjM[u][v] = cap;
	}

	void updateVertex(int node, int val) {
		vertices[node] = val;
	}

	vector<int> getNeighbors(int u) {
		vector<int> neighbors;
		for (int i = 0; i < s; ++i) {
			if (u == i) continue;
			if (adjM[u][i] > 0)
				neighbors.push_back(i);
		}
		return neighbors;
	}

	int size() {
		return s;
	}
};

bool checkOptimal(Graph &G) {
	for (int i = 0; i < G.size(); ++i) {
		int in = G.getVertex(i);
		int out = G.getOutEdgeSum(i);
		//cout << i << " " << in << " " << out << endl;
		if (in < out)
			return false;
	}
	return true;
} 

void updateG(Graph &G) {
	for (int i = 0; i < G.size(); ++i) {
		int out = G.getOutEdgeSum(i);
		int in = G.getInEdgeSum(i);
		G.updateVertex(i, G.getVertex(i) + in - out);
	}
	G.clearEdges();
}

int main() {
	int k, m, n;
	cin >> k >> m >> n;

	int u, v, day, val;
	Graph G(k);

	// Initialize allEdges. It will store all the edges across timestep
	int allEdges[n][k][k];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			for (int l = 0; l < k; ++l) {
				allEdges[i][j][l] = 0;
			}
		}
	}

	for (int i = 0; i < m; ++i) {
 		cin >> u >> v >> day >> val;
 		allEdges[day-1][u-1][v-1] = val;
	}

	// Initalize allNodes which stores all number of people arriving at each nodes across timestep
	int a, b, c; 
	int allNodes[n][k];
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			allNodes[i][j] = 0;
		}
	}

	for (int i = 0; i < k*n; ++i) {
		cin >> a >> b >> c;
		allNodes[b-1][a-1] += c;
	}

	bool isOpt = true;
	for (int i = 0; i < n; ++i) {
		// Every day, new people flowing in, new flights going out
		for (int j = 0; j < k; ++j) {
			G.updateVertex(j, allNodes[i][j]+G.getVertex(j));
			for (int l = 0; l < k; ++l) {
				G.updateEdge(j, l, allEdges[i][j][l]);
			}
		}
		if (!checkOptimal(G)) {
			isOpt = false;
			break;
		}
		updateG(G);
	}

	if (isOpt)
		cout << "optimal" << endl;
	else
		cout << "suboptimal" << endl;

}