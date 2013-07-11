// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A palindrome is a string that is spelled the same forward and backward. We want to rearrange letters of the given string baseString so that it becomes a palindrome.
You will be given a string baseString. Return the palindrome that can be made from baseString. When more than one palindrome can be made, return the lexicographically earliest (i.e., the one that occurs first in alphabetical order). Return "" (the empty string) if no palindromes can be made from baseString.


DEFINITION
Class:PalindromeMaker2
Method:make
Parameters:string
Returns:string
Method signature:string make(string baseString)


CONSTRAINTS
-baseString will contain between 1 and 50 characters, inclusive. 
-Each character in baseString will be an uppercase letter ('A'-'Z').


EXAMPLES

0)
"AABB"

Returns: "ABBA"



1)
"AAABB"

Returns: "ABABA"



2)
"ABACABA"

Returns: "AABCBAA"



3)
"ABCD"

Returns: ""



*/
// END CUT HERE
#line 54 "PalindromeMaker2.cpp"
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

class PalindromeMaker2
{
public:
 string make(string baseString)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "AABB"; string Arg1 = "ABBA"; verify_case(0, Arg1, make(Arg0)); }
	void test_case_1() { string Arg0 = "AAABB"; string Arg1 = "ABABA"; verify_case(1, Arg1, make(Arg0)); }
	void test_case_2() { string Arg0 = "ABACABA"; string Arg1 = "AABCBAA"; verify_case(2, Arg1, make(Arg0)); }
	void test_case_3() { string Arg0 = "ABCD"; string Arg1 = ""; verify_case(3, Arg1, make(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PalindromeMaker2 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
