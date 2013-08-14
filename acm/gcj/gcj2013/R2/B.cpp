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
}

void read() {
    cin >> r >> t;
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
    bruteforce(4);
    return 0;
    freopen("xiaomei.in", "r", stdin);
    freopen("xiaomei.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
