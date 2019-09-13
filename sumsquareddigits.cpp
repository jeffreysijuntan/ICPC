#include <iostream>
#include <vector>
using namespace std;

vector<int> compute(int n, int b) {
	vector<int> ans;
	while (n != 0) {
		ans.push_back(n % b);
		n /= b;
	}
	return ans;
}

int main() {
	int P;
	scanf("%d", &P);

	int K, b, n;

	for (int i = 0; i < P; i++) {
		scanf("%d %d %d", &K, &b, &n);
		vector<int> ans = compute(n, b);
		long long sum = 0;
		for (int i = 0; i < ans.size(); i++) {
			sum += ans[i] * ans[i];
		}
		printf("%d %lld \n", K, sum);
	}


	return 0;
}