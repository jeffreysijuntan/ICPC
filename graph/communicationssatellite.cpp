#include <iostream>
#include <algorithm>
#include <math.h>
#include <vector>
#include <stdio.h>
using namespace std;

const int maxN = 2000;

int X[maxN];
int Y[maxN];
int R[maxN];

int n;

class Point {
public:
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator - (const Point& b) {
    	return Point(x-b.x, y-b.y);
    }
};

inline int dot(const Point& p1, const Point& p2) {
    return p1.x * p2.x + p1.y + p2.y;
}

inline double dist(const Point& p1, const Point& p2) {
	return sqrt(pow((p1.x - p2.x),2) + pow(p1.y-p2.y, 2));
}

inline double norm(const Point& p1, const Point& p2) {
	return pow((p1.x - p2.x),2) + pow(p1.y-p2.y, 2);
}

struct Segment {
	Point p1, p2;
	Segment() {}
	Segment(Point p1, Point p2) : p1(p1), p2(p2) {}
};

inline double dist(Point& p, Segment& s) {
	double base = dot((s.p1 - p), (s.p2 - s.p1)) / (dist(s.p1,p) * dist(s.p2, s.p1));
	return sqrt(norm(s.p1, p) - base * base);
}

struct Edge {
	int src,trg;
	double d;
	Edge(int src, int trg, double d) : src(src), trg(trg), d(d) {}
};

inline bool operator < (const Edge& a, const Edge& b) {
	return a.d < b.d;
}

int find(int parent[], int i)  
{  
    if (parent[i] == -1)  
        return i;  
    return find(parent, parent[i]);  
}  
  
// A utility function to do union of two subsets  
void Union(int parent[], int x, int y)  
{  
    int xset = find(parent, x);  
    int yset = find(parent, y);  
    if(xset != yset) 
    {  
        parent[xset] = yset;  
    }  
}  

// Check if edge cross circles;
bool valid(int u, int v) {
	if (u > v) swap(u, v);
	int xu, yu, xv, yv;
	xu = X[u]; yu = Y[u]; xv = X[v]; yv = Y[v];
	Point p1(xu, yu);
	Point p2(xv, yv);
	Segment s(p1, p2);
	
	int x, y, r;
	for (int i = 0; i < n; ++i) {
		x = X[i]; y = Y[i]; r = R[i];
		Point c(x, y);
		if (dist(c, s) < r) {
			return false;
		}
	}
	return true;
}

void mst(vector<Edge> &edges) {
	double cost = 0.0;
	sort(edges.begin(), edges.end());
	
	int parent[n];
	for (int i = 0; i < n; ++i) {
		parent[i] = -1;
	}

	for (int i = 0; i < edges.size(); ++i) {
		Edge e = edges[i];
		//cout << e.src << " " << e.trg << " " << e.d << endl;
		if (find(parent, e.src) != find(parent, e.trg)) {
			Union(parent, e.src, e.trg);
			if (valid(e.src, e.trg))
				cost += e.d;
		}
	}
	printf("%f", cost);
} 

// Modificatio of minimum spanning tree
// For every greedy step, test if the edge is valid.
int main() {
	cin >> n;

	int x, y, r;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y >> r;
		X[i] = x;
		Y[i] = y;
		R[i] = r;
	}

	vector<Edge> edges;

	// compute pairwise distance
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			double d = sqrt(pow(X[i]-X[j],2)+pow(Y[i]-Y[j], 2)) - R[i] - R[j];
			Edge edge(i, j, d);
			edges.push_back(edge);
		}
	}
	mst(edges);
}