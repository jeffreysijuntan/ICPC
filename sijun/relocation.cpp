#include <iostream>
using namespace std;

const int maxN = 100000;
const int maxQ = 100000;

int C[maxN];

int main() {
	int N, Q;
	cin >> N >> Q;
	for (int i = 0; i < N; ++i) {
		cin >> C[i]; 
	}

	int a, b, c;
	for (int i = 0; i < Q; ++i) {
		cin >> a >> b >> c;
		if (a == 1) {
			C[b-1] = c; 
		} else if (a == 2) {
			cout << abs(C[b-1] - C[c-1]) << endl;
		}
	}
}
