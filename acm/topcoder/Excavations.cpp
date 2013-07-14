// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Once upon a time, there was a civilization called Ruritania. It had n building sites numbered from 0 to n-1. There were various types of buildings such as libraries, markets, and palaces. Each building type was assigned an integer from 1 to 50. The building at site i (0-based index) was of type kind[i].

With the passing of millennia, Ruritania declined and its building sites were covered in sand, concealing all the buildings. Due to wind and terrain, the depth of the sand varied. The building at site i (0-based index) was buried depth[i] meters below the surface.

Recently, an intrepid archeologist excavated K building sites using a machine that could dig to a maximum depth of D meters. Thus, he only discovered buildings that had been buried at most D meters below the surface.

You are given vector <int>s kind, depth, and found as well as the int K. The types of buildings discovered by the excavation are given by the vector <int> found, which contains at most one value for each building type even if several buildings of a type were excavated.

Return the number of K-tuples of sites that could have been excavated to arrive at the given values. If the given information is not consistent with any configuration of building sites, return 0.


DEFINITION
Class:Excavations
Method:count
Parameters:vector <int>, vector <int>, vector <int>, int
Returns:long long
Method signature:long long count(vector <int> kind, vector <int> depth, vector <int> found, int K)


CONSTRAINTS
-kind will contain N elements, where N is between 1 and 50, inclusive.
-Each element of kind will be between 1 and 50, inclusive.
-depth will contain N elements.
-Each element of depth will be between 1 and 100,000, inclusive.
-found will contain between 1 and 50 elements, inclusive.
-Each element of found will occur in kind at least once.
-The elements of found will be distinct.
-K will be between the number of elements in found and N, inclusive.


EXAMPLES

0)
{1, 1, 2, 2}
{10, 15, 10, 20}
{1}
2

Returns: 3

There are four building sites. Two have buildings of type 1 and two have buildings of type 2. The type 1 buildings are at depths 10 and 15. The type 2 buildings are at depths 10 and 20. The archeologist has excavated two sites and discovered only type 1 buildings. He must have excavated one of three possible pairs of sites:

Sites 0 and 1. The archeologist's machine excavates to a maximum depth D of at least 10.
Sites 0 and 3. The machine excavates to a maximum depth D that falls in the interval [10, 20).
Sites 1 and 3. The machine excavates to a maximum depth that falls in the interval [15, 20).

The other pairs of sites could not have been excavated. For example, the archeologist could not have excavated sites 0 and 2, because he would have found either none or both of the buildings.


1)
{1, 1, 2, 2}
{10, 15, 10, 20}
{1, 2}
2

Returns: 4

The archeologist could have chosen any pair of sites containing a type 1 and a type 2 building. With a large enough value of D, he could have excavated both.


2)
{1, 2, 3, 4}
{10, 10, 10, 10}
{1, 2}
3

Returns: 0

The archeologist cannot have excavated three sites, or else he would have found three types of buildings.

3)
{1, 2, 2, 3, 1, 3, 2, 1, 2}
{12512, 12859, 125, 1000, 99, 114, 125, 125, 114}
{1, 2, 3}
7

Returns: 35



4)
{50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}
{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3}
{50}
18

Returns: 9075135300



*/
// END CUT HERE
#line 97 "Excavations.cpp"
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

typedef long long ll;

const int MAX = 100;

//dp[at][left_k][max_height]
ll dp[MAX][MAX][MAX];
map<int, int> depth_map;
int depth_index;
int K;
vector<int>  kind, depth, found;

class Excavations
{
public:
 long long count(vector <int> _kind, vector <int> _depth, vector <int> _found, int _K)
 {
 //$CARETPOSITION$
    int i, j, k;
    kind = _kind;
    depth = _depth;
    found = _found;
    depth_index = 1;
    depth_map.clear();
    vector<int> vd = depth;
    sort(vd.begin(), vd.end());
    for (i = 0; i < vd.size(); i++) {
        if (depth_map.find(vd[i]) == depth_map.end()) {
            depth_map[vd[i]] = depth_index++;
        }
    }
    for (i = 0; i < depth.size(); i++) depth[i] = depth_map[depth[i]];
    memset(dp, -1, sizeof(dp));
    int at, left_k, max_height;
    dp[0][K][0] = 1;
    for (at = 0; at < found.size(); at++) {
        for (left_k = 0; left_k < K; left_k++) {
            for (max_height = 0; max_height < depth_index) {
                if (dp[at][left_k][max_height] > 0) {
                    vector<int> hlist;
                    for (i = 0; i < kind.size(); i++) {
                        if (kind[i] == found[at]) {
                            hlist.push_back(depth[i]);
                        }
                    }
                    sort(hlist.begin(), hlist.end());
                    int add = 0;
                    for (i = 0; i < hlist.size(); i++) {
                        if (hlist[i] <= max_height) {
                            add ++;
                        } else {
                            break;
                        }
                    }

                    if ((add + left_k > K) || (add == 0)) {
                        continue;
                    }
                        dp[at + 1][add + left_k][cur_height] += dp[at][left_k][max_height];

                    int cur_height = max_height;

                    int next_i = i;
                    for (; i < hlist.size(); i = next_i) {
                        next_i = i;
                        while (next < hlist.size() && hlist[next_i] == hlist[i]) next_i ++;
                    }
                }
            }
        }
    }
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 1, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 15, 10, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; long long Arg4 = 3LL; verify_case(0, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {1, 1, 2, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 15, 10, 20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; long long Arg4 = 4LL; verify_case(1, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {1, 2, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10, 10, 10, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 3; long long Arg4 = 0LL; verify_case(2, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {1, 2, 2, 3, 1, 3, 2, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {12512, 12859, 125, 1000, 99, 114, 125, 125, 114}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 7; long long Arg4 = 35LL; verify_case(3, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {50}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 18; long long Arg4 = 9075135300LL; verify_case(4, Arg4, count(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 Excavations ___test;
 ___test.run_test(-1);
}
// END CUT HERE
