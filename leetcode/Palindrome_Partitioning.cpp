class Solution {
public:
    
    bool is_palindrome(string s) {
        for (int i = 0; i < s.size() / 2; i++) {
            if (s[i] != s[s.size() - 1 - i]) {
                return false;
            }
        }
        return true;
    }
    
    map<string, vector<vector<string>> > mem;
    
    vector<vector<string>> calc(string s) {
        
        if (mem.find(s) != mem.end()) {
            return mem[s];
        }
        
        mem[s] = vector<vector<string>>();
        
        if (s == "") {
            mem[s].push_back(vector<string>());
            return mem[s];
        }
        
        for (int f = 0; f < s.size(); f++) {
            string prev = s.substr(0, f);
            string next = s.substr(f, s.size());
            if (is_palindrome(next)) {
                vector<vector<string>> vp = calc(prev);
                for (int i = 0; i < vp.size(); i++) {
                    vp[i].push_back(next);
                    mem[s].push_back(vp[i]);
                }                
            }
        }
        
        return mem[s];
        
    }

    vector<vector<string>> partition(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        mem.clear();
        return calc(s);
        
    }
};
