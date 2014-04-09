// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
For non-negative integers A and B, let A&B denote the bitwise AND operation.
That is, for each i, the i-th bit of A&B in binary representation is 1 if and only if the i-th bits of A and B are 1.



We call a set of non-negative integers S cool if the following conditions are satisfied.


For any two distinct elements A, B in S, A&B > 0.
For any three distinct elements A, B, C in S, A&B&C = 0.



You are given a vector<long long> subset and an int N.
All elements in subset are distinct.
Compute a cool set with N distinct elements such that the cool set contains each element of subset and each element is between 1 and 2^60 - 1, inclusive.
Return one such cool set as a vector<long long> with elements in increasing order.
If there are multiple solutions, return the lexicographically smallest one.
If there are no such cool sets, return an empty vector<long long> instead.




DEFINITION
Class:BitwiseAnd
Method:lexSmallest
Parameters:vector<long long>, int
Returns:vector<long long>
Method signature:vector<long long> lexSmallest(vector<long long> subset, int N)


CONSTRAINTS
-N will be between 3 and 50, inclusive.
-subset will contain between 0 and N elements, inclusive.
-Each element of subset will be between 1 and 2^60 - 1, inclusive.
-All the elements in subset will be distinct.
-Elements in subset will be sorted in increasing order.


EXAMPLES

0)
{14, 20}
3

Returns: {14, 18, 20 }

There are several possible cool sets.
For example, the following sets are cool and each of them contains all the elements of subset.

{14, 18, 20}
{14, 20, 26}
{14, 20, 50}
...
  
Among these sets, the first one is the lexicographically smallest one.



1)
{11, 17, 20}
4

Returns: { }

There is no cool set because (11&20) equals 0.

2)
{99, 157}
4

Returns: {99, 157, 262, 296 }



3)
{1152921504606846975}
3

Returns: { }

The element in subset equals to 2^60-1.
Note that each element of your cool set should be less than or equal to 2^60-1. 

4)
{}
5

Returns: {15, 113, 402, 676, 840 }



5)
{1, 3, 5, 7, 9, 11}
6

Returns: { }



*/
// END CUT HERE
#line 108 "BitwiseAnd.cpp"
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
typedef long long ll;

class BitwiseAnd
{
public:
 vector<long long> lexSmallest(vector<long long> subset, int N)
 {
 //$CARETPOSITION$
    vector<ll> ret;
    if (subset.size() == 0) {
        subset.pb(two(N-1) - 1);

    }
    int M = subset.size();
    range(i, M) {
        range(j, i) {
            if ((subset[i] & subset[j]) == 0) {
                return ret;
            }
            range(k, j) {
                if ((subset[i] & subset[j] & subset[k]) > 0) {
                    return ret;
                }
            }
        }
    }

    ll LIMIT = two(60) - 1;

    while (M < N) {
        ll cur = 0;
        vector<ll> offer;
        range(i, M) {
            ll bad = 0;
            range(j, M) {
                if (i == j) continue;
                bad |= subset[i] & subset[j];
            }
            ll good = subset[i] & (~bad) & LIMIT;
            offer.pb(good);
        }
        range(ct, M) {
            int high;
            for (high = 0; high <= 60; high++) {
                bool flag = true;
                range(i, M) {
                    if (offer[i] & cur) continue;
                    if (!(offer[i] & (~cur) & (two(high) - 1))) {
                        flag = false;
                        break;
                    }
                }
                if (flag) {
                    break;
                }
            }
            if (high > 60)  {
                return ret;
            } else {
                cur |= two(high - 1);
            }
        }

        if (M < N - 1) {
            ll all = 0;
            int left = N - 1 - M;
            range(i, M) {
                all |= subset[i];
            }
            range(i, 61) {
                if (!(two(i) & all)) {
                    cur |= two(i);
                    left --;
                    if (!left) break;
                }
            }
            if (left) return ret;
        }
        subset.pb(cur);
        M++;
    }
    sort(subset.begin(), subset.end());

    return subset;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector<long long> &Expected, const vector<long long> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { long Arr0[] = {14, 20}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long Arr2[] = {14, 18, 20 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(0, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {11, 17, 20}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long Arr2[] = { }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(1, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_2() { long Arr0[] = {99, 157}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 4; long Arr2[] = {99, 157, 262, 296 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(2, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {1152921504606846975}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; long Arr2[] = { }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(3, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_4() { long Arr0[] = {}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; long Arr2[] = {15, 113, 402, 676, 840 }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(4, Arg2, lexSmallest(Arg0, Arg1)); }
	void test_case_5() { long Arr0[] = {1, 3, 5, 7, 9, 11}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; long Arr2[] = { }; vector<long long> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); verify_case(5, Arg2, lexSmallest(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 BitwiseAnd ___test;
 ___test.run_test(-1);
}
// END CUT HERE
