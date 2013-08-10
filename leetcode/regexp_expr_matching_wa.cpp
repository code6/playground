class Solution {
public:
    bool isequal(char a, char b) {
        return a==b || (a=='.' || b =='.');
    }
    bool isMatch(const char *s, const char *p) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function    
        int ls = strlen(s);
        int lp = strlen(p);
        set<int> vs, nvs;
        vs.insert(0);
        for (int i = 0; i < lp; i++) {
            nvs.clear();
            if (p[i + 1] == '*') {
                for (set<int>::iterator it = vs.begin(); it != vs.end(); it++) {
                    int at = *it;
                    nvs.insert(at);
                    for (;at < ls; at++) {
                        if (isequal(s[at], p[i])) {
                            nvs.insert(at+1);
                        }
                    }
                }
                i++;
            } else {
                for (set<int>::iterator it = vs.begin(); it != vs.end(); it++) {
                    int at = *it;
                    if (isequal(s[at], p[i])) {
                        nvs.insert(at+1);
                    }
                }
            }
            vs = nvs;
        }
        return vs.find(ls) != vs.end();
    }
};
