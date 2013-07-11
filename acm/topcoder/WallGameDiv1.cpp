// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Rabbit and Eel are playing a board game.
The game is played with a single token on a rectangular board that is divided into a grid of unit cells.
Each cell contains a digit that represents the cost of placing the token onto that cell.


The game is played in turns.
In each turn, Rabbit moves first and Eel moves second.
In the first turn, Rabbit places the token onto one of the cells in the topmost row, and he pays the associated cost.
In each of the following turns, Rabbit moves the token one cell left, right, or down, and pays the cost written in the target cell.
(Note that Rabbit is not allowed to move the token upwards.)
Eel never moves the token.
Instead, in each turn, Eel gets to place some walls.
In each turn, Eel may place as many walls as he wants, including none.
Each wall must be placed between two adjacent cells in the same column.


The game ends when Rabbit first moves the token into the bottommost row.
The game must always be allowed to end.
That is, Eel must never place a wall that would prevent Rabbit from reaching the bottommost row from the token's current location.
Rabbit's goal is to minimize and Eel's goal is to maximize the total cost paid by Rabbit during the game.


You are given the vector <string> costs representing the costs of cells:
character j of element i of cost represents the cost written in the cell in row i, column j.
Return the total cost of the game assuming that both Rabbit and Eel play optimally.

DEFINITION
Class:WallGameDiv1
Method:play
Parameters:vector <string>
Returns:int
Method signature:int play(vector <string> costs)


CONSTRAINTS
-costs will contain between 2 and 50 elements, inclusive.
-Each element of costs will contain between 1 and 50 characters, inclusive.
-Each element of costs will contain the same number of characters.
-Each character of each element of costs will be between '0' and '9', inclusive.


EXAMPLES

0)
{"12"
,"34"}

Returns: 6

One possible gameplay is as follows:

Rabbit puts a token on '2' and pays 2.
Eel puts a wall between '2' and '4'
Rabbit moves the token to '1' and pays 1.
Eel does nothing.
Rabbit moves the token to '3', pays 3, and the game ends.

The total cost is 2+1+3 = 6.

1)
{"99999"
,"99999"
,"99999"}

Returns: 99

Let's label the cells in the following way:

ABCDE
FGHIJ
KLMNO

We will not show you the optimal strategy. Instead, we will just show you one possible gameplay.

Rabbit puts a token on C and pays 9.
Eel puts eight walls: between AF, BG, CH, DI, GL, HM, IN, and JO.
Rabbit moves the token to D and pays 9.
Eel does nothing.
Rabbit moves the token to E and pays 9.
Eel does nothing.
During next several turns, Rabbit will move the token along the path E->J->I->H->G->F and Eel does nothing.
Rabbit moves the token to K, pays 9, and ends the game with total cost 81.

In the above example, neither player played optimally.

2)
{"11111"
,"90005"}

Returns: 10

Let's label the cells in the following way:

ABCDE
FGHIJ

Again, we will not show you the optimal strategy. Instead, we will just show you one possible gameplay.

Rabbit puts a token on C.
Eel puts three walls: between BG, CH, and DI.
Rabbit moves the token to D and pays 1.
Eel puts a wall between EJ.
Now Rabbit is forced to move the token back. Rabbit will move the token along the path D->C->B->A->F and Eel does nothing.
The game ends with total cost 14.


3)
{"4417231387449337370319219832088987579792"
,"3117295688208899006196193430472892512797"
,"0835796222361526836944954410684516919758"
,"1988200069973565052900745230547016216225"
,"8080511471118865780390486996601082102418"
,"4229084185957675819725844582167613108400"
,"9068653877952162764545674979144308771754"
,"8551565425951612499712254182109991511690"
,"7090525592007482152807163656647658543093"
,"9198968742256995592729889137556032960142"
,"2071864379877766468141740053503050313101"
,"1055375249261868472993219156394129253481"
,"2461178270502857106406495509025426298874"
,"8216781259733537757203421037984512664825"
,"4693452554407216935375049784445568498482"
,"2709693439640250842244170297203200674391"
,"5122217695676372684217182241705137947908"
,"6668814191410691246849638388008228444294"
,"4952122070212780440963814752538149378639"
,"9827737761436134120332969866554332504400"
,"3412406588339828249986707470540386748886"
,"7521506848088506994554600408372456405830"
,"1916926179183007872881163173153907665999"
,"6636166791472761992310264951474925339024"
,"6679667717747231380196787943691121008076"
,"3218993234115685151069259138068533004433"
,"4920152552986426962081492913852060211795"
,"0365186235986445521382132973036266396894"
,"3205351414936828189305188614651974318855"
,"3144278971529524658788277656125598825426"
,"5525287537572356662391582052968411726245"
,"2130137226726919525622574701068062252930"
,"2369996694245544770519574837226971226841"
,"6806769058165410189286521891570936341547"
,"0448109211631660241710734664066810078242"
,"4622919135804954122810530631429501069659"
,"0235247446548732490429856705369583140671"
,"2193399741215975228987754171460722199304"
,"1203037020703833716225328076959743850915"
,"5419885193880826109484912489603262199432"}

Returns: 7366



*/
// END CUT HERE
#line 159 "WallGameDiv1.cpp"
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

const int INF = 100000000;

