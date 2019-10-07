#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int INF=numeric_limits<int>::max();

struct edge {
	int fr;
	int to;
	int ca;
	int fl;
	int co;

	edge(int a, int b, int c, int d, int e){
		fr = a;
		to = b;
		ca = c;
		fl = d;
		co = e;
	}
};

struct MinCostMaxFlow {
	int mf;
	int mc;
	vector<vector<int> > g;
	vector<edge> es;
	int v;
	vector<int> ch;
	vector<int> p;

	MinCostMaxFlow(int a){
		mf = 0;
		mc = 0;
		v = a;
		for(int i=0; i<v; i++){
			vector<int> tmp;
			g.push_back(tmp);
			ch.push_back(INF);
			p.push_back(0);
		}
	}

	void ae(int a, int b, int c, int d){
		edge e1(a, b, c, 0, d);
		edge e2(b, a, c, c, -d);
		es.push_back(e1);
		es.push_back(e2);
		g[a].push_back(es.size()-2);
		g[b].push_back(es.size()-1);
	}

	int bellmanFord(int s, int t){
		queue<int> q;
		vector<int> f(v, 0);
		vector<int> d(v, INF);
		d[s] = 0;
		f[s] = 1;
		ch[s] = INF;
		p[s] = -1;
		q.push(s);
		while(!q.empty()){
			int i = q.front();
			q.pop();
			f[i] = 0;
			for(int j = 0; j<g[i].size(); j++){
				edge e = es[g[i][j]];
				if(e.ca>e.fl && d[e.to]>d[i]+e.co){
					d[e.to] = d[i] + e.co;
					p[e.to] = g[i][j];
					ch[e.to] = min(ch[i], e.ca-e.fl);
					if(f[e.to]==0) {
						q.push(e.to);
						f[e.to] = 1;
					}
				}
			}
		}
		if(d[t]==INF) return 0;
		mf += ch[t];
		mc += d[t]*ch[t];
		for(int i=t; i!=s; i=es[p[i]].fr){
			es[p[i]].fl += ch[t];
			es[p[i]^1].fl -= ch[t];
		}
		return 1;
	}

	void MCMF(int s, int t){
		while(bellmanFord(s, t));
	}
};

int main(){
	int p, r, l;
	cin>>p>>r>>l;
	MinCostMaxFlow g = MinCostMaxFlow(r+4);
	//r is left bank, r+1 is right bank
	//r+2 is source, r+3 is sink;
	g.ae(r+2, r, p, 0);
	g.ae(r+1, r+3, p, 0);
	for(int i=0; i<l; i++){
		int a, b;
		cin>>a>>b;
		if(a==-2) a = r;
		if(a==-1) a = r+1;
		if(b==-2) b = r;
		if(b==-1) b = r+1;
		g.ae(a, b, 1, 1);
		g.ae(b, a, 1, 1);
	}
	g.MCMF(r+2, r+3);
	if(g.mf==p) cout<<g.mc<<endl;
	else cout<<p-g.mf<<" people left behind"<<endl;
	return 0;
}
