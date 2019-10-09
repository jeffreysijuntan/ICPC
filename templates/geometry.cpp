#include <iostream>
#include <math.h>
using namespace std;

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

int main() {

}