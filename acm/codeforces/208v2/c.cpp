#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
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

string tostring(int v) {
    stringstream ssin;
    ssin << v;
    return ssin.str();
}

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

string in_message[] = {
    "pushStack",
    "pushQueue",
    "pushBack",
};

string out_message[] = {
    "popStack",
    "popQueue",
    "popBack",
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    int n;
    vector<int> vp;
    cin >> n;
    range(i, n) {
        int val;
        cin >> val;
        vp.pb(val);
    }
    vp.pb(0);
    n++;

    vector<string> ans;

    int i, j, k;
    for (i = 0; i < n; i = j + 1) {
        vector<PII> max_val;
        for (j = i; j < n && vp[j] != 0; j++) {
            if (max_val.size() < 3) {
                max_val.pb(mp(vp[j], j));
            } else {
                sort(all(max_val));
                for (k = 0; k < 3; k++) {
                    if (vp[j] > max_val[k].fs) {
                        max_val[k] = mp(vp[j], j);
                        break;
                    }
                }
            }
        }

        for (k = i; k < j; k++) {
            int pos = -1;
            for (int u = 0; u < max_val.size(); u++) {
                if (max_val[u].sc == k) {
                    pos = u;
                    break;
                }
            }
            if (pos == -1) {
                ans.pb("pushFront");
            } else {
                ans.pb(in_message[pos]);
            }
        }

        string re = tostring(max_val.size()); 
        for (int u = 0; u < max_val.size(); u++) {
            re += " " + out_message[u];
        }

        ans.pb(re);
    }
    ans.pop_back();
    range(i, ans.size()) cout << ans[i] << endl;

    return 0;
}
