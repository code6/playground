#include <iostream>
#include <vector>
#include <stdio.h>

using namespace std;

const int MAX = 1000000 + 50;

char S[MAX];

int main() {
    int i, j;
    while (scanf("%s", S)!=EOF) {
        int n = strlen(S);
        if (n == 1 && S[0] == '.') break;
        vector<int> fail(n + 1);
        fail[0] = -1;
        for (i = 1; i <= n; i++) {
            j = fail[i - 1];
            while (j >= 0 && S[i - 1] != S[j]) {
                j = fail[j];
            }
            fail[i] = j + 1;
        }
        int ret;
        if (n % (n - fail[n]) == 0) {
             ret = n / (n - fail[n]);
        } else {
            ret = 1;
        }
        printf("%d\n", ret);
    }
    return 0;
}
