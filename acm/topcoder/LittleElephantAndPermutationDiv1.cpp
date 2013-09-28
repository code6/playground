// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
This problem statement contains superscripts and/or subscripts. These may not display properly outside the applet.




Little Elephant from the Zoo of Lviv likes permutations.
A permutation of size N is a sequence (a1, ..., aN) that contains each of the numbers from 1 to N exactly once.
For example, (3,1,4,5,2) is a permutation of size 5.




Given two permutations A = (a1, ..., aN) and B = (b1, ..., bN), the value magic(A,B) is defined as follows:
magic(A,B) = max(a1,b1) + max(a2,b2) + ... + max(aN,bN).




You are given the int N.
You are also given another int K.
Return the number of pairs (A,B) such that both A and B are permutations of size N, and magic(A,B) is greater than or equal to K.
(Note that A and B are not required to be distinct.)


DEFINITION
Class:LittleElephantAndPermutationDiv1
Method:getNumber
Parameters:int, int
Returns:int
Method signature:int getNumber(int N, int K)


CONSTRAINTS
-N will be between 1 and 50, inclusive.
-K will be between 1 and 2500, inclusive.


EXAMPLES

0)
1
1

Returns: 1

For N=1 the only pair of permutations is ( (1), (1) ).
The magic of this pair of permutations is 1, so we count it.

1)
2
1

Returns: 4

Now there are four possible pairs of permutations. They are shown below, along with their magic value.

magic( (1,2), (1,2) ) = 1+2 = 3
magic( (1,2), (2,1) ) = 2+2 = 4
magic( (2,1), (1,2) ) = 2+2 = 4
magic( (2,1), (2,1) ) = 2+1 = 3

In all four cases the magic value is greater than or equal to K.

2)
3
8

Returns: 18



3)
10
74

Returns: 484682624



4)
50
1000

Returns: 539792695



*/
// END CUT HERE
#line 95 "LittleElephantAndPermutationDiv1.cpp"
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

const int MOD = 1000000000 + 7;

int dp[55][55][2505];
void update(int &ret, int val) {
    ret = (ret + val) % MOD;
}

class LittleElephantAndPermutationDiv1
{
public:
 int getNumber(int N, int K)
 {
     memset(dp, 0, sizeof(dp));
     dp[0][0][0] = 1;
     range(i, N) {
         range(j, i + 1) {
             range(k, i * i + 1) {
                 if (!dp[i][j][k]) {
                     continue;
                 }
          //       if (N == 2) cout << i << ' ' << j << ' ' << k << ' ' << dp[i][j][k] << endl;
                 //i + 1 use at i + 1
                 update(dp[i+1][j][k+(i+1)], dp[i][j][k]);
                 //i + 1 use at lower
                 update(dp[i+1][j][k+(i+1)], (long long)dp[i][j][k] * j % MOD);

                 //i + 1 use at lower and put one of [1 .. j]  at i + 1
                 if (j)
                     update(dp[i+1][j - 1][k+(i+1) * 2], (long long)dp[i][j][k] * j * j % MOD);

                 //i + 1 not use
                 update(dp[i+1][j + 1][k], dp[i][j][k]);

                 //i + 1 not use, put one of [1 .. j] 
                 update(dp[i+1][j][k+(i+1)], (long long)dp[i][j][k] * j % MOD);
             }
         }
     }
     int ans = 0;
     range(i, N * N + 5) {
         //if (N == 2 && dp[N][0][i]) cout << N << ' ' << 0 << ' ' << i << ' ' << dp[N][0][i] << endl;
         if (i >= K)
             update(ans, dp[N][0][i]);
     }

     range(i, N) ans = (long long)ans * (i + 1) % MOD;

     return ans;
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 1; int Arg2 = 1; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 1; int Arg2 = 4; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 8; int Arg2 = 18; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 10; int Arg1 = 74; int Arg2 = 484682624; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 50; int Arg1 = 1000; int Arg2 = 539792695; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 LittleElephantAndPermutationDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
