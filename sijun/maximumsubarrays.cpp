#include<iostream>
#include <climits>
using namespace std;

int argmax(int arr[], int size) {
	int max = INT_MIN;
	int res = 0;
	for (int i = 0; i < size; ++i) {
		if (arr[i] > max) {
			res = i;
			max = arr[i];
		}
	}
	return res;
}

int main() {
	int n, k;
	cin >> n >> k;

	int arr[n];
	for (int i = 0; i < n; ++i) {
		cin >> arr[i];
	}

	int sum = 0;
	int totalLen = 0;
	for (int i = 0; i < k; i++) {
		int index[n];
		int maxDP[n];
		maxDP[0] = arr[0];
		index[0] = 0;
		for (int j = 1; j < n; ++j) {
			if (arr[j] == INT_MIN) {
				maxDP[j] = INT_MIN;
				index[j] = j;
			} 
			else if (maxDP[j-1] == INT_MIN) {
				maxDP[j] = arr[j];
				index[j] = j;
			}
			else {
				maxDP[j] = std::max(maxDP[j-1]+arr[j], arr[j]);
				index[j] = arr[j] >= maxDP[j-1] + arr[j] ? j : index[j-1];
			}
		}

		int amax = argmax(maxDP, n);
		sum += std::max(0, maxDP[amax]);
		cout << amax << endl;

		for (int g = 0; g < n; ++g) {
			cout << maxDP[g] << " ";
		}

		for (int l = index[amax]; l <= amax; ++l) {
			arr[l] = INT_MIN;
		}
		totalLen += amax - index[amax]+1;
		if (totalLen >= n) {
			
		}
		cout << endl;
	}
	cout << sum << endl;
}