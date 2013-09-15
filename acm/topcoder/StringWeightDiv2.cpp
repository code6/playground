// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// In this problem, all strings consist of uppercase English letters only.
That is, there are 26 distinct letters.

The weight of a string S can be computed as follows: 
for each letter that occurs at least once in S, its leftmost and rightmost occurrences L and R are found and the weight is increased by R-L.

For example, if S="ABCACAZ", the weight of S is (5-0) + (1-1) + (4-2) + (6-6) = 7.
(The leftmost occurrence of 'A' is at the index L=0, the rightmost one is at R=5, so 'A' contributes 5-0 = 5 to the weight of S. The only 'B' contributes 0, the pair of 'C's adds 2, and the only 'Z' adds 0.)

You are given a int L.
Consider all strings of length L.
Compute the weight of each of these strings.
The strings with the minimum weight among all of them are called light.
Your task is to count the number of light strings of length L.
Since this count may be very large, return it modulo 1,000,000,009.

DEFINITION
Class:StringWeightDiv2
Method:countMinimums
Parameters:int
Returns:int
Method signature:int countMinimums(int L)


CONSTRAINTS
-L will be between 1 and 1000, inclusive.


EXAMPLES

0)
1

Returns: 26

Any string of length 1 has weight equal to 0.

1)
2

Returns: 650

We can divide strings of length 2 into two classes: the strings with distinct first and second letter, and the strings with two equal letters. The strings composed of two equal letters have weight 1. All the other strings have weight 0. Thus, the number of strings of minimum weight is 26*26-26=650.

2)
50

Returns: 488801539



*/
// END CUT HERE
#line 58 "StringWeightDiv2.cpp"
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
typedef long long ll;

const int MOD = 1000000000 + 9;
const int MAX = 1000 + 5;
int comb[MAX][MAX];

class StringWeightDiv2
{
public:
 int countMinimums(int L)
 {
 //$CARETPOSITION$
    int n = (L > 26) ? 26 : L;
    int perm = 1;
    range(i, n) {
        perm = (ll)perm * (i + 1) % MOD;
    }
    memset(comb, 0, sizeof(comb));
    range(i, max(L, 30)) {
        range(j, i + 1) {
            if (j == 0 || j == i) {
                comb[i][j] = 1;
            } else {
                comb[i][j] = ((ll)comb[i-1][j] + comb[i-1][j-1]) % MOD;
            }
        }
    }
    ll ans = (ll)comb[26][n] * comb[L - 1][ n - 1] % MOD * perm % MOD;
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 1; int Arg1 = 26; verify_case(0, Arg1, countMinimums(Arg0)); }
	void test_case_1() { int Arg0 = 2; int Arg1 = 650; verify_case(1, Arg1, countMinimums(Arg0)); }
	void test_case_2() { int Arg0 = 50; int Arg1 = 488801539; verify_case(2, Arg1, countMinimums(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 StringWeightDiv2 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
