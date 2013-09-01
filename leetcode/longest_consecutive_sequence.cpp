class Solution {
public:
    
    int longestConsecutive(vector<int> &num) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        //prev[i] : wheather i - 1 exists 
        //next[i] : wheather i + 1 exists
        unordered_map<int, bool> prev, next;            
        for (int i = 0; i < num.size(); i++) {
            prev[num[i]] = next[num[i]] = false;
        }
        for (int i = 0; i < num.size(); i++) {
            int val = num[i];
            if (prev.find(val - 1) != prev.end()) {
                prev[val] = true;
            }
            if (next.find(val + 1) != next.end()) {
                next[val] = true;
            }
        }
        int ans = 0;
        for (int i = 0; i < num.size(); i++) {
            int val = num[i];
            if (!prev[val]) {
                int tmp = 1;
                while (next[val]) {
                    tmp += 1;
                    val ++;
                }
                ans = max(ans, tmp);
            }
        }
        return ans;
    }
};
