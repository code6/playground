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

int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
#endif
    int n;
    cin >> n;

    int bv = 0; 
    int zero_cnt = 0;
    range(i, 2 * n) {
        double val;
        cin >> val;
        int cv = ((int)(val * 1000 + 0.5)) % 1000;
        if (cv == 0) {
            zero_cnt ++;
        }
        bv += cv;
    }
    int non_zero = 2 * n - zero_cnt;
    double ans = 1e10;
    range(i, zero_cnt + 1) {
        if (2 * n - zero_cnt < i) continue;
        if ((zero_cnt - i) % 2) continue;
        int base = (non_zero - i) / 2;
        int lo = base * 1000;
        int hi = (base + i) * 1000;
        double tmp;
        if (bv <= lo) {
            tmp = abs(bv - lo) / 1000.0;
        } else {
            if (hi <= bv) {
            tmp = abs(bv - hi) / 1000.0;
            } else {
                tmp = min(bv % 1000, 1000 - bv % 1000) / 1000.0;
            }
        }
        ans = min(ans, tmp);
    }

    printf("%.3lf\n", ans);

    return 0;
}
