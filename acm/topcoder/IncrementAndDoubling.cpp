// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
You have an array with N elements.
Initially, each element is 0.
You can perform the following operations:



Increment operation: Choose one element of the array and increment the value by one.
Doubling operation: Double the value of each element.



You are given a vector <int> desiredArray containing N elements.
Compute and return the smallest possible number of operations needed to change the array from all zeros to desiredArray.


DEFINITION
Class:IncrementAndDoubling
Method:getMin
Parameters:vector <int>
Returns:int
Method signature:int getMin(vector <int> desiredArray)


CONSTRAINTS
-desiredArray will contain between 1 and 50 elements, inclusive.
-Each element of desiredArray will be between 0 and 1,000, inclusive.


EXAMPLES

0)
{2, 1}

Returns: 3

One of the optimal solutions is to apply increment operations to element 0 twice and then to element 1 once.
Total number of operations is 3.



1)
{16, 16, 16}

Returns: 7

The optimum solution looks as follows.
First, apply an increment operation to each element.
Then apply the doubling operation four times.
Total number of operations is 3+4=7.



2)
{100}

Returns: 9



3)
{0, 0, 1, 0, 1}

Returns: 2

Some elements in desiredArray may be zeros.

4)
{123, 234, 345, 456, 567, 789}

Returns: 40



5)
{7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7}

Returns: 84



*/
// END CUT HERE
#line 88 "IncrementAndDoubling.cpp"
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

class IncrementAndDoubling
{
public:
 int getMin(vector <int> desiredArray)
 {
 //$CARETPOSITION$
    int ans = 0;
    int n = desiredArray.size();
    while (true) {
        bool flag = false;
        range(i, n) {
            if (desiredArray[i] % 2) {
                ans++;
                desiredArray[i] --;
            }
            if (desiredArray[i] > 0) {
                flag = true;
            }
        }
        if (flag) {
            range(i, n) desiredArray[i] /= 2;
            ans ++;
        } else {
            break;
        }
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { int Arr0[] = {16, 16, 16}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 9; verify_case(2, Arg1, getMin(Arg0)); }
	void test_case_3() { int Arr0[] = {0, 0, 1, 0, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; verify_case(3, Arg1, getMin(Arg0)); }
	void test_case_4() { int Arr0[] = {123, 234, 345, 456, 567, 789}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 40; verify_case(4, Arg1, getMin(Arg0)); }
	void test_case_5() { int Arr0[] = {7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 84; verify_case(5, Arg1, getMin(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 IncrementAndDoubling ___test;
 ___test.run_test(-1);
}
// END CUT HERE
