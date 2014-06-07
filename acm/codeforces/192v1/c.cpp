#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
#define range(i, n) for (int i=0; i<(n); ++i)

using namespace std;

typedef pair<int, int> PII;
#define mp make_pair

const int MAX = 100000 + 500;
const int LIMIT = 5; 

int n, m;
vector<int> g[MAX];
int du[MAX];
vector<vector<int> > cycle;
bool vis[MAX];
set<PII> S;

bool check(int u, int v) {
    if (S.find(mp(u,v)) == S.end()) {
        return true;
    } else {
        return false;
    }
}

bool islegal(const vector<int>& vp) {
    int i;
    for (i = 1; i < vp.size(); i++) if (!check(vp[i- 1], vp[i])) 
    {
        //cout << vp[i - 1] << " " << vp[i] << endl;
        return false;
    }
    return true;
}

vector<int> change(vector<int> vp, int ty) {
    vector<int> ret;
    if (ty == 1) {
        ret = vp;
        sort(vp.begin(), vp.end());
        do {
            if (islegal(vp)) {
                ret = vp;
                break;
            }
        } while (next_permutation(vp.begin(), vp.end()));
    } else {
        int i;
        for (i = 0; i < vp.size(); i+=2) {
            ret.push_back(vp[i]);
        }
        vector<int> odd;
        for (i = 1; i < vp.size(); i+=2) {
            odd.push_back(vp[i]);
        }
        for (i = 0; i < odd.size(); i++) {
            int j = (i) % odd.size();
            ret.push_back(odd[j]);
        }
    }
    return ret;
}

vector<int> find_bag(int at) {
    vector<int> bag;
    bag.push_back(at);
    vis[at] = true;
    queue<int> Q;
    Q.push(at);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        range(i, g[cur].size()) {
            int next = g[cur][i];
            if (!vis[next]) {
                vis[next] = true;
                bag.push_back(next);
                Q.push(next);
                break;
            }
        }
    }
    return bag;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    range(i, n) vis[i] = false, du[i] = 0;
    S.clear();
    cin >> n >> m;
    range(i, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        u--;v--;
        S.insert(mp(u,v));
        S.insert(mp(v,u));
        du[u] ++;
        du[v] ++;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    cycle.clear();
    range(i, n) {
        if (du[i] <= 1 && !vis[i]) {
            vector<int> bag = find_bag(i);
            cycle.push_back(bag);
        }
    }

    range(i, n) {
        if (!vis[i]) {
            vector<int> bag = find_bag(i);
            cycle.push_back(bag);
        }
    }

    /*
    range(i, cycle.size()) {
        cout << "cycle = " << cycle[i].size() << endl;
        range(j, cycle[i].size()) cout << ' ' << cycle[i][j] ; cout<< endl;
    }
    */

    int maxlen = 0;
    int best_pos;
    int cz = cycle.size();
    range(i, cz) {
        if (cycle[i].size() > maxlen) {
            maxlen = cycle[i].size();
            best_pos = i;
        }
    }
    vector<int> vp; 
    if (maxlen >= LIMIT) {
        vp = cycle[best_pos];
        cycle.erase(cycle.begin() + best_pos);
        vp = change(vp, 2);
    } else {
        range(i, cz) {
            int pos = cz - 1 - i;
            vp.insert(vp.end(), cycle[pos].begin(), cycle[pos].end());
            //range(i, vp.size()) cout << vp[i] << ' '; cout << endl;
            cycle.erase(cycle.begin() + pos);
            if (vp.size() >= LIMIT) {
                break;
            }
        }
        vp = change(vp, 1);
    }

    //range(i, vp.size()) cout << vp[i] << ' '; cout << endl;


    if (islegal(vp)) {
        vector<int> last;
        range(i, vp.size()) {
            last.push_back(vp[i]);
            for (int j = (int)cycle.size() - 1; j >= 0; j--) {
                last.push_back(cycle[j].back());
                cycle[j].pop_back();
                if (cycle[j].size() == 0) {
                    cycle.erase(cycle.begin() + j);
                }
            }
        }
        last.push_back(last[0]);
        int used = m;
        range(i, last.size()) {
            if (i > 0 && used > 0) {
                cout << last[i - 1] + 1 << ' ' << last[i] + 1 << endl;
                used --;
            }
        }
    } else {
        puts("-1");
    }

    return 0;
}
