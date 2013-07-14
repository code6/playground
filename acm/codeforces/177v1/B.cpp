#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MOD = 1000000007;

int arr[10];
int n, m;
int c1;

bool check() {
    int i;
    bool vis[10];
    for (i = 0; i < m; i++) {
        memset(vis, 0, sizeof(vis));
        vis[i] = true;
        int cur = arr[i];
        while (cur != 0) {
            vis[cur] = true;
            cur = arr[cur];
            if (vis[cur]) {
                break;
            }
        }
        if (cur != 0) {
            return false;
        }
    }
    return true;
}

void dfs(int dep) {
    if (dep == m) {
        if (check()) {
            c1 ++;
        }
        return;
    }
    for (int i = 0; i < m; i++) {
        arr[dep] = i;
        dfs(dep + 1);
    }
}

int run(int level) {
    m = level;
    c1 = 0;
    dfs(0);
    return c1;
}


int pmd(int a, int b, int c) {
    int ret = 1;
    while (b) {
        if (b & 1) {
            ret = (long long)ret * a % c;
        }
        a = (long long)a * a % c;
        b >>= 1;
    }
    return ret;
}


int main() {
    int i;
    int bak[10];
    for (i = 1; i <= 8; i++) {
        bak[i] = run(i);
 //       cout<<i<<' '<<bak[i]<<endl;
    }
    cin >> n >> m;
    int ans = bak[m];
    if (n > m) {
        ans = (long long)ans * pmd(n - m, n - m, MOD) % MOD;
    }
    cout<<ans<<endl;

    return 0;
}
