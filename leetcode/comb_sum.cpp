class Solution {
public:
    vector<vector<int> > rec(int prev, const vector<int> &cand, int target) {
        vector<vector<int> > ret;
        if (target == 0) {
            vector<int> row;
            ret.push_back(row);
            return ret;
        }
        
        int i;
        for (i = prev; i < cand.size(); i++) {
            if (i > 0 && cand[i] == cand[i - 1]) continue;
            if (target < cand[i]) break;
            vector<vector<int> > tmp = rec(i, cand, target - cand[i]);
            int j;
            for (j = 0; j < tmp.size(); j++) {
                vector<int> row = tmp[j];
                row.insert(row.begin(), cand[i]);
                ret.push_back(row);
            }
        }
        
        return ret;
        
    }
    vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> sorted_cand = candidates;
        sort(sorted_cand.begin(), sorted_cand.end());
        vector<vector<int> > ret = rec(0, sorted_cand, target);
        return ret;
    }
};
