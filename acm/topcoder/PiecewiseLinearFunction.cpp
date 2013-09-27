// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// F is a function that is defined on all real numbers from the closed interval [1,N].
You are given a vector <int> Y with N elements.
For each i (1 <= i <= N) we have F(i) = Y[i-1].
Additionally, you know that F is piecewise linear: for each i, on the interval [i,i+1] F is a linear function.
The function F is uniquely determined by this information.
For example, if F(4)=1 and F(5)=6 then we must have F(4.7)=4.5.

As another example, this is the plot of the function F for Y = {1, 4, -1, 2}.



Given a real number y, we can count the number of solutions to the equation F(x)=y.
For example, for the function plotted above there are 0 solutions for y=7, there is 1 solution for y=4, and there are 3 solutions for y=1.1.
We are looking for the largest number of solutions such an equation can have.
For the function plotted above the answer would be 3: there is no y such that F(x)=y has more than 3 solutions.

If there is an y such that the equation F(x)=y has infinitely many solutions, return -1.
Otherwise, return the maximum possible number of solutions such an equation may have.


DEFINITION
Class:PiecewiseLinearFunction
Method:maximumSolutions
Parameters:vector <int>
Returns:int
Method signature:int maximumSolutions(vector <int> Y)


CONSTRAINTS
-Y will contain between 2 and 50 elements, inclusive.
-Each element of Y will be between -1,000,000,000 and 1,000,000,000, inclusive.


EXAMPLES

0)
{3, 2}

Returns: 1

The graph of this function is a line segment between (1, 3) and (2, 2). For any y such that 2 ? y ? 3 the equation F(x)=y has 1 solution, and for any other y it has 0 solutions.

1)
{4, 4}

Returns: -1

The function's plot is a horizontal line segment between points (1, 4) and (2, 4). For y=4, F(x)=y has infinitely many solutions.

2)
{1, 4, -1, 2}

Returns: 3

This is the example from the problem statement. Three solutions are obtained for any value of y between 1 and 2, inclusive:



3)
{2, 1, 2, 1, 3, 2, 3, 2}

Returns: 5



4)
{125612666, -991004227, 0, 6, 88023, -1000000000, 1000000000, -1000000000, 1000000000}

Returns: 6



*/
// END CUT HERE
#line 79 "PiecewiseLinearFunction.cpp"
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
typedef long long ll;

int check(vector<int> Y, double v) {
    int tmp = 0;
    range(j, Y.size()) {
        if (j == 0) {
            tmp += fabs(v- Y[j]) < 1e-9;
        } else {
            if (fabs(v- Y[j]) < 1e-9) {
                tmp ++;
            } else {
                tmp += (v - Y[j - 1]) * (v - Y[j]) < 0;
            }
        }
    }
    return tmp;
}

class PiecewiseLinearFunction
{
public:
 int maximumSolutions(vector <int> Y)
 {
 //$CARETPOSITION$
    int ans = 0;
    range(i, Y.size()) {
        if (i && Y[i] == Y[i -1]) {
            return -1;
        }
        ans = max(ans, check(Y, Y[i]));
        ans = max(ans, check(Y, Y[i] + 0.5));
        ans = max(ans, check(Y, Y[i] - 0.5));
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(0, Arg1, maximumSolutions(Arg0)); }
	void test_case_1() { int Arr0[] = {4, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = -1; verify_case(1, Arg1, maximumSolutions(Arg0)); }
	void test_case_2() { int Arr0[] = {1, 4, -1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(2, Arg1, maximumSolutions(Arg0)); }
	void test_case_3() { int Arr0[] = {2, 1, 2, 1, 3, 2, 3, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(3, Arg1, maximumSolutions(Arg0)); }
	void test_case_4() { int Arr0[] = {125612666, -991004227, 0, 6, 88023, -1000000000, 1000000000, -1000000000, 1000000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(4, Arg1, maximumSolutions(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 PiecewiseLinearFunction ___test;
 ___test.run_test(-1);
}
// END CUT HERE
