// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Bob recently went to Mars.

There are N cities on Mars. The cities all lie on a circular railroad and they are numbered 0 through N-1 along the railroad. More precisely, there is a railroad segment that connects cities N-1 and 0, and for each i (0 <= i <= N-2) there is a railroad segment that connects cities i and i+1. Trains travel along the railroad in both directions.

You are given a vector <int> range with N elements. For each i: the set of cities that are reachable from city i by a direct train is precisely the set of cities that are within the distance range[i] of city i. (The distance between two cities is the smallest number of railroad segments one needs to travel in order to get from one city to the other. For example, if N=17 and range[2]=3, the cities directly reachable from city 2 are the cities {16,0,1,2,3,4,5}.)

You are also given ints startCity and endCity. Bob starts his tour in the city startCity and wants to end it in the city endCity. Calculate and return the minimum number of succesive direct trains he needs to take.


DEFINITION
Class:TravelOnMars2
Method:minTimes
Parameters:vector <int>, int, int
Returns:int
Method signature:int minTimes(vector <int> range, int startCity, int endCity)


CONSTRAINTS
-range will contain N elements, where N is between 2 and 50, inclusive.
-Each element of range will be between 1 and 50, inclusive.
-startCity will be between 0 and N-1, inclusive.
-endCity will be between 0 and N-1, inclusive.
-startCity and endCity will be different.


EXAMPLES

0)
{2, 1, 1, 1, 1, 1}
1
4

Returns: 2

Bob wants to get from city 1 to city 4.
The optimal solution is to travel from city 1 to city 0, and then (as range[0]=2) from city 0 to city 4.


1)
{2, 1, 1, 2, 1, 2, 1, 1}
2
6

Returns: 3

This is the same test case as Example 0, only startCity and endCity have been swapped. Note that the answer is now 3 instead of 2.


2)
{3, 2, 1, 1, 3, 1, 2, 2, 1, 1, 2, 2, 2, 2, 3}
6
13

Returns: 4

Bob starts in city 2. There are two optimal routes: (2->3->5->6) and (2->1->0->6).


3)
{2, 4, 2, 3, 4, 1, 4, 2, 5, 4, 3, 3, 5, 4, 5, 2, 2, 4, 4, 3, 3, 4, 2, 3, 5, 4, 2, 4, 1, 3, 2, 3, 4, 1, 1, 4, 4, 3, 5, 3, 2, 1, 4, 1, 4}
24
8

Returns: 5



*/
// END CUT HERE
#line 74 "TravelOnMars2.cpp"
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

class TravelOnMars2
{
public:
 int minTimes(vector <int> range, int startCity, int endCity)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 1, 1, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 4; int Arg3 = 2; verify_case(0, Arg3, minTimes(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arr0[] = {2, 1, 1, 2, 1, 2, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 6; int Arg3 = 3; verify_case(1, Arg3, minTimes(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arr0[] = {3, 2, 1, 1, 3, 1, 2, 2, 1, 1, 2, 2, 2, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 13; int Arg3 = 4; verify_case(2, Arg3, minTimes(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arr0[] = {2, 4, 2, 3, 4, 1, 4, 2, 5, 4, 3, 3, 5, 4, 5, 2, 2, 4, 4, 3, 3, 4, 2, 3, 5, 4, 2, 4, 1, 3, 2, 3, 4, 1, 1, 4, 4, 3, 5, 3, 2, 1, 4, 1, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 24; int Arg2 = 8; int Arg3 = 5; verify_case(3, Arg3, minTimes(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 TravelOnMars2 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
