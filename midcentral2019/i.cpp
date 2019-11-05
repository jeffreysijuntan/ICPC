#include <iostream>
#include <string>
using namespace std;

int main(){
	string s, p;
	cin>>s>>p;
	if(s==p){
		cout<<"Yes"<<endl;
		return 0;
	}
	if('0'<=s[0] && s[0]<='9' && s.substr(1)==p){
		cout<<"Yes"<<endl;
		return 0;
	}
	if('0'<=s[s.length()-1] && s[s.length()-1]<='9' && s.substr(0, s.length()-1)==p){
		cout<<"Yes"<<endl;
		return 0;
	}
	if(s.length()!=p.length()){
		cout<<"No"<<endl;
		return 0;
	}
	for(int i=0; i<s.length()-1; i++){
		if('0'<=s[i] && s[i]<='9' && s[i]==p[i]) continue;
		if('a'<=s[i] && s[i]<='z' && s[i]==p[i]+32) continue;
		if('A'<=s[i] && s[i]<='Z' && s[i]+32==p[i]) continue;
		cout<<"No"<<endl;
		return 0;
	}
	cout<<"Yes"<<endl;
	return 0;
}