// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Note that the return value is a floating-point number and that in this problem the allowed absolute or relative error has been increased to 1e-6.

This problem takes place in a plane.
Nikola works at a radio station that is located in the point (0, 0).
You can hear the station if and only if you are within a circle with center at (0, 0) and some unknown radius.

There are some cities near the station.
Each city has the shape of a circle with some positive integer radius.
Cities may partially or even completely overlap each other, and some of them may contain the radio station.
You are given the description of all cities as vector <int>s X, Y, and R.
For each valid i, there is a city with center at (X[i], Y[i]) and radius R[i].

The radius of our radio station is bad if there is a city that is only partially covered by the radio signal.
Otherwise, the radius is good.
In other words, if there is a point in a city where you can listen to our radio and another point in the same city where you cannot do so, the radius is bad.
A radius is good if and only if each city is either covered completely by radio signal, or not covered at all.

You are given a int Z.
The radius of our radio station is a real number chosen uniformly at random from the range [0, Z].
Return the probability that the radius is good.

DEFINITION
Class:RadioRange
Method:RadiusProbability
Parameters:vector <int>, vector <int>, vector <int>, int
Returns:double
Method signature:double RadiusProbability(vector <int> X, vector <int> Y, vector <int> R, int Z)


NOTES
-Your return value must have an absolute or relative error less than 1e-6.


CONSTRAINTS
-X will contain between 1 and 100 elements, inclusive.
-X, Y, and R will each contain the same number of elements.
-Each element of X will be between -10^9 and 10^9, inclusive.
-Each element of Y will be between -10^9 and 10^9, inclusive.
-Each element of R will be between 1 and 10^9, inclusive.
-Z will be between 1 and 10^9, inclusive.


EXAMPLES

0)
{0}
{0}
{5}
10

Returns: 0.5

Our radio station is in the center of a city with radius 5, and we are choosing the radius for the station uniformly at random from [0,10].
Radii in [0,5) are all bad, because people in the center of the city can hear our radio but people on its boundary cannot.
Radii in [5,10] are all good, as the entire city is covered.
Hence, the probability of having a good radius is 5/10 = 0.5.

1)
{0}
{0}
{10}
10

Returns: 0.0

Our radio station is in the center of a city with radius 10, and we are choosing the radius for the station uniformly at random from [0,10].
In this case, the only good radius is 10, but the probability that it will be chosen is zero.

2)
{10}
{10}
{10}
10

Returns: 0.4142135623730951

The center of the city is at (10, 10) and its radius is 10.
The good radii for our station are those where the city is not covered at all.
These are the radii from 0 to approximately 4.14.

3)
{11, -11, 0, 0}
{0, 0, 11, -11}
{10, 10, 10, 10}
31

Returns: 0.3548387096774194

Here we have four cities.
They are located to the north, south, east, and west of the station.
A radius is good if it lies in [0,1) or in [21,31].

4)
{100}
{100}
{1}
10

Returns: 1.0

It is possible that some cities will not be covered even if the radius of our radio station is Z.

5)
{1000000000}
{1000000000}
{1000000000}
1000000000

Returns: 0.41421356237309503



6)
{20, -20, 0, 0}
{0, 0, 20, -20}
{50, 50, 50, 50}
100

Returns: 0.3



7)
{0, -60, -62, -60, 63, -97}
{-72, 67, 61, -8, -32, 89}
{6, 7, 8, 7, 5, 6}
918

Returns: 0.9407071068962471



*/
// END CUT HERE
#line 139 "RadioRange.cpp"
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

typedef long long ll;
typedef pair<ll, ll> PLL;

class RadioRange
{
public:
 double RadiusProbability(vector <int> X, vector <int> Y, vector <int> R, int Z)
 {
 //$CARETPOSITION$
    int n = X.size();
    double b0, b1;
    vector<double> vp, v0, v1;
    b0 = Z;
    b1= 0;
    double r0, r1;
    range(i, n) {
        ll x = X[i];
        ll y = Y[i];
        ll r = R[i];
        if (x * x + y * y  <= r * r) {
             r0 = 0;
             r1 = r + sqrt(1.0 * y * y + x * x);
        } else {
            r0 = sqrt(1.0 * y * y + x * x) - r;
            r1 = r0 + 2 * r;
        }
        r0 = min(r0, Z*1.0);
        r1 = min(r1, Z*1.0);
        v0.pb(r0);
        v1.pb(r1);
        vp.pb(r0);
        vp.pb(r1);
    }
    vp.pb(0);
    vp.pb(Z);
    sort(all(vp));
    double ans = 0.0;
    range(i, vp.size()) {
        if (i == 0) continue;
        bool ok = true;
        double f1 = vp[i - 1];
        double f2 = vp[i];
   //     cout << f1 << ' ' << f2 << endl;
        range(j, n) {
            if (!(f2 < v0[j] + 1e-7 || f1 > v1[j] - 1e-7))  {
   //             cout << f1 << ' ' << f2 << ' ' << v0[j] << ' ' << v1[j] << endl;
                ok = false;
                break;
            }
        }
        if (ok) ans += f2 -f1;
    }
    ans /= Z;
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); if ((Case == -1) || (Case == 7)) test_case_7(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {5}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; double Arg4 = 0.5; verify_case(0, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_1() { int Arr0[] = {0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; double Arg4 = 0.0; verify_case(1, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_2() { int Arr0[] = {10}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; double Arg4 = 0.4142135623730951; verify_case(2, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_3() { int Arr0[] = {11, -11, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 11, -11}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {10, 10, 10, 10}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 31; double Arg4 = 0.3548387096774194; verify_case(3, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_4() { int Arr0[] = {100}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 10; double Arg4 = 1.0; verify_case(4, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_5() { int Arr0[] = {1000000000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1000000000}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {1000000000}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1000000000; double Arg4 = 0.41421356237309503; verify_case(5, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_6() { int Arr0[] = {20, -20, 0, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 20, -20}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {50, 50, 50, 50}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 100; double Arg4 = 0.3; verify_case(6, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }
	void test_case_7() { int Arr0[] = {0, -60, -62, -60, 63, -97}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-72, 67, 61, -8, -32, 89}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = {6, 7, 8, 7, 5, 6}; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 918; double Arg4 = 0.9407071068962471; verify_case(7, Arg4, RadiusProbability(Arg0, Arg1, Arg2, Arg3)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 RadioRange ___test;
 ___test.run_test(-1);
}
// END CUT HERE
