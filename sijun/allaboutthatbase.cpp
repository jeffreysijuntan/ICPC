#include <iostream>
#include <math.h>
#include <climits>
using namespace std;

bool isValid(int num1, int num2, int res, char op) {
	if (num1 == -1 || num2 == -1 || res == -1) {
		return false;
	}
	if (op == '+') {
		return num1 + num2 == res;
	}
	else if (op == '-') {
		return num1 - num2 == res;
	}
	else if (op == '*') {
		return num1 * num2 == res;
	}
	else if (op == '/') {
		return (float) num1 / num2 == res;
	}
	return false;
}

int charToInt(char digit) {
	if (isdigit(digit)) {
		return (int)digit - (int)'0';
	}
	if (isalpha(digit)) {
		return 10 + (int)digit - (int)'a';
	}
	return -1;
}

int toBase10(string num, int base) {
	int res;
	for (int i = 0; i < num.size(); ++i) {
		int digit = charToInt(num[i]);
		
		if (base == 1 && digit != 1) {
			return -1;
		}
		else if (base != 1 && digit >= base) {
			return -1;
		}
		res += digit * pow(base, num.size()-i-1);
	}
	return res;
}

char intToChar(int digit) {
	if (digit == 36) {
		return '0';
	}
	if (digit < 10) {
		return '0' + digit;
	}
	if (digit >= 10) {
		return (char) ((int)'a' + digit - 10);
	}
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		string num1, num2, eql, res;
		char op;
		cin >> num1 >> op >> num2  >> eql >> res;

		string resString = "";
		for (int base = 1; base <= 36; ++base) {
			int n1 = toBase10(num1, base);
			int n2 = toBase10(num2, base);
			int n3 = toBase10(res, base);
			if (isValid(n1, n2, n3, op)) {
				resString += intToChar(base);
			}
		}
		if (resString == "")
			cout << "invalid" << endl;
		else
			cout << resString << endl;
	}
}