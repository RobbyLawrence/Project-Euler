#include <gmpxx.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct Point {
    int x;
    int y;
    Point operator-(const Point& other) const { // element-wise subtraction
        return Point{x - other.x, y - other.y};
    }
    Point() : x(0), y(0) {}
    Point(int x_n, int y_n) : x(x_n), y(y_n) {}

    friend ostream& operator<<(ostream& os, const Point& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

struct Triangle {
    Point a;
    Point b;
    Point c;
    Triangle(Point a_n, Point b_n, Point c_n) : a(a_n), b(b_n), c(c_n) {}
};

double cross_prod(const Point& v1, const Point& v2) {
    return v1.x*v2.y-v2.x*v1.y;
}

int sign(double num) {
    if (num > 0) {
        return 1;
    }
    else {
        return -1;
    }
}
bool contains(const Triangle& t, Point p) {
    Point AB = t.b - t.a;
    Point BC = t.c - t.b;
    Point CA = t.a - t.c;
    Point AP = p - t.a;
    Point BP = p - t.b;
    Point CP = p - t.c;
    if (sign(cross_prod(AB, AP)) == sign(cross_prod(BC, BP)) && sign(cross_prod(BC, BP)) == sign(cross_prod(CA, CP))) {
        return true;
    }
    else {
        return false;
    }
}

int main() {
    Triangle triangle = Triangle(Point(-1,-6),Point(-2,-1),Point(4,0));
    bool result = contains(triangle, Point(0,0));
    if (result) {
        cout << "YES\n";
    }
    else {
        cout << "NO\n";
    }
    return 0;
}
