class Solution {
public:
    
    bool iszero(double x) {
        return fabs(x) < 1e-9;
    }
    
    double _pow(double x, long long n) {
        double ret = 1.0, a = x;
        while (n) {
            if (n&1) ret = ret * a;
            a = a * a;
            n >>= 1;
        }
        return ret; 
    }
    double pow(double x, int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
       if (n <= 0) {
           if (iszero(x)) {
               return 1.0;
           } else {
               return 1.0 / _pow(x, -(long long)n);
           }
       } else {
           return _pow(x, n);
       }
    }
};
