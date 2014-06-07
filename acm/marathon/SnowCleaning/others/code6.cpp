/*
 *  0. 人可以更少
 *  1. 中心点重新分配 (done)
 *  2. 雇人计划更严格 (done)
 *      不能一次加一片工人
 *  3. assign 优化
 *  4. 引入雪块概念
 *  5. 添加新的脚本来调参数
 *      *  确定需要调整的参数
 */


#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

const int SIMULATION_TIME = 2000;
const int INF = 100000000;
const int NEAR_DISTANCE = 0;
const int MAX_WORKERS = 100;
const int MAX_BOARDSZIE = 55;
const char* DIR_STR = "DLUR";
const int dir[][2] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

typedef pair<int, int> PII;
typedef vector<vector<int> > VVI;
#define mp make_pair

int global_interval_factor = -1;


int dist(PII x, PII y) {
    return abs(x.first - y.first) + abs(x.second - y.second);
}

int get_dir(PII x, PII y) {
    int d, offset;
    int r = rand() % 2;
    if (r) {
        d = -1;
        offset = 1;
    } else {
        d = 4;
        offset = -1;
    }
    for (int t = 0; t < 4; t++) {
        d += offset;
        PII tmp = mp(x.first + dir[d][0], x.second + dir[d][1]);
        if (dist(tmp, y) < dist(x, y)) {
            return d;
        }
    }
    return -1;
}

string getMoveCmd(int id, int d) {
    char dir_ch = DIR_STR[d];
    char buf[100];
    sprintf(buf, "M %d %c", id, dir_ch);
    string cmd = buf;
    return cmd;
}

string getHireCmd(PII p) {
    char buf[100];
    sprintf(buf, "H %d %d", p.first, p.second);
    string cmd = buf;
    return cmd;
}


PII walk(PII x, int d) {
    return mp(x.first + dir[d][0], x.second + dir[d][1]);
}

vector<int> assign_4(VVI graph) {
    int n = graph.size();
    int m = graph[0].size();
    int i,j;

    vector<int> assign;
    for (i = 0; i < n; i++) {
        assign.push_back(-1);
    }

    while (true) {
        int best_dist = INF;
        PII bpos;
        for (i = 0; i < n; i++)  {
            for (j = 0; j < m; j++) {
                if (best_dist > graph[i][j]) {
                    best_dist = graph[i][j];
                    bpos = mp(i, j);
                }
            }
        }
        if (best_dist < INF) {
            assign[bpos.first] = bpos.second;
            for (i = 0; i < n; i++) {
                for (j = 0; j < m; j++) {
                    if (i == bpos.first || j == bpos.second) {
                        graph[i][j] = INF;
                    }
                }
            }
        } else {
            break;
        }
    }
    return assign;
}

vector<int> simple_matching(vector< vector<int> > worker_snow) {
    int i, j;
    int n = worker_snow.size();
    vector<int> assign;
    if (n == 0) {
        return assign;
    }
    return assign_4(worker_snow);
}


class Worker {
    public:
        int id;
        PII cur_pos;
        PII center_pos;
        int radius;

    bool cover(PII p) {
        return 
            (
        p.first >= center_pos.first - radius &&
        p.first <= center_pos.first + radius &&
        p.second >= center_pos.second - radius &&
        p.second <= center_pos.second + radius
        ) or (
        p.first >= cur_pos.first - radius &&
        p.first <= cur_pos.first + radius &&
        p.second >= cur_pos.second - radius &&
        p.second <= cur_pos.second + radius
        );
    }
};

class SnowCleaning {
    public:
        int boardSize;
        int salary;
        int snowFine;
        int best_workernum;
        int best_radius;
        int interval_factor;

        vector<Worker> workers;
        vector<PII> snows;
        VVI worker_snow;
        int worker_cnt;
        bool hasSnow[MAX_BOARDSZIE][MAX_BOARDSZIE];

        bool isvalid(PII p) {
            return 0 <= p.first && p.first < boardSize &&
                0 <= p.second && p.second < boardSize;
        }

        void init_worker() {
            srand(1);
            worker_cnt = 0;
            workers.clear();
        }

        void calc_interval_factor() {
            double per = 1.0 *  snowFine / salary;
            double c1 = 5.5;
            double c2 = 0.75;
            if (boardSize < 30) {
                c1 = 4.5;
                c2 = 0.65;
            }
            interval_factor = round(max(2.0, (boardSize / c1) * (1.0 - c2 * log(per) / log(10.0))));
        }

        void calc_best_workernum() {
            best_radius = round(interval_factor * 3 / 2.0);
            double num = boardSize / interval_factor;
            best_workernum = round(num * num);
        }

        int init(int boardSize, int salary, int snowFine) {
            this->boardSize = boardSize;
            this->salary = salary;
            this->snowFine = snowFine;

            if (global_interval_factor > 0) {
                interval_factor = global_interval_factor;
            } else {
                calc_interval_factor();
            }
            calc_best_workernum();
            init_worker();
            memset(hasSnow, 0, sizeof(hasSnow));
            return 0;
        }

        void addSnow(int x, int y) {
            hasSnow[x][y] = true;
        }

        void cleanSnow(PII p) {
            hasSnow[p.first][p.second] = false;
        }

