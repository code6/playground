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

int n, m, k;

const int MOD = 1000000009;

int power_mod(int a, int b, int c) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = (long long)ret * a % c;
        }
        a = (long long)a * a;
        b >>= 1;
    }
    return ret;
}

int calc(int l) {
    int times = l / k;
    int left = l % k;
    int ans = 0;
    if (times) {
        ans = (long long)(power_mod(2, times + 1, MOD) - 2) * k % MOD;
    }
    ans += left;
    ans = (ans + MOD) % MOD;
    return ans;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
#endif
    cin >> n >> m >> k;

    long long ans = 0;
    if (m == 0) {
        ans = 0;
    } else {
        int d = n / m;
        if ( d > 1) {
            ans = m % MOD;
        } else {
            if (n == m) {
                ans = calc(n);
            } else {
                if (m >= k) {
                    int seq = min(n - m, (m / (k - 1) + (m % (k -1)!= 0) - 1));
                    ans = calc(k - 1) * seq  + calc(m - (k - 1) * seq);
                } else {
                    ans = m;
                }
            }
        }
    }
    ans = (ans + MOD) % MOD;
    cout << ans << endl;

    return 0;
}
