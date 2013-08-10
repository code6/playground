class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ret;
        sort(num.begin(), num.end());
        int i, j;
        for (i = 0; i < num.size(); i++) {
            if (i && num[i] == num[i - 1]) continue;
            for (j = i + 1; j < num.size(); j++) {
                if (j > i + 1 && num[j] == num[j - 1]) continue;
                int val = 0 - num[i] - num[j];
                bool found = binary_search(num.begin() + j + 1, num.end(), val);
                if (found) {
                   vector<int> row;
                   row.push_back(num[i]);
                   row.push_back(num[j]);
                   row.push_back(-num[i]-num[j]);
                   ret.push_back(row); 
                }
            }
        }
        return ret;
    }
};
