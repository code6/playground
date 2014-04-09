// you can also use includes, for example:
// #include <algorithm>

#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;

int solution(string &S) {
    // write your code in C++98
    int len = S.size();
    vector<int> next, add;
    next.resize(len + 1);
    next[0] = -1;
    for (int i = 1; i <= len; i++) {
        int j = next[i - 1];
        while (j >= 0 && S[i - 1] != S[j]) {
            j = next[j];            
        }
        next[i] = j + 1;
    }
    
    ll max_val = 1000000000LL;
    ll ans = 0;    
    
    add.resize(len + 1);
    for (int i = len; i > 0; i--) {
        add[i] += 1;
        ans = min(max_val, max(ans, (long long)i * add[i]));
        add[next[i]] += add[i];        
    }    
    return ans;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        cout << solution(s) << endl;
    }
    return 0;
}

