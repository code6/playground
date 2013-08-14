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

typedef long long ll;
using namespace std;
const int MAX = 2000;

int n, m;
int board[MAX][MAX];

int dir[][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1,0}
};

bool valid(int x, int y) {
    return 0 <= x && x < n && 0 <= y && y < m;
}


int rowmax[MAX], colmax[MAX];

void process(int cas) {
    int i, j, u, v;
    bool ans = true;
    memset(rowmax, 0, sizeof(rowmax));
    memset(colmax, 0, sizeof(colmax));
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            rowmax[i] = max(rowmax[i], board[i][j]);
            colmax[j] = max(colmax[j], board[i][j]);
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (board[i][j] < min(rowmax[i], colmax[j])) {
                ans = false;
            }
        }
    }
    printf("Case #%d: %s\n", cas, ans ? "YES":"NO");
}

void read() {
    int i, j;
    cin >> n >> m;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            cin >> board[i][j];
        }
    }
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    freopen("B-large.in", "r", stdin);
    freopen("B-large.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}


/*
 
 
 */
