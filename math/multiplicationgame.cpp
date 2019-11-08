#include <iostream>
#include <vector>
using namespace std;
const int maxn=6e+5;

int main(){
	int num;
	vector<int> prime;
	vector<int> tmp(maxn, 0);
	tmp[1]=1;
	for(int i=2; i<maxn; i++){
		if(tmp[i]==0) prime.push_back(i);
		for(int j=i*2; j<=maxn; j+=i) {
                tmp[j]=1;
            }
	}
	cin>>num;
	for(int i = 0; i<num; i++){
		int n;
		int flag = 0;
		string s;
		cin>>n>>s;
		int count = 0;
		vector<int> m;
		int k = 0;
		while(count<3 && k<prime.size()){
			if(n % prime[k] == 0){
				//cout<<prime[k]<<endl;
				count++;
				int c = 0;
				while(n%prime[k]==0){
					n/=prime[k];
					c++;
				}
				m.push_back(c);
			}
			//cout<<"k"<<k<<endl;
			k++;
		}
		//cout<<"c"<<count<<endl;
		if(n>1){
            count++;
            m.push_back(1);
        }
		if(count==2){
			if(m[0]==m[1]) flag = 2;
			if(abs(m[0]-m[1])==1) flag = 1;
		}
		if(count==1){
			if(m[0]%2==0) flag = 2;
			if(m[0]%2==1) flag = 1;
		}
		if(flag==0) cout<<"tie"<<endl;
		else if(s=="Alice" && flag==1) cout<<"Alice"<<endl;
		else if(s=="Alice" && flag==2) cout<<"Bob"<<endl;
		else if(s=="Bob" && flag==1) cout<<"Bob"<<endl;
		else cout<<"Alice"<<endl;
	}
	return 0;
}