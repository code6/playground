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
    freopen("A-large-practice.in", "r", stdin);
    freopen("A-large-practice.out", "w", stdout);
#endif
    int T;
    int n;
    cin >> T;
    for (int cas = 1; cas <= T; cas++) {
        cin >> n;
        vector<int>a, b;
        range(i, n) {
            int val;
            cin >> val;
            a.pb(val);
        }
        range(i, n) {
            int val;
            cin >> val;
            b.pb(val);
        }
        sort(all(a));
        sort(all(b));
        long long ret = 0;
        range(i, n) ret += (long long)a[i] * b[n - 1 - i];
        cout << "Case #" << cas << ": "<< ret << endl;
    }

    return 0;
}
