//不要那么早放弃，要锲而不舍。

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <queue>

using namespace std;
const int MOD = 1000000007;
const int N = 101;

typedef long long LL;

LL K;
int war[11][11];
int a[N][N], res[N][N];

void build_matrix() {
    int i, j;
    memset(a, 0, sizeof(a));
    a[100][100] = 1;
    for (i = 0; i < 100; i++) {
        if (!war[i/10][i%10] && (i%10 > 0)) {
            a[i][100] = 1;
        }
    }
    for (i = 0; i < 100; i++) {
        int i1, i2;
        i1 = i / 10;
        i2 = i % 10;
        for (j = 0; j < 100; j++) {
            int j1, j2;
            j1 = j / 10;
            j2 = j % 10;
            if (i2 == j1 && !war[i1][i2] && !war[j1][j2] && !war[i1][j2]) {
                a[i][j] = 1;
            }
        }
    }
}

void one() {
    int i, j;
    memset(res, 0, sizeof(res));
    for (i = 0; i < N; i++) {
        res[i][i] = 1;
    }
}


int C[N][N];
void mul(int A[N][N], int B[N][N]) {
    int i, j , k;
    memset(C, 0, sizeof(C));
    for (k = 0; k < N; k++) {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] = (C[i][j] + (LL)A[i][k] * B[k][j]) % MOD;
            }
        }
    }
    memcpy(A, C, sizeof(C));
}

void output(int A[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) {
            printf("%d ", A[i][100]);
    }
    puts("\n");
}

void po(LL T) {
    one();
    while (T) {
        if (T & 1) {
            mul(res, a);
        }
        mul(a, a);
        T >>=1;
    }
    //output(res);
}

int main() {
    int t;
    freopen("digits_war.txt", "r", stdin);
    freopen("digits_war.out", "w", stdout);
    cin >> t;
    for (int ca = 1; ca <= t; ca++) {
        cin>>K;
        int i, j;
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 10; j++) {
                cin>>war[i][j];
            }
        }
        build_matrix();
        int ans = 9;
        if (K > 1) {
            po(K - 1);
            for (i = 0;i < 100; i++) {
                ans = (ans + res[i][100]) % MOD;
            }
        }
        printf("Case #%d: %d\n", ca, ans);
    }
    return 0;
}
