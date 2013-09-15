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
#define range(i, n) for (long long i=0; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define two(i) (1LL<<(i))

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

int n;
vector<ll>  arr;
ll ans;
map<PII, ll> M;

void update(ll & ret, ll tmp) {
    if (tmp == -1) return;
    if (ret == -1) ret = tmp;
    ret = min(ret, tmp);
}

/*
 * memoization(mask, pos)
 * Args:
 * mask: if 2^i in mask it means arr[i] has been added a high bit before, and all lower bit(<=pos) can be considerd zero.
 * pos: current check bit position, start from high to low
 * Return:
 *  return -1 if not valid ans exists else return minimum addition sum 
 */
int memoization(int mask, int pos) {

    if (pos < 0) {
        return 0;
    }

    PII state = mp(mask, pos);
    if (M.find(state) != M.end()) {
        return M[state];
    }

    ll &ret = M[state];
    ret = -1;

    int one_cnt = 0;
    for (int i = 0; i < n; i++) {
        if ( !(mask & two(i)) && 
                (two(pos) & arr[i])) {
            one_cnt ++;
        }
    }

    if (one_cnt % 2 == 0) { // even, xor on this pos equals zero
        ret = memoization(mask, pos - 1);
    } else {
        if (one_cnt == n)  { //full odd  bad state, do nothing
            //pass
        } else { //not full odd, choose one empty bit  to place 1  
            for (int i = 0; i < n; i++) {
                if ((mask & two(i))  //if number i has been added before, then it contain zero at pos 
                        || !(two(pos) & arr[i])  // or if number i has zero at pos and hasn't been added before
                        ) {
                    ll candi = memoization(mask | two(i), pos - 1);
                    ll added = mask & two(i) ? two(pos)  // number i has been added before, so we need extra two(pos) sum
                        //number i hasn't been added before, we need calc the new sum 
                        //here we only consider bits in [0 .. pos]
                        : two(pos) - arr[i] % two(pos + 1); 
                    if (candi >= 0)  // legal result
                        update(ret,  candi + added);
                }
            }
        }
    }

    return ret;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("g.in", "r", stdin);
#endif
    while (cin >> n) {
        arr.clear();
        for (int i = 0; i < n; i++) {
            ll val;
            cin >> val;
            arr.push_back(val);
        }

        ll max_val = arr[0];
        for (int i = 1; i < n; i++) max_val = max(max_val, arr[i]);

        int max_pos = 0;
        while (max_val) max_pos ++, max_val >>= 1;
        max_pos ++;

        //no adjust
        M.clear();
        ans = memoization(0, 31);

        bool even_bit = true;
        for (int i = max_pos; i >= 0; i--) {
            int one_cnt = 0;

            for (int j = 0; j < n; j++) one_cnt += (two(i) & arr[j]) > 0;
            even_bit &= one_cnt % 2 == 0;

            if (even_bit) {
                for (int j = 0; j < n; j++) {
                    //arr[j] at pos i is empty, try add to 1
                    if (!(two(i) & arr[j])) {
                        ll backup = arr[j];
                        arr[j] = two(i);

                        //since previous pos all contain even one bits, we just start from current pos i
                        M.clear();
                        ll candi = memoization(0, i);
                        ll added = two(i) - backup % two(i);
                        if (candi >= 0) 
                            update(ans, candi + added);

                        arr[j] = backup;
                    }
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
