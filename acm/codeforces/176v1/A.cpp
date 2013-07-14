#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;


void bf(int n) {
    vector<int>v;
    int i;
    for (i = 1; i <= n; i++) {
        v.push_back(i);
    }
    int cnt = 0;
    do {
        cnt ++;
        for (i = 0; i < n; i++) {
            if (!(v[v[i] - 1] == n - (i + 1)  + 1)) {
                break;
            }
        }
        if (i == n) {
            for (i = 0; i < n; i++) {
                printf("%d ", v[i]);
            }
            printf("\n");
        }
    } while (next_permutation(v.begin(), v.end()));
    printf("try cnt = %d\n", cnt);
}

bool check(vector<int>v, int n) {
    int i;
    for (i = 1; i <= n; i++) {
        if (v[v[i]] != n - i + 1) {
            return false;
        }
    }
    return true;
}

void output(vector<int>v, int n) {
    int i;
    printf("%d", v[1]);
    for (i = 2; i <= n; i++) {
        printf(" %d", v[i]);
    }
    printf("\n");
}

void gen(int n) {
    if (n % 4 == 0 || n % 4 == 1) {
        vector<int> v(n + 1);
        int i, j;
        j = 2;
        i = 1;
        for (int t = 1; t <= int(n/4); t++) {
            v[i] = j;
            v[j] = n - i + 1;
            v[n - i + 1] = n - j + 1;
            v[n - j + 1] = n - (n - i + 1) + 1;
            i += 2;
            j += 2;
        }
        if (n % 4 == 1) {
            v[i] = j - 1;
        }
        if(check(v, n)) {
            output(v, n);
        } else {
            printf("fail!\n");
        }
    } else {
        puts("-1");
    }
}

int main() {
    int n;
    cin >> n;
    gen(n);
    return 0;
}
