#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
using namespace std;

typedef pair<long long, long long> pii;
//typedef map<pair<long long, long long>, long long> dmap;
// #define long long long long64_t;
// using  long long = long long;

long long n, m;
const long long INF = 2000000001;
const long long N=200001;
vector<pii> edges[N];
vector<long long> dist(N, INF);


long long dij(long long s, long long t) {
	priority_queue<pii, vector<pii>, greater<pii>> Q;
	Q.push({0, s});
	for(long long i = 0; i < n; ++i) dist[i] = INF;
	dist[s] = 0;
	while (!Q.empty()) {
		pii p = Q.top();
		Q.pop();
		long long here = p.second;
		if (dist[here] != p.first) continue;
		for (vector<pii>::iterator it = edges[here].begin(); it != edges[here].end(); it++) {
			if (dist[here] + it->first < dist[it->second]) {
				dist[it->second] = dist[here] + it->first;
				Q.push({dist[it->second], it->second});
			}
		}
	}
	auto v = dist[t];
	return v;
}

int main() {
	cin >> n >> m;

	// edges.resize(n);
	//for (long long i=0; i<n; ++i) edges[i] = vector<long long>();

	for (long long i = 0; i < m; ++i) {
		long long u, v, dist;
		cin >> u >> v >> dist;
		edges[u].push_back({dist, v});
		edges[v].push_back({dist, u});
	}

	// cout << "a";

	set<long long> db;
	// db.insert(6);
	for (long long i = 0; i < 7; ++i) {
		long long loc;
		cin >> loc;
		if (loc != 1) db.insert(loc);
	}

	// // cout << "b";

	vector<long long> vec(db.begin(), db.end());
	if (vec.size() == 0){
		cout << 0 << endl;
		return 0;
	}

	sort(vec.begin(), vec.end());

	// cout << "b";
	map<pii, long long> dmap;

	for (long long i = 0; i < vec.size(); ++i) {
		dmap.insert({{1, vec[i]}, dij(1, vec[i])});
		for (long long j = 0; j < vec.size(); ++j) {
			long long s = vec[i]; long long t = vec[j];
			if (s == t) continue;
			dmap.insert({{s,t}, dij(s,t)});
		}
	}

	// cout << "c";

	long long minD = INF;

	do {
		long long s, t;

		long long dist = dmap[{1, vec[0]}];
		if (dist >= INF) continue;

		bool infdist = false;
		for (long long i = 0; i < vec.size()-1; ++i) {
			s = vec[i];
			t = vec[i+1];
			long long d = dmap[{s, t}];
			if (d >= INF) {
				infdist = true;
				break;
			}
			dist += d;
		}

		if (infdist) continue;
		minD = min(dist, minD);
	} while (next_permutation(vec.begin(), vec.end()));


	if (minD < INF) 
		cout << minD;
	else
		cout << -1;
}
