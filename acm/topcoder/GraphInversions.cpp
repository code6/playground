// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You are given a connected undirected graph with N vertices.
The vertices are numbered 0 through N-1.
The graph is special: the number of edges is exactly equal to the number of vertices.
You are given the description of the graph as three vector <int>s: A, B, and V.
Each of these vector <int>s has N elements.
For each valid i, there's an edge between vertices A[i] and B[i].
There are no self-loops and no duplicate edges.
For each valid i, we associate the value V[i] with the vertex i.

We will be interested in some simple paths in this graph.
A simple path is a sequence of vertices such that no vertex is used twice, and each pair of consecutive vertices is connected by an edge.
For any simple path, we can write down a sequence of integers: the values associated with the vertices on the path, in order of appearance.
We will call such a sequence the value list of the given simple path.

An inversion in a sequence S is a pair of valid indices (i,j) into the sequence S such that i < j but S[i] > S[j].
For example, the sequence S = {10, 30, 20, 20} has two inversions: (1,2) and (1,3).
(The indices are 0-based.)

You are given a graph G in the format described above, and an int K.
In the graph G, consider all simple paths with K or more vertices.
If there is no such simple path, return -1.
Otherwise, return the smallest number of inversions in the value list of such path.


DEFINITION
Class:GraphInversions
Method:getMinimumInversions
Parameters:vector <int>, vector <int>, vector <int>, int
Returns:int
Method signature:int getMinimumInversions(vector <int> A, vector <int> B, vector <int> V, int K)


CONSTRAINTS
-N will be between 3 and 1000, inclusive.
-A, B, and V will each have N elements.
-Each element of A and B will be between 0 and N-1, inclusive.
-For all valid i, A[i] will not be equal to B[i]. (I.e., there are no self loops.)
-No two edges will connect the same pair of vertices.
-The graph described by A and B will be connected.
-Each element of V will be between 1 and 1000, inclusive.
-K will be between 1 and N, inclusive.


EXAMPLES

0)
{0,1,2}
{1,2,0}
{40,50,60}
3

Returns: 0

The best path is the path {0, 1, 2}. Its value list is the sequence {40, 50, 60}, and there are 0 inversions in this sequence.



1)
{0,1,2,3}
{1,2,3,0}
{60,40,50,30}
3

Returns: 1

As K=3, we are interested in simple paths of lengths 3 or more.
There are no simple paths of length 4 or more in this graph.
Each simple path of length 3 gives us at least one inversion.
The path {3, 2, 1} is an example of an optimal path.
Its value list is {30, 50, 40}.
There is 1 inversion: the 50 occurring before the 40.


2)
{0,1,2,3,0}
{1,2,3,0,4}
{10,10,10,5,5}
5

Returns: 1

Two or more nodes can have the same associated value.


3)
{0,1,2,3,0,2}
{1,2,3,0,4,5}
{10,2,5,3,7,1}
6

Returns: -1

There are no simple paths with length 6.


4)
{5,7,7,5,5,7,6,4}
{2,0,2,0,1,4,7,3}
{15,10,5,30,22,10,5,2}
6

Returns: 3



*/
// END CUT HERE
#line 112 "GraphInversions.cpp"
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
const int MAXN = 1000 + 5;


vector<int> g[MAX];
int n;

void update(int & ans, int v) {
    if (v == -1) return;
    if (ans == -1) ans = v;
    else ans = min(ans, v);
}

bool istree(int n, vector<int>  (&g)[MAXN]) {
    queue<int> Q;
    vector<bool> visit;
    visit.resize(n);
    visit[0] = true;
    Q.push(0);
    while (!Q.empty()) {
        int cur = Q.front();
        Q.pop();
        for (int i = 0; i < g[cur].size(); i++) {
            int ne = g[cur][i];
            if (visit[ne]) continue;
            visit[ne] = true;
            Q.push(ne);
        }
    }
    range(i, n) if (!visit[i]) return false;
    return true;
}

int _search(int start, int n, vector<int> (&g)[MAXN], vector<int> & v, int k, vector<bool> &visit, vector<int>&path, int inv_cnt) {
    visit[start] = true;
    for (int i = 0; i < g[cur].size(); i++) {
            int ne = g[cur][i];
            if (visit[ne]) continue;
            _search(ne, n, g, v, k, visit, path, inv_cnt);
    }
}

int search(int n, vector<int> (&g)[MAXN], vector<int> & v, int k) {
    int ans = -1;
    range(i, n) {
        vector<bool> visit;
        visist.resize(n);
        update(ans, _search(i, n, g, v, k, visit, vector<int>(), -1));
    }
    return ans;
}


class GraphInversions
{
public:
 int getMinimumInversions(vector <int> A, vector <int> B, vector <int> V, int K)
 {
 //$CARETPOSITION$
    int n = A.size();
    int ans = -1;
    range(i, n) {
        vector<int> g[MAXN];
        range(j, n) {
            if (i == j) continue;
            g[A[j]].pb(B[j]);
            g[B[j]].pb(A[j]);
        }
        if (!istree(n, g)) continue;
        update(ans, search(n, g, V, K));
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0,1,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {40,50,60}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 0; verify_case(0, Arg4, getMinimumInversions(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0,1,2,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {60,40,50,30}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; int Arg4 = 1; verify_case(1, Arg4, getMinimumInversions(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {0,1,2,3,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,0,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10,10,10,5,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 5; int Arg4 = 1; verify_case(2, Arg4, getMinimumInversions(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {0,1,2,3,0,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1,2,3,0,4,5}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10,2,5,3,7,1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; int Arg4 = -1; verify_case(3, Arg4, getMinimumInversions(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {5,7,7,5,5,7,6,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2,0,2,0,1,4,7,3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {15,10,5,30,22,10,5,2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 6; int Arg4 = 3; verify_case(4, Arg4, getMinimumInversions(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 GraphInversions ___test;
 ___test.run_test(-1);
}
// END CUT HERE
