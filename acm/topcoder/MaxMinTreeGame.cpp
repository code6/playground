// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// MaxMinTreeGame is a game for two players.
The game is played on a tree.
The tree has N nodes, labeled 0 through N-1.
Each node of the tree also has an integer cost.

The players take alternating turns.
In her turn, the current player starts by choosing one edge of the tree and erasing it.
This necessarily divides the tree into two components.
The current player then decides which of the components to keep, and erases the other component completely.

The game ends when there is only one node left.
The cost of that node is the result of the game.
The first player (i.e., the one that starts the game) wants to maximize the result.
Naturally, the second player's goal is to minimize the result.

You are given a vector <int> edges that describes the structure of the tree.
For each i between 0 and N-2, inclusive, the tree contains an edge between the vertices i+1 and edges[i].
You are also given a vector <int> costs.
For each i between 0 and N-1, inclusive, the cost of vertex i is costs[i].

Return the result of the game, assuming that both players play optimally.

DEFINITION
Class:MaxMinTreeGame
Method:findend
Parameters:vector <int>, vector <int>
Returns:int
Method signature:int findend(vector <int> edges, vector <int> costs)


CONSTRAINTS
-The number of nodes in the tree N will be between 2 and 50, inclusive.
-edges will contain exactly N-1 elements.
-For each i, edges[i] will be between 0 and i, inclusive.
-costs will contain exactly N elements.
-Each element of costs will be between 0 and 1,000,000,000, inclusive.


EXAMPLES

0)
{0}
{4,6}

Returns: 6

There is only one edge in this tree and the first player will choose it. After that she will keep the component containing the node with cost 6.


1)
{0,1}
{4,6,5}

Returns: 5

One of the optimal moves for the first player is to remove the edge between nodes 0 and 1 and to keep the component containing nodes 1 and 2. The second player will then remove the remaining edge and keep the node with cost 5.


2)
{0,1,2,3}
{0,1,0,1,0}

Returns: 0



3)
{0,0,0}
{5,1,2,3}

Returns: 3



4)
{0,0}
{3,2,5}

Returns: 5



*/
// END CUT HERE
#line 89 "MaxMinTreeGame.cpp"
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

int du[100];
int n;

class MaxMinTreeGame
{
public:
 int findend(vector <int> edges, vector <int> costs)
 {
 //$CARETPOSITION$
    n = edges.size() + 1;
    memset(du, 0, sizeof(du));
    range(i, edges.size()) {
        int x = i + 1;
        int y = edges[i];
        du[x] ++;
        du[y] ++;
    }
    int ans = -1;
    range(i, n) {
        if (du[i] == 1) {
            ans = max(ans, costs[i]);
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
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,6}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 6; verify_case(0, Arg2, findend(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4,6,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, findend(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0,1,0,1,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, findend(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {5,1,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, findend(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3,2,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(4, Arg2, findend(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 MaxMinTreeGame ___test;
 ___test.run_test(-1);
}
// END CUT HERE
