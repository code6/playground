#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

const int MOD = 1000000007;
const int MAX = 10000 + 50;

typedef long long ll;

int n, m;
ll C[MAX][MAX / 2 + 5];
int val[MAX];

int calc(int arr[], int n, int m) {
    int i;
    ll ret = 0;
    for (i = m - 1; i < n; i++) {
        ll temp = arr[i] % MOD * C[i][min(m - 1, i - m + 1)] % MOD;
        ret = (ret + temp) % MOD;
    }
    return ret;
}

void init() {
    int i, j;
    for (i = 0; i < MAX; i++) {
        for (j = 0; j <= i / 2; j++) {
            if (j == 0 || j == i) {
                C[i][j] = 1;
            } else {
                C[i][j] = (C[i - 1][min(j, i - 1 - j)] + C[i - 1][min(j - 1, i - j)]) % MOD;
            }
        }
    }
}


int main() {
    init();
    freopen("card_game.txt", "r", stdin);
    freopen("card_game.out", "w", stdout);
    int t;
    cin >> t;
    for (int ca = 1; ca <= t; ca++) {
        cin >> n >> m;
        int i;
        for (i = 0; i < n; i++) {
            scanf("%d", &val[i]);
        }
        sort(val, val + n);
        int ans = calc(val, n, m);

        printf("Case #%d: %d\n", ca, ans);
    }
    return 0;
}
