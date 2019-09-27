#include<iostream>
#include <climits>
#include <math.h>
using namespace std;

using ll = long long;
using ld = long double;
const ll INF = 1e14;

int main() {
	int n, k;
	cin >> n >> k;

	ll arr[n];
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	ll f[n+1][k+1];
	ll g[n+1][k+1];
	// Initalize f and g
	for (int i = 0; i < n+1; ++i) {
		for (int j = 0; j < k+1; ++j) {
			f[i][j] = -INF;
			g[i][j] = -INF;
		}
	}
	f[0][0] = 0;
	g[0][0] = 0;
	for (int i = 1; i < n+1; ++i) {
		f[i][0] = 0;
		g[i][0] = 0;
		for (int j = 1; j < k+1; ++j) {
			g[i][j] = std::max(g[i-1][j]+arr[i-1], f[i-1][j-1] + arr[i-1]);
			f[i][j] = std::max(f[i-1][j], g[i][j]);
		}
	}
	cout << f[n][k] << endl;
}