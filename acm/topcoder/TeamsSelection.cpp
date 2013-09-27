// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// The boys in the yard are going to play soccer. There are N+2 boys, two of which have been chosen as captains. Now they want to divide the other N children into two teams. For convenience, we number the boys who are not captains from 1 to N.

The division into teams works as follows. Initially, the first captain chooses one person for his team. Then, the second captain chooses one boy from those who are left. Then the first captain chooses again, and so on. The process continues until there are no more boys left.

You are given vector <int>s preference1 and preference2, each containing N elements. preference1[0] is the number of the boy whom the first captain regards to be the best player, preference1[1] is the next best player according to the first captain, and so on. preference2 describes the second captain's assessment in the same fashion. The captains pick the players greedily, i.e., each of them always chooses the boy whom he considers to be the strongest between the children not yet chosen.

Return a string consisting of N characters. Character i in the returned string must be '1' if the boy i+1 will be assigned to the first captain's team and '2' otherwise.

DEFINITION
Class:TeamsSelection
Method:simulate
Parameters:vector <int>, vector <int>
Returns:string
Method signature:string simulate(vector <int> preference1, vector <int> preference2)


CONSTRAINTS
-preference1 will contain N elements, where N is between 2 and 50, inclusive.
-Elements of preference1 will contain each of the numbers from 1 to N exactly once.
-preference2 will contain N elements.
-Elements of preference2 will contain each of the numbers from 1 to N exactly once.


EXAMPLES

0)
{1, 2, 3, 4}
{1, 2, 3, 4}

Returns: "1212"

There are 4 boys to be divided between the two captains. Both captains believe that boy 1 plays best, then come boy 2 and boy 3, and boy 4 plays worst. Thus, the first captain will choose boy 1, the second captain will choose boy 2, since boy 1 is already assigned to a team, then the first captain will choose boy 3 and in the end the second captain will take boy 4.

1)
{3, 2, 1}
{1, 3, 2}

Returns: "211"

The first captain will choose boy 3, the second captain will choose boy 1 and then the first captain will choose boy 2. Note that when there is an odd number of children, the first team ends up one man larger.

2)
{6, 1, 5, 2, 3, 4}
{1, 6, 3, 4, 5, 2}

Returns: "212211"



3)
{8, 7, 1, 2, 4, 5, 6, 3, 9}
{7, 2, 4, 8, 1, 5, 9, 6, 3}

Returns: "121121212"



*/
// END CUT HERE
#line 64 "TeamsSelection.cpp"
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

class TeamsSelection
{
public:
 string simulate(vector <int> preference1, vector <int> preference2)
 {
 //$CARETPOSITION$
    string ret = "";
    vector<int> used;
    int n = preference1.size();
    used.resize(n);
    int i, j;
    for (i = 0; i < n; i++) used[i] = 0;
    for (i  =0; i < n; i++) cout << preference1[i] <<" vs " << preference2[i] << endl;
    i = j  = 0;
    while (i < n && j < n) {
        while (i < n && used[preference1[i] - 1]) {
            i++;
        }
        if (i < n) {
            used[preference1[i] - 1] = 1;
            i++;
        }
        while (j < n && used[preference2[j] - 1]) {
            j++;
        }
        if (j < n) {
            used[preference2[j] - 1] = 2;
            j++;
        }
    }
    for (i = 0; i < n; i++) ret += used[i] + '0';

    return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {1, 2, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 3, 4}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1212"; verify_case(0, Arg2, simulate(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {3, 2, 1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 3, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "211"; verify_case(1, Arg2, simulate(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {6, 1, 5, 2, 3, 4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 6, 3, 4, 5, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "212211"; verify_case(2, Arg2, simulate(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {8, 7, 1, 2, 4, 5, 6, 3, 9}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {7, 2, 4, 8, 1, 5, 9, 6, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "121121212"; verify_case(3, Arg2, simulate(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 TeamsSelection ___test;
 ___test.run_test(-1);
}
// END CUT HERE
