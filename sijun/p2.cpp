#include <iostream>
using namespace std;

int main() {
	int a;
	scanf("%d", &a);

	for (int i = 0; i < a; i++) {
		printf("%d %s \n", i+1, "Abracadabra");
	}
	return 0;
}