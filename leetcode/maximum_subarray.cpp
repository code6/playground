class Solution {
public:
    int maxSubArray(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0) return 0;
        
        int best = A[0];
        int tmp = 0;
        int i;
        for (i = 0; i < n; i++) {
            tmp = tmp + A[i];
            best = max(best, tmp);
            if (tmp < 0) tmp = 0;
        }
        return best;
    }
};
