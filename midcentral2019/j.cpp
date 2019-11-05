#include <iostream>
#include <vector>
using namespace std;

int main(){
	int n;
	vector<int> a;
	cin>>n;
	for(int i=0; i<n; i++){
		int t;
		cin>>t;
		a.push_back(t);
	}
	int onepre = 0;
	int i = 0;
	int total = 0;
	while(i<n){
		long long sum = 0;
		int begin = i;
		long long prod = 1;
		while(a[i]!=1 && i<n){
			prod *= a[i];
			sum+=a[i];
			if(prod-sum!=0 && prod-sum<=onepre) total++;
			i++;
		}
		int end = i;
		int onecur = 0;
		while(a[i]==1 && i<n){
			onecur++;
			i++;
		}
		if(end-begin>=2){
			long long prodback = a[end-1]*a[end-2];
			long long sumback = a[end-1]+a[end-2];
			end = end-2;
			while(prodback-sumback<=onecur){
				total++;
				end--;
				prodback *= a[end];
				prodback += a[end];
			}
		}
		if(onecur+onepre>=prod-sum){
			int offset = 0;
			if(prod-sum<=onepre) offset--;
			if(prod-sum<=onecur) offset--;
			total+=(onecur+onepre-prod+sum)+offset+1;
		}
		cout<<onepre<<" "<<onecur<<" "<<total<<endl;
		onepre = onecur;
	}
	cout<<total<<endl;
	return 0;
}