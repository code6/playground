// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Suffix number i of a string S is the suffix that starts with the character S[i].
For example, for S="abcde" suffix 0 is "abcde" and suffix 3 is "de". 


The suffix array of a string S is defined as the permutation of suffix numbers that corresponds to their lexicographic order.
For example, suppose that S="abca".
If we order all suffixes of S lexicographically, we get the following: "a" < "abca" < "bca" < "ca".
The corresponding suffix numbers are 3, 0, 1, and 2, in this order.
Thus, for this string S the suffix array would be {3, 0, 1, 2}.
Note that the length of a suffix array is the same as the length of the original string.


You are given a vector <int> SA: the suffix array of an unknown string.
Return the smallest possible number of different characters in that string.

DEFINITION
Class:SuffixArrayDiv1
Method:minimalCharacters
Parameters:vector <int>
Returns:int
Method signature:int minimalCharacters(vector <int> SA)


NOTES
-We do not consider any specific alphabet. In particular, it is possible to have more than 26 different letters.
-For any suffix array, there is at least one string with such a suffix array, so the return value is always defined.
-The string A is smaller than a different string B in lexicographic order either if A is a prefix of B, or if there are indices where A and B differ, and for the smallest such index i we have A[i] < B[i].


CONSTRAINTS
-SA will contain between 1 and 50 elements, inclusive.
-SA will be a permutation of 0 to |SA|-1, inclusive.


EXAMPLES

0)
{3,0,1,2}

Returns: 2

As we saw in the problem statement, the suffix array {3,0,1,2} corresponds to the string "abca".
However, there are also other string with the same suffix array.
For example, the string "xxyx" also has this property, and contains only two different characters.

1)
{3,2,1,0}

Returns: 1

One optimal string is "aaaa".

2)
{0,1,2,3}

Returns: 2

Here, one optimal string is "aaaz".

3)
{7,4,8,6,1,5,2,9,3,0}

Returns: 4



4)
{0}

Returns: 1



*/
// END CUT HERE
#line 80 "SuffixArrayDiv1.cpp"
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

class SuffixArrayDiv1
{
public:
 int minimalCharacters(vector <int> SA)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3,0,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minimalCharacters(Arg0)); }
	void test_case_1() { int Arr0[] = {3,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minimalCharacters(Arg0)); }
	void test_case_2() { int Arr0[] = {0,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minimalCharacters(Arg0)); }
	void test_case_3() { int Arr0[] = {7,4,8,6,1,5,2,9,3,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, minimalCharacters(Arg0)); }
	void test_case_4() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(4, Arg1, minimalCharacters(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 SuffixArrayDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
