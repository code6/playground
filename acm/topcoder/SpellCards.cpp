// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// You are playing a card game.
In the card game, each card holds a magic spell with two properties: its level and its damage.
During the game, you will play some of the cards (possibly none or all of them) to attack your enemy.



Initially, there are n cards.
The cards are placed in a row and they are labeled from 0 to n-1, in order.
You are given two vector <int>s: level and damage.
For each i, the level of card i is level[i], and its damage is damage[i].



In each turn of the game, you can do one of two possible actions:


Let L be the level and D the damage of the card that is currently the leftmost card in the row.
If there are at least L cards in the row, you may play the leftmost card.
Playing it deals D damage to your enemy.
After you play this card, the first L cards in the row (including the played one) are discarded.
That is, the cards currently labeled 0 through (L-1), inclusive, are discarded.
The order of the remaining cards does not change.


If you have at least one card, you can take the last card in the row and move it to the beginning.
For example, if the row initially contained cards A,B,C,D,E, in this order, after this operation it will contain E,A,B,C,D.


After each turn, the cards are relabeled 0 through x-1, where x is their current count.



Return the maximal total damage you can deal to your opponent.

DEFINITION
Class:SpellCards
Method:maxDamage
Parameters:vector <int>, vector <int>
Returns:int
Method signature:int maxDamage(vector <int> level, vector <int> damage)


CONSTRAINTS
-level will contain between 1 and 50 elements, inclusive.
-level and damage will contain the same number of elements.
-Each element in level will be between 1 and 50, inclusive.
-Each element in damage will be between 1 and 10,000, inclusive.


EXAMPLES

0)
{1,1,1}
{10,20,30}

Returns: 60

You can play card 0 three times in a row, dealing 10+20+30 = 60 damage.

1)
{3,3,3}
{10,20,30}

Returns: 30

Here, it is optimal to start by moving the last card to the beginning of the row.
In the second turn we then use the card and deal 30 damage.
Afterwards, all three cards are discarded.

2)
{4,4,4}
{10,20,30}

Returns: 0

This time you can't use any spell card.

3)
{50,1,50,1,50}
{10,20,30,40,50}

Returns: 60

You can use 2 cards with damage 20 and 40.

4)
{2,1,1}
{40,40,10}

Returns: 80



5)
{1,2,1,1,3,2,1}
{10,40,10,10,90,40,10}

Returns: 170



6)
{1,2,2,3,1,4,2}
{113,253,523,941,250,534,454}

Returns: 1918



*/
// END CUT HERE
#line 116 "SpellCards.cpp"
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

const int N = 200;

int dp[N];
int l[N], d[N];
int bomb[N][N];
int opt[N][N];

void update(int & x, int y)
{
    x = max(x, y);
}


int calc(vector<int> l, vector<int> d)
{
    int n = l.size();
    int dp[55];
    memset(dp, 0, sizeof(dp));
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = n; j >= l[i]; j--) {
            dp[j] = max(dp[j], dp[j - l[i]] + d[i]);
        }
    }

    int ret = 0;
    for (i = 0; i <= n; i++) {
        ret = max(ret, dp[i]);
    }
    return ret;
}


class SpellCards
{
public:
 int maxDamage(vector <int> level, vector <int> damage)
 {
     int result = calc(level, damage);
     printf("true result = %d\n", result);
     int n = level.size();
     int nn = 2 * n;
     int i, j, k, u;
     for (i = 0; i < nn; i++) {
         l[i] = level[i % n];
         d[i] = damage[i % n];
     }

     memset(bomb, -1, sizeof(bomb));

     for (i = 0; i < nn; i++) {
         if (l[i] == 1) {
             bomb[i][i] = d[i];
         }
     }

     for (k = 1; k <= n; k++) {
         for (i = 0; i < nn; i++) {
             j = i + k;
             if (j >= nn) {
                 break;
             }

             for (u = i; u < j; u++) {
                 if (bomb[i][u] > 0 && bomb[u + 1][j] > 0) {
                     update(bomb[i][j], bomb[i][u] + bomb[u + 1][j]);
                 }
             }

             if (l[i] == k + 1) {
                 update(bomb[i][j], d[i]);
             } else {
                 if (l[i] > 1 && l[i] < k + 1) {
                     int le = k - l[i];
                     for (u = i + 1; u < j; u++) {
                         int nu = u + le;
                         if (nu >= j) {
                             break;
                         }
                         if (bomb[u][nu] > 0) {
                             update(bomb[i][j], d[i] + bomb[u][nu]);
                         }
                     }
                 }
             }
         }
     }


     memset(opt, 0, sizeof(opt));
     for (i = 0; i < nn; i++) {
         if (bomb[i][i] > 0) {
            opt[i][i] = bomb[i][i];
         }
     }

     for (k = 1; k <= n; k++) {
         for (i = 0; i < nn; i++) {
             j = i + k;
             if (j >= nn) {
                 break;
             }
             opt[i][j] = opt[i][j - 1];
             for (u = i; u <= j; u++) {
                 if (bomb[u][j] > 0) {
                     opt[i][j] = max(opt[i][j], (u > i ? opt[i][u - 1] : 0) + bomb[u][j]);
                 }
             }
         }
     }

     int ret = 0;

     for (i = 0; i < n; i++) {
         j = i + n - 1;
         ret = max(ret, opt[i][j]);
     }

     return ret;

 //$CARETPOSITION$
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); if ((Case == -1) || (Case == 6)) test_case_6(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {2, 1, 2, 2, 1, 2, 1, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {117, 205, 176, 248, 198, 176, 132, 130, 108, 270, 167, 276, 114, 176, 254, 201, 144, 205, 195, 192, 255, 199, 170, 110, 278, 101, 142, 116, 131, 132, 102, 169, 129, 173, 148, 222, 135, 199}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5341; verify_case(0, Arg2, maxDamage(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {3,3,3}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,20,30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 30; verify_case(1, Arg2, maxDamage(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {4,4,4}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,20,30}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 0; verify_case(2, Arg2, maxDamage(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {50,1,50,1,50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,20,30,40,50}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 60; verify_case(3, Arg2, maxDamage(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {2,1,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {40,40,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 80; verify_case(4, Arg2, maxDamage(Arg0, Arg1)); }
	void test_case_5() { int Arr0[] = {1,2,1,1,3,2,1}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {10,40,10,10,90,40,10}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 170; verify_case(5, Arg2, maxDamage(Arg0, Arg1)); }
	void test_case_6() { int Arr0[] = {1,2,2,3,1,4,2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {113,253,523,941,250,534,454}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 1918; verify_case(6, Arg2, maxDamage(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 SpellCards ___test;
 ___test.run_test(-1);
}
// END CUT HERE
