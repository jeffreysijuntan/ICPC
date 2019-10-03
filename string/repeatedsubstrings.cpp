#include<iostream>
#include<string>
#include <vector>
#include <algorithm>
using namespace std;

struct suffix{
	int rank1;
	int rank2;
	int index;
};

int cmp(suffix a, suffix b){
	if(a.rank1<b.rank1)
		return 1;
	if(a.rank1>b.rank1)
		return 0;
	return a.rank2<b.rank2;
}

int main(){
	string s;
	cin>>s;
	//cout<<s.length();
	vector<suffix> arr;
	vector<int> r;
	for(int i=0; i<s.length(); i++){
		r.push_back(s[i]-'a');
	}
	for(int i=1, exp=2; (exp>>1)<s.length(); i++, exp<<=1){
		arr.clear();
		for(int j=0; j<s.length(); j++){
			suffix x;
			x.rank1 = r[j];
			x.rank2 = j+exp/2>=s.length()?-1:r[j+exp/2];
			x.index = j;
			arr.push_back(x);
		}
		sort(arr.begin(), arr.end(), cmp);
		//for(int i=0; i<r.size(); i++) cout<<r[i]<<"   "; cout<<endl;
		//for(int i=0; i<r.size(); i++) cout<<arr[i].rank1<<" "<<arr[i].rank2<<"  "<<arr[i].index<<"   "; cout<<endl;
		int c = -1;
		for(int j=0; j<arr.size(); j++){
			//r[arr[j].index] = j;
			if(j>0 && arr[j].rank1==arr[j-1].rank1 && arr[j].rank2==arr[j-1].rank2) 
				r[arr[j].index] = c;
			else r[arr[j].index] = ++c;
		}
	}
	// for(int i=0; i<r.size(); i++) cout<<r[i]<<" "<<arr[i].index<<endl;
	int maxs = 0;
 	int maxi = 0;
 	int k=0;
 	int rankk = -1;
 	for(int i=0; i<s.length(); i++){
 		if(r[i]==0) {
 			k=0;
 			continue;
 		}
 		//cout<<i<<endl;
 		int s1 = i;
 		int s2 = arr[r[i]-1].index;
 		while(s1+k<s.length() && s2+k<s.length() && s[s1+k]==s[s2+k]){
 			k++;
 		}
 		if(k>maxi) {
 			maxi = k;
 			maxs = s1;
 			rankk = r[i];
 		}
 		else if(k==maxi && rankk>r[i]){
 			maxi = k;
 			maxs = s1;
 			rankk = r[i];
 		}
 		if(k>0) k--;
 	}
 	//cout<<maxi<<" "<<maxs<<endl;
 	for(int i=maxs; i<maxs+maxi; i++){
 		cout<<s[i];
 	}
 	cout<<endl;
 	return 0;
} 