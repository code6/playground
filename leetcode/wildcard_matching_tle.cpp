

class Solution {
public:
    map<pair<int, int>, bool> mem;
    
    void update(bool & ret, bool tmp) {
        if (tmp) {
            ret = tmp;
        }
    }
    
    bool match(int la, int lb, const char *sa, const char *sb) {
        if (la < 0 || lb < 0) {
            if (la < 0 && lb <0) {
                return true;
            }
            if (la < 0) {
                for (int i = 0; i <= lb; i++) {
                    if (sb[i] != '*') {
                        return false;
                    }
                }
                return true;
            }
            return false;
        }
        
        pair<int, int> state = make_pair(la, lb);
        
        if (mem.find(state) != mem.end()) {
            return mem[state];
        }
        
        bool & ret = mem[state];        
        ret = false;
        
        if (sb[lb] == '?') {
            update(ret, match(la - 1, lb - 1, sa, sb));
        } else {
            if (sb[lb] == '*') {
                for (int i = -1; i <= la; i++) {
                    update(ret, match(i, lb - 1, sa, sb));
                    if (ret) {
                        break;
                    }
                }
                
            } else {
                if (sb[lb] == sa[la]) {
                    update(ret, match(la - 1, lb - 1, sa, sb));
                }
            }
        }
        
        return ret;
    }
    
    bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        mem.clear();
        int len_s = strlen(s);
        int len_p = strlen(p);
        return match(len_s - 1, len_p - 1, s, p);
    }
};
