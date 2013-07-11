// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
A group of freshman rabbits has recently joined the Eel club.
No two of the rabbits knew each other.
Yesterday, each of the rabbits went to the club for the first time.
For each i, rabbit number i entered the club at the time s[i] and left the club at the time t[i].


Each pair of rabbits that was in the club at the same time got to know each other, and they became friends on the social network service Shoutter.
This is also the case for rabbits who just met for a single moment (i.e., one of them entered the club exactly at the time when the other one was leaving).


In Shoutter, each user can post a short message at any time.
The message can be read by the user's friends.
The friends can also repost the message, making it visible to their friends that are not friends with the original poster.
In turn, those friends can then repost the message again, and so on.
Each message can be reposted in this way arbitrarily many times. 
If a rabbit wants to repost multiple messages, he must repost each of them separately.


Today, each of the rabbits posted a self-introduction to Shoutter.
Each rabbit would now like to read the self-introductions of all other rabbits (including those that are currently not his friends).
Compute and return the minimal number of reposts necessary to reach this goal.
If it is impossible to reach the goal, return -1 instead.


As the number of rabbits can be greater than what the TopCoder arena supports, you are given the times s[i] and t[i] encoded in the following form:
You are given vector <string>s s1000, s100, s10, and s1.
Concatenate all elements of s1000 to obtain a string S1000.
In the same way obtain the strings S100, S10, and S1.
Character i of each of these strings corresponds to the rabbit number i.
More precisely, these characters are the digits of s[i]:
we obtain s[i] by converting the string S1000[i]+S100[i]+S10[i]+S1[i] to an integer.
For example, if S1000[4]='0', S100[4]='1', S10[4]='4', and S1[4]='7', then s[4]=to_integer("0147")=147.
You are also given vector <string>s t1000, t100, t10, and t1.
These encode the times t[i] in the same way.


DEFINITION
Class:ShoutterDiv1
Method:count
Parameters:vector <string>, vector <string>, vector <string>, vector <string>, vector <string>, vector <string>, vector <string>, vector <string>
Returns:int
Method signature:int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)


CONSTRAINTS
-s1000, s100, s10, s1, t1000, t100, t10 and t1 will each contain between 1 and 50 elements, inclusive.
-s1000, s100, s10, s1, t1000, t100, t10 and t1 will contain the same number of elements.
-Each element of s1000, s100, s10, s1, t1000, t100, t10 and t1 will contain between 1 and 50 characters, inclusive.
-For each i, the i-th elements of all input variables will all contain the same number of characters.
-Each character in the input variables will be a digit ('0'-'9').
-For each i, t[i] will be greater than or equal to s[i].


EXAMPLES

0)
{"22", "2"}
{"00", "0"}
{"11", "1"}
{"21", "4"}
{"22", "2"}
{"00", "0"}
{"11", "1"}
{"43", "6"}

Returns: 2

After parsing the input, you will get the following information: Rabbit 0 will enter the room at 2012 and leave the room at 2014. Rabbit 1 will enter the room at 2011 and leave the room at 2013. Rabbit 2 will enter the room at 2014 and leave the room at 2016. Therefore, Rabbit 0 and Rabbit 1 will be friends, and Rabbit 0 and Rabbit 2 will be friends too, but Rabbit 1 and Rabbit 2 won't be friends.


Rabbit 0 can already see the self-introductions of all rabbits, but rabbits 1 and 2 cannot see each other's self-introduction.
Two actions are needed: First, Rabbit 0 reposts the self-introduction of Rabbit 1, and then Rabbit 0 reposts the self-introduction of Rabbit 2.
Now everybody can read everything.

1)
{"00"}
{"00"}
{"00"}
{"13"}
{"00"}
{"00"}
{"00"}
{"24"}

Returns: -1

If it is impossible to achieve the goal, return -1.

2)
{"0000"}
{"0000"}
{"0000"}
{"1234"}
{"0000"}
{"0000"}
{"0000"}
{"2345"}

Returns: 6

The following pairs will be friends: Rabbit 0 and 1, 1 and 2, and 2 and 3. One of the optimal strategies is as follows:

Rabbit 1 shares introductions of Rabbit 0 and 2.
Rabbit 2 shares introductions of Rabbit 1 and 3.
Rabbit 1 shares introduction of Rabbit 3 (this is possible because now Rabbit 3's introduction is shared by Rabbit 2, who is a Rabbit 1's friend).
Rabbit 2 shares introduction of Rabbit 0 (this is possible because now Rabbit 0's introduction is shared by Rabbit 1, who is a Rabbit 2's friend).


3)
{"0000000000"}
{"0000000000"}
{"0000000000"}
{"7626463146"}
{"0000000000"}
{"0000000000"}
{"0000000000"}
{"9927686479"}

Returns: 18



4)
{"00000000000000000000000000000000000000000000000000"}
{"00000000000000000000000000000000000000000000000000"}
{"50353624751857130208544645495168271486083954769538"}
{"85748487990028258641117783760944852941545064635928"}
{"00000000000000000000000000000000000000000000000000"}
{"00000000000000000000000000000000000000000000000000"}
{"61465744851859252308555855596388482696094965779649"}
{"37620749792666153778227385275518278477865684777411"}

Returns: 333



*/
// END CUT HERE
#line 144 "ShoutterDiv1.cpp"
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

class ShoutterDiv1
{
public:
 int count(vector <string> s1000, vector <string> s100, vector <string> s10, vector <string> s1, vector <string> t1000, vector <string> t100, vector <string> t10, vector <string> t1)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"22", "2"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00", "0"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"11", "1"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"21", "4"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"22", "2"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"00", "0"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"11", "1"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"43", "6"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 2; verify_case(0, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_1() { string Arr0[] = {"00"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"00"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"13"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"00"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"00"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"00"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"24"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = -1; verify_case(1, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_2() { string Arr0[] = {"0000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"1234"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"0000"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"0000"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"0000"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"2345"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 6; verify_case(2, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_3() { string Arr0[] = {"0000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"0000000000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"0000000000"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"7626463146"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"0000000000"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"0000000000"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"0000000000"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"9927686479"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 18; verify_case(3, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }
	void test_case_4() { string Arr0[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"50353624751857130208544645495168271486083954769538"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); string Arr3[] = {"85748487990028258641117783760944852941545064635928"}; vector <string> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); string Arr4[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg4(Arr4, Arr4 + (sizeof(Arr4) / sizeof(Arr4[0]))); string Arr5[] = {"00000000000000000000000000000000000000000000000000"}; vector <string> Arg5(Arr5, Arr5 + (sizeof(Arr5) / sizeof(Arr5[0]))); string Arr6[] = {"61465744851859252308555855596388482696094965779649"}; vector <string> Arg6(Arr6, Arr6 + (sizeof(Arr6) / sizeof(Arr6[0]))); string Arr7[] = {"37620749792666153778227385275518278477865684777411"}; vector <string> Arg7(Arr7, Arr7 + (sizeof(Arr7) / sizeof(Arr7[0]))); int Arg8 = 333; verify_case(4, Arg8, count(Arg0, Arg1, Arg2, Arg3, Arg4, Arg5, Arg6, Arg7)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 ShoutterDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
