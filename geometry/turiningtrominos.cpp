#include <iostream>
using namespace std;

int trominoShape(long x, long y, long s){
	//cout<<x<<" "<<y<<" "<<s<<endl;
	if(s==4){
		if((x==0 && y==2) || (x==0 && y==3) || (x==1 && y==3)) return 1;
		if((x==2 && y==0) || (x==3 && y==0) || (x==3 && y==1)) return 3;
		return 0;
	}
	if((x<(s>>2) && y>=(s>>1)) || (x<(s>>1) && y>=(s-(s>>2)))){
		//cout<<"lu"<<endl;
		return (trominoShape(s-1-y, x, s>>1)+9) % 4;
	}
	if((x>=(s-(s>>2)) && y<(s>>1)) || (x>=(s>>1) && y<(s>>2))){
		//cout<<"rd"<<endl;
		return (trominoShape(y, s-1-x, s>>1)+7) % 4;
	}
	if((x<(s>>2) && y<(s>>1)) || (x<(s>>1) && y<(s>>2))){
		//cout<<"ld"<<endl;
		return (trominoShape(x, y, s>>1)+8)%4;
	}
	else {
		//cout<<"mi"<<endl;
		return (trominoShape(x-(s>>2), y-(s>>2), s)+8)%4;
	}
}

int main(){
	int n;
	cin>>n;
	for(int c=0; c<n; c++){
		long x, y;
		cin>>x>>y;
		long s = 4;
		while(x>=s || y>=s || !(x<(s>>1) || y<(s>>1))) s = s << 1;
		//cout<<s<<endl;
		cout<<(trominoShape(x, y, s)+8) % 4<<endl;
	}
	return 0;
}
