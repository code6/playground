class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int pos = lower_bound(A, A + n, target) - A;
        return pos;
    }
};
