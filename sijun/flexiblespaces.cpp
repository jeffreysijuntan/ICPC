#include <iostream>
#include <stdio.h>
using namespace std;

int main() {
	int W, P;
	scanf("%d %d", &W, &P);
	
	bool table[W];
	for (int i = 0; i < W; i++) {
		table[i] = false;
	}

	int Plist[P+2];
	for (int i = 1; i < P+1; i++) {
		scanf("%d", &Plist[i]);
	}
	Plist[0] = 0;
	Plist[P+1] = W;

	for (int i = 0; i < P+1; i++) {
		for (int j = i+1; j < P+2; j++) {
			table[Plist[j] - Plist[i]-1] = true;
		}
	}

	for (int i = 0; i < W; i++) {
		if (table[i] == true)
			printf("%d ", i+1);
	}

}