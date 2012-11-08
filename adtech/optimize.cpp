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

string tostring(char v)
{
    stringstream ss;
    ss << int(v);
    return ss.str();
}

bool used[N][N];

struct ANS
{
    vector<vector<vector<int> > > rounds;

    //10 * 31 * 6 = 1860
    int calc_score()
    {
        int ret = 0;
        int i, j, u, v;
        memset(used, 0, sizeof(used));
        for (i = 0; i < 10; i++) {
            for (j = 0; j < 31; j++) {
                for (u = 0; u < 4; u++) {
                    for (v = u + 1; v < 4; v++) {
                        int x, y;
                        x = rounds[i][j][u];
                        y = rounds[i][j][v];
                        if (!used[x][y]) {
                            used[x][y] = true;
                            used[y][x] = true;
                            //fprintf(stderr, "x = %d, y = %d, v = %d\n", x, y, dis[x][y]);
                            ret += dis[x][y];
                        }
                    }
                }
            }
        }
        return ret;
    }


    void output()
    {
        int i, j, k;
        for (i = 0; i < rounds.size(); i++) {
            string ret = "";
            for (j = 0; j < rounds[i].size(); j++) {
                string temp = "";
                for (k = 0; k < rounds[i][j].size(); k++) {
                    if (k > 0) {
                        temp += ',';
                    }
                    temp += tostring(re_mapper(rounds[i][j][k]));
                }
                if (j > 0) {
                    ret += ';';
                }
                ret += temp;
            }
            cout<<ret<<endl;
        }
    }


    void input()
    {
        char buffer[1000];
        rounds.clear();
        while (gets(buffer)) {
            stringstream ssin(buffer);
            int i, j, val;
            char ch;
            vector<vector<int> > round;
            for (i = 0; i < 31; i++) {
                if (i > 0) {
                    ssin >> ch;
                }
                vector<int> single;
                for (j = 0; j < 4; j++) {
                    if (j > 0) {
                        ssin >> ch;
                    }
                    ssin >> val;
                    single.push_back(mapper(val));
                }
                round.push_back(single);
            }
            rounds.push_back(round);
        }
    }
} ans;

int next_int(int f, int r)
{
    return (int)(rand() * 1.0 / RAND_MAX * (r - f + 1) + f);
}

void change_number(ANS & temp)
{
    int r = next_int(0, 9);
    int px = next_int(0, 123);
    int tv = 125 * 124 / 2;
    for (int j = 0; j < 124; j++) {
        tv -= ans.rounds[r][j / 4][j % 4];
    }
    temp.rounds[r][px / 4][ px % 4] = tv;
}

void swap_number(ANS & temp, int times = 1)
{
    int r = next_int(0, 9);
    while (times --) {
        int px = next_int(0, 123);
        int py = next_int(0, 123);
        swap(temp.rounds[r][px / 4][px % 4], temp.rounds[r][py / 4][py % 4]);
    }
}

void optimize()
{
    int TIMES = 100000;
    int score = ans.calc_score();
    while (TIMES --) {
        if (TIMES % 100 == 0) {
            fprintf(stderr, "at TIMES = %d\n", TIMES);
        }
        ANS temp = ans;
        int ty, r, px, py;

        ty = next_int(0, 0);

        //change number
        if (ty == 0) {
            change_number(temp);
        } else {
            int swap_times = next_int(1, 4);
            swap_number(temp, swap_times);
        }

        int next_score = temp.calc_score();
        if (next_score > score) {
            ans = temp;
            fprintf(stderr, " score update from %d to %d\n", score, next_score);
            score = next_score;
        }
    }
}


int main() {
    srand(time(NULL));
    freopen("answer.origin", "r", stdin);
    //freopen("answer1", "r", stdin);
    freopen("answer.opti", "w", stdout);
    FILE *fp;
    fp = fopen("data_number_distance", "r");

    int x, y, d;
    vector<pair<int, pair<int, int> >  > vd;
    memset(dis, 0, sizeof(dis));
    while (fscanf(fp, "%d %d %d", &x, &y, &d) != EOF) {
        x = mapper(x);
        y = mapper(y);
        dis[x][y] = d;
        if (x < y) {
            vd.push_back(MP(d, MP(x, y)));
        }
    }

    ans.input();

    sort(vd.begin(), vd.end());
    int score_upperbound = 0;
    int nei[N];
    int total = 10 * 31 * 6;

    memset(nei, 0, sizeof(nei));
    for (int i =  vd.size() - 1; i >= 0 && total >= 0; i--) {
        d = vd[i].first;
        x = vd[i].second.first;
        y = vd[i].second.second;
        if (nei[x] == 33 || nei[y] == 33) {
            continue;
        }
        nei[x] ++; nei[y] ++;
        score_upperbound += d;
        total --;
    }

    optimize();
    fprintf(stderr, "score_upper = %d, cur_ans = %d\n", score_upperbound, ans.calc_score());
    ans.output();
    return 0;
}
