class Solution {
public:
    string build_line(const vector<string> &word_line, int L, bool isLast) {
        string ret = "";
        if (isLast) {
            for (int i = 0; i < word_line.size(); i++) {
                if (i) ret += ' ';
                ret += word_line[i];
            }
            int left = L - ret.size();
            for (int i = 0; i < left; i++) {
                ret += ' ';
            }
            return ret;
        }
        
        int i, j;
        int n = word_line.size();
        for (i = 0; i < n; i++) {
            L -= word_line[i].size();
        }
        
        int dis, left;
        
        if (word_line.size() > 1) {
            dis = L / (n - 1);
            left = L % (n - 1);
        } else {
            left = L;
        }
        
        for (i = 0; i < n; i++) {
            ret += word_line[i];
            if (i < n - 1) {
                int space_width = dis + (left > 0);
                left --;
                for (j = 0; j < space_width; j++) {
                    ret += ' ';
                }
            }
        }        
        
        for (i = 0; i < left; i++) ret += ' ';
        
        return ret;
        
    }
    vector<string> fullJustify(vector<string> &words, int L) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> ret;
        if (words.size() == 0) {
            return ret;
        }
        
        if (L == 0) {
            return words;
        }
        
        int i, j;
        for (i = 0; i < words.size(); i = j) {
            vector<string> word_line;
            word_line.push_back(words[i]);
            int length = words[i].size();
            for (j = i + 1; j < words.size(); j++) {
                string cur_word = words[j];                
                if (length + cur_word.size() + word_line.size() <= L) {
                    word_line.push_back(cur_word);
                    length += cur_word.size();
                } else {
                    break;
                }
            }
            ret.push_back(build_line(word_line, L, j == words.size()));
        }        
        
        return ret;
    }
};
