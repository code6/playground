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
using namespace std;

typedef pair<int, int> PII;
typedef pair<PII, ll> PIIL;
#define mp make_pair

const int MOD = 1000002013;

ll n, m;
vector<PIIL> vp;

ll get_score(const vector<PIIL> & vp) {
    ll score = 0;
    for (int i = 0; i < vp.size(); i++) {
        int x = vp[i].first.first;
        int y = vp[i].first.second;
        int z = vp[i].second;
        int sz = y - x;
        score = (score + z * (sz - 1) * sz / 2) % MOD;
    }
    return score;
}

vector<PIIL> perform(vector<PIIL> vp) {
    int i, j;
    vector<PIIL> next_vp;
    while (true) {
        sort(vp.begin(), vp.end());
        bool found = false;
        for (i = 0; i < vp.size() && !found; i++) {
            for (j = 0; j < vp.size() && !found; j++) {
                if (i == j) continue;
                int x1, y1, x2, y2;
                ll v1, v2;
                x1 = vp[i].first.first;
                y1 = vp[i].first.second;
                v1 = vp[i].second;
                x2 = vp[j].first.first;
                y2 = vp[j].first.second;
                v2 = vp[j].second;
                if (x1 < x2 && x2 <= y1 && y1 < y2) {
                    found = true;
                    ll comm = min(v1, v2);
                    vp[i].second -= comm;
                    vp[j].second -= comm;
                    PIIL ni, nj;
                    ni = mp(mp(x1, y2), comm);
                    nj = mp(mp(x2, y1), comm);
                    vp.push_back(ni);
                    vp.push_back(nj);
                    break;
                }
            }
        }
        if (found) {
            sort(vp.begin(), vp.end());
            next_vp.clear();
            for (i = 0; i < vp.size(); i++) {
                if (vp[i].second > 0) {
                    if (next_vp.size() > 0 && next_vp.back().first == vp[i].first) {
                        next_vp.back().second += vp[i].second;
                    } else {
                        next_vp.push_back(vp[i]);
                    }
                }
            }
            vp = next_vp;
        } else {
            break;
        }
    }
    return vp;
}

void output(vector<PIIL> vp) {
    int i, j;
    for (i = 0; i < vp.size(); i++) {
        cout << " (" << vp[i].first.first << " " << vp[i].first.second << " " << vp[i].second << " ) ";
    }
    cout<<endl;
}

void process(int cas) {
    ll origin_score = get_score(vp);
    vector<PIIL> final_vp = perform(vp);
    ll last_score = get_score(final_vp);
    //output(vp);
    //output(final_vp);
    //cout << origin_score << " " << last_score << endl;
    ll ans = ((last_score - origin_score) % MOD + MOD) % MOD;
    cout<<"Case #"<<cas<<": "<<ans<<endl;
}

void read() {
    cin >> n >> m;
    int i;
    vp.clear();
    for (i = 0; i < m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        PIIL o = mp(mp(x, y), z);
        vp.push_back(o);
    }
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    freopen("A-large.in", "r", stdin);
    freopen("A-large.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }
    return 0;
}
