class Solution {
public:
    int climbStairs(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> ret(n+1);
        ret[0] = 1;
        ret[1] = 1;
        for (int i = 2; i <= n; i++) ret[i] = ret[i-1] + ret[i-2];
        return ret[n];        
    }
};
