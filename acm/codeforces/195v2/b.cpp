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

const int MOD = 1000000007;
int n, m, g;

int C(int x, int y) {
}

int inv(int val) {
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("d.in", "r", stdin);
#endif
    cin >> n >> m >> g;

    int ans = 0;
    if (m == 0) {
        ans = (n % 2 ? 0:1) == g;
    } else {
        if (n == 0) {
            ans = (m == 1 ? 1:0) == g;
        } else {
            range(i, n + m) {
                if (i <= n) {
                    int times = C(n - i + m - 1, n - i);
                }
            }
        }
    }
    ans = (ans % MOD + MOD) % MOD;
    cout << ans << endl;
    return 0;
}
