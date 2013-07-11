class Solution {
public:
    
    bool check(char *haystack, char *needle) {
        while ((*haystack != '\0') && (*needle != '\0') ){
            if ((*haystack) != (*needle)) break;
            haystack++;
            needle++;
        }
        return ((*haystack == '\0') && (*needle == '\0'));
    }
    
    char *strStr(char *haystack, char *needle) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        if (*needle == '\0') {
            return haystack;
        }
        
        while (*haystack != '\0') {
            if( (*haystack) == (*needle)) {
                if (check(haystack, needle)) {
                    return haystack;
                }
                haystack ++;
            }
        }
        
        return NULL;
    }
};
