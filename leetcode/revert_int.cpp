class Solution {
public:
    int reverse(int x) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        long long bx = x;
        int sign = bx < 0 ? -1 : 1;
        bx = abs(bx);
        long long bx_rev = 0;
        while (bx) {
            bx_rev =(bx_rev * 10) + (bx % 10);
            bx /= 10;
        }
        return (int)(bx_rev * sign);
    }
};
