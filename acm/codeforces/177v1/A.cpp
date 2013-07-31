#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1000000 + 50;
char v[MAX];

int main() {
    int n, m;
    cin >> n >> m;
    int i, j;

    if (n < m) {
        puts("-1");
    } else {
        if (n > 1 && m == 1) {
            puts("-1");
        } else {
            v[0] = 'a';
            m --;
            char ma = 'a';
            for (i = 1; i < n; i++) {
                if (n - i > m) {
                    if (ma == 'a') {
                        ma = 'b';
                        m--;
                    }
                    v[i] = v[i - 1] == 'a' ? 'b' : 'a';
                } else {
                    ma = char(ma + 1);
                    v[i] = ma;
                }
            }
            v[n] = '\0';
            puts(v);
        }
    }
    return 0;
}
