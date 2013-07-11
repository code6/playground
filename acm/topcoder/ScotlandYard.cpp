// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Fox Ciel and Fox Jiro play a game called Scotland Yard.
Their version of the game is a bit simplified, so if you know the original game, make sure you read the problem statement carefully.


In the game Ciel and Jiro play, they use a map containing n cities.
The cities are numbered 0 through n-1.
The map also contains a bunch of arrows.
Each arrow leads from one city to another (different) city, and has one of three possible colors.
The colors represent three types of transportation: taxis, buses, and metro (subway).
Both Ciel and Jiro know all information in this map.


You are given three vector <string>s: taxi, bus, and metro.
The j-th character of the i-th element of taxi is 'Y' if it is possible to travel directly from city i to city j using a taxi, or 'N' if that is not possible.
In the same way, bus and metro encode the information about bus and subway travel.
Note that all transportation options are one-way. Also note that there are no additional restrictions.
(That is, it may be possible to travel between some pairs of cities in both directions, there may be more than one transportation option from city i to city j, and for each transport type there can be arbitrarily many options leaving a given city.)


The game starts by Ciel secretly choosing one of the n cities as her initial location.
The game then proceeds in turns.
In each turn, first Ciel moves to an adjacent location, then Jiro has the option to announce her new location.
More precisely, it looks as follows:
Whenever it is Ciel's turn to move, she has to move from her current city X to some other city Y.
If there are no transportation options that start in the city X, Ciel announces this and the game ends.
Otherwise, she chooses one of the available options and moves to its destination.
Additionally, Ciel announces to Jiro the type of the transportation system she used ("taxi", "bus", or "metro").
Whenever it is Jiro's turn, if he is certain of Ciel's current city, he announces it and the game ends.
Otherwise, Jiro passes and it's again Ciel's turn to move.
(Note that Jiro can use all the information he has: the layout of the map, and the sequence of transportation systems Ciel already announced.)


Ciel's score is the number of travels she made.
Return Ciel's score, assuming that she plays optimally.
If she can continue the game forever without being discovered by Jiro, return -1 instead.

DEFINITION
Class:ScotlandYard
Method:maxMoves
Parameters:vector <string>, vector <string>, vector <string>
Returns:int
Method signature:int maxMoves(vector <string> taxi, vector <string> bus, vector <string> metro)


NOTES
-The answer will always fit into a signed 32bit integer.


CONSTRAINTS
-taxi will contain between 2 and 50 elements, inclusive.
-taxi, bus, and metro will contain the same number of elements.
-Each element of taxi, bus, and metro will contain n characters, where n is the number of elements in taxi.
-Each character in taxi, bus, and metro will be either 'Y' or 'N'.
-The i-th character of the i-th element of taxi, bus, and metro will be 'N'.


EXAMPLES

0)
{"NYN",
 "NNY",
 "NNN"}
{"NNN",
 "NNN",
 "NNN"}
{"NNN",
 "NNN",
 "NNN"}

Returns: 2


Ciel starts in city 0.
In her first move, she announces "taxi" and moves from 0 to 1.
At that moment, Jiro is not certain of her location: she can be in city 1 or in city 2.
In her second move, Ciel announces "taxi" and moves from 1 to 2.
Jiro announces that Ciel is in city 2 and the game ends.

1)
{"NYY",
 "NNN",
 "NNN"}
{"NNN",
 "NNN",
 "NNN"}
{"NNN",
 "NNN",
 "NNN"}

Returns: 1


After Ciel's first move, Jiro doesn't know her location. Still, the game ends, because Ciel has no more moves.

