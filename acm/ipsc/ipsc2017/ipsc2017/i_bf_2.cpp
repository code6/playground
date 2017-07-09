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
int back;

void dfs(int cur, int par, const vector<vector<int> >& cg, int bad, vector<int>* dfs_out) {
    if (cur == bad) return;
    vis[cur] = true;
    if (dfs_out != nullptr) {
        dfs_out->pb(cur);
    }
    range(i, cg[cur].size()) {
        int nei = cg[cur][i];
        if (nei == bad) continue;
        if (nei == par) back = 1;
        if (vis[nei]) continue;
        dfs(nei, par, cg, bad, dfs_out);
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
        }
        int s0, sn;
        s0 = 0;
        sn = n-1;
        memset(vis, 0, sizeof(vis));
        dfs_out.clear();
        dfs(s0, s0, g, -1, &dfs_out);
        eprintf("vis=");
        range(i, n) eprintf("%d ", vis[i]); eprintf("\n");
        if (vis[sn]) {
            vector<int> candi;
            set<int> V;
            range(i, n) {
                int a = dfs_out[i];
                if (V.find(a) != V.end()) {
                    continue;
                }
                V.insert(a);
                memset(vis, 0, sizeof(vis));
                dfs(s0, s0, g, a, nullptr);
                if (!vis[sn]) {
                    back = -1;
                    memset(vis, 0, sizeof(vis));
                    dfs(a, a, g, -1, nullptr);
                    eprintf("%d %d\n", a, back);
                    if (back == -1) {
                        candi.pb(a);
                    }
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
