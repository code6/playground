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
vector<int> dfs_out;
bool vis[MAX];
int par[MAX], gz[MAX];
int t;
int n,m;

void dfs(int cur, const vector<vector<int> >& cg, vector<int>* dfs_out, int bad) {
    if (cur == bad) return;
    vis[cur] = true;
    range(i, cg[cur].size()) {
        int nei = cg[cur][i];
        if (nei == bad) continue;
        if (vis[nei]) continue;
        dfs(nei, cg, dfs_out, bad);
    }
    if (dfs_out != nullptr) {
        dfs_out->pb(cur);
    }
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

int main() {
    ios :: sync_with_stdio(false);
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d",&n, &m);
        g.clear();
        rev_g.clear();
        ng.clear();
        rev_ng.clear();
        g.resize(n);
        rev_g.resize(n);
        ng.resize(n);
        rev_ng.resize(n);
        range(i, m) {
            int a, b;
            scanf("%d%d", &a, &b);
            --a; --b;
            g[a].pb(b);
            rev_g[b].pb(a);
        }
        dfs_out.clear();
        memset(vis, 0, sizeof(vis));
        range(i, n) {
            if (!vis[i]) {
                dfs(i, g, &dfs_out, -1);
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
        memset(vis, 0, sizeof(vis));
        dfs(s0, ng, nullptr, -1);
        if (vis[sn]) {
            vector<int> candi;
            range(a, n) {
                memset(vis, 0, sizeof(vis));
                dfs(s0, ng, nullptr, a);
                if (gz[a] == 1 && !vis[sn]) {
                    candi.pb(a);
                }
            }
            printf("%d\n", int(candi.size()));
            if (candi.size()) {
                printf("%d", candi[0] + 1);
            }
            range2(i, 1, candi.size()) {
                printf(" %d", candi[i] + 1);
            }
            printf("\n");
        } else {
            printf("0\n\n");
        }
    }
    return 0;
}
