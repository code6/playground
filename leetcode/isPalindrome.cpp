class Solution {
public:
    bool isPalindrome(string s1) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        string s = "";
        for (int i = 0; i < s1.size(); i++) if (isalnum(s1[i])) s+=s1[i];
        
        if (s.size() == 0) return true;
        
        for (int i = 0; i < s.size() / 2; i++) {
            char c1 = tolower(s[i]);
            char c2 = tolower(s[s.size() - 1 - i]);
            if (isalnum(c1) || isalnum(c2)) {
                if (c1 != c2) {
                    return false;
                }
            }
        }
        return true;
    }
};
