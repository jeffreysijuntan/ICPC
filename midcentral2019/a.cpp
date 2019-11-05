#include <iostream>
#include <string>
using namespace std;

int main(){
	string s;
	cin>>s;
	int a=0, b=0, flag = 0;
	for(int i=0; i<s.length(); i+=2){
		//cout<<s[i]<<endl;
		//cout<<a<<" "<<b<<endl;
		if(s[i]=='A') a+=s[i+1]-'0';
		if(s[i]=='B') b+=s[i+1]-'0';
		if(a==10 && b==10) flag=1;
		if(flag==1){
			if(a-b>=2) {
				cout<<"A"<<endl;
				return 0;
			}
			if(b-a>=2) {
				cout<<"B"<<endl;
				return 0;
			}
		}
		if(flag==0){
			if(a>=11){
					cout<<"A"<<endl;
					return 0;
				}
			if(b>=11) {
				cout<<"B"<<endl;
				return 0;
			}
		}
	}
	return 0;
}