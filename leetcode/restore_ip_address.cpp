bool isvalid(string num) {
    if (num.size() == 0) return false;
    if (num[0] == '0' && num.size() > 1) return false;
    if (num.size() > 3) return false;
    int val = 0;
    for (int i = 0; i < num.size(); i++) {
        val = val * 10 + num[i] - '0';
    }
    if (val > 255) return false;
    return true;
}


class Solution {
public:
    vector<string> rec(const string & s, int f, int part) {
        vector<string> ret;
        
        if (f >= s.size()) {
            return ret;
        }
        
        if (part == 1) {
            string cur = s.substr(f);
            if (isvalid(cur)) {
                ret.push_back(cur);
            }
            return ret;
        }
        
        string cur = "";
        for (; f < s.size(); f++) {
            cur += s[f];
            if (!isvalid(cur)) {
                break;
            }
            vector<string> next_list = rec(s, f + 1, part - 1);
            for (int i = 0; i < next_list.size(); i++) {
                string ans = cur + '.' + next_list[i];
                ret.push_back(ans);
            }
        }
        return ret;        
    }
    vector<string> restoreIpAddresses(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> ips = rec(s, 0, 4);
        return ips;
    }
};
