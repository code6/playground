// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// There is an infinitely long straight road.
Fox Ciel is going to plant trees of three kinds: apple trees, kiwi trees, and grape trees.
There will be infinitely many trees of each kind.
Trees of each kind will be placed along the entire road in regular intervals.


More precisely, you are given ints apple, kiwi, and grape with the following meaning:
The distance between any two consecutive apple trees must be apple, the distance between any two consecutive kiwi trees must be kiwi, and the distance between any two consecutive grape trees must be grape.


Ciel can only plant the trees at integer coordinates, but she gets to choose those coordinates as long as the above conditions are satisfied.
In other words, Ciel gets to choose three integers x, y, and z such that:

She plants apple trees at coordinates ..., x - 2 * apple, x - apple, x, x + apple, x + 2 * apple, ...
She plants kiwi trees at coordinates ..., y - 2 * kiwi, y - kiwi, y, y + kiwi, y + 2 * kiwi, ...
She plants grape trees at coordinates ..., z - 2 * grape, z - grape, z, z + grape, z + 2 * grape, ...

Ciel wants to maximize the distance between two closest trees (of any kind).
Return this distance.

DEFINITION
Class:FruitTrees
Method:maxDist
Parameters:int, int, int
Returns:int
Method signature:int maxDist(int apple, int kiwi, int grape)


CONSTRAINTS
-apple will be between 1 and 2,000, inclusive.
-kiwi will be between 1 and 2,000, inclusive.
-grape will be between 1 and 2,000, inclusive.


EXAMPLES

0)
1
5
8

Returns: 0

Apple trees will be planted at all integer coordinates, so at least two trees will be planted where a kiwi tree is planted.

1)
3
3
6

Returns: 1

One of the optimal solutions is as follows:

Plant apple trees at ..., -5, -2, 1, 4, ...
Plant kiwi trees at ..., -4, -1, 2, 5, ...
Plant grape trees at ..., -9, -3, 3, 9, ...




2)
40
30
20

Returns: 5



3)
899
1073
1147

Returns: 14



4)
2000
2000
2000

Returns: 666



*/
// END CUT HERE
#line 95 "FruitTrees.cpp"
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
const int INF = 100000000;

typedef pair<int, int> PII;
typedef pair<PII, int> PIII;

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int calc(int v0, int x0, int v1, int x1) {
    if (v0 < v1) {
        swap(v0, v1);
        swap(x0, x1);
    }
    int x2 = ((x1 - x0) % v1 + v1) % v1;
    int g = gcd(v0, v1);
    int ret = min(x2 % g, g - x2 % g);
    return ret;
}

class FruitTrees
{
    public:
        int maxDist(int apple, int kiwi, int grape)
        {
            //$CARETPOSITION$
            //ax + x0
            //by + y0
            //cz + z0
            int ret = 0;
            for (int x0 = 0; x0 <=0 ; x0++) 
                for (int y0 = -kiwi; y0 < kiwi; y0++) {
                    for (int z0 = -grape; z0 < grape; z0++) {
                        int tmp = INF;
                        tmp = min(tmp, calc(apple, x0, kiwi, y0));
                        tmp = min(tmp, calc(apple, x0, grape, z0));
                        tmp = min(tmp, calc(kiwi, y0, grape, z0));
                        if (ret < tmp) {
                            ret = max(ret, tmp);
                        }
                    }
                }
            return ret;
        }

        // BEGIN CUT HERE
    public:
        void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
    private:
        template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
        void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
        void test_case_0() { int Arg0 = 10; int Arg1 = 30; int Arg2 = 60; int Arg3 = 0; verify_case(0, Arg3, maxDist(Arg0, Arg1, Arg2)); }
        void test_case_1() { int Arg0 = 3; int Arg1 = 3; int Arg2 = 6; int Arg3 = 1; verify_case(1, Arg3, maxDist(Arg0, Arg1, Arg2)); }
        void test_case_2() { int Arg0 = 40; int Arg1 = 30; int Arg2 = 20; int Arg3 = 5; verify_case(2, Arg3, maxDist(Arg0, Arg1, Arg2)); }
        void test_case_3() { int Arg0 = 899; int Arg1 = 1073; int Arg2 = 1147; int Arg3 = 14; verify_case(3, Arg3, maxDist(Arg0, Arg1, Arg2)); }
        void test_case_4() { int Arg0 = 2000; int Arg1 = 2000; int Arg2 = 2000; int Arg3 = 666; verify_case(4, Arg3, maxDist(Arg0, Arg1, Arg2)); }

        // END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
    FruitTrees ___test;
    ___test.run_test(-1);
}
// END CUT HERE
