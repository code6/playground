class Solution {
public:
    vector<string> rec(int dep, int n, int val) {
        vector<string> ret;
        if (dep == n) {
            if (val == 0) {
                ret.push_back("");
                return ret;
            } else {
                return ret;
            }
        }
        int i;
        vector<string> tmp; 
        tmp = rec(dep + 1, n , val + 1);
        for (i = 0; i < tmp.size(); i++) {
            ret.push_back('(' + tmp[i]);
        }
        if (val > 0) {
            tmp = rec(dep + 1, n, val - 1);
            for (i = 0; i < tmp.size(); i++) {
                ret.push_back(')' + tmp[i]);
            }
        }
        
        return ret;
        
    }
    vector<string> generateParenthesis(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        return rec(0, 2 * n, 0);
        
    }
};
