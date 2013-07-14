#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 1000000 + 50; 
int n, t; 
int v[MAX],sta[MAX];
int flag[MAX];

int main() {
    cin >> n;
    int i, j;
    memset(flag, 0, sizeof(flag));
    for (i = 0; i < n; i++) {
        scanf("%d", &v[i]);
    }
    scanf("%d", &t);
    int a;
    for (i = 0; i < t; i++) {
        scanf("%d", &a);
        flag[a - 1] = -1;
    }
    a = 0;
    for (i = n - 1; i >= 0; i--) {
        if (flag[i] == -1) {
            sta[a++] = v[i];
        } else {
            if (a && sta[a - 1] == v[i]) {
                flag[i] = 1;
                a--;
            } else {
                flag[i] = -1;
                sta[a++] = v[i];
            }
        }
    }

    if (a == 0) {
        puts("YES");
        printf("%d", v[0] * flag[0]);
        for (i = 1; i < n; i++) {
            printf(" %d", v[i] * flag[i]);
        }
        puts("");
    } else {
        puts("NO");
    }

    return 0;
}
