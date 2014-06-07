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

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

int n, k;
vector<int> arr;

int gcd(int a, int b) {
    return b ? gcd(b, a % b): a;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    int n;
    cin >> n >> k;
    range(i, n) {
        int v;
        cin >> v;
        arr.pb(v);
    }

    sort(all(arr));
    vector<int> base;
    range(i, k + 1) {
        if (arr[0] - i > 0) {
            base.pb(arr[0] - i);
        }
    }
    sort(all(base));
    range(i, n) {
        range(j, base.size()) {
            printf("%d ", base[j]);
        }
        putchar('\n');
        range(j, base.size()) {
            int tmp = 1;
            range(u, k + 1) {
                int ne = arr[i] - u;
                if (ne < 0) continue;
                int d = gcd(tmp, ne);
            }
            base[j] = tmp;
        }
    }

    return 0;
}
