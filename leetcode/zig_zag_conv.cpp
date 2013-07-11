

typedef pair<int, int> PII;
#define mp make_pair

class Solution {
public:
    string convert(string s, int nRows) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function  
        
        
        
        if (s.size() == 0 || nRows == 1) {
            return s;
        }
        
        int dir[][2] = {
            {1, 0},
            {-1, 1},            
        };
        
        int x, y, d;
        d = 0;
        PII pos = mp(0, 0);
        PII next;
        map<PII, char> M;
        M[pos] = s[0];
        for (int i = 1; i < s.size(); i++) {
            next.first = pos.first + dir[d][0];
            next.second = pos.second + dir[d][1];
            if (next.first < 0 || next.first >= nRows || next.second < 0) {
                d  = (d + 1) % 2;
                next.first = pos.first + dir[d][0];
                next.second = pos.second + dir[d][1];
            } else {
                
            }
            pos = next;
            M[pos] = s[i];
        }
        
        string ret = "";
        for (map<PII, char>::iterator it = M.begin(); it != M.end(); it++) {
            ret += it->second;
        }
        return ret;
        
    }
};

