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
        int m = word_list[0].size();
        vector<vector<int> > g;
        
        
        int i, j, k;
        g.resize(n);
        for (k = 0; k < m; k++) {
            map<string, unordered_set<int> > V;
            for (i = 0; i < n; i++) {
                 {
                    string miss_one = word_list[i].substr(0, k) + word_list[i].substr(k + 1);
                    V[miss_one].insert(i);
                }
            }
            for (map<string, unordered_set<int> >::iterator it = V.begin(); it != V.end(); it++) {
               vector<int> vl(it->second.begin(), it->second.end());
                for (i = 0; i < vl.size(); i++) {
                    for (j = i + 1; j < vl.size(); j++) {
                        int x = vl[i];
                        int y = vl[j];
                        g[x].push_back(y);
                        g[y].push_back(x);
                    }
                }
            }
        }
        
        int s_pos = dict_map[start];
        int e_pos = dict_map[end];
        vector<int> dis;
        dis.resize(n);
        for (i = 0; i < n; i++) dis[i] = -1;
        dis[s_pos] = 0;
        
        queue<int> Q;
        Q.push(s_pos);
        
        while (!Q.empty()) {
            int cur = Q.front();
            Q.pop();
            for (i = 0; i < g[cur].size(); i++) {
                int next = g[cur][i];
                if (dis[next] != -1) continue;
                dis[next] = dis[cur] + 1;
                if (next == e_pos) return dis[next] + 1;
                Q.push(next);
            }
        }
        
        return 0;
    }
};
