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
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef pair<int, int> PII;
typedef vector<ULL> HV;

const int MAX = 100000 + 50;

static const int base[] = {33};
vector<int> hash_base (base, base + sizeof(base) / sizeof(base[0]));
int num_of_hash = sizeof(base) / sizeof(base[0]);

string s;
int n;
int next_pos[MAX];
int ans[MAX];

struct Mapping {
    int last_pos;
    int val;
    HV base;
    Mapping() {}
    Mapping(int last_pos, int val, HV base):last_pos(last_pos), val(val), base(base){}
};

void add_char(HV &ha, int pos, map<char, Mapping> & char_mapping) {
    char ch = s[pos];
    if (char_mapping.find(ch) == char_mapping.end()) {
        int tag = char_mapping.size() + 1;
        HV char_base;
        char_base.resize(num_of_hash);
        char_mapping[ch] = Mapping(pos, tag, char_base);
    }
    Mapping & m = char_mapping[ch];
    range(j, num_of_hash) {
        ha[j] = ha[j] * hash_base[j] + m.val;
        for (map<char, Mapping>::iterator it = char_mapping.begin(); it != char_mapping.end(); it++) {
            (it->second).base[j] = (it->second).base[j] * hash_base[j] + (it->first == ch);
        }
    }
}


void init_encode(HV & ha, map<char, Mapping> & char_mapping, HV & high_base) {
    char_mapping.clear();
    ha.clear();
    ha.resize(num_of_hash);
    high_base.clear();
    high_base.resize(num_of_hash);
}
void opti_encode(HV & ha, int pos, map<char, Mapping> & char_mapping, HV & high_base) {
    add_char(ha, pos, char_mapping);
    range(j, num_of_hash) {
        if (pos == 0) high_base[j] = 1; else high_base[j] *= hash_base[j];
    }
}

void update(HV &ha, map<char, Mapping> & char_mapping, HV & high_base, int del_pos, int add_pos, int len) {
    char del_char = s[del_pos];
    char new_char = s[add_pos];
    Mapping & char_info = char_mapping[del_char];

    //del first
    range(j, num_of_hash) {
        ha[j] -= high_base[j];
        char_info.base[j] -= high_base[j];
    }
    //eprintf("del_pos = %d, last pos change %d to %d\n", del_pos, char_info.last_pos, next_pos[del_pos]);
    char_info.last_pos = next_pos[del_pos];
    if (char_info.last_pos >= add_pos) {
        char_mapping.erase(del_char);
    }

    //change tag
    map<int, char> new_tag;
    for (map<char, Mapping>::iterator it = char_mapping.begin(); it != char_mapping.end(); it++) {
        new_tag[it->second.last_pos] = it->first;
    }
    int tag = 0;
    for (map<int, char>::iterator it = new_tag.begin(); it != new_tag.end(); it++) {
        int last_pos = it->first;
        char ch = it->second;
        Mapping & cur_char_info = char_mapping[ch];
        tag ++;
        int diff = tag - cur_char_info.val;
        if (diff) {
           // eprintf("char %c tag change %d to %d\n", ch, cur_char_info.val, tag);
            range(j, num_of_hash) {
                ha[j] += cur_char_info.base[j] * diff;
            }
        }
        cur_char_info.val = tag;
    }

    //add last
    add_char(ha, add_pos, char_mapping);
}

void dump(HV ha) {
    range(i, ha.size()) cout << " " << ha[i] ; cout << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("e.in", "r", stdin);
#endif
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   


    cin >> s;
    n = s.size();

    map<char, int> last_pos_map;
    range(i, n) next_pos[i] = n + 1000;
    range(i, n) {
        char ch = s[i];
        if (last_pos_map.find(ch) != last_pos_map.end()) {
            next_pos[last_pos_map[ch]] = i;
            //eprintf("next_pos pos of %d = %d\n", last_pos_map[ch], i);
        }
        last_pos_map[ch] = i;
    }

    map<char, Mapping> inc_char_mapping;
    HV inc_high_base;
    HV inc_ha;
    init_encode(inc_ha, inc_char_mapping, inc_high_base);

    for (int len = 1; len <= n; len++) {
        set<HV> M;

        map<char, Mapping> char_mapping;
        HV high_base;
        HV ha;
        for (int start = 0; start + len - 1 < n; start ++) {
            if (start == 0) {
                opti_encode(inc_ha, len - 1, inc_char_mapping, inc_high_base);
                char_mapping = inc_char_mapping;
                high_base = inc_high_base;
                ha = inc_ha;
            } else {
                update(ha, char_mapping, high_base, start - 1, start + len - 1, len);
            }
            if (M.find(ha) == M.end()) {
                M.insert(ha);
            }

            //eprintf("len = %d, start = %d, end = %d, set_size = %d, ha = ", len, start, start + len - 1, M.size());
            //dump(ha);
            ans[start + len - 1] += M.size();
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
