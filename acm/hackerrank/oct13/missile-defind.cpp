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


PII convert(int x, int y) {
    return mp(x - y, x + y);
}

int main() {
#ifndef ONLINE_JUDGE
    //freopen("c.in", "r", stdin);
    freopen("missile.in", "r", stdin);
    freopen("missile.me.out", "w", stdout);
#endif
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   

    int t;
    int cas = 0;
    //int target_cas = 90;
    int target_cas = -1;

    cin >> t;
    while (t--) {
    cas ++;
    int n;
    cin >> n;
    
    vector<PII> arr;
    
    range(i, n) {
        int x, y;
        cin >> x >> y;
        PII p = convert(x, y);
        arr.pb(p);
    }
    
    sort(all(arr));

    map<int, int> M;

    int ans = 0;
    int i, j;
    for(i = 0; i < n; i=j) {
        j = i;
        while (j < n && arr[j] == arr[i]) j++;
        if (cas == target_cas) {
            printf("from %d to %d, map = \n", i, j - 1);
            for (map<int, int>::iterator it = M.begin(); it != M.end(); it++) {
                printf("%d %d\n", it->first, it->second);
            }
            printf("\n");
        }
        for (int k = i; k < j; k++) {
            int y = arr[k].sc;
            if (M.size() > 0 && (M.begin())->first <= y) {
                map<int, int>::iterator it = M.upper_bound(y);
                it --;
                if (cas == target_cas) {
                    printf("(%d, %d)\n", arr[k].fs, arr[k].sc);
                    cout << M.begin()->first << " k = " << k << " y = " << y << " found = " << it->first << ' ' << it-> second << endl;
                }
                it->second --;
                if (it->second == 0) {
                    M.erase(it);
                }
            } else {
                if (cas == target_cas) {
                    printf("add one: (%d, %d)\n", arr[k].fs, arr[k].sc);
                }
                ans ++;
            }
        }
      for (int k = i; k < j; k++) {
          M[arr[k].sc] ++;
      }
    }

    if (cas == target_cas) {
        cout << ans << endl;
    }
    cout << ans << endl;
    }
    
    return 0;
}

