#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
typedef long long ll;

ll factor(ll a) {
	ll prod = 1;
	for (ll i=2; i<=a; i++){
		prod *= i;
	}
	return prod;
}

int main(){
	ll n, k;
	cin >> n >> k;
	k--;

	vector<int>order(n-1, 0);
	if (n-2 < 20) {
		ll num = factor(n-2);
		for (ll p=n-2; p>0; p--){
			// if( num == 0) {
			// 	cout << "num zero" << endl;
			// 	exit(0);
			// }
			order[p] = k/num;
			k = k % num;
			num /= p; 
		}
	}else{
		for (ll p = n-2; p>40; p--) order[p] = 0;
		ll num = factor(20);
		for (ll p=20; p>0; p--){
			// if( num == 0) {
			// 	cout << "num zero" << endl;
			// 	exit(0);
			// }
			order[p] = k/num;
			k = k % num;
			num /= p; 
		}		
	}
	

	vector<bool> last(n, false);
	last[0] = true;

	// for (ll i=0; i<n;i++) cout << i << "\t";
	// cout << endl;
	for (ll p=n-2; p>0; p--){
		ll res = order[p];
		// cout << p << ":" << num << "..." << k << "|" << res<< endl;
		// for (ll i=0; i<n;i++) cout << last[i] << "\t";
		// cout << endl;
		
		ll c = 0;
		for (ll i=0; i<=res; i++) {
			c++;
			while(last[n-c]) {
				c++;
				// if( (n-c < 0) ) exit(0);
			}
		} 
		cout << c << " ";
		// cout << endl;
		vector<bool> new_last(n, false);
		new_last[0] = true;
		for (ll i=0; i<n; i++){
			if (last[i]) new_last[ (i+c)%n ] = true;
		}
		last = new_last;
	}
	// cout << 0 << ":" << num << "..." << k << "|"  << endl;
	// for (ll i=0; i<n;i++) cout << last[i] << "\t";
 //    cout << endl;
	
	for (ll i=0; i<n;i++) {
		if (!last[i]) {
			cout << n-i << endl;
		}
	}

}
