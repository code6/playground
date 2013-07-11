#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;


class Solution {
public:

    int find_kth(int A[], int m, int B[], int n, int k) {
       if (n == 0 || m == 0) {
            if (m == 0) {
                return B[k - 1];
            } else {
                return A[k - 1];
            }
       }
       vector<int> C;
       for (int i = 0; i < m; i++) C.push_back(A[i]);
       for (int i =0; i < n; i++) C.push_back(B[i]);
       sort(C.begin(), C.end());
       return C[k - 1];
       
    }
    
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int total = n + m;
        int p1, p2;
        if (total % 2) {
            p1 = p2 = total / 2 + 1;
        } else {
            p1 = total / 2;
            p2 = p1 + 1;
        }

        
        return (find_kth(A, m, B, n, p1) + find_kth(A, m, B, n, p2)) / 2.0;
        
    }
};

int main(int argc, char *argv[]) {
	
}