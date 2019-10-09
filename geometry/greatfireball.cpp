#include <iostream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
using namespace std;

// 1. Binary search on radius
// 2. For each radius, for each point, get the interval.
// 3. Using line sweep to find the maximum interval intersection. 

typedef std::pair<double, bool> pp;
const double PI = 3.1415926535897;
const double eps = 1e-9;

const int maxN = 100000;
int N, K;

class Point {
public:
	double x, y, r, theta;
	Point() {}
	Point(double x, double y) : x(x), y(y) {
		r = sqrt(x * x + y * y);
		theta = atan2(y, x);
		if (theta < 0) theta += 2 * PI;
	}
};

vector<Point> orcs;

std::vector<pp> getItvs(double R) {
	vector<pp> res;
	double itv1, itv2;
	for (int i = 0; i < N; ++i) {
		Point p = orcs[i];
		if (0.5 * p.r >= R)
			continue;
		itv1 = p.theta - acos(0.5 * p.r / R);
		itv2 = p.theta + acos(0.5 * p.r / R);
		if (itv1 < 0) {
			res.push_back(std::make_pair(itv1+2*PI, true));
			res.push_back(std::make_pair(2*PI, false));
			res.push_back(std::make_pair(0, true));
			res.push_back(std::make_pair(itv2, false));
		} 
		else if (itv2 > 2 * PI) {
			res.push_back(std::make_pair(itv1, true));
			res.push_back(std::make_pair(2*PI, false));
			res.push_back(std::make_pair(0, true));
			res.push_back(std::make_pair(itv2-2*PI, false));
		} else {
			res.push_back(std::make_pair(itv1, true));
			res.push_back(std::make_pair(itv2, false));	
		}
	}
	return res;
}

int sweepLine(vector<pp> itvs) {
	stable_sort(itvs.begin(), itvs.end());
	int cnt = 0;
	int max = 0;
	for (auto & itv : itvs) {
		if (itv.second == true) {
			cnt++;
			max = std::max(max, cnt);
		} else if (itv.second == false) {
			cnt--;
		}
 	}
 	return max;
}

double binSearch(double l, double r) {
	double mid = (l + r) / 2;
	if (r - l < eps) return mid;
	vector<pp> itvs = getItvs(mid);
	int k = sweepLine(itvs);
	if (k >= K) 
		return binSearch(l, mid);
	else 
		return binSearch(mid, r);
}

int main() {
	cin >> N >> K;

	orcs.resize(N);
	int x, y;
	for (int i = 0; i < N; ++i) {
		cin >> x >> y;
		Point p(x, y);
		orcs[i] = p;
	}

	double maxR = 1e10;
	double res = binSearch(0, maxR);
	if (sweepLine(getItvs(maxR)) < K) cout << -1 << endl;
	else printf("%10f", res);
}