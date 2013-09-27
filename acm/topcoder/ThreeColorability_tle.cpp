// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// 
There is a H times W rectangle divided into unit cells.
The rows of cells are numbered 0 to H-1 from top to bottom, and the columns are numbered 0 to W-1 from left to right.
The corners of cells are called lattice points.
By definition, there are (H+1)*(W+1) lattice points in our rectangle.


Each of the four edges of each cell is painted white.
Additionally, in some cells exactly one of the two diagonals is painted white.
In the remaining cells no diagonal is painted white yet.
Later, you are going to paint exactly one of the diagonals white in each of these cells.


Once you are done painting the diagonals, your next goal will be to color each of the lattice points using one of three available colors: red, green, or blue.
There is only one constraint: adjacent lattice points are not allowed to share the same color.


Two lattice points are called adjacent if they are connected by a white line segment.
(In other words, consecutive corners of a cell are always adjacent, opposite corners of a cell are adjacent if and only if they are connected by a painted diagonal, and no other pairs of lattice points are adjacent.)


Obviously, you need to paint the missing diagonals in such a way that there will be a valid coloring of lattice points, if possible.


You are given a vector <string> cells with H elements, each consisting of W characters.
If cells[i][j] is 'N', there is a diagonal line from the top left to the bottom right corner in the cell in row i, column j.
If cells[i][j] is 'Z', there is a diagonal line from the top right to the bottom left corner in the cell in row i, column j.
If cells[i][j] is '?', there is no diagonal yet in the cell in row i, column j.


If it is impossible to fill in the missing diagonals in such a way that there will be a valid coloring of all lattice points, return an empty vector <string>.
Otherwise, return a vector <string> that represents the rectangle with all the missing diagonals filled in.
I.e., the return value must be obtained from cells by replacing each '?' by either 'N' or 'Z'.
The return value must represent a rectangle for which a valid coloring of its lattice points exists.
If there are multiple possibilities, return the lexicographically smallest one.




DEFINITION
Class:ThreeColorability
Method:lexSmallest
Parameters:vector <string>
Returns:vector <string>
Method signature:vector <string> lexSmallest(vector <string> cells)


NOTES
-Given two different vector <string>s A and B with the same number of elements, find the smallest index i such that A[i] and B[i] differ. If A[i] < B[i] we say that A is lexicographically smaller than B and vice versa.


CONSTRAINTS
-cells will contain between 1 and 50 elements, inclusive.
-Each element of cells will contain between 1 and 50 characters, inclusive.
-All elements of cells will contain the same number of characters.
-Each character of cells will be either 'N' or 'Z' or '?'.


EXAMPLES

0)
{"Z"}

Returns: {"Z" }

The given rectangle and a possible coloring is as follows.






1)
{"??", "?N"}

Returns: {"NN", "NN" }





2)
{"ZZZ", "ZNZ"}

Returns: { }



3)
{"N?N??NN","??ZN??Z","NN???Z?","ZZZ?Z??","Z???NN?","N?????N","ZZ?N?NN"}

Returns: { }



4)
{"ZZZZ","ZZZZ","ZZZZ"}

Returns: {"ZZZZ", "ZZZZ", "ZZZZ" }



*/
// END CUT HERE
#line 109 "ThreeColorability.cpp"
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
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()
#define two(i) (1<<(i))

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

const int MAX = 200;

vector<string> cells;
int n, m;
int n1, m1;
int color[MAX][MAX];
vector<PII> d[MAX][MAX];

const int dir[][2] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0},
};

const int dir_dia[][2] = {
    {-1, -1},
    {-1, 1},
    {1, -1},
    {1, 1},
};

const int dir_cell[][2] = {
    {-1, -1},
    {-1, 0},
    {0, -1},
    {0, 0},
};

const string dia_type = "NZZN";

bool islegal(int x, int y) {
    return x >= 0 && x < n1 && y >= 0 && y < m1;
}

