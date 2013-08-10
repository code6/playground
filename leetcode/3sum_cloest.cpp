class Solution {
public:
    int threeSumClosest(vector<int> &num, int target) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        sort(num.begin(), num.end());
        int i, j;
        int ret = 0;
        int best = 0;
        bool found = false;
        for (i = 0; i < num.size(); i++) {
            if (i && num[i] == num[i - 1]) continue;
            for (j = i + 1; j < num.size(); j++) {
                if (j > i + 1 && num[j] == num[j - 1]) continue;
                int val = target - num[i] - num[j];
                int start = lower_bound(num.begin() + j + 1, num.end(), val) - num.begin();
                for (int d = -1; d <= 1; d++) {
                    int pos = start + d;
                    if (pos < num.size() && pos > j) {
                       int tmp = num[i] + num[j] + num[pos];
                       if (!found) {
                           found = true;
                           best = abs(target - tmp);
                           ret = tmp;
                       } else {
                           if (abs(target-tmp) < best) {
                               best = abs(target - tmp);
                               ret = tmp;
                           }
                       }                  
                    }
                }
            }
        }
        return ret;
    }
};
