#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAX = 100000 + 5000;

int A[MAX], B[MAX];

int main() {
    int T;
    cin >> T;
    int i;
    for (i = 0; i < T; i++) {
            scanf("%d", &A[i]);
    }
    B[T] = T;
    B[T - 1] = T - 1;
    for (i = T - 2; i >= 0; i--) {
        if (A[i] < A[B[i + 1]]) {
            B[i] = i;
        } else {
            B[i] = B[i + 1];
        }
    }
    int ans = 0;
    for (i = 0; i < T ; i = B[i] +  1) {
        ans += B[i] - i;
    }

    printf("%d\n", ans);

    return 0;
}
