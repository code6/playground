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
const int MAX_V = 100000 + 10;

int w, h, b, tot, half;

struct edge {
    int to, cap, rev;
};


bool valid[105][505];
vector<edge> G[MAX_V];
bool used[MAX_V];

void add_edge(int from, int to, int cap) {
    //printf(" (%d, %d) to (%d, %d) cap = %d \n",  from % w, from / w, to % w, to / w, cap);
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
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
    int t;
    int x0, y0, x1, y1;
    int cas = 0;
    cin >> t;
    while (t--) {
        cas ++;
        cin >> w >> h >> b;
        tot = w * h * 2 + 2;
        half = w * h;
        range(x, w)
            range(y, h)
                valid[x][y] = true;
        range(i, tot) {
            G[i].clear();
        }

        range(i, b) {
            cin >> x0 >> y0 >> x1 >> y1;
            for (int px = x0; px <= x1; px++)
                for (int py = y0; py <= y1; py++) {
        //            printf("grid(%d,%d) is not valid\n", px, py);
                    valid[px][py] = false;
                }
        }

        range(i, w) {
            if (valid[i][0])
                add_edge(tot - 2, i, 1);
            if (valid[i][h - 1])
                add_edge( (h - 1) * w + i + half, tot - 1, 1);
        }

        range(x, w)
            range(y, h) {
                if (!valid[x][y]) continue;
                int p1 = y * w + x + half;
                add_edge(p1 - half, p1, 1);
                for (int dx = -1; dx <= 1; dx ++) 
                    for (int dy = -1; dy <= 1; dy++) {
                        if (abs(dx) + abs(dy) != 1) continue;
                        int nx = x + dx;
                        int ny = y + dy;
                        if (nx < 0 || nx >= w || ny < 0 || ny >= h || !valid[nx][ny]) continue;
                        int p2 = ny * w + nx;
                        add_edge(p1, p2, 1);
                    }
            }

        cout << "Case #" << cas << ": " << max_flow(tot - 2 , tot - 1) << endl;
    }

    return 0;
}

