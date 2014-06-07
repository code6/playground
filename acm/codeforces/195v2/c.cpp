/* --- Author: Vladimir Smykalov, enot.1.10@gmail.com --- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <ctime>
#include <cassert>

using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define range(i, n) for (int i=0; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define two(i) (1LL<<(i))

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    int n;
    vector<int> arr;
    scanf("%d", &n);
    range(i, n) {
        int v;
        cin >> v;
        arr.push_back(v);
    }

    int best = 0;
    range(i, 32) {
        int val = -1;
        range(j, n) {
            if (arr[j] & two(i)) {
                if (val == -1) {
                    val = arr[j];
                } else {
                    val &= arr[j];
                }
            }
        }
        if (val != -1 && val % two(i) == 0) {
            best = max(best, i);
        }
    }

    vector<int> ret;
    range(i, n) {
        if (arr[i] & two(best)) {
            ret.push_back(arr[i]);
        }
    }

    printf("%d\n", ret.size());
    range(i, ret.size()) {
        if (i) putchar(' ');
        printf("%d", ret[i]);
    }
    putchar('\n');

    return 0;
}
