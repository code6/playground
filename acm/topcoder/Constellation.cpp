// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Fox Ciel has a map of the night sky.
On this map she found a constellation that consists of n stars, numbered 0 through n-1 in no particular order.


You are given vector <int>s x, y, and prob.
For each i, star i is located at coordinates (x[i],y[i]) on the map.
The probability that star i will be visible when Ciel looks at the sky is prob[i]/1000.


In the evening Ciel is going to take a look at the night sky.
She will find the constellation in the sky, and mark all the visible stars on her map.
She will then compute the area of the convex hull of the visible stars.
Compute and return the expected value of that area.

DEFINITION
Class:Constellation
Method:expectation
Parameters:vector <int>, vector <int>, vector <int>
Returns:double
Method signature:double expectation(vector <int> x, vector <int> y, vector <int> prob)


NOTES
-The events that represent the visibility of individual stars are mutually independent. Thus you may assume that the visibility of each star was independently generated at random with the given probability, just before Ciel looked at the sky.
-Whenever there is a line that contains all the visible stars, the area of their convex hull is 0.
-Return values with absolute or relative error at most 1e-9 will be accepted as correct.


CONSTRAINTS
-x will contain between 3 and 50 elements, inclusive.
-x, y and prob will contain same number of elements.
-Each element in x will be between -100 and 100, inclusive.
-Each element in y will be between -100 and 100, inclusive.
-Each element in prob will be between 1 and 1,000, inclusive.
-There will be no two stars at the same position.


EXAMPLES

0)
{0,0,1}
{0,1,0}
{500,500,500}

Returns: 0.0625

We have 3 points (0,0), (0,1), (1,0), all of them have 50% probability to be visible. We have 0.5^3 probability to see all 3 stars, and the area will be 0.5, in all other cases, the area will be 0. So the expectation is 0.5^4 = 0.0625.

1)
{0,1,0,1}
{0,0,1,1}
{1000,1000,400,800}

Returns: 0.6000000000000001

Stars 0 and 1 are always visible, thus there are four possible cases:

All four stars are visible with probability 0.4 * 0.8 = 0.32, and in that case the area is 1.
With probability (1-0.4)*0.8 = 0.48 star 3 is the only invisible star, and the area is 0.5.
With probability 0.4*(1-0.8) = 0.08 star 2 is the only invisible star, and the area is 0.5.
Finally, with probability (1-0.4)*(1-0.8) = 0.12 only stars 0 and 1 are visible, and the area is 0.

Thus, the answer is 0.32 * 1 + 0.48 * 0.5 + 0.08 * 0.5 + 0.12 * 0 = 0.6.

2)
{-1,-1,-1,0,0,0,1,1,1}
{-1,0,1,-1,0,1,-1,0,1}
{500,500,500,500,500,500,500,500,500}

Returns: 1.9375



3)
{0,0,1,2,2}
{0,1,2,1,0}
{1000,500,200,500,1000}

Returns: 1.3



4)
{1,5,5,8,2,6,9}
{3,6,4,2,5,7,9}
{100,400,200,1000,400,900,600}

Returns: 12.888936



5)
{-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43}
{-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44}
{1000,1000,1000,1000,342,747,897,325,678,34,53,6,253}

Returns: 40000.0



*/
// END CUT HERE
#line 107 "Constellation.cpp"
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

class Constellation
{
public:
 double expectation(vector <int> x, vector <int> y, vector <int> prob)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500,500,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.0625; verify_case(0, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {0,1,0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,0,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,400,800}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 0.6000000000000001; verify_case(1, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {-1,-1,-1,0,0,0,1,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1,0,1,-1,0,1,-1,0,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {500,500,500,500,500,500,500,500,500}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.9375; verify_case(2, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {0,0,1,2,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,2,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,500,200,500,1000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 1.3; verify_case(3, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_4() { int Arr0[] = {1,5,5,8,2,6,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,6,4,2,5,7,9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {100,400,200,1000,400,900,600}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 12.888936; verify_case(4, Arg3, expectation(Arg0, Arg1, Arg2)); }
	void test_case_5() { int Arr0[] = {-100,100,-100,100,-42,57,-34,76,35,-75,-54,10,43}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-100,-100,100,100,52,-57,-84,63,-43,50,63,10,-44}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000,1000,1000,1000,342,747,897,325,678,34,53,6,253}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); double Arg3 = 40000.0; verify_case(5, Arg3, expectation(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 Constellation ___test;
 ___test.run_test(-1);
}
// END CUT HERE
