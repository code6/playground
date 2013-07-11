#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>

using namespace std;

const int MAX = 100 + 50;
int g[MAX][MAX];
bool used[MAX];
int match[MAX];

bool find(int m,int i)
{
    for (int j = 0; j < m; j++) {
        if (g[i][j] && !used[j]) {
            used[j] = true;
            if (match[j] == -1 || find(m, match[j])) {
                match[j] = i;
                return true;
            }
        }
    }
    return false;
}


int hungry(int n, int m) {
    int ret = 0;
    memset(match, -1, sizeof(match));
    int i;
    for (i = 0; i < n; i++) {
        memset(used, false, sizeof(used));
        if (find(m, i)) {
            ret ++;
        }
    }
    return ret;
}

bool check(char a, char b) {
    if (a == '?' || b == '?') {
        return true;
    }
    return a == b;
}

bool match_string(string A, string B, int m) {
    int n = A.size();
    int gn = m;
    int per = n / m;
    int i, j, k;
    memset(g, 0, sizeof(g));
    for (i = 0; i <  gn; i++) {
        for (j = 0; j < gn; j++) {
            bool flag = true;
            for (k = 0; k < per; k++) {
                if (!check(A[i * per + k], B[j * per + k])) {
                    flag = false;
                    break;
                }
            }
            g[i][j] = flag;
        }
    }
    return  hungry(gn, gn) == gn;
}

string calc(string A, string B, int m) {
    string NO_RESULT="IMPOSSIBLE";
    int n = A.size();
    int i, j;
    for (i = 0; i < n; i++) {
        if (A[i] == '?') {
            bool found = false;
            for (j = 0; j < 6; j++) {
                char ch = (char)('a' + j);
                A[i] = ch;
                if (match_string(A, B, m)) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                //cout << "A = " << A << " i = " << i << " B = " << B <<endl;
                return NO_RESULT;
            }
        }
    }
    if (match_string(A, B, m)) {
        return A;
    } else {
        return NO_RESULT;
    }
}

int main() {
    //freopen("b.in", "r", stdin);
    freopen("security.txt", "r", stdin);
    freopen("security.out", "w", stdout);
    int t;
    cin >> t;
    int m;
    string A, B;
    for (int ca = 1; ca <= t; ca++) {
        cin >> m >> A >> B;
        string ans = calc(A, B, m);
        printf("Case #%d: %s\n", ca, ans.c_str());
    }
    return 0;
}
