c:
    void nextPermutation(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int n = num.size();
        if (n == 1) return;
        int i;
        for ( i = n - 2; i >= 0; i--) {
            if (num[i] < num[i + 1]) break;
        }
        if (i < 0) {
            sort(num.begin(), num.end());
        } else {
            int val = num[i];
            sort(num.begin() + i + 1, num.end());
            for (int j = i + 1; j < n; j++) {
                if (num[j] > val) {
                    swap(num[j], num[i]);
                    break;
                } 
            }
        }
    }
};
