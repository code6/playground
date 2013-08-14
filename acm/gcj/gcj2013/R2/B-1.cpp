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

typedef pair<ll, ll> PLL;
#define mp make_pair
#define two(i) (1LL<<(i))

ll n, p, M;
ll x, y;
vector<PLL> vmin, vmax;

ll get_can_win() {
    int i;
    ll who;
    who = 0;
    for (int i = 0; i < vmax.size() ; i++) {
        if (vmax[i].first <= p) {
            who += vmax[i].second;
        } else {
            break;
        }
    }
    return who - 1;
}

ll get_may_win() {
    int i;
    ll who;
    who = 0;
    for (int i = 0; i < vmin.size() ; i++) {
        if (vmin[i].first <= p) {
            who += vmin[i].second;
        } else {
            break;
        }
    }
    return who - 1;
}

void process(int cas) {
    vmin.clear();
    vmax.clear();
    M = two(n);
    p --;

    int i, j;

    ll sz = M;
    ll val;
    vmin.push_back(mp(0, 1));
    for (i = 0; i < n; i++) {
        val = 2 * vmin.back().first + 1;
        sz /= 2;
        vmin.push_back(mp(val, sz));
    }

    vmax.push_back(mp(two(n) - 1, 1));
    sz = M;
    for (i = 1; i <= n; i++) {
        val = M  - 1 - vmin[i].first;
        sz /= 2;
        vmax.push_back(mp(val, sz));
    }
    for (i = 0; i < vmax.size() / 2; i++) {
        swap(vmax[i], vmax[vmax.size() - 1 - i]);
    }

    /*
    for (i = 0; i < n + 1; i++) {
        cout << '(' << vmin[i].first << ' ' << vmin[i].second << " ) ";
    }
    cout<<endl;

    for (i = 0; i < n + 1; i++) {
        cout << '(' << vmax[i].first << ' ' << vmax[i].second << " ) ";
    }
    cout<<endl;
    */

    x = get_can_win();
    y = get_may_win();
    cout<<"Case #"<<cas<<": "<<x<<" "<<y<<endl;
}

void read() {
    cin >> n >> p;
}

void run(int cas) {
    read();
    process(cas);
}

void output_arr(vector<int> arr) {
    int i;
    for (i = 0; i < arr.size(); i++) printf("%d ", arr[i]);putchar('\n');
}

vector<int> go(vector<int> arr, int n, int p) {
    int sz = n;
    int i, j;

    /*
    cout<<"\nbefore:";
    output_arr(arr);
    */

    for (i = 0; i < p; i++) {
        vector<int> brr = arr;
        for (j = 0; j < n; j += sz) {
            int k;
            for (k = 0; k < sz / 2; k ++) {
                int x, y;
                x = arr[j + 2 * k];
                y = arr[j + 2 * k + 1];
                brr[j + k] = min(x, y);
                brr[j + sz / 2 + k] = max(x, y);
            }
        }
        sz /= 2;
        arr = brr;
    }

    /*
    cout<<"\nafter:";
    output_arr(arr);
    */

    return arr;
}

void bruteforce(int p) {
    int i, j;
    int n = 1;
    for (i = 0; i < p; i++) n *= 2;
    vector<int> arr;
    vector<int> min_pos, max_pos;
    for (i = 0; i < n; i++) {
        arr.push_back(i);
        min_pos.push_back(-1);
        max_pos.push_back(-1);
    }
    int times = 0;
    do {
        times ++;
        if (times % 100000 == 0) {
            cout<<" Times = " << times << endl;
        cout << " P = " << p << " N = " << n << endl;
        for (i = 0; i < n; i++) {
            //printf("(v = %d, %d, %d) ", i, min_pos[i], max_pos[i]);
            printf("%d ",  i);
        }
        putchar('\n');
        for (i = 0; i < n; i++) {
            //printf("(v = %d, %d, %d) ", i, min_pos[i], max_pos[i]);
            printf("%d ",  min_pos[i]);
        }
        putchar('\n');
        for (i = 0; i < n; i++) {
            //printf("(v = %d, %d, %d) ", i, min_pos[i], max_pos[i]);
            printf("%d ",  max_pos[i]);
        }
        }
        vector<int> res = go(arr, n, p);
        for (i = 0; i < n; i++) {
            int at = i;
            int val = res[i];
            if (min_pos[val] == -1 || min_pos[val] > at) {
                min_pos[val] = at;
            }
            if (max_pos[val] == -1 || max_pos[val] < at) {
                max_pos[val] = at;
            }
        }
    } while (next_permutation(arr.begin(), arr.end()));
    cout << " P = " << p << " N = " << n << endl;
    for (i = 0; i < n; i++) {
        //printf("(v = %d, %d, %d) ", i, min_pos[i], max_pos[i]);
        printf("%d ",  i);
    }
    putchar('\n');
    for (i = 0; i < n; i++) {
        //printf("(v = %d, %d, %d) ", i, min_pos[i], max_pos[i]);
        printf("%d ",  min_pos[i]);
    }
    putchar('\n');
    for (i = 0; i < n; i++) {
        //printf("(v = %d, %d, %d) ", i, min_pos[i], max_pos[i]);
        printf("%d ",  max_pos[i]);
    }
    putchar('\n');
}

int main() {
    int i;
    
    //for (i = 1; i < 5; i++) 
    //bruteforce(4);
    //return 0;
    freopen("B-large.in", "r", stdin);
    freopen("B-large.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
