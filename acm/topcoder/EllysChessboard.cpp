// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Elly has a standard chessboard, divided into 8 by 8 unit square cells.
She wants to place pebbles onto some of the cells.
You are given a vector <string> board.
The j-th character of the i-th element of board is '#' if she wants to put a pebble onto the cell (i, j), and it is '.' otherwise.

Initially the chessboard doesn't contain any pebbles.
Elly places the pebbles one by one.
The cost of adding a pebble is defined as follows.
If this is the first pebble to be placed (i.e., the board is empty), it can be placed for free.
Otherwise, the cost is the Manhattan distance (see Notes for the definition) to the most distant pebble that has already been placed on the board.

Return the minimal total cost of placing a pebble onto each chosen cell.

DEFINITION
Class:EllysChessboard
Method:minCost
Parameters:vector <string>
Returns:int
Method signature:int minCost(vector <string> board)


NOTES
-The Manhattan distance between the cell (x1, y1) and the cell (x2, y2) is defined as |x1-x2| + |y1-y2|, where || denotes absolute value.


CONSTRAINTS
-board will contain exactly 8 elements.
-Each element of board will contain exactly 8 characters.
-Each character in board will be either '#' or '.'.


EXAMPLES

0)
{"........",
 "........",
 "...#....",
 ".#......",
 ".......#",
 "........",
 "........",
 "........"}

Returns: 10

Elly wants to put pebbles on three cells: (2, 3), (3, 1), and (4, 7). One of the optimal ways to do this is as follows:

First, put a pebble to (2, 3). It costs nothing.
Next, put a pebble to (3, 1). It costs |2-3| + |3-1| = 3.
Next, put a pebble to (4, 7). The Manhattan distance between (4, 7) and (2, 3) is 6, and the Manhattan distance between (4, 7) and (3, 1) is 7, so the cost is max(6, 7) = 7.

The total cost is 0 + 3 + 7 = 10.

1)
{"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}

Returns: 0



2)
{".#......",
 "........",
 "..#..#.#",
 "...#..#.",
 "........",
 "...#...#",
 "...#...#",
 "........"}

Returns: 58



3)
{"##..####",
 "#####..#",
 "..#.#...",
 "#..##.##",
 ".#.###.#",
 "####.###",
 "#.#...#.",
 "##....#."}

Returns: 275



4)
{"########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########"}

Returns: 476



*/
// END CUT HERE
#line 116 "EllysChessboard.cpp"
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

const int MAX = 100;
typedef pair<int, int> PII;
const int INF = 10000000;

int dis[MAX][MAX];
int N;
int best;

typedef unsigned long long U;
#define two(i) (((U)1)<(i))
U mask[100];

int find_min(int at, U state) {
    int cost = 0;
    int j;
    for (j = 0; j < N; j++) {
        if ((mask[j] & state) > 0) {
            int tmp = dis[at][j];
            if (cost == 0) {
                cost = tmp;
            } else {
                cost = max(cost, tmp);
            }
        }
    }
    return cost;
}

void search(int dep, int curcost, U state) {
    if (dep == N) {
        cout<<dep<<' '<<curcost<<' '<<state<<' '<<best<<endl;
        if (best > curcost) {
            best = curcost;
        }
    }
    int i, j;
    int limit = curcost;
    for (i = 0; i < N; i++) {
        if (!(mask[i] & state)) {
            limit += find_min(i, state);
        }
    }
    if (limit >= best) {
        return;
    }

    for (i = 0; i < N; i++) {
        if (!(mask[i] & state)) {
            search(dep + 1, curcost + find_min(i, state), state | mask[i]);
        }
    }
}

class EllysChessboard
{
public:
 int minCost(vector <string> board)
 {
 //$CARETPOSITION$
    int i, j;
    vector<PII> vp;
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 8; j++) {
            if (board[i][j] == '#') {
                vp.push_back(mp(i, j));
            }
        }
    }
    N = vp.size();
    mask[0] = 1;
    for (i = 1; i < N; i++) mask[i] = mask[i - 1] * 2;
    if (N <= 1) {
        return 0;
    }
    memset(dis, 0, sizeof(dis));
    for (i = 0; i < N; i++) {
        for (j = i + 1; j < N; j++) {
            dis[i][j] = dis[j][i] = abs(vp[i].first - vp[j].first) + abs(vp[i].second - vp[j].second);
        }
    }
    best = 1000000000;
    search(0, 0, 0);
    return best;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"........",
 "........",
 "...#....",
 ".#......",
 ".......#",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(0, Arg1, minCost(Arg0)); }
	void test_case_1() { string Arr0[] = {"........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(1, Arg1, minCost(Arg0)); }
	void test_case_2() { string Arr0[] = {".#......",
 "........",
 "..#..#.#",
 "...#..#.",
 "........",
 "...#...#",
 "...#...#",
 "........"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 58; verify_case(2, Arg1, minCost(Arg0)); }
	void test_case_3() { string Arr0[] = {"##..####",
 "#####..#",
 "..#.#...",
 "#..##.##",
 ".#.###.#",
 "####.###",
 "#.#...#.",
 "##....#."}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 275; verify_case(3, Arg1, minCost(Arg0)); }
	void test_case_4() { string Arr0[] = {"########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########",
 "########"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 476; verify_case(4, Arg1, minCost(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 EllysChessboard ___test;
 ___test.run_test(-1);
}
// END CUT HERE
