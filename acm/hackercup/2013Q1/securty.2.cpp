#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>

using namespace std;

const int MAX = 100 + 50;

bool check(char a, char b) {
    if (a == '?' || b == '?') {
        return true;
    }
    return a == b;
}

bool match_string(string A, string B, int m) {
    int da[10], db[10];
    memset(da, 0, sizeof(da));
    memset(db, 0, sizeof(db));

    int i, j;
    for (i = 0; i < A.size(); i++) {
        if (A[i] == '?') {
            da[6] ++;
        } else {
            da[A[i] - 'a'] ++;
        }
        if (B[i] == '?') {
            db[6] ++;
        } else {
            db[B[i] - 'a'] ++;
        }
    }
    int total = da[6] + db[6];
    for (i = 0; i < 6; i++) {
        total -= abs(da[i] - db[i]);
    }
    return total >= 0;
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
    freopen("security.txt", "r", stdin);
    freopen("security.2.out", "w", stdout);
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
