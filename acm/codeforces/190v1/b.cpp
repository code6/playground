#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <vector>
#define range(i, n) for (int i=0; i<(n); ++i)

using namespace std;

int n, m;

int main() {
//    freopen("b.in", "r", stdin);
    cin >> n >> m;
    int i, j;
    vector<int> atk, def, me;
    range(i, n) {
        string type;
        int val;
        cin >> type >> val;
        if (type == "ATK")  {
            atk.push_back(val);
        } else {
            def.push_back(val);
        }
    }
    range(i, m) {
        int val;
        cin >> val;
        me.push_back(val);
    }

    sort(atk.begin(), atk.end());
    sort(def.begin(), def.end());
    sort(me.begin(), me.end());

    int ret = 0;
    int maxlen = 0;

    //ATK
    for (i = 1; i <= atk.size(); i++) {
        if (i > me.size()) {
            break;
        }
        bool legal = true;
        int tmpval = 0;
        range(j, i) {
            int me_at = me.size() - i + j;
            if (me[me_at] < atk[j]) {
                legal = false;
                break;
            }
            tmpval += me[me_at] - atk[j];
        }
        if (legal) {
            ret = max(ret, tmpval);
            maxlen = i;
        }
    }

    if (maxlen == atk.size() && me.size() >= atk.size() + def.size()) {
        //ATK + DEF
        bool legal = true;
        range(i, def.size()) {
            int val = def[i];
            int at = upper_bound(me.begin(), me.end(), val) - me.begin();
            if (at == me.size()) {
                legal = false;
                 break;
            }
            me.erase(me.begin() + at);
        }

        if (legal) {
            range(i, atk.size()) {
                int me_at = me.size() - 1 - i;
                if (me[me_at] < atk[atk.size() - 1 - i]) {
                    legal = false;
                    break;
                }
            }
            if (legal) {
                int tmpval = 0;
                range(i, me.size()) tmpval += me[i];
                range(i, atk.size()) tmpval -= atk[i];
                ret = max(ret, tmpval);
            }
        }
    }

    cout << ret << endl;

    return 0;
}
