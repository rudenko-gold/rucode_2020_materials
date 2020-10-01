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

double len(Vector v) {
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

    Line(double a, double b, double c) {
        // ax + by + c = 0
        // y = - (c + ax) / b

        if (fabs(b) < EPS) {
            begin.x = -c / a;
            end.x = -c / a;

            begin.y = 0;
            begin.y = 10;
        } else {
            begin.x = 0;
            end.x = 10;
            begin.y = - (c + (a * begin.x)) / b;
            end.y = - (c + (a * end.x)) / b;
        }

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

pair<int, pair<double, double>> solve_quad(double a, double b, double c) {
    double x1, x2;

    long  double D = b * b - 4 * a * c;
    if (fabs(a) < EPS && fabs(b) < EPS && fabs(c) < EPS){
        return {4, {}};
    }

    if (fabs(a) < EPS && fabs(b) < EPS) {
        return {0, {}};
    }

    if(fabs(a) < EPS){
        x1 = c * (-1.0) / b;
        return { 1, {x1, x1 } };
    }

    if (D < 0.0){
        return { 0, {}};
    } else if (fabs(D) < EPS){
        x1 = (b * (-1)) / (2 * a);
        return { 1, {x1, x1}};
    } else {
        x1 = (b * (-1.0) - sqrt(D)) / (2 * a);
        x2 = (b * (-1.0) + sqrt(D)) / (2 * a);

        if(x2 < x1) {
            swap(x1, x2);
        }
        return {2, {x1, x2}};
    }
}

pair<int, pair<Point, Point>> cross(Line line1, Point center, double r) {
    //cerr << line1.begin.x << " " << line1.begin.y << " " << line1.end.x << " " << line1.end.y << endl;
    //cerr << (line1.end - line1.begin) * (line1.end - line1.begin) << " " << 2 * ((line1.end - line1.begin) * (line1.begin - center)) << " " << (line1.begin - center) * (line1.begin - center) - r * r << endl;
    pair<int, pair<double, double>> sol = solve_quad((line1.end - line1.begin) * (line1.end - line1.begin), 2 * ((line1.end - line1.begin) * (line1.begin - center)), (line1.begin - center) * (line1.begin - center) - r * r);

    if (sol.first == 0) {
        return {0, {}};
    } else if (sol.first == 1) {
        Point point = line1.begin +  (line1.end - line1.begin) * sol.second.first;
        return { 1, {point, point}};
    } else {
        Point point1 = line1.begin + (line1.end - line1.begin) * sol.second.first;
        Point point2 = line1.begin + (line1.end - line1.begin) * sol.second.second;

        return { 2, {point1, point2}};
    }
}

int main() {
    Point center;
    long double r, a, b, c;
    cin >> center.x >> center.y >> r >> a >> b >> c;

    pair<int, pair<Point, Point>> res = cross(Line(a, b, c), center, r);

    cout << res.first << "\n";
    if (res.first > 0) {
        cout << fixed << setprecision(5) << res.second.first.x << " " << res.second.first.y << endl;
    }
    if (res.first > 1) {
        cout << fixed << setprecision(5) << res.second.second.x << " " << res.second.second.y << endl;
    }
}
