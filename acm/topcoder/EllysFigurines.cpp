// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Elly has placed several (possibly none) figurines on a rectangular board with several rows and columns. Now Kristina wants to remove all figurines from the board. In a single move she selects either up to R consecutive rows, or up to C consecutive columns and removes all remaining figurines that are located there. The girl wonders what is the minimal number of moves in which she can clear the entire board.

The position of the figurines will be given to you in the vector <string> board. The j-th character of the i-th element of board will be '.' if the cell is empty, or 'X' if it contains a figurine. The maximal number of cleared rows in a single move will be given in the int R. The maximal number of cleared columns in a single move will be given in the int C. Return the minimal number of moves that is sufficient to clear the entire board.

DEFINITION
Class:EllysFigurines
Method:getMoves
Parameters:vector <string>, int, int
Returns:int
Method signature:int getMoves(vector <string> board, int R, int C)


NOTES
-In a single move the girl can only select a consecutive group of rows or columns to be cleared. In other words, in each move Kristina first decides whether she wants rows or columns, then she picks the index i of the first chosen row/column, then the number k of chosen rows/columns, and finally she removes all figurines from the rows/columns with indices i, i+1, i+2, ..., i+k-1.


CONSTRAINTS
-board will contain between 1 and 15 elements, inclusive.
-Each element of board will contain between 1 and 15 characters, inclusive.
-All elements of board will contain the same number of characters.
-Each character of board will be either '.' or 'X'.
-R will be between 1 and 15, inclusive.
-C will be between 1 and 15, inclusive.


EXAMPLES

0)
{".X.X.",
 "XX..X",
 ".XXX.",
 "...X.",
 ".X.XX"}
1
2

Returns: 3

In this case in a single move Elly can remove all figurines from a single row, all figurines from a single column or all figurines from two consecutive columns.
One way to achieve the optimal answer here would be to remove the figurines from the first and second column in the first move, then the ones from the fourth and fifth column in the second move, and finally the remaining ones on the third row in the third move.
Another solution would be to erase only columns, again using three moves.

1)
{".X.X.",
 "XX..X",
 ".X.X.",
 "...X.",
 ".X.XX"}
2
2

Returns: 2

Almost the same as the first example, but without the figurine in the middle and the number of maximal rows removed is increased by one.
This time, the only optimal solution is to clear the first two columns in one move and the last two in another move.

2)
{"XXXXXXX"}
2
3

Returns: 1

The maximal allowed number of cleared rows or columns might be greater than the corresponding dimension of the board. The optimal solution for this board is to clear the only row in one move.

3)
{"XXXXX",
 "X....",
 "XXX..",
 "X....",
 "XXXXX"}
1
1

Returns: 4

Here clearing rows 1, 3 and 5, together with column 1 yields the best result 4.

4)
{"XXX..XXX..XXX.",
 ".X..X....X...X",
 ".X..X....X...X",
 ".X..X....X...X",
 ".X...XXX..XXX.",
 "..............",
 "...XX...XXX...",
 "....X......X..",
 "....X....XXX..",
 "....X......X..",
 "...XXX..XXX..."}
1
2

Returns: 7

Good luck in TCO 13!

*/
// END CUT HERE
#line 104 "EllysFigurines.cpp"
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
#define two(i) (1<<(i))

int H, W;

int ch[1<<20], cw[1<<20];

void calc(int state[], int l, int s) {
    int i, j;
    int arr[20];
    for (i = 0; i < two(l); i++) {
        state[i] = 0;
        for (j = 0; j < l; j++) {
            if (two(j) & i) {
                arr[j] = 1;
            } else {
                arr[j] = 0;
            }
        }
        for (j = 0; j < l; j++) {
            if (arr[j] == 1) {
                state[i] ++;
                j += s - 1;
            }
        }
    }
}

class EllysFigurines
{
public:
 int getMoves(vector <string> board, int R, int C)
 {
 //$CARETPOSITION$
    H = board.size();
    W = board[0].size();
    memset(ch, 0, sizeof(ch));
    memset(cw, 0, sizeof(cw));
    calc(ch, H, R);
    calc(cw, W, C);
    int ans = 10000;
    int i, j, k;
    for (i = 0; i < two(H); i++) {
        int temp = ch[i];
        int s = 0;
        for (j = 0; j < H; j++) {
            if (!(two(j) & i)) {
                for (k = 0; k < W; k++) {
                    if (board[j][k] == 'X') {
                        s |= two(k);
                    }
                }
            }
        }
        temp += cw[s];
        ans = min(ans, temp);
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {".X.X.",
 "XX..X",
 ".XXX.",
 "...X.",
 ".X.XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 3; verify_case(0, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {".X.X.",
 "XX..X",
 ".X.X.",
 "...X.",
 ".X.XX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; verify_case(1, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"XXXXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 1; verify_case(2, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"XXXXX",
 "X....",
 "XXX..",
 "X....",
 "XXXXX"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 1; int Arg3 = 4; verify_case(3, Arg3, getMoves(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"XXX..XXX..XXX.",
 ".X..X....X...X",
 ".X..X....X...X",
 ".X..X....X...X",
 ".X...XXX..XXX.",
 "..............",
 "...XX...XXX...",
 "....X......X..",
 "....X....XXX..",
 "....X......X..",
 "...XXX..XXX..."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; int Arg3 = 7; verify_case(4, Arg3, getMoves(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 EllysFigurines ___test;
 ___test.run_test(-1);
}
// END CUT HERE
