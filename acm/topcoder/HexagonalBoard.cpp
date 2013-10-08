// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// The pony Applejack has an N by N hexagonal board. The following picture shows the hexagonal board when N = 1, 2, 3, and 4.





She wants to color some cells of the board. You are given a vector <string> board. If the j-th character of the i-th element of board is 'X', she wants to color the cell (i, j). If she colors two cells that share an edge, she must use different colors for those cells. Return the minimal number of colors she needs.

DEFINITION
Class:HexagonalBoard
Method:minColors
Parameters:vector <string>
Returns:int
Method signature:int minColors(vector <string> board)


CONSTRAINTS
-board will contain between 1 and 50 elements, inclusive.
-Each element of board will contain exactly N characters, where N is the number of elements in board.
-Each character in board will be either 'X' or '-'.


EXAMPLES

0)
{"---",
 "---",
 "---"}
 

Returns: 0

She won't color any cells, so she won't need any colors.

1)
{"-X--",
 "---X",
 "----",
 "-X--"}

Returns: 1

She can color all cells with the same color.

2)
{"XXXX",
 "---X",
 "---X",
 "---X"}

Returns: 2

For example, she can color cells in the following way:

Color cells (0, 0), (0, 2), (1, 3), and (3, 3) red.
Color cells (0, 1), (0, 3), and (2, 3) blue.



3)
{"XX-XX--"
,"-XX-XXX"
,"X-XX--X"
,"X--X-X-"
,"XX-X-XX"
,"-X-XX-X"
,"-XX-XX-"}

Returns: 3



*/
// END CUT HERE
#line 79 "HexagonalBoard.cpp"
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

const int MAX = 100;

int col[MAX][MAX];
int dir[][2] = {
    {-1, 0},
    {-1, 1},
    {0, 1},
    {1, 0},
    {1, -1},
    {0, -1},
};

class HexagonalBoard
{
public:
 int minColors(vector <string> board)
 {
 //$CARETPOSITION$
    int n = board.size();
    int ans = 0;
    memset(col, -1, sizeof(col));
    range(i, n) {
        range(j, n) {
            if (board[i][j] == 'X') {
                set<int> vis;
                range(d, 6) {
                    int i1 = i + dir[d][0];
                    int j1 = j + dir[d][1];
                    if (i1 < 0 || i1 > n-1 || j1 < 0 || j1 > n-1 || board[i1][j1] != 'X') continue;
                    if (col[i1][j1] == -1) continue;
                    vis.insert(col[i1][j1]);
                }
                int choose = 0;
                for (choose = 0; choose < ans; choose++) {
                    if (vis.find(choose) == vis.end()) {
                        break;
                    }
                }
                if (choose == ans) {
                    ans++;
                }
                col[i][j] = choose;
            }
        }
    }
    ans = min(ans, 3);
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"XXX",
 "XX-",
 "---"}
 ; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, minColors(Arg0)); }
	void test_case_1() { string Arr0[] = {"-X--",
 "---X",
 "----",
 "-X--"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(1, Arg1, minColors(Arg0)); }
	void test_case_2() { string Arr0[] = {"XXXX",
 "---X",
 "---X",
 "---X"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minColors(Arg0)); }
	void test_case_3() { string Arr0[] = {"XX-XX--"
,"-XX-XXX"
,"X-XX--X"
,"X--X-X-"
,"XX-X-XX"
,"-X-XX-X"
,"-XX-XX-"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minColors(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 HexagonalBoard ___test;
 ___test.run_test(-1);
}
// END CUT HERE
