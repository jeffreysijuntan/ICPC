#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>
using namespace std;

const int INF=0x3f3f3f3f;

struct Edge { 
    int v ;  
    int flow ; 
    int C;     
    int rev ; 
}; 
  
// Residual Graph 
class Graph { 
    int V; // number of vertex 
    int *level ; // stores level of a node 
    vector<Edge> *adj; 
public : 
    Graph(int V) { 
        adj = new vector<Edge>[V]; 
        this->V = V; 
        level = new int[V]; 
    } 
  
    // add edge to the graph 
    void ae(int u, int v, int C) { 
        // Forward edge : 0 flow and C capacity 
        Edge a={v, 0, C, adj[v].size()};
  
        Edge b={u, 0, 0, adj[u].size()}; 
  
        adj[u].push_back(a); 
        adj[v].push_back(b); // reverse edge 
    } 
  
    bool BFS(int s, int t); 
    int sendFlow(int s, int flow, int t, int ptr[]); 
    int DinicMaxflow(int s, int t); 
}; 
  

bool Graph::BFS(int s, int t) { 
    for (int i = 0 ; i < V ; i++) 
        level[i] = -1; 
  
    level[s] = 0;  // Level of source vertex 
  
    queue<int> q; 
    q.push(s); 
  
    vector<Edge>::iterator i ; 
    while (!q.empty()) { 
        int u = q.front(); 
        q.pop(); 
        for (i = adj[u].begin(); i != adj[u].end(); i++) { 
            Edge &e = *i; 
            if (level[e.v] < 0  && e.flow < e.C) { 
                level[e.v] = level[u] + 1; 
  
                q.push(e.v); 
            } 
        } 
    } 

    return level[t] < 0 ? false : true ; 
} 
  
int Graph::sendFlow(int u, int flow, int t, int start[]) { 
    // Sink reached 
    if (u == t) 
        return flow; 
  
    // Traverse all adjacent edges one -by - one. 
    for (  ; start[u] < adj[u].size(); start[u]++) { 
        // Pick next edge from adjacency list of u 
        Edge &e = adj[u][start[u]];  
                                      
        if (level[e.v] == level[u]+1 && e.flow < e.C) { 
            // find minimum flow from u to t 
            int curr_flow = min(flow, e.C - e.flow); 
  
            int temp_flow = sendFlow(e.v, curr_flow, t, start); 
  
            // flow is greater than zero 
            if (temp_flow > 0) { 
                // add flow  to current edge 
                e.flow += temp_flow; 
  
                // subtract flow from reverse edge 
                // of current edge 
                adj[e.v][e.rev].flow -= temp_flow; 
                return temp_flow; 
            } 
        } 
    } 
  
    return 0; 
} 
  
// Returns maximum flow in graph 
int Graph::DinicMaxflow(int s, int t) { 
    // Corner case 
    if (s == t) 
        return -1; 
  
    int total = 0;  // Initialize result 
  
    // Augment the flow while there is path 
    // from source to sink 
    while (BFS(s, t) == true) { 
        // store how many edges are visited 
        // from V { 0 to V } 
        int *start = new int[V+1]; 
  
        // while flow is not zero in graph from S to D 
        while (int flow = sendFlow(s, INT_MAX, t, start)) 
  
            // Add path flow to overall flow 
            total += flow; 
    } 
  
    // return maximum flow 
    return total; 
} 

int main(){
	int n, k, m;
	cin>>n>>k>>m;
	Graph g = Graph(n*k+2);

	for(int i=0; i<m; i++){
		int x, y;
		cin>>x>>y;
		g.ae(x*k, (y-1)*k+1, 1);
		for(int j=2; j<=k; j++){
		 	g.ae((x-1)*k+(j-1), (y-1)*k+j, 1);
		}
	}
	for(int i=1; i<=k; i++){
		g.ae(0, (i-1)*k+i, 1);
	}
	for(int i=1; i<=k; i++){
		g.ae((n-1)*k+i, n*k+1, INF);
	}
	int fl = g.DinicMaxflow(0, n*k+1);
	cout<<fl<<endl;
	return 0;
}