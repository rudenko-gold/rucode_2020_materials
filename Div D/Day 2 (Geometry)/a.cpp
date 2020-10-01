#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Vector {
    Vector(Point begin, Point end) {
        this->x = end.x - begin.x;
        this->y = end.y - begin.y;
    }

    double x, y;
};

double len(Vector& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

int main() {
    Point a, b;
    cin >> a.x >> a.y >> b.x >> b.y;
    Vector v(a, b);
    cout << fixed << setprecision(4) << len(v);
}
