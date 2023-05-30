#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#define PI 3.1415926535

using namespace std;

bool debug = true;

struct point {
    int x, y;
    point(int x, int y) : x(x), y(y) {}
    bool operator<(point p) const { return x < p.x || (x == p.x && y < p.y); }
    bool operator==(point p) const { return y == p.y ? x == p.x : false; }
};

int xcross(point p, point q, point r) {
    return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
}

double angle(point p, point q, point r) {
    double num = (p.x - q.x) * (r.x - q.x) + (p.y - q.y) * (r.y - q.y);
    double den = sqrt(pow(p.x - q.x, 2) + pow(p.y - q.y, 2)) *
                 sqrt(pow(r.x - q.x, 2) + pow(r.y - q.y, 2));
    return num / den;
}

void convexHull(vector<point> &points) {
    int n = points.size();
    vector<point> hull;

    if (n < 3) {
        printf("0.0000000\n");
        return;
    }

    // 找到初始值
    int l = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].x < points[l].x) {
            l = i;
        }
    }

    int p = l, q;
    do {
        hull.push_back(points[p]);

        q = (p + 1) % n;
        while (p == q) { // 去重
            q = (q + 1) % n;
        }
        for (int i = 0; i < n; i++) {
            if (points[p] == points[i] || points[q] == points[i]) { // 去重
                continue;
            }
            if (xcross(points[p], points[i], points[q]) < 0) {
                q = i;
            }
        }
        p = q;
    } while (p != l);

    if (debug) {
        for (auto point : hull) {
            cout << "(" << point.x << ", " << point.y << ")"
                 << "  ";
        }
    }

    int m = hull.size();
    double max = -1;
    for (int i = 0; i < m; ++i) {
        double temp = angle(hull[i], hull[(i + 1) % m], hull[(i + 2) % m]);
        if (temp > max) {
            max = temp;
        }
    }
    printf("%.7lf\n", acos(max) / PI * 180);
}

int main() {

    if (debug)
        freopen("./data.in", "r", stdin);

    int total;
    scanf("%d", &total);

    for (int i = 0; i < total; ++i) {
        int appleCnt;
        scanf("%d", &appleCnt);
        vector<point> points;
        for (int j = 0; j < appleCnt; ++j) {
            int x, y;
            scanf("%d%d", &x, &y);
            points.push_back({x, y});
        }
        convexHull(points);
    }

    return 0;
}