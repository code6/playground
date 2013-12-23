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

int n;
VI va, vb;

bool bigger(PLL a, PLL b) {
    return a.fs >= b.fs && a.sc >= b.sc;
}

vector<PLL> shrink(vector<PLL> now) {
    sort(all(now));
    now.erase( unique( now.begin(), now.end() ), now.end());
    vector<PLL> ret;
    range(i, now.size()) {
        while (ret.size() > 1 && bigger(now[i], ret.back()) && bigger(ret[ret.size()-1], ret[ret.size() -2]) ) {
            ret.pop_back();
        }
        ret.pb(now[i]);
    }
    return ret;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n;
        va.clear();
        vb.clear();
        int v;
        range(i, n) {
            cin >> v;
            va.pb(v);
        }
        range(i, n) {
            cin >> v;
            vb.pb(v);
        }
        vector<PLL> now, pre;
        now.pb(mp(0LL, 0LL));
        range(i, n) {
            pre = now;
            //no use
            now = pre;
            //use
            range(j, pre.size()) {
                now.pb(mp(pre[j].fs + va[i], pre[j].sc + vb[i]));
            }
            now = shrink(now);


        }
        ll ans = 0;
        range(i, now.size()) {
            ans = max(ans, now[i].fs * now[i].fs + now[i].sc * now[i].sc);
        }
        cout << ans << endl;
    }
    return 0;
}

