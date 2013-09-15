struct State {
    int a1, a2, b1, b2;
    bool operator<(const State & rhs) const {
        if (a1 != rhs.a1) {
            return a1 < rhs.a1;
        }
        if (a2 != rhs.a2) {
            return a2 < rhs.a2;
        }
        if (b1 != rhs.b1) {
            return b1 < rhs.b1;
        }
        return b2 < rhs.b2;
    }
};

class Solution {
public:
    map<State, bool> M;
    bool _isScramble(const string &s1, const string &s2, State s) {                       
        if (s.a2 - s.a1 != s.b2 - s.b1) {
            return false;
        }
        
        if (s.a1 == s.a2) {
            return s1[s.a1] == s2[s.b1];
        }
        
        if (M.find(s) != M.end()) {
            return M[s];
        }
        bool & ret = M[s];
        ret = false;
        
        for (int i = s.a1; i < s.a2; i++) {
            for (int j = s.b1; j < s.b2; j++) {
                
                if ( _isScramble(s1, s2, (State){s.a1, i, s.b1, j})
                 && _isScramble(s1, s2, (State){i + 1, s.a2, j + 1, s.b2})) {
                      return ret = true;
                 }
                if ( _isScramble(s1, s2, (State){s.a1, i, j + 1, s.b2})
                  && _isScramble(s1, s2, (State){i + 1, s.a2, s.b1, j})) {
                      return ret = true;
                  } 
            }
        }
        
        return ret;
    }
    bool isScramble(string s1, string s2) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (s1.size() != s2.size()) return false;
        int len = s1.size();
        if (len == 0) return true;
        M.clear();
        return _isScramble(s1, s2, (State){0, len - 1, 0, len - 1});
    }
};

