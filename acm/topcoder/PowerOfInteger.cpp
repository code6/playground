// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
A number y is said to be the k-th power of a number x if y = x^k, i.e., y is the product of k copies of x.


You are given two strings left and right. Return the greatest k such that there is an integer y (left <= y <= right) such that y is the k-th power of some integer x.


DEFINITION
Class:PowerOfInteger
Method:greatestPower
Parameters:string, string
Returns:int
Method signature:int greatestPower(string left, string right)


CONSTRAINTS
-left will be an integer between 2 and 10^12, inclusive, without extra leading zeroes.
-right will be an integer between left and 10^12, inclusive, without extra leading zeroes.


EXAMPLES

0)
"5"
"20"

Returns: 4

The greatest power between 5 and 20 is 16=2^4.

1)
"10"
"12"

Returns: 1

No nontrivial power of integer between 10 and 12, so return 1.

2)
"2"
"100"

Returns: 6



3)
"1000000000000"
"1000000000000"

Returns: 12



*/
// END CUT HERE
#line 61 "PowerOfInteger.cpp"
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

class PowerOfInteger
{
public:
 int greatestPower(string left, string right)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "5"; string Arg1 = "20"; int Arg2 = 4; verify_case(0, Arg2, greatestPower(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "10"; string Arg1 = "12"; int Arg2 = 1; verify_case(1, Arg2, greatestPower(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "2"; string Arg1 = "100"; int Arg2 = 6; verify_case(2, Arg2, greatestPower(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "1000000000000"; string Arg1 = "1000000000000"; int Arg2 = 12; verify_case(3, Arg2, greatestPower(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PowerOfInteger ___test;
 ___test.run_test(-1);
}
// END CUT HERE
