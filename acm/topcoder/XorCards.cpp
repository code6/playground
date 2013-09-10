// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You have a set of cards.
There is one non-negative integer on each card.
Different cards may contain the same integer.
For each i, the number written on the i-th card (0-based index) is number[i].
Your friend wants to select a subset of those cards such that the bitwise xor of the selected cards is less than or equal to limit.



You are given the vector<long long> number and the long long limit.
Count the number of ways in which your friend can select the subset of cards.
Two subsets count as different if they differ as sets of cards (even if the corresponding sets of numbers are the same, see Example 4).

DEFINITION
Class:XorCards
Method:numberOfWays
Parameters:vector<long long>, long long
Returns:long long
Method signature:long long numberOfWays(vector<long long> number, long long limit)


NOTES
-XOR (exclusive or) is a binary operation, performed on two numbers in binary notation. First, the shorter number is prepended with leading zeroes until both numbers have the same number of digits (in binary). Then, the result is calculated as follows: for each bit where the numbers differ the result has 1 in its binary representation. It has 0 in all other positions.
-For example 42 XOR 7 is performed as follows. First, the numbers are converted to binary: 42 is 101010 and 7 is 111. Then the shorter number is prepended with leading zeros until both numbers have the same number of digits. This means 7 becomes 000111. Then 101010 XOR 000111 = 101101 (the result has ones only in the positions where the two numbers differ). Then the result can be converted back to decimal notation. In this case 101101 = 45, so 42 XOR 7 = 45.
-If your friend decides to select zero cards, the bitwise xor of numbers on selected cards is zero.
-If your friend decides to select a single card, the bitwise xor of numbers on selected cards is the number on the selected card.


CONSTRAINTS
-number will contain between 1 and 50 elements, inclusive.
-Each element in number will be between 0 and 1,000,000,000,000,000 (10^15), inclusive.
-limit will be between 0 and 1,000,000,000,000,000 (10^15), inclusive.


EXAMPLES

0)
{1,2}
2

Returns: 3

This set of cards has four possible subsets.
Here they are, along with the corresponding bitwise xors:
{} => 0, {1} => 1, {2} => 2, and {1,2} => 3.
Note that limit=2.
Out of these four subsets, for the first three the bitwise xor of selected numbers is at most equal to limit.

1)
{5,5}
3

Returns: 2

The two good subsets are {} and {5,5}.

2)
{1,2,3,4,5,6,7}
5

Returns: 96



3)
{123, 456, 789, 147, 258, 369, 159, 357}
500

Returns: 125



4)
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
1000000000000000

Returns: 4294967296



5)
{1000000000000000, 999999999999999}
65535

Returns: 2



*/
// END CUT HERE
#line 94 "XorCards.cpp"
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

typedef vector<int> VI;
typedef pair<int, int> PII;

typedef long long ll;

bool show = false;

ll gauss(vector<vector<int> > a, vector<int> b) {
    int i, j, row = 0, col;
    int m = a[0].size();
    int n = a.size();
    for (col = 0; col < m; col++) {
        for (i = row; i < n; i++) {
            if (a[i][col]) break;
        }
        if (i >= n) continue;
        if (i != row) {
            for (j = col; j < m; j++) 
                swap(a[row][j], a[i][j]);
            swap(b[i], b[row]);
        }
        for (i = row + 1; i < n; i++) {
            if (a[i][col]) {
                for (j = col; j < m; j++) {
                    a[i][j] ^= a[row][j];
                }
                b[i] ^= b[row];
            }
        }
        row ++;
    }
    for (i = row; i < n; i++) if (b[i]) return 0;
    return two(m - row);
}

ll gauss_bad(vector<vector<int> > a, vector<int> b) {
    int n = a.size();
    int m = a[0].size();
    range(i, n) {
        a[i].pb(b[i]);
    }

    int row = 0;
    range(col, m) {
        range(j, n) {
            if (j < row) continue;
            if (a[j][col] == 1) {
                if (j != row) {
                    range(k, m + 1)  {
                        if (k < col) continue;
                        swap(a[j][k], a[row][k]);
                    }
                }
                break;
            }
        }
        if (!a[row][col]) {
            continue;
        }
        range(j, n) {
            if (j <= row)  continue;
            if (a[j][col]) {
                range(k, m + 1) {
                    a[j][k] ^= a[row][k];
                }
            }
        }
        row++;
    }

    range(i, n) {
        if (i >= row && a[i][m]) return 0;
    }

    return two(m - row);
}

ll generate(vector<ll>  a, ll target) {
    vector<vector<int> > coe;
    vector<int> b;


    ll t = target;
    range(i, 63) {
        b.pb(target & 1);
        target >>= 1;
    }

    range(j, 63) {
        vector<int> row;
        range(i, a.size()) {
            row.pb(a[i] & 1);
            a[i] >>= 1;
        }
        coe.pb(row);
    }

    ll res = gauss_bad(coe, b);

    if (show) {
        cout << t << ' ' << res << endl;
    }
    return res;
}

class XorCards
{
public:
 long long numberOfWays(vector<long long> number, long long limit)
 {
 //$CARETPOSITION$
    if (limit == 65535)  {
        show = true;
    } else {
        show = false;
    }
    ll ans = 0;
    ans += generate(number, limit);
    range(pos, 63) {
        if (limit & 1) {
            limit ^= 1;
            ans += generate(number, limit);
        }
        limit >>= 1;
        range(j, number.size()) {
            number[j] >>= 1;
        }
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {1,2}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 2LL; long long Arg2 = 3LL; verify_case(0, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {5,5}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 3LL; long long Arg2 = 2LL; verify_case(1, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_2() { long Arr0[] = {1,2,3,4,5,6,7}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 5LL; long long Arg2 = 96LL; verify_case(2, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {123, 456, 789, 147, 258, 369, 159, 357}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 500LL; long long Arg2 = 125LL; verify_case(3, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_4() { long Arr0[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 1000000000000000LL; long long Arg2 = 4294967296LL; verify_case(4, Arg2, numberOfWays(Arg0, Arg1)); }
	void test_case_5() { long Arr0[] = {1000000000000000, 999999999999999}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); long long Arg1 = 65535LL; long long Arg2 = 2LL; verify_case(5, Arg2, numberOfWays(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 XorCards ___test;
 ___test.run_test(-1);
}
// END CUT HERE
