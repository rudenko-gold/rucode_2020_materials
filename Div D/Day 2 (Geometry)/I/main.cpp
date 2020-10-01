#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <iomanip>
#include <cmath>

using namespace std;

const double EPS = 0.000000001;

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

Vector operator+(Vector& left, Vector& right) {
    Vector result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    return result;
}

Vector operator-(Vector& left, Vector& right) {
    Vector result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    return result;
}

Vector operator-(Point& left, Point& right) {
    Vector result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    return result;
}

double cos(Vector& left, Vector& right) {
    return (left * right) / (len(left) * len(right));
}

Vector rotate90(Vector vector) {
    swap(vector.x, vector.y);
    vector.x *= -1.0;
    return vector;
}

double pseudo_scalar(Vector left, Vector right) {
    return left.x * right.y - left.y * right.x;
}

double triangle_area(Point p0, Point p1, Point p2) {
    return fabs(pseudo_scalar(Vector(p0, p1), Vector(p0, p2))) / 2.0;
}


struct Line {
    Line(Point begin, Point end) {
        this->direct = end - begin;
        this->p = begin;
        this->norm = rotate90(direct);
    }

    Vector norm, direct;
    Point p;
};

bool isLeftTurn(Point p0, Point p1, Point p2) {
    return pseudo_scalar(Vector(p0, p1), Vector(p0, p2)) > 0.0;
}

bool onSameLine(Point p0, Point p1, Point p2) {
    return fabs(pseudo_scalar(Vector(p0, p1), Vector(p0, p2))) < EPS;
}

int main() {
    int n;
    cin >> n;

    vector<Point> poly(n);

    for (int i = 0; i < n; i++) {
        cin >> poly[i].x >> poly[i].y;
    }

    poly.push_back(poly[0]);
    poly.push_back(poly[1]);

    for (int i = 3; i < poly.size(); i++) {
        if (
                isLeftTurn(poly[i - 2], poly[i - 1], poly[i]) != isLeftTurn(poly[i - 3], poly[i - 2], poly[i - 1]) ||
                onSameLine(poly[i - 2], poly[i - 1], poly[i])
        ) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes";
}
