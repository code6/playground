// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Cucumber Boy likes drawing pictures.  Today, he plans to draw a picture using a very simple graphics editor.

The editor has the following functions:

The canvas is an infinite two-dimensional grid of pixels.
There are only two colors: black, and transparent. These are denoted 'B' and '.' (a period), respectively.
The editor has a clipboard that contains a rectangular picture.
The editor can take the picture in the clipboard and paste it onto any corresponding rectangle of the canvas. The user just has to select the pixel of the canvas where the upper left corner of the clipboard will be pasted.
When pasting the picture, the black pixels of the picture in the clipboard will overwrite their corresponding pixels on the canvas. The pixels that are transparent in the clipboard picture do not change the canvas.


At this moment, all pixels on the infinite canvas are transparent.  Cucumber Boy has already stored a picture in the clipboard.  You are given this picture as a vector <string> clipboard.

Cucumber Boy now wants to paste the clipboard picture onto the canvas exactly T times in a row.
For each i, when pasting the clipboard for the i-th time, he will choose the pixel (i,i) as the upper left corner of the pasted picture.

You are given the vector <string> clipboard and the int T.  Return the number of black pixels on the canvas after all the pasting is finished.

DEFINITION
Class:PastingPaintingDivTwo
Method:countColors
Parameters:vector <string>, int
Returns:long long
Method signature:long long countColors(vector <string> clipboard, int T)


CONSTRAINTS
-clipboard will contain between 1 and 50 elements, inclusive.
-Each element of clipboard will contain between 1 and 50 characters, inclusive.
-Each element of clipboard will contain the same number of characters.
-Each character of each element of clipboard will be 'B' or '.'.
-T will be between 1 and 1,000,000,000, inclusive.


EXAMPLES

0)
{
"..B",
"B..",
"BB."
}
3

Returns: 10



1)
{
"B...",
"....",
"....",
"...B"
}
2

Returns: 4



2)
{"BBB"}
10000

Returns: 30000



3)
{"."}
1000000000

Returns: 0



4)
{
"BB.",
".B."
}
100

Returns: 201



5)
{
"..........B..........",
".........B.B.........",
"........B...B........",
".......B.....B.......",
"......B..B.B..B......",
".....B...B.B...B.....",
"....B...........B....",
"...B...B.....B...B...",
"..B.....BBBBBB....B..",
".B..........BB.....B.",
"BBBBBBBBBBBBBBBBBBBBB"
}
1000000000

Returns: 21000000071

Note that the answer may overflow a 32-bit integer variable.


This is the image of clipboard in this example.

*/
// END CUT HERE
#line 118 "PastingPaintingDivTwo.cpp"
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

class PastingPaintingDivTwo
{
public:
 long long countColors(vector <string> clipboard, int T)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {
"..B",
"B..",
"BB."
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 10LL; verify_case(0, Arg2, countColors(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {
"B...",
"....",
"....",
"...B"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 4LL; verify_case(1, Arg2, countColors(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"BBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10000; long long Arg2 = 30000LL; verify_case(2, Arg2, countColors(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; long long Arg2 = 0LL; verify_case(3, Arg2, countColors(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {
"BB.",
".B."
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 100; long long Arg2 = 201LL; verify_case(4, Arg2, countColors(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {
"..........B..........",
".........B.B.........",
"........B...B........",
".......B.....B.......",
"......B..B.B..B......",
".....B...B.B...B.....",
"....B...........B....",
"...B...B.....B...B...",
"..B.....BBBBBB....B..",
".B..........BB.....B.",
"BBBBBBBBBBBBBBBBBBBBB"
}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000000000; long long Arg2 = 21000000071LL; verify_case(5, Arg2, countColors(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PastingPaintingDivTwo ___test;
 ___test.run_test(-1);
}
// END CUT HERE
