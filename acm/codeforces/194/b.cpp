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

const int MAX = 1000 + 50;

int n, m;
vector<PII> vp;
bool fx[MAX], fy[MAX];

int main() {
#ifndef ONLINE_JUDGE
    freopen("b.in", "r", stdin);
#endif
    cin >> n >> m;
    memset(fx, 0, sizeof(fx));
    memset(fy, 0, sizeof(fy));
    range(i, m) {
        int x, y;
        scanf("%d%d", &x, &y);
        x--;y--;
        fx[x] = true;
        fy[y] = true;
    }

    range(i, n) {
        range(j, n) {
            if (i == 0 || i == n -1 || j == 0 || j == n - 1) {
                continue;
            }
            if (fx[i] || fy[j]) continue;
        }
    }

    return 0;
}
