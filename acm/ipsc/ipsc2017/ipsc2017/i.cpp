/* 
 * STL refer:
 * a.insert(a.end(), b.begin(), b.end());
 * copy(b.begin(), b.end(), back_inserter(a));
 * */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <sstream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
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
#define range2(i, m,  n) for (int i=m; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
//#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define eprintf(...) 
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

const double eps = 1e-8;
const double pi = acos(-1.0);

const int MAX  = 500000 + 5;
const int MOD = 1000000000 + 9;
 
vector<vector<int> > g, rev_g,  ng, rev_ng;
vector<int> dfs_pre;
vector<int> dfs_out;
bool vis[MAX];
int self[MAX];
int par[MAX], gz[MAX];
int t;
int n,m;

void dfs(int cur) {
    vis[cur] = true;
    dfs_pre.pb(cur);
    range(i, g[cur].size()) {
        int nei = g[cur][i];
        if (vis[nei]) continue;
        dfs(nei);
    }
    dfs_out.pb(cur);
}


void rdfs(int cur, int p) {
    vis[cur] = true;
    par[cur] = p;
    gz[p] ++;
    range(i, rev_g[cur].size()) {
        int nei = rev_g[cur][i];
        if (vis[nei]) continue;
        rdfs(nei, p);
    }
}

vector<ll> topsort(int n, int start, const vector<vector<int> >& cg) {
    vector<int> du;
    vector<ll> ans;
    range(i, n) {
        ans.pb(0);
        du.pb(0);
    }
    range(i, n) {
        range(j, cg[i].size()) {
            du[cg[i][j]] ++;
        }
    }
    eprintf("du\n");
    range(i, n) eprintf("%d ", du[i]); eprintf("\n");
    ans[start] = 1;
    queue<int> Q;
    range(i, n) {
        if (du[i] == 0) Q.push(i);
    }
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        range(i, cg[cur].size()) {
            int nei = cg[cur][i];
            du[nei]--;
            ans[nei] = (ans[nei] + ans[cur]) % MOD;
            if (du[nei] == 0) {
                Q.push(nei);
            }
        }
    }
    return ans;
}

int main() {
    ios :: sync_with_stdio(false);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d",&n, &m);
        //printf("n=%d, m=%d\n", n, m);
        g.clear();
        rev_g.clear();
        ng.clear();
        rev_ng.clear();
        g.resize(n);
        rev_g.resize(n);
        ng.resize(n);
        rev_ng.resize(n);
        memset(self, 0, sizeof(self));
        range(i, m) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a; --b;
            if (a == b) {
                self[a] = 1;
                continue;
            }
            g[a].pb(b);
            rev_g[b].pb(a);
        }
        dfs_pre.clear();
        dfs_out.clear();
        memset(vis, 0, sizeof(vis));
        range(i, n) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        memset(vis, 0, sizeof(vis));
        memset(par, -1, sizeof(par));
        memset(gz, 0, sizeof(gz));
        range(i, n) eprintf("%d ", dfs_out[i]); eprintf("\n");
        range(i, n) {
            int cur = dfs_out[n - 1 - i];
            if (vis[cur]) continue;
            rdfs(cur, cur);
        }
        set<pair<int, int> > H;
        range(i, n) {
            range(j, g[i].size()) {
                int a, b;
                a = par[i];
                b = par[g[i][j]];
                if (a == b) continue;
                if (H.find(mp(a, b)) != H.end()) continue;
                H.insert(mp(a,b));
                ng[a].pb(b);
                rev_ng[b].pb(a);
            }
        }
        eprintf("par:\n");
        range(i, n) {
            eprintf("%d ", par[i]);
        }
        eprintf("\n");
        int s0, sn;
        s0 = par[0];
        sn = par[n-1];
        vector<ll> ans = topsort(n, s0, ng);
        vector<ll> r_ans = topsort(n, sn, rev_ng);
        // TODO(zhichunw): should we check here?
        ll total = ans[sn];
        eprintf("s0=%d, sn=%d:\n", s0, sn);
        eprintf("ans:\n");
        range(i, n) eprintf("%lld ", ans[i]);
        eprintf("\n");
        eprintf("r_ans:\n");
        range(i, n) eprintf("%lld ", r_ans[i]);
        eprintf("\n");
        vector<int> candi;
        set<int> V;
        range(i, n) {
            int a = par[dfs_pre[i]];
            if (V.find(a) != V.end()) {
                continue;
            }
            V.insert(a);
            ll tmp = (ans[a] * r_ans[a]) % MOD;
            eprintf("At i=%d, ans=%lld, r_ans=%lld, tmp=%lld\n", i, ans[a], r_ans[a], tmp);
            if (tmp == total && gz[a] == 1 && !self[a]) {
                candi.pb(a);
            }
        }
        if (total == 0 || candi.size() == 0) {
            printf("0\n\n");
        } else {
            printf("%d\n", int(candi.size()));
            printf("%d", candi[0] + 1);
            range2(i, 1, candi.size()) {
                printf(" %d", candi[i] + 1);
            }
            printf("\n");
        }
    }
    return 0;
}
