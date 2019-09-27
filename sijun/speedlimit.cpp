#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	int hrs;
	while (true) {
		scanf("%d", &hrs);
		if (hrs == -1)
			break;
		
		int prev = 0;
		int ans = 0;
		for (int i = 0; i < hrs; i++) {
			int avgm, tot;
			scanf("%d %d", &avgm, &tot);
			ans += (tot - prev) * avgm;
			prev = tot;
		}
		printf("%d miles \n", ans);
	}
}