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

const int MAX = 1000000 + 50;

ll n, m;
string a, b;
int tag[MAX];

ll gcd(ll a, ll b) {
    return b ? gcd(b, a % b) : a;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("b.in", "r", stdin);
#endif
    cin >> n >> m;
    cin >> a >> b;
    ll la = a.size();
    ll lb = b.size();
    ll d = gcd(la, lb);
    ll lcm = la * lb / d;
    ll total = n * la;
    ll times = total / lcm;


    memset(tag, -1, sizeof(tag));

    map<int, map<char, ll> > M;


    ll comm =  0;
    range(i, lb) {
        int cur = i % la;
        if (tag[cur] == -1) {
            int pos = cur;
            do {
                M[cur][a[pos]] ++;
                tag[pos] = cur;
                pos = (pos + lb) % la;
        //        cout << cur << ' ' << pos << ' ' << a[pos] << endl;
            } while (pos != cur);
        }
        comm += M[tag[cur]][b[i]] * times;
    }

    ll ans = total - comm;
    cout << ans << endl;

    return 0;
}
