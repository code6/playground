class Solution {
public:
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
                
        int len = strlen(needle);
        
        if (len == 0) {
            return haystack;
        }
        
        
        vector<int> fail(len + 1);
        fail[0] = -1;
        for (int i = 1; i <= len; i++) {
            int j = fail[i - 1];
            while (j >= 0 && needle[i - 1] != needle[j]) {
                j = fail[j];
            }
            fail[i] = j + 1;
        }
        
        int match_pos = 0;
        
        for (; *haystack ;) {
            if (*haystack == needle[match_pos]) {
                match_pos ++;
                haystack++;
                if (match_pos == len) {
                    return haystack - len;
                }
            } else {
                match_pos = fail[match_pos];
                if (match_pos < 0) {
                    haystack ++;
                    match_pos = 0;
                }
            }
        }
        
        return NULL;        
    }
};
