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
vector<PLL> arr;

ll s2(PLL a) {
    return a.fs * a.fs + a.sc * a.sc;
}

bool cmp(const PLL & a, const PLL& b) {
    return atan2(a.fs, a.sc) < atan2(b.fs, b.sc);
}

int main() {
    freopen("best_sum.in", "r", stdin);
    freopen("best_sum.out", "w", stdout);
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
        ll ans = 0;
        range(i, arr.size()) {
            PLL tmp = mp(0, 0);
            for (int j = 0; j < n; j++) {
                int at = (i + j) % n;
                tmp.fs += arr[at].fs;
                tmp.sc += arr[at].sc;
                ans = max(ans, s2(tmp));
            }
        }
        cout << ans << endl;
    }
    return 0;
}

