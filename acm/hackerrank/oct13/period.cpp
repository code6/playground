#include <iostream>
#include <tr1/unordered_map>
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


template <>
struct std::tr1::hash<std::pair<int, int> > {
public:
        size_t operator()(std::pair<int, int> x) const throw() {
             size_t h = x.fs + x.sc;
             return h;
        }
};

typedef std::tr1::unordered_map< pair<int, int> , int> OO;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int calc(int a, int b, int m) {
    OO M;
    PII cur = mp(a % m, b % m);
    PII target = mp(1, 0);

    int n = 1;
    while (true) {
        M[cur] = n;
        if (cur == target) {
            break;
        }
        if (cur.sc == 0) {
            int step = n;
            int val = cur.fs;
            PII p = mp(n, val);
            do {
                if (p.sc == 1) {
                    return p.fs;
                }
                p = mp(p.fs + step, ((ll)p.sc * val) % m);
            } while (p.sc != val && p.sc > 0);
            return -1;
        }

        PII next = mp( ((ll)cur.fs * a + (ll)cur.sc * b * 5) % m,
                        ((ll)cur.fs * b + (ll)cur.sc * a) % m );

        if (M.find(next) != M.end()) {
            n = -1;
            break;
        } else {
            cur = next;
            n++;
        }
    }
    return n;
}


int main() {
#ifndef ONLINE_JUDGE
    freopen("p.in", "r", stdin);
#endif
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int t;
    int a, b, m;
    cin >> t;
    while (t--) {
        cin >> a >> b >> m;
        cout<< calc(a, b, m) << endl;
    }
    return 0;
}

