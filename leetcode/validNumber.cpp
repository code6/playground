class Solution {
public:
    bool isempty(char ch) {
        return ch == ' ' || ch == '\n' || ch == '\t';
    }
    
    int acceptEmpty(const char * &s) {
        int ret = 0;
        while (isempty(*s)) s++, ret++;
        return ret;
    }
    
    int acceptFlag(const char * &s) {
        int ret = 0;
        if (*s == '-' || *s == '+') s++, ret ++;
        return ret;
    }
    
    int acceptNumber(const char * &s) {
        int ret = 0;
        while ('0' <= *s && *s <= '9') s++, ret++;
        return ret;
    }
    
    bool isNumber(const char *s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function        
        
        acceptEmpty(s);
        acceptFlag(s);
        int num1, num2;
        num1 = num2 = 0;
        num1 = acceptNumber(s);
                
        if (*s == '.') {
            s++;
            num2 = acceptNumber(s);            
        }
        
        if (num1 == 0 && num2 == 0) {
                return false;
            }
            
        if ((*s == 'e' || *s == 'E')) {
                s++;
                acceptFlag(s);
                int num3 = acceptNumber(s);
                if (num3 == 0) {
                    return false;
                }
        }
        
        acceptEmpty(s);
        if (*s != '\0') return false;

        return true;
    }
};
