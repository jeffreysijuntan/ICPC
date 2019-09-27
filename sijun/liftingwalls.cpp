#include <iostream>
#include <stdio.h>
#include <math.h>
#include <unordered_set>
using namespace std;

int main() {
	int l, w, n, r;
	scanf("%d %d %d %d", &l, &w, &n, &r);
	int xs[n], ys[n];
	for (int i = 0; i < n; ++i) {
		cin >> xs[i];
		cin >> ys[i];
	}

	int xwall[4] = {(-l/2), (l/2), 0, 0};
	int ywall[4] = {0, 0, (-w/2), (w/2)};

	//Sets containing all the walls that can be reached by candidate i;
	unordered_set<int> sets[n];
	// You know max must be 4. So start with 1
	// First calculate the distance
	bool reachWall[4] = {false, false, false, false};
	for (int i = 0; i < n; ++i) {
		int x = xs[i];
		int y = ys[i];
		bool reachAll = true;
		for (int j = 0; j < 4; ++j) {
			int xw = xwall[j];
			int yw = ywall[j];
			double dist = sqrt((x-xw) * (x-xw) + (y-yw) * (y-yw));
			if (dist < r) {
				sets[i].insert(j);
				reachWall[j] = true;
			} else {
				reachAll = false;
			}
		}
		if (reachAll) {
			cout << 1 << endl;
			return 0;
		}
	}

	for (int w = 0; w < 4; ++w) {
		if (reachWall[w] == false) {
			cout << "Impossible" << endl;
			return 0;
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			bool reachAll = true;
			for (int w = 0; w < 4; ++w) {
				if (!sets[i].count(w) && !sets[j].count(w)) {
					reachAll = false;
					break;
				}
			}
			if (reachAll) {
				cout << 2 << endl;
				return 0;
			}
		}
	}

	for (int i = 0; i < n; ++i) {
		for (int j = i+1; j < n; ++j) {
			for (int k = j+1; k < n; ++k) {
				bool reachAll = true;
				for (int w = 0; w < 4; ++w) {
					if (!sets[i].count(w) && !sets[j].count(w) && !sets[k].count(w)) {
						reachAll = false;
						break;
					}
				}
				if (reachAll) {
					cout << 3 << endl;
					return 0;
				}
			}
		}
	}

	cout << 4 << endl;
	return 0;
}