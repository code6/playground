class Solution {
public:
    bool can(string a, string b) {
        int diff = 0;
        int i;
        for (i = 0; i < a.size(); i++) diff += a[i] != b[i];
        return diff == 1;
    }
    int ladderLength(string start, string end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        
        map<string, int> dict_map;
        vector<string> word_list;
        int dict_index = 0;
        for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++) {
            dict_map[*it] = dict_index ++;
            word_list.push_back(*it);
        }
                
        int n = dict_index;
        vector<vector<int> > d;
        
        int i, j, k;
        d.resize(n);
        for (i = 0; i < n; i++) {
            d[i].resize(n);
            for (j = 0; j < n; j++) {
                if (i == j) d[i][j] = 0;
                else {
                
                    if (can(word_list[i], word_list[j])) 
                        d[i][j] = 1;
                    else
                        d[i][j] = 100000;
                }
            }
        }
        
        for (k = 0; k < n; k++) {
            for (i = 0; i < n; i++) {
                for (j = 0; j < n; j++) {
                   if (i == k || j == k || i == j) continue;
                   d[i][j] = min(d[i][k] + d[k][j], d[i][j]);
                }
            }
        }
        int ret =  d[dict_map[start]][dict_map[end]] ;
        if (ret > n) return 0; else return ret + 1;
    }
};
