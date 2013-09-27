class Solution {
public:
    int firstMissingPositive(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
       for (int i = 0; i < n; i++) {
            int val = A[i];
            if (val >0 && val <= n && A[val - 1] != val) {
                swap(A[val-1], A[i]);  
                i--;
            }
       }
       for (int i = 0; i < n; i++) {
           if (A[i] != i + 1) {
               return i + 1;
           }
       }
       return n + 1;
    }
};
