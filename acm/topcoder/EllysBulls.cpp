// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// Elly and Kristina play a game called "Bulls". Initially each of them thinks of a non-negative integer with K digits, possibly containing leading zeroes. Then they take alternating turns, trying to guess the opponent's number. After each guess, the other person says how many positions were guessed correctly. For example if Kristina's number was "1337" and Elly's guess was "1738", Kristina should answer 2, since the digits at positions 0 and 2 (zero-based indices from the left) are correct. A guessed position is called "bull's hit", or simply a "bull", thus the name of the game.

Elly has already made several guesses. She wonders if the information she has is enough to uniquely determine Kristina's number.

You are given the guesses so far in a vector <string> guesses and the corresponding number of bull's hits in vector <int> bulls. If a unique number satisfies the given information, return it as a string. If there is more than one number that is valid according to the current guesses, return "Ambiguity" (quotes for clarity only). If no number satisfies the given information, then Kristina has lied and you should return "Liar" instead.

DEFINITION
Class:EllysBulls
Method:getNumber
Parameters:vector <string>, vector <int>
Returns:string
Method signature:string getNumber(vector <string> guesses, vector <int> bulls)


NOTES
-The game "Bulls" is a simplification of a game played in Bulgaria, called "Kravi & Bikove" ("Cows & Bulls").


CONSTRAINTS
-guesses will contain between 1 and 50 elements, inclusive.
-Each element of guesses will contain between 2 and 9 characters, inclusive.
-All elements of guesses will contain the same number of characters.
-All elements of guesses will consist only of digits ('0'-'9').
-bulls will contain the same number of elements as guesses.
-Each element of bulls will be between 0 and K-1, inclusive, where K is the length of each element of guesses.


EXAMPLES

0)
{"1234", "4321", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"}
{2, 1, 1, 0, 2, 0, 0, 0, 1, 0, 0}

Returns: "1337"

From {1234->2, 2222->0, 4444->0} it follows that the number is {1?3?}. The additional information {4321->1} tells us that either the digit at position 1 (0-indexed) is 3, or that the one at position 3 is 1. However, since {1111->1} and we already know that the 0-th digit is 1, then the third digit cannot be 1. Now we know that the number is {133?}. When trying {7777->1} we see that Kristina's number contains a 7, which cannot be anywhere else except in the last position. Thus, her number is 1337.


1)
{"0000", "1111", "2222"}
{2, 2, 2}

Returns: "Liar"

There are supposed to be two 0s, two 1s and two 2s in a four-digit number. Thus, Kristina is clearly a liar.


2)
{"666666", "666677", "777777", "999999"}
{2, 3, 1, 0}

Returns: "Ambiguity"

Some of the possible configurations that satisfy the current results are the numbers 636172, 336617, 660007. Thus, the answer is ambiguous.


3)
{"000", "987", "654", "321", "100", "010"}
{2, 1, 0, 0, 1, 1}

Returns: "007"

The guesses, as well as the answer, can have leading zeroes.

4)
{"28", "92", "70", "30", "67", "63", "06", "65",
 "11", "06", "88", "48", "09", "65", "48", "08"}
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

Returns: "54"



5)
{"0294884", "1711527", "2362216", "7666148", "7295642",
 "4166623", "1166638", "2767693", "8650248", "2486509",
 "6138934", "4018642", "6236742", "2961643", "8407361",
 "2097376", "6575410", "6071777", "3569948", "2606380"}
{1, 0, 1, 3, 4, 4, 3, 2, 1, 1, 0, 4, 4, 3, 0, 0, 0, 0, 2, 1}

Returns: "4266642"



*/
// END CUT HERE
#line 91 "EllysBulls.cpp"
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

const int MAX = 200;

int n, m;
int mat[MAX][MAX];
int equ, var; // 有equ个方程，var个变元。增广阵行数为equ, 分别为0到equ - 1，列数为var + 1，分别为0到var.
int a[MAX][MAX];
int x[MAX]; // 解集.
bool free_x[MAX]; // 判断是否是不确定的变元.
int free_num;

