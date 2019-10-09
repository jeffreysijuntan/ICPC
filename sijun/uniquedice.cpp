#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
using namespace std;

// rotate the dice up
string up(string d) {
	int tmp = d[0];
	d[0] = d[2];
	d[2] = d[1];
	d[1] = d[3];
	d[3] = tmp;
	return d;
}

// rotate the dice right
string right(string d) {
	int tmp = d[2];
	d[2] = d[4];
	d[4] = d[3];
	d[3] = d[5];
	d[5] = tmp;
	return d;
}

string front(string d) {
	int tmp = d[0];
	d[0] = d[4];
	d[4] = d[1];
	d[1] = d[5];
	d[5] = tmp;
	return d;
}

string getUniqueDice(string d) {
	string res = "999999";
	queue<string> q;
	q.push(d);
	unordered_set<string> visited;
	while (!q.empty()) {
		string curr = q.front(); q.pop();
		if (visited.count(curr)) continue;
		q.push(up(curr));
		q.push(right(curr));
		q.push(front(curr));
		visited.insert(curr);
	}
	for (auto& v : visited) {
		res = min(res, v);
	}
	return res;
}

int main() {
	int n;
	cin >> n;
	
	// Find the min representation of the dice and add 1 to the bucket size
	unordered_map<string,int> bucket;

	for (int i = 0; i < n; ++i) {
		string dice = "";
		string t;
		for (int j = 0; j < 6; ++j) {
			cin >> t;
			dice += t;
		}
	    string uni = getUniqueDice(dice);
		if (!bucket.count(uni))
			bucket[uni] = 1;
		else
			bucket[uni]++;
	}

	int best = 0;
	for (auto &p : bucket) {
		best = max(best, p.second);
	}
	cout << best << endl;
}
