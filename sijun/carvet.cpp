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

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using StateSet = unordered_set<int>;

vector<vector<int> > grid;
vector<int> best;
int m, n;

vector<vector<int> > copy2dVec(vector<vector<int> >& vec) {
	vector<vector<int> > cp(vec.size());
	for (int i = 0; i < vec.size(); i++) {
		cp[i].resize(vec[i].size());
		for (int j = 0; j < vec[i].size(); j++) {
			cp[i][j] = vec[i][j];
		}
	}
	return cp;
}

bool compareVec(vector<int>& v1, vector<int>& v2) {
	if (v1.size() == 0)
		return false;
	if (v1.size() == v2.size()) {
		for (int i = 0; i < v1.size(); ++i) {
			if (v1[i] == v2[i])
				continue;
			return v1[i] < v2[i];
		}
	}	
	return v1.size() < v2.size();
}


void search(pii start, pii end, vector<vector<int> >& grid, vector<int> &bt, StateSet& visited) {
	visited.insert(start.first * m + start.second);
	if (grid[end.first][end.second] == -1) {
		best = compareVec(best, bt) ? best : bt;
	}

	int r = start.first; 
	int c = start.second;
	//check 4 dir
	if (c >= 2 && grid[r][c-1] != -2 && grid[r][c-1] == grid[r][c-2]) {
		bt.push_back(grid[r][c-2]);
		swap(grid[r][c-2], grid[r][c]);
		if (!visited.count(r*m+c-2)) {
			search(make_pair(r,c-2), end, grid, bt, visited);
		}
		bt.pop_back();
		swap(grid[r][c-2], grid[r][c]);
	}
	if (c+2 < n && grid[r][c+1] != -2 && grid[r][c+1] == grid[r][c+2]) {
		bt.push_back(grid[r][c+2]);
		swap(grid[r][c+2], grid[r][c]);
		if (!visited.count(r*m+c+2)) {
			search(make_pair(r,c+2), end, grid, bt, visited);
		}
		bt.pop_back();
		swap(grid[r][c+2], grid[r][c]);
	}
	if (r >= 2 &&  grid[r-1][c] != -2 && grid[r-1][c] == grid[r-2][c]) {
		bt.push_back(grid[r-2][c]);
		swap(grid[r-2][c], grid[r][c]);
		if (!visited.count(m*(r-2)+c)) {
			search(make_pair(r-2,c), end, grid, bt, visited);
		}
		bt.pop_back();
		swap(grid[r-2][c], grid[r][c]);
	}
	if (r+2 < m && grid[r+1][c] != -2 &&  grid[r+1][c] == grid[r+2][c]) {
		bt.push_back(grid[r+2][c]);
		swap(grid[r+2][c], grid[r][c]);
		if (!visited.count(m*(r+2)+c)) {
			search(make_pair(r+2,c), end, grid, bt, visited);
		}
		bt.pop_back();
		swap(grid[r+2][c], grid[r][c]);
	}
	return;
}

int main() {
	int r, c;
	cin >> m >> n;

	grid.resize(m);

	pii start;
	pii end;
	for (int i = 0; i < m; ++i) {
		grid[i].resize(n);
		for (int j = 0; j < n; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] == -1)
				start = std::make_pair(i, j);
		}
	}

	cin >> r >> c;
	end = std::make_pair(r-1, c-1);

	if (grid[r-1][c-1] == -2) {
		cout << "Impossible" << endl;
		return 0;
	}

	vector<int> bt;
	StateSet visited;
	search(start, end, grid, bt, visited);

	if (best.size() == 0) {
		cout << "Impossible" << endl;
		return 0;
	}

	for (auto e : best) {
		cout << e << " ";
	}

	cout << endl;
}