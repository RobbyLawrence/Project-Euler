#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {}
    Point(int x_n, int y_n) : x(x_n), y(y_n) {}
};

struct Triangle {
    Point a;
    Point b;
    Point c;

    Triangle(Point a_n, Point b_n, Point c_n) : a(a_n), b(b_n), c(c_n) {}
};

static int sign(const Point &p1, const Point &p2, const Point &p3) {
    return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool contains_origin(const Triangle &t) {
    Point origin(0, 0);
    int d1 = sign(origin, t.a, t.b);
    int d2 = sign(origin, t.b, t.c);
    int d3 = sign(origin, t.c, t.a);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

int main() {

    return 0;
}
