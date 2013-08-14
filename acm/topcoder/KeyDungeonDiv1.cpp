// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You are exploring a dungeon.
In the dungeon you found some locked doors.
Each locked door has some red and some green keyholes (zero or more of each kind).
In order to open a door, you must insert fitting keys into all its keyholes simultaneously.
All the keys used to open a door break in the process of opening it and you have to throw them away.
However, each door hides a small chamber that contains some new keys for you.
Once you open the door, you may take all of those keys and possibly use them to open new doors.
(Of course, it only makes sense to open each door at most once. If you open the same door again, there will be no new keys for you.) 

There are three kinds of keys: red, green, and white ones.
Each red key fits into any red keyhole.
Each green key fits into any green keyhole.
Each white key fits into any keyhole (both red and green ones). 

You are given vector <int>s doorR, doorG, roomR, roomG, and roomW.
These five vector <int>s all have the same length.
For each valid i, the values at index i describe one of the doors you found:
the door has doorR[i] red and doorG[i] green keyholes, and upon opening it you gain new keys: roomR[i] red ones, roomG[i] green ones, and roomW[i] white ones. 

You are also given the vector <int> keys with three elements:
keys[0] is the number of red keys, keys[1] the number of green keys, and keys[2] the number of white keys you have at the beginning. 

Your goal is to have as many keys as possible at the moment when you decide to stop opening doors.
(The colors of the keys do not matter.)
You are allowed to open the doors in any order you like, and to choose the keys used to open each of the doors.
You are also allowed to stop opening doors whenever you are satisfied with your current number of keys.
Compute and return the maximal total number of keys you can have at the end.

DEFINITION
Class:KeyDungeonDiv1
Method:maxKeys
Parameters:vector <int>, vector <int>, vector <int>, vector <int>, vector <int>, vector <int>
Returns:int
Method signature:int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)


CONSTRAINTS
-doorR, doorG, roomR, roomG and roomW will each contain between 1 and 12 elements, inclusive.
-doorR, doorG, roomR, roomG and roomW will contain the same number of elements.
-Each element of doorR, doorG, roomR, roomG and roomW will be between 0 and 10, inclusive.
-keys will contain exactly 3 elements.
-Each element of keys will be between 0 and 10, inclusive.


EXAMPLES

0)
{1, 2, 3}
{0, 4, 9}
{0, 0, 10}
{0, 8, 9}
{1, 0, 8}
{3, 1, 2}

Returns: 8

First you have 3 red keys, 1 green key, 2 white keys. You can end with 8 keys as follows:


First, you open door 0 using 1 red key. From the opened chamber you gain 1 white key, so currently you have 2 red keys, 1 green key, and 3 white keys.


Second, you open door 1 using 2 red keys, 1 green key, and 3 white keys (all of them into green locks). Immediately after opening the door you have no keys: all the ones you had were just used and thus they broke. However, the chamber you just opened contains 8 green keys.


You can't end with more than 8 keys, so you should return 8.

1)
{1, 1, 1, 2}
{0, 2, 3, 1}
{2, 1, 0, 4}
{1, 3, 3, 1}
{1, 0, 2, 1}
{0, 4, 0}

Returns: 4

You have only green keys, while each door has at least 1 red keyhole. So you cannot open any of the doors.

2)
{2, 0, 4}
{3, 0, 4}
{0, 0, 9}
{0, 0, 9}
{8, 5, 9}
{0, 0, 0}

Returns: 27

Initially you have no key at all, but door 1 also has no key hole. Therefore, you can start by opening door 1.

3)
{5, 3, 0, 0}
{0, 1, 2, 1}
{0, 9, 2, 4}
{2, 9, 2, 0}
{0, 9, 1, 1}
{1, 1, 0}

Returns: 32



4)
{9,5,10,8,4,3,0,8,4,1,3,9}
{9,10,0,8,9,4,3,8,1,8,10,4}
{1,2,0,2,3,3,5,3,1,3,0,5}
{5,2,5,0,5,2,3,4,0,0,5,2}
{1,5,1,2,0,4,4,0,3,3,1,3}
{5,0,1}

Returns: 16


keys equal
white keys not know?

state current_at 
2^12   12 

dp[state][current_at] store max white key we can have

*/




// END CUT HERE
#line 122 "KeyDungeonDiv1.cpp"
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
const int MAX = 5000;

int add[MAX][3];
int dp[MAX][150];
int n;

class KeyDungeonDiv1
{
public:
 int maxKeys(vector <int> doorR, vector <int> doorG, vector <int> roomR, vector <int> roomG, vector <int> roomW, vector <int> keys)
 {
 //$CARETPOSITION$
    n = doorR.size();
    range(i, two(n)) {
        add[i][0] = keys[0];
        add[i][1] = keys[1];
        add[i][2] = keys[2];
        range(k, n) {
            if (two(k) & i) {
                add[i][0] -= doorR[k];
                add[i][1] -= doorG[k];

                add[i][0] += roomR[k];
                add[i][1] += roomG[k];
                add[i][2] += roomW[k];
            }
        }
    }

    int totalA = keys[0];
    range(i, n) totalA += roomR[i];
    totalA += 5;

    memset(dp, -1, sizeof(dp));
    dp[0][keys[0]] = keys[2];
    range(i, two(n)) {
        range(j, totalA) {
            if (dp[i][j] != -1) {
                range(k, n) {
                    if (((two(k) & i) == 0)) {
                        int val[3], need[3];
                        int sum_v = add[i][0] + add[i][1] + add[i][2];
                        val[0] = j;
                        val[2] = dp[i][j];
                        val[1] = sum_v - val[0] - val[2];
                        need[0] = doorR[k];
                        need[1] = doorG[k];
                        int left = val[2] - (max(need[0] - val[0], 0) + max(need[1] - val[1], 0));
                        if (left >= 0) {
                            int next_j = max(val[0] - need[0], 0) + roomR[k];
                            int next_i = i | two(k);
                            dp[next_i][next_j] = max(dp[next_i][next_j], left + roomW[k]);
                        }
                    }
                }
            }
        }
    }

    int ans = 0;
    range(i, two(n)) {
        range(j, totalA) {
            if (dp[i][j] >= 0) {
                ans = max(ans, add[i][0] + add[i][1] + add[i][2]);
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
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 4, 9}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 0, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 8, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0, 8}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {3, 1, 2}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 8; verify_case(0, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_1() { int Arr0[] = {1, 1, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 2, 3, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {2, 1, 0, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {1, 3, 3, 1}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1, 0, 2, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 4, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 4; verify_case(1, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_2() { int Arr0[] = {2, 0, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {3, 0, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 0, 9}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {0, 0, 9}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {8, 5, 9}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {0, 0, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 27; verify_case(2, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_3() { int Arr0[] = {5, 3, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 1, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {0, 9, 2, 4}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {2, 9, 2, 0}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {0, 9, 1, 1}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {1, 1, 0}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 32; verify_case(3, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }
	void test_case_4() { int Arr0[] = {9,5,10,8,4,3,0,8,4,1,3,9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {9,10,0,8,9,4,3,8,1,8,10,4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1,2,0,2,3,3,5,3,1,3,0,5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = {5,2,5,0,5,2,3,4,0,0,5,2}; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arr4[] = {1,5,1,2,0,4,4,0,3,3,1,3}; vector <int> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); int Arr5[] = {5,0,1}; vector <int> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); int Arg6 = 16; verify_case(4, Arg6, maxKeys(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 KeyDungeonDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
