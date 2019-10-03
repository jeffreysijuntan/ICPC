#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int main(){
	int n;
	cin>>n;
	for(int ca=0; ca<n; ca++){
		string s1;
		string s2;
		cin>>s1>>s2;
		set<vector<int> > all;
		for(int i=0; i<s2.length(); i++){
			vector<int> temp(26, 0);
			for(int j=i; j<s2.length(); j++){
				temp[s2[j]-'a']++;
				all.insert(temp);
			}
		}
		int left = 0;
		int right = -1;
		for(int i=0; i<s1.length(); i++){
			vector<int> temp(26, 0);
			for(int j=i; j<s1.length(); j++){
				temp[s1[j]-'a']++;
				if(all.count(temp)){
					if(j-i>right-left){
						left = i;
						right = j;
					}
				}
			}
		}
		if(right==-1) cout<<"NONE"<<endl;
		else{
			for(int i=left; i<=right; i++){
				cout<<s1[i];
			}
			cout<<endl;
		}
	}
	return 0;
}
