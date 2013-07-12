class Solution {
public:
    int numDecodings(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        if (s.size() == 0) return 0;
        
        int n = s.size();
        vector<int> dp(n + 1);
        dp[0] = 1;
        int i;
        for (i = 0; i < n; i++) {
            if (s[i] != '0') {
                dp[i + 1] += dp[i];
                if (i + 1 < n) {
                    int v = (s[i] - '0') * 10 + (s[i + 1] - '0');
                    if (v <= 26) {
                        dp[i + 2] += dp[i];
                    }
                }
            }
        }
        return dp[n];
        
    }
};
