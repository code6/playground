#include <iostream>
#include <stdio.h>
#include <string.h>
#include <queue>
#include <map>

using namespace std;

const int MAX = 2 * 100000  + 50;
typedef long long ll;

int t;
ll N, K;
ll A,B,C,R;
ll m[MAX], ct[MAX];
/*
m[0] = a
m[i] = (b * m[i - 1] + c) % r, 0 < i < k
*/

int main() {
    int i;
    //freopen("c.in", "r", stdin);
    freopen("find_the_mintxt.txt", "r", stdin);
    //freopen("c.out", "w", stdout);
    freopen("find_the_mintxt.out", "w", stdout);
    cin >> t;
    for (int ca = 1; ca <= t; ca++) {
        cin >> N >> K;
        cin >> A >> B >> C >> R;
        memset(ct, 0, sizeof(ct));
        m[0] = A;
        if (A <= K) {
            ct[A] ++;
        }
        for (i = 1; i < K; i++) {
            m[i] = (B * m[i - 1] + C) % R;
            if (m[i] <= K) {
                 ct[m[i]] ++;
            }
        }

        priority_queue< int, vector<int>, greater<int> > Q;

        for (i = 0; i <= K; i++) {
            if (ct[i] == 0) {
                Q.push(i);
            }
        }

        for (i = K; i <= 2 * K; i++) {
            m[i] = Q.top();
            Q.pop();
            ll le = m[i - K];
            if (le <= K) {
                ct[le] --;
                if (ct[le] == 0) {
                    Q.push(le);
                }
            }
        }

        int ans;
        if (N <= 2 * K + 1) {
            ans = m[N - 1];
        } else {
            ans = m [K + (N - 2 * K - 2) % (K + 1)];
        }

        printf("Case #%d: %d\n", ca, ans);
    }
    return 0;
}
