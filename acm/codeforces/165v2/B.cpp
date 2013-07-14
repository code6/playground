#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

const int MAX = 100000 + 5000;

int A[MAX];

int main() {
    int T;
    cin >> T;
    int i;
    for (i = 0; i < T; i++) {
            scanf("%d", &A[i]);
    }

    for (i = T - 2; i>= 0; i--) {
        if (A[i] > A[i + 1]) {
            break;
        }
    }

    printf("%d\n", i + 1);

    return 0;
}