2)
{"NYYY",
 "YNYY",
 "YYNY",
 "YYYN"}
{"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}
{"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}

Returns: -1


Ciel can use taxis to drive back and forth between the cities indefinitely. Jiro has no chance to discover her location.

3)
{"NNY",
 "NNY",
 "NNN"}
{"NYN",
 "NNY",
 "NNN"}
{"NNN",
 "NNN",
 "YNN"}

Returns: 2


Ciel starts by choosing her initial location and the first mode of transport.
Here is how Jiro will think after Ciel's first move:

Suppose that Ciel announced "taxi". She could have started in city 0 or in city 1, but either way she would take the taxi to city 2. Thus, Jiro knows that Ciel is in city 2 and the game ends.
Metro is even simpler. If Ciel announced she took the metro, she must have started in city 2 and then she took the metro to city 0. Jiro announces city 0 and the game ends.
If Ciel announed that she took the bus, Jiro is not sure about her location: she can be either in city 1, or in city 2.

Regardless of where Ciel started and what she does in the second step after taking a bus in the first step, Jiro will always be able to determine her location and the game ends.

4)
{"NNN",
 "YNY",
 "NNN"}
{"NNN",
 "YNN",
 "YNN"}
{"NNN",
 "NNN",
 "YYN"}

Returns: -1


If Ciel travels back and forth between cities 1 and 2, Jiro will never catch her.

5)
{"NNNNYNNNYY",
 "NNYNNYYYYY",
 "NNNNNNNNNN",
 "YYNNYYNNNY",
 "NNYNNNNNNN",
 "YNYNYNNNYN",
 "NNYNYNNNYN",
 "NNNNNNYNNN",
 "NNNNNNNNNN",
 "NNNNNNYNNN"}
{"NNYNNNYNNY",
 "YNYNNYYNYY",
 "NNNNNNNNNN",
 "YNYNNYNYNY",
 "NNYNNNNNYN",
 "YNYNYNYNYN",
 "NNYNNNNNNY",
 "YNYNNNNNNN",
 "NNNNNNNNNN",
 "NNYNYNNNNN"}
{"NNNNNNNYNN",
 "YNYNNNNNYN",
 "NNNNNNNNNN",
 "NYNNYNNNYY",
 "NNYNNNNNNN",
 "YNYNNNNNYY",
 "NNNNYNNNYN",
 "NNYNNNYNNN",
 "NNNNNNNNNY",
 "NNYNYNNNNN"}

Returns: 21



*/
// END CUT HERE
#line 195 "ScotlandYard.cpp"
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

class ScotlandYard
{
public:
 int maxMoves(vector <string> taxi, vector <string> bus, vector <string> metro)
 {
 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"NYN",
 "NNY",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(0, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"NYY",
 "NNN",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "NNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 1; verify_case(1, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"NYYY",
 "YNYY",
 "YYNY",
 "YYYN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNNN",
 "NNNN",
 "NNNN",
 "NNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(2, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"NNY",
 "NNY",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NYN",
 "NNY",
 "NNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "YNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 2; verify_case(3, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"NNN",
 "YNY",
 "NNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNN",
 "YNN",
 "YNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNN",
 "NNN",
 "YYN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = -1; verify_case(4, Arg3, maxMoves(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"NNNNYNNNYY",
 "NNYNNYYYYY",
 "NNNNNNNNNN",
 "YYNNYYNNNY",
 "NNYNNNNNNN",
 "YNYNYNNNYN",
 "NNYNYNNNYN",
 "NNNNNNYNNN",
 "NNNNNNNNNN",
 "NNNNNNYNNN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NNYNNNYNNY",
 "YNYNNYYNYY",
 "NNNNNNNNNN",
 "YNYNNYNYNY",
 "NNYNNNNNYN",
 "YNYNYNYNYN",
 "NNYNNNNNNY",
 "YNYNNNNNNN",
 "NNNNNNNNNN",
 "NNYNYNNNNN"}; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arr2[] = {"NNNNNNNYNN",
 "YNYNNNNNYN",
 "NNNNNNNNNN",
 "NYNNYNNNYY",
 "NNYNNNNNNN",
 "YNYNNNNNYY",
 "NNNNYNNNYN",
 "NNYNNNYNNN",
 "NNNNNNNNNY",
 "NNYNYNNNNN"}; vector <string> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arg3 = 21; verify_case(5, Arg3, maxMoves(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 ScotlandYard ___test;
 ___test.run_test(-1);
}
// END CUT HERE
