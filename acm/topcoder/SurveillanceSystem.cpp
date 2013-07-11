// BEGIN CUT HERE
/*
// PROBLEM STATEMENT
// There is a long narrow storehouse.
The storehouse is divided into a sequence of N identical sectors, labeled 0 through N-1.
Each sector is large enough to contain a single container.
Currently, some sectors are empty and some sectors are filled by containers.
The storehouse also contains a surveillance system that is described below.

We are going to break into the storehouse.
As a part of preparation for the heist, we already found out some information about the warehouse.
In particular, we know exactly how the containers are currently placed in the warehouse.
You are given a string containers consisting of N characters.
For each i, character i of containers is 'X' if sector i contains a container, and it is '-' if sector i is empty.

We also discovered some information about the surveillance system.
The system consists of several hidden cameras.
You are given a int L with the following meaning:
Each of the cameras monitors exactly L consecutive sectors.
The segments of sectors monitored by different cameras might overlap, but no two cameras watch exactly the same segment.
(In other words, each sector may be monitored by multiple cameras, but each camera monitors a different set of consecutive sectors.)

Finally, we know something about what the cameras currently see.
You are given a vector <int> reports.
Each element of reports corresponds to one of the cameras (in no particular order).
More precisely, reports[i] is the number of containers stored in the sectors monitored by the corresponding camera.

It is guaranteed that all our information is correct and consistent.

Your task is to use the provided information to deduce which sectors are monitored by at least one surveillance camera.
Return a string containing N characters.
For each i, character i of the return value should be one of '+', '?', and '-'.
Character '+' represents that sector i is certainly monitored by at least one camera.
Character '-' represents that sector i is certainly not monitored by any of the cameras.
Character '?' represents the remaining case: given the information we have, it is possible that sector i is monitored, but it is also possible that it is not monitored.

DEFINITION
Class:SurveillanceSystem
Method:getContainerInfo
Parameters:string, vector <int>, int
Returns:string
Method signature:string getContainerInfo(string containers, vector <int> reports, int L)


CONSTRAINTS
-containers will contain N elements, where N is between 1 and 50, inclusive.
-Each character in containers will be either 'X' or '-'.
-L will be between 1 and N, inclusive.
-reports will contain between 1 and N-L+1 elements, inclusive.
-Each element of reports will be between 0 and L, inclusive.
-The given information will be consistent.


EXAMPLES

0)
"-X--XX"
{1, 2}
3

Returns: "??++++"

This storehouse has 6 sectors.
There are containers in sectors 1, 4, and 5.
There are two cameras: camera #0 monitors 1 container, and camera #1 monitors 2 containers.
Clearly, camera #1 must be watching sectors 3, 4, and 5.
Camera #0 may be watching sectors (0, 1, 2), (1, 2, 3), or (2, 3, 4).
Thus, camera #0 is surely monitoring sector 2.
Sectors 0 and 1 may or may not be monitored.

1)
"-XXXXX-"
{2}
3

Returns: "???-???"

The camera is monitoring either the leftmost or the rightmost segment, thus the middle sector is surely not under surveillance.

2)
"------X-XX-"
{3, 0, 2, 0}
5

Returns: "++++++++++?"

We can deduce that cameras #1 and #3 are watching segments (0, 1, 2, 3, 4) and (1, 2, 3, 4, 5). Camera #2 is monitoring the segment (4, 5, 6, 7, 8), since this is the only segment with two occupied sectors. Camera #0 is either watching (5, 6, 7, 8, 9) or (6, 7, 8, 9, 10), thus the rightmost sector might have slipped from the surveillance.

3)
"-XXXXX---X--"
{2, 1, 0, 1}
3

Returns: "???-??++++??"



4)
"-XX--X-XX-X-X--X---XX-X---XXXX-----X"
{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}
7

Returns: "???++++?++++++++++++++++++++??????--"



*/
// END CUT HERE
#line 110 "SurveillanceSystem.cpp"
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

int n;
bool ok(vector<int> avail, vector<int> need) {
    map<int, int> M;
    for (int  i = 0; i < avail.size(); i++) M[avail[i]] ++;
    for (int  i = 0; i < need.size(); i++) {
        M[need[i]] --;
        if (M[need[i]] < 0) {
            return false;
        }
    }
    return true;
}

class SurveillanceSystem
{
public:
 string getContainerInfo(string containers, vector <int> reports, int L)
 {
 //$CARETPOSITION$
    n = containers.size();
    string ans = "";
    vector<int> avail;
    int i, j, k;
    for (int i = 0; i < n; i++) {
        j = i + L - 1;
        if (j >= n) break;
        int sum = 0;
        for (k = i; k <= j; k++) {
            sum += containers[k] == 'X';
        }
        avail.push_back(sum);
    }

    for (i = 0; i < n; i++) {
        bool can_cover, must_cover;
        can_cover = must_cover = false;
        vector<int> no_cover_arr;
        for (j = 0; j < avail.size(); j++) {
            if (j<= i && i <= j + L - 1) {
                for (k = 0; k < reports.size(); k++) {
                    if (reports[k] == avail[j]) {
                        break;
                    }
                }
                if (k == reports.size()) {
                    continue;
                }
                vector<int> next_reports = reports;
                swap(next_reports[k], next_reports[next_reports.size() - 1]);
                next_reports.pop_back();

                vector<int> next_avail = avail;
                swap(next_avail[j], next_avail[next_avail.size() - 1]);
                next_avail.pop_back();

                if (ok(next_avail, next_reports)) {
                    can_cover = true;
                }

            } else {
                //if (n < 10) printf("i = %d, put %d %d at no_cover\n", i, j, avail[j]);
                no_cover_arr.push_back(avail[j]);
            }
        }


        if (ok(no_cover_arr, reports)) {
            must_cover = false;
        } else {
            must_cover = true;
        }
        if (must_cover) {
            ans += "+";
        } else {
            if (can_cover) {
                ans += "?";
            } else {
                ans += '-';
            }
        }
    }
    return ans;
 }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const string &Expected, const string &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arg0 = "-X--XX"; int Arr1[] = {1, 2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "??++++"; verify_case(0, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arg0 = "-XXXXX-"; int Arr1[] = {2}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "???-???"; verify_case(1, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arg0 = "------X-XX-"; int Arr1[] = {3, 0, 2, 0}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 5; string Arg3 = "++++++++++?"; verify_case(2, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arg0 = "-XXXXX---X--"; int Arr1[] = {2, 1, 0, 1}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 3; string Arg3 = "???-??++++??"; verify_case(3, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arg0 = "-XX--X-XX-X-X--X---XX-X---XXXX-----X"; int Arr1[] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arg2 = 7; string Arg3 = "???++++?++++++++++++++++++++??????--"; verify_case(4, Arg3, getContainerInfo(Arg0, Arg1, Arg2)); }

// END CUT HERE

}; 
// BEGIN CUT HERE
int main()
{
 SurveillanceSystem ___test;
 ___test.run_test(-1);
}
// END CUT HERE