int n, m;
int c[55][55];
int s[55][55];
int dp[55][55];
int best[55][55][55][2];

int get_val(int at, int f, int r) {
    return s[at][r + 1] - s[at][f];
}

int get_idx(int f, int r, int side) {
    if (side == 0) {
        return f - 1;
    } else {
        return r;
    }
}

int left_idx(int f, int r, int side) {
    if (side == 0) {
        return f - 2;
    } else {
        return f - 1;
    }
}
int right_idx(int f, int r, int side) {
    if (side == 0) {
        return r ;
    } else {
        return r + 1;
    }
}

int calc(int at, int f, int r, int side) {
    if (best[at][f][r][side] != -1) {
        return best[at][f][r][side];
    }

    int & ret = best[at][f][r][side];
    ret = 0;

    if (r - f == m - 1) {
        if (side == 0) {
            ret = dp[at + 1][0] + c[at][0];
        } else {
            ret = dp[at + 1][m - 1] + c[at][m - 1];
        }
        return ret;
    }

    int idx = get_idx(f, r, side);
    //let go
    ret = dp[at + 1][idx] + c[at][idx];

    //don't let go
    int other_ret = INF;
    int lidx = left_idx(f, r, side);
    int ridx = right_idx(f, r, side);
    int nf = f;
    int nr = r;
    if (side == 0) {
        nf --;
    }
    if (side == 1) {
        nr ++;
    }

    if (lidx >= 0) {
        other_ret = min(other_ret, calc(at, nf, nr, 0) + get_val(at, lidx + 1, idx));
    }

    if (ridx < m) {
        other_ret = min(other_ret, calc(at, nf, nr, 1) + get_val(at, idx, ridx - 1));
    }

    ret = max(ret, other_ret);

    return ret;
}

class WallGameDiv1
{
public:
 int play(vector <string> cost)
 {
 //$CARETPOSITION$
    n = cost.size();
    m = cost[0].size();
    int i, j;
    for (i = 0; i < n; i++) {
        s[i][0] = 0;
        for (j = 0; j < m; j++) {
            c[i][j] = cost[i][j] - '0';
            s[i][j + 1] = s[i][j] + c[i][j];
        }
    }

    memset(dp, -1, sizeof(dp));
    for (i = 0; i < m; i++) {
        dp[n - 1][i] = c[n - 1][i];
    }

    memset(best, -1, sizeof(best));
    for (i = n - 2; i >= 0; i--) {
        for (j = 0; j < m; j++) {
            dp[i][j] = calc(i, j, j, 1);
        }
    }

    if (n  < 5) {
        printf("dp arr:\n");
        for (i = 0; i < n; i++,  putchar('\n')) {
            for (j = 0; j < m; j++) {
                printf("%d ", dp[i][j]);
            }
        }
    }

    int ans = dp[0][0];
    for (i = 0; i < m; i++) 
        ans = min(ans, dp[0][i]);

    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"12"
,"34"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; verify_case(0, Arg1, play(Arg0)); }
	void test_case_1() { string Arr0[] = {"99999"
,"99999"
,"99999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 99; verify_case(1, Arg1, play(Arg0)); }
	void test_case_2() { string Arr0[] = {"11111"
,"90005"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 10; verify_case(2, Arg1, play(Arg0)); }
	void test_case_3() { string Arr0[] = {"4417231387449337370319219832088987579792"
,"3117295688208899006196193430472892512797"
,"0835796222361526836944954410684516919758"
,"1988200069973565052900745230547016216225"
,"8080511471118865780390486996601082102418"
,"4229084185957675819725844582167613108400"
,"9068653877952162764545674979144308771754"
,"8551565425951612499712254182109991511690"
,"7090525592007482152807163656647658543093"
,"9198968742256995592729889137556032960142"
,"2071864379877766468141740053503050313101"
,"1055375249261868472993219156394129253481"
,"2461178270502857106406495509025426298874"
,"8216781259733537757203421037984512664825"
,"4693452554407216935375049784445568498482"
,"2709693439640250842244170297203200674391"
,"5122217695676372684217182241705137947908"
,"6668814191410691246849638388008228444294"
,"4952122070212780440963814752538149378639"
,"9827737761436134120332969866554332504400"
,"3412406588339828249986707470540386748886"
,"7521506848088506994554600408372456405830"
,"1916926179183007872881163173153907665999"
,"6636166791472761992310264951474925339024"
,"6679667717747231380196787943691121008076"
,"3218993234115685151069259138068533004433"
,"4920152552986426962081492913852060211795"
,"0365186235986445521382132973036266396894"
,"3205351414936828189305188614651974318855"
,"3144278971529524658788277656125598825426"
,"5525287537572356662391582052968411726245"
,"2130137226726919525622574701068062252930"
,"2369996694245544770519574837226971226841"
,"6806769058165410189286521891570936341547"
,"0448109211631660241710734664066810078242"
,"4622919135804954122810530631429501069659"
,"0235247446548732490429856705369583140671"
,"2193399741215975228987754171460722199304"
,"1203037020703833716225328076959743850915"
,"5419885193880826109484912489603262199432"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 7366; verify_case(3, Arg1, play(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 WallGameDiv1 ___test;
 ___test.run_test(-1);
}
// END CUT HERE
