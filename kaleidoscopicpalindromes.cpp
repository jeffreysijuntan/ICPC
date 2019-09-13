#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> toBaseK(int num, int base) {
	vector<int> vec;
	while (num != 0) {
		vec.push_back(num % base);
		num /= base;
	}
	return vec;
}

bool isPal(vector<int> &vec) {
	int i = 0;
	int j = vec.size() - 1;

	while (i <= j) {
		if (vec[i] != vec[j])
			return false;
		i++;
		j--;
	}
	return true;
}

int main() {
	int a, b, k;
	cin >> a >> b >> k;

	int ans = 0;	
	unordered_set<int> set;
	for (int i = a; i <= b; i++) {
		set.insert(i);
	}

	for (int base = 2; base <= k; ++base) {
		unordered_set<int> new_set;
		for (int i : set) {
			vector<int> vec = toBaseK(i, base);
			if (isPal(vec)) {
				new_set.insert(i);
			}
		}
		set = new_set;
		if (set.size() == 0) break;
	}
	
	cout << set.size() << endl;
}