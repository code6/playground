class Solution {
public:
    bool my_next_permutation(vector<int> & num) {
        if (num.size() <= 1) return false;
        for (int i = num.size() - 2; i >= 0; i--) {
            if (num[i] < num[i + 1]) {
                 for (int j = num.size() - 1; j > i ; j--) {
                     if (num[i] < num[j]) {
                         swap(num[i], num[j]);                         
                         break;
                     }
                 }
                 int sz = num.size() - 1 - i;
                 for (int j = 0; j < sz / 2; j++) {
                     swap(num[i + 1 + j], num[num.size() - 1 - j]);
                 }
                 return true;
            }
        }
        return false;
    }
    
    vector<vector<int> > permute(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());
        vector<vector<int> > ret;
        do {
            ret.push_back(num);
        } while (my_next_permutation(num));
        
        return ret;
    }
};
