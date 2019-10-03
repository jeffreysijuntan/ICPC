#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct edge{
    int p1;
    int p2;
    double c;
};

vector<int> pa;

int parent(int x){
    while(pa[x]!=x) x = pa[x];
    return x;
}

void uni(int a, int b){
    int ap = parent(a);
    int bp = parent(b);
    if(ap!=bp) pa[ap] = bp;
}

int cmp(edge x, edge y){
    if(x.c<y.c) return 1;
    return 0;
}
//int find(int a, int b)

int main(){
    int n, e, p;
    cin>>n>>e>>p;
    vector<pair<double, double> > t;
    for(int i=0;i<n;i++){
        double x, y;
        cin>>x>>y;
        t.push_back(make_pair(x, y));
        if(i<e) pa.push_back(0); else pa.push_back(i);
    }
    for(int i=0;i<p;i++){
        int a, b;
        cin>>a>>b;
        uni(a-1, b-1);
    }
    vector<edge> edges;
    for(int i=0; i<n; i++){
        for(int j=0; j<i; j++){
            edge ed;
            ed.p1 = i;
            ed.p2 = j;
            ed.c = sqrt((t[i].first-t[j].first)*(t[i].first-t[j].first)+
            (t[i].second-t[j].second)*(t[i].second-t[j].second));
            edges.push_back(ed);
        }
    }
    //cout<<"edges"<<edges.size()<<endl;
    double ret = 0.0;
    sort(edges.begin(), edges.end(), cmp);
    for(int i=0; i<edges.size(); i++){
        //cout<<edges[i].p1<<" "<<edges[i].p2<<" "<<edges[i].c<<endl;
        int fa = parent(edges[i].p1);
        int fb = parent(edges[i].p2);
        if(fa!=fb){
            ret+=edges[i].c;
            pa[fa]=fb;
        }
    }
    printf("%.6lf\n", ret);
    return 0;
}
