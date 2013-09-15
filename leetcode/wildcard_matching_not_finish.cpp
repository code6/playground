

class Solution {
public:
    
    
    bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        mem.clear();
        int len_s = strlen(s);
        int len_p = strlen(p);
        vector<string> p_arr;
        bool star_first, star_end;
        
        star_first = star_end = false;
        
        if (len_p) {
            string cur = "";
            for (int i = 0; i < len_p; i++) {
                if (p[i] == '*') {
                    if (cur != "") {
                        p_arr.push_back(cur);                        
                    }
                    cur = "";
                } else {
                    cur += p[i];
                }
            }
            star_first = p[0] == '*';
            star_end = p[len_p - 1] == '*';
        }
        
        if (p_arr.size() == 0) {
            if (len_s == 0) {
                return true;
            } else {
                return false;
            }
        } else {
            int f = 0, r = len_s - 1;
            int pf = 0, pr = p_arr.size() - 1;
            
            if (!star_first) {
                if (match(s, p, 0, p_arr[pf].size() - 1, 0, p_arr[pf].size() - 1)) {
                    f = p_arr[0].size();
                    pf ++;
                } else {
                    return false;
                }
            }
            
            if (!star_end) {
                if (match(s, p, len_s - p_arr[pr].size(), len_s - 1,
                                len_p - p_arr[pr].size(), len_p - 1)) {
                    r = len_s - p_arr[0].size() - 1;
                    pr --;
                } else {
                    return false;
                } 
            }
            
            
            
        }
        
    }
};
