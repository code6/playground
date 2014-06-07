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

const int MAX = 3000 + 50;

vector<int> arr[3];
int n;
int dp[MAX][2];
int get_val(int at, int le, int ri) {
    if (le && ri) return arr[2][at];
    if (!le && !ri) return arr[0][at];
    return arr[1][at];
}

int rec(int at,  int left_occ) {
    if (at == n) {
        return 0;
    }
    if (dp[at][left_occ] != -1) 
        return dp[at][left_occ];
    int & ret = dp[at][left_occ];

    //put current
    ret = rec(at + 1, 1) + get_val(at, left_occ, 0);
    
    //put last
    if (at < n - 1) {
        ret = max(ret, rec(at + 1, 0) + get_val(at, left_occ, 1));
    }

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("d.in", "r", stdin);
#endif
    cin >> n;
    range(i, 3) {
        range(j, n) {
            int val;
            cin >> val;
            arr[i].pb(val);
        }
    }
    memset(dp, -1, sizeof(dp));
    int ans = rec(0, 0);
    cout << ans << endl;

    return 0;
}
