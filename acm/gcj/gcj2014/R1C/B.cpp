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

vector<string> vp;
int n;

typedef long long ll;
using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define range(i, n) for (int i=0; i<(n); ++i)
#define range2(i, m,  n) for (int i=m; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;


void process(int cas) {
    int ans = 0;
    sort(all(vp));
    do {
        if (vp.size() > 5 ) {
            ans = -1;
            break;
        }
        char pre = vp[0][0];
        set<char> s;
        s.insert(pre);
        bool ok = true;
        for (int i = 0; i < vp.size() && ok; i++) {
            for (int j = 0; j < vp[i].size() && ok; j++) {
                if (vp[i][j] != pre) {
                    pre = vp[i][j];
                    if (s.find(pre) != s.end()) {
                        ok = false;
                    }
                    s.insert(pre);
                }
            }
        }
        if (ok) ans ++;
    } while (next_permutation(vp.begin(), vp.end()));
    cout<<"Case #"<<cas<<": "<<ans<<endl;
}

void read() {
    cin >> n;
    vp.clear();
    string s;
    range(i, n) {
        cin >> s;
        vp.pb(s);
    }
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    freopen("B-small-attempt0.in", "r", stdin);
    freopen("B-small-attempt0.bf", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
