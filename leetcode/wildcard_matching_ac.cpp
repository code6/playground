

class Solution {
public:    
    bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
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
            
            if (cur != "") {
                p_arr.push_back(cur);
            }
            
            star_first = p[0] == '*';
            star_end = p[len_p - 1] == '*';
        }
        
        if (p_arr.size() == 0) {
            return star_first || len_s == 0;
        } else {
            int f = 0;            
            for (int i = 0; i < p_arr.size(); i++) {
                string candi = p_arr[i];
                bool found = false;
                for (int j = f; j < len_s; j++) {
                    if (j + candi.size()  - 1 >= len_s) break;
                    
                    //star_first
                    if (i == 0 && !star_first && j > 0) break;
                    
                    //star_end
                    if (i == p_arr.size() - 1 && !star_end && j + candi.size() -1 != len_s -1) continue;
                    
                    bool legal = true;
                    for (int k = 0; k < candi.size(); k++) {
                        if (s[j + k] != candi[k] && candi[k] != '?') {
                            legal = false;
                            break;
                        }
                    }
                    if (legal) {
                        found = true;
                        f =  j + candi.size();
                        break;
                    }
                }
                if (!found) {
                    return false;
                }
            }
            return true;            
        }        
    }
};

