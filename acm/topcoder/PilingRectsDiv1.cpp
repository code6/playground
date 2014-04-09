// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Snake Snuke has 2N rectangles cut out of paper.
The rectangles are labeled 0 through 2N-1.
For each i, the side lengths of rectangle i will be denoted X[i] and Y[i].

The number N can be very large, therefore we will use a pseudorandom generator to define the values X[i] and Y[i].
You are given the following input:

The int N.
Two vector <int>s: XS and YS.
Six ints: XA, XB, XC, YA, YB, YC.


Use the following pseudocode to generate X and Y:


for (i = 0; i < (length of XS); i++) {
    X[i] = XS[i];
    Y[i] = YS[i];
}
for (i = (length of XS); i < 2 * N; i++) {
    X[i] = (X[i - 1] * XA + XB) % XC + 1;
    Y[i] = (Y[i - 1] * YA + YB) % YC + 1;
}


Snake Snuke will divide his 2N rectangles into two bags, each bag containing exactly N rectangles.
Then he will process each bag separately.

When processing a bag, he will take all the rectangles out of the bag and he will place them onto a table, one rectangle at a time.
Each rectangle (except for the first one) must overlap the immediately previous one, so at the end Snuke will have a pile of N rectangles.
Snuke may rotate the rectangles, but once placed, the sides of each rectangle must be parallel with the sides of the table.
(I.e., he may only swap the width and height of some rectangles.)
After placing all the rectangles, Snuke computes the area that is covered by all N rectangles.
(Formally, the area of their intersection.)
That area is called the outcome of that bag.

Snuke wants to maximize the sum of the outcomes of his two bags.
That is, he must first divide the rectangles into bags in an optimal way, and then process each bag in an optimal way.
Return the maximal possible sum of the two outcomes.


DEFINITION
Class:PilingRectsDiv1
Method:getmax
Parameters:int, vector <int>, vector <int>, int, int, int, int, int, int
Returns:long long
Method signature:long long getmax(int N, vector <int> XS, vector <int> YS, int XA, int XB, int XC, int YA, int YB, int YC)


CONSTRAINTS
-N will be between 1 and 100,000, inclusive.
-XS will contain between 1 and min{50, 2*N} elements, inclusive.
-XS and YS will be contain the same number of elements, inclusive.
-Each element of XS and YS will be between 1 and 1,000,000,000 (109), inclusive.
-XA, XB, YA and YB will be between 0 and 1,000,000,000 (109), inclusive.
-XC and YC will be between 1 and 1,000,000,000 (109), inclusive.


EXAMPLES

0)
2
{1,2,3,4}
{10,5,3,5}
0
0
1
0
0
1

Returns: 14

Snuke should put rectangles 0 and 1 in one bag, and rectangles 2 and 3 into the other bag. He can then process the bags as shown in the picture below (where rectangle 0 is labeled as "first", and so on). The sum of the two areas is 14. There are other equally good solutions, but there is no better solution than 14.



1)
2
{7,7}
{4,4}
9
0
10
2
7
9

Returns: 56

X is {7,7,4,7} and Y is {4,4,7,4}. Note that it is allowed to rotate the rectangles. Regardless of how Snuke divides the rectangles into bags, each bag will contain two 4x7 rectangles. When processing a bag, Snuke can align the two rectangles perfectly. Thus the answer is 28 + 28 = 56.

2)
3
{5,6,9,10,4,7}
{9,5,8,6,8,7}
0
0
1
0
0
1

Returns: 69



3)
10000
{1000000000}
{1000000000}
93827162
91238127
98231267
92138287
98563732
99381279

Returns: 1240119561532788

Use a 64-bit data type for generating the input data in order to avoid overflow. Also note that the return value is a long long.

4)
5
{375,571,973,896,460,930,583,530,657,590}
{284,37,994,699,941,745,166,884,270,708}
428
1000
788
851
125
894

Returns: 420515



5)
34734
{898,579,465,665,875,391,583,901,326,133,656,562,701,707,492,617,455,441,382,952,689,656,334,877,120,318,497,25,569,962,845,562,632,898,882,498,595,889,382,507,791,548,810,606,105,869,569,970,322,974}
{83,18,492,27,339,622,851,915,464,347,287,210,282,166,976,167,968,769,14,383,454,983,319,165,185,315,795,851,124,287,846,745,19,639,894,828,540,420,147,452,501,670,466,554,166,1,446,808,508,172}
569
185
285
741
304
296

Returns: 10050



*/
// END CUT HERE
#line 159 "PilingRectsDiv1.cpp"
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
typedef long long ll;
typedef pair<ll, ll> PLL;

class PilingRectsDiv1
{
public:
 long long getmax(int N, vector <int> XS, vector <int> YS, int XA, int XB, int XC, int YA, int YB, int YC)
 {
 //$CARETPOSITION$
    vector<PLL> arr;
    range(i, 2 * N) {
        if (i < XS.size()) {
            arr[i].fs = XS[i];
            arr[i].sc = YS[i];
        } else {
            arr[i].fs = (arr[i-1].fs  * XA + XB) % XC + 1;
            arr[i].sc = (arr[i-1].sc  * YA + YB) % YC + 1;
        }
    }
    sort(all(arr));
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 2; int Arr1[] = {1,2,3,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10,5,3,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 0; int Arg5 = 1; int Arg6 = 0; int Arg7 = 0; int Arg8 = 1; long long Arg9 = 14LL; verify_case(0, Arg9, getmax(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_1() { int Arg0 = 2; int Arr1[] = {7,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {4,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 9; int Arg4 = 0; int Arg5 = 10; int Arg6 = 2; int Arg7 = 7; int Arg8 = 9; long long Arg9 = 56LL; verify_case(1, Arg9, getmax(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_2() { int Arg0 = 3; int Arr1[] = {5,6,9,10,4,7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {9,5,8,6,8,7}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 0; int Arg4 = 0; int Arg5 = 1; int Arg6 = 0; int Arg7 = 0; int Arg8 = 1; long long Arg9 = 69LL; verify_case(2, Arg9, getmax(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_3() { int Arg0 = 10000; int Arr1[] = {1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000000000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 93827162; int Arg4 = 91238127; int Arg5 = 98231267; int Arg6 = 92138287; int Arg7 = 98563732; int Arg8 = 99381279; long long Arg9 = 1240119561532788LL; verify_case(3, Arg9, getmax(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_4() { int Arg0 = 5; int Arr1[] = {375,571,973,896,460,930,583,530,657,590}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {284,37,994,699,941,745,166,884,270,708}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 428; int Arg4 = 1000; int Arg5 = 788; int Arg6 = 851; int Arg7 = 125; int Arg8 = 894; long long Arg9 = 420515LL; verify_case(4, Arg9, getmax(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }
	void test_case_5() { int Arg0 = 34734; int Arr1[] = {898,579,465,665,875,391,583,901,326,133,656,562,701,707,492,617,455,441,382,952,689,656,334,877,120,318,497,25,569,962,845,562,632,898,882,498,595,889,382,507,791,548,810,606,105,869,569,970,322,974}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {83,18,492,27,339,622,851,915,464,347,287,210,282,166,976,167,968,769,14,383,454,983,319,165,185,315,795,851,124,287,846,745,19,639,894,828,540,420,147,452,501,670,466,554,166,1,446,808,508,172}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 569; int Arg4 = 185; int Arg5 = 285; int Arg6 = 741; int Arg7 = 304; int Arg8 = 296; long long Arg9 = 10050LL; verify_case(5, Arg9, getmax(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7, Arg8)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PilingRectsDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
