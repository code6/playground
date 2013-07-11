// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// John chooses positive integer X that is at most A and Brus chooses positive integer Y that is at most B.
Then they calculate X to the power of Y, i.e., X^Y.
Return the number of different results they can get.

DEFINITION
Class:ThePowers
Method:find
Parameters:int, int
Returns:long long
Method signature:long long find(int A, int B)


CONSTRAINTS
-A will be between 1 and 1,000,000,000, inclusive.
-B will be between 1 and 1,000,000,000, inclusive.


EXAMPLES

0)
7
4

Returns: 23

There are 23 possible results:

1 = 1^1 = 1^2 = 1^3 = 1^4, 2 = 2^1, 3 = 3^1, 4 = 2^2 = 4^1,

5 = 5^1, 6 = 6^1, 7 = 7^1, 8 = 2^3, 9 = 3^2, 16 = 2^4 = 4^2,

25 = 5^2, 27 = 3^3, 36 = 6^2, 49 = 7^2, 64 = 4^3, 81 = 3^4, 125 = 5^3,

216 = 6^3, 256 = 4^4, 343 = 7^3, 625 = 5^4, 1296 = 6^4 and 2401 = 7^4.


1)
1
1

Returns: 1



2)
1000000000
1000000000

Returns: 999983644283653287



3)
999999999
5

Returns: 4999934406



*/
// END CUT HERE
#line 67 "ThePowers.cpp"
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

typedef long long ll;

class ThePowers
{
public:
 long long find(int A, int B)
 {
 //$CARETPOSITION$
    ll ret = (ll)A * B;
    //x = 1
    ret -= B - 1;
    // x > 1
    // x = u^v (v > 1)
    for (ll u = 2; u * u <= A; u++) {
        G
    }
    
    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 7; int Arg1 = 4; long long Arg2 = 23LL; verify_case(0, Arg2, find(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 1; int Arg1 = 1; long long Arg2 = 1LL; verify_case(1, Arg2, find(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 1000000000; int Arg1 = 1000000000; long long Arg2 = 999983644283653287LL; verify_case(2, Arg2, find(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 999999999; int Arg1 = 5; long long Arg2 = 4999934406LL; verify_case(3, Arg2, find(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 ThePowers ___test;
 ___test.run_test(-1);
}
// END CUT HERE
