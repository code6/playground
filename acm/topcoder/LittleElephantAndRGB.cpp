// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
Little Elephant from the Zoo of Lviv likes strings that consist of characters 'R', 'G' and 'B'. You are given a vector <string> list. Concatenate all elements of list to get the string S of length N. The characters in S are numbered from 0 to N-1, inclusive.




You are also given int minGreen. Little Elephant thinks that string is nice if and only if it contains a substring of at least minGreen consecutive characters 'G'. For example, if minGreen = 2, then strings "GG", "GGRGBB" and "RRRGRBGGG" are nice, but "G", "GRG", "BBRRGRGB" are not.




Little Elephant wants to know the number of quadruples of integers (a,b,c,d) such that:

Each of a, b, c, d is between 0 and N-1, inclusive.
a <= b and c <= d. (Both a..b and c..d are valid ranges of values.)
b < c. (The entire range a..b lies before the range c..d.)
The string T = S[a..b] + S[c..d] is nice.

Compute and return the number of such quadruples (a,b,c,d).


DEFINITION
Class:LittleElephantAndRGB
Method:getNumber
Parameters:vector <string>, int
Returns:long long
Method signature:long long getNumber(vector <string> list, int minGreen)


CONSTRAINTS
-list will contain between 1 and 50 elements, inclusive.
-Each element of list will contain between 1 and 50 characters, inclusive.
-Each element of list will consist only of characters 'R', 'G' and 'B'.
-minGreen will be between 1 and 2500, inclusive.


EXAMPLES

0)
{"GRG"}
2

Returns: 1

The only valid quadruple is (0,0,2,2).
For this quadruple we have S[a..b]="G" and S[c..d]="G", thus T = "GG".

1)
{"GG", "GG"}
3

Returns: 9

There are 3 valid quadruples such that T="GGGG" and 6 quadruples such that T="GGG".

2)
{"GRBGRBBRG"}
2

Returns: 11

One of the valid quadruples is (0,0,3,5).
This quadruple corresponds to the nice string T="GGRB".

3)
{"RRBRBBRRR", "R", "B"}
1

Returns: 0



4)
{"GRGGGRBRGG", "GGGGGGGG", "BRGRBRB"}
4

Returns: 12430



*/
// END CUT HERE
#line 87 "LittleElephantAndRGB.cpp"
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
typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

const int MAX = 2500 + 5;
string s;
int cnt[MAX][MAX];
int cnt2[MAX][MAX];

class LittleElephantAndRGB
{
public:
 long long getNumber(vector <string> list, int minGreen)
 {
 //$CARETPOSITION$
    s = "";
    range(i, list.size()) {
        s += list[i];
    }

    string s1 = "";
    range(i, 50) s1 += 'G';
    string ss;
    range(i, 50) {
        if (i) ss += ',';
        ss += s1;
    }
    cout << ss << endl;

    memset(cnt, 0, sizeof(cnt));
    memset(cnt2, 0, sizeof(cnt2));

    int n = s.size();

    int i, j;
    for (i = 0; i < s.size(); i++) {
        bool all_g = true;
        int last_gg;
        int first_gg;
        int gg;
        first_gg = last_gg = gg = 0;
        for (j = i; j < n; j++) {
            last_gg = s[j] == 'G' ? last_gg + 1 : 0;
            all_g = all_g && s[j] == 'G';
            if (all_g) {
                first_gg = max(first_gg, last_gg);
            }
            gg = max(gg, last_gg);
            if (gg >= minGreen) {
                cnt[i][minGreen] ++;
            } else {
                cnt[i][first_gg] ++;
            }
        }
    }

    for (i = n - 1; i >= 0; i--) {
        for (j = minGreen; j >= 0; j--) {
            cnt2[i][j] = cnt2[i + 1][j] + cnt2[i][j + 1] - cnt2[i+1][j+1] + cnt[i][j];
            /*
            if (n == 4 && cnt2[i][j]) {
                printf("(%d, %d) = %lld, %lld, %lld, %lld\n", i, j, cnt2[i][j], cnt2[i+1][j], cnt2[i][j+1], cnt[i][j]);
            }
            */
        }
    }


    ll ans = 0;

    for (i = 0; i < n; i++) {
        int last_gg = 0;
        int gg = 0;
        for (j = i; j < s.size(); j++) {
            last_gg = s[j] == 'G' ? last_gg + 1 : 0;
            gg = max(gg, last_gg);
            if (gg >= minGreen) {
                /*
                if ((n == 4) && (cnt2[j + 1][0] != 0)) {
                    printf("at %d, %d, gg= %d, use (%d, %d) = %lld\n", i, j, gg,  j+1, 0, cnt2[j+1][0]);
                }
                */
                ans += cnt2[j + 1][0];
            } else {
                /*
                if ((n == 4) && (cnt2[j + 1][minGreen - last_gg] != 0)) {
                    printf("at %d, %d, gg= %d, use (%d, %d) = %lld\n", i, j, gg,  j+1, minGreen - last_gg, cnt2[j+1][minGreen - last_gg]);
                }
                */
                ans += cnt2[j + 1][minGreen - last_gg];
            }
        }
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"GRG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 1LL; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"GG", "GG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long long Arg2 = 9LL; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"GRBGRBBRG"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; long long Arg2 = 11LL; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"RRBRBBRRR", "R", "B"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; long long Arg2 = 0LL; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"GRGGGRBRGG", "GGGGGGGG", "BRGRBRB"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long long Arg2 = 12430LL; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 LittleElephantAndRGB ___test;
 ___test.run_test(-1);
}
// END CUT HERE
