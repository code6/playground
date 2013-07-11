// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Manao likes to play the Division Game with his friends. This two-player game is played with some collection of natural numbers S. Manao plays first and the players alternate in making a move. A move is choosing some number X from S and a natural number Y &gt 1 such that Y divides X. Then, X is replaced by X / Y in the collection. Note that at any moment the collection may contain multiple copies of the same number. The game proceeds until no more moves can be made. The player who managed to make the last move is declared the winner.

Since hot debates arise on what numbers should be in S, the friends decided to regularize their choice. They always choose a contiguous interval of numbers [A, B] to be the initial collection S. That is, at the beginning of the game, the collection S contains each of the integers A through B, inclusive, exactly once. Manao knows that A and B will satisfy the condition L &le A &le B &le R. You are given the ints L and R. Count the number of such intervals for which Manao will win the Division Game given that both players play optimally.

DEFINITION
Class:TheDivisionGame
Method:countWinningIntervals
Parameters:int, int
Returns:long long
Method signature:long long countWinningIntervals(int L, int R)


NOTES
-Only one number from the collection changes in each move. For example, if the collection contains three copies of the number 8, and the player chooses X=8 and Y=4, only one of the 8s in the collection will change to a 2.


CONSTRAINTS
-L will be between 2 and 1,000,000,000, inclusive.
-R will be between L and L + 1,000,000, inclusive.


EXAMPLES

0)
9
10

Returns: 2

If the chosen interval is [9,9] or [10,10], the collection S contains only one number. In these two situations Manao can win the game in a single move. On the other hand, if the chosen interval is [9,10], Manao will lose to an optimally playing opponent.


1)
2
5

Returns: 9

The only case where Manao loses is if the game starts with the interval [2,3]. Note that if the starting interval is [2,5], Manao can choose X=4 and Y=2 in his first move. After that move, the collection will contain the values 2, 2, 3, and 5.

2)
2
6

Returns: 13

Manao will also lose the game if the starting interval is [3,6].

3)
2
100

Returns: 4345



4)
12566125
12567777

Returns: 1313432



*/
// END CUT HERE
#line 71 "TheDivisionGame.cpp"
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

vector<int> pr;

typedef long long ll;

void init()
{
    int i, j;
    pr.clear();
    for (i = 2; i <= 100000; i++) {
        for (j = 2; j <= i / j; j ++) {
            if (i % j == 0) {
                break;
            }
        }
        if (j > i / j) {
            pr.push_back(i);
        }
    }
    printf("sz = %ld\n", pr.size());
}

long long gcnt = 0;

int getcnt(int v) {
    int i, j;
    int ret = 0;
    for (j = 0; j < pr.size(); j++) {
        i = pr[j];
        gcnt += 1;
        
        if (i * i > v) {
            break;
        }

        if (v % i == 0) {
            while (v % i == 0) {
                v /= i;
                ret ++;
            }
        }
    }
    if (v > 1) {
        ret ++;
    }
    return ret;
}

class TheDivisionGame
{
public:
 long long countWinningIntervals(int L, int R)
 {
     init();
     gcnt = 0;
 //$CARETPOSITION$
    int n = R - L + 1;
    int i, j;
    vector<int> vs, rs;

    vs.resize(n);
    rs.resize(n);
    for (i = 0; i < n; i++) {
        rs[i] = i + L;
    }

    for (i = 0;  i < pr.size() && pr[i] <=  R / pr[i]; i++) {
        ll candi = pr[i];
        for (;  candi <= R; candi *= pr[i]) {
            ll sta = (L - 1) / candi * candi + candi;
            while (sta <= R) {
               // if (L == 9) {
               //     printf("pr = %d, candi = %lld, sta = %lld, vs[sta - L] = %d, rs[sta - L] = %d\n", pr[i], candi, sta, vs[sta - L], rs[sta - L]);
               // }
                vs[sta - L] += 1;
                rs[sta - L] /= pr[i];
                sta += candi;
            }
        }
    }

    for (i = 0; i < vs.size(); i++) {
       // if (L == 9) {
       //     printf("i = %d, rs[i] = %d, vs[i] = %d\n", i, rs[i], vs[i]);
       // }
        if (rs[i] > 1) {
            vs[i] += 1;
        }
        if (i > 0) {
            vs[i] ^= vs[i - 1];
        }
    }

    vs.push_back(0);
    
    /*
     * TLE version:
    vs.push_back(0);
    for (i = 0; i < n; i++) {
        vs.push_back(vs.back() ^ getcnt(L + i));
    }
    */

    printf("n = %d, gcnt = %lld\n", n, gcnt);
    long long add = 0;
    sort(vs.begin(), vs.end());
    for (i = 0; i < vs.size(); i = j) {
        for (j = i + 1; j < vs.size() && vs[j] == vs[i]; j++);
        long long sz = j - i;
        add += sz * (sz - 1) / 2;
    }

    long long ret = (long long)n * (n - 1) / 2 + n ;
    printf("total = %lld, add = %lld\n",ret,  add);

    ret -= add;

    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 9; int Arg1 = 10; long long Arg2 = 2LL; verify_case(0, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 972332890 ; int Arg1 = 972991678; long long Arg2 = 210198241511LL; verify_case(1, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 2; int Arg1 = 6; long long Arg2 = 13LL; verify_case(2, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 100000000; int Arg1 = 100600000; long long Arg2 = 174366593967LL; verify_case(3, Arg2, countWinningIntervals(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 12566125; int Arg1 = 12567777; long long Arg2 = 1313432LL; verify_case(4, Arg2, countWinningIntervals(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 TheDivisionGame ___test;
 ___test.run_test(-1);
}
// END CUT HERE
