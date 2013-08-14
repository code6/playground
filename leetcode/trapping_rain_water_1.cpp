class Solution {
public:
    int trap(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int ret = 0;
        int i, j;
        for (i = 0; i < n; i++) {
            int le, ri;
            le = ri = 0;
            for (j = i - 1; j >= 0; j--) le = max(le, A[j]);
            for (j = i + 1; j < n; j++) ri = max(ri, A[j]);
            ret += max(A[i], min(le, ri)) - A[i];
        }
        return ret;
    }
};
