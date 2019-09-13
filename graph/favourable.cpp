#include <iostream>
#include <unordered_map>
#include <utility> 
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_set>
#include <stack>
using namespace std;

// Graph was not initialized inside the right loop;
// Add duplicated nodes into the graph;
// Algorithm too inefficient;

void countPathNaive(unordered_map<int, unordered_set<int> > &G, int curr, unordered_set<int> &visited, int &count, string path){
    if (curr == 0) {
        count++;
        //cout << path << endl;
        return;
    } else if (curr == -1) {
        return;
    }
    visited.insert(curr);
    for (int vertex : G[curr]) {
        if (visited.find(vertex) == visited.end()) {
            string new_path = path + "->" + std::to_string(vertex);
            countPathNaive(G, vertex, visited, count, new_path);
        }
    }
    visited.erase(curr);
}

void topSort(unordered_map<int, unordered_set<int> > &G, int curr, stack<int> &st, unordered_set<int> &visited) {
    if (curr == 0 || curr == -1) {
    	st.push(curr);
        //return;
    }    
    visited.insert(curr);
    for (int vertex : G[curr]) {
        if (visited.find(vertex) == visited.end()) {
            topSort(G, vertex, st, visited);
        }
    }
    st.push(curr);
}

long long countPath(unordered_map<int, unordered_set<int> > &G, stack<int> &st) {
	unordered_map<int, long long> counts;
	counts[1] = 1;

    while (!st.empty()) {
        int curr = st.top();
        st.pop();
        for (int next : G[curr]) {
            if (counts.find(next) == counts.end())
                counts[next] = counts[curr];
            else
                counts[next] += counts[curr];
        }
    }

    return counts[0];
}

int main() {
    int n;
    
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int s;
        scanf("%d", &s);
        unordered_map<int, std::unordered_set<int> > G;
        
        int vertex;
        for (int j = 0; j < s; j++) {
            int a, b, c;
            char str[256];
            
            scanf("%d", &vertex);

            G.insert(pair<int,unordered_set<int> >(vertex, unordered_set<int>()));
            scanf("%s", str);

            int ret1 = strcmp(str, "favourably");
            int ret2 = strcmp(str, "catastrophically");

            if (ret1 == 0)
                G[vertex].insert(0);
            else if (ret2 == 0)
                G[vertex].insert(-1);
            else {
                a = atoi(str);
                scanf("%d %d", &b, &c);
                G[vertex].insert(a);
                G[vertex].insert(b);
                G[vertex].insert(c);
            }
        }
        
        unordered_set<int> visited;
        stack<int> st;
        topSort(G, 1, st, visited);
        long long count = countPath(G, st);
        printf("%lld \n", count);
    }
    
}