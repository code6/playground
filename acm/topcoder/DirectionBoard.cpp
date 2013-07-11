// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A direction board is a matrix filled with arrows. Each arrow occupies one cell and points in one of the four directions: left, right, down, up. Each cell has two coordinates (row, column), starting with (0, 0) in the top left corner. Given a starting cell (r, c), you can move through the board in the following way. First, check the arrow in cell (r, c). If it points left, move left of the current cell, i.e. into cell(r, c - 1). For the right arrow, move to (r, c + 1). Up goes to (r - 1, c) and down to (r + 1, c). Each row and column of the board is cyclic, so whenever the new cell is outside the board, you appear on the other side. For example, moving left from (3, 0) on a board of size 5 by 5 results in appearing in cell (3, 4).

You need a board such that for every starting cell you always return to it during the movement process. If the given board does not satisfy this condition, you can change the direction of the arrow in any cell. For example, look at the following boards. In the left one, one only returns to the initial cell when he begins in cells (1, 1), (1, 2), (2, 0), (2, 3). After redirecting two arrows, you obtain a board with the given property.



Find the minimum number of arrow redirections which transforms the given board into a valid one.

DEFINITION
Class:DirectionBoard
Method:getMinimum
Parameters:vector <string>
Returns:int
Method signature:int getMinimum(vector <string> board)


CONSTRAINTS
-board will contain between 1 and 15 elements, inclusive.
-Each element of board will contain between 1 and 15 characters, inclusive.
-All elements of board will be of the same length.
-Each element of board will consist of characters from the set {'L', 'R', 'U', 'D'} only.


EXAMPLES

0)
{"RRRD",
 "URDD",
 "UULD",
 "ULLL"}

Returns: 0

This board is already good. No matter which cell you start in, you always you return to it.

1)
{"RRRD",
 "URLL",
 "LRRR"}

Returns: 2

The example from the problem statement.

2)
{"RRD",
 "URD",
 "ULL"}

Returns: 2

This board is not valid, because if one starts from (1, 1), he never returns to this cell. A possible solution with only two changes:



3)
{"ULRLRD",
 "UDDLRR"}

Returns: 4



4)
{"UDLRLDLD",
 "DLDLLDLR",
 "LLLLLDLD",
 "UUURRRDD"}

Returns: 9



5)
{"UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUUDDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "RRRDLDURDURUDDR"}


Returns: 73



*/
// END CUT HERE
#line 102 "DirectionBoard.cpp"
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

class DirectionBoard
{
public:
 int getMinimum(vector <string> board)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"RRRD",
 "URDD",
 "UULD",
 "ULLL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(0, Arg1, getMinimum(Arg0)); }
	void test_case_1() { string Arr0[] = {"RRRD",
 "URLL",
 "LRRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, getMinimum(Arg0)); }
	void test_case_2() { string Arr0[] = {"RRD",
 "URD",
 "ULL"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, getMinimum(Arg0)); }
	void test_case_3() { string Arr0[] = {"ULRLRD",
 "UDDLRR"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(3, Arg1, getMinimum(Arg0)); }
	void test_case_4() { string Arr0[] = {"UDLRLDLD",
 "DLDLLDLR",
 "LLLLLDLD",
 "UUURRRDD"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(4, Arg1, getMinimum(Arg0)); }
	void test_case_5() { string Arr0[] = {"UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUUDDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "DLLDLDURDURUDDL",
 "UDUDUUDUDUDUDUR",
 "LLLLDUUDRDLUDRU",
 "RRRDLDURDURUDDR"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 73; verify_case(5, Arg1, getMinimum(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 DirectionBoard ___test;
 ___test.run_test(-1);
}
// END CUT HERE
