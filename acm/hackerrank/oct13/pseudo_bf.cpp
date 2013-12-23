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
const int MAX = 100000 + 50;

string s;
int n;
int ans[MAX];

bool is_pseudo_isomorphic(int x1, int y1, int x2, int y2) {
    for (int i = x1; i <= y1; i++)
        for (int j = i + 1; j <= y1; j++) {
            if ((s[i] == s[j]) != (s[x2 + i - x1] == s[x2 + j - x1])) return false;
        }
    return true;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("e.in", "r", stdin);
#endif
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    cin >> s;
    n = s.size();

    for (int len = 1; len <= n; len++) {
        vector<int> vp;
        for (int start = 0; start + len - 1 < n; start ++) {
            int pos;
            for (pos = 0; pos < vp.size(); pos++) {
                if (is_pseudo_isomorphic(start, start + len - 1, vp[pos], vp[pos] + len - 1)) {
                    break;
                }
            }
            if (pos == vp.size()) {
                vp.pb(start);
            }
            ans[start + len - 1] += vp.size();
        }
    }

    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
