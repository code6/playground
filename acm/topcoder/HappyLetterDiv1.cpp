// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// The Happy Letter game is played as follows:
At the beginning, several players enter the field.
Each player has a lowercase English letter on their back.
The game is played in turns.
In each turn, you select two players with different letters, and both selected players leave the field.
The game ends once it is impossible to take another turn.

If there are some players left in the field at the end of the game, they must all have the same letter.
That letter is called the winning letter.
If there are no players left in the field at the end of the game, there is no winning letter.

You are given a string letters.
The characters in letters are the characters carried by the players at the beginning of the game.
Return a string with all possible winning letters.
The letters in the returned string must be sorted in increasing order.


DEFINITION
Class:HappyLetterDiv1
Method:getHappyLetters
Parameters:string
Returns:string
Method signature:string getHappyLetters(string letters)


NOTES
-If there's no happy letter, return the empty string.


CONSTRAINTS
-letters will contain between 1 and 50 elements.
-Each element of letters will be a lowercase English letter ('a'-'z').


EXAMPLES

0)
"aabbacccc"

Returns: "abc"

Each of the three letters can be the winning letter.
Here is one possibility how 'a' can be the winning letter:
Let's number the players 0 through 8 in the order in which they appear in the input.
We can then play the game as follows:

Send away players 1 ('a') and 8 ('c').
Send away players 2 ('b') and 6 ('c').
Send away players 7 ('c') and 0 ('a').
Send away players 5 ('c') and 3 ('b').
The only player left is player 4 ('a'), hence 'a' is the winning letter.



1)
"aaaaaaaccdd"

Returns: "a"

Only letter 'a' can win.

2)
"ddabccadb"

Returns: "abcd"



3)
"aaabbb"

Returns: ""

No letter can win.


4)
"rdokcogscosn"

Returns: "cos"



*/
// END CUT HERE
#line 90 "HappyLetterDiv1.cpp"
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

class HappyLetterDiv1
{
public:
 string getHappyLetters(string letters)
 {
 //$CARETPOSITION$
        int n = letters.size();
        map<char, int> ct;
        range(i, n) {
            ct[letters[i]] += 1;
        }
        vector<pair<int, char> > vic;
        string ret = "";
        int total = 0;
        for (map<char,int>::iterator it = ct.begin(); it != ct.end(); it++) {
            vic.pb(mp(it->sc, it->fs));
            total += it->sc;
        }
        sort(all(vic));
        if (vic.size() == 1) {
            ret += vic[0].sc;
        } else {
            range(i, vic.size()) {
                    int cur = vic[i].fs;
                    int bg = (i < vic.size() - 1) ? vic.back().fs : vic[i - 1].fs;
                    int other = total - cur - bg;
                    //printf("ch = %c, cur = %d, bg = %d, other = %d\n",  vic[i].sc, cur, bg, other);
                    int left;
                    if (other <= bg) {
                        left = bg - other;
                    } else {
                        left = (other + bg) % 2;
                    }
                    if (cur > left) {
                        ret += vic[i].sc;
                    }
                }
        }
        sort(all(ret));

        return ret;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "aabbacccc"; string Arg1 = "abc"; verify_case(0, Arg1, getHappyLetters(Arg0)); }
	void test_case_1() { string Arg0 = "aaaaaaaccdd"; string Arg1 = "a"; verify_case(1, Arg1, getHappyLetters(Arg0)); }
	void test_case_2() { string Arg0 = "ddabccadb"; string Arg1 = "abcd"; verify_case(2, Arg1, getHappyLetters(Arg0)); }
	void test_case_3() { string Arg0 = "aaabbb"; string Arg1 = ""; verify_case(3, Arg1, getHappyLetters(Arg0)); }
	void test_case_4() { string Arg0 = "rdokcogscosn"; string Arg1 = "cos"; verify_case(4, Arg1, getHappyLetters(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 HappyLetterDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
