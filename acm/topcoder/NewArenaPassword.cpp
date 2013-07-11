// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You are a huge fan of an online programming contest called SRM (Special Round Match). To participate in an SRM contest, you must first download an applet called Arena, log in to the Arena by entering your username and password, and start competing.

Recently, to avoid hackers' attacks on the Arena, SRM imposes a new rule for the users' passwords. From now on, the first K characters of each user's password must match its last K characters. In this way, if someone enters a password with different first and last K characters repeatedly, it can be considered an attack from hackers.

However, you love your old password and do not want to change many characters from it. You are given a string oldPassword representing your old password, and an int K. Return the minimum number of characters of oldPassword that must be changed so that the string containing the first K characters of oldPassword is equal to the string containing the last K characters of oldPassword.

DEFINITION
Class:NewArenaPassword
Method:minChange
Parameters:string, int
Returns:int
Method signature:int minChange(string oldPassword, int K)


CONSTRAINTS
-oldPassword will contain between 1 and 50 characters, inclusive.
-Each character of oldPassword will be a lowercase letter 'a' - 'z'.
-K will be between 1 and the number of characters of oldPassword, inclusive.


EXAMPLES

0)
"topcoderopen"
5

Returns: 3

A possible solution is changing your password into "topcndetopcn". To do this, you must change the 4th, 7th, and 10th characters (0-based) of "topcoderopen".

1)
"puyopuyo"
4

Returns: 0

Your old password already satisfies the new rule.

2)
"loool"
3

Returns: 1

The first and the last K characters can overlap. In this case, the only optimal solution is to change your password into "lolol".

3)
"arena"
5

Returns: 0



4)
"amavckdkz"
7

Returns: 5



*/
// END CUT HERE
#line 69 "NewArenaPassword.cpp"
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

const int MAX = 100 + 40;
int parent[MAX];

void init(int n)
{
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int u_find(int a)
{
    while (a != parent[a]) {
        //halving path length
        parent[a] = parent[parent[a]];
        a = parent[a];
    }
    return a;
}

void u_union(int a, int b)
{
    a = u_find(a);
    b = u_find(b);
    if (a == b) {
        return;
    }
    parent[b] = a;
}

class NewArenaPassword
{
public:
 int minChange(string oldPassword, int K)
 {
 //$CARETPOSITION$
    int len = oldPassword.length();
    int i, j;
    init(len);
    for (i = 0; i < K; i++) {
        int x, y, z;
        x = i;
        y = len - (K - i);
        u_union(x, y);
        if (y < K) {
            z = len - (K - y);
            u_union(x, z);
        }
    }
    int ans = 0;
    int cnt[100];

    for (i = 0; i < len; i++) {
        memset(cnt, 0, sizeof(cnt));
        int tot = 0;
        int maxt = 0;
        for (j = 0; j < len; j++) {
            if (u_find(j) == i) {
                int at = oldPassword[j] - 'a';
                cnt[at] ++;
                tot ++;
                if (cnt[at] > maxt) {
                    maxt = cnt[at];
                }
            }
        }
        if (tot > 0 && tot > maxt) {
            ans += tot - maxt;
        }
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "topcoderopen"; int Arg1 = 5; int Arg2 = 3; verify_case(0, Arg2, minChange(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "puyopuyo"; int Arg1 = 4; int Arg2 = 0; verify_case(1, Arg2, minChange(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "loool"; int Arg1 = 3; int Arg2 = 1; verify_case(2, Arg2, minChange(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "arena"; int Arg1 = 5; int Arg2 = 0; verify_case(3, Arg2, minChange(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "amavckdkz"; int Arg1 = 7; int Arg2 = 5; verify_case(4, Arg2, minChange(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 NewArenaPassword ___test;
 ___test.run_test(-1);
}
// END CUT HERE
