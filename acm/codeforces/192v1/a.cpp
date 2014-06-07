#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
#define range(i, n) for (int i=0; i<(n); ++i)

using namespace std;

const int MAX = 100 +5;

int n ;
char board[MAX][MAX];

int main() {
    //freopen("a.in", "r", stdin);
    cin >> n;
    vector<int> row, col;
    row.resize(n);
    col.resize(n);
    range(i, n) row[i] = -1, col[i] = -1;

    range(i, n)
        range(j, n) {
            scanf(" %c ", &board[i][j]);
            if (board[i][j] != 'E') {
                    row[i] = j;
                    col[j] = i;
                }
        }

    bool rf, cf;
    rf = true;
    cf = true;
    range(i, n) if (row[i] == -1) rf = false;
    range(i, n) if (col[i] == -1) cf = false;
    if (cf || rf) {
        if (cf) {
            range(i, n) printf("%d %d\n", col[i] +1, i + 1);
        } else {
            range(i, n) printf("%d %d\n", i + 1, row[i] +1);
        }
    } else {
        puts("-1");
    }

    return 0;
}
