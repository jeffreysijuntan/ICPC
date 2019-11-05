#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
using namespace std;


int main() {
	int n,m;
	cin >> n >> m;
	unordered_map<string, int> mm;
	string s;
	int id = 0;
	vector<string> vec(n);
	for (int i=0; i<n; i++) {
		cin >> s;
		vec[i] = s;
		if (mm.count(s) == 0) {
			mm[s] = id;
			id += 1;
		}
	}
	int cnt[n+1][id];
	for (int i=0; i<n; i++) for (int j=0; j<id; j++) cnt[i][j] = 0;
	for (int i=0; i<n; i++) {
		for (int j=0; j<id; j++) {
			cnt[i+1][ j ] = cnt[i][ j ];
		}
		auto key = mm[vec[i]];
		cnt[i+1][ key ] += 1 ;
	}

	int l, r;
	for (int i=0; i<m; i++) {
		cin >> l >> r;
		int len = (r-l+1)/2+1 ;
		bool bad = true;
		// cout << len << endl;
		for (int j=0; j<id; j++) {
			int num = cnt[r][j] - cnt[l-1][j];
			// cout << num << " ";
			if ( num >= len) {
				cout << "usable" << endl;
				bad = false;
				break;
			}
		}
		if (bad) cout << "unusable" << endl;
		// cout << endl << endl;

	}


}