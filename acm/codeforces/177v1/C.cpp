#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

int bf(int n) {
    vector<int> v;
    int i;
    int ret = 0;
    for (i = 0; i <= n; i++) v.push_back(i);
    do 
    {
        int tmp = 0;
        for (i = 0; i <= n; i++) {
            tmp += v[i]  ^ i;
        }
        ret = max(ret, tmp);
    } while (next_permutation(v.begin(), v.end()));
    return ret;
}

const int MAX = 1000000 + 50;
int arr[MAX];

int main() {
    int i;
    int n;
    cin >> n;
    cout << (long long)n * (n + 1) << endl;
    for (i = 0; i <= n; i++) arr[i] = i;
    int left = n;
    while (left > 0) {
        int m = 1;
        while (m * 2 - 1 <= left) {
            m *= 2;
        }
        for (i = 0; i < m / 2; i++) {
            swap(arr[i], arr[m - 1 - i]);
        }
        for (i = m; i <= left; i++) {
            swap(arr[i], arr[i % m]);
        }
        left = left - m;
    }
    printf("%d", arr[0]);
    for (i = 1; i <= n; i++) {
        printf(" %d", arr[i]);
    }
    puts("");
    return 0;
}
