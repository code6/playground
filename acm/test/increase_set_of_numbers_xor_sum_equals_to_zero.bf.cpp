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
#define range(i, n) for (long long i=0; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define two(i) (1LL<<(i))

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

int n;
vector<ll> ori_v, best_v;
ll limit, ans, ans2;
map<PII, ll> M;

void update(ll & ret, ll tmp) {
    if (tmp == -1) return;
    if (ret == -1) ret = tmp;
    ret = min(ret, tmp);
}

int mem(int state, int dep) {
    if (dep < 0) {
        return 0;
    }

    PII key = mp(state, dep);
    if (M.find(key) != M.end()) {
        return M[key];
    }

    ll &ret = M[key];
    ret = -1;

    int cnt = 0;
    range(i, n) {
        if ( (!(state & two(i))) && (two(dep) & ori_v[i])) {
            cnt ++;
        } 
    }

    if (cnt % 2 == 0) {
        ret = mem(state, dep - 1);
    } else {
        if (cnt == n)  { //full odd
            /*
            range(i, n) 
                range(j, n)
                    if (i != j) 
                        update(ret,  mem(state | two(i) | two(j), dep) + 
                                (state & two(i) ? two(dep) : two(dep + 1) - ori_v[i] % two(dep + 1) ) +
                                (state & two(j) ? two(dep) : two(dep + 1) - ori_v[j] % two(dep + 1) ) 
                                );
            */
        } else { //odd
            range(i, n) {
                if ((state & two(i)) || !(two(dep) & ori_v[i])) {
                    ll tv = mem(state | two(i), dep - 1);
                    if (tv >= 0) {
                        update(ret,  tv + 
                                (state & two(i) ? two(dep) : two(dep) - ori_v[i] % two(dep + 1))  
                                );
                    }
                }
            }
        }
    }

    //cout << state << ' ' << dep << ' ' << ret << endl;

    return ret;
}

void dfs(vector<ll> v, int dep) {
    if (dep == n) {
        int xsum = 0;
        ll cost = 0;
        int same = 0;
        range(i, n) xsum ^= v[i], cost += v[i] - ori_v[i], same += v[i] == ori_v[i];
        if (xsum == 0) {
            if (ans == -1 || ans > cost) {
                ans = cost;
                best_v = v;
            }
        }
        return;
    }

    int cost = 0;
    range(i, n) {
        cost += v[i] - ori_v[i];
    }
    if (cost > ans2) {
        return;
    }

    range(i, limit + 1) {
        if (i < v[dep]) {
            continue;
        }
        v[dep] = i;
        dfs(v, dep + 1);
        v[dep] = ori_v[dep];
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("g.in", "r", stdin);
    freopen("g.out", "w", stdout);
#endif
    while (cin >> n) {
        ori_v.clear();
        ll ma = 0;
        range(i, n) {
            ll val;
            cin >> val;
            ori_v.pb(val);
            ma = max(val, ma);
        }

        limit = 1;
        while (limit < ma) limit *= 2;
        limit *= 2;

        int len = 0;
        ll tmp = ma;
        while (tmp) len ++, tmp >>= 1;
        len ++;

        M.clear();
        ans2 = mem(0, 31);
        bool even_bit = true;
        for (int i = len; i >= 0; i--) {
            int cnt = 0;
            for (int j = 0; j < n; j++) cnt += (two(i) & ori_v[j]) > 0;
            even_bit &= cnt % 2 == 0;
            if (even_bit) {
                for (int j = 0; j < n; j++) {
                    if (!(two(i) & ori_v[j])) {
                        ll backup = ori_v[j];
                        ori_v[j] = two(i);
                        M.clear();
                        ll tmp = mem(0, i);
                        if (tmp != -1) {
                            tmp += two(i) - backup % two(i);
                        }
                        update(ans2, tmp);
                        ori_v[j] = backup;
                    }
                }
            }
        }

        cout << ans2 << endl;

        /*
        ans = -1;
        dfs(ori_v, 0);
        if (ans != ans2) {
            cout << n << endl;
            range(i, n) cout << ori_v[i] << ' ' ; cout << endl;
            cout << ans << ' ' << ans2<< endl;
            break;
        }
        */
    }

    return 0;
}
