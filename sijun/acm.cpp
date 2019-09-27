#include <iostream>
#include <unordered_set>
#include <map>
using namespace std;

int main() {
	int a;
	char b;
	string r;
	std::map<char, int> map;
	unordered_set<char> correct;

	cin >> a;
	while(a != -1) {
		cin >> b;
		cin >> r;
		if (r == "right") {
			correct.insert(b);
		}
		if (map.find(b) != map.end()) {
			if (r == "wrong")
				map[b] += 20;
			else map[b] += a;
		} else {
			if (r == "wrong")
				map[b] = 20;
			else map[b] = a;
		}
		cin >> a;
	}

	int count = 0;
	int res = 0;

	for (auto it = correct.begin(); it != correct.end(); ++it) {
		res+= map[*it];
		count += 1;
	}

	printf("%d %d", count, res);


	return 0;
}