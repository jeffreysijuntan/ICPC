#include <iostream>
#include <algorithm>
#include <stdio.h>
using namespace std;

int main() {
	bool board[8][8];
	bool valid = true;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = true;
		}
	}

	string s;
	for (int i = 0; i < 8; ++i) {
		cin >> s;

		std::size_t n = std::count(s.begin(), s.end(), '*');
		if (n > 1 || n == 0) {
			valid = false;
			printf("%s", "invalid");
			break;
		}			

		int pos = s.find("*");
		
		if (board[i][pos] == false) {
			valid = false;
			printf("%s", "invalid");
			break;
		} else {
			board[i][pos] = false;
			for (int j = 0; j < 8; ++j) {
				board[j][pos] = false;
			}
			for (int j = i+1; j < 8; ++j) {
				if (pos + j - i < 8)
					board[j][pos+j-i] = false;
				if (pos - j + i >= 0) {
					board[j][pos-j+i] = false;
				}
			}
		}
		
	}

	if (valid)
		printf("%s", "valid");
	
	return 0;
}