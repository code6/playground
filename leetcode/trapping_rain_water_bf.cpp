class Solution {
public:
    int trap(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int i, j;
        int ans = 0;
        set<pair<int, int> > S;
        for (i = 0; i < n; i++) {
            int le, ri;
            int pl, pr;
            le = ri = -1;
            for (j = i -1; j >=0 ; j--) {
                if (A[j] > A[i]) {
                    le = A[j];
                    pl = j;
                    break;
                }
            }
            for (j = i + 1; j < n; j++) {
                if (A[j] > A[i]) {
                    ri = A[j];
                    pr = j;
                    break;
                }
            }
            if (le == -1 || ri == -1) {
                continue;
            }
            if (S.find(make_pair(pl, pr)) == S.end()) {
                ans += (min(le, ri) - A[i]) * (pr - pl - 1);
                S.insert(make_pair(pl, pr));
            }
            
        }        
        return ans;
    }
};
