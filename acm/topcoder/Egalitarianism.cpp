// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// A kingdom has n citizens. Each one has some amount of money, a number of dollars denoted by a non-negative integer.

Citizens are numbered from 0 to n-1. Some citizens have friends. Their friendship network is described by a vector <string> called isFriend, such that if isFriend[i][j] == 'Y', the citizens numbered i and j are friends, and if isFriend[i][j] == 'N', these citizens are not friends.

The king decrees the following:

Each citizen's amount of money must be within d dollars of the amount of money belonging to any of his friends. In other words, a citizen with x dollars must not have any friends with less than x-d dollars or more than x+d dollars.

Given the number of citizens and their friendship network, what is the greatest possible money difference between any two people (not necessarily friends) in this kingdom? If there is a finite answer, return it. Otherwise, return -1.

DEFINITION
Class:Egalitarianism
Method:maxDifference
Parameters:vector <string>, int
Returns:int
Method signature:int maxDifference(vector <string> isFriend, int d)


CONSTRAINTS
-n will be between 2 and 50, inclusive.
-d will be between 0 and 1,000, inclusive.
-isFriend will contain exactly n elements.
-Each element of isFriend will contain exactly n characters, each of which is either 'Y' or 'N'.
-For any i, isFriend[i][i] = 'N'.
-For any i and j, isFriend[i][j] = isFriend[j][i].


EXAMPLES

0)
{"NYN",
 "YNY",
 "NYN"}
10

Returns: 20

The kingdom has three citizens. Citizens 0 and 1 are friends. Also, citizens 1 and 2 are friends. The greatest possible money difference between any two citizens is $20, as in the following configuration: citizen 0 has $100; citizen 1 has $110; citizen 2 has $120.

1)
{"NN",
 "NN"}
1

Returns: -1

Since citizens 0 and 1 are not friends, there are no constraints between them.

2)
{"NNYNNN",
 "NNYNNN",
 "YYNYNN",
 "NNYNYY",
 "NNNYNN",
 "NNNYNN"}
1000

Returns: 3000



3)
{"NNYN",
 "NNNY",
 "YNNN",
 "NYNN"}
584

Returns: -1



4)
{"NYNYYYN",
 "YNNYYYN",
 "NNNNYNN",
 "YYNNYYN",
 "YYYYNNN",
 "YYNYNNY",
 "NNNNNYN"}
5

Returns: 20



5)
{"NYYNNNNYYYYNNNN",
 "YNNNYNNNNNNYYNN",
 "YNNYNYNNNNYNNNN",
 "NNYNNYNNNNNNNNN",
 "NYNNNNYNNYNNNNN",
 "NNYYNNYNNYNNNYN",
 "NNNNYYNNYNNNNNN",
 "YNNNNNNNNNYNNNN",
 "YNNNNNYNNNNNYNN",
 "YNNNYYNNNNNNNNY",
 "YNYNNNNYNNNNNNN",
 "NYNNNNNNNNNNNNY",
 "NYNNNNNNYNNNNYN",
 "NNNNNYNNNNNNYNN",
 "NNNNNNNNNYNYNNN"}

747

Returns: 2988



6)
{"NY",
 "YN"}
0

Returns: 0



*/
// END CUT HERE
#line 125 "Egalitarianism.cpp"
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

const int MAX = 100;

int n, d;
bool flag[MAX][MAX];
bool vis[MAX];
int val[MAX];

int bfs(int start) {
    memset(vis, 0, sizeof(vis));
    vis[start] = true;
    val[start] = 0;
    int ret = 0;
    int i;

    queue<int> Q;
    Q.push(start);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (i = 0; i < n; i++) {
            if (flag[cur][i] && !vis[i]) {
                    vis[i] = true;
                    val[i] = val[cur] + d;
                    ret = max(ret, val[i]);
                    Q.push(i);
            }
        }
    }

    for (i = 0; i < n; i++) {
        if (!vis[i]) {
            return -1;
        }
    }

    return ret;
}

class Egalitarianism
{
public:
 int maxDifference(vector <string> isFriend, int _d)
 {
 //$CARETPOSITION$
    n = isFriend.size();
    d = _d;
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            flag[i][j] = isFriend[i][j] == 'Y';
        }
    }
    int ret = -1;
    for (i = 0; i < n; i++) ret = max(ret, bfs(i));
    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN",
 "YNY",
 "NYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; int Arg2 = 20; verify_case(0, Arg2, maxDifference(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"NN",
 "NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = -1; verify_case(1, Arg2, maxDifference(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"NNYNNN",
 "NNYNNN",
 "YYNYNN",
 "NNYNYY",
 "NNNYNN",
 "NNNYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 3000; verify_case(2, Arg2, maxDifference(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"NNYN",
 "NNNY",
 "YNNN",
 "NYNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 584; int Arg2 = -1; verify_case(3, Arg2, maxDifference(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"NYNYYYN",
 "YNNYYYN",
 "NNNNYNN",
 "YYNNYYN",
 "YYYYNNN",
 "YYNYNNY",
 "NNNNNYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; int Arg2 = 20; verify_case(4, Arg2, maxDifference(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"NYYNNNNYYYYNNNN",
 "YNNNYNNNNNNYYNN",
 "YNNYNYNNNNYNNNN",
 "NNYNNYNNNNNNNNN",
 "NYNNNNYNNYNNNNN",
 "NNYYNNYNNYNNNYN",
 "NNNNYYNNYNNNNNN",
 "YNNNNNNNNNYNNNN",
 "YNNNNNYNNNNNYNN",
 "YNNNYYNNNNNNNNY",
 "YNYNNNNYNNNNNNN",
 "NYNNNNNNNNNNNNY",
 "NYNNNNNNYNNNNYN",
 "NNNNNYNNNNNNYNN",
 "NNNNNNNNNYNYNNN"}
; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 747; int Arg2 = 2988; verify_case(5, Arg2, maxDifference(Arg0, Arg1)); }
	void test_case_6() { string Arr0[] = {"NY",
 "YN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 0; verify_case(6, Arg2, maxDifference(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 Egalitarianism ___test;
 ___test.run_test(-1);
}
// END CUT HERE
