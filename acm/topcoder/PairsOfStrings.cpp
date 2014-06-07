// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// We are interested in pairs of strings (A, B) that satisfy the following conditions: 

A and B consist of exactly n characters each. 
Each character in A and B is one of the first k lowercase letters of the English alphabet. 
There exists a string C such that A + C = C + B. Here, + denotes string concatenation. 

For example, if n = 3 and k = 4 then one valid pair of strings is ("aad", "daa"): 
both strings have length 3, only the first 4 letters are used in each of them, and C = "aa" shows that the third condition is satisfied as well. 

You are given the ints n and k. 
Find the number of such pairs of strings, and return the number modulo 1,000,000,007. 


DEFINITION
Class:PairsOfStrings
Method:getNumber
Parameters:int, int
Returns:int
Method signature:int getNumber(int n, int k)


CONSTRAINTS
-n will be between 1 and 1,000,000,000, inclusive. 
-k will be between 1 and 26, inclusive. 


EXAMPLES

0)
2
2

Returns: 6

The following 6 pairs satisfy the conditions: 
("aa", "aa"), ("ab", "ab"), ("ab", "ba"), ("ba", "ab"), ("ba", "ba"), ("bb", "bb"). 

1)
3
2

Returns: 20



2)
3
4

Returns: 184



3)
6
2

Returns: 348



4)
100
26

Returns: 46519912



*/
// END CUT HERE
#line 76 "PairsOfStrings.cpp"
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

const ll MOD=1000000000 + 7;

map<int, int> square_free;
set<int> memo;

void get_factor(int n) {
    int m = n;
    for (int i = 2; i <= n; i++) {
        if (i > m) break;
        if (i * i > n) break;
        if (m % i == 0) {
            while (m % i == 0) m /= i;
            if (n / i > 1) 
                gen_square_free(n / i);
            if ((n / i) % i != 0) {
                if (n / i > 1) {
                    if (square_free.find(n / i) != square_free.end()) {
                        square_free[n] = square_free[n / i] * -1;
                    }
                } else {
                    square_free[n] = -1;
                }
            } 
        }
    }
    if (m > 1) {
        square_free[n] = -1;
    }
}

ll pmd(int a, int b, int c) {
    ll ret = 1;
    while (b) {
        if (b&1) {
            ret = (ret * a) % c;
        }
        b >>= 1;
        a = ((ll)a * a) % c;
    }
    return ret;
}

map<int, ll> M;

ll Q(int n, int k) {
    if (M.find(n) != M.end()) {
        return M[n];
    }
    ll tot = pmd(k, n, MOD);
    for (map<int, int>::iterator it= square_free.begin(); it != square_free.end(); it++) {
        int num = it->fs;
        int op = it->sc;
        if (num > n) break;
        if (n % num == 0) {
            ll tmp = pmd(k, n / num, MOD);
            tot = (tot + tmp * op + MOD) % MOD;
        }
    }
    return M[n] = tot;
}

class PairsOfStrings
{
public:
 int getNumber(int n, int k)
 {
     ll ret = 0;
     square_free.clear();
     memo.clear();
     gen_square_free(n);
     M.clear();
     range(i, n + 1) {
         if (i == 0) continue;
         if (n % i == 0) {
             int x = i;
             int y = n / i;
             if (x > y) break;
             ret = (ret + (ll)Q(x, k) * x % MOD) % MOD;
             if (x != y) 
                 ret = (ret + (ll)Q(y, k) * y % MOD) % MOD;
         }
     }
     return ret ;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 10; int Arg1 = 6; int Arg2 = 604622616; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 3; int Arg1 = 2; int Arg2 = 20; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 3; int Arg1 = 4; int Arg2 = 184; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 6; int Arg1 = 2; int Arg2 = 348; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { int Arg0 = 100; int Arg1 = 26; int Arg2 = 46519912; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PairsOfStrings ___test;
 ___test.run_test(-1);
}
// END CUT HERE
