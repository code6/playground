/*
Please write complete compilable code.
Read input from standard input (STDIN) and print output to standard output(STDOUT).
For more details, please check https://www.interviewstreet.com/recruit/challenges/faq/view#stdio
*/

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

const int INF = 10000000;
const int MAX_V = 100;

struct edge {
    int to, cap, rev;
};

vector<edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to, int cap) {
    //cout << from << ' ' << to << ' ' << cap << endl;
    G[from].pb((edge){to, cap, G[to].size()});
    G[to].pb((edge){from, 0, G[from].size() - 1});
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;
    range(i, G[v].size()) {
        edge &e = G[v][i];
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));
            if (d > 0) {
                e.cap -= d;
                G[e.to][e.rev].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    for (;;) {
        memset(used, 0, sizeof(used));
        int f = dfs(s, t, INF);
        if (f == 0) return flow;
        flow += f;
    }
}

char tags[MAX_V];



int main() {
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    int t;
    int n,m ;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        range(i, n + 2) {
            G[i].clear();
        }
        range(i, n) {
            char tag;
            int cost;
            cin >> tag >> cost;
            tags[i + 1] = tag;
            if (tag == 'A') {
                add_edge(0, i + 1, cost);
            } else {
                add_edge(i + 1, n + 1, cost);
            }
        }
        range(i, m) {
            int a, b;
            cin >> a >> b;
            if (tags[a] != tags[b]) {
                if (tags[a] == 'A') 
                    add_edge(a, b, INF);
                else
                    add_edge(b,a, INF);
            }
        }
        cout << max_flow(0, n + 1) << endl;
    }

    return 0;
}
