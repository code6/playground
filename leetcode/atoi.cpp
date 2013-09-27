class Solution {
public:
    bool isspace(char c) {
        return c == ' ' || c == '\t';
    }
    
    bool isdigit(char c) {
        return '0' <= c && c <= '9';
    }
    
    int atoi(const char *str) {
        
        int at = 0;
                
        while (isspace(str[at])) {            
            at++;
        }
        
        int sign = 1;
        if (str[at] == '-' || str[at] == '+') {
            sign = str[at++]  ==  '-' ? -1:1;
        }
        
        int val = 0;
        while (isdigit(str[at])) {
            int dig = str[at++] - '0';
            if (sign == 1) {
              
              if (val > (INT_MAX - dig) / 10) {
                  //overflow
                  val = INT_MAX;
                  break;
              }
              val = val * 10 + dig;                    
            } else {
              if (val < (INT_MIN + dig) / 10) {
                  //underflow
                  val = INT_MIN;
                  break;
              }
              val = val * 10 - dig;
            }                        
        }        
        return val;
    }
};
