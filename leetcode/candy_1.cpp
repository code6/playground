class Solution {
public:
    int candy(vector<int> &ratings) {
        int n = ratings.size();
        vector<int> candies(n);
        int i, j;
        for (i = 0; i < n; i=j) {
            j = i+1;
            while (j < n && ratings[j] < ratings[j-1]) j++;
            candies[j-1] = 1;
            for (int k = j-2; k>= i;k--) candies[k] = candies[k+1]+1;
            if (i && ratings[i-1]<ratings[i]) candies[i] = max(candies[i], candies[i-1]+1);
        }
        int res = 0;
        for (int i =0; i < n; i++) res += candies[i];

        return res;
    }
};
