// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
Monicka has an array of N cells, numbered 0 through N-1. She chooses one cell of the array uniformly at random and places a token into that cell.


Misko will then play a game with Monicka, trying to guess the location of the token. The gameplay is similar to binary searching for the token ? in each turn, Misko picks a cell of the array and receives one of three possible answers: "left" if the token is in a cell with a smaller number, "right" if it is in a cell with a larger number, or "correct" if the chosen cell contains the token. The game ends when Misko gets the answer "correct".


Misko is not allowed to ask useless questions. For example, if he already chose the cell 47 and received the answer "right", he is not allowed to choose any of the cells 3, 12, and 47: it is already known that these cells do not contain the token.


Monicka does not like games that are too short or too long. She is happy with a game that takes at least A, but at most B turns. Misko wants to make Monicka happy, therefore he aims to finish the game in such a number of turns.


You are given the ints N, A, and B.
Find the optimal strategy for Misko and return the probability that he will finish the game in at least A, but at most B turns.


DEFINITION
Class:WellTimedSearch
Method:getProbability
Parameters:int, int, int
Returns:double
Method signature:double getProbability(int N, int A, int B)


NOTES
-Return values with absolute or relative error at most 1e-9 will be accepted as correct.


CONSTRAINTS
-N will be between 1 and 1,000,000, inclusive.
-A will be between 1 and N, inclusive.
-B will be between A and N, inclusive.


EXAMPLES

0)
3
2
2

Returns: 0.6666666666666666

Monicka will be happy if Misko's second guess is correct. The best strategy for Misko is to choose the index 1 first. If he gets the answer "correct", he won the game too early. But if he gets the answer "left" or "right", he will win the game in the second turn. Thus the probability that Monicka will be happy when Misko uses this strategy is 2/3.

1)
3
3
3

Returns: 0.3333333333333333

This time Misko wants to postpone his correct guess until the third turn.

2)
123456
1
20

Returns: 1.0

Misko can use binary search to guarantee that he will be able to guess Monicka's number in well under 20 guesses.

3)
5
3
4

Returns: 0.6



*/
// END CUT HERE
#line 80 "WellTimedSearch.cpp"
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

int mask[23];
int n, a, b;
int minStep(int n) {
    int i;
    for (i = 0; mask[i] <= n; i++);
    return i;
}

bool legal(int at) {
    int total = n;
    int x = a, y = b;
    while (true) {
        if (total < x || y < minStep(total)) {
            return false;
        }
        int choose;
        if (minStep(total) < y) {
            choose = 1;
        } else {
            choose = total / 2;
        }
        if (n == 3)
        printf("at= %d, total = %d, min = %d y = %d choose=%d\n", at, total, minStep(total), y, choose);
        x --; y --;

        if (at == choose) {
            if (x > 0) {
                return false;
            }
            return true;
        } else {
            if (at < choose) {
                total = choose - 1;
            } else {
                total = total - choose;
                at -= choose;
            }
        }
    }
}

class WellTimedSearch
{
public:
 double getProbability(int N, int A, int B)
 {
 //$CARETPOSITION$
    int i, j;
    mask[0] = 1;
    for (i = 1; i < 23; i++) mask[i] = mask[i - 1] * 2;
    n = N;
    a = A;
    b = B;
    double ret = 0.0;
    for (i = 1; i <= n; i++) {
        if (legal(i)) {
            ret += 1.0 / n;
        }
    }
    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 2; double Arg3 = 0.6666666666666666; verify_case(0, Arg3, getProbability(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 3; double Arg3 = 0.3333333333333333; verify_case(1, Arg3, getProbability(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 123456; int Arg1 = 1; int Arg2 = 20; double Arg3 = 1.0; verify_case(2, Arg3, getProbability(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 5; int Arg1 = 3; int Arg2 = 4; double Arg3 = 0.6; verify_case(3, Arg3, getProbability(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 WellTimedSearch ___test;
 ___test.run_test(-1);
}
// END CUT HERE
