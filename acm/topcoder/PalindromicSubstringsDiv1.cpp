// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Marco likes strings.
In particular, he likes strings that have a lot of palindromic substrings.
For example, he really likes the string "aaa" because it has 6 palindromic substrings: "a" occurs three times, "aa" occurs twice, and "aaa" occurs once.

Right now, Marco has a string S composed of lowercase letters and question marks.
You are to reconstruct S from the given vector <string>s S1 and S2 as follows:

Concatenate all elements of S1 to make a string A.
Concatenate all elements of S2 to make a string B.
Finally, concatenate A and B to get S.



Marco is going to replace every question mark in S with a random lowercase letter ('a' - 'z').
Return the expected number of palindromic substrings in the resulting string.

DEFINITION
Class:PalindromicSubstringsDiv1
Method:expectedPalindromes
Parameters:vector <string>, vector <string>
Returns:double
Method signature:double expectedPalindromes(vector <string> S1, vector <string> S2)


NOTES
-For each question mark, the letter used to replace it is chosen uniformly at random. That is, the probability of choosing any particular letter is 1/26. All random choices are mutually independent.
-A palindromic string is a string that reads the same forwards and backwards.
-Your return value must have an absolute or a relative error of less than 1e-9.


CONSTRAINTS
-S1 and S2 will contain no more than 50 elements.
-Each element of S1 and S2 will contain no more than 50 characters.
-S will contain at least 1 character.
-S will contain only lowercase letters ('a' - 'z') and question marks ('?').


EXAMPLES

0)
{"a","a",""}
{"a"}

Returns: 6.0

This is the example given in the statement.

1)
{"z??"}
{}

Returns: 3.115384615384615

There are 26^2 = 676 equally likely possibilities for the letters used to replace the question marks.
Here are all possible outcomes:

The string "zzz" has 6 palindromic substrings.
Each of the 25 strings "zaz", "zbz", ..., "zyz" has 4 palindromic substrings.
Each of the 25 strings "zza", "zzb", ..., "zzy" has 4 palindromic substrings.
Each of the 25 strings "zaa", "zbb", ..., "zyy" has 4 palindromic substrings.
Each of the remaining 600 possible strings only has the 3 single-letter palindromic substrings.

The expected number of palindromic substrings can be computed simply as the average over all 676 possible cases.
Hence, the correct return value is (6 + 75*4 + 600*3) / 676.

2)
{"ab","c"}
{"??","a?"}

Returns: 7.315088757396449



3)
{}
{"?"}

Returns: 1.0



4)
{"ab?def","?"}
{"f??a"}

Returns: 12.545971779699588



*/
// END CUT HERE
#line 96 "PalindromicSubstringsDiv1.cpp"
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

bool match(char c1, char c2) {
    if (c1 == '?' || c2 == '?') return true;
    return c1 == c2;
}

double get_per(char c1, char c2) {
    if (c1 != '?'  && c2 != '?') {
        return 1.0;
    }
    if (c1 == '?' && c2 == '?') {
        return 1.0 / 26;
    }
    return 1.0 / 26;
}

class PalindromicSubstringsDiv1
{
public:
 double expectedPalindromes(vector <string> S1, vector <string> S2)
 {
    //$CARETPOSITION$
    // 5000 
    string s = "";
    range(i, S1.size()) s += S1[i];
    range(i, S2.size()) s += S2[i];
    int l = s.length();
    double ans = 0.0;
    double per;

  //  printf("%s\n", s.c_str());

    //with center
    for (int i = 0; i < l; i++) {
        per = 1.0;
        for (int j = 0; ; j++) {
            int le = i - j;
            int ri = i + j;
            if (le < 0 || ri >= l) break;
            if (!match(s[le], s[ri])) break;
            per *= (le == ri) ? 1.0 : get_per(s[le], s[ri]);
//            printf("%d ,%d , %lf\n", le, ri, per);
            ans += per;
        }
    }
    //without center
    for (int i = 0; i < l; i++) {
        per = 1.0;
        for (int j = 0; ; j++) {
            int le = i - j;
            int ri = i + 1 + j;
            if (le < 0 || ri >= l) break;
            if (!match(s[le], s[ri])) break;
            per *= get_per(s[le], s[ri]);
 //           printf("%d ,%d , %lf\n", le, ri, per);
            ans += per;
        }
    }

    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"a","a",""}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"a"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 6.0; verify_case(0, Arg2, expectedPalindromes(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"z??"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 3.115384615384615; verify_case(1, Arg2, expectedPalindromes(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"ab","c"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"??","a?"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 7.315088757396449; verify_case(2, Arg2, expectedPalindromes(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"?"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 1.0; verify_case(3, Arg2, expectedPalindromes(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"ab?def","?"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"f??a"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); double Arg2 = 12.545971779699588; verify_case(4, Arg2, expectedPalindromes(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PalindromicSubstringsDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
