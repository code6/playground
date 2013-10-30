/* 
 * STL refer:
 * a.insert(a.end(), b.begin(), b.end());
 * copy(b.begin(), b.end(), back_inserter(a));
 * */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <ctime>
#include <cassert>

using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define range(i, n) for (int i=0; i<(n); ++i)
#define range2(i, m,  n) for (int i=m; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

const double eps = 1e-8;
const double pi = acos(-1.0);
 
//copy from dumbear(Yaxiong Liang)
int sgn(double d) {
    return d > eps ? 1 : (d < -eps ? -1 : 0);
}
 
double trim(double d, double l = 1.0) {
    return d > l ? l : (d < -l ? -l : d);
}

struct point {
    double x, y;
    point(double _x = 0, double _y = 0): x(_x), y(_y) {
    }
    void input() {
        scanf("%lf%lf", &x, &y);
    }
    double len() const {
        return sqrt(x * x + y * y);
    }
    point trunc(double l) const {
        double r = l / len();
        return point(x * r, y * r);
    }
    point rotate_left() const {
        return point(-y, x);
    }
    point rotate_left(double ang) const {
        double c = cos(ang), s = sin(ang);
        return point(x * c - y * s, y * c + x * s);
    }
    point rotate_right() const {
        return point(y, -x);
    }
    point rotate_right(double ang) const {
        double c = cos(ang), s = sin(ang);
        return point(x * c + y * s, y * c - x * s);
    }
    string tostring() {
        stringstream ssin;
        ssin << x << ' ' << y;
        return ssin.str();
    }
};
 
bool operator==(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 && sgn(p1.y - p2.y) == 0;
}
 
bool operator!=(const point& p1, const point& p2) {
    return !(p1 == p2);
}
 
bool operator<(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) < 0 : p1.x < p2.x;
}
 
bool operator>(const point& p1, const point& p2) {
    return sgn(p1.x - p2.x) == 0 ? sgn(p1.y - p2.y) > 0 : p1.x > p2.x;
}
 
point operator+(const point& p1, const point& p2) {
    return point(p1.x + p2.x, p1.y + p2.y);
}
 
point operator-(const point& p1, const point& p2) {
    return point(p1.x - p2.x, p1.y - p2.y);
}
 
double operator^(const point& p1, const point& p2) {
    return p1.x * p2.x + p1.y * p2.y;
}
 
double operator*(const point& p1, const point& p2) {
    return p1.x * p2.y - p1.y * p2.x;
}
 
point operator*(const point& p, double r) {
    return point(p.x * r, p.y * r);
}
 
point operator/(const point& p, double r) {
    return point(p.x / r, p.y / r);
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    ios :: sync_with_stdio(false);
    vector<PII> vp;
    vp.pb(mp(5, 2));
    vp.pb(mp(3, 4));
    vp.pb(mp(6, 1));
    range(i, vp.size()) {
        eprintf("(%d, %d)\n", vp[i].fs, vp[i].sc);
    }
    range2(i, 3, 5) {
        eprintf("range2: %d\n", i);
    }
    forit(it, vp) {
        eprintf("(%d, %d)\n", it->fs, it->sc);
    }
    cout << "sz = " << sz(vp) << endl;
    sort(all(vp));
    forit(it, vp) {
        eprintf("(%d, %d)\n", it->fs, it->sc);
    }

    point p(4.0, 2.0);
    cout << p.tostring() << endl;
    cout << (p * 5).tostring() << endl;
    cout << (p / 2).tostring() << endl;
    cout << (p ^ point(3, 4)) << endl;
    

    return 0;
}
