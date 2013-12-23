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
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<int, int> PII;

const int MAX = 100000 + 50;

string s;
int n;
ll ans[MAX];
ll ans2[MAX];

struct Mapping {
    int m[26];
    int m_size;
    int pos;
    int last_val;

    Mapping() {
        memset(m, -1, sizeof(m));
        pos = -1;
        m_size = 0;
        last_val = -1;
    }

    bool advance() {
        if (pos == n - 1) {
            return false;
        }
        pos ++;
        int at = s[pos] - 'a';
        if (m[at] == -1) {
            m[at] = m_size++;
        }
        last_val = m[at];
        return true;
    }
};

int main() {
#ifndef ONLINE_JUDGE
    freopen("e1.in", "r", stdin);
#endif

    cin >> s;
    n = s.size();

    vector<vector<Mapping> > vvm, next_vvm;
    vector<Mapping> vm;
    for (int i = 0; i < n; i++) {
        Mapping m;
        m.pos = i - 1;
        m.advance();
        vm.pb(m);
    }
    vvm.pb(vm);

    while (vvm.size() > 0) {
        next_vvm.clear();
        range(i, vvm.size()) {
            vm = vvm[i];
            if (vm.size() == 1) {
                ans2[vm[0].pos] += 1;
            } else {
                ans[vm[0].pos] +=1;
                map<int, vector<Mapping> > M;
                range(i, vm.size()) {
                    if (vm[i].advance()) {
                        M[vm[i].last_val].pb(vm[i]);
                    }
                }
                for (map<int, vector<Mapping> >::iterator it = M.begin(); it != M.end(); it++) {
                    next_vvm.pb(it->second);
                }
            }
        }
        vvm = next_vvm;
    }

    for (int i = 0; i < n; i++) {
        printf(" %lld", ans[i]);
    }
    putchar('\n');

    for (int i = 0; i < n; i++) {
        printf(" %lld", ans2[i]);
    }
    putchar('\n');

    for (int i = 0; i < n; i++) {
        if (i) {
            ans[i] += ans[i-1];
            ans2[i] += ans2[i-1];
        }
        ans[i] += ans2[i];
        cout << ans[i] << endl;
    }

    return 0;
}
