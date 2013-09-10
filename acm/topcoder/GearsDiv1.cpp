// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Goose Tattarrattat has a machine that contains N gears (cogwheels).
The gears are numbered 0 through N-1.
Each of the gears has one of three colors: red, green, or blue.

Some pairs of gears mesh.
Let X and Y be two meshing gears.
Note that if X is turning, Y must clearly be turning in the opposite direction (clockwise vs. counter-clockwise).
Two gears with the same color never mesh.
Apart from that, do not assume anything about the pairs of meshing gears.

You are given a string color and a vector <string> graph.
For each i, character i of color represents the color of gear i: 'R' is red, 'G' is green, and 'B' is blue.
The vector <string> graph contains the information on meshing pairs of gears:
If the j-th character of the i-th element of graph is 'Y', gear i meshes with gear j.

We want all gears to turn at the same time.
Additionally, all gears of the same color must turn in the same direction.
Return the minimal number of gears that have to be removed from the machine in order to achieve this goal.

DEFINITION
Class:GearsDiv1
Method:getmin
Parameters:string, vector <string>
Returns:int
Method signature:int getmin(string color, vector <string> graph)


NOTES
-Removing a gear creates a gap between the other gears, no new meshing pairs of gears are created by removing a gear.
-The graph described by graph is not necessarily planar.


CONSTRAINTS
-color will contain between 2 and 50 characters, inclusive.
-Each character in color will be 'R' or 'G' or 'B'.
-graph will contain exactly N elements, where N is the number of characters in color.
-Each element of graph will contain exactly N characters, where N is the number of characters in color.
-Each character in graph will be either 'Y' or 'N'.
-For each i, the i-th character of the i-th element of graph will be 'N'.
-For each i and j, the i-th character of the j-th element of graph and the j-th character of the i-th element of graph will be same.
-For each i and j, if the i-th and the j-th character of color are equal, then the i-th character of the j-th element of graph will be 'N'.


EXAMPLES

0)
"RGB"
{"NYY","YNY","YYN"}

Returns: 1

We have three gears, each meshes with each of the others.
In this configuration the gears are not able to turn at all.
However, as soon as we remove any of the gears, the other two will be able to turn.

1)
"RGBR"
{"NNNN","NNNN","NNNN","NNNN"}

Returns: 0

Here, each of the gears can turn without interacting with the others.

2)
"RGBR"
{"NYNN","YNYN","NYNY","NNYN"}

Returns: 1

These are four gears arranged into a row. It is possible to turn all these gears at the same time, but the two red gears would turn in opposite directions. Thus we need to remove at least one gear.

3)
"RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG"
{"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"}

Returns: 3



*/
// END CUT HERE
#line 115 "GearsDiv1.cpp"
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

bool dfs(char cy, const string&color, const vector<string>&graph, int at, vector<int>&rmatch, vector<bool>&vis) {
    if (vis[at]) {
        return false;
    }
    vis[at] = true;
    int n = color.size();
    range(i, n) {
        if (color[i] == cy && graph[i][at] == 'Y') {
            if (rmatch[i] == -1 || dfs(cy, color, graph, rmatch[i], rmatch, vis)) {
                rmatch[i] = at;
                return true;
            }
        }
    }
    return false;
}

int match(char cx, char cy, const string& color, const vector<string> &graph) {
    int n = color.size();
    vector<int> rmatch;
    range(i, n) {
        rmatch.push_back(-1);
    }
    vector<bool> vis(n);
    int res = 0;
    range(i, n) {
        if (color[i] == cx && !vis[i]) {
            if (dfs(cy, color, graph, i, rmatch, vis)) {
                res ++;
            }
        }
    }
    return res;
}

class GearsDiv1
{
public:
 int getmin(string color, vector <string> graph)
 {
 //$CARETPOSITION$
    int n = graph.size();
    int ans = n;
    ans = min(ans, match('R', 'G', color, graph));
    ans = min(ans, match('R', 'B', color, graph));
    ans = min(ans, match('B', 'G', color, graph));
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "RGB"; string Arr1[] = {"NYY","YNY","YYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(0, Arg2, getmin(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "RGBR"; string Arr1[] = {"NNNN","NNNN","NNNN","NNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, getmin(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "RGBR"; string Arr1[] = {"NYNN","YNYN","NYNY","NNYN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1; verify_case(2, Arg2, getmin(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "RRRRRGRRBGRRGBBGGGBRRRGBRGRRGG"; string Arr1[] = {"NNNNNYNNNYNNYNNNYNNNNNNNNYNNYY",
 "NNNNNNNNYNNNYNYNNYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNNNNYNNNNNNYNNNY",
 "NNNNNNNNNYNNYNNYYYNNNNYNNYNNNN",
 "NNNNNNNNNYNNYNNYYYNNNNYNNNNNNN",
 "YNYNNNYYYNNYNYYNNNNNYYNYNNYYNN",
 "NNNNNYNNNNNNNNNYYYNNNNYNNYNNYY",
 "NNNNNYNNNNNNNNNYNNNNNNNNNNNNYN",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "YNNYYNNNYNNNNYYNNNYNYYNYNNNNNN",
 "NNNNNNNNNNNNYNNYNYNNNNYNNNNNNY",
 "NNNNNYNNNNNNYNNYYYNNNNNNNNNNYN",
 "YYNYYNNNYNYYNYYNNNYNYNNYNNNNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNYNYYY",
 "NYNNNYNNNYNNYNNYYYNNNNYNNYNNYY",
 "NNNYYNYYYNYYNYYNNNYNYNNYYNYYNN",
 "YNNYYNYNYNNYNYYNNNYNNNNYYNNYNN",
 "NYNYYNYNYNYYNYYNNNNYYNNYYNYNNN",
 "NNYNNNNNNYNNYNNYYNNNNNYNNYNNNY",
 "NNNNNNNNNNNNNNNNNYNNNNYNNYNNNY",
 "NNNNNYNNNYNNYNNYNYNNNNYNNNNNYY",
 "NNNNNYNNNYNNNNNNNNNNNNYNNNNNNN",
 "NYNYYNYNYNYNNYYNNNYYYYNYYNYNNN",
 "NNNNNYNNNYNNYNNYYYNNNNYNNNNNNY",
 "NNNNNNNNNNNNNNNYYYNNNNYNNYNNYY",
 "YYYYNNYNYNNNNYYNNNYYNNNNYNYYNN",
 "NNNNNYNNNNNNNNNYNYNNNNYNNYNNYN",
 "NNNNNYNNNNNNNYNYYNNNNNNNNYNNYY",
 "YYNNNNYYYNNYNYYNNNNNYNNNYNYYNN",
 "YYYNNNYNYNYNNYYNNNYYYNNYYNNYNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; verify_case(3, Arg2, getmin(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 GearsDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
