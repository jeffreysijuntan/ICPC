#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 30000;
const int MAXM = 100000;
const double EPS = 1e-8;

struct Point
{
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
};

inline bool operator < (const Point& a, const Point& b)
{
    return a.x + EPS < b.x || fabs(a.x - b.x) < EPS && a.y + EPS < b.y;
}

inline Point operator - (const Point& a, const Point& b)
{
    return Point(a.x - b.x, a.y - b.y);
}

inline double det(const Point& a, const Point &b)
{
    return a.x * b.y - a.y * b.x;
}

inline double f(double lambda, const Point& a, const Point& b)
{
    double x = lambda * a.x + (1 - lambda) * b.x;
    double y = lambda * a.y + (1 - lambda) * b.y;
    return x * y;
}

int main()
{
    int n, m;
    assert(scanf("%d%d", &n, &m) == 2);
    assert(1 <= n && n <= MAXN);
    assert(0 <= m && m <= MAXM);
    double ret = 0;
    vector<Point> hull;
//Process each of the M row (cost, health, and potency) 
//into a 2D point (budget*health/cost,  budget*potency/cost) 
//-- the maximum point to reach if using only this troop type
    for (int i = 0; i < n; ++ i) {
        int c;
        double h, p;
        assert(scanf("%d%lf%lf", &c, &h, &p) == 3);
        assert(1 <= c && c <= MAXM);
        assert(0 - EPS <= h && h <= 1 + EPS);
        assert(0 - EPS <= p && p <= 1 + EPS);
        double cnt = (double)m / c;
        Point cur(h * cnt, p * cnt);
        ret = max(ret, cur.x * cur.y);
        hull.push_back(cur);
    }
//Sort the points by X then Y, 
//and use the convex hull algorithm to find the subset of points P* ={ (X_i, Y_i) }^N that forms the convex polygon

    sort(hull.begin(), hull.end());

    int ptr = 0;
    for (int i = 0; i < hull.size(); ++ i) {
// fprintf(stderr, "(%.6f, %.6f)\n", hull[i].x, hull[i].y);
        while (ptr > 1 && det(hull[ptr - 1] - hull[ptr - 2], hull[i] - hull[ptr - 1]) > -EPS) {
            -- ptr;
        }
        hull[ptr ++] = hull[i];
    }
    hull.resize(ptr);

//Claim: the maximum possible efficacy  X*Y* is achieved by some point (X*, Y*) on the convex polygon contour
//to find such point  (X*, Y*): 
//the point is on some edge formed by the pair of consecutive vertex points P_i=(X_i, Y_i) and P_{i+1}=(X_{i+1}, Y_{i+1})
//
    for (int i = 1; i < hull.size(); ++ i) {
        // try to find a point between hull[i] and hull[i - 1]
        // lambda * (hull[i].x, hull[i].y) + (1 - lambda) * (hull[i - 1].x, hull[i - 1].y)
        // X' = lambda * hull[i].x + (1 - lambda) * hull[i - 1].x
        // Y' = lambda * hull[i].y + (1 - lambda) * hull[i - 1].y
        // X' * Y' is a quadratic function
        // we can solve it numerically as it only requires two digits of accuracy
        double l = 0, r = 1; // lambda \in [0, 1]
        for (int iter = 0; iter < 50; ++ iter) {
            double m1 = (l * 2 + r) / 3;
            double m2 = (l + r * 2) / 3;
            if (f(m1, hull[i], hull[i - 1]) < f(m2, hull[i], hull[i - 1])) {
                l = m1;
            } else {
                r = m2;
            }
        }
        ret = max(ret, f((l + r) / 2, hull[i], hull[i - 1]));
    }

    printf("%.2f\n", ret);

    return 0;
}
