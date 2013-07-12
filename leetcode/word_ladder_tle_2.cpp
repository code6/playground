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
        vector<vector<int> > g;
        
        int i, j, k;
        g.resize(n);
        for (i = 0; i < n; i++) {
            for (j = i + 1; j < n; j++) {
                if (can(word_list[i], word_list[j])) {
                    g[i].push_back(j);
                    g[j].push_back(i);
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
