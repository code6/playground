// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// TypoCoder is a programming contest like TopCoder.
TypoCoder also has a rating system.
There are two types of coders in TypoCoder: brown coders and ciel coders.
A brown coder is a coder whose rating is greater than or equal to 2200.
A ciel coder is a coder whose rating is less than 2200.

Cat Lower competes in TypoCoder.
He is currently a ciel coder.
His rating at the end of the current year is X.

Next year there will be some contests.
In each of those contests, Cat Lower can either try his best or lose on purpose.
For each i, the i-th contest (0-based index) has weight D[i].
If Cat Lower tries his best in the i-th contest, his rating will increase by D[i].
If he decides to lose on purpose instead, his rating will decrease by D[i], but not below zero.
Formally, his rating will decrease by min(D[i],his rating before the contest).

Cat Lower loves being a ciel coder.
Therefore, he must never be a brown coder twice in a row.
That is, whenever Cat Lower becomes a brown coder, he must be ciel again after the next contest (if there are any contests left).

TypoCoder awards "Chameleon coder of the year" to the coder whose color changed the most times during the year.

You are given the vector <int> D and the int X.
Return the maximal number of color changes Cat Lower can have next year.


DEFINITION
Class:TypoCoderDiv1
Method:getmax
Parameters:vector <int>, int
Returns:int
Method signature:int getmax(vector <int> D, int X)


CONSTRAINTS
-D will contain between 1 and 50 elements, inclusive.
-Each element of D will be between 0 and 1,000,000,000 (10^9), inclusive.
-X will be between 0 and 2199, inclusive.


EXAMPLES

0)
{100,200,100,1,1}
2000

Returns: 3

When he increase at the second, the third and the last competition and decrease at the first and the fourth competition, he can change the color 3 times and this is the maximal.

1)
{0,0,0,0,0}
2199

Returns: 0

He cannot be a brown coder in this case.

2)
{90000,80000,70000,60000,50000,40000,30000,20000,10000}
0

Returns: 1

Note that Cat Lower always has at least one valid strategy: if he decides to lose in all contests, he will remain ciel forever.
In this test case, the optimal strategy for him is to lose in the first eight contests and then to win in the last one.
Note that before the last contest his rating will be 0.

3)
{1000000000,1000000000,10000,100000,2202,1}
1000

Returns: 4



4)
{2048,1024,5012,256,128,64,32,16,8,4,2,1,0}
2199

Returns: 0



5)
{61,666,512,229,618,419,757,217,458,883,23,932,547,679,565,767,513,798,870,31,379,294,929,892,173,127,796,353,913,115,802,803,948,592,959,127,501,319,140,694,851,189,924,590,790,3,669,541,342,272}
1223

Returns: 29



6)
{34,64,43,14,58,30,2,16,90,58,35,55,46,24,14,73,96,13,9,42,64,36,89,42,42,64,52,68,53,76,52,54,23,88,32,52,28,96,70,32,26,3,23,78,47,23,54,30,86,32}
1328

Returns: 20



*/
// END CUT HERE
#line 108 "TypoCoderDiv1.cpp"
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

int ty(ll val) {
    return val >= 2200;
}

class TypoCoderDiv1
{
public:
 int getmax(vector <int> D, int X)
 {
 //$CARETPOSITION$
    map<ll, int> cur, pre;
    cur[X] = 0;
    range(i, D.size()) {
        ll cost = D[i];
        pre = cur;
        cur.clear();
        for (map<ll, int>::iterator it = pre.begin(); it!=pre.end(); it++) {
            //del
            ll nkey = max(it->fs - cost, 0LL);
            int nval = it->sc + (ty(it->fs) != ty(nkey));
            if (!(ty(it->fs) == 1 && ty(nkey) == 1)) {
                cur[nkey] = max(cur[nkey], nval);
            }
            //add
            nkey = max(it->fs + cost, 0LL);
            nval = it->sc + (ty(it->fs) != ty(nkey));
            if (!(ty(it->fs) == 1 && ty(nkey) == 1)) {
                cur[nkey] = max(cur[nkey], nval);
            }
        }
    }
    int ans = 0;
    for (map<ll, int>::iterator it = cur.begin(); it!=cur.end(); it++) {
        ans = max(ans, it->sc);
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {100,200,100,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2000; int Arg2 = 3; verify_case(0, Arg2, getmax(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0,0,0,0,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2199; int Arg2 = 0; verify_case(1, Arg2, getmax(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {90000,80000,70000,60000,50000,40000,30000,20000,10000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 1; verify_case(2, Arg2, getmax(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {1000000000,1000000000,10000,100000,2202,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1000; int Arg2 = 4; verify_case(3, Arg2, getmax(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {2048,1024,5012,256,128,64,32,16,8,4,2,1,0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2199; int Arg2 = 0; verify_case(4, Arg2, getmax(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {61,666,512,229,618,419,757,217,458,883,23,932,547,679,565,767,513,798,870,31,379,294,929,892,173,127,796,353,913,115,802,803,948,592,959,127,501,319,140,694,851,189,924,590,790,3,669,541,342,272}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1223; int Arg2 = 29; verify_case(5, Arg2, getmax(Arg0, Arg1)); }
	void test_case_6() { int Arr0[] = {34,64,43,14,58,30,2,16,90,58,35,55,46,24,14,73,96,13,9,42,64,36,89,42,42,64,52,68,53,76,52,54,23,88,32,52,28,96,70,32,26,3,23,78,47,23,54,30,86,32}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1328; int Arg2 = 20; verify_case(6, Arg2, getmax(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 TypoCoderDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
