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
    Vector() {}

    Vector(Point point) {
        this->x = point.x;
        this->y = point.y;
    }

    Vector(Point begin, Point end) {
        this->x = end.x - begin.x;
        this->y = end.y - begin.y;
    }

    double x, y;
};

double len(Vector& v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

double operator*(Vector& left, Vector& right) {
    return left.x * right.x + left.y * right.y;
}

double cos(Vector& left, Vector& right) {
    return (left * right) / (len(left) * len(right));
}

int main() {
    Vector a, b;
    cin >> a.x >> a.y >> b.x >> b.y;
    cout << fixed << setprecision(7) << acos(cos(a, b));
}
