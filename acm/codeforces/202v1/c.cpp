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

struct Set {
    vector<int> sk;
    ll add;
};


int n, m, q;
vector<ll> a;
vector<Set> sa;

ll query(int at) {
    ll ret = 0;

    range(i, sa.size()) {
        if (sa[i].add) {
            range(j, sa[i].sk.size()) {
                int pos = sa[i].sk[j];
                a[pos] += sa[i].add;
            }
            sa[i].add = 0;
        }
    }

    range(j, sa[at].sk.size()) {
        int pos = sa[at].sk[j];
        ret += a[pos];
    }
    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    scanf("%d %d %d", &n, &m, &q);
    range(i, n) {
        int val;
        scanf("%d", &val);
        a.pb(val);
    }

    range(i, m) {
        Set s;
        s.add = 0;
        int num;
        scanf("%d", &num);
        range(i, num) {
            int pos;
            scanf("%d", &pos);
            pos --;
            s.sk.pb(pos);
        }
        sa.pb(s);
    }

    range(i, q) {
        char op;
        int k, x;
        scanf(" %c", &op);
        if (op == '?') {
            scanf("%d", &k);
            k --;
            ll ans = query(k);
            cout << ans << endl;
        } else {
            scanf("%d %d", &k, &x);
            k --;
            sa[k].add += x;
        }
    }

    return 0;
}
