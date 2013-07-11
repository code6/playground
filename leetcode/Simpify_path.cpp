class Solution {
public:
    string simplifyPath(string path) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<string> path_arr;
       
        path_arr.clear();
       
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == '/') {
                if (path_arr.size() == 0 || (path_arr.size() > 0 && path_arr.back() != "/")) {
                    path_arr.push_back("/");
                }
            } else {
                if (path_arr.back() == "/") {
                    string cur = "";
                    cur += path[i];
                    path_arr.push_back(cur);
                } else {
                    path_arr.back() += path[i];
                }
            }
            //cout << " i = " << i +"" << " path_arr.back() = " << path_arr.back() << endl;
        }
       
       
       
        vector<string> final_arr;
        final_arr.clear();
       
        for (int i = 0; i < path_arr.size(); i++) {
            string val = path_arr[i];
            //cout << " " << path_arr[i] << endl;
            if (val == "/") continue;
           
            if (val == "..") {
                if (final_arr.size() > 0) {
                    final_arr.pop_back();
                }
            } else {
                if (val == ".") {
                   
                } else {
                    final_arr.push_back(val);       
                }
            }
        }
       
        if (final_arr.size() == 0) return "/";
        string ret = "";
        for (int i = 0; i < final_arr.size(); i++) ret += "/" + final_arr[i];
       
       
        return ret;
       
    }
};


