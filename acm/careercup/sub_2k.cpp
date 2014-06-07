/*
 * http://www.careercup.com/question?id=5399897561890816
 */

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
#define two(i) (1LL<<(i))

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

map<int, int> mem;

int bf(int n) {
    if (mem.find(n) != mem.end()) {
        return mem[n];
    }
    mem[n] = 0;
    range(i, 40) {
        if (two(i) > n) break;
        if ((n & two(i)) == 0 && (n & two(i+1)) > 0) {
            if (!bf(n - two(i))) {
                mem[n] = 1;
                break;
            }
        }
    }
    return mem[n];
}

int opti(int n) {
    int pos = 0;
    int steps = 0;
    range(i, 40) {
        if (two(i) > n) break;
        if ((two(i) & n) > 0) {
            steps += i - pos;
            pos ++;
        }
    }
    return steps % 2 == 0 ? 0: 1;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("sub_2k.in", "r", stdin);
#endif
    int n, t;
    bool all_passed = true;
    cin >> t;
    range(i, t) {
        cin >> n;
        int state = bf(n);
        int state1 = opti(n);
        if (state != state1) {
            printf("answer for %d diff bf=%d  but opti=%d\n", n, state, state1);
            all_passed = false;
        }
    }
    if (all_passed) {
        puts("ALL PASSED");
    }
    return 0;
}