        vector<PII> gen_center_pos() {
            double part_cnt = sqrt(worker_cnt + 1.0);
            int part = floor(boardSize / part_cnt);
            int sz = floor((boardSize - part * 1.0) / part) + 1;
            int i, j;
            vector<PII> vp;
            for (i = 0; i < sz; i++) {
                int x = max(1, min(boardSize - 2, (int) round(part / 2.0 + i * part)));
                for (j = 0; j < sz; j++) {
                    int y = max(1, min(boardSize - 2, (int) round(part / 2.0 + j * part)));
                    PII p = mp(x, y);
                    if (isvalid(p)) {
                        vp.push_back(p);
                    }
                }
            }

            vector<PII> ans;
            vector<PII> bk = vp;
            PII center = mp(boardSize / 2, boardSize / 2);
            for (i = 0; i < worker_cnt; i++) {
                int best = -1;
                int bestp = -1;
                if (vp.size() > 0) {
                    for (j = 0; j < vp.size(); j++) {
                        int tmp = dist(center, vp[j]);
                        if (tmp > best) {
                            best = tmp;
                            bestp = j;
                        }
                    }
                    ans.push_back(vp[bestp]);
                    swap(vp[bestp], vp[vp.size()-1]);
                    vp.pop_back();
                } else {
                    ans.push_back(center);
                }
            }

            return ans;
        }

        void worker_change_center_position() {
            int i, j;
            vector<PII> center_pos = gen_center_pos();
            VVI worker_center;
            for (i = 0; i < worker_cnt; i++) {
                vector<int> row;
                for (j = 0; j < worker_cnt; j++) {
                    row.push_back(dist(workers[i].cur_pos, center_pos[j]));
                }
                worker_center.push_back(row);
            }
            vector<int> assign = simple_matching(worker_center);
            for (i = 0; i < worker_cnt; i++) {
                workers[i].center_pos = center_pos[assign[i]];
            }
        }

        bool worker_near(PII p) {
            for (int i = 0; i < workers.size(); i++) {
                if (dist(workers[i].cur_pos, p) <= NEAR_DISTANCE) {
                    return true;
                }
            }
            return false;
        }

        vector<string> nextDay(vector<int> snowFalls) {

            worker_change_center_position();

            vector<string> commands;

            for (int i = 0; i < snowFalls.size(); i+=2) {
                addSnow(snowFalls[i], snowFalls[i + 1]);
            }

            snows.clear();
            for (int i = 0; i < boardSize; i++) {
                for (int j = 0; j < boardSize; j++) {
                    if (hasSnow[i][j]) {
                        snows.push_back(mp(i, j));
                    }
                }
            }

            worker_snow.clear();
            for (int i = 0; i < workers.size(); i++) {
                vector<int> cur_row(snows.size());
                for (int j = 0; j < snows.size(); j++) {
                    if (workers[i].cover(snows[j])) {
                        cur_row[j] = dist(workers[i].cur_pos, snows[j]);
                    } else {
                        cur_row[j]  = INF;
                    }
                }
                worker_snow.push_back(cur_row);
            }

            vector<int> assign = simple_matching(worker_snow);

            for (int i = 0; i < workers.size(); i++) {
                PII target;
                if (assign[i] != -1) {
                    target = snows[assign[i]];
                } else {
                    target = workers[i].center_pos;
                }
                if (workers[i].cur_pos != target) {
                    int d = get_dir(workers[i].cur_pos, target);
                    string cmd = getMoveCmd(workers[i].id, d);
                    commands.push_back(cmd);
                    PII next_pos = walk(workers[i].cur_pos, d);
                    workers[i].cur_pos = next_pos;
                }
                cleanSnow(workers[i].cur_pos);
            }

            for (int r = 0; r < boardSize; r++) {
                for (int c = 0; c < boardSize; c++) {
                    if (hasSnow[r][c] && !worker_near(mp(r, c))) {
                        if (worker_cnt < best_workernum) {
                            Worker cur_worker;
                            cur_worker.id = worker_cnt++;
                            cur_worker.radius = best_radius;
                            cur_worker.cur_pos = cur_worker.center_pos = mp(r, c);
                            string cmd = getHireCmd(cur_worker.cur_pos);
                            workers.push_back(cur_worker);
                            commands.push_back(cmd);
                            cleanSnow(cur_worker.cur_pos);
                        } 
                    }
                }
            }

            return commands;
        }
};

int main(int argc, char ** argv) {
    int boardSize;
    int salary;
    int snowFine;

    cin >> boardSize;
    cin >> salary;
    cin >> snowFine;

    if (argc > 1) {
         global_interval_factor = atoi(argv[1]);
    } else {
        global_interval_factor = -1;
    }

    fprintf(stderr, "boardsize = %d\nper_fine = %d\nper_salary = %d\n", boardSize, salary, snowFine);

    SnowCleaning sn;
    sn.init(boardSize, salary, snowFine);
    for (int  t = 0; t < SIMULATION_TIME; t++) {
        int snowCnt;
        cin >> snowCnt;
        vector<int> snowFalls;
        for (int i = 0; i < 2 * snowCnt; i++) {
            int pos;
            cin >> pos;
            snowFalls.push_back(pos);
        }
        vector<string> ret = sn.nextDay(snowFalls);
        cout<<ret.size()<<endl;
        for (int i = 0; i < ret.size(); i++) {
           cout<<ret[i].c_str()<<endl;
        }
        cout.flush();
    }
    return 0;
}
