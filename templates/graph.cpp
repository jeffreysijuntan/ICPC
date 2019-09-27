
// Adjacency List
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


// Adjacency Matrix
class Graph {
public:
	vector<vector<int>> adjList;
	int **adjM;
	int size;

	Graph(int N) {
		size = N;
		adjM = int[N][N];
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				adjM[i][j] = 0;
			}
		}
	}

	void addEdge(int u, int v, int val) {
		adjM[u][v] = val;
	}

	vector<int> getNeighbors(int u) {
		vector<int> neighbors;
		for (int i = 0; i < size ++i) {
			if (u == i) continue;
			if (adjList[u][i]) > 0)
				neighbors.push_back(i);
		}
		return neighbors;
	}
};