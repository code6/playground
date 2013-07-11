// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// There is a white rectangular board divided into a grid of unit square cells.
Fox Ciel wants to paint some of the cells black, so that the board looks as described by the vector <string> target.
More precisely: for each i, j, the cell in row i, column j of the board (0-based indices) should be painted black if target[i][j] is '#', and it should remain white if target[i][j] is '.'.



Fox Ciel paints in steps.
In each step, she selects a group of white cells and paints all of them black.
She is only allowed to select a contiguous sequence of white cells in a single row or in a single column.



Return the minimal number of steps needed to color the board.

DEFINITION
Class:BoardPainting
Method:minimalSteps
Parameters:vector <string>
Returns:int
Method signature:int minimalSteps(vector <string> target)


CONSTRAINTS
-n will be between 1 and 50, inclusive.
-m will be between 1 and 50, inclusive.
-target will contains exactly n elements.
-Each element in target will contains exactly m characters.
-Each character in target will be '#' or '.'.


EXAMPLES

0)
{"#####"}

Returns: 1

Fox Ciel can select the entire row of the board and paint it all black in a single step.

1)
{"#####",
 ".....",
 "#####",
 ".....",
 "#####"}

Returns: 3

In each turn, Ciel selects and colors one of the rows that should be black.

2)
{"..#..",
 "..#..",
 "#####",
 "..#..",
 "..#.."}

Returns: 3

Note that each sequence of cells selected by Ciel has to be a contiguous sequence of white cells. It is not allowed to select a black cell. Therefore the best solution has three steps. One possibility: first she selects row 2, then the first two cells in column 2, and finally the last two cells in column 2.

3)
{"#####",
 "..#..",
 "#####",
 "..#..",
 "#####"}

Returns: 5



4)
{".#.#.",
 "#####",
 ".#.#.",
 "#####",
 ".#.#."}

Returns: 8



5)
{".##.####.####.#########.##..",
 "##.#.####################.##",
 ".##.###.##.###.###.###.###..",
 "#..###..#########..###.##.##",
 "####..#######.#.#####.######",
 "##.######.#..#.#############",
 "##.######.###########.######",
 "#######.#######.#..###.#.###",
 "#####..#######.#####.#.###.#",
 "#..#################.#.####.",
 "##.######..#.#####.######.##",
 "..#.#############.#.##....#.",
 "....##..##..#.#####.#.###.##",
 "##.#########...#..#.#.######",
 "##.#..###########..#..####.#",
 "#.####.###.########.########",
 "#####.#########.##.##.######",
 ".##.####..###.###...######.#"}

Returns: 88



6)
{"...................."}

Returns: 0

Note that the target can be totally white.

*/
// END CUT HERE
#line 121 "BoardPainting.cpp"
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

class BoardPainting
{
public:
 int minimalSteps(vector <string> target)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"#####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minimalSteps(Arg0)); }
	void test_case_1() { string Arr0[] = {"#####",
 ".....",
 "#####",
 ".....",
 "#####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(1, Arg1, minimalSteps(Arg0)); }
	void test_case_2() { string Arr0[] = {"..#..",
 "..#..",
 "#####",
 "..#..",
 "..#.."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, minimalSteps(Arg0)); }
	void test_case_3() { string Arr0[] = {"#####",
 "..#..",
 "#####",
 "..#..",
 "#####"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, minimalSteps(Arg0)); }
	void test_case_4() { string Arr0[] = {".#.#.",
 "#####",
 ".#.#.",
 "#####",
 ".#.#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 8; verify_case(4, Arg1, minimalSteps(Arg0)); }
	void test_case_5() { string Arr0[] = {".##.####.####.#########.##..",
 "##.#.####################.##",
 ".##.###.##.###.###.###.###..",
 "#..###..#########..###.##.##",
 "####..#######.#.#####.######",
 "##.######.#..#.#############",
 "##.######.###########.######",
 "#######.#######.#..###.#.###",
 "#####..#######.#####.#.###.#",
 "#..#################.#.####.",
 "##.######..#.#####.######.##",
 "..#.#############.#.##....#.",
 "....##..##..#.#####.#.###.##",
 "##.#########...#..#.#.######",
 "##.#..###########..#..####.#",
 "#.####.###.########.########",
 "#####.#########.##.##.######",
 ".##.####..###.###...######.#"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 88; verify_case(5, Arg1, minimalSteps(Arg0)); }
	void test_case_6() { string Arr0[] = {"...................."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(6, Arg1, minimalSteps(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 BoardPainting ___test;
 ___test.run_test(-1);
}
// END CUT HERE
