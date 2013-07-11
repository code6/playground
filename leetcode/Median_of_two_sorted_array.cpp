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
       
       int lo, hi, mid;
       lo = 0;
       hi = min(k - 1, m - 1);
       while (lo <= hi) {
           mid = (lo + hi) / 2;
           int left = k - 1 - mid;
			 
           if (left > n || (left >0  && left <= n && B[left -1] > A[mid]) ){
               lo = mid + 1;
           } else {
               hi = mid - 1;
           }
       }
       
       //check low
       if (lo < m) {
           int next = ((k - 1 - lo) -1 ) +1;
           if ((next < n && B[next] >= A[lo]) || next >= n) {
               return A[lo];
           }
       }
       //otherwise it's high
       return B[k - (hi + 1) -1];
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

using namespace std;
int main(int argc, char *argv[]) {
	int arr[] = {1,2,3,4,5,6};
	int brr[] = {7,8};
	int la = sizeof(arr) / sizeof(int);
	int lb = sizeof(brr) / sizeof(int);
	Solution sol = Solution();
	double res;
	res = sol.findMedianSortedArrays(arr, la, brr, lb);
	cout<< res<< endl;
	res = sol.findMedianSortedArrays(brr, lb, arr, la);
	cout << res << endl;

}