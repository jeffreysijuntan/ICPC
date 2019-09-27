#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace std;

int main() {
	int a;
	scanf("%d", &a);

	for (int i = 0; i < a; i++) {
		std::string str;
		cin >> str;
		int M = ceil(sqrt(str.size()));

		char table[M][M];
		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (M * i + j < str.size())
					table[j][M-1-i] = str[M * i + j];
				else
					table[j][M-1-i] = '*';
			}
		}

		for (int i = 0; i < M; i++) {
			for (int j = 0; j < M; j++) {
				if (table[i][j] != '*'){
					printf("%c", table[i][j]);
				}
			}
		}

		cout << endl;
	}

	return 0;
}