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
typedef pair<ll, ll> PLL; 

/*
vector<PII> vp;
vp.pb(mp(5, 2));
vp.pb(mp(3, 4));
vp.pb(mp(6, 1));
range(i, vp.size()) {
    eprintf("(%d, %d)\n", vp[i].fs, vp[i].sc);
}
forit(it, vp) {
    eprintf("(%d, %d)\n", it->fs, it->sc);
}
cout << "sz = " << sz(vp) << endl;
sort(all(vp));
forit(it, vp) {
    eprintf("(%d, %d)\n", it->fs, it->sc);
}
*/

const int MAX = 300000 + 50;
int n, m;
int arr[MAX];
ll sum_arr[MAX];
PLL last_best_arr[MAX];

int main() {
#ifndef ONLINE_JUDGE
    freopen("b.in", "r", stdin);
#endif
    cin >> n >> m;
    range(i, n) scanf("%d", &arr[i]);
    range(i, m) sum_arr[0] += arr[i];
    range(i, n) {
        if (i == 0) continue;
        if (i + m - 1 >= n) break;
        sum_arr[i] = sum_arr[i - 1] - arr[i - 1] + arr[i + m - 1];
    }

    last_best_arr[n] = mp(0, n);
    range(i, n) {
        ll at = n - 1 - i;
        last_best_arr[at] = last_best_arr[at + 1];
        PLL tmp = mp(sum_arr[at], at);
        if (tmp.fs >= last_best_arr[at].fs) {
            last_best_arr[at] = tmp;
        }
    }

    ll res = 0;
    PLL bestp;

    range(i, n) {
        if (i + 2 * m  - 1 >= n) break;
        int p1 = i;
        int p2 = last_best_arr[i + m].second;
        ll tmp = sum_arr[p1] + sum_arr[p2];
        if (tmp > res) {
            res = tmp;
            bestp = mp(p1,p2);
        }
    }
    cout << bestp.fs + 1<< " " << bestp.sc + 1<< endl;


    return 0;
}
