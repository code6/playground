// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Cucumberman planted N cucumbers along a straight road. Cucumbers are numbered 0 through N-1, and the position of the i-th cucumber is x[i]. The cucumbers are at pairwise distinct coordinates, but their coordinates are not necessarily in sorted order. He waters all cucumbers every day. He can't change the order of watering cucumbers, so he must water cucumber 0 first, water cucumber 1 next, and so on. (Note that this means he may be going back and forth along the road.)


Watering a cucumber takes zero time. When walking, Cucumberman needs one unit of time to travel one unit of distance. Additionally, he can build at most K teleports at any positions (including non-integer ones). If there are teleports at both P and Q, he can move from P to Q instantly using teleports.


He wants to minimize the duration between watering cucumber 0 and watering cucumber N-1. Return this minimum time, assuming that he builds and uses the K teleports optimally.


DEFINITION
Class:CucumberWatering
Method:theMin
Parameters:vector <int>, int
Returns:long long
Method signature:long long theMin(vector <int> x, int K)


CONSTRAINTS
-x will contain between 2 and 50 elements, inclusive.
-Each element of x will be between -1,000,000,000 (-10^9) and 1,000,000,000 (10^9), inclusive.
-Elements of x will be pairwise distinct.
-K will be between 1 and 50, inclusive.


EXAMPLES

0)
{0, 6, 8, 2}
2

Returns: 6

One optimal way is as follows:

Build teleports at 1 and 7.
Water cucumber 0 at 0. Walk to 1, teleport to 7, walk to 6 and water cucumber 1. Walk to 8 and water cucumber 2. Walk to 7, teleport back to 1, walk to 2 and water cucumber 3.

It takes |0-1| + |7-6| + |6-8| + |8-7| + |1-2| = 6 unit time in total.


1)
{-1000000000, 1000000000, 0}
1

Returns: 3000000000

Only one teleport is useless.

2)
{58, 2012}
50

Returns: 0



3)
{9, -3, 14, 6, 5, -9, 32, 7, -5, 26, 2, 11}
3

Returns: 58



*/
// END CUT HERE
#line 71 "CucumberWatering.cpp"
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <algorithm>
using namespace std;

#define mp make_pair

typedef pair<int, int> PII;
typedef long long ll;

ll dp[55][55];

bool is_in(int u, int v, int p) {
    return u <= p && p <= v;
}

void update(ll & v, ll tmp) {
    if (v == -1) {
        v = tmp;
    }
    v = min(v, tmp);
}

class CucumberWatering
{
    public:
        long long theMin(vector <int> x, int m)
        {
            //$CARETPOSITION$
            vector<PII> vp;
            int n = x.size();
            ll base = 0;
            for (int i = 0; i < n; i++) {
                vp.push_back(mp(x[i], i));
                if (i) {
                    base += abs((ll)x[i] - x[i - 1]);
                }
            }
            sort(vp.begin(), vp.end());

            //calc edge
            vector<PII> edge;
            for (int i = 0; i < n; i++) {
                int u = i;
                int v = -1;
                for (int j = 0; j < n; j++) {
                    if (vp[j].second == vp[u].second + 1) {
                        v = j;
                        break;
                    }
                }
                if (u > v) {
                    swap(u, v);
                }
                if (u > -1) {
                    edge.push_back(mp(u,v));
                }
            }

            memset(dp, -1, sizeof(dp));
            for (int i = 0; i < n; i++) {
                dp[1][i] = base;
            }

            for (int i = 2; i <= m; i++) {
                for (int j = 0; j < n; j++) {
                    if (dp[i - 1][j] != -1) {
                        for (int k = j + 1; k < n; k++) {
                            ll tmp = dp[i - 1][j];
                            for (int u = 0; u < edge.size(); u++) {
                                if (edge[u].first >= k || edge[u].second <= j) {
                                    continue;
                                }
                                int f, r;
                                f = edge[u].first;
                                r = edge[u].second;
                                if (is_in(f, r, j) && is_in(f, r, k)) {
                                    tmp -= vp[k].first - vp[j].first;
                                } else {
                                    if (is_in(f, r, j)) {
                                        tmp -= max(0LL, 2LL * vp[r].first - ((ll)vp[k].first + vp[j].first));
                                    } else {
                                        if (is_in(f, r, k)) {
                                            tmp -= max(0LL, ((ll)vp[k].first + vp[j].first) - 2LL * vp[f].first);
                                        } else {
                                            tmp -= max(0LL, 2LL * ((ll)vp[r].first - vp[f].first) - ((ll)vp[k].first - vp[j].first));
                                        }
                                    }
                                }
                            }
                            update(dp[i][k], tmp);
                        }
                    }
                }
            }

            ll ans = -1;
            for (int i = 0; i < n; i++) {
                if (dp[min(n, m)][i] != -1) {
                    if (ans == -1 || ans > dp[min(n, m)][i]) {
                        //printf("ans = %lld, v = %lld, i = %d\n", ans, dp[min(n, m)][i], i);
                        ans = dp[min(n, m)][i];
                    }
                }
            }

            return ans;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arr0[] = {0, 6, 8, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 6LL; verify_case(0, Arg2, theMin(Arg0, Arg1)); }
        void test_case_1() { int Arr0[] = {-1000000000, 1000000000, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; long long Arg2 = 3000000000LL; verify_case(1, Arg2, theMin(Arg0, Arg1)); }
        void test_case_2() { int Arr0[] = {58, 2012}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 50; long long Arg2 = 0LL; verify_case(2, Arg2, theMin(Arg0, Arg1)); }
        void test_case_3() { int Arr0[] = {9, -3, 14, 6, 5, -9, 32, 7, -5, 26, 2, 11}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 58LL; verify_case(3, Arg2, theMin(Arg0, Arg1)); }

        // END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
    CucumberWatering ___test;
    ___test.run_test(-1);
}
// END CUT HERE
