#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() 
        vector<int> last_pos;
        int i, j;
        for (i = 0; i < 1000; i++) last_pos.push_back(-1);
        int ans = 0;
        int f = -1;
        for (i = 0; i < s.size(); i++) {
            char ch = s[i];
            int ch_pos = int(ch);
            f = max(f, last_pos[ch_pos]);
            ans = max(ans, i - f);
            last_pos[ch_pos] = i;
            
        }
        
        return ans;
        
    }
};

using namespace std;
int main(int argc, char *argv[]) {
	
}