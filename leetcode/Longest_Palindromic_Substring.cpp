#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for (int l = s.size(); l > 0; l --) {
            for (int i = 0; i < s.size(); i++) {
                int j = i + l - 1;
                if (j >= s.size()) {
                    break;
                }
                int k;
                bool ok = true;
                for (k = 0; k < l / 2; k++) {
                    if (s[i + k] != s[j - k]) {
                        ok = false;
                        break;
                    }
                }
                if (ok) {
                    return s.substr(i, l);
                }
            }
        }
        assert(1 == 0);
    }
};

int main(int argc, char *argv[]) {
	
}