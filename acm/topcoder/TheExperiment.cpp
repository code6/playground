// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Manao is conducting an experiment to measure the humidity level of some spongy material. The experiment is conducted in a closed room which is observed from a side, so we will consider it in two dimensions.

The room is N centimeters wide. There are N drop counters built in the ceiling of the room. Drop counter 0 is attached 0.5 centimeters from the left end of the room, and each next one is attached 1 centimeter to the right of the previous one. You are given a vector <string> intensity filled with digits. Concatenate its elements to obtain one string S of length N. The i-th (0-based index) drop counter drips exactly S[i] drops per minute, where S[i] is the digit at the i-th position in S.

Manao is going to place M sponges in the room. All sponges are exactly L centimeters long and their thickness is negligible.
Each sponge must be placed horizontally, it must be entirely within the room, and the distance between the left wall of the room and the sponge must be an integer.
In other words, the coordinate of its left end must be an integer between 0 and N-L, inclusive.
Different sponges must be attached at different heights.
Each sponge will totally absorb every drop that drips at it.
For example, in the following picture, the sponges (from top to bottom) absorb 12, 5, and 3 drops per minute.



The experiment requires the sponges to be attached in such a way that each of them absorbs between A and B drops per minute, inclusive.
Manao is interested in the number of ways in which this can be done.
Two ways P and Q of attaching the sponges are the same if and only if for each sponge S1 in P there exists a sponge S2 in Q such that S1 and S2 lie directly beneath the same sets of drop counters.
A sponge X lies directly beneath a drop counter Y if there is no other sponge between them.
That is, if there is some water dripping from the drop counter Y, it all lands on the sponge X.
Note that according to these definitions the sponges are indistinguishable.

You are given the vector <string> intensity and the ints M, L, A, and B.
Count the number of different ways to attach the sponges and return that count modulo 1,000,000,009.

DEFINITION
Class:TheExperiment
Method:countPlacements
Parameters:vector <string>, int, int, int, int
Returns:int
Method signature:int countPlacements(vector <string> intensity, int M, int L, int A, int B)


CONSTRAINTS
-intensity will contain between 1 and 6 elements, inclusive.
-Each element of intensity will be between 1 and 50 characters long, inclusive.
-Each element of intensity will consist of digits ('0'-'9') only.
-M will be between 1 and 300, inclusive.
-L will be between 1 and N, inclusive, where N is the total number of characters in intensity.
-A will be between 1 and 2700, inclusive.
-B will be between A and 2700, inclusive.


EXAMPLES

0)
{"341156"}
3
3
6
10

Returns: 2

Manao needs to place three sponges of length 3 in such a way that they absorb between 6 and 10 drops per minute. The valid ways to attach the sponges are the following:


In the first way, the sponges receive 8, 6 and 6 drops, from highest to lowest. In the second way, they absorb 7, 7 and 6. Note that Manao could interchange the heights of the lower two sponges in the second picture, but this would result in the same way.

1)
{"999112999"}
2
4
21
30

Returns: 2

One of the platforms should have its left end exactly at the left wall. The other's left end can be either 4 or 5 centimeters away from the left wall.

2)
{"111"}
2
2
2
3

Returns: 0

One of the platforms will never receive enough drops.

3)
{"59059", "110", "1132230231"}
1
5
10
20

Returns: 6



4)
{"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"}
12
8
4
2700

Returns: 418629948



*/
// END CUT HERE
#line 108 "TheExperiment.cpp"
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

const int MAX = 300 + 50;
const int MOD = 1000000009;


int score[MAX];
//dp[next_pos][used_sponge][move_left][move_right]
int dp[MAX][MAX][2][2];
int n;
int m, l, a, b;

int doit(int next_pos, int used_sponge, int move_left, int move_right) {
    if (used_sponge == m && move_right) {
        return 1;
    }

    if (next_pos >= n) {
        return 0;
    }

    if (dp[next_pos][used_sponge][move_left][move_right] != -1) {
        return dp[next_pos][used_sponge][move_left][move_right];
    }
    int ret = 0;

    int i;
    int absorb;
    if (move_right) {
        ret = (ret + doit(next_pos + 1, used_sponge, 0, move_right)) % MOD;
    }

    if (move_left) {
        absorb = 0;
        for (i = 0; i < l; i++) {
            absorb += score[next_pos + i];
            if (next_pos + i < n && a <= absorb && absorb <= b) {
                ret = (ret + doit(next_pos + i + 1, used_sponge + 1, 1, 1)) % MOD;
            }
        }
    } else {
        absorb = 0;
        for (i = 0; i < l; i++) {
            absorb += score[next_pos + i];
            if (next_pos + i < n && a <= absorb && absorb <= b) {
                ret = (ret + doit(next_pos + i + 1, used_sponge + 1, (i == l - 1), (i == l - 1) )) % MOD;
            }
        }
    }
    
    //printf("next_pos = %d, used_sponge =%d, move_left = %d, move_right = %d, ret = %d \n", next_pos, used_sponge, move_left, move_right, ret);

    return dp[next_pos][used_sponge][move_left][move_right] = ret;
}


class TheExperiment
{
public:
 int countPlacements(vector <string> intensity, int M, int L, int A, int B)
 {
 //$CARETPOSITION$
    n = 0;
    m = M;
    l = L;
    a = A;
    b = B;
    int i, j;
    for (i = 0; i < intensity.size(); i++) {
        for (j = 0; j < intensity[i].size(); j++) {
            score[n++] = intensity[i][j] - '0';
        }
    }
    memset(dp, -1, sizeof(dp));
    int ret = doit(0, 0, 0, 1);
    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"341156"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; int Arg3 = 6; int Arg4 = 10; int Arg5 = 2; verify_case(0, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { string Arr0[] = {"999112999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 4; int Arg3 = 21; int Arg4 = 30; int Arg5 = 2; verify_case(1, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { string Arr0[] = {"111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 2; int Arg3 = 2; int Arg4 = 3; int Arg5 = 0; verify_case(2, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { string Arr0[] = {"59059", "110", "1132230231"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 5; int Arg3 = 10; int Arg4 = 20; int Arg5 = 6; verify_case(3, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_4() { string Arr0[] = {"111111111111111111111111", "111111111111111111111111111", "11111111111111111111111"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 12; int Arg2 = 8; int Arg3 = 4; int Arg4 = 2700; int Arg5 = 418629948; verify_case(4, Arg5, countPlacements(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 TheExperiment ___test;
 ___test.run_test(-1);
}
// END CUT HERE
