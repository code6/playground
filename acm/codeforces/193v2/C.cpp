#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
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
typedef pair<ll, ll> PLL;


/*
vector<PII> vp;
vp.pb(mp(5, 2));
vp.pb(mp(3, 4));
vp.pb(mp(6, 1));
range(i, vp.size()) {
    eprintf("(%d, %d)\n", vp[i].fs, vp[i].sc);
}
forit(it, vp) {
    eprintf("(%d, %d)\n", it->fs, it->sc);
}
cout << "sz = " << sz(vp) << endl;
sort(all(vp));
forit(it, vp) {
    eprintf("(%d, %d)\n", it->fs, it->sc);
}
*/

struct Node
{
    int b;
    int a;
    int pos;
    Node(){}
    Node(int a, int b, int pos):a(a),b(b),pos(pos){}
    bool operator < (const Node& rhs) const {
        if (b != rhs.b) return b < rhs.b;
        else return a > rhs.a;
    }
    bool operator () (const Node&lhs, const Node&rhs)const {
        return lhs.a > rhs.a;
    }
    void output() {
        cout << b << " " << a << " " << pos << endl;
    }
};

vector<Node> vn;

const int MAX = 100000 + 50;
int n, p, k;
PII arr[MAX];

int main() {
#ifndef ONLINE_JUDGE
    freopen("c.in", "r", stdin);
#endif
    cin >> n >> p >> k;
    int a_cnt = k;
    int b_cnt = p - k;
    range(i, n) {
        int a, b;
        scanf("%d %d", &a, &b);
        vn.pb(Node(a, b, i));
    }
    sort(vn.begin(), vn.end());

    //cout << " acnt = " << a_cnt << " bcnt = " << b_cnt << endl;
   // range(i, n) {
   //     vn[i].output();
   // }

    PLL res;
    int best_pos;
    priority_queue<Node, vector<Node>, Node> pq;

    ll aval = 0, bval = 0;
    range(i, a_cnt) {
        int pos = n - 1 - i;
        pq.push(vn[pos]);
        aval += vn[pos].a;
    }
    range(i, b_cnt) {
        int pos = n - 1 - a_cnt - i;
        bval += vn[pos].b;
    }
    res = mp(aval, bval);
    best_pos = n - a_cnt;

    //cout << "tmp_pos = " << best_pos << " aval = " << aval << " bval = " << bval << endl;
    range(i, n - a_cnt) {
        int pos = n - a_cnt - 1 - i;
        if (pos < b_cnt) break;
        bval += vn[pos - b_cnt].b - vn[pos].b;
        aval += vn[pos].a;
        pq.push(vn[pos]);
        Node out = pq.top();
        pq.pop();
        aval -= out.a;
        PLL tmp = mp(aval, bval);
        if (res < tmp) {
            res = tmp;
            best_pos = pos;
        }
        //cout << "tmp_pos = " << pos << " aval = " << aval << " bval = " << bval << endl;
    }
    //cout << res.fs << ' ' << res.sc << endl;
    vector<int> res_pos;

    while (!pq.empty()) pq.pop();
    range(i, n  - best_pos) {
        int pos = n - 1 - i;
        pq.push(vn[pos]);
        if (pq.size() > a_cnt) pq.pop();
    }
    while (!pq.empty()) res_pos.pb(pq.top().pos), pq.pop();
    range(i, b_cnt) {
        res_pos.pb(vn[best_pos - 1 - i].pos);
    }

    bool first = true;
    range(i, res_pos.size()) {
        if (!first) putchar(' '); else first = false;
        printf("%d", res_pos[i] + 1);
    }
    putchar('\n');

    return 0;
}
