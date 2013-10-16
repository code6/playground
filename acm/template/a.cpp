/* --- Author: Vladimir Smykalov, enot.1.10@gmail.com ---
 * STL refer:
 * a.insert(a.end(), b.begin(), b.end());
 * copy(b.begin(), b.end(), back_inserter(a));
 * */
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
    freopen("c.in", "r", stdin);
#endif
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

    return 0;
}
