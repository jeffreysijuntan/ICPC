#include <iostream>
using namespace std;

#define INF 0x0fffffff

int main() {
	int n; int m; int q;

	while (true) {
		scanf("%d %d %d", &n,&m,&q);
		if (n == 0 && m == 0 && q == 0)
			break;

		int G[n][n];
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i == j) G[i][j] = 0;
				else G[i][j] = INF;
			}
		}

		int u; int v; int w;
		int dist[n][n];
	 	
		for (int i = 0; i < m; i++) {
			scanf("%d %d %d", &u, &v, &w);
			G[u][v] = min(w, G[u][v]);
		}

		for (int i = 0; i < n; i++) 
	        for (int j = 0; j < n; j++) 
	            dist[i][j] = G[i][j];

		for (int k = 0; k < n; k++) { 
	        // Pick all vertices as source one by one 
	        for (int i = 0; i < n; i++) { 
	            // Pick all vertices as destination for the 
	            // above picked source 
	            for (int j = 0; j < n; j++) { 
	                // If vertex k is on the shortest path from 
	                // i to j, then update the value of dist[i][j] 
	                if (dist[i][k] + dist[k][j] < dist[i][j] && dist[i][k] < INF && dist[k][j] < INF) 
	                    dist[i][j] = dist[i][k] + dist[k][j]; 
	            } 
	        } 
	    }

	    // detect negative cycle
	    for (int i=0;i<n;i++)
			for (int j=0;j<n;j++)
				for (int k=0;dist[i][j]!=-INF && k<n;k++)
					if (dist[k][k]<0 && dist[i][k]!=INF && dist[k][j]!=INF)
						dist[i][j] = -INF;

	    for (int i = 0; i < q; i++) {
	    	scanf("%d %d", &u, &v);
	    	if (dist[u][v] == INF) {
	    		printf("%s \n", "Impossible");
	    	} else if (dist[u][v] == -INF) {
	    		printf("%s \n", "-Infinity");
	    	} else {
	    		printf("%d \n", dist[u][v]);
	    	}
	    }

	   cout << endl;
	} 


}