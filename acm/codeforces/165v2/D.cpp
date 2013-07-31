#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int MAX = 100000 + 5000;

int A[MAX], B[MAX];

int LCS(int A[MAX], int n) {
    int m = 1;
    B[0] = A[0];
    int i;
    for (i = 1; i < n; i++) {
        int cur = A[i];
        int pos = upper_bound(B, B + m, A[i]) - B;
        B[pos] = cur;
        if (pos == m) {
            m++;
        }
    }
    return m;
}

int main() {
    int T, M;
    cin >> T >> M;
    int i;
    for (i = 0; i < T; i++) {
            double x;
            scanf("%d%lf", &A[i], &x);
    }
    printf("%d\n", T - LCS(A, T));

    return 0;
}
