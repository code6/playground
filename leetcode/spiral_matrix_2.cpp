class Solution {
public:
    vector<vector<int> > generateMatrix(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ret;
        ret.resize(n);
        int i, j;
        for (i = 0; i < n; i++) ret[i].resize(n);
        char dir[][2] = {
          {0, 1},
          {1, 0},
          {0, -1},
          {-1, 0},
        };
        
        int cnt = 0;
        int x, y, d;
        x = y = d = 0; 
        
        while (cnt < n * n) {
            cnt ++;
            ret[x][y] = cnt;
            int nx = x + dir[d][0];
            int ny = y + dir[d][1];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n || ret[nx][ny]!=0) {
                d = (d + 1) % 4;
                x +=dir[d][0];
                y +=dir[d][1];
            } else {
                x = nx;
                y = ny;
            }
        }
        return ret;
    }
};
