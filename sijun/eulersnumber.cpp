#include <iostream>
#include <iomanip>
using namespace std;

int main() {
	int n;
	cin >> n;

	if (n == 0)
		cout << 1 << endl; 

	int k = 1;
	long double prod = 1;
	long double ans = 1;

	if (n > 30)
		n = 30;

	for (int i = 1; i <= n; ++i) {
		prod *= i;
		ans += 1 / prod;
	}

	cout << fixed;
    cout.precision(15);
    cout << ans << endl;

	//cout << std::setprecision(200) << ans << endl;
}