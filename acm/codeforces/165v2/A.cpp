#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        if ( 180 -n > 0 && 360  % (180 - n) == 0) {
            puts("YES");
        } else {
            puts("NO");
        }
    }
    return 0;
}
