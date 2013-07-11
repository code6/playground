#include <iostream>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

typedef long long ll;

ll N, K, P;


int main() {
    freopen("roboelection.txt", "r", stdin);
    freopen("roboelection.out", "w", stdout);
    int t;
    cin >> t;
    for (int ca = 1; ca <= t; ca++) {
        cin >> N >> K >> P;
        ll safe = (N - 1) % K + 1;
        while (true) {
            if ((N - safe) * 100 < P * N) {
                 break;
            }
            ll lo = 1, hi = (N - safe) / K;
            ll mid;
            while (lo <= hi) {
                mid = (lo + hi) / 2;
                ll add = mid * K;
                if (add * 100 >= P * (safe + add)) {
                    hi = mid - 1;
                } else {
                    lo = mid + 1;
                }
            }
            safe += lo * K;
        }

        ll ans = (N - safe) / K + 1;
        ans += (N - safe) % K != 0;

        printf("Case #%d: %lld\n", ca, ans);
    }
    return 0;
}
