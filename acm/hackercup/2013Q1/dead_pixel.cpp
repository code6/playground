#include <iostream>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>

using namespace std;

const int MAX = 40000 + 50;

int W, H,P,Q,N,X,Y,A,B,C,D;

//x[0] = X
//y[0] = Y
//x[i] = (x[i - 1] * a + y[i - 1] * b + 1) % W (for 0 < i < N)
//y[i] = (x[i - 1] * c + y[i - 1] * d + 1) % H (for 0 < i < N)

bool board[MAX][MAX];
int score[MAX][MAX];

int get_val(int x1, int y1, int x2, int y2) {
    return score[x2][y2] - score[x2][y1 - 1] - score[x1 - 1][y2] + score[x1 - 1][y1 - 1];
}

void printboard()
{
    int i, j;
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int calc() {
    memset(board, false, sizeof(board));
    memset(score, 0, sizeof(score));
    int px, py;
    int tx, ty;
    board[Y][X] = true;
    px = X, py = Y;
    int i, j;
    for (i = 1; i < N; i++) {
        tx = (px * A + py * B + 1) % W;
        ty = (px * C + py * D + 1) % H;
        board[ty][tx] = true;
        px = tx, py = ty;
    }
    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {
            px = i + 1;
            py = j + 1;
            score[px][py] = score[px - 1][py] + score[px][py - 1] - score[px - 1][py - 1] + board[i][j];
        }
    }

    int ret = 0;

    for (i = 1; i <= H; i++) {
        for (j = 1; j <= W; j++) {
            ty = i + Q - 1;
            tx = j + P - 1;
            if (tx <= W && ty <= H) {
                int s = get_val(i, j, ty, tx);
                if (s == 0) {
                    ret ++;
                }
            }
        }
    }
    return ret;
}

int main() {
    freopen("c.in", "r", stdin);
    //freopen("c.out", "w", stdout);
    int t;
    cin >> t;
    int m;
    //W, H, P, Q, N, X, Y, a, b, c, d
    for (int ca = 1; ca <= t; ca++) {
        cin >> W >> H >> P >> Q >> N >> X >> Y >> A >> B >> C >> D;
        int ans = calc();
        printf("Case #%d: %d\n", ca, ans);
    }
    return 0;
}
