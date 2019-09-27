#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

bool dfs(int i, int sink, int **resG, std::unordered_set<int>& visited, std::vector<int>& path) {
	if (i == sink) {
		return true;
	}
	for (int j = 0; j < 4; j++) {
		if (!visited.count(j) && resG[i][j] > 0) {
			visited.insert(j);
			if (dfs(j, sink, resG, visited, path)) {
				path.push_back(j);
				return true;
			}
		}
	}
	return false;
} 

void printGraph(int **graph) {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << endl;
	}
}

void updateFlow(int **flow, std::vector<int> path) {

	for (auto i: path)
		cout << i << endl;

	// Find the amount of flow available to add, must be smaller than what the source node could offer
	int inc = flow[0][0];
	for (int i = 0; i < path.size() - 1; ++i) {
		inc = std::min(inc, flow[path[i+1]][path[i]]);
	}
	flow[0][0] -= inc;
	cout << "flow increment: " << inc << endl;
	// Update the flow
	for (int i = 0; i < path.size() - 1; ++i) {
		flow[path[i]][path[i+1]] += inc;
		flow[path[i+1]][path[i]] -= inc;
	}
	flow[3][3] += inc;
}

void maxFlow(int **graph) {
	// Iteratively find an available path
	while (true) {
		std::unordered_set<int> visited;
		std::vector<int> path;
		if (dfs(0, 3, graph, visited, path)){
			updateFlow(graph, path);
			cout << endl;
			printGraph(graph);
		} else {
			break;
		}
	}
}

int main() {
	int **graph;
	graph = new int *[4];
	for (int i = 0; i < 4; ++i) {
		graph[i] = new int[4];
	}

	int tmp[4][4] = {{5,3,2,0}, 
					 {0,0,3,2},
				     {0,0,0,3},
				     {0,0,0,0}};

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			graph[i][j] = tmp[i][j];
		}
	}

	maxFlow(graph);
}