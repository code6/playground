// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
Little Elephant from the Zoo of Lviv has some balls arranged in a row. Each ball can be painted in one of two possible colors: black or white. Initially all the balls are painted white. 




You are given an int M, which represents the number of balls in the row. 
The balls are numbered from left to right, starting from 1. 
You are also given two vector <int>s L and R. 
To repaint balls, Little Elephant wants to use a robot. 
The robot will paint the balls in several consecutive stages.
For each i, the i-th stage (1-based index) will look as follows:
First, the robot will choose one of the two colors: white or black.
Then, the robot will paint the balls with indices from L[i-1] to R[i-1], inclusive, using the chosen color.
(Painting a ball covers all previous layers of paint.)




Return the number of different colorings Little Elephant can get after the last stage. (Two colorings are considered different if there exists some ball that is white in one coloring and black in the other one).


DEFINITION
Class:LittleElephantAndIntervalsDiv1
Method:getNumber
Parameters:int, vector <int>, vector <int>
Returns:long long
Method signature:long long getNumber(int M, vector <int> L, vector <int> R)


CONSTRAINTS
-M will be between 1 and 1,000, inclusive. 
-L will contain between 1 and 50 elements, inclusive.
-R will contain the same number of elements as L.
-Each element of R will be between 1 and M, inclusive.
-i-th element of L will be between 1 and R[i], inclusive.


EXAMPLES

0)
4
{1, 2, 3}
{1, 2, 3}

Returns: 8

In the three stages the robot will choose the color for balls number 1, 2, and 3. The choices are independent of each other. The last, fourth ball will always remain white. Thus there are 2*2*2 = 8 different colorings.

1)
3
{1, 1, 2}
{3, 1, 3}

Returns: 4



2)
1000
{47}
{747}

Returns: 2



3)
42
{5, 23, 4, 1, 15, 2, 22, 26, 13, 16, 28, 13, 27, 9, 18, 4, 10, 3, 4, 4, 3, 4, 1, 18, 18, 2, 38, 4, 10, 12, 3, 30, 11, 38, 2, 13, 1, 13, 18, 16, 13, 2, 14, 27, 13, 3, 26, 19, 5, 10}
{30, 41, 17, 1, 21, 6, 28, 30, 15, 19, 31, 28, 35, 27, 30, 13, 31, 5, 8, 25, 40, 10, 3, 26, 23, 9, 40, 8, 40, 23, 12, 37, 35, 39, 11, 34, 10, 21, 22, 21, 24, 5, 39, 27, 17, 16, 26, 35, 25, 36}

Returns: 256



*/
// END CUT HERE
#line 83 "LittleElephantAndIntervalsDiv1.cpp"
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

string tostring( int v) {
    string ret = "";
    while (v) {
        ret += (v % 10) + '0';
        v /= 10;
    }
    range(i, ret.size() / 2) swap(ret[i], ret[ret.size() - 1 - i]);
    return ret;
}

class LittleElephantAndIntervalsDiv1
{
public:
 long long getNumber(int M, vector <int> L, vector <int> R)
 {
 //$CARETPOSITION$
    vector<int> vc;
    vc.resize(M + 5);
    int col = 0;
    range(i, L.size()) {
        col++;
        for (int j = L[i]; j <= R[i]; j++) {
            vc[j] = col;
        }
    }
    set<int> sc;
    range(i, M + 5) {
        if (vc[i] > 0) sc.insert(vc[i]);
    }
    return two(sc.size());
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const long long &Expected, const long long &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 4; int Arr1[] = {1, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1, 2, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 8LL; verify_case(0, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_1() { int Arg0 = 3; int Arr1[] = {1, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {3, 1, 3}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 4LL; verify_case(1, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_2() { int Arg0 = 1000; int Arr1[] = {47}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {747}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 2LL; verify_case(2, Arg3, getNumber(Arg0, Arg1, Arg2)); }
	void test_case_3() { int Arg0 = 42; int Arr1[] = {5, 23, 4, 1, 15, 2, 22, 26, 13, 16, 28, 13, 27, 9, 18, 4, 10, 3, 4, 4, 3, 4, 1, 18, 18, 2, 38, 4, 10, 12, 3, 30, 11, 38, 2, 13, 1, 13, 18, 16, 13, 2, 14, 27, 13, 3, 26, 19, 5, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {30, 41, 17, 1, 21, 6, 28, 30, 15, 19, 31, 28, 35, 27, 30, 13, 31, 5, 8, 25, 40, 10, 3, 26, 23, 9, 40, 8, 40, 23, 12, 37, 35, 39, 11, 34, 10, 21, 22, 21, 24, 5, 39, 27, 17, 16, 26, 35, 25, 36}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); long long Arg3 = 256LL; verify_case(3, Arg3, getNumber(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 LittleElephantAndIntervalsDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
