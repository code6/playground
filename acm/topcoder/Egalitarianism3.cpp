// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// In Treeland there are n cities, numbered 1 through n.
The cities are linked by n-1 bidirectional roads.
Each road connects a pair of cities.
The roads are built in such a way that each city is reachable from each other city by roads.
(In other words, the topology of the road network is a tree.)


You are given the int n and three vector <int>s that describe the road network: a, b, and len.
For each i between 0 and n-2, inclusive, there is a road of length len[i] that connects the cities a[i] and b[i].


The distance between two cities is the sum of lengths of roads on the sequence of roads that connects them. (Note that this sequence of roads is always unique.)


You want to select k cities in such a way that all pairwise distances between the selected cities are the same.
In other words, there must be a distance d such that the distance between every two selected cities is d.
Return the largest possible value of k for which this is possible.


DEFINITION
Class:Egalitarianism3
Method:maxCities
Parameters:int, vector <int>, vector <int>, vector <int>
Returns:int
Method signature:int maxCities(int n, vector <int> a, vector <int> b, vector <int> len)


CONSTRAINTS
-n will be between 1 and 50, inclusive.
-a will contain exactly n-1 elements.
-b will contain exactly n-1 elements.
-len will contain exactly n-1 elements.
-Each element in a will be between 1 and n, inclusive.
-Each element in b will be between 1 and n, inclusive.
-Each element in len will be between 1 and 1,000, inclusive.
-The graph described by a and b will be a tree.


EXAMPLES

0)
4
{1,1,1}
{2,3,4}
{1,1,1}

Returns: 3

There are 4 cities and 3 roads, each of length 1.
The roads connect the following pairs of cities: (1,2), (1,3), and (1,4).
The optimal answer is k=3.
We can select three cities in the required way: we select the cities {2, 3, 4}.
The distance between any two of these cities is 2.

1)
6
{1,2,3,2,3}
{2,3,4,5,6}
{2,1,3,2,3}

Returns: 3

Again, the largest possible k is 3.
There are two ways to select three equidistant cities: {1, 4, 6} and {4, 5, 6}.
(In both cases the common distance is 3.)

2)
10
{1,1,1,1,1,1,1,1,1}
{2,3,4,5,6,7,8,9,10}
{1000,1000,1000,1000,1000,1000,1000,1000,1000}

Returns: 9



3)
1
{}
{}
{}

Returns: 1

Note that n can be 1.

*/
// END CUT HERE
#line 93 "Egalitarianism3.cpp"
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

const int MAX = 100 + 50;
const int INF = 10000000;
int n;
int g[MAX][MAX];

class Egalitarianism3
{
public:
 int maxCities(int _n, vector <int> a, vector <int> b, vector <int> len)
 {
 //$CARETPOSITION$
    n = _n;
    range(i, n)
        range(j, n)
            g[i][j] = i == j ? 0 : INF;
    range(i, n - 1) {
        int u = a[i] - 1;
        int v = b[i] - 1;
        g[u][v] = g[v][u] = len[i];
    }
    range(i, n)
        range(j, n)
            range(k, n)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    int ans = 1;
    range(i, n)
        range(j, n)
            if (i != j)
            {
                int d = g[i][j];
                vector<int> arr;
                arr.pb(i);
                arr.pb(j);
                range(k, n)
                    if (k != i && k != j) {
                        bool ok = true;
                        range(u, arr.size()) {
                            if (g[k][arr[u]] != d) {
                                ok = false;
                                break;
                            }
                        }
                        if (ok) arr.pb(k);
                    }
                ans = max(ans, (int)arr.size());
            }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = {1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1,1,1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; verify_case(0, Arg4, maxCities(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arg0 = 6; int Arr1[] = {1,2,3,2,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,4,5,6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2,1,3,2,3}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; verify_case(1, Arg4, maxCities(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arg0 = 10; int Arr1[] = {1,1,1,1,1,1,1,1,1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2,3,4,5,6,7,8,9,10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1000,1000,1000,1000,1000,1000,1000,1000,1000}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 9; verify_case(2, Arg4, maxCities(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arg0 = 1; int Arr1[] = {}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; verify_case(3, Arg4, maxCities(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 Egalitarianism3 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
