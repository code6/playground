#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

int n;
char buf[10000];
int valid[200][200];
int check(char *str, int f, int r) {
    if (f > r) {
        return 1;
    }

    if (f == r) {
        if (str[f] == '(' || str[f] == ')') {
            return 0;
        } else {
            return 1;
        }
    }

    if (f + 1 == r) {
        if ((str[f] == ':') && (str[f + 1] == '(' || str[f + 1] == ')')) {
            return 1;
        }
    }

    if (valid[f][r] != -1) {
        return valid[f][r];
    }

    int &ret  = valid[f][r];

    ret = 0;

    if (str[f] == '(' and str[r] == ')') {
        ret = max(ret, check(str, f + 1, r - 1));
    }

    int i, j;
    for (i = f; i < r; i++) {
        ret = max(ret, min(check(str, f, i), check(str, i + 1, r)));
    }
    return ret;
}

int main() {
    //freopen("b.in", "r", stdin);
    //freopen("b.out", "w", stdout);
    freopen("balanced_smileystxt.txt", "r", stdin);
    freopen("balanced_smileystxt.out", "w", stdout);
    cin >> n;
    gets(buf);
    for (int ca = 1; ca <= n; ca++) {
        gets(buf);
        int l = strlen(buf);
        memset(valid, -1, sizeof(valid));
        int ans = check(buf, 0, l - 1);
        printf("Case #%d: %s\n", ca, ans ? "YES" : "NO");
    }
    return 0;
}
