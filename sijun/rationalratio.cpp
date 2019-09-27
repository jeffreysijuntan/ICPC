#include <iostream>
#include <math.h>
using namespace std;

int gcd(int a, int b) {
	if (b > a)
		a = b;
	int r = a % b;
	return gcd(b, r);
}

int main() {
	double f; int k;
	cin >> f >> k;
	string fs =  to_string(abs(f-(int)f));
	cout << fs.substr(fs.find(".")+1);
}