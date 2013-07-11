//不要那么早放弃，要锲而不舍。

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <queue>

using namespace std;

const int MAX = 1000 + 50;
const int MOD = 1000000007;

typedef long long ll;

#define mp make_pair
#define pb push_back

int N;
vector<pair<int, int> >g[MAX];
int dp[MAX][MAX];
int sz[MAX];
int C[MAX][MAX];

void init() {
    int i, j;
    for (i = 0; i < MAX; i++) {
        for (j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                C[i][j] = 1;
            } else {
                C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % MOD;
            }
        }
    }
}

int Comb(int i, int j) {
    if (i < j) {
        return 0;
    }
    return C[i][j];
}

int target[MAX];
void dfs(int at, int parent) {
    dp[at][0] = 1;
    sz[at] = 1;
    int p, i, j, k;
    for (p = 0; p < g[at].size(); p++) {
        int ne = g[at][p].first;
        int ty = g[at][p].second;
        if (ne == parent) {
            continue;
        }
        dfs(ne, at);
        memset(target, 0, sizeof(target));
        int total_sz = sz[at] + sz[ne];
        for (k = 0; k < total_sz; k++) {
            for (i = 0; i < min(k + 1, sz[at]); i++) {
                for (j = 0; j < sz[ne]; j++) {
                    int op = (int)(k - i < j + 1);
                    if (ty == op) {
                        int temp = (ll)dp[at][i] * dp[ne][j]  % MOD * Comb(k, i) % MOD * Comb(total_sz - k - 1, sz[at] - i - 1) % MOD;
                        //printf("at = %d, parent = %d, ne = %d, ty = %d, k = %d, i = %d, j = %d, op = %d, dp[at][i] = %d, dp[ne][j] = %d, temp = %d, v1= %d, v2=%d\n", at, parent, ne, ty, k, i, j, op, dp[at][i], dp[ne][j], temp, Comb(k, i), Comb(total_sz - k - 1, sz[at] - i - 1));
                        target[k] = (target[k] + temp) % MOD;
                    }
                }
            }
        }
        sz[at] = total_sz;
        for (i = 0; i < total_sz; i++) {
            dp[at][i] = target[i];
        }
    }
}

int main() {
    init();
    freopen("permutations_1.txt", "r", stdin);
    //freopen("permutations.out", "w", stdout);
    int t;
    cin >> t;
    for (int ca = 1; ca <= t; ca++) {
        cin >> N;
        int i, j, cur;

        for (i = 0; i < N; i++) {
            g[i].clear();
        }

        for (i = 0; i < N - 1; i++) {
            int x, y;
            char op;
            cin >> x >> op >> y;
            g[x].pb(mp(y, op == '<'));
            g[y].pb(mp(x, op == '>'));
        }

        memset(dp, 0, sizeof(dp));
        memset(sz, 0, sizeof(sz));
        dfs(0, -1);

        int ans = 0;
        for (i = 0; i < N; i++) {
            ans = (ans + dp[0][i]) % MOD;
        }

        printf("Case #%d: %d\n", ca, ans);
    }
    return 0;
}
