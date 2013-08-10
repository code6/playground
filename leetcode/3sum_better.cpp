class Solution {
public:
    vector<vector<int> > threeSum(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ret;
        sort(num.begin(), num.end());
        for (int i = 0; i + 2 < num.size(); i++) {
            if (i && num[i]  == num[i - 1]) {
                continue;
            }
            int j = i + 1; 
            int k = num.size() - 1;
            while (j < k) {
                int val = num[i] + num[j] + num[k];
                if (val > 0) {
                    k --;
                } else {
                    if (val < 0) {
                        j ++;
                    } else {
                        vector<int> row;
                        row.push_back(num[i]);
                        row.push_back(num[j]);
                        row.push_back(num[k]);
                        ret.push_back(row);
                        j++;
                        while (j < k && num[j] == num[j-1]) j++;
                    }
                }
            }
        }
        return ret;
    }
};
