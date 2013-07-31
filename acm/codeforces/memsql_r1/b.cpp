#include <string.h>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;
int n;

int f[100];
void bf() {
    map<int, int> M;
    f[1] = 0;
    int i, j;
    for (i = 2; i < 100; i++) {
        if (i % 2 == 0) {
            f[i] = f[i / 2] + (i / 2);
        } else {
            f[i] = i * (i - 1) / 2;
        }
        printf("f[%d] = %d\n", i, f[i]); M[f[i]] ++;
    }
}


int main() {
    bf();
    return 0;
}
