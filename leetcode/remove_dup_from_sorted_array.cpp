class Solution {
public:
    int removeDuplicates(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (n == 0) return 0;
        int new_n = 1;
        for (int i = 1; i < n; i++) {
            if (A[i] != A[new_n - 1]) {
                A[new_n++] = A[i];
            }
        }
        return new_n;
    }
};
