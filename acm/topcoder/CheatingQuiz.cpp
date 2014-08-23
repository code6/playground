// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Mr. Dengklek is taking part in an online quiz. The quiz consists of N multiple-choice questions, conveniently numbered 0 through N-1. For each question there are three possible answers labeled A, B, and C. For each question, exactly one of the three possible answers is correct. You are given the information on correct answers as a string answers. More precisely, answers[i] is the correct answer to the i-th question. This is of course unknown to Mr. Dengklek.

Mr. Dengklek did not know the answer to any of the quiz questions. Being desperate, he hacked the website of the quiz. However, the only thing he could obtain was aggregate information on the answers that will be used. More precisely, thanks to the hack Mr. Dengklek now knows how many questions have the answer A, how many have the answer B, and how many have the answer C.

When taking the quiz, Mr. Dengklek will be given the questions one at a time, in the same order that is used in answers. For each of the questions, he will use his intuition to pick one of the answers that are still possible. After he picks the answer for a question, the quiz will always show him the correct answer for that question.

Mr. Dengklek has noticed that sometimes he can rule out some of the answers when answering a question. Your method must return a vector <int> containing N elements. The i-th element in this vector <int> must be the number of options Mr. Dengklek will choose from when answering the i-th question.


DEFINITION
Class:CheatingQuiz
Method:howMany
Parameters:string
Returns:vector <int>
Method signature:vector <int> howMany(string answers)


CONSTRAINTS
-answers will contain between 1 and 50 characters, inclusive.
-Each character of answers will be 'A', 'B', or 'C'.


EXAMPLES

0)
"AAAAA"

Returns: {1, 1, 1, 1, 1 }

Mr. Dengklek knows that A is the correct answer to all questions. Therefore, for each question, he only has one choice: answering A.

1)
"AAABBB"

Returns: {2, 2, 2, 1, 1, 1 }

Mr. Dengklek knows that there will be three As and three Bs. For each of the first three questions he has two choices: answering A or B. After answering the third question, he will discover that all As have been used, so for each of the remaining questions he only has one choice: answering B.

2)
"CAAAAAC"

Returns: {2, 2, 2, 2, 2, 2, 1 }



3)
"BBCA"

Returns: {3, 3, 2, 1 }



4)
"BACACABCBBBBCAAAAACCCABBCAA"

Returns: {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1 }



*/
// END CUT HERE
#line 66 "CheatingQuiz.cpp"
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

class CheatingQuiz
{
public:
 vector <int> howMany(string answers)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <int> &Expected, const vector <int> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arg0 = "AAAAA"; int Arr1[] = {1, 1, 1, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, howMany(Arg0)); }
	void test_case_1() { string Arg0 = "AAABBB"; int Arr1[] = {2, 2, 2, 1, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, howMany(Arg0)); }
	void test_case_2() { string Arg0 = "CAAAAAC"; int Arr1[] = {2, 2, 2, 2, 2, 2, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, howMany(Arg0)); }
	void test_case_3() { string Arg0 = "BBCA"; int Arr1[] = {3, 3, 2, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, howMany(Arg0)); }
	void test_case_4() { string Arg0 = "BACACABCBBBBCAAAAACCCABBCAA"; int Arr1[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 1, 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, howMany(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 CheatingQuiz ___test;
 ___test.run_test(-1);
}
// END CUT HERE
