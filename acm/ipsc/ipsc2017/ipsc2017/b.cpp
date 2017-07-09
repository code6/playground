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

const int MAX  = 200+ 5;

 
int t;
int n,m;
char ty;
int du[MAX][MAX];
vector<PII> dir;

bool valid(PII a) {
    return a.first >= 0 && a.first < n && a.second >= 0 && a.second < m;
}

void update_du(PII a) {
    du[a.first][a.second] = 0;
    range(d, 4) {
        range(k, max(n, m)) {
            int i1 = a.first + dir[d].first * k;
            int j1 = a.second + dir[d].second * k;
            if (valid(mp(i1, j1)) && du[i1][j1] >0) {
                du[i1][j1]--;
            }
        }
    }
}


void greedy(PII start, int tot) {
    vector<PII> ans;
    while (true) {
        ans.pb(start);
        update_du(start);
        PII next;
        int min_du = -1;
        range(d, 4) {
            range(k, max(n, m)) {
                int i1 = start.first + dir[d].first * k;
                int j1 = start.second + dir[d].second * k;
                if (valid(mp(i1, j1)) && du[i1][j1] >0) {
                    if (min_du == -1 || min_du > du[i1][j1]) {
                        min_du = du[i1][j1];
                        next = mp(i1, j1);
                    }
                }
            }
        }
        if (min_du != -1) {
            start = next;
        } else {
            break;
        }
    }
    if (ans.size() == tot) {
        range(i, ans.size()) {
            printf("%d %d\n", ans[i].first + 1, ans[i].second + 1);
        }
        printf("\n");
    } else {
        printf("impossible\n");
    }
}


int main() {
    ios :: sync_with_stdio(false);
    scanf("%d", &t);
    dir.pb(mp(1, 1));
    dir.pb(mp(-1, -1));
    dir.pb(mp(-1, 1));
    dir.pb(mp(1, -1));
    while (t--) {
        scanf("%d%d%c",&n, &m, &ty);
        PII start;
        int min_du = -1;
        memset(du, 0, sizeof(du));
        range(i, n) {
            range(j, m) {
                du[i][j] = 1;
                range(d, 4) {
                    range(k, max(n, m)) {
                        int i1 = i + dir[d].first * k;
                        int j1 = j + dir[d].second * k;
                        if (valid(mp(i1, j1))) {
                            du[i1][j1] ++;
                        }
                    }
                }
            }
        }
        range(i, n) {
            range(j, m) {
                if ((ty == 'W' && (i+j)%2 ==0) || (ty == 'B' && (i+j)%2)) {
                    if (min_du == -1 || min_du > du[i][j]) {
                        min_du = du[i][j];
                        start = mp(i, j);
                    }
                }
            }
        }
        int tot = 0;
        if (ty == 'W') {
            tot = ((n + 1) /2)  * ((m + 1) / 2);
        } else {
            tot = (n /2) * (m / 2);
        }
        greedy(start, tot);
    }
    return 0;
}
