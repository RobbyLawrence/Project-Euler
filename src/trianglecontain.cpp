#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

struct Point {
    int x;
    int y;
    Point();
    Point(int x_n, int y_n) : x(x_n), y(y_n) {}
};

struct Triangle {
    tuple<Point, Point, Point> points;
    Triangle(Point a, Point b,) {

        this->points = make_tuple(a,b);
    }
};

int main() {

    return 0;
}
