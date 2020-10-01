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

double operator*(Vector left, Vector right) {
    return left.x * right.x + left.y * right.y;
}

Vector operator+(Vector left, Vector right) {
    Vector result;
    result.x = left.x + right.x;
    result.y = left.y + right.y;
    return result;
}

Vector operator*(Vector left, double scalar) {
    Vector result;
    result.x = left.x * scalar;
    result.y = left.y * scalar;
    return result;
}

Vector operator-(Point left, Point right) {
    Vector result;
    result.x = left.x - right.x;
    result.y = left.y - right.y;
    return result;
}

double cos(Vector left, Vector right) {
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

double signed_triangle_area(Point p0, Point p1, Point p2) {
    return pseudo_scalar(Vector(p0, p1), Vector(p0, p2)) / 2.0;
}

struct Line {
    Line(Point begin, Point end) {
        this->begin = begin;
        this->end = end;
        this->direct = end - begin;
        this->p = begin;
        this->norm = rotate90(direct);
    }

    Point begin, end;
    Vector norm, direct;
    Point p;
};

bool is_colinear(Line left, Line right) {
    return abs(pseudo_scalar(left.direct, right.direct)) < EPS;
}

bool operator==(Line left, Line right) {
    return is_colinear(left, right) && abs(pseudo_scalar(left.p - right.p, left.direct)) < EPS;
}

bool isLeftTurn(Point p0, Point p1, Point p2) {
    return pseudo_scalar(Vector(p0, p1), Vector(p0, p2)) > 0.0;
}

bool onSameLine(Point p0, Point p1, Point p2) {
    return fabs(pseudo_scalar(Vector(p0, p1), Vector(p0, p2))) < EPS;
}

Point operator+(Point p, Vector v) {
    p.x += v.x;
    p.y += v.y;
    return p;
}

pair<int, Point> cross(Line line1, Line line2) {
    if (line1 == line2) {
        return { 2, { } };
    } else if (is_colinear(line1, line2)) {
        return { 0, {} };
    }

    Vector norm = rotate90(line2.direct);

    double t = (norm * (line2.begin - line1.begin)) / (norm * (line1.end - line1.begin));
    Point ans = line1.begin + ((line1.end - line1.begin) * t);

    return { 1, ans };
}

int main() {
    Point a, b, c, d;

    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

    Line line1(a, b);
    Line line2(c, d);

    pair<int, Point> result = cross(line1, line2);

    cout << result.first << " ";
    if (result.first == 1) {
        cout << fixed << setprecision(6) << result.second.x << " " << result.second.y;
    }
}
