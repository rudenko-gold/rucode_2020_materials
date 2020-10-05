#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <deque>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point {
    int x, y;
};

struct Vector {
    Vector(Point p0, Point p1) {
        x = p1.x - p0.x;
        y = p1.y - p0.y;
    }

    double x, y;
};

double pseudo_scalar(Vector left, Vector right) {
    return left.x * right.y - left.y * right.x;
}

double triangle_area(Point p0, Point p1, Point p2) {
    return fabs(pseudo_scalar(Vector(p0, p1), Vector(p0, p2))) / 2.0;
}
int main () {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    Point center = { 0, 0 };

    Point a, b, c;

    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;

    if (triangle_area(a, b, c) == triangle_area(a, b, center) + triangle_area(a, c, center) + triangle_area(b, c, center)) {
        cout <<  "987654321";
    } else {

        cout << a.x * (-1) << " " << a.y * (-1) << " " << b.x * (-1) << " " << b.y * (-1) << " " << c.x * (-1) << " " << c.y * (-1);
    }


}v
