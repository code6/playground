class Solution {
public:
    vector<vector<int> > fourSum(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<int> > ret;
        vector<int> data = num;
        sort(data.begin(), data.end());
                
        int i, j, k;
        int next_k;
        for (i = 0; i < data.size(); i++) {
            if (i > 0 && data[i] == data[i - 1]) continue;
            for (j = i + 1; j < data.size(); j++) {
                if (j > i + 1 && data[j] == data[j - 1]) continue;
                for (k = j + 1; k < data.size(); k ++) {
                    if (k > j + 1 && data[k] == data[k - 1]) continue;
                    int d = target - data[i] - data[j] - data[k];
                    if (d < data[k]) break;
                    bool found = binary_search(data.begin() + k + 1, data.end(), d);
                    if (found) {
                        vector<int> row;
                        row.push_back(data[i]);
                        row.push_back(data[j]);
                        row.push_back(data[k]);
                        row.push_back(d);
                        ret.push_back(row);
                    }
                
                }
            }
        }
        
        
        
        return ret;
    }
};
