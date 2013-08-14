
typedef pair<int, int> PII;
#define mp make_pair
#define fs first
#define sc second

class Solution {
public:
    void solve(vector<vector<char>> &board) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        if (board.size() == 0) return ;
        
        int n , m;
        n  = board.size();
        m = board[0].size();
        
        vector<vector<bool> > visit;        
        visit.resize(n);
        for (int i = 0; i < n; i++) {
            visit[i].resize(m);
        }
        
        int i, j;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    if (board[i][j] != 'O' || visit[i][j]) {
                        continue;
                    }
                    int dir[][2] = {
                      {0, 1},
                      {0, -1},
                      {1, 0},
                      {-1, 0},
                    };
                    visit[i][j] = true;
                    queue<PII> Q;
                    Q.push(mp(i, j));
                    while (!Q.empty()) {
                        PII cur = Q.front();
                        Q.pop();
                        for (int d = 0; d < 4; d++) {
                            PII next = mp(cur.fs + dir[d][0], cur.sc + dir[d][1]);
                            if (next.fs < 0 || next.fs >= n || next.sc < 0 || next.sc >= m || 
                                board[next.fs][next.sc] != 'O' || visit[next.fs][next.sc]) {
                                    continue;
                            }
                        
                            visit[next.fs][next.sc] = true;
                            Q.push(next);                        
                        }
                    }
                }
            }
        }
        
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < m ;j++) {
                if (board[i][j] == 'O' and !visit[i][j]) {
                    board[i][j] = 'X';
                }
            }
        }
    }
};
