#include<stdio.h>
#include <string.h>
#include<vector>
#include <iostream>
#include <unordered_map>
using namespace std;

int cal(int a, int b, char c){
    if(c=='+') return a+b;
    if(c=='-') return a-b;
    if(c=='*') return a*b;
    if(c=='/') return a/b;
    return 0;
}

int main(){
    string s = "+-*/";
    char n[300];
    unordered_map<int, string> ans;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            for(int k=0;k<4;k++){
                vector<int> num = {4, 4, 4, 4};
                vector<char> op = {s[i], s[j], s[k]};
                for(int q=0; q<op.size(); q++){
                    if(op[q] == '*' || op[q] == '/'){
                        num[q] = cal(num[q], num[q+1], op[q]);
                        num.erase(num.begin()+q+1);
                        op.erase(op.begin()+q);
                        q--;
                    }
                }
                for(int q=0;q<op.size(); q++){
                    num[q] = cal(num[q], num[q+1], op[q]);
                    num.erase(num.begin()+q+1);
                    op.erase(op.begin()+q);
                    q--;
                }
                string tt = "4 ";
                ans[num[0]] = tt + s[i] + " 4 " + s[j] + " 4 " + s[k] + " 4 = " + to_string(num[0]);
            }
        }
    }

    int ip;
    scanf("%d", &ip);
    for(int i=0;i<ip;i++){
        int nn;
        scanf("%d", &nn);
        if(ans.count(nn)!=0) cout<<ans[nn]<<endl;
        else printf("no solution\n");
    }
    return 0;
}
