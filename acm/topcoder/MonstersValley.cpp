// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Manao is traversing a valley inhabited by monsters. During his journey, he will encounter several monsters one by one. The scariness of each monster is a positive integer. Some monsters may be scarier than others. The i-th (0-based index) monster Manao will meet has scariness equal to dread[i].

Manao is not going to fight the monsters. Instead, he will bribe some of them and make them join him. To bribe the i-th monster, Manao needs price[i] gold coins. The monsters are not too greedy, therefore each value in price will be either 1 or 2.

At the beginning, Manao travels alone. Each time he meets a monster, he first has the option to bribe it, and then the monster may decide to attack him. A monster will attack Manao if and only if he did not bribe it and its scariness is strictly greater than the total scariness of all monsters in Manao's party. In other words, whenever Manao encounters a monster that would attack him, he has to bribe it. If he encounters a monster that would not attack him, he may either bribe it, or simply walk past the monster.



Consider this example: Manao is traversing the valley inhabited by the Dragon, the Hydra and the Killer Rabbit. When he encounters the Dragon, he has no choice but to bribe him, spending 1 gold coin (in each test case, Manao has to bribe the first monster he meets, because when he travels alone, the total scariness of monsters in his party is zero). When they come by the Hydra, Manao can either pass or bribe her. In the end, he needs to get past the Killer Rabbit. If Manao bribed the Hydra, the total scariness of his party exceeds the Rabbit's, so they will pass. Otherwise, the Rabbit has to be bribed for two gold coins. Therefore, the optimal choice is to bribe the Hydra and then to walk past the Killer Rabbit. The total cost of getting through the valley this way is 2 gold coins.

You are given the vector<long long> dread and the vector <int> price. Compute the minimum price Manao will pay to safely pass the valley.

DEFINITION
Class:MonstersValley
Method:minimumPrice
Parameters:vector<long long>, vector <int>
Returns:int
Method signature:int minimumPrice(vector<long long> dread, vector <int> price)


CONSTRAINTS
-dread will contain between 1 and 50 elements, inclusive.
-Each element of dread will be between 1 and 1,000,000,000,000 (10^12), inclusive.
-price will contain the same number of elements as dread.
-Each element of price will be either 1 or 2.


EXAMPLES

0)
{8, 5, 10}
{1, 1, 2}

Returns: 2

The example from the problem statement.

1)
{1, 2, 4, 1000000000}
{1, 1, 1, 2}

Returns: 5

Manao has to bribe all monsters in the valley.

2)
{200, 107, 105, 206, 307, 400}
{1, 2, 1, 1, 1, 2}

Returns: 2

Manao can bribe monsters 0 and 3.

3)
{5216, 12512, 613, 1256, 66, 17202, 30000, 23512, 2125, 33333}
{2, 2, 1, 1, 1, 1, 2, 1, 2, 1}

Returns: 5

Bribing monsters 0, 1 and 5 is sufficient to pass safely.

*/
// END CUT HERE
#line 68 "MonstersValley.cpp"
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

const int MAX = 100;

typedef long long ll;

ll dp[MAX][2 * MAX];

void update(ll & x, ll y)
{
    x = max(x, y);
}

class MonstersValley
{
public:
 int minimumPrice(vector<long long> dread, vector <int> price)
 {
     int n = dread.size();
     int i, j;

     memset(dp, -1, sizeof(dp));
     dp[0][0] = 0;
     for (i = 0; i < n; i++) {
         for (j = 0; j <= 2 * i; j++) {
             if (dp[i][j] >= 0) {
                 if (dp[i][j] >= dread[i]) {
                     update(dp[i + 1][j], dp[i][j]);
                 }
                 update(dp[i + 1][j + price[i]], dp[i][j] + dread[i]);
             }
         }
     }

     for (i = 0; i <= 2 * n; i++) {
         if (dp[n][i] >= 0) {
             return i;
         }
     }
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { long Arr0[] = {8, 5, 10}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(0, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_1() { long Arr0[] = {1, 2, 4, 1000000000}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 1, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(1, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_2() { long Arr0[] = {200, 107, 105, 206, 307, 400}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 2, 1, 1, 1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 2; verify_case(2, Arg2, minimumPrice(Arg0, Arg1)); }
	void test_case_3() { long Arr0[] = {5216, 12512, 613, 1256, 66, 17202, 30000, 23512, 2125, 33333}; vector<long long> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 1, 1, 1, 1, 2, 1, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; verify_case(3, Arg2, minimumPrice(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 MonstersValley ___test;
 ___test.run_test(-1);
}
// END CUT HERE
