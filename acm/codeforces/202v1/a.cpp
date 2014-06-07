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
    int val;
    cin >> n;
    vector<int> a;
    int ma = 0;
    range(i, n) {
        cin >> val;
        a.pb(val);
        ma = max(ma, val);
    }

    int lo = ma, hi = 2 * ma;
    int mid;
    while (lo <= hi) {
        mid = ((long long)lo + hi) / 2;
        int le = mid;
        range(i, n) {
            le -= mid - a[i];
            if (le < 0) break;
        }
        if (le <= 0) {
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    
    cout << lo << endl;

    return 0;
}
