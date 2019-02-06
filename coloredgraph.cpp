#include <iostream>
#include <queue>
using namespace std;

int dfs() {

}

int main() {
	int N;
	scanf("%d", N);
	map<int, vector<int>> G;

	int v;
	char tmp;
	for (int u = 0; u < N; u++) {
		do {
			scanf("%d%c", &v, &tmp);
			M[u][v] = 1;
			M[v][u] = 1;
		} while (tmp != "\n");
	}

	bool visited[N];
	for (int i = 0; i < N; ++1) {
		visited[i] = false;
	}

	bfs()

}