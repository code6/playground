// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// We say that a string Z can be obtained by shuffling two strings X and Y together, if it is possible to interleave the letters of X and Y so that Z is obtained. It is not allowed to change the order of letters in X and Y.
For example, you can shuffle the strings X="abcd" and Y="efg" to produce any of the strings "abcdefg", "aebfcgd", "abcefgd", or "eabcfdg", but you cannot produce the string "bacdefg".



Formally, let Shuffle(X,Y) be the set of all strings that can be produced by shuffling X and Y together.
We can define Shuffle inductively as follows:

for any string X: Shuffle("",X) = Shuffle(X,"") = { X }
for any letters a, b and any strings X, Y:
Shuffle(aX,bY) = { aZ : Z belongs to Shuffle(X,bY) } united with { bZ : Z belongs to Shuffle(aX,Y) }.




Fox Ciel wants to register on TopCoder.
In order to do that, she has to pick a handle.
Ciel has a pet cat called S.
As her handle, Ciel wants to use a string H with the following property:
S can be obtained by shuffling H and some permutation of H together.
For example, if S="ceiiclel", one possible handle would be H="ciel":
she can permute H to obtain H'="eicl", and then shuffle these H and H' together to produce S.



You are given the string S.
The constraints guarantee that there is at least one possible handle H with the above property.
Find and return the lexicographically smallest valid H.

DEFINITION
Class:FoxAndHandle
Method:lexSmallestName
Parameters:string
Returns:string
Method signature:string lexSmallestName(string S)


CONSTRAINTS
-S will contain between 2 and 50 characters, inclusive.
-Each character of S will be a lowercase letter ('a'-'z').
-Each letter ('a'-'z') will occur in S an even number of times.


EXAMPLES

0)
"foxfox"

Returns: "fox"

There are five possible handles for Fox Ciel in this test case: "fox", "fxo", "ofx", "oxf", and "xfo".
The lexicographically smallest one is "fox".

1)
"ccieliel"

Returns: "ceil"

Note that "ciel" is also a valid handle, but "ceil" is lexicographically smaller.

2)
"abaabbab"

Returns: "aabb"



3)
"bbbbaaaa"

Returns: "bbaa"



4)
"fedcbafedcba"

Returns: "afedcb"



5)
"nodevillivedon"

Returns: "deilvon"



*/
// END CUT HERE
#line 95 "FoxAndHandle.cpp"
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

bool ok (int cost[50], int next[50]) {
    int i;
    for (i = 0; i < 50; i++) {
        if (next[i] > cost[i]) {
            return false;
        }
    }
    for (i = 0; i < 50; i++) {
        if (next[i]) {
            //printf("ch = %c, cost = %d, next = %d\n", i + 'a', cost[i], next[i]);
            cost[i] -= next[i];
        }
    }
    return true;
}

class FoxAndHandle
{
public:
 string lexSmallestName(string S)
 {
 //$CARETPOSITION$
    int n = S.size();
    int i, j, k;
    int cnt[50];
    int mycnt[50];
    memset(cnt, 0, sizeof(cnt));
    for (i = 0; i < n; i++) {
        cnt[S[i] - 'a'] ++;
    }
    for (i = 0; i < 50; i++) {
       cnt[i] /= 2;
       mycnt[i] = cnt[i];
    }


    string ret;
    ret = "";
    int sta = 0;
    for (i = 0; i < n / 2; i++) {
        for (j = 0; j < 26; j++) {
            if (mycnt[j] == 0)  {
                continue;
            }
            char nc = 'a' + j;
            int next_cost[50];
            memset(next_cost, 0, sizeof(next_cost));
            for (k = sta; k < n && S[k] != nc ; k++) {
                next_cost[S[k] - 'a'] ++;
            }
            if (ok(cnt, next_cost)) {
                //printf("nc = %c sta = %d\n", nc, sta);
                ret += nc;
                sta = k + 1;
                mycnt[j] -= 1;
                break;
            }
        }
    }

    return ret;

 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "foxfox"; string Arg1 = "fox"; verify_case(0, Arg1, lexSmallestName(Arg0)); }
	void test_case_1() { string Arg0 = "ccieliel"; string Arg1 = "ceil"; verify_case(1, Arg1, lexSmallestName(Arg0)); }
	void test_case_2() { string Arg0 = "abaabbab"; string Arg1 = "aabb"; verify_case(2, Arg1, lexSmallestName(Arg0)); }
	void test_case_3() { string Arg0 = "bbbbaaaa"; string Arg1 = "bbaa"; verify_case(3, Arg1, lexSmallestName(Arg0)); }
	void test_case_4() { string Arg0 = "fedcbafedcba"; string Arg1 = "afedcb"; verify_case(4, Arg1, lexSmallestName(Arg0)); }
	void test_case_5() { string Arg0 = "nodevillivedon"; string Arg1 = "deilvon"; verify_case(5, Arg1, lexSmallestName(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 FoxAndHandle ___test;
 ___test.run_test(-1);
}
// END CUT HERE
