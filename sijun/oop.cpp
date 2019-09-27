#include <iostream>
using namespace std;

bool match(string p, string b) {
	int loc = p.find("*");
	int len_b = b.size();
	int len_p = p.size();

	if (len_b < len_p - 1)
		return false;

	if (loc == 0) {
		return p.substr(1, len_p-1) == b.substr(len_b-(len_p-1), len_p-1);
	} else if (loc == len_p-1) {
		return p.substr(0, len_p-1) == b.substr(0, len_p-1);
	} else {
		return p.substr(0, loc) == b.substr(0, loc) && p.substr(loc+1, len_p-loc-1) == b.substr(len_b-(len_p-loc-1), len_p-loc-1);
	}

}

int main() {
	int a, b;
	scanf("%d %d", &a, &b);

	string w[a];
	string p;


	for (int i = 0; i < a; i++) {
		cin >> w[i];
	}

	for (int i = 0; i < b; i++) {
		//scanf("%s", p);
		cin >> p;
		int count = 0;
		for (int j = 0; j < a; j++) {
			if (match(p, w[j])) count++;
		}
		printf("%d \n", count);
	}
	return 0;
}