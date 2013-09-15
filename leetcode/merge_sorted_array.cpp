class Solution {
public:
    void merge(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int pa, pb, pc;
        pa = m - 1;
        pb = n - 1;
        pc = n + m - 1;
        while (pa >= 0 && pb >= 0) {
            if (A[pa] < B[pb]) {
                A[pc--] = B[pb--];
            } else {
                A[pc--] = A[pa--];
            }
        }
        while (pa >= 0) A[pc --] = A[pa--];
        while (pb >= 0) A[pc--] = B[pb--];
    }
};
