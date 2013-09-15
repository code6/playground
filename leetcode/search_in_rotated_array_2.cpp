class Solution {
public:
    bool search(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int lo = 0, hi = n - 1, mid;
        while (lo <= hi) {
            mid = (lo + hi) / 2;
            if (A[mid] == target) return true;
            
            for (; lo <= mid && A[lo] == A[mid]; lo++);
            
            if (lo <= mid && ((A[lo] < A[mid] &&  (A[lo] <= target && target <= A[mid])) ||
                (A[lo] > A[mid] && (A[lo] <= target || target < A[mid]))
                ))    hi = mid - 1;            
            else lo = mid + 1;
            
        }
        return false;
    }
};
