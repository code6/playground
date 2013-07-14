#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

typedef long long ll;

const int MAX = 100000 + 5000;

map<int, int> M;

int main() {
    int T;
    cin >> T;
    int i;
    int k, v;
    for (i = 0; i < T; i++) {
        scanf("%d %d", &k, &v);
        M[k] = v;
    }

    
    ll tk, tv;

    tk = 0;
    tv = 0;

    for (map<int, int>::iterator it = M.begin(); it != M.end(); it++) {
        k = it->first;
        v = it->second;
        if (tv > 0) {
            while (tv > 1 && tk < k) {
                tk ++;
                tv = (tv - 1) / 4 + 1;
            }
            tk = k;
            tv =max(tv, (ll)v);
        } else {
            tk = k;
            tv = v;
        }
    }

    if (tv > 1) {
        while (tv > 1) {
            tv = (tv - 1) / 4 + 1;
            tk ++;
        }
    } else {
        tk ++;
    }


    cout<<tk<<endl;

    return 0;
}