void debug(void)
{
    int i, j;
    for (i = 0; i < equ; i++)
    {
        for (j = 0; j < var + 1; j++)
        {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int gcd(int a, int b)
{
    int t;
    while (b != 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}
 int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

// 高斯消元法解方程组(Gauss-Jordan elimination).(-2表示有浮点数解，但无整数解，-1表示无解，0表示唯一解，大于0表示无穷解，并返回自由变元的个数)
int Gauss(void)
{
    int i, j, k;
    int max_r; // 当前这列绝对值最大的行.
int col; // 当前处理的列.
    int ta, tb;
    int LCM;
    int temp;
    int free_x_num;
    int free_index;
    // 转换为阶梯阵.
    col = 0; // 当前处理的列.
    for (k = 0; k < equ && col < var; k++, col++)
    { // 枚举当前处理的行.
        // 找到该col列元素绝对值最大的那行与第k行交换.(为了在除法时减小误差)
        max_r = k;
        for (i = k + 1; i < equ; i++)
        {
            if (abs(a[i][col]) > abs(a[max_r][col])) max_r = i;
        }
        if (max_r != k)
        { // 与第k行交换.
            for (j = k; j < var + 1; j++) swap(a[k][j], a[max_r][j]);
        }
        if (a[k][col] == 0)
        { // 说明该col列第k行以下全是0了，则处理当前行的下一列.
            k--; continue;
        }
        for (i = k + 1; i < equ; i++)
        { // 枚举要删去的行.
            if (a[i][col] != 0)
    {
                LCM = lcm(abs(a[i][col]), abs(a[k][col]));
                ta = LCM / abs(a[i][col]), tb = LCM / abs(a[k][col]);
                if (a[i][col] * a[k][col] < 0) tb = -tb; // 异号的情况是两个数相加.
                for (j = col; j < var + 1; j++)
                {
                    a[i][j] = a[i][j] * ta - a[k][j] * tb;
                }
    }
        }
    }
    // 1. 无解的情况: 化简的增广阵中存在(0, 0, ..., a)这样的行(a != 0).
    for (i = k; i < equ; i++)
    { // 对于无穷解来说，如果要判断哪些是自由变元，那么初等行变换中的交换就会影响，则要记录交换.
        if (a[i][col] != 0) return -1;
    }
    // 2. 无穷解的情况: 在var * (var + 1)的增广阵中出现(0, 0, ..., 0)这样的行，即说明没有形成严格的上三角阵.
    // 且出现的行数即为自由变元的个数.
    if (k < var)
    {
        // 首先，自由变元有var - k个，即不确定的变元至少有var - k个.
        for (i = k - 1; i >= 0; i--)
        {
            // 第i行一定不会是(0, 0, ..., 0)的情况，因为这样的行是在第k行到第equ行.
            // 同样，第i行一定不会是(0, 0, ..., a), a != 0的情况，这样的无解的.
            free_x_num = 0; // 用于判断该行中的不确定的变元的个数，如果超过1个，则无法求解，它们仍然为不确定的变元.
 for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && free_x[j]) free_x_num++, free_index = j;
            }
            if (free_x_num > 1) continue; // 无法求解出确定的变元.
            // 说明就只有一个不确定的变元free_index，那么可以求解出该变元，且该变元是确定的.
            temp = a[i][var];
            for (j = 0; j < var; j++)
            {
                if (a[i][j] != 0 && j != free_index) temp -= a[i][j] * x[j];
            }
            x[free_index] = temp / a[i][free_index]; // 求出该变元.
            free_x[free_index] = 0; // 该变元是确定的.
        }
        return var - k; // 自由变元有var - k个.
    }
    // 3. 唯一解的情况: 在var * (var + 1)的增广阵中形成严格的上三角阵.
    // 计算出Xn-1, Xn-2 ... X0.
    for (i = var - 1; i >= 0; i--)
    {
        temp = a[i][var];
        for (j = i + 1; j < var; j++)
        {
            if (a[i][j] != 0) temp -= a[i][j] * x[j];
        }
        if (temp % a[i][i] != 0) return -2; // 说明有浮点数解，但无整数解.
        x[i] = temp / a[i][i];
    }
return 0;
}
        
class EllysBulls
{
public:
 string getNumber(vector <string> guesses, vector <int> bulls)
 {
 //$CARETPOSITION$
    int i, j;
    memset(mat, 0, sizeof(mat));
    m = 10 * guesses[0].size();
    n = bulls.size() + guesses[0].size();
    for (i = 0; i < bulls.size(); i++) {
        for (j = 0; j < guesses[i].size(); j++) {
            int at = (guesses[i][j] - '0') + 10 * j;
            mat[i][at] = 1;
        }
        mat[i][m] = bulls[i];
    }
    for (i = 0; i < guesses[0].size(); i++) {
        for (j = 0; j < 10; j++) {
            mat[bulls.size() + i][i * 10 + j] = 1;
        }
        mat[bulls.size() + i][m] = 1;
    }


    memset(a, 0, sizeof(a));
    memset(x, 0, sizeof(x));
    memset(free_x, 1, sizeof(free_x));
    equ = n;
    var = m;
    for (i = 0; i < equ; i++) {
        for (j = 0; j < var + 1; j++) {
            a[i][j] = mat[i][j];
        }
    }

    debug();

    int free_num = Gauss();
    printf("equ = %d, var = %d, free_num = %d\n", equ, var, free_num);

    if (free_num == 0) {
        string ret = guesses[0];
        for (i = 0; i < m; i++) {
            if (x[i] == 1) {
                int at = i / 10;
                ret[at] = char('0' + (i%10));
            }
        }
        return ret;
    } else {
        if (free_num > 0) {
            return "Ambiguity";
        } else {
            return "Liar";
        }
    }
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); if ((Case == -1) || (Case == 5)) test_case_5(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"1234", "4321", "1111", "2222", "3333", "4444", "5555", "6666", "7777", "8888", "9999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 1, 1, 0, 2, 0, 0, 0, 1, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "1337"; verify_case(0, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_1() { string Arr0[] = {"0000", "1111", "2222"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 2, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Liar"; verify_case(1, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_2() { string Arr0[] = {"666666", "666677", "777777", "999999"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 3, 1, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "Ambiguity"; verify_case(2, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_3() { string Arr0[] = {"000", "987", "654", "321", "100", "010"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {2, 1, 0, 0, 1, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "007"; verify_case(3, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_4() { string Arr0[] = {"28", "92", "70", "30", "67", "63", "06", "65",
 "11", "06", "88", "48", "09", "65", "48", "08"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "54"; verify_case(4, Arg2, getNumber(Arg0, Arg1)); }
	void test_case_5() { string Arr0[] = {"0294884", "1711527", "2362216", "7666148", "7295642",
 "4166623", "1166638", "2767693", "8650248", "2486509",
 "6138934", "4018642", "6236742", "2961643", "8407361",
 "2097376", "6575410", "6071777", "3569948", "2606380"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = {1, 0, 1, 3, 4, 4, 3, 2, 1, 1, 0, 4, 4, 3, 0, 0, 0, 0, 2, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); string Arg2 = "4266642"; verify_case(5, Arg2, getNumber(Arg0, Arg1)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 EllysBulls ___test;
 ___test.run_test(-1);
}
// END CUT HERE
