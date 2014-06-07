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

const int MAX = 3000 + 5;
const int MOD = 1000000000 + 7;
int n, m;
char bo[MAX][MAX];
int dp[MAX][MAX];

void update(int &i, int j) {
    i = (i + j) % MOD;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("d.in", "r", stdin);
#endif
    cin >> n >> m;
    range(i, n) {
        scanf(" %s", bo[i]);
    }
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1;
    range(i, n) {
        range(j, m) {
            if (i == 0 && j == 0) continue;
            if (bo[i][j] == '#') continue;
            if (i) update(dp[i][j], dp[i-1][j]);
            if (j) update(dp[i][j], dp[i][j-1]);
        }
    }
    int ret = 0;
    range(i, n) {
        range(j, m) {
            cout << dp[i][j] << ' ';
            ret = (ret - (long long)dp[i][j] * dp[i][j]) % MOD;
        }
        cout << endl;
    }
    ret = (ret + 2LL * dp[n - 1][m - 1] + MOD) % MOD;
    cout << "ans = " << endl;
    cout << ret << endl;

    return 0;
}
