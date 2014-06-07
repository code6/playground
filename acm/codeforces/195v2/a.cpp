/* --- Author: Vladimir Smykalov, enot.1.10@gmail.com --- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
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
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

void output(int x1, int y1, int x2, int y2) {
    cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
#endif

    int x, y;
    cin >> x >> y;
    ll zx = abs(x);
    ll zy = abs(y);
    ll k = zy + zx;
    if (x > 0 && y > 0) {
        output(0, k, k, 0);
    } else {
        if (x > 0 && y < 0) {
            output(0, -k, k, 0);
        } else {
            if (x < 0 && y > 0) {
                output(-k, 0, 0, k);
            } else {
                output(-k, 0, 0, -k);
            }
        }
    }

    return 0;
}
