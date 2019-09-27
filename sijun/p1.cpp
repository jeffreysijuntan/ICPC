#include <iostream>
using namespace std;

int main() {
	signed long long a, b;
	while (scanf("%lld %lld", &a, &b) != EOF) {
		printf("%lld \n", std::abs(a-b));
	}
	return 0;
}