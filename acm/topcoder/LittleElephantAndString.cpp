// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
Little Elephant from the Zoo of Lviv likes strings.




You are given a string A and a string B of the same length. In one turn Little Elephant can choose any character of A and move it to the beginning of the string (i.e., before the first character of A). Return the minimal number of turns needed to transform A into B. If it's impossible, return -1 instead.


DEFINITION
Class:LittleElephantAndString
Method:getNumber
Parameters:string, string
Returns:int
Method signature:int getNumber(string A, string B)


CONSTRAINTS
-A will contain between 1 and 50 characters, inclusive.
-B will contain between 1 and 50 characters, inclusive.
-A and B will be of the same length.
-A and B will consist of uppercase letters ('A'-'Z') only.


EXAMPLES

0)
"ABC"
"CBA"

Returns: 2

The optimal solution is to make two turns. On the first turn, choose character 'B' and obtain string "BAC". On the second turn, choose character 'C' and obtain "CBA".

1)
"A"
"B"

Returns: -1

In this case, it's impossible to transform A into B.

2)
"AAABBB"
"BBBAAA"

Returns: 3



3)
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"ZYXWVUTSRQPONMLKJIHGFEDCBA"

Returns: 25



4)
"A"
"A"

Returns: 0



5)
"DCABA"
"DACBA"

Returns: 2



*/
// END CUT HERE
#line 81 "LittleElephantAndString.cpp"
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

class LittleElephantAndString
{
public:
 int getNumber(string A, string B)
 {
     string sA, sB;
     sA = A;
     sB = B;
     sort(sA.begin(), sA.end());
     sort(sB.begin(), sB.end());
     if (sA != sB) return -1;
     int n = A.size();
     int i;
     for (i = n; i > 0; i--) {
         int j, k;
         j = n - i;
         k = 0;
         for (; j < n; j++) {
             for (; k < n && A[k] != B[j]; k++);
             if (k == n) break;
             k++;
         }
         if (j == n) break;
     }
     return n - i;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "ABC"; string Arg1 = "CBA"; int Arg2 = 2; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "A"; string Arg1 = "B"; int Arg2 = -1; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "AAABBB"; string Arg1 = "BBBAAA"; int Arg2 = 3; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; string Arg1 = "ZYXWVUTSRQPONMLKJIHGFEDCBA"; int Arg2 = 25; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arg0 = "A"; string Arg1 = "A"; int Arg2 = 0; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_5() { string Arg0 = "DCABA"; string Arg1 = "DACBA"; int Arg2 = 2; verify_case(5, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 LittleElephantAndString ___test;
 ___test.run_test(-1);
}
// END CUT HERE
