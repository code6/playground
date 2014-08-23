typedef pair<int, int> PII;
class Solution {
public:
    int candy(vector<int> &ratings) {
        vector<PII> vp;
        int n = ratings.size();
        vector<int> candies(n);
        for (int i = 0; i < n; i++) {
            vp.push_back(make_pair(ratings[i], i));
            candies[i] = 1;
        }
        sort(vp.begin(), vp.end());
        int res = 0;
        for (int i = 0; i < n; i++) {
            int pos = vp[i].second;
            int cur_candy = max(max(candies[pos], pos > 0 && ratings[pos - 1] < ratings[pos] ? candies[pos-1] +1 : 0) ,pos < n -1 && ratings[pos + 1] < ratings[pos]? candies[pos+1] +1:0);
            candies[pos] = cur_candy;
            res += cur_candy;
        }
        return res;
    }
};
