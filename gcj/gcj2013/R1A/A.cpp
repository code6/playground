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

ll r, t;


void process(int cas) {
    ll lo, hi;
    lo = 1, hi = t;
    while (lo <= hi) {
        ll mid = (lo + hi) / 2;
        if (2 * r + 2 * mid + 1 <= t / (mid + 1)) {
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    ll ans = lo;
    cout<<"Case #"<<cas<<": "<<ans<<endl;
}

void read() {
    cin >> r >> t;
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    freopen("xiaomei.in", "r", stdin);
    freopen("xiaomei.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
