// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Goose Tattarrattat has a string S of lowercase letters.
Tattarrattat wants to change her string into a palindrome: a string that reads the same forwards and backwards.
(For example, "racecar" is a palindrome.)

She will do this in a series of steps.
In each step, Tattarrattat will choose two letters of the alphabet: X and Y.
She will then change each X in her string into a Y.
Changing each single character takes 1 second.

For example, if S="goose" and Tattarrattat chooses X='o' and Y='e' in the next step, the step will take 2 seconds (because there are two 'o's in S) and after the step she would have S="geese".

You are given the string S.
Return the smallest number of seconds in which Tattarrattat can change S into a palindrome.

DEFINITION
Class:GooseTattarrattatDiv1
Method:getmin
Parameters:string
Returns:int
Method signature:int getmin(string S)


NOTES
-Tattarrattat must always change all occurrences of the chosen letter into the other one; she is not allowed to change only some of the occurrences.


CONSTRAINTS
-S will contain between 1 and 50 characters, inclusive.
-Each character in S will be a lowercase letter ('a'-'z').


EXAMPLES

0)
"geese"

Returns: 2

There are many ways how Tattarrattat can change this S into a palindrome.
For example, she could do it in two steps as follows:

Change all 'g's to 'e's: this takes 1 second and produces the string "eeese".
Change all 'e's to 's's: this takes 4 seconds and produces the string "sssss".

This way took her 1+4 = 5 seconds.
However, there are faster ways.
The best one only takes 2 seconds.
For example, she can first change all 'g's to 'e's (1 second), and then change all 's's to 'e's (1 second), obtaining the palindrome "eeeee".

1)
"tattarrattat"

Returns: 0

This string is already a palindrome so no changes are needed.

2)
"xyyzzzxxx"

Returns: 2



3)
"xrepayuyubctwtykrauccnquqfuqvccuaakylwlcjuyhyammag"

Returns: 11



4)
"abaabb"

Returns: 3



*/
// END CUT HERE
#line 84 "GooseTattarrattatDiv1.cpp"
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

int par[26];
int cnt[26];

int find(int a) {
    return par[a] == a ? a : par[a] = find(par[a]);
}

class GooseTattarrattatDiv1
{
public:
 int getmin(string S)
 {
 //$CARETPOSITION$
    int n = S.size();
    range(i, 26) par[i] = i, cnt[i] = 0;
    range(i, n) cnt[S[i] - 'a'] ++;
    range(i, n / 2) {
        int x, y;
        x = S[i] - 'a';
        y = S[n - 1 - i] - 'a';
        if (x != y) {
            int fx = find(x);
            int fy = find(y);
            if (fx != fy) {
                par[fx] = fy;
            }
        }
    }
    int ans = 0;
    range(i, 26) {
        if (par[i] == i) {
            int total, largest;
            total = largest = 0;
            range(j, 26) {
                if (find(j) == i) {
                    total += cnt[j];
                    largest = max(largest, cnt[j]);
                }
            }
            ans += total - largest;
        }
    }
    return ans;

    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "geese"; int Arg1 = 2; verify_case(0, Arg1, getmin(Arg0)); }
	void test_case_1() { string Arg0 = "tattarrattat"; int Arg1 = 0; verify_case(1, Arg1, getmin(Arg0)); }
	void test_case_2() { string Arg0 = "xyyzzzxxx"; int Arg1 = 2; verify_case(2, Arg1, getmin(Arg0)); }
	void test_case_3() { string Arg0 = "xrepayuyubctwtykrauccnquqfuqvccuaakylwlcjuyhyammag"; int Arg1 = 11; verify_case(3, Arg1, getmin(Arg0)); }
	void test_case_4() { string Arg0 = "aaabbbcxyyopqrorrqoxyxcbaaddd"; int Arg1 = 13; verify_case(4, Arg1, getmin(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 GooseTattarrattatDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
