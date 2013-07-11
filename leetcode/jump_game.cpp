class Solution {
public:
    bool canJump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int rightmost = 0;
        int i;
        for (i = 0; i < n; i++) {
            if (i > rightmost) break;
            rightmost = max(rightmost, i + A[i]);
        }
        return rightmost >= n - 1;
    }
};
