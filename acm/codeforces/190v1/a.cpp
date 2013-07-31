#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
int n;


int main() {
//    freopen("in", "r", stdin);
    cin >> n;
    int i;
    ll square = 0;
    int bx1, by1, bx2, by2;
    bx1 = by1 = bx2 = by2 = -1;
    for (i = 0; i < n; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        square += (ll)abs(x1 - x2) * abs(y1 - y2);
        if (bx1 == -1 || bx1 > x1) bx1 = x1;
        if (bx2 == -1 || bx2 < x2) bx2 = x2;
        if (by1 == -1 || by1 > y1) by1 = y1;
        if (by2 == -1 || by2 < y2) by2 = y2;
    }
    ll s2 = (ll)abs(bx1 - bx2) * abs(by1 - by2);
    if ((bx2 - bx1 == by2 - by1) && (s2 == square)) {
        puts("YES");
    } else {
        puts("NO");
    }

    return 0;
}
