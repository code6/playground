// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Manao is building a new house. He already purchased a rectangular area where he will place the house. The basement of the house should be built on a level ground, so Manao will have to level the entire area. The area is leveled if the difference between the heights of its lowest and highest square meter is at most 1. Manao wants to measure the effort he needs to put into ground leveling.

You are given a vector <string> area. Each character in area denotes the height at the corresponding square meter of Manao's area. Using 1 unit of effort, Manao can change the height of any square meter on his area by 1 up or down. Return the minimum total effort he needs to put to obtain a leveled area.


DEFINITION
Class:HouseBuilding
Method:getMinimum
Parameters:vector <string>
Returns:int
Method signature:int getMinimum(vector <string> area)


CONSTRAINTS
-area will contain between 1 and 50 elements, inclusive.
-Each element of area will be between 1 and 50 characters long, inclusive.
-All elements of area will be of the same length.
-Each element of area will contain digits ('0'-'9') only.


EXAMPLES

0)
{"10",
 "31"}

Returns: 2

The given area is not leveled, because the minimum height is 0 and the maximum height is 3. Manao needs to reduce the height of lower left square by 2.

1)
{"54454",
 "61551"}

Returns: 7

In the optimal solution each square will have height either 4 or 5. To reach such a configuration, Manao should reduce the height of one square from 6 to 5, and increase the heights of two other squares from 1 to 4.

2)
{"989"}

Returns: 0

The area is already leveled.

3)
{"90"}

Returns: 8



4)
{"5781252",
 "2471255",
 "0000291",
 "1212489"}

Returns: 53



*/
// END CUT HERE
#line 69 "HouseBuilding.cpp"
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

class HouseBuilding
{
public:
 int getMinimum(vector <string> area)
 {
     int i, j, k;
     int ans = 100000000;
     for (i = 0; i < 9; i++) {
         int tempcost = 0;
         for(j = 0; j < area.size(); j++) {
             for (k = 0; k < area[j].size(); k++) {
                 int d = area[j][k] - '0';
                 int cost = min(abs(d - i), abs(d - i - 1));
                 tempcost += cost;
             }
         }
         ans = min(ans, tempcost);
     }
     return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"10",
 "31"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { string Arr0[] = {"54454",
 "61551"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { string Arr0[] = {"989"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { string Arr0[] = {"90"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { string Arr0[] = {"5781252",
 "2471255",
 "0000291",
 "1212489"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 53; verify_case(4, Arg1, getMinimum(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 HouseBuilding ___test;
 ___test.run_test(-1);
}
// END CUT HERE
