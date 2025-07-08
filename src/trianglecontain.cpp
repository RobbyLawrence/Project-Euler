#include <gmpxx.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

/*
 * Problem 102: Triangle Containment
 * started this one with Matthew.
 *
 * The strategy I ended up using is the cross product strategy for determining
 * if a point is within a triangle instead of barycentric weights.
 */
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
    // everything works now, but need to handle processing
    ifstream fin("problemfiles/102_triangles.txt");
    if (!fin.is_open()) {
        cerr << "Unable to open file\n";
        return 1;
    }
    int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0;
    char comma;
    Point origin = Point();
    int num_triangles = 0;
    while (fin >> a >> comma
        >> b >> comma
        >> c >> comma
        >> d >> comma
        >> e >> comma
        >> f) {
            Triangle t = Triangle(Point(a,b),Point(c,d),Point(e,f));
            if (contains(t, origin)) {
                num_triangles++;
            }
    }
    cout << "Number of triangles containing origin: " << num_triangles << endl;

    return 0;
}

/*
 * this wasn't too bad. all I was doing was implementing the cross product strategy
 * I did get to try some cool operator overloading stuff.
 */
