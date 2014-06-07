// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// One of the modes in the game "osu!" is called "catch the beat".
In this mode, you control a character that catches falling fruit.



The game is played in the vertical plane.
For simplicity, we will assume that both your character and all pieces of fruit are points in that plane.



You start the game at the coordinates (0, 0).
Your character can only move along the x-axis.
The maximum speed of your character is 1 unit of distance per second.
For example, you need at least 3 seconds to move from (-2, 0) to (1, 0).



There are n pieces of fruit.
The pieces are numbered 0 through n-1.
For each i, fruit i starts at (x[i], y[i]).
All pieces of fruit fall down with constant speed of 1 unit of distance per second.
That is, a fruit currently located at (xf, yf) will move to (xf, yf-t) in t seconds.
You will catch a fruit if the character is located at the same point as the fruit at some moment in time.



The initial coordinates x[] and y[] are generated using the following pseudocode:



x[0] = x0
for i = 1 to n-1:
    x[i] = (x[i-1] * a + b) % mod1

for i = 0 to n-1:
    x[i] = x[i] - offset

y[0] = y0
for i = 1 to n-1:
    y[i] = (y[i-1] * c + d) % mod2

(In the pseudocode, '%' represents the 'modulo' operator.)


You are given all the ints used in the above pseudocode.
Return the maximum number of pieces of fruit you can catch.

DEFINITION
Class:CatchTheBeat
Method:maxCatched
Parameters:int, int, int, int, int, int, int, int, int, int
Returns:int
Method signature:int maxCatched(int n, int x0, int y0, int a, int b, int c, int d, int mod1, int mod2, int offset)


CONSTRAINTS
-n will be between 1 and 500,000, inclusive.
-mod1 and mod2 will be between 1 and 1,000,000,000, inclusive.
-x0, a and b will be between 0 and (mod1 - 1), inclusive.
-y0, c and d will be between 0 and (mod2 - 1), inclusive.
-offset will be between 0 and 1,000,000,000, inclusive.


EXAMPLES

0)
3
0
0
1
1
1
1
100
100
1

Returns: 2

There are 3 pieces of fruit.
Their initial coordinates are (-1, 0), (0, 1), and (1, 2).
Clearly you cannot catch fruit 0.
You can catch the other two.
One way of doing so:

Wait at (0, 0) for 1 second.
Catch fruit 1.
Move to (1, 0) in 1 second.
Immediately catch fruit 2.


1)
1
0
1234
0
0
0
0
1000000000
1000000000
1000

Returns: 1

The only fruit is located at (-1000, 1234). We can go to (-1000, 0) and then wait for 234 seconds to catch it.

2)
1
0
999
0
0
0
0
1000000000
1000000000
1000

Returns: 0

Now the only fruit is located at (-1000, 999). We can't catch it.

3)
100
0
0
1
1
1
1
3
58585858
1

Returns: 66



4)
500000
123456
0
1
0
1
1
1000000000
1000000000
0

Returns: 376544

The fruits are located in (123456, 0), (123456, 1), ..., (123456, 499999).

5)
500000
0
0
0
0
0
0
1
1
0

Returns: 500000

In this case all the fruits start at (0, 0).
Note that there can be more than one fruit at any position.
We can catch all such fruit at the same time.

6)
10
999999957
79
993948167
24597383
212151897
999940854
999999986
999940855
3404

Returns: 3

Watch out for integer overflow when generating the coordinates.

*/
// END CUT HERE
#line 196 "CatchTheBeat.cpp"
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

class CatchTheBeat
{
public:
 int maxCatched(int n, int x0, int y0, int a, int b, int c, int d, int mod1, int mod2, int offset)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 0; int Arg2 = 0; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; int Arg6 = 1; int Arg7 = 100; int Arg8 = 100; int Arg9 = 1; int Arg10 = 2; verify_case(0, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 1234; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1000000000; int Arg8 = 1000000000; int Arg9 = 1000; int Arg10 = 1; verify_case(1, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }
	void test_case_2() { int Arg0 = 1; int Arg1 = 0; int Arg2 = 999; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1000000000; int Arg8 = 1000000000; int Arg9 = 1000; int Arg10 = 0; verify_case(2, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }
	void test_case_3() { int Arg0 = 100; int Arg1 = 0; int Arg2 = 0; int Arg3 = 1; int Arg4 = 1; int Arg5 = 1; int Arg6 = 1; int Arg7 = 3; int Arg8 = 58585858; int Arg9 = 1; int Arg10 = 66; verify_case(3, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }
	void test_case_4() { int Arg0 = 500000; int Arg1 = 123456; int Arg2 = 0; int Arg3 = 1; int Arg4 = 0; int Arg5 = 1; int Arg6 = 1; int Arg7 = 1000000000; int Arg8 = 1000000000; int Arg9 = 0; int Arg10 = 376544; verify_case(4, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }
	void test_case_5() { int Arg0 = 500000; int Arg1 = 0; int Arg2 = 0; int Arg3 = 0; int Arg4 = 0; int Arg5 = 0; int Arg6 = 0; int Arg7 = 1; int Arg8 = 1; int Arg9 = 0; int Arg10 = 500000; verify_case(5, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }
	void test_case_6() { int Arg0 = 10; int Arg1 = 999999957; int Arg2 = 79; int Arg3 = 993948167; int Arg4 = 24597383; int Arg5 = 212151897; int Arg6 = 999940854; int Arg7 = 999999986; int Arg8 = 999940855; int Arg9 = 3404; int Arg10 = 3; verify_case(6, Arg10, maxCatched(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8, Arg9)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 CatchTheBeat ___test;
 ___test.run_test(-1);
}
// END CUT HERE
