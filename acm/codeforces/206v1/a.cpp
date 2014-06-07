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

int n, l, r, ql, qr;
vector<int> vw;

int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
#endif
    int n;
    cin >> n >> l >> r >> ql >> qr;
    vw.clear();

    int best = 0, sumv = 0;
    int le = n, ri = 0;
    range(i, n) {
        int v;
        cin >> v;
        vw.pb(v);
        sumv += v * l;
    }
    best = sumv + (n - 1) * ql;

    range(i, n) {
        int pos = n - 1 - i;
        le --; ri ++;
        sumv += vw[pos] * (r - l);
        int tmp = sumv + (le > ri ? max(0, le - 1 - ri) * ql : max(0, ri - 1 - le) * qr);
        //cout << le <<' ' << ri << ' ' << sumv << ' ' << tmp << endl;
        best = min(best, tmp);
    }

    cout << best << endl;

    return 0;
}
