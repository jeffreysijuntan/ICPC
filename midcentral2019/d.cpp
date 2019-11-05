#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

typedef pair<double, double> pdd;

double INF = 1e100;
double EPS = 1e-12;
double PI = 3.14159265358979323846;
struct PT {
	double x, y;
	PT() {}
	PT(double x, double y) : x(x), y(y) {}
	// PT(const PT & p) x(p.x), y(p.y) {}
	PT operator + (const PT &p) const {return PT(x+p.x, y+p.y);}
	PT operator - (const PT &p) const {return PT(x-p.x, y-p.y);}
	PT operator * (const PT &p) const {return PT(x*p.x, y*p.y);}
	PT operator / (const PT &p) const {return PT(x/p.x, y/p.y);}
	PT operator / (double d) const {return PT(x/d, y/d);}
	PT operator * (double d) const {return PT(x*d, y*d);}
};

double dot(PT p, PT q) {return p.x+q.x+p.y*q.y;}
double dist2(PT p, PT q) {return dot(p-q, p-q);}

//dist2
typedef pair<PT, double> Circle;

PT rotateCCW90(PT p) {return PT(-p.y, p.x);}

// vector<PT> CircleCircleIntersection(PT a, PT b, double r, double R) {
// 	vector<PT> ret;
// 	double d = sqrt(dist2(a, b));
// 	if (d > r+R || d+min(r,R) < max(r, R)) return ret;
// 	double x = (d*d-R*R+r*r) / (2*d);
// 	double y = sqrt(r*r-x*x);
// 	PT v = (b-a)/d;
// 	ret.push_back(a+v*x+RotateCCW90(v)*y);
// 	if (y > 0)
// 		ret.push_back(a+v*x - RotateCCW90(v)*y);
// 	return ret; 
// }

// double prob(PT tr, ) {

// }

double arccos(double a, double b, double c) {
	double val = (a*a+b*b - c*c) / (2*a*b);
	double angle = acos(val);
	// return abs(angle);
}

double arctan(double a, double b) {
	double angle = asin(b/a);
	return abs(angle);
}

int n;
vector<Circle> trees;

int main() {
	cin >> n;
	double x, y, r;
	for (int i = 0; i < n; ++i) {
		cin >> x >> y >> r;
		trees.push_back({PT(x, y), r});
	}
	double b, d;
	auto origin = PT(0.0, 0.0);
	cin >> b >> d; 

	PT boar(0,0);
	// double res = 0;
	vector<pdd> ranges ;
	for (auto &tr : trees) {
		auto dist = dist2( tr.first, origin );
		double R = tr.second;
		double angle;
		if ( dist < (R+b)*(R+b) ) {
			continue;
		}else if ( dist - (R+b)*(R+b) >= d*d )  {
			angle = arctan(  sqrt(dist) , R+b );
		}else{
			angle = arccos( sqrt(dist), d, R+d );
		}
		double a0 = atan2( tr.first.y ,  tr.first.x );

		cout << a0 << "," << angle << endl;
		cout << a0 + angle << endl;
		cout << a0 - angle << endl;


		if (a0 - angle < 0) {
			ranges.emplace_back( 2*PI + a0-angle, 2*PI );
			ranges.emplace_back( 0,  a0+angle  );
		}
		if (a0 + angle >  2*PI ) {
			ranges.emplace_back( a0-angle, 2*PI );
			ranges.emplace_back( 0,  a0+angle - 2*PI );
		}
		if (a0 - angle > 0 && a0 + angle <  2*PI ) 
				ranges.emplace_back( a0-angle, a0+angle );

		// res += prob(tr);
	}

	sort(ranges.begin(), ranges.end() );
	double start, end;
	if (ranges.size() == 0) {
		cout << 0 <<endl;
		return 0;
	}
	start = ranges[0].first;
	end = ranges[0].second;
	// vector<pdd> newrange;
	double total = 0.0;
	for (int i=1; i<ranges.size(); i++) {
		// cout << i << endl;
			if ( ranges[i].first < end ) {
				end = max(end, ranges[i].second);
			}else{
				// newrange.push_back( {start, end} );
				total  += (end-start);
				start = ranges[i].first;
				end = ranges[i].second;
			}
	} 

	cout << total / (2 * PI) << endl;


	// if (res >= 1) cout << 1;
	// else cout << res;

}