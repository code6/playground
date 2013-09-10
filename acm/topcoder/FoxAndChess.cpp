// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Fox Ciel is playing a game with some chess pawns and a strip of paper.
The strip of paper is divided into a row of cells.
Each cell can contain at most one pawn.
The white pawns will be denoted 'R', because they are only allowed to move to the right.
The black pawns will be denoted 'L', because they are only allowed to move to the left.


You are given a string begin that describes the current state of the strip: 'R' and 'L' are cells with corresponding pawns, and '.' are empty cells.


You are now allowed to make some moves (as many as you wish, possibly zero).
In each move you may either take a 'R' pawn and move it one cell to the right, or take a 'L' pawn and move it one cell to the left.
Of course, both types of moves are only valid if the destination cell is currently empty.
Pawns are not allowed to move out of bounds.


You are also given a string target that represents the desired state of the strip.
If it is possible to reach target from begin by making some valid moves, return "Possible" (quotes for clarity), otherwise return "Impossible".

DEFINITION
Class:FoxAndChess
Method:ableToMove
Parameters:string, string
Returns:string
Method signature:string ableToMove(string begin, string target)


CONSTRAINTS
-begin will contain between 1 and 50 elements, inclusive.
-begin and target will contain the same number of elements.
-Each character in begin and target will be one of '.', 'L' and 'R'.


EXAMPLES

0)
"R..."
"..R."

Returns: "Possible"

You have to move the only pawn to the right twice.

1)
"..R."
"R..."

Returns: "Impossible"

Here target cannot be reached because the only pawn is only allowed to move to the right.

2)
".L.R.R."
"L...R.R"

Returns: "Possible"



3)
".L.R."
".R.L."

Returns: "Impossible"



4)
"LRLLRLRLLRLLRLRLRL"
"LRLLRLRLLRLLRLRLRL"

Returns: "Possible"



5)
"L"
"."

Returns: "Impossible"



*/
// END CUT HERE
#line 90 "FoxAndChess.cpp"
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

bool legal_move(int val, int ty) {
    if (ty == 0) {
        return val <= 0;
    } else {
        return val >= 0;
    }
}

bool check_legal(const vector<PII>& a, const vector<PII> & b) {
    if (a.size() != b.size()) {
        return false;
    }

    int n = a.size();
    range(i, n) {
        if (a[i].fs != b[i].fs) {
            return false;
        }
    }
    int f, r;
    f = 0; r = n - 1;
    while (f <= r) {
        bool found = false;
        if (legal_move(b[f].sc - a[f].sc, a[f].fs)) {
            f++;
            found = true;
        }
        if (legal_move(b[r].sc - a[r].sc, a[r].fs)) {
            r--; 
            found = true;
        }
        if (!found) {
            break;
        }
    }
    if (f <= r) {
        return false;
    } else {
        return true;
    }
}

class FoxAndChess
{
public:
 string ableToMove(string begin, string target)
 {
 //$CARETPOSITION$
    int n =  begin.size();
    vector<PII> b_arr, e_arr;
    range(i, n) {
        if (begin[i] == 'L') {
            b_arr.pb(mp(0, i));
        }
        if (begin[i] == 'R') {
            b_arr.pb(mp(1, i));
        }
        if (target[i] == 'L') {
            e_arr.pb(mp(0, i));
        }
        if (target[i] == 'R') {
            e_arr.pb(mp(1, i));
        }
    }

    bool legal = check_legal(b_arr, e_arr);
    return legal ? "Possible": "Impossible";

 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "R..."; string Arg1 = "..R."; string Arg2 = "Possible"; verify_case(0, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "..R."; string Arg1 = "R..."; string Arg2 = "Impossible"; verify_case(1, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = ".L.R.R."; string Arg1 = "L...R.R"; string Arg2 = "Possible"; verify_case(2, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = ".L.R."; string Arg1 = ".R.L."; string Arg2 = "Impossible"; verify_case(3, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "LRLLRLRLLRLLRLRLRL"; string Arg1 = "LRLLRLRLLRLLRLRLRL"; string Arg2 = "Possible"; verify_case(4, Arg2, ableToMove(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "L"; string Arg1 = "."; string Arg2 = "Impossible"; verify_case(5, Arg2, ableToMove(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 FoxAndChess ___test;
 ___test.run_test(-1);
}
// END CUT HERE
