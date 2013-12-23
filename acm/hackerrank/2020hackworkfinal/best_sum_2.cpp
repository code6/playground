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
typedef vector<ll> VL;
typedef pair<int, int> PII;
typedef pair<ll, ll> PLL;

const int TY_KEEP = 100;

int n;
vector<PLL> arr;

ll s2(PLL a) {
    return a.fs * a.fs + a.sc * a.sc;
}
ll as(PLL a) {
    return abs(a.fs) + abs(a.sc);
}

int get_ty(PLL a) {
    return 2 * (a.fs >= 0) + (a.sc >= 0);
}

bool cmp(const PLL & a, const PLL& b) {
    if (get_ty(a) != get_ty(b)) 
        return get_ty(a) < get_ty(b);
    if (as(a) != as(b))
        return as(a) < as(b);
    return abs(a.fs) < abs(b.fs);
}

vector<PLL> shrink(vector<PLL> now) {
    if (now.size() == 0) return now;
    sort(all(now));
    now.erase( unique( now.begin(), now.end() ), now.end());
    sort(all(now), cmp);
    vector<PLL> ret;
    int ct = 1;
    ret.pb(now.back());
    for (int i = (int)now.size() - 2; i>=0; i--) {
        if (get_ty(now[i]) == get_ty(now[i+1])) {
            if (ct < TY_KEEP) {
                ret.pb(now[i]);
                ct++;
            }
        } else {
            ret.pb(now[i]);
            ct = 1;
        }
    }
    return ret;
}

int main() {
    freopen("best_sum.in", "r", stdin);
    freopen("best_sum.out.2", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        arr.clear();
        int v;
        range(i, n) {
            cin >> v;
            arr.pb(mp(v, 0));
        }
        range(i, n) {
            cin >> v;
            arr[i].sc = v;
        }
        sort(all(arr), cmp);
        vector<PLL> now, pre;
        now.pb(mp(0LL, 0LL));
        range(k, n) {
            int i = n - 1 - k;
            pre = now;
            //no use
            //use
            range(j, pre.size()) {
                now.pb(mp(pre[j].fs + arr[i].fs, pre[j].sc + arr[i].sc));
            }
            now = shrink(now);
            //eprintf("i = %d, now.size() = %d\n", i, now.size());
        }
        ll ans = 0;
        range(i, now.size()) {
            if (ans < s2(now[i])) {
                eprintf("(%lld, %lld)\n", now[i].fs, now[i].sc);
                ans = s2(now[i]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}

