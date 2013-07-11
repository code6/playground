// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Fox Ciel and Fox Jiro both went to spend an evening in the dancing room.
Together, there are N foxes in the room.
The foxes are numbered 0 through N-1.
In particular, Ciel is fox 0 and Jiro is fox 1.



You are given a vector <string> friendship that describes the initial friendship between the foxes in the room.
More precisely, friendship contains N elements with N characters each.
Character j of element i of friendship is 'Y' if foxes i and j are friends at the beginning of the evening, and 'N' otherwise.
Note that friendship is symmetric: whenever X is a friend of Y, Y is a friend of X.



During the evening, multiple songs will be played in succession.
During each song, some pairs of foxes will be dancing together.
Foxes are not allowed to change partners during the dance.
Thus in each dance each fox either dances with a single partner, or sits the dance out.



Foxes are not allowed to form the pairs for a dance arbitrarily.
It is only allowed for two foxes to dance together if they are friends, or if they have a common friend who can introduce them.
That is, if foxes A and B are not friends at the moment, they can only dance together if there is a fox C such that A and B are both friends with C.
After two foxes dance together, they become friends.



Fox Ciel wants to become friends with Fox Jiro.
Return the smallest number of dances in which this can be achieved (assuming that all other foxes cooperate and form pairs for the dances optimally).
If it's impossible to make Ciel and Jiro friends, return -1 instead.

DEFINITION
Class:DancingFoxes
Method:minimalDays
Parameters:vector <string>
Returns:int
Method signature:int minimalDays(vector <string> friendship)


NOTES
-Gender does not matter for the foxes when choosing their dance partners.


CONSTRAINTS
-N will be between 2 and 50, inclusive.
-friendship will contain exactly N elements.
-Each element of friendship will contain exactly N characters.
-Each character in friendship will be 'Y' or 'N'.
-For each i, friendship[i][i] = 'N'.
-For each i and j, friendship[i][j] = friendship[j][i].


EXAMPLES

0)
{"NNY",
 "NNY",
 "YYN"}

Returns: 1

There are 3 foxes. Ciel and Jiro are not friends, but they are both friends with fox 2. Thus, they may dance together in the first dance and become friends.

1)
{"NNNNN",
 "NNYYY",
 "NYNYY",
 "NYYNY",
 "NYYYN"}

Returns: -1

Ciel does not know any other fox at the dance, so she cannot dance with anybody.

2)
{"NNYYNN",
 "NNNNYY",
 "YNNNYN",
 "YNNNNY",
 "NYYNNN",
 "NYNYNN"}

Returns: 2



3)
{"NNYNNNNYN",
 "NNNNYNYNN",
 "YNNYNYNNN",
 "NNYNYNYYN",
 "NYNYNNNNY",
 "NNYNNNYNN",
 "NYNYNYNNN",
 "YNNYNNNNY",
 "NNNNYNNYN"}

Returns: 3



4)
{"NY",
 "YN"}

Returns: 0

Ciel and Jiro are already friends in the beginning, no dances are needed. In such a case, the correct return value is 0.

*/
// END CUT HERE
#line 117 "DancingFoxes.cpp"
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

const int MAX = 50 + 5;
const int INF = 100000;

int dis[MAX][MAX];
int dp[MAX];
int n;


int calc(int L) {
    if (L == INF) {
        return -1;
    }
    printf("L = %d\n", L);
    return dp[L];
}

void pp() {
    n = 6;
    memset(dis, 0, sizeof(dis));
    dis[0][2] = dis[2][3] = dis[3][4] = dis[4][5] = dis[5][1] = 1;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dis[i][j] == 1) {
                dis[j][i] = 1;
            }
        }
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (dis[i][j] == 1) {
                printf("Y");
            } else {
                printf("N");
            }
        }
        if (i < n ) {
            printf(",");
        } else {
            puts("");
        }
    }
}

class DancingFoxes
{
public:
 int minimalDays(vector <string> friendship)
 {
     pp();
 //$CARETPOSITION$
    n = friendship.size();
    int i, j;
    dp[1] = 0;
    dp[2] = 1;
    for (i = 3; i < MAX; i++) {
        int ne = i - i / 3;
        if (i % 3 == 2) {
            ne --;
        }
        dp[i] = dp[ne] + 1;
        /*
        if (dp[i] != i - 1) {
            printf("i = %d, dp[i] = %d\n", i, dp[i]);
        }
        */
    }
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i == j) {
                dis[i][j] = 0;
            } else {
                dis[i][j] = friendship[i][j] == 'Y' ? 1: INF;
            }
        }
    }

    int k;
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (k == i || k == j || i == j) {
                    continue;
                }
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }


    return calc(dis[0][1]);

 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NNY",
 "NNY",
 "YYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, minimalDays(Arg0)); }
	void test_case_1() { string Arr0[] = {"NNNNN",
 "NNYYY",
 "NYNYY",
 "NYYNY",
 "NYYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, minimalDays(Arg0)); }
	void test_case_2() { string Arr0[] = {"NNYYNN",
 "NNNNYY",
 "YNNNYN",
 "YNNNNY",
 "NYYNNN",
 "NYNYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(2, Arg1, minimalDays(Arg0)); }
	void test_case_3() { string Arr0[] = {
"NNYNNN",
"NNNNNY",
"YNNYNN",
"NNYNYN",
"NNNYNY",
"NYNNYN",
    }; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(3, Arg1, minimalDays(Arg0)); }
	void test_case_4() { string Arr0[] = {"NY",
 "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(4, Arg1, minimalDays(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 DancingFoxes ___test;
 ___test.run_test(-1);
}
// END CUT HERE
// NNYNNN,NNNNNY,YNNYNN,NNYNYN,NNNYNY,NYNNYN
