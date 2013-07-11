class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int> > &obstacleGrid) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int>> dp;
        int n = obstacleGrid.size();
        int m = obstacleGrid[0].size();
        dp.resize(n);
        int i, j;
        for (i = 0; i < n; i++) dp[i].resize(m);
        dp[0][0] = obstacleGrid[0][0] == 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (i == 0 && j == 0) continue;
                dp[i][j] = 0;
                if (obstacleGrid[i][j] == 1) continue;
                if (i > 0) dp[i][j] += dp[i - 1][j];
                if (j > 0) dp[i][j] += dp[i][j - 1];
            }
        }
        return dp[n - 1][m - 1];
    }
};
