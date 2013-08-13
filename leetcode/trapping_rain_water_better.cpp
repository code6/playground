class Solution {
public:
    int trap(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0) return 0;
        int ret = 0;
        int i, j;
        vector<int> le, ri;
        le.resize(n);
        ri.resize(n);

        le[0] = A[0];
        for (i = 1; i < n; i++) le[i] = max(le[i-1], A[i]);
        ri[n - 1] = A[n - 1];
        for (i = n - 2; i >= 0; i--) ri[i] = max(ri[i + 1], A[i]);

        for (i = 0; i < n; i++) {
            ret += max(A[i], min(le[i], ri[i])) - A[i];
        }
        return ret;
    }
};
