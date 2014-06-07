// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// There are N cities in Treeland.
The cities are numbered 1 through N.
The roads in Treeland have the topology of a tree.
That is, there are exactly N-1 bidirectional roads in Treeland, each connecting a pair of cities, and it is possible to travel between any two cities along the roads.
For the purpose of this problem, all roads have the same length, and this length is our unit of distance.

You are given two vector <int>s A and B that describe the tree.
Each of these vector <int>s has N-1 elements.
For each valid i, there is a road that connects the cities A[i] and B[i].

There are some foxes in Treeland.
Currently, each of the foxes lives in a different city.
You are given a string haveFox with N characters.
For each i, character i of haveFox is 'Y' if there is a fox in city i+1, or 'N' otherwise.

The foxes would like to live closer to each other.
To achieve that, some foxes (possibly all of them or none at all) will move to different cities.
There are three constraints for the move:

After the foxes move, there must again be at most one fox in each city. (There are no restrictions on how the foxes travel while they are moving.)
After the foxes move, the set of cities inhabited by the foxes must be connected. That is, for any two different cities i and j that both contain a fox, all the cities on the (only) path between i and j must also contain a fox.
The total distance traveled by the foxes during the move must be as small as possible.



Return the smallest possible sum of distances traveled by the foxes.

DEFINITION
Class:FoxConnection
Method:minimalDistance
Parameters:vector <int>, vector <int>, string
Returns:int
Method signature:int minimalDistance(vector <int> A, vector <int> B, string haveFox)


CONSTRAINTS
-N will be between 2 and 50, inclusive.
-A will contain exactly N-1 elements.
-Each element of A will be between 1 and N, inclusive.
-B will contain exactly N-1 elements.
-Each element of B will be between 1 and N, inclusive.
-The graph described by A and B will be a tree.
-haveFox will contain exactly N characters.
-Each character in haveFox will be either 'Y' or 'N'.


EXAMPLES

0)
{1,2,3}
{2,3,4}
"YNNY"

Returns: 2

Treeland looks as follows: 1-2-3-4. Two foxes are located in city 1 and city 4. One optimal solution is:

The fox located in city 1 moves to city 2.
The fox located in city 4 moves to city 3.


1)
{1,1,1,1}
{2,3,4,5}
"NYYYY"

Returns: 1

We can move any one of the foxes to city 1. After that the cities with foxes will form a connected set.

2)
{1,3,4,5,4}
{2,2,2,4,6}
"YNYNYY"

Returns: 2



3)
{1,2,3,4,5,6,7,8,9}
{2,3,4,5,6,7,8,9,10}
"YNNNYNYNNY"

Returns: 7



4)
{1,2,3,4,3,6,8,7}
{2,3,4,5,6,8,9,6}
"YNNYYNYYY"

Returns: 3



5)
{1}
{2}
"NY"

Returns: 0

There can be only 1 fox.

6)
{1}
{2}
"NN"

Returns: 0

And there can be no foxes.

*/
// END CUT HERE
#line 122 "FoxConnection.cpp"
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

class FoxConnection
{
public:
 int minimalDistance(vector <int> A, vector <int> B, string haveFox)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "YNNY"; int Arg3 = 2; verify_case(0, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {1,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NYYYY"; int Arg3 = 1; verify_case(1, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {1,3,4,5,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,2,2,4,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "YNYNYY"; int Arg3 = 2; verify_case(2, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {1,2,3,4,5,6,7,8,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "YNNNYNYNNY"; int Arg3 = 7; verify_case(3, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1,2,3,4,3,6,8,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,3,4,5,6,8,9,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "YNNYYNYYY"; int Arg3 = 3; verify_case(4, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NY"; int Arg3 = 0; verify_case(5, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }
	void test_case_6() { int Arr0[] = {1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "NN"; int Arg3 = 0; verify_case(6, Arg3, minimalDistance(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 FoxConnection ___test;
 ___test.run_test(-1);
}
// END CUT HERE
