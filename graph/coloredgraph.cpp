#include <iostream>
#include <queue>
#include <map>
#include <set>
using namespace std;

int main() {
	int N;
	scanf("%d", &N);
	map<int, set<int> > G;

	int C[N];
	for (int i = 0; i < N; i++) {
		C[i] = 1;
	}

	int v;
	char tmp;
	for (int u = 0; u < N; u++) {
		do{
        	scanf("%d%c", &v, &tmp); 
        	G[u].insert(v);
        	G[v].insert(u);
        } while(tmp!= '\n');
	}

	for (int node = 0; node < N; node++) {
		set<int> set;
		for(int i = 1; i <= G[node].size(); i++)
			set.insert(i);

		for (int nb : G[node]) {

		}
	}

	for (auto x : G) {
		cout << x.first << " ";
		for (int a : x.second) {
			cout << a << " ";
		}
		cout << endl;
	}

}