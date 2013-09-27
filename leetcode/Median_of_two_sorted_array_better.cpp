class Solution {
public:
    int find_kth(int A[], int m, int B[], int n, int k) {
        if (m > n) {
            return find_kth(B, n, A, m, k);        
        }
        if (m == 0) {
            return B[k - 1];
        }
        if (k == 1) {
            return min(A[0], B[0]);
        }
        
        int pa = min(m, k / 2);
        int pb = k - pa;
        
        if (A[pa - 1] < B[pb - 1]) {
         return find_kth(A + pa, m - pa, B, n, k - pa);   
        } else {
            if (A[pa - 1] > B[pb - 1]) {                
                return find_kth(A, m, B + pb, n - pb, k - pb);
            } else {
                return A[pa - 1];
            }
        }        
    }
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        int total = n + m;
        
        if (total == 0) {
            return 0;
        }
        
        double  ret = 0.0;        
        if (total % 2 == 0) {
            ret = (find_kth(A, m, B, n, total / 2) +
                find_kth(A, m, B, n, total / 2 + 1)) / 2.0;
        } else {
            ret = find_kth(A, m, B, n, total / 2 + 1);
        }
                      
        return ret;
        
    }
};
