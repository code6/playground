// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Manao is playing a new board game. The game is played on an NxM board with each cell initially colored either black or white. The cell on the intersection of the i-th (0-based) row and j-th (0-based) column is referred to as (i, j).

Manao may perform two types of moves:

Pick a cell (i, j) (0 ? i < N, 0 ? j < M) and toggle the color of cells (i-1, j), (i+1, j), (i, j-1), (i, j+1). If some of these cells are outside the board, the move is considered valid, and the cells outside of the board are ignored.
Pick a cell (i, j) (0 ? i < N, 0 ? j < M) and toggle the color of cells (i, j), (i-1, j), (i+1, j), (i, j-1), (i, j+1). Again, the cells outside of the board, if any, are ignored.

We call the two move types "type 1 moves" and "type 2 moves". In both cases, we say that Manao performed the move on the cell (i, j).

Manao cannot perform the moves arbitrarily, he has to follow some additional constraints:
For each row, all moves applied to cells in the row have to be of the same type.
Also, for each column, all moves applied to cells in the column have to be of the same type.
In particular, Manao is not allowed to perform a type 1 move on a cell and then a type 2 move on the same cell (nor vice versa).

You are given a vector <string> board consisting of N elements, each M characters long. The j-th character in the i-th row (0-based indices) of board is 'W' if cell (i, j) is initially white, and 'B' otherwise. Manao wants to turn the board all black. Determine the minimum number of moves he needs to perform to accomplish this task. If it is impossible to turn every cell on the board black, return -1.

DEFINITION
Class:YetAnotherBoardGame
Method:minimumMoves
Parameters:vector <string>
Returns:int
Method signature:int minimumMoves(vector <string> board)


CONSTRAINTS
-board will contain between 1 and 13 elements, inclusive.
-Each element of board will be between 1 and 13 characters long, inclusive.
-The elements of board will be of the same length.
-Each element of board will consist of 'W' and 'B' characters only.


EXAMPLES

0)
{"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"}

Returns: 2

A type 1 move on (4, 6) and a type 2 move on (2, 2) turn the whole board black.

1)
{"BBW",
 "WWW",
 "BWW"}

Returns: 2

Manao can perform a move of type 2 on cell (1, 2) and a move of type 1 on cell (2, 0).

2)
{"WBW",
 "BBW",
 "WBW"}

Returns: 4

If no additional constraints were imposed, Manao would perform a type 1 move on (1, 0) and a type 2 move on (1, 2). However, these cells are in the same row and thus these moves are incompatible. Instead, Manao can perform four type 2 moves on cells (1, 0), (1, 1), (0, 2) and (2, 2).

3)
{"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"}

Returns: -1

There is no way to turn this board black.

4)
{"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"}

Returns: 7



5)
{"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}


Returns: 30



*/
// END CUT HERE
#line 106 "YetAnotherBoardGame.cpp"
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

const int MAX = 100 + 50;

int n, m;
int bo[MAX][MAX];
int mask3[15];

struct Node {
    int x, y, last, rowtype, coltype;
    Node(int _x, int _y, int _last, int _rowtype, int _coltype) {
        x = _x;
        y = _y;
        last = _last;
        rowtype = _rowtype;
        coltype = _coltype;
    }
};

map<Node, int> dp;

void update(int & ret, int tmp) {
    if (tmp == -1) return;
    if (ret == -1) ret = tmp;
    ret = min(ret, tmp);
}

int memo(int x, int y, int last, int rowtype, int coltype) {
    int i, j;
    if (x == n) {
        if (last == 0) {
            return 0;
        } else {
            return -1;
        }
    }

    if (y == m) {
        //forward to next row
        int new_last = 0;
        for (i = 0; i < m; i++) {
            if (bo[x][i]) {
                new_last += two(i);
            }
        }
        return memo(x + 1, 0, new_last, rowtype, coltype);
    }

    Node cur = Node(x, y, last, rowtype, coltype);
    if (dp.find(cur) != dp.end()) {
        return dp[cur];
    }
    int & ret = dp[cur];
    ret = -1;
    //no put
    int tmp;
    tmp = memo(x, y + 1, last, rowtype, coltype);
    update(ret, tmp);
    ctype = get_ctype(coltype);
    rtype = get_rtype(rowtype);

    //put type 1
    if (!(ctype == 2 || rtype == 2)) {
    
    }

    //put type 2
    if (!(ctype == 1 || rtype == 1)) {
    }

    return ret;
}

class YetAnotherBoardGame
{
public:
 int minimumMoves(vector <string> board)
 {
 //$CARETPOSITION$
    int i, j;

    mask3[0] = 1;
    for (i = 1; i < 15; i++) mask3[i] = mask3[i - 1] * 3;

    n = board.size();
    m = board[0].size();
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            bo[i][j] = board[i][j] == 'W';
        }
    }
    int ans = memo(0, 0, 0, 0, 0);
    return ans;

 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"BBBBBBBBB",
 "BBWBBBBBB",
 "BWWWBBBBB",
 "BBWBBBWBB",
 "BBBBBWBWB",
 "BBBBBBWBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(0, Arg1, minimumMoves(Arg0)); }
	void test_case_1() { string Arr0[] = {"BBW",
 "WWW",
 "BWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(1, Arg1, minimumMoves(Arg0)); }
	void test_case_2() { string Arr0[] = {"WBW",
 "BBW",
 "WBW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; verify_case(2, Arg1, minimumMoves(Arg0)); }
	void test_case_3() { string Arr0[] = {"BBBB",
 "WBWB",
 "BBBB",
 "BBBB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(3, Arg1, minimumMoves(Arg0)); }
	void test_case_4() { string Arr0[] = {"WWWWWBW",
 "WBWBWBW",
 "BBWBBWW"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(4, Arg1, minimumMoves(Arg0)); }
	void test_case_5() { string Arr0[] = {"WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW",
 "WWWWWWWWWW"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 30; verify_case(5, Arg1, minimumMoves(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 YetAnotherBoardGame ___test;
 ___test.run_test(-1);
}
// END CUT HERE
