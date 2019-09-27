#include <iostream>
using namespace std;

bool isPossible(int w, int s, int c, int k) {
	if (s < k) 
		return true;
	else if (s > k) {
		if (w + c < k)
			return true;
		if (w + c == k && s <= 2*k)
			return true;
		else
			return false;
	}
	else if (s == k) {
		if (w + c <= 2*k)
			return true;
		else
			return false;
	}
}

int main() {
	int w, s, c, k;
	cin >> w >> s >> c >> k;

	if (isPossible(w,s,c,k)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl; 
	}
}