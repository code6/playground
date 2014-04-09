// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Andrew has a combination lock.
The lock consists of multiple dials that are placed next to each other.
Each dial contains the digits 0 through 9, in order.
At any moment, exactly one of the digits on each dial is visible.
The string formed by the currently visible digits is called the current combination.

The visible digit on a dial can be changed by rotating the dial up or down.
Rotating the dial up changes 0 to 1, 1 to 2, and so on.
Note that the digits on a dial wrap around: if we rotate up a dial that shows a 9, it will show a 0 again.
Naturally, rotating the dial down changes the digit in the other direction.

We are able to rotate multiple dials at the same time, as long as they are next to each other.
More precisely, in a single turn we can take an arbitrarily long segment of consecutive dials, and rotate all of them one step in the same direction (i.e., either all of them up, or all of them down).

For example, suppose that the current combination is "123".
In one step, we can change it to many different combinations, including "012" (all three dials down), "234" (all three dials up), "133" (middle dial up), and "013" (first two dials down).
Note that we cannot change "123" to "224" in a single step.

You are given two vector <string>s: P and Q.
Concatenate the elements of P to get S.
S is the current combination.
Concatenate the elements of Q to get T.
T is the secret combination that unlocks the lock.
That is, to open the lock we need to change S into T by rotating some of the dials.
Return the smallest number of steps needed.

DEFINITION
Class:CombinationLockDiv1
Method:minimumMoves
Parameters:vector <string>, vector <string>
Returns:int
Method signature:int minimumMoves(vector <string> P, vector <string> Q)


CONSTRAINTS
-P and Q will each contain no more than 50 elements.
-Each element of P and Q will contain no more than 50 characters.
-S will contain at least 1 character.
-S will contain the same number of characters as T.
-Each character in S and T will be a digit ('0'-'9').


EXAMPLES

0)
{"123"}
{"112"}

Returns: 1

Rotate the last two dials down.

1)
{"1"}
{"7"}

Returns: 4

Rotate the dial down 4 times: from 1 to 0, from 0 to 9, from 9 to 8, and from 8 to 7.

2)
{"6","07"}
{"","60","7"}

Returns: 0



3)
{"1234"}
{"4567"}

Returns: 3



4)
{"020"}
{"909"}

Returns: 2



5)
{"4423232218340"}
{"6290421476245"}

Returns: 18



*/
// END CUT HERE
#line 99 "CombinationLockDiv1.cpp"
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

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define range(i, n) for (int i=0; i<(n); ++i)
#define all(a) (a).begin(),a.end()
#define two(i) (1<<(i))

typedef vector<int> VI;
typedef pair<int, int> PII;

const int MAX = 5000 + 5;

int n;
vector<int> up, down;
int dp[MAX];

int solve(int n) {
    if (n < 0) return 0;
    if (dp[n] != -1) return dp[n];
    int & ret = dp[n];
    ret = -1;
    //prev .. n
    int up_cost, up_left;
    int down_cost, down_left;
    up_cost = up_left = down_cost = down_left = 0;
    for (int prev = n; prev >= 0; prev --) {
        int extra_cost = max(0, up[prev] - up_left);
        up_cost += extra_cost;
        up_left = up[prev];
        extra_cost = max(0, down[prev] - down_left);
        down_cost += extra_cost;
        down_left = down[prev];

        int tmp = min(up_cost, down_cost) + solve(prev - 1);
        if (ret == -1 || ret > tmp) {
            printf("n = %d, prev=  %d, up_cost = %d, down_cost = %d, ret = %d, tmp = %d\n", n , prev, up_cost, down_cost, ret, tmp);
            ret = tmp;
        }
    }
    return ret;
}

class CombinationLockDiv1
{
public:
 int minimumMoves(vector <string> P, vector <string> Q)
 {
    string beg, end;
 //$CARETPOSITION$
    beg = "";
    range(i, P.size()) beg += P[i];
    end = "";
    range(i, Q.size()) end += Q[i];
    n = beg.size();
    up.clear();
    down.clear();
    range(i, beg.size()) {
        int x = beg[i] - '0';
        int y = end[i] - '0';
        if (x <= y) {
            up.pb(y - x);
            down.pb(x + 10 - y);
        } else {
            up.pb(10 + y - x);
            down.pb(x - y);
        }
    }
    range(i, n) printf("%2d ", i); putchar('\n');
    range(i, n) printf("%2d ", up[i]); putchar('\n');
    range(i, n) printf("%2d ", down[i]); putchar('\n');
    memset(dp, -1, sizeof(dp));
    int ans = solve(n - 1);
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"123"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"112"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"1"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"7"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 4; verify_case(1, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"6","07"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"","60","7"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"1234"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"4567"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"020"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"909"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(4, Arg2, minimumMoves(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"4423232218340"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"6290421476245"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 18; verify_case(5, Arg2, minimumMoves(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 CombinationLockDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
