typedef pair<int,int> PII;
#define mp make_pair

class Solution {
public:
    int largestRectangleArea(vector<int> &height) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
                
        
        int n = height.size();
        
        if (n == 0) {
            return 0;
        }
        
        vector<int> le, ri;
        le.resize(n + 1);
        ri.resize(n + 1);
        stack<PII> s;
        s.push(mp(0, INT_MIN));
        for (int i = 0; i < n; i++) {
            int pos = i + 1;
            int val = height[i];
            while (!s.empty() && s.top().second >= val) {
                s.pop();
            }
            le[pos] = s.top().first;
            s.push(mp(pos, val));
        }
        while (!s.empty()) {
            s.pop();
        }
        s.push(mp(n + 1, INT_MIN));
        for (int i = n - 1; i >= 0; i--) {
            int pos = i + 1;
            int val = height[i];
            while (!s.empty() && s.top().second >= val) {
                s.pop();
            }
            ri[pos] = s.top().first;
            s.push(mp(pos, val));
        }
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            ans =max(ans, height[i -1] * (ri[i] - le[i] - 1));
        }
        return ans;
    }
};
