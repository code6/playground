#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double du;
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define FOR(i, s, t) for(i = (s); i < (t); i++)
#define RFOR(i, s, t) for(i = (s)-1; i >= (t); i--)
const int MAXN = 1004;
const int P = 1000000007;

int c[MAXN][MAXN];
int a[MAXN][MAXN];
int f[MAXN][MAXN];
int size[MAXN];
int s[MAXN], t[MAXN];
int n;

int foo(int i, int j){
    return c[i+j][i];
}

void dfs(int i){
    int j, k, l;
    size[i] = 1;
    memset(f[i], 0, sizeof f[i]);
    f[i][0] = 1;
    for(j = 0; j < n; j++)
        if(a[i][j] && size[j] == -1){
            dfs(j);
            memset(s, 0, sizeof s);
            memset(t, 0, sizeof t);
            if(a[i][j] == -1){
                s[size[j]-1] = f[j][size[j]-1];
                for(k = size[j]-2; k >= 0; k--)
                    s[k] = (s[k+1] + f[j][k]) % P;
                for(k = 0; k < size[i]; k++)
                    for(l = 0; l < size[j]; l++)
                        t[k+l] = (t[k+l] + (ll)f[i][k]*s[l]%P*foo(k, l)%P*foo(size[i]-k-1, size[j]-l)) % P;
            }
            else{
                s[1] = f[j][0];
                for(k = 2; k <= size[j]; k++)
                    s[k] = (s[k-1] + f[j][k-1]) % P;
                for(k = 0; k < size[i]; k++)
                    for(l = 1; l <= size[j]; l++)
                        t[k+l] = (t[k+l] + (ll)f[i][k]*s[l]%P*foo(k, l)%P*foo(size[i]-k-1, size[j]-l)) % P;
            }
            size[i] += size[j];
            for(k = 0; k < size[i]; k++)
                f[i][k] = t[k];
        }
}

int main()
{
    #ifdef __FIO
    freopen("permutations_1.txt", "r", stdin);
    freopen("permutations.out.qinshi", "w", stdout);
    #endif
    int T, i0;
    scanf("%d", &T);
    for(i0 = 1; i0 <= T; i0++){
        int i, j;
        int x, y;
        char sign;
        c[0][0] = 1;
        scanf("%d\n", &n);
        for(i = 1; i <= n; i++){
            c[i][0] = 1;
            for(j = 1; j <= i; j++)
                c[i][j] = (c[i-1][j-1] + c[i-1][j]) % P;
        }
        memset(a, 0, sizeof a);
        for(i = 1; i < n; i++){
            scanf("%d %c %d\n", &x, &sign, &y);
            if(sign == '>')
                swap(x, y);
            a[x][y] = -1;
            a[y][x] = 1;
        }
        memset(size, -1, sizeof size);
        dfs(0);
        int ans = 0;
        for(i = 0; i < n; i++)
            ans = (ans + f[0][i]) % P;
        printf("Case #%d: %d\n", i0, ans);
    }
    return 0;
}
