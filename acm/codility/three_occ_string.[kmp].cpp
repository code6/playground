/* --- Author: Vladimir Smykalov, enot.1.10@gmail.com --- */
/**
 * 这题求头尾加一个中间的相同子串的最大长度，这个用KMP加一点枚举即可做到，不过得对KMP以及board的性质有一点了解
 * 按末尾来说可用 board 的序列是 {board[N], board^2[N], board^3[N]}
 * 所以我们很容易知道末尾能够接受的board长度列表，然后对中间每一个位置，判断其是否可以达到末尾可达的状态，并用其约束(non overlap)来做限制，最后倒叙扫描一遍合法状态即可。
 * http://codility.com/cert/view/certJME4C9-XD63M5FQKGTRFD7C
 */
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


const int MAX = 1000000 + 50;
int fail[MAX];
int board[MAX];
int limit[MAX];


int solution_bf(string &S) {
    int i, j;
    int n = S.size();
    fail[0] = -1;
    for (i = 1; i <= n; i++) {
        j = fail[i - 1];
        while (j >= 0 && S[i - 1] != S[j]) {
            j = fail[j];
        }
        fail[i] = j + 1;
    }
    for (i = 0; i <= n; i++) {
        board[i] = -1;
    }
    int at = n;
    while (at > 0) {
        board[at] = at;
        at = fail[at];
    }

    int ret = 0;
    for (i = 1; i <= n; i++) {
        int lim = min(i / 2, n - i);
        int at = i;
        while (at > ret) {
            if (board[at] != -1 && at <= lim) ret =max(ret, at);
            at = fail[at];
        }
    }
    return ret;
}

int solution(string &S) {
    int i, j;
    int n = S.size();
    fail[0] = -1;
    for (i = 1; i <= n; i++) {
        j = fail[i - 1];
        while (j >= 0 && S[i - 1] != S[j]) {
            j = fail[j];
        }
        fail[i] = j + 1;
    }
    for (i = 0; i <= n; i++) {
        board[i] = -1;
        limit[i] = 0;
    }
    int at = n;
    while (at > 0) {
        board[at] = at;
        at = fail[at];
    }

    for (i = 1; i <= n; i++) {
        int lim = min(i / 2, n - i);
        if (board[i] == -1) {
            board[i] = board[fail[i]];
        }
        if (board[i] != -1) {
            limit[board[i]] = max(limit[board[i]], lim);
        }
    }
    int ret = 0;
    at = n;
    int limit_current = 0;
    while (at > 0) {
        limit_current = max(limit_current, limit[at]);
        //cout << "at = " << at << " limit = " << limit_current << endl;
        if (at <= limit_current) {
            ret = at;
            break;
        }
        at = fail[at];
    }
    return ret;
 }


int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
#endif
    int n;
    string s;
    while( cin >> s)
    {
        cin >> s;
        int ret = solution(s);
        int bf = solution_bf(s);
        if (ret != bf) {
            cout << s << ' ' << ret << " vs " << bf << endl;
        }
    }
    return 0;
}
