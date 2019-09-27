#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int dist(vector<int> &ps) {
	int n = ps.size();
	int end = ps.size() - 1;

	int ans = 0;
	for (int i = 0; i < ps.size(); ++i) {
		if (i > 0 && ps[i] == ps[i-1]) {
			n--;
			continue;
		}
		int D = ps[end] - ps[i];
		ans += D * n;
		n--;
	}

	return ans;
}


int main()  {
	int n;
	cin >> n;

	vector<int> xs;
	vector<int> ys;

	xs.resize(n);
	ys.resize(n);
	
	for (int i = 0; i < n; i++) {
		cin >> xs[i] >> ys[i];
	}

	std::sort(xs.begin(), xs.end());
	std::sort(ys.begin(), ys.end());

	cout << dist(xs) << " " << dist(ys) << endl;

	cout << std::setprecision(9) << (double)(dist(xs) + dist(ys)) / (n*(n-1)) << endl;

	return 0;
}