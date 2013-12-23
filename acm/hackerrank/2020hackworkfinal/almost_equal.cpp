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
#define all(a) (a).begin(),(a).end()

typedef long long ll;
typedef vector<int> VI;
typedef vector<ll> VL;
typedef pair<int, int> PII;

int lowbit(int n) {
    return n & -n;
}

//Index Tree
struct IndexTree {
    int n;
    vector<int> arr;
    IndexTree() {
    }
    void init(int sz) {
        n = sz;
        arr.clear();
        arr.resize(n + 10);
    }
    int sum(int i) {
        int ret = 0;
        while (i) {
            ret += arr[i];
            i -= lowbit(i);
        }
        return ret;
    }
    int sum(int f, int r) {
        if (f > r) return 0;
        return sum(r) - (f > 0 ? sum(f-1):0);
    }
    void add(int i, int x) {
        while (i <= n) {
            arr[i] += x;
            i += lowbit(i);
        }
    }
};

struct Val {
    int f, r, v;
    Val(int _f, int _r, int _v):f(_f), r(_r), v(_v){}
};

struct SegCover {
    IndexTree le, ri;
    int sz;
    int n;

    void init(int _sz) {
        sz = _sz;
        n = 0;
        le.init(sz);
        ri.init(sz);
    }

    void add(Val s) {
        le.add(s.f, 1);
        ri.add(s.r, 1);
        n++;
    }
    void del(Val s) {
        le.add(s.f, -1);
        ri.add(s.r, -1);
        n--;
    }
    int query(Val s) {
        int ret =  n - ri.sum(0, s.v - 1)  - le.sum(s.v + 1, sz);
        return ret;
    }
};

struct Q {
    int id;
    int f, r;
    ll ans;
    Q(int _id, int _f, int _r) {
        id = _id;
        f = _f, r = _r;
        ans = 0;
    }
    bool operator<(const Q & rhs)const {
        if (r != rhs.r) 
            return r < rhs.r;
        return f < rhs.f;
    }
};

struct Node {
    vector<Val> seg_arr;
    SegCover sc;
    ll pair_cnt;
    int f,r;
    Node(vector<Val>  _seg_arr) {
        seg_arr = _seg_arr;
    }
    void init(int at) {
        sc.init(seg_arr.size() * 2 + 10);
        sc.add(seg_arr[at]);
        pair_cnt = 0;
        f = r = at;
    }
    void beg_add(int inc) {
        //eprintf("at beg_add, inc = %d\n", inc);
        if (inc > 0) {
            f --;
            pair_cnt += sc.query(seg_arr[f]);
            sc.add(seg_arr[f]);
        } else {
            if (f == r) {
                end_add(1);
                beg_add(-1);
            } else {
                sc.del(seg_arr[f]);
                pair_cnt -= sc.query(seg_arr[f]);
                f++;
            }
        }
    }
    void end_add(int inc) {
        //eprintf("at end_add, inc = %d\n", inc);
        if (inc > 0) {
            r++;
            pair_cnt += sc.query(seg_arr[r]);
            sc.add(seg_arr[r]);
        } else {
            if (f == r) {
                beg_add(1);
                end_add(-1);
            } else {
                sc.del(seg_arr[r]);
                pair_cnt -= sc.query(seg_arr[r]);
                r--;
            }
        }
    }
};


int n, k;
vector<Val> h_arr;
int q;

vector<Q> q_arr;

vector<Q> arrange(vector<Q> arr) {
   random_shuffle(all(arr)); 
   return arr;
}

vector<Val> trans(vector<Val> arr) {
    vector<int> num;
    range(i, arr.size()) {
        num.pb(arr[i].f);
        num.pb(arr[i].r);
        num.pb(arr[i].v);
    }
    sort(all(num));
    num.erase(unique(all(num)), num.end());
    range(i, arr.size()) {
        arr[i].f = find(all(num), arr[i].f) - num.begin() + 1;
        arr[i].r = find(all(num), arr[i].r) - num.begin() + 1;
        arr[i].v = find(all(num), arr[i].v) - num.begin() + 1;
    }
    return arr;
}

vector<ll> offline_calucate(vector<Val> seg_arr, vector<Q> q_arr) {
    Node cn(seg_arr);
    bool isnew = true;
    range(i, q_arr.size()) {
        int tf, tr;
        tf = q_arr[i].f;
        tr = q_arr[i].r;
        if (isnew) {
            cn.init(tf);
            isnew = false;
        } 
        while (cn.r != tr) {
            cn.end_add(cn.r < tr ? 1: -1);
        }
        while (cn.f != tf) {
            cn.beg_add(cn.f < tf ? -1 : 1);
        }
        q_arr[i].ans = cn.pair_cnt;
    }

    vector<ll> ret;
    ret.resize(q_arr.size());
    range(i, q_arr.size()) {
        ret[q_arr[i].id] = q_arr[i].ans;
    }
    return ret;
}

int main() {
    int i, j;
    freopen("almost_equal.in", "r", stdin);
    scanf("%d %d", &n, &k);
    range(i, n) {
        int v;
        scanf("%d", &v);
        h_arr.pb(Val(v-k, v+k, v));
    }

    h_arr = trans(h_arr);
    scanf("%d", &q);
    range(i, q) {
        int l, r;
        scanf("%d %d", &l, &r);
        q_arr.pb(Q(i, l, r));
    }

    vector<ll> ans = offline_calucate(h_arr, arrange(q_arr));
    range(i, ans.size()) {
        cout << ans[i] << endl;
    }
    return 0;
}

