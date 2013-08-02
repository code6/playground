class Solution {
public:
    int maximalRectangle(vector<vector<char> > &matrix) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > sum;
    
        
        int n = matrix.size();
        
        if (n == 0) return 0;
        
        int m = matrix[0].size();
        
        if (m == 0) return 0;
                
        int i, j;
            
        sum.resize(n + 1);
        sum[0].resize(m + 1);
        for (i = 1; i <= n; i++) {
            sum[i].resize(m + 1);    
            for (j = 1; j <= m; j++) {
                sum[i][j] = sum[i - 1][j] + (matrix[i - 1][j - 1] - '0');                
            }
        }
        
        int best = 0;        
        
        int i1, j1;
        for (i = 1; i <= n; i++) {
            for (i1 = i; i1 <= n; i1++) {
                
                int sz = i1 - i + 1;
                int tmp_len = 0;
                int best_len = 0;
                for (j = 1; j <= m; j++) {
                    bool filled = (sum[i1][j] - sum[i-1][j]) == sz;
                    if (filled) {
                        tmp_len ++;
                        best_len = max(best_len, tmp_len);
                    } else {
                        best_len = max(best_len, tmp_len);
                        tmp_len = 0;
                    }
                }
                int tmp = best_len * sz;
                best = max(best, tmp);
            }           
        }
        return best;
        
    }
};
