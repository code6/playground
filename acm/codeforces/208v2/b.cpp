#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <ctime>
#include <cassert>

using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define range(i, n) for (int i=0; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

int n, l, r, ql, qr;
vector<int> vw;

int main() {
#ifndef ONLINE_JUDGE
    freopen("b.in", "r", stdin);
#endif
    int n;
    cin >> n;
    vector<string> vs;
    range(i, n) {
        string str;
        cin >> str;
        vs.pb(str);
    }

    string target_text = "<3";
    range(i, n) {
        target_text += vs[i] + "<3";
    }
    string encode_text;
    cin >> encode_text;

    int at = 0;
    range(i, encode_text.size()) {
        if (encode_text[i] == target_text[at]) {
            at ++;
            if (at == target_text.size()) {
                break;
            }
        }
    }
    cout << (at == target_text.size() ? "yes" : "no") << endl;


    return 0;
}
