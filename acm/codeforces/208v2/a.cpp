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

bool intersect(int x1, int y1, int x2, int y2) {
    if (x1 > y1) swap(x1, y1);
    if (x2 > y2) swap(x2, y2);
    if (x1 == x2 || x1 == y2 || y1 == x2 || y1 == y2) return false;
    if ((x1 < x2 && x2 < y1 && y1 < y2) || (x2 < x1 && x1 < y2 && y2 < y1)) return true;
    return false;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("a.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<int> vp;
    range(i, n) {
        int val;
        cin >> val;
        vp.pb(val);
    }

    bool flag = true;

    range(i, n - 1)
        range(j, i - 1)
        {
            if (intersect(vp[i], vp[i+1], vp[j], vp[j+1])) {
                flag = false;
            }
        }

    cout << (flag ? "no" : "yes") << endl;

    return 0;
}
