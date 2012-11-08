#include <functional>
#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include <cctype>
#include <vector>
#include <string>
#include <bitset>
#include <cmath>
#include <queue>
#include <stack>
#include <ctime>
#include <list>
#include <map>
#include <set>
 
using namespace std;
 
#define PB push_back
#define MP make_pair
 
typedef vector<int> VI;
typedef vector<string> VS;
typedef vector<double> VD;
typedef pair<int,int> PII;
typedef long long LL;
typedef unsigned long long ULL;

int mapper(int n)
{
    return n > 60 ? n - 2 : n - 1;
}

int re_mapper(int n)
{
    return n >= 59 ? n + 2 : n + 1;
}

const int N = 125;
const int N4 = 244140625;
const int N2 = 15625;
int dis[N][N];
struct Node
{
    char pl[4];
    char score;
    bool operator<(const Node& rhs) const {
        return score < rhs.score;
    }
};

vector<Node> vs;
bool used[N][N];
bool vis[N];

char calc_score(int s)
{
    int i, j;
    char ret = 0;
    for (i = 0; i < 4; i++) {
        for (j = i + 1; j < 4; j++) {
            int pa = vs[s].pl[i];
            int pb = vs[s].pl[j];
            if (!used[pa][pb]) {
                ret += dis[pa][pb];
            }
        }
    }
    return ret;
}

string tostring(char v)
{
    stringstream ss;
    ss << int(v);
    return ss.str();
}


void process()
{
    memset(used, 0, sizeof(used));
    int i, j, k;

    for (int round = 1; round <= 10; round ++) {
        fprintf(stderr, "at round = %d\n", round);
        string ret = "";
        int  gcnt = 0;
        memset(vis, 0, sizeof(vis));
        for (i = vs.size() - 1; i >= 0 ; i--) {
            vs[i].score = calc_score(i);
        }

        sort(vs.begin(), vs.end());
        for (i = vs.size() - 1; i >= 0 ; i--) {
            Node & cur = vs[i];
            bool  ok = true;
            for (j = 0; j < 4; j++) {
                if (vis[cur.pl[j]]) {
                    ok = false;
                    break;
                }
            }

            if (ok) {
                string temp = "";
                for (j = 0; j < 4; j++) {
                    if (temp != "") {
                        temp += ',';
                    }
                    temp += tostring(re_mapper(cur.pl[j]));
                    vis[cur.pl[j]] = true;
                }
                if (ret != "") {
                    ret += ";";
                }
                ret += temp;

                for (j = 0; j < 4; j++) {
                    for (k = j + 1; k < 4; k++) {
                        int pa, pb;
                        pa = cur.pl[j];
                        pb = cur.pl[k];
                        used[pa][pb] = used[pb][pa] = true;
                    }
                }

                gcnt ++;
                if (gcnt == 31) {
                    break;
                }
            }
        }
        cout<<ret<<endl;
    }
}

int main() {
    freopen("data_number_distance", "r", stdin);
    freopen("my.out", "w", stdout);
    int x, y, d;
    while (cin >> x >> y >> d) {
        x = mapper(x);
        y = mapper(y);
        dis[x][y] = d;
    }

    int i, j, s, cs;
    for (s = 0; s < N4; s++) {
        Node cur;
        cs = s;
        for (i = 0; i < 4; i++) {
            cur.pl[i] = cs % N;
            cs /= N;
        }
        bool ok = true;
        for (i =  0;  i < 4; i++) {
            for (j = i + 1; j < 4; j++) {
                if (cur.pl[i] == cur.pl[j]) {
                    ok = false;
                }
            }
        }
        if (ok) {
            vs.push_back(cur);
        }
    }

    process();


    return 0;
}

