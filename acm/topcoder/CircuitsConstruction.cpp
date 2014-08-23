// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Janusz is a young physicist.
He is currently playing with some electric circuits.

The simplest circuit consists of a single conductor (i.e., a single piece of wire).
Each such circuit is labeled using the string "X".

Janusz is using two different ways to connect two simpler circuits into one new, more complex circuit.
Note that these are not the standard two ways (connecting in series and in parallel), so read the following description carefully.

If Janusz uses the type-A connection, the resistance of the new circuit is the sum of the resistances of the two original circuits.
If Janusz uses the type-B connection, the resistance of the new circuit is the maximum of the resistances of the two original circuits.


Suppose that the two original circuits had labels C1 and C2.
Then we use the label "A"+C1+C2 for a new circuit constructed from them using the type-A connection, and the label "B"+C1+C2 if type-B connection was used.
For example, "AXX" is the label of the circuit obtained by using a type-A connection on two conductors.

You are given a string circuit with a valid label of a circuit.
You are also given a vector <int> conductors with as many elements as the number of occurrences of 'X' in circuit.
The elements of conductors are the resistances of all conductors you are going to use to construct the circuit described by circuit.
Each of the conductors can only be used once.
Each of the conductors can be used as each of the 'X's.
Return the largest possible resistance of the constructed circuit.


DEFINITION
Class:CircuitsConstruction
Method:maximizeResistance
Parameters:string, vector <int>
Returns:int
Method signature:int maximizeResistance(string circuit, vector <int> conductors)


NOTES
-There is no explicit constraint on the length of circuit. This is intentional, as it can be derived from the other constraints.


CONSTRAINTS
-Each character in circuit will be 'A', 'B', or 'X'.
-circuit will be a valid circuit label according to the problem statement.
-conductors will contain between 1 and 2,000 elements, inclusive.
-Each element of conductors will be between 1 and 100,000, inclusive.
-The number of occurrences of the character 'X' in circuit will be equal to the number of elements of conductors.


EXAMPLES

0)
"BXBXX"
{8, 2, 3}

Returns: 8

Regardless of the order in which we use the conductors, the final resistance will be the maximum of the resistances of our three conductors.

1)
"AAXXAXAXX"
{1, 1, 2, 8, 10}

Returns: 22

Regardless of the order in which we use the conductors, the final resistance will be the sum of the resistances of our five conductors.

2)
"AXBXX"
{8, 2, 3}

Returns: 11

One possible optimal solution looks as follows:

We take the conductors with resistance 2 and 3, and use a type-B connection to combine them into a new circuit.
We take the remaining conductor (with resistance 8) and the new circuit constructed in the previous step. We use a type-A connection to combine them into the resulting circuit.

The resistance of the circuit constructed in the first step is max(2,3) = 3.
The resistance of the whole circuit is 8 + 3 = 11, which is the largest value we can obtain.

3)
"BAAXBXXBXAXXBBAXXBXXAAXXX"
{17, 7, 21, 102, 56, 72, 88, 15, 9, 192, 16, 8, 30}

Returns: 454



*/
// END CUT HERE
#line 92 "CircuitsConstruction.cpp"
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

int search(const string & circuit, int &beg) {
    int pos = beg;
    char ty = circuit[beg++];
    if (ty == 'X') return 1;
    int res = 0;
    if (ty == 'A') {
        res += search(circuit, beg);
        res += search(circuit, beg);
    } else {
        res = search(circuit, beg);
        res = max(res, search(circuit, beg));
    }
    //cout << " pos = " << pos << " res = " << res << endl;
    return res;
}

class CircuitsConstruction
{
public:
 int maximizeResistance(string circuit, vector <int> conductors)
 {
 //$CARETPOSITION$
    sort(all(conductors));
    int res = 0;
    int beg = 0;
    int cnt = search(circuit, beg);
    //cout << "cnt = " << cnt << endl;
    range(i, cnt) res += conductors[conductors.size() - 1 - i];
    return res;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "BXBXX"; int Arr1[] = {8, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 8; verify_case(0, Arg2, maximizeResistance(Arg0, Arg1)); }
	void test_case_1() { string Arg0 = "AAXXAXAXX"; int Arr1[] = {1, 1, 2, 8, 10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 22; verify_case(1, Arg2, maximizeResistance(Arg0, Arg1)); }
	void test_case_2() { string Arg0 = "AXBXX"; int Arr1[] = {8, 2, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 11; verify_case(2, Arg2, maximizeResistance(Arg0, Arg1)); }
	void test_case_3() { string Arg0 = "BAAXBXXBXAXXBBAXXBXXAAXXX"; int Arr1[] = {17, 7, 21, 102, 56, 72, 88, 15, 9, 192, 16, 8, 30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 454; verify_case(3, Arg2, maximizeResistance(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 CircuitsConstruction ___test;
 ___test.run_test(-1);
}
// END CUT HERE
