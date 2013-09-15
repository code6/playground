

class Solution {
public:
    map<pair<int, int>, bool> mem;
    vector<int> prev;
    
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
        
        if (sb[lb] != '*') {
            bool legal = true;
            for (; lb >= 0 && sb[lb] != '*'; lb --, la--) {
                if (la <0 || (sa[la] != sb[lb] && sb[lb] != '?')) {
                    legal = false;
                    break;
                }                
            }
            if (legal) {
                update(ret, match(la, lb, sa, sb));     
            }          
        } else {
            if (sb[lb] == '*') {
                lb = prev[lb];
                for (int i = la; i >= -1; i--) {
                    update(ret, match(i, lb, sa, sb));
                    if (ret) {
                        break;
                    }
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
        if (len_p) {
            prev.clear();
            for (int i = 0; i < len_p; i++) {
                if (p[i] != '*') {
                    prev.push_back(i);
                } else {
                    if (prev.size()) 
                        prev.push_back(prev.back());
                    else
                        prev.push_back(-1);
                }
            }
        }
        return match(len_s - 1, len_p - 1, s, p);
    }
};
