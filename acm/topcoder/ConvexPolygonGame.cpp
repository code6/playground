// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Little Petya likes convex polygons a lot. Recently he has received a convex polygon as a gift from his mother. The only thing that Petya likes more than convex polygons is playing with little Masha. Petya invented the following game for two players that involves his polygon.
At the beginning of the game there is a convex polygon drawn on the plane. The coordinates of vertices of this polygon are given in vector <int> X and vector <int> Y. Petya and Masha take alternate turns, Masha plays first. On his or her turn the player draws a new convex polygon that has the following properties:

 All vertices of the new polygon have integer coordinates.

 Each new vertex is located either strictly inside the old polygon or on an edge of the old polygon.

 No vertex of the new polygon coincides with any vertex of the old polygon.

 No three vertices of the new polygon lie on the same line.

 The new polygon has non-zero area.


Note that the new polygon and the old polygon are not required to have the same number of vertices. 
After drawing a new polygon the player erases the old one. A player who can't make a move loses the game. Determine who will be the winner if both kids play optimally. If the winner is Masha, return the string "Masha" (without quotes), otherwise return "Petya".

DEFINITION
Class:ConvexPolygonGame
Method:winner
Parameters:vector <int>, vector <int>
Returns:string
Method signature:string winner(vector <int> X, vector <int> Y)


CONSTRAINTS
-X will contain between 3 and 50 elements, inclusive.
-Y will contain between 3 and 50 elements, inclusive.
-X and Y will contain the same number of elements.
-Each element of X will be between -100 000 and 100 000, inclusive.
-Each element of Y will be between -100 000 and 100 000, inclusive.
-The polygon represented by X and Y will be convex, will have non-zero area and won't contain any 3 vertices that are located on the same line.
-Vertices of the polygon will be listed in counter-clockwise order.


EXAMPLES

0)
{0, 1, 0}
{0, 0, 1}

Returns: "Petya"

Masha has no valid moves, so she loses the game immediately.

1)
{0, 4, 2}
{0, 0, 2}

Returns: "Masha"

One of the possible Masha's moves is to select the triangle (1, 0), (3, 1), (1, 1). Regardless of her first move Petya will never be able to make the next move.

2)
{0, 100, 100, 0}
{0, 0, 100, 100}

Returns: "Masha"



3)
{0, 50, 100, 50}
{0, -1, 0, 1}

Returns: "Petya"



4)
{-100000, 100000, 100000, -100000}
{-1, -1, 1, 1}

Returns: "Masha"



*/
// END CUT HERE
#line 84 "ConvexPolygonGame.cpp"
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

const int MAX = 1000000;

bool check(int x1, int x2, int x3, int x4) {
    if (x1 > x2 || x3 > x4) return false;
    if (x1 + 1 == x2 && x3 + 1 == x4) return false;
    if (x2 < x3 || x4 < x1) return false;
    return true;
}

double cross(PII p0,PII p1, PII p2){
        return 1.0 * (p1.fs-p0.fs)*(p2.sc-p0.sc)- 1.0 * (p2.fs-p0.fs)*(p1.sc-p0.sc);  
}  

bool in_poly(int n, const vector<int>& X, const vector<int>& Y, int cx, int cy) {
    PII p0, p1;
    for (int i = 0; i < n; i++)  {
        p0 = mp(X[i], Y[i]);
        p1 = mp(X[(i+1)%n], Y[(i+1)%n]);
        if (cross(p0, p1, mp(cx, cy)) < 0) {
            return false;
        }
    }
    return true;
}

void find_intersect(int n, const vector<int>& X, const vector<int>& Y, int cy, int& cx_min, int& cx_max) {
    cx_min = MAX;
    cx_max = -MAX;
    for (int i = 0; i < n; i++) {
        PII p0, p1;
        p0 = mp(X[i], Y[i]);
        p1 = mp(X[(i+1)%n], Y[(i+1)%n]);

        int min_x = min(p0.fs, p1.fs);
        int max_x = max(p0.fs, p1.fs);
        int min_y = min(p0.sc, p1.sc);
        int max_y = max(p0.sc, p1.sc);

        if (!(min_y <= cy && cy <= max_y)) {
            continue;
        }

        if (min_y == max_y) {
            cx_min = min(cx_min, min_x);
            cx_max = max(cx_max, max_x);
        } else {
            if (min_x == max_x) {
                cx_min = min(cx_min, min_x);
                cx_max = max(cx_max, min_x);
            } else {
                double k = 1.0 * (p1.sc - p0.sc) / (p1.fs - p0.fs);
                double b = p1.sc - k * p1.fs;
                double fx = (cy - b) / k;
                for (int cx = int(fx - 10); cx <=(int)(fx + 10); cx++) {
                //    printf("test %d %d, k = %lf\n", cx, cy, k);
                    if (in_poly(n, X, Y, cx, cy)) {
                        cx_min = min(cx_min, cx);
                        cx_max = max(cx_max, cx);
                    }
                }
            }
        }
    }
}

class ConvexPolygonGame
{
public:
 string winner(vector <int> X, vector <int> Y)
 {
 //$CARETPOSITION$
    
    int n, min_y, max_y;
    min_y = MAX;
    max_y = -MAX;
    n = X.size();

    set<PII> poly;
    range(i, n) {
        poly.insert(mp(X[i], Y[i]));
    }

    range(i, n) {
        min_y = min(Y[i], min_y);
        max_y = max(Y[i], max_y);
    }

    int cnt = 0;
    for (int cy = min_y; cy <= max_y; cy++) {
        int cx_min, cx_max;
        find_intersect(n, X, Y, cy, cx_min, cx_max);
        //printf("%d %d %d\n", cy, cx_min, cx_max);
        while (poly.find(mp(cx_min, cy)) != poly.end()) {
            cx_min ++;
        }
        while (poly.find(mp(cx_max, cy)) != poly.end()) {
            cx_max --;
        }
        if (cx_min > cx_max) continue;
        cnt += min(cx_max - cx_min, 2);
    }
    return cnt >= 3 ? "Masha" : "Petya";
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = {0, 1, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Petya"; verify_case(0, Arg2, winner(Arg0, Arg1)); }
	void test_case_1() { int Arr0[] = {0, 4, 2}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(1, Arg2, winner(Arg0, Arg1)); }
	void test_case_2() { int Arr0[] = {0, 100, 100, 0}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 100, 100}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(2, Arg2, winner(Arg0, Arg1)); }
	void test_case_3() { int Arr0[] = {0, 50, 100, 50}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, -1, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Petya"; verify_case(3, Arg2, winner(Arg0, Arg1)); }
	void test_case_4() { int Arr0[] = {-100000, 100000, 100000, -100000}; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {-1, -1, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Masha"; verify_case(4, Arg2, winner(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 ConvexPolygonGame ___test;
 ___test.run_test(-1);
}
// END CUT HERE
