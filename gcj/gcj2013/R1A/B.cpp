#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

#define mp make_pair

vector<int> pr;

typedef long long ll;
const int MAX = 10000 + 100;

int E, R, N;
int v[MAX];
int used[MAX];
int must[MAX];

int find_max(int f, int r) {
    int i;
    int vmax = -1;
    int pmax = -1;
    for (i = f + 1; i < r; i++) {
        if (v[i] > vmax) {
            vmax =v[i];
            pmax = i;
        }
    }
    return pmax;
}

void get_max(int f, int r, int p) {
    int flimit = min((ll)E, must[f] - used[f] + (ll)R * (p - f));
    int rlimit = max((ll)0, must[r] - (ll)R * (r - p));
    must[p] = flimit;
    used[p] = flimit - rlimit;
}

void doit(int f, int r) {
    if (!(f + 1 < r)) {
        return;
    }
    int p = find_max(f, r);
    get_max(f, r, p);
    doit(f, p);
    doit(p, r);
}

void process(int cas) {
    memset(used, -1, sizeof(used));
    memset(must, -1, sizeof(must));
    must[0] = E - R;
    used[0] = 0;
    must[N + 1] = R;
    used[N + 1] = 0;
    doit(0, N + 1);
    ll ans = 0;
    for (int i = 1; i <= N; i++) {
        ans += (ll) used[i] * v[i];
    }
    cout<<"Case #"<<cas<<": "<<ans<<endl;
}

void read() {
    scanf("%d %d %d", &E, &R, &N);
    for (int i = 1; i <= N; i++) {
        scanf("%d", &v[i]);
    }
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    freopen("B-large.in", "r", stdin);
    freopen("B-large.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
