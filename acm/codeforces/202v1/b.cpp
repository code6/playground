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

const int MAX = 100000 + 50;

vector<int> G[MAX];
int weight[MAX];
ll weight_sum[MAX];
ll weight_divide[MAX];
ll total;
bool remove_total;


ll gcd(ll a, ll b) {
    if (b) {
        return gcd(b, a % b);
    } else {
        return a;
    }
}

void dfs(int current, int parent) {
    ll min_sum = total;
    int son_cnt = 0;
    range(i, G[current].size()) {
        if (G[current][i] == parent) continue;
        dfs(G[current][i], current);
        min_sum = min(min_sum, weight_sum[G[current][i]]);
        son_cnt ++;
    }
    if (remove_total) return;
    if (son_cnt > 0) { //non leaf
        ll lcm = 1;
        range(i, G[current].size()) {
            if (G[current][i] == parent) continue;
            ll son_div = weight_divide[G[current][i]];
            if (lcm / gcd(lcm, son_div) > min_sum / son_div) {
                //too big
                remove_total = true;
                return;
            } else {
                lcm = lcm * son_div / gcd(lcm, son_div);
            }
        }
        weight_divide[current] = lcm * son_cnt;
        weight_sum[current] = (min_sum / lcm) * lcm * son_cnt;
        //cout << current << ' ' << weight_divide[current]  << ' ' << weight_sum[current] << endl;
    } else {
        weight_sum[current] = weight[current];
        weight_divide[current] = 1;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("b.in", "r", stdin);
#endif
    int n;
    cin >> n;
    total = 0;
    range(i, n) {
        int val;
        cin >> val;
        weight[i + 1] = val;
        total += val;
    }
    range(i, n - 1) {
        int a, b;
        cin >> a >> b;
        G[a].pb(b);
        G[b].pb(a);
    }
    remove_total = false;
    dfs(1, -1);
    if (remove_total) {
        cout << total << endl;
    } else {
        cout << total - weight_sum[1] << endl;
    }

    return 0;
}
