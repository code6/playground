// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
Alien Fred wants to destroy the Earth.
But before he does that, he wants to eat some hamburgers.




You are given two vector <int>s: type and taste.
They describe all hamburgers available in the shop he found.
Each hamburger has a type (some positive integer) and a taste (some, possibly negative, integer).
For each i, type[i] represents the type of i-th hamburger (0-based index), and taste[i] represents the taste of i-th hamburger.
It is possible that different hamburgers have the same type but a different taste.




Fred wants to eat some subset of those hamburgers (possibly none or all of them).
Eating the chosen hamburgers will give him some amount of joy.
This amount can be computed as Y * A, where Y is the number of different types of hamburgers eaten, and A is their total taste.




Return the largest possible amount of joy he can get.


DEFINITION
Class:AlienAndHamburgers
Method:getNumber
Parameters:vector <int>, vector <int>
Returns:int
Method signature:int getNumber(vector <int> type, vector <int> taste)


CONSTRAINTS
-type will contain between 1 and 50 elements, inclusive.
-type and taste will contain the same number of elements.
-Each element of type will be between 1 and 100, inclusive.
-Each element of taste will be between -100,000 and 100,000, inclusive.


EXAMPLES

0)
{1, 2}
{4, 7}

Returns: 22

In this case, the best choice is to choose both hamburgers. The number of different types is 2, and the total taste is 11. Thus, the answer is 2*11 = 22.

1)
{1, 1}
{-1, -1}

Returns: 0

Note that sometimes the best choice is not to eat any hamburgers. In such a case the amount of joy is 0.

2)
{1, 2, 3}
{7, 4, -1}

Returns: 30



3)
{1, 2, 3, 2, 3, 1, 3, 2, 3, 1, 1, 1}
{1, 7, -2, 3, -4, -1, 3, 1, 3, -5, -1, 0}

Returns: 54



4)
{30, 20, 10}
{100000, -100000, 100000}

Returns: 400000



*/
// END CUT HERE
#line 90 "AlienAndHamburgers.cpp"
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

class AlienAndHamburgers
{
public:
 int getNumber(vector <int> type, vector <int> taste)
 {
 //$CARETPOSITION$
    int ret = 0;
    int n = type.size();
    map<int, int> p, q;
    range(i, n) {
        int ty = type[i];
        if (taste[i] >= 0) {
            p[ty] = p[ty] + taste[i];
        } else {
            if (q.find(ty) == q.end()) {
                q[ty] = taste[i];
            } else {
                q[ty] = max(q[ty], taste[i]);
            }
        }
    }

    int A = 0;
    int Y = 0;
    for (map<int, int>::iterator it = p.begin(); it != p.end(); it++) {
        A += it->sc;
        Y ++;
    }

    vector<int> le;
    for (map<int, int>::iterator it = q.begin(); it != q.end(); it++) {
        if (p.find(it->fs) != p.end()) {
            continue;
        } else {
            le.pb(it->sc);
        }
    }
    sort(all(le));
    ret = max(ret, Y * A);
    range(i, le.size()) {
        int at = le.size() - 1 - i;
        A += le[at];
        Y ++;
        ret = max(ret, Y * A);
    }

    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {4, 7}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 22; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {1, 2, 3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 4, -1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 30; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1, 2, 3, 2, 3, 1, 3, 2, 3, 1, 1, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 7, -2, 3, -4, -1, 3, 1, 3, -5, -1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 54; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {30, 20, 10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100000, -100000, 100000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 400000; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 AlienAndHamburgers ___test;
 ___test.run_test(-1);
}
// END CUT HERE
