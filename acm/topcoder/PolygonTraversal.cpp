// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Manao had a sheet of paper. He drew N points on it, which corresponded to vertices of a regular N-gon. He numbered the vertices from 1 to N in clockwise order.

After that, Manao connected several pairs of points with straight line segments. Namely, he connected points points[i] and points[i+1] for each i between 0 and M-2, where M is the number of elements in points. Note that all numbers in points are distinct.

Manao took a look at what he had drawn and decided to continue his traversal by adding every remaining point of the polygon to it and then returning to point points[0]. In other words, Manao is going to connect point points[M-1] with some point tail[0] which is not in points, then connect tail[0] with some point tail[1] which is neither in points nor in tail, and so on. In the end, he will connect point tail[N-M-1] with point points[0], thus completing the traversal.

Manao is really fond of intersections, so he wants to continue the traversal in such a way that every new line segment he draws intersects with at least one of the previously drawn line segments. (Note that the set of previously drawn segments includes not only the original set of segments, but also the new segments drawn before the current one.) Count and return the number of ways in which he can complete the traversal.

DEFINITION
Class:PolygonTraversal
Method:count
Parameters:int, vector <int>
Returns:long long
Method signature:long long count(int N, vector <int> points)


CONSTRAINTS
-N will be between 4 and 18, inclusive.
-points will contain between 2 and N-1 elements, inclusive.
-Each element of points will be between 1 and N, inclusive.
-The elements of points will be distinct.


EXAMPLES

0)
5
{1, 3, 5}

Returns: 1

The only way for Manao to complete the traversal is:



1)
6
{1, 4, 2}

Returns: 1

The only way to complete the traversal is to visit vertices {6, 3, 5, 1}, in order.
Note that the segment 5-1 does not intersect the original two segments (1-4 and 4-2), but it does intersect segments 2-6 and 6-3 which were both added before 5-1.

2)
7
{2, 4, 7}

Returns: 2

The two possible tails are:

3-5-1-6-2
3-6-1-5-2


3)
7
{1, 2, 3, 4, 6, 5}

Returns: 0

Manao needs to connect points 5 and 7 and then connect points 7 and 1. Obviously, segment 1-7 will not intersect with any other segment.

4)
18
{1, 7, 18}

Returns: 4374612736



*/
// END CUT HERE
#line 79 "PolygonTraversal.cpp"
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
#define two(i) (1<<(i))

typedef long long ll;

const int MAX = 1 << 18;

ll dp[MAX][18];
int N, sta;

bool ok(int mask, int from, int to) {
    int i;
    for (i = 1; i < N; i++) {
        int ne = (from + i) % N;
        if (ne == to) {
            return false;
        }
        if (mask & two(ne)) {
            break;
        }
    }
    for (i = 1; i < N; i++) {
        int ne = (from - i + N) % N;
        if (ne == to) {
            return false;
        }
        if (mask & two(ne)) {
            break;
        }
    }
    return true;
}

ll solve(int mask, int at) {
    if (mask == two(N) - 1) {
        if (ok(mask, at, sta)) {
            return 1;
        } else {
            return 0;
        }
    }

    if (dp[mask][at] != -1) {
        return dp[mask][at];
    }

    ll ret = 0;

    int i;
    for (i = 0; i < N; i++) {
        if (two(i) & mask) {
            continue;
        }

        if (ok(mask, at, i)) {
            ret += solve(mask | two(i), i);
        }
    }
    return dp[mask][at] = ret;
}

class PolygonTraversal
{
public:
 long long count(int _N, vector <int> points)
 {
 //$CARETPOSITION$
    N = _N;
    int i;
    int state = 0;
    int last = 0;
    sta = points[0] - 1;
    for (i = 0; i < points.size(); i++) {
        state |= two(points[i] - 1);
        last = points[i] - 1;
    }
    memset(dp, -1, sizeof(dp));
    solve(state, last);
    ll ret = dp[state][last];
    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arr1[] = {1, 3, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(0, Arg2, count(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 6; int Arr1[] = {1, 4, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 1LL; verify_case(1, Arg2, count(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 7; int Arr1[] = {2, 4, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 2LL; verify_case(2, Arg2, count(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 7; int Arr1[] = {1, 2, 3, 4, 6, 5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 0LL; verify_case(3, Arg2, count(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 18; int Arr1[] = {1, 7, 18}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); long long Arg2 = 4374612736LL; verify_case(4, Arg2, count(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PolygonTraversal ___test;
 ___test.run_test(-1);
}
// END CUT HERE
