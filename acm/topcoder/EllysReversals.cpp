// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Elly has a list of several distinct strings given in the vector <string> words. She can apply the following operation as many times as she wants (including zero times):

Choose one of the words and call it S.
Choose an even number k between 2 and |S|, inclusive, where |S| is the length of S (thus, chose a prefix with even length).
Reverse the order of the first k characters of S (thus, reverse the chosen prefix without the rest of the word).

For example, if she has the word "topcoder", she can reverse its first 2, 4, 6, or all 8 characters. If she chooses to reverse its first 4 characters, the change will be: "topcoder" -> "cpotoder". If at a later time she decides to chose the same string and reverse all of its characters (which is also a valid prefix with even length), she would get "cpotoder"->"redotopc".

After performing some operations two strings might become equal. If that happens, Elly crosses them out and continues playing her game with the remaining strings only, i.e. they "disappear" from the list. The girl wonders what is the minimal number of strings she can end up with.

For example, suppose she has the strings {"esprit", "god", "redotopc", "odcpoter", "dog"}. The word "redotopc" can be converted to "topcoder" by first reversing all 8 characters and then reversing the first 4. The word "odcpoter" can also be converted to "topcoder" by performing "odcpoter" -> "docpoter" -> "topcoder". At that point the words become equal and disappear, leaving Elly only with {"esprit", "god", "dog"}. This is where she gets stuck: The words "god" and "dog" cannot become equal, because she can only reverse prefixes with even length. Thus, the minimal number of words she can get is 3.

Given her initial strings in vector <string> words, return an int indicating the minimal number of strings she can be left with.

DEFINITION
Class:EllysReversals
Method:getMin
Parameters:vector <string>
Returns:int
Method signature:int getMin(vector <string> words)


CONSTRAINTS
-words will contain between 1 and 50 elements, inclusive.
-Each element of words will contain between 1 and 50 characters, inclusive.
-Each element of words will consist only of lowercase letters of the English alphabet ('a'-'z').
-All elements of words will be distinct.


EXAMPLES

0)
{"esprit", "god", "redotopc", "odcpoter", "dog"}

Returns: 3

The example from the problem statement.

1)
{"no", "zaphod", "just", "very", "improbable"}

Returns: 5

It is possible that she cannot get rid of any of the words.

2)
{"rats", "live", "stressed", "to", "act", "as", "star", "desserts", "of", "evil", "cat", "sa", "fo", "ot"}

Returns: 0

It is possible that she ends up with zero words.

3)
{"topcoder", "redocpot", "doretopc", "cpotdoer", "harlemshake"}

Returns: 1

Sometimes it is possible to match different words when using a different sequence of operations.

4)
{"iprlzgukfggzg", "bmhxvjbrtkbxy", "khapjiabbny", "nqlwgmcyvdikt",
 "nxromtvtpug", "leealcapovm", "ushnxwjczczbmd", "bwhykzupcux",
 "xrlboyuwlnsp", "bbjoketeheezfs", "dxfztrldomjqkv", "dkbktqdtgfujcut",
 "zfybzyuxgpnt", "ffmsldrdftode", "vopuufksxd", "pqhbsiujwda",
 "yhwbkzupcux", "hkbabnapjiy", "zqsqefrrzehtxn", "yovinyguyudmv"}

Returns: 16



*/
// END CUT HERE
#line 77 "EllysReversals.cpp"
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
const int MAX = 100 + 40;
int parent[MAX];

void init(int n)
{
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = i;
    }
}

int u_find(int a)
{
    while (a != parent[a]) {
        //halving path length
        parent[a] = parent[parent[a]];
        a = parent[a];
    }
    return a;
}

void u_union(int a, int b)
{
    a = u_find(a);
    b = u_find(b);
    if (a == b) {
        return;
    }
    parent[b] = a;
}

bool calc(string A, string B) {
    //cout<<"A = "<<A<<" B = "<<B<<endl;
    if (A.length() != B.length()) {
        return false;
    }
    string a1 = A, b1 = B;
    sort(a1.begin(), a1.end());
    sort(b1.begin(), b1.end());
    if (a1 != b1) {
        return false;
    }
    if (A.length() % 2) {
        if (A[A.length() - 1] != B[B.length() - 1]) {
            return false;
        }
        A = A.substr(0, A.length() - 1);
        B = B.substr(0, B.length() - 1);
    }
    vector<string> va, vb;
    int i;
    for (i = 0; i < A.length() / 2; i++) {
        va.push_back(A.substr(2 * i, 2));
        vb.push_back(B.substr(2 * i, 2));
    }
    for (i = 0; i < va.size(); i++) {
        sort(va[i].begin(), va[i].end());
        sort(vb[i].begin(), vb[i].end());
    }
    sort(va.begin(), va.end());
    sort(vb.begin(), vb.end());
    if (va != vb) {
        return false;
    } 
    return true;
}

int N;

class EllysReversals
{
public:
 int getMin(vector <string> words)
 {
     N = words.size();
     init(N);
     int i, j;
     for (i = 0; i < N; i++) {
         for (j = i + 1; j < N; j++) {
             if (calc(words[i], words[j])) {
                 u_union(i, j);
             }
         }
     }

     int cnt[MAX];
     memset(cnt, 0, sizeof(cnt));
     for (i = 0; i < N; i++) {
         cnt[u_find(i)] ++;
     }

     int ans = 0;
     for (i = 0; i < N; i++) {
         ans += cnt[i] % 2;
     }
     return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"esprit", "god", "redotopc", "odcpoter", "dog"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; verify_case(0, Arg1, getMin(Arg0)); }
	void test_case_1() { string Arr0[] = {"no", "zaphod", "just", "very", "improbable"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 5; verify_case(1, Arg1, getMin(Arg0)); }
	void test_case_2() { string Arr0[] = {"rats", "live", "stressed", "to", "act", "as", "star", "desserts", "of", "evil", "cat", "sa", "fo", "ot"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; verify_case(2, Arg1, getMin(Arg0)); }
	void test_case_3() { string Arr0[] = {"topcoder", "redocpot", "doretopc", "cpotdoer", "harlemshake"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; verify_case(3, Arg1, getMin(Arg0)); }
	void test_case_4() { string Arr0[] = {"iprlzgukfggzg", "bmhxvjbrtkbxy", "khapjiabbny", "nqlwgmcyvdikt",
 "nxromtvtpug", "leealcapovm", "ushnxwjczczbmd", "bwhykzupcux",
 "xrlboyuwlnsp", "bbjoketeheezfs", "dxfztrldomjqkv", "dkbktqdtgfujcut",
 "zfybzyuxgpnt", "ffmsldrdftode", "vopuufksxd", "pqhbsiujwda",
 "yhwbkzupcux", "hkbabnapjiy", "zqsqefrrzehtxn", "yovinyguyudmv"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 16; verify_case(4, Arg1, getMin(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 EllysReversals ___test;
 ___test.run_test(-1);
}
// END CUT HERE
