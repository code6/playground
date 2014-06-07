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

const int MAX = 1000 + 500;

typedef pair<int, int> PII;
#define mp make_pair

int dir[][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

int  n, m;
char bo[MAX][MAX];
int dis[MAX][MAX];
PII start, end;

int main() {
    //freopen("b.in", "r", stdin);
    cin >> n >> m;
    range(i, n)
        range(j, m) {
            scanf(" %c ", &bo[i][j]);
            //cout << bo[i][j] << endl;
            if (bo[i][j] == 'E') {
                end = mp(i, j);
            }
            if (bo[i][j] == 'S') {
                start = mp(i, j);
            }
        }
    memset(dis, -1, sizeof(dis));
    queue<PII> Q;
    Q.push(end);
    dis[end.first][end.second] = 0;
    while (!Q.empty()) {
        PII cur = Q.front();
        Q.pop();
        range(d, 4) {
            PII tmp;
            tmp.first = cur.first + dir[d][0];
            tmp.second = cur.second + dir[d][1];
            if (tmp.first < 0 || tmp.first >= n || tmp.second < 0 || tmp.second >= m || bo[tmp.first][tmp.second] == 'T' ||
                    dis[tmp.first][tmp.second] != -1 ) {
                continue;
            }
            dis[tmp.first][tmp.second] = dis[cur.first][cur.second] + 1;
            Q.push(tmp);
        }
    }

    int mydis = dis[start.first][start.second];
//    cout << start.first << ' ' << start.second << ' ' << mydis << endl;
    int ans = 0;

    range(i, n)
        range(j, m) {
            if ('1' <= bo[i][j] && bo[i][j] <= '9') {
                if (dis[i][j] != -1 && dis[i][j] <= mydis) {
 //                   cout << i << ' ' << j << endl;
                    ans += bo[i][j] - '0';
                }
            }
        }
    
    cout << ans << endl;

    return 0;
}
