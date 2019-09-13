#include <iostream>
using namespace std;

int main() {
	int n;
	scanf("%d", &n);
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		printf("%lu \n", s.size());
	}
}