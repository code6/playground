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

typedef long long ll;
typedef pair<ll, ll> PLL;
using namespace std;

ll a, b;
vector<ll> cache;

ll calc(ll n) {
    if (n  == 0) {
        return 0;
    }
    int ret = upper_bound(cache.begin(), cache.end(), n) - cache.begin();
    return ret;
}

void process(int cas) {
    int  ans = calc(b) - calc(a - 1);
    printf("Case #%d: %d\n", cas, ans);
}

void read() {
    cin >> a >> b;
}

void run(int cas) {
    read();
    process(cas);
}


bool is_palindrome(ll n) {
    ll t = n;
    ll rev = 0;
    while (t) {
        rev = rev * 10 + (t % 10);
        t /= 10;
    }
    return n == rev;
}

void bf(ll n) {
    ll i;
    cache.clear();
    for (i = 1; i <= n; i++) {
        if (is_palindrome(i)) {
            ll squ = (ll)i * i;
            if (is_palindrome(squ)) {
                printf("%lld, %lld\n", i, squ);
                cache.push_back(squ);
            }
        }
    }
}

int main() {
    bf(10000000LL);
    return 0;
    //freopen("C-large-1.in", "r", stdin);
    //freopen("C-large-1.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
