// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A square board is divided into N rows by N columns of unit square cells.
Some cells of the board are empty.
Each of the other cells contains either an apple or a pear.
You are given the current state of the board as a vector <string> board.
In board, the character '.' denotes an empty cell, 'A' denotes an apple, and 'P' denotes a pear.

You are allowed to perform at most K moves.
In each move, you can pick up one fruit (an apple or a pear) and place it onto any empty cell.
(The new cell doesn't have to be adjacent to the old one.)
Note that you cannot remove fruit from the board, you are only allowed to move it onto different cells.

A rectangular section of the board is called uniform if each cell in the rectangle contains an apple. After you are done moving the fruit, you want to have a uniform rectangle that is as large as possible somewhere on the board.
Return the largest possible area of such a rectangle. If there are no apples, return 0.

DEFINITION
Class:UniformBoard
Method:getBoard
Parameters:vector <string>, int
Returns:int
Method signature:int getBoard(vector <string> board, int K)


CONSTRAINTS
-N will be between 1 and 20, inclusive.
-board will contain exactly N elements.
-Each element of board will contain exactly N characters.
-Each character in board will be '.', 'A', or 'P'.
-K will be between 0 and 1000, inclusive.


EXAMPLES

0)
{"AP",
 ".A"}
0

Returns: 1

You cannot move anything.
The largest uniform rectangle on the board is a 1x1 rectangle that consists of a single cell with an apple.

1)
{"AP",
 ".A"}
1

Returns: 2

You are allowed to make one move.
You can move one of the apples onto the currently empty cell, thus creating a 1x2 rectangle of apples.

2)
{"PPP",
 "APA",
 "A.P"}
2

Returns: 3

In three moves you can create a 1x3 rectangle of apples.

3)
{"AAA",
 "PPP",
 "AAA"}
10

Returns: 3

You are allowed to make at most 10 moves.
However, you cannot make any moves because there are no empty cells.

4)
{"."}
1000

Returns: 0



5)
{"PPAAPA..AP",
 "PPA.APAP..",
 "..P.AA.PPP",
 "P.P..APAA.",
 "P.P..P.APA",
 "PPA..AP.AA",
 "APP..AAPAA",
 "P.P.AP...P",
 ".P.A.PAPPA",
 "..PAPAP..P"}
10

Returns: 15



*/
// END CUT HERE
#line 105 "UniformBoard.cpp"
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
#define two(i) (1LL<<(i))

typedef long long ll;
typedef pair<ll, ll> PLL;


int fcnt[25][25][3];

void prepare_fruit(const vector<string> & board) {
    memset(fcnt, 0, sizeof(fcnt));
    int n = board.size();
    range(x, n)
        range(y, n) {
            int cty = board[x][y] == '.' ? 0 : board[x][y] == 'A' ? 1:2;
            range(ty, 3) {
                fcnt[x+1][y+1][ty] = fcnt[x+1][y][ty] + fcnt[x][y+1][ty] - fcnt[x][y][ty] + (ty == cty);
            }
        }
}

int get_fruit(int x0, int y0, int x1, int y1, int ty) {
    x0 ++; y0++; x1 ++; y1 ++;
    int ret = fcnt[x1][y1][ty] - fcnt[x0-1][y1][ty] - fcnt[x1][y0-1][ty] + fcnt[x0-1][y0-1][ty];
    return ret;
}

class UniformBoard
{
public:
 int getBoard(vector <string> board, int K)
 {
 //$CARETPOSITION$
    prepare_fruit(board);
    int n = board.size();
    int empty_total = get_fruit(0, 0, n - 1, n - 1, 0);
    int apple_total = get_fruit(0, 0, n - 1, n - 1, 1);
    int pear_total  = get_fruit(0, 0, n - 1, n - 1, 2);
    int ans = 0;
    range(x0, n)
        range(y0, n)
            range(x1, n)
                range(y1, n)
                {
                    if (x0 > x1 || y0 > y1) continue;
                    int empty_cnt = get_fruit(x0, y0, x1, y1, 0);
                    int apple_cnt = get_fruit(x0, y0, x1, y1, 1);
                    int pear_cnt = get_fruit(x0, y0, x1, y1, 2);
                    int total = (x1 - x0 + 1) * (y1 - y0 + 1);
                    if (apple_total < total) continue;
                    if (empty_cnt || empty_total) {
                        if (pear_cnt + (total -  apple_cnt) <= K) {
                            ans = max(ans, total);
                        }
                    } else {
                        if (pear_cnt == 0) {
                            ans = max(ans, total);
                        }
                    }
                }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"AP",
 ".A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; verify_case(0, Arg2, getBoard(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"AP",
 ".A"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 2; verify_case(1, Arg2, getBoard(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"PPP",
 "APA",
 "A.P"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; verify_case(2, Arg2, getBoard(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"AAA",
 "PPP",
 "AAA"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 3; verify_case(3, Arg2, getBoard(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 0; verify_case(4, Arg2, getBoard(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"PPAAPA..AP",
 "PPA.APAP..",
 "..P.AA.PPP",
 "P.P..APAA.",
 "P.P..P.APA",
 "PPA..AP.AA",
 "APP..AAPAA",
 "P.P.AP...P",
 ".P.A.PAPPA",
 "..PAPAP..P"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 15; verify_case(5, Arg2, getBoard(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 UniformBoard ___test;
 ___test.run_test(-1);
}
// END CUT HERE