int get_val(int a) {
    for (int i = 0; i < 5; i++) {
        if (two(i) == a) {
            return i;
        }
    }
    return 0;
}

bool test() {
    memset(color, -1, sizeof(color));

    range(i, n1) {
        range(j, m1) {
            d[i][j].clear();
            range(k, 4) {
                int i1, j1;
                //4 dir
                i1 = i + dir[k][0];
                j1 = j + dir[k][1];
                if (islegal(i1, j1)) {
                    d[i][j].push_back(mp(i1, j1));
                }
                //diagonal
                i1 = i + dir_dia[k][0];
                j1 = j + dir_dia[k][1];
                if (islegal(i1, j1)) {
                    int i2, j2;
                    i2 = i + dir_cell[k][0];
                    j2 = j + dir_cell[k][1];
                    if (cells[i2][j2] == dia_type[k]) {
                        d[i][j].push_back(mp(i1, j1));
                    }
                }
            }
        }
    }

    color[0][0] = 0;
    color[0][1] = 1;

    while (true) {
        bool found = false;
        range(i, n1) {
            range(j, m1) {
                int mask = 0;
                range(k, d[i][j].size()) {
                    PII next = d[i][j][k];
                    if (color[next.fs][next.sc] != -1) {
                        mask |= two(color[next.fs][next.sc]);
                    }
                }
                if (color[i][j] == -1) {
                    if (mask == 7) {
                        return false;
                    }
                    if (mask == 3 || mask == 5 || mask == 6) {
                        color[i][j] = get_val(7 - mask);
                        //cout << i << ' ' << j << ' ' << color[i][j] << endl;
                        found = true;
                    }
                } else {
                    if (mask & two(color[i][j])) {
                        return false;
                    }
                }
            }
        }
        if (!found) {
            break;
        }
    }
    return true;
}


class ThreeColorability
{
public:
 vector <string> lexSmallest(vector <string> _cells)
 {
 //$CARETPOSITION$
    string tpl="N???????????????????????????????????????????????????????????????";
    string sample = "";
    range(i, 50) {
        string row = "";
        range(j, 50) {
            row+=tpl[rand()%tpl.size()];
        }
        if (i > 0) sample +=',';
        sample+=row;
    }
    cout<<sample<<endl;

    cells = _cells;
    n = cells.size();
    m = cells[0].size();
    n1 = n + 1;
    m1 = m + 1;
    bool ok = true;
    range(i, n) {
        range(j, m) {
            if (cells[i][j] == '?') {
                cells[i][j] = 'N';
                if (!test()) {
                    cells[i][j] = 'Z';
                    if (!test()) {
                        ok = false;
                        break;
                    }
                }
            }
        }
        if (!ok) {
            break;
        }
    }
    ok = test();
    vector<string> ret;
    if (!ok) return ret;
    else {
        return cells;
    }
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const vector <string> &Expected, const vector <string> &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: " << print_array(Expected) << endl; cerr << "\tReceived: " << print_array(Received) << endl; } }
	void test_case_0() { string Arr0[] = {"Z"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"Z" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(0, Arg1, lexSmallest(Arg0)); }
	void test_case_1() { string Arr0[] = {"??", "?N"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"NN", "NN" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(1, Arg1, lexSmallest(Arg0)); }
	void test_case_2() { string Arr0[] = {"ZZZ", "ZNZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(2, Arg1, lexSmallest(Arg0)); }
	void test_case_3() { string Arr0[] = {"N?N??NN","??ZN??Z","NN???Z?","ZZZ?Z??","Z???NN?","N?????N","ZZ?N?NN"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = { }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(3, Arg1, lexSmallest(Arg0)); }
	void test_case_4() { string Arr0[] = {"ZZZZ","ZZZZ","ZZZZ"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); string Arr1[] = {"ZZZZ", "ZZZZ", "ZZZZ" }; vector <string> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); verify_case(4, Arg1, lexSmallest(Arg0)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 ThreeColorability ___test;
 ___test.run_test(-1);
}
// END CUT HERE
