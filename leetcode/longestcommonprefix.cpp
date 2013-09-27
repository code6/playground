class Solution {
public:
    string longestCommonPrefix(vector<string> &strs) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (strs.size() == 0) {
            return "";
        }
        string ret = strs[0];
        for (int i = 1; i < strs.size(); i++) {            
            int j;
            for ( j = 0; j < min(ret.size(), strs[i].size()); j++) {
                if (ret[j] != strs[i][j]) {
                    break;
                }
            }
            ret = ret.substr(0, j);
            if (ret == "") {
                break;
            }
        }
        return ret;
    }
};
