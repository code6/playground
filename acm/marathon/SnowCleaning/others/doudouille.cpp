#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <sys/time.h>
using namespace std;

#define NDEBUG

double TIME_LIMIT = 20;

struct CloudType {
  int size;
  int liveTime;
  double snowProbGlobal;
  double snowProbLocal[8][8];
  double moveProb[4];
};
int cloudCnt, cloudTypeCnt;
CloudType cloud_types[10];

struct Point {
  short x;
  short y;
  int step;
  int cumulative_step;
  int remove_gain;
  Point(int x, int y) : x(x), y(y), step(0), cumulative_step(0) {}
  Point() : x(-1), y(-1), step(0), cumulative_step(0) {}
  Point& operator+=(const Point &P) {x += P.x; y += P.y;}
  Point& operator-=(const Point &P) {x -= P.x; y -= P.y;}
};


struct Worker {
  Point pos;
  int step;
  int score;
  bool hired;
  bool best_permutation;
  vector<Point> path;
  Worker() : pos(), step(0), score(0), hired(false), best_permutation(false), path() {}
  bool operator<(const Worker &W2) {return score < W2.score;}
};

int ABS[256] = {128,127,126,125,124,123,122,121,120,119,118,117,116,115,114,113,112,111,110,109,108,107,106,105,104,103,102,101,100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127};
 
inline int dist( Point P1,  Point P2) {
//  cerr << P1.x << " " << P1.y << endl;
    return ABS[128+P1.x-P2.x] + ABS[128+P1.y - P2.y];}

int T[64][64];
int NBW;
Worker W[100];
int N;
int salary;
int snowfine;
int step;
int step_with_computation;
int total_snow;
int total_cost;
int nb_current_snow;
int nb_snow_day;
vector<string> actions;

class SnowCleaning {

  timeval STEP_BEGIN;
  double total_time;

  inline void start_step() {
    gettimeofday(&STEP_BEGIN, NULL);
  }
  inline void end_step() {
    timeval NOW; gettimeofday(&NOW, NULL);
    total_time += NOW.tv_sec - STEP_BEGIN.tv_sec + (NOW.tv_usec - STEP_BEGIN.tv_usec)/1000000.;
//    if(step % 100 == 0) cerr << "step " << step << ": " << total_time << "s" << endl;
  }
  inline double step_time() {
    timeval NOW; gettimeofday(&NOW, NULL);
    return NOW.tv_sec - STEP_BEGIN.tv_sec + (NOW.tv_usec - STEP_BEGIN.tv_usec)/1000000.;    
  }

  public:
  int init(int boardSize, int sal, int snowFine) {
    timeval BEGIN; gettimeofday(&BEGIN, NULL);
    srand(123457);
    N = boardSize;
    salary = sal;
    snowfine = snowFine;
    nb_current_snow = 0;
    step = 0;
    step_with_computation = 0;
    total_cost = 0;
    total_snow = 0;
    nb_snow_day = 0;
    memset(T, 0, sizeof(T));
    NBW = 0;
    timeval NOW; gettimeofday(&NOW, NULL);
    total_time = NOW.tv_sec - BEGIN.tv_sec + (NOW.tv_usec - BEGIN.tv_usec)/1000000.;
  }


  void print_path() {
    for(int i = 0; i < NBW; i++) {
      cerr << i << " : " << W[i].hired << " " << W[i].pos.x << " " << W[i].pos.y << " | ";
      for(int j = 0; j < W[i].path.size(); j++) cerr << "(" << W[i].path[j].x << "," << W[i].path[j].y << ") ";
      cerr << endl;
    }
    cerr << "======================" << endl;
  }

  struct PosDelta {
    int pos;
    int delta;
    PosDelta() :pos(-1), delta(-1) {}
  };

  int delta_insert_after(const Worker &worker, int pos, const Point &P) {
    int step1 = worker.path[pos].cumulative_step + dist(worker.path[pos], P);
    if(worker.hired && pos == 0) step1 = 0;
    int remaining = worker.path.size() - pos - 1;
    if(remaining > 0) remaining *= step1 + dist(P, worker.path[pos+1]) - worker.path[pos+1].cumulative_step;
    return step1 + remaining;
  }

  void compute_best_pos(int w, const vector<Point> &new_snow, vector<PosDelta> best_pos[]) {
    for(int j = 0; j < new_snow.size(); j++) {
      best_pos[j][w].pos = -1;
      best_pos[j][w].delta = 1000000;
      for(int pos = 0; pos < W[w].path.size(); pos++) {
        int delta = delta_insert_after(W[w], pos, new_snow[j]);
        if(delta < best_pos[j][w].delta) {
          best_pos[j][w].pos = pos;
          best_pos[j][w].delta = delta;
        }
      }
    }
  }

  void insert_after(Worker &worker, int pos, Point P) {
    worker.path.insert(worker.path.begin()+pos + 1, P);
    score(worker);
  }

  int insert_new_snow(vector<Point> new_snow) {
    vector<PosDelta> best_pos[20000];
    for(int i = 0; i < new_snow.size(); i++) best_pos[i].resize(NBW);
    for(int i = 0; i < NBW; i++) compute_best_pos(i, new_snow, best_pos);
    
    vector<int> best_worker(new_snow.size(), 0);
    for(int i = 0; i < best_worker.size(); i++) 
      for(int j = 0; j < NBW; j++)
        if(best_pos[i][j].delta < best_pos[i][best_worker[i]].delta)
          best_worker[i] = j;

    while(new_snow.size() > 0) {
      int min_snow = 0;
      int min_delta = 1000000;

      for(int i = 0; i < new_snow.size(); i++) 
        if(best_pos[i][best_worker[i]].delta < min_delta) {
          min_delta = best_pos[i][best_worker[i]].delta;
          min_snow = i;
        }      
      int w = best_worker[min_snow];
      insert_after(W[w], best_pos[min_snow][w].pos, new_snow[min_snow]);
      new_snow[min_snow] = new_snow.back();
      best_worker[min_snow] = best_worker.back();
      new_snow.pop_back();
      best_worker.pop_back();
      best_pos[min_snow].swap(best_pos[new_snow.size()]);
      compute_best_pos(w, new_snow, best_pos);

      for(int i = 0; i < best_worker.size(); i++) {        
        if(best_pos[i][w].delta < best_pos[i][best_worker[i]].delta)
          best_worker[i] = w;
        else if(best_worker[i] == w) {
          for(int j = 0; j < NBW; j++)
            if(best_pos[i][j].delta < best_pos[i][best_worker[i]].delta)
              best_worker[i] = j;
        }
      }
    }
  }


  struct Neighbour {
    Point pos;
    int step1;
    int worker1;
    int step2;
    int worker2;
    Neighbour(int x, int y) : pos(x,y), step1(1000000), worker1(-1), step2(1000000), worker2(-1) {}
    Neighbour() : pos(-1,-1), step1(1000000), worker1(-1), step2(1000000), worker2(-1) {}
    inline bool operator<(const Neighbour &N2) {
      return step1*100000 - step2*100 + T[pos.x][pos.y] < N2.step1*100000 - N2.step2*100 + T[N2.pos.x][N2.pos.y];
    }
  };

  void update_neighbour(Neighbour &Nb) {
    Nb.step1 = 100000;
    Nb.worker1 = -1;
    Nb.step2 = 100000;
    Nb.worker2 = -1;
    for(int i = 0; i < NBW; i++) {
      int d = W[i].step + dist(Nb.pos, W[i].path.back());
      if(d < Nb.step1) {
        Nb.step2 = Nb.step1;
        Nb.worker2 = Nb.worker1;
        Nb.step1 = d;
        Nb.worker1 = i;
      }
      else if(d < Nb.step2) {
        Nb.step2 = d;
        Nb.worker2 = i;
      }
    }
  }


    int init_greedy_path() {
      if(NBW == 0) return 0;

      vector<Neighbour> Target;
      for(int x = 0; x < N; x++) for(int y = 0; y < N; y++) if(T[x][y]) Target.push_back(Neighbour(x,y));

      for(int i = 0; i < NBW; i++) {
        W[i].path.clear();
        W[i].path.push_back(W[i].pos);
        W[i].step = 0;
      }
      for(int i = 0; i < Target.size(); i++) update_neighbour(Target[i]);

      while(true) {
        int best_i = 0;
        for(int i = 0; i < Target.size(); i++) if(Target[i] < Target[best_i]) best_i = i;
        int w = Target[best_i].worker1;
        W[w].step += dist(W[w].path.back(), Target[best_i].pos);
        W[w].path.push_back(Target[best_i].pos);
        Target[best_i] = Target[Target.size()-1];
        Target.pop_back();
        if(Target.size() == 0) break;
        for(int i = 0; i < Target.size(); i++) if(Target[i].worker1 == w || Target[i].worker2 == w) update_neighbour(Target[i]); 
      }

      return score();
    }

  int score(Worker &worker) {
    int score = 0;
    int cumulative_step = 0;
    worker.path[0].step = 0;
    worker.path[0].cumulative_step = 0;
    worker.path[0].remove_gain = 0;
    int start = 1;
    if(worker.hired && worker.path.size() > 1) {
      start = 2;
      worker.path[1].step = 0;
      worker.path[1].cumulative_step = 0;    
      worker.path[1].remove_gain = 0;
    }
    for(int i = start; i < worker.path.size(); i++) {
      int step = dist(worker.path[i-1], worker.path[i]);
      cumulative_step += step;
      worker.path[i].step = step;
      worker.path[i].cumulative_step = cumulative_step;
      worker.path[i].remove_gain = cumulative_step;
      if(i+1 < worker.path.size()) {
        worker.path[i].remove_gain += (dist(worker.path[i-1], worker.path[i+1]) - step - dist(worker.path[i], worker.path[i+1]))*(worker.path.size() - i - 1);
      }
      score += cumulative_step;
    }
    worker.score = score;
    return score;
  }


  int score() {
    int sc = 0;
    for(int i = 0; i < NBW; i++) sc += score(W[i]);
    return sc;
  }

  struct Perturbation {
    int delta;
    int type;
    int worker1;
    int worker2;
    int pos1;
    int pos2;
    int pos3;
    Perturbation() : delta(1000000000), type(-1), worker1(-1), worker2(-1), pos1(-1), pos2(-1), pos3(-1) {}
    bool operator<(const Perturbation &P) {return delta < P.delta;}
  };


  static const int nb_type_perturbation = 4;
  Perturbation perturbation_cache[100][100][nb_type_perturbation];
  bool valid_cache[100][100][nb_type_perturbation];

  void find_best_swap_block(int worker, Perturbation &P) {
    P.type = 0;
    P.worker1 = worker;
    P.worker2 = worker;
    for(int pos1 = 1; pos1 < W[worker].path.size(); pos1++)
      for(int pos2 = pos1+1; pos2 < W[worker].path.size(); pos2++) 
        for(int pos3 = pos2+1; pos3 < W[worker].path.size(); pos3++) {
          int delta =  delta_swap_block(W[worker], pos1, pos2, pos3);
          if(delta < P.delta) {
            P.delta = delta;
            P.pos1 = pos1;
            P.pos2 = pos2;
            P.pos3 = pos3;
          }
        }
  }

  void find_best_swap_end(int worker1, int worker2, Perturbation &P) {
    P.type = 1;
    P.worker1 = worker1;
    P.worker2 = worker2;
    for(int pos1 = 1; pos1 < W[worker1].path.size(); pos1++)
      for(int pos2 = 1; pos2 < W[worker2].path.size(); pos2++) {
        int delta =  delta_swap_end(W[worker1], pos1, W[worker2], pos2);
        if(delta < P.delta) {
          P.delta = delta;
          P.pos1 = pos1;
          P.pos2 = pos2;
        }
      }
  }
  
  bool find_best_simple_swap(int worker1, int worker2, Perturbation &P) {
    P.type = 3;
    P.worker1 = worker1;
    P.worker2 = worker2;
    for(int pos1 = 1; pos1 < W[worker1].path.size(); pos1++)
      for(int pos2 = 1; pos2 < W[worker2].path.size(); pos2++) {
        int delta =  delta_simple_swap(W[worker1], pos1, W[worker2], pos2);
        if(delta < P.delta) {
          P.delta = delta;
          P.pos1 = pos1;
          P.pos2 = pos2;
        }
      }
  }


  bool find_best_move_block_after(int worker1, int worker2, Perturbation &P) {
    P.type = 2;
    P.worker1 = worker1;
    P.worker2 = worker2;
    for(int pos1 = 1; pos1 < W[worker1].path.size(); pos1++)
      for(int pos2 = pos1; pos2 < W[worker1].path.size() && pos2 < pos1 + 3; pos2++) {
        if(pos2 == pos1 + 2) pos2 = W[worker1].path.size() - 1;
        for(int pos3 = 0; pos3 < W[worker2].path.size(); pos3++) {
          int delta =  delta_move_block_after(W[worker1], pos1, pos2, W[worker2], pos3);
          if(delta < P.delta) {
            P.delta = delta;
            P.pos1 = pos1;
            P.pos2 = pos2;
            P.pos3 = pos3;
          }
        }
      }
  }

  void make_perturbation(Perturbation P) {
    switch(P.type) {
      case 0: move_swap_block(W[P.worker1], P.pos1, P.pos2, P.pos3); break;
      case 1: move_swap_end(W[P.worker1], P.pos1, W[P.worker2], P.pos2); break;
      case 2: move_block_after(W[P.worker1], P.pos1, P.pos2, W[P.worker2], P.pos3); break;
      case 3: move_simple_swap(W[P.worker1], P.pos1, W[P.worker2], P.pos2); break;              
    }
    reset_perturbation_cache(P.worker1);
    reset_perturbation_cache(P.worker2);
    score(W[P.worker1]);
    score(W[P.worker2]);
    W[P.worker1].best_permutation = false;
    W[P.worker2].best_permutation = false;
  }


  bool get_best_perturbation(int worker1, int worker2, int type, Perturbation &P) {
    Perturbation &cache = perturbation_cache[worker1][worker2][type];
    if(!valid_cache[worker1][worker2][type]) {
      valid_cache[worker1][worker2][type] = true;
      cache.delta = 1000000000;
      switch(type) {
        case 0: if(worker1 == worker2) find_best_swap_block(worker1, cache); break;
        case 1: if(worker1 < worker2) find_best_swap_end(worker1, worker2, cache); break;
        case 2: if(worker1 != worker2) find_best_move_block_after(worker1, worker2, cache); break;
        case 3: if(worker1 < worker2) find_best_simple_swap(worker1, worker2, cache); break;              
      }
    }
    if(cache.delta != 1000000000) {
      P = cache;
      return true;
    }
    else return false;
  }

  void reset_perturbation_cache(int worker) {
    for(int i = 0; i < nb_type_perturbation; i++) 
      for(int j = 0; j < NBW; j++) {
        valid_cache[worker][j][i] = false;
        valid_cache[j][worker][i] = false;
      }
  }
  void  reset_perturbation_cache() {
    memset(valid_cache, 0, sizeof(valid_cache));
  }




  int _D[16][16];
  int best_permutation[16];
  int current_permutation[16];
  int mind[16];
  int nb_call;
  static const int max_call = 600;


  int find_best_permutation(int from, int nb, int max) {
    if(nb == 1) {
      memcpy(best_permutation, current_permutation, sizeof(best_permutation));
      return 0;
    }
    if(nb_call++ > max_call) return max;
    int best_sc = max;
    for(int i = 1; i < nb; i++) {
      int tmp = current_permutation[from+i];
      current_permutation[from+i] = current_permutation[from+1];
      current_permutation[from+1] = tmp;
      int sc = _D[current_permutation[from]][tmp] * (nb - 1);
      int min_bound = 0;
      for(int j = from+2; j < nb; j++) min_bound += mind[current_permutation[j]];

      if(sc + min_bound < best_sc) {
        sc += find_best_permutation(from+1, nb-1, best_sc - sc);
        if(sc < best_sc) best_sc = sc;
      }
      current_permutation[from+1] = current_permutation[from+i];
      current_permutation[from+i] = tmp;
    }
    return best_sc;
  }



  bool make_best_permutation(int w) {
    Worker &worker = W[w];
    if(worker.best_permutation) return false;    
//    if(worker.best_permutation || worker.path.size() > 9) return false;    

    int nb = min(int(worker.path.size()), 8);
    for(int i = 0; i < nb; i++) {current_permutation[i] = i; mind[i] = 1000;}
    for(int i = 0; i < nb; i++) for(int j = i+1; j < nb; j++) {
      _D[i][j] = _D[j][i] = dist(worker.path[i], worker.path[j]);
      if(_D[i][j] < mind[i]) mind[i] = _D[i][j]; 
      if(_D[i][j] < mind[j]) mind[j] = _D[i][j]; 
    }

   nb_call = 0;
    int sc = find_best_permutation(0, nb, worker.score);
    if(sc < worker.score) {
      vector<Point> tmp(worker.path);
      for(int i = 1; i < nb; i++) worker.path[i] = tmp[best_permutation[i]];
      score(worker);
    }
    worker.best_permutation = true;//nb_call < max_call;
    return sc < worker.score;
  }

  // [A] pos1 [B] pos2 [C] pos3 
  // W1 . . A a a a B b b C . . .  => . . B b b A a a a C . . . 
    inline int delta_swap_block(const Worker &W1, int pos1, int pos2, int pos3) {
      int nb1 = pos2 - pos1;
      int nb2 = pos3 - pos2;
      int remaining = W1.path.size() - pos3;
      int d1 = dist(W1.path[pos1-1], W1.path[pos2]) - W1.path[pos1].step;
      int d2 = dist(W1.path[pos3-1], W1.path[pos1]) - W1.path[pos2].step;
      if(W1.hired && pos1 == 1) d1 = 0;
      int d3 = 0; if(remaining > 0) d3 = dist(W1.path[pos2-1], W1.path[pos3]) - W1.path[pos3].step;
      int delta = (W1.path[pos1].cumulative_step - W1.path[pos2].cumulative_step + d1)*nb2 
        + (W1.path[pos3-1].cumulative_step - W1.path[pos2-1].cumulative_step + d1 + d2)*nb1
        + (d1 + d2 + d3)*remaining;
      return delta;
    }
    void move_swap_block(Worker &W1, int pos1, int pos2, int pos3) {
      W1.path.insert(W1.path.begin() + pos3, W1.path.begin() + pos1, W1.path.begin() + pos2);
      W1.path.erase(W1.path.begin() + pos1, W1.path.begin() + pos2);
      score(W1);
    }

  // [B] pos1 [b] pos2 [D] pos3
  // W1 . . A [B] b b [b] C . . .  => . . A C . . . 
  // W2 . . [D] E . . . .  => . . D B b b b E . . . .
    inline int delta_move_block_after(const Worker &W1, int pos1, int pos2, const Worker &W2, int pos3) {
      int remaining_1 = W1.path.size() - pos2 - 1;
      int remaining_2 = W2.path.size() - pos3 - 1;

      int d2 = dist(W2.path[pos3], W1.path[pos1]);
      if(W2.hired && pos3 == 0) d2 = 0;
      int delta = (W2.path[pos3].cumulative_step + d2 - W1.path[pos1].cumulative_step)*(pos2 - pos1 + 1);

      if(remaining_1) {
        int d1 = dist(W1.path[pos1-1], W1.path[pos2+1]);
        if(W1.hired && pos1 == 0) d1 = 0;
        delta += (W1.path[pos1-1].cumulative_step + d1 - W1.path[pos2+1].cumulative_step)*remaining_1;
      }
      if(remaining_2) delta += (W2.path[pos3].cumulative_step + d2 + W1.path[pos2].cumulative_step - W1.path[pos1].cumulative_step + dist(W1.path[pos2], W2.path[pos3+1]) - W2.path[pos3+1].cumulative_step)*remaining_2;
      return delta;
    }
    void move_block_after(Worker &W1, int pos1, int pos2, Worker &W2, int pos3) {
      W2.path.insert(W2.path.begin() + pos3 + 1, W1.path.begin() + pos1, W1.path.begin() + pos2 + 1);
      W1.path.erase(W1.path.begin() + pos1, W1.path.begin() + pos2 + 1);
      score(W1);
      score(W2);
    }


  // [A] pos1 [B] pos2
  // W1 . . A a a a a a  => . . B b b b
  // W2 . . B b b b      => . . A a a a a a
    inline int delta_swap_end(const Worker &W1, int pos1, const Worker &W2, int pos2) { // TODO pouvoir swaper toute la ligne pour nouvelle recrues...
      int nb1 = W1.path.size() - pos1;
      int nb2 = W2.path.size() - pos2;
      int d1 = dist(W1.path[pos1 - 1], W2.path[pos2]);
      int d2 = dist(W2.path[pos2 - 1], W1.path[pos1]);
      if(W1.hired && pos1 == 1) d1 = 0;
      if(W2.hired && pos2 == 1) d2 = 0;
      int delta = (W2.path[pos2 - 1].cumulative_step + d2 - W1.path[pos1].cumulative_step)*nb1
        + (W1.path[pos1 - 1].cumulative_step + d1 - W2.path[pos2].cumulative_step)*nb2;
      return delta;
    }
    void move_swap_end(Worker &W1, int pos1, Worker &W2, int pos2) {
      int nb1 = W1.path.size() - pos1;
      int nb2 = W2.path.size() - pos2;
      W1.path.insert(W1.path.end(), W2.path.begin() + pos2, W2.path.end());
      W2.path.insert(W2.path.end(), W1.path.begin() + pos1, W1.path.begin() + pos1 + nb1);
      W1.path.erase(W1.path.begin() + pos1, W1.path.begin() + pos1 + nb1);
      W2.path.erase(W2.path.begin() + pos2, W2.path.begin() + pos2 + nb2);
      score(W1);
      score(W2);
    }


      // [A] pos1 [B] pos2
  // W1 . . A . . .  => . . B . . .
  // W2 . . B . . .  => . . A . . .
    inline int delta_simple_swap(const Worker &W1, int pos1, const Worker &W2, int pos2) {
      int nb1 = W1.path.size() - pos1 - 1;
      int nb2 = W2.path.size() - pos2 - 1;
      int d1 = dist(W1.path[pos1 - 1], W2.path[pos2]);
      int d2 = dist(W2.path[pos2 - 1], W1.path[pos1]);
      if(W1.hired && pos1 == 1) d1 = 0;
      if(W2.hired && pos2 == 1) d2 = 0;

      int step_1 = W1.path[pos1 - 1].cumulative_step + d1;
      int step_2 = W2.path[pos2 - 1].cumulative_step + d2;
      int delta = step_1 - W2.path[pos2].cumulative_step + step_2 - W1.path[pos1].cumulative_step;
      if(nb1 > 0) delta += nb1*(step_1 + dist(W2.path[pos2],W1.path[pos1+1]) - W1.path[pos1+1].cumulative_step);
      if(nb2 > 0) delta += nb2*(step_2 + dist(W1.path[pos1],W2.path[pos2+1]) - W2.path[pos2+1].cumulative_step);
      return delta;
    }

    void move_simple_swap(Worker &W1, int pos1, Worker &W2, int pos2) {
      Point tmp = W1.path[pos1];
      W1.path[pos1] = W2.path[pos2];
      W2.path[pos2] = tmp;
      score(W1);
      score(W2);
    }

  Worker BEST_W[100];
  int best_score;

  void reset_best() {
    best_score = 1000000000;
  }

  bool save_best() {
    if(score() < best_score) {
      best_score = score();
      for(int i = 0; i < NBW; i++) BEST_W[i] = W[i];
      return true;
    }
    else return false;
  }
  void restore_best() {
    for(int i = 0; i < NBW; i++) W[i] = BEST_W[i];
  }


  int order1[100];
  int order2[100];

  void shuffle(int* TAB, int nb) {
    for(int i = nb - 1; i > 0; i--) {
      int tmp = TAB[i];
      int r = rand()%(i+1);
      TAB[i] = TAB[r];
      TAB[r] = tmp;
    }
  }


  void get_random_pos(int &w, int &pos, int nb_node) {
    int r = rand()%nb_node;
    int nb = 0;
    for(w = 0;  w < NBW && nb + W[w].path.size() - 1 <= r; w++) nb += W[w].path.size() - 1;
    pos = r - nb;
  }

  bool get_random_perturbation(Perturbation &P) {
    int nb_node = 0;
    for(int i = 0; i < NBW; i++) nb_node += W[i].path.size() - 1;
    if(nb_node <= 1) return false;
    get_random_pos(P.worker1, P.pos1, nb_node);
    get_random_pos(P.worker2, P.pos2, nb_node);
    P.pos1++;
    P.pos2++;

    P.type = 3;
    if(P.worker1 != P.worker2 && rand() % 100 < 80) P.type = 1;
    return true;
  }


    int improve_path(double time_fraction) {
      if(NBW == 0) return 0;

      int nb_minima = 0, nb_minina_since_best = 0;
      reset_perturbation_cache();
      reset_best();
      for(int i = 0; i < NBW; i++) order1[i] = order2[i] = i;

      int nb = 0;
    //  cerr << "##############################################" << endl;
      for(int loop = 0; ; loop++) {

        double remaining_time = 0.99*TIME_LIMIT - total_time;
        double nb_remaining_computation_step = 10. + (2001 - step) * double(step_with_computation)/double(step);
        double time_per_step = remaining_time / nb_remaining_computation_step;
        double t = step_time();

  //      cerr << time_per_step << " " << remaining_time << " " << nb_remaining_computation_step << endl;
   //     cerr << step << " " << step_with_computation << " " << time_fraction << " " << time_per_step << " " << t << " " << nb_minima << " " << nb_minina_since_best << " " << best_score << " " << score() << endl;
        if(t > time_fraction*time_per_step) {
//        if(nb_minina_since_best > 3) {
          save_best();
          break;
        }

        bool perm = false;
        for(int i = 0; i < NBW; i++) make_best_permutation(i);
//        if(NBW == 1 && W[0].best_permutation) break;

        shuffle(order1, NBW);
        shuffle(order2, NBW);

        int ordt[4] = {1, 2, 3};

        Perturbation best_P;
        best_P.delta = 1000000000;
        for(int type = 0; best_P.delta >= 0 && type < 3; type++) 
          for(int i = 0; best_P.delta >= 0 && i < NBW; i++) {
            if(ordt[type] == 0 && W[order1[i]].best_permutation) continue;
            for(int j = 0; best_P.delta >= 0 && j < NBW; j++) {
              Perturbation P;
              if(get_best_perturbation(order1[i], order2[j], ordt[type], P)) if(P < best_P) {
                best_P = P;
                //            cerr << best_P.worker1 << " " << best_P.worker2 << " " << best_P.delta << endl;
              }
            }
          }

        if(best_P.delta >= 0) {
          nb_minima++;
          nb_minina_since_best++;
          if(save_best()) nb_minina_since_best = 0;
        
          if(nb_minina_since_best % 3 == 0) restore_best();

          for(int i = 0; i < 1 + nb_minina_since_best; i++) {
            Perturbation P;
            if(!get_random_perturbation(P)) break;
            make_perturbation(P);
          }
        }
        else {
//          int sc1 = score();
          make_perturbation(best_P);
//          int sc2 = score();
/*          if(sc2 - sc1 != best_P.delta) {
            print_path();
            cerr << "ERRRRORRR  " << sc2 - sc1 << " " << best_P.delta << endl;
          }*/
        }

      }
      restore_best();

      return score();
    }


  bool make_hire() {
    if(NBW >= 100) return false;
    W[NBW].pos = Point(-1, -1);
    W[NBW].path.clear();
    W[NBW].path.push_back(Point(-1, -1));
    W[NBW].path[0].cumulative_step = 0;
    W[NBW].path[0].step = 0;
    W[NBW].hired = true;
    W[NBW].best_permutation = false;
    NBW++;
    return true;
  }

  bool make_move(int id) {

    int dx = W[id].path[1].x - W[id].path[0].x;
    int dy = W[id].path[1].y - W[id].path[0].y;
    int d = abs(dx) + abs(dy);

    if(d > 0) {
      int r = rand()%d; // idee : plutot que random optimiser le chemin et privilegier chemin disjoints....
      if(r < abs(dx)) {dx = dx / abs(dx); dy = 0;}
      else {dx = 0; dy = dy/abs(dy);}
    }

    W[id].pos.x += dx;
    W[id].pos.y += dy;
    W[id].path[0] = W[id].pos;

    if(dx == 0 && dy == 0) return false;
    assert(W[id].pos.x >= 0 && W[id].pos.x < N);
    assert(W[id].pos.y >= 0 && W[id].pos.y < N);
    ostringstream S;
    S << "M " << id << " ";
    if(dx == -1) {S << 'U'; assert(dy == 0);}
    else if(dx == 1)  {S << 'D'; assert(dy == 0);}
    else if(dy == -1) {S << 'L'; assert(dx == 0);}
    else if(dy == 1)  {S << 'R'; assert(dx == 0);}
    else {
      cerr << dx << " " << dy << endl;
      for(int i = 0; i < W[id].path.size(); i++) cerr << W[id].path[i].x << " " << W[id].path[i].y << endl;
    }
    //    cerr << S.str() << endl;
    actions.push_back(S.str());
    return true;
  }

  bool make_hire(int id) {
    while(W[id].path.size() <= 1) {
      if(!W[NBW-1].hired) {
        cerr << "ERRRROR" << endl;
        cerr << id << " " << W[id].path.size() << " " << W[id].pos.x << " " << W[id].pos.y << endl;
        W[id].path.push_back(Point(N/2, N/2));
        continue;
      }
      W[id] = W[NBW-1];
      NBW--;
      if(NBW == id) return false;
    }
    W[id].pos = W[id].path[1];
    W[id].hired = false;
    W[id].path.erase(W[id].path.begin());

    ostringstream S;
    S << "H " << W[id].pos.x << " " << W[id].pos.y;
    actions.push_back(S.str());
    return true;
  }

  void make_cleaning() {
    for(int i = 0; i < NBW; i++) {
      if(T[W[i].pos.x][W[i].pos.y]) nb_current_snow--;
      T[W[i].pos.x][W[i].pos.y] = 0;
    }
    for(int i = 0; i < NBW; i++) {
      bool rescore = false;
      for(int j = 1; j < W[i].path.size(); j++)
        if(T[W[i].path[j].x][W[i].path[j].y] == 0) {
          W[i].path.erase(W[i].path.begin()+j);
          W[i].best_permutation = false;
          j--;
          rescore = true;
        }
      if(rescore) score(W[i]);
    }
  }


  float Fx[100], Fy[100];
  inline float force(int dx, int dy) { // param
    int d = (dx*dx+dy*dy);
    if(d == 0) return 10;
    return 1./float(d);
  }

    void compute_deployment() {
      memset(Fx, 0, sizeof(Fx));
      memset(Fy, 0, sizeof(Fy));
      for(int i = 0; i < NBW; i++) if(W[i].path.size() == 1) {
        Fx[i] +=  2*force(W[i].pos.x, 0);
        Fy[i] +=  2*force(W[i].pos.y, 0);
        Fx[i] -=  2*force((N-1-W[i].pos.x), 0);
        Fy[i] -=  2*force((N-1-W[i].pos.y), 0); // tester force des mur assymétrique en fonction du vent....
        for(int j = i; j < NBW; j++) if(W[j].path.size() == 1) 
          if(i != j) {
            int dx = W[j].pos.x - W[i].pos.x;
            int dy = W[j].pos.y - W[i].pos.y;
            float f = force(dx, dy);
            if(dx == 0) dx = 1-2*rand()%2;
            if(dy == 0) dy = 1-2*rand()%2;
            if(dx > 0) {Fx[i] -= f; Fx[j] += f;} else {Fx[i] += f; Fx[j] -= f;}
            if(dy > 0) {Fy[i] -= f; Fy[j] += f;} else {Fy[i] += f; Fy[j] -= f;}
          }
      }
      for(int i = 0; i < NBW; i++) if(W[i].path.size() == 1) {
        int dx = 0, dy = 0;
        if(abs(Fx[i]) > abs(Fy[i])) dx = Fx[i]<0?-1:1;
        else dy = Fy[i]<0?-1:1;
        Point P(W[i].pos.x + dx, W[i].pos.y + dy);
        if(P.x >= 0 && P.x < N && P.y >= 0 && P.y < N) W[i].path.push_back(P);
      }
    }


  void init_stat(const vector<int> &S) {
    step++;
    actions.clear();    
    if(S.size() > 0) nb_snow_day++;
    total_snow += S.size()/2;
    for(int i = 0; i < S.size(); i += 2) {
      if(T[S[i]][S[i+1]] == 0) nb_current_snow++;
      T[S[i]][S[i+1]] = step;
    }
  }


  Point choose_hire_pos() {
    Point best_pos(N/2,N/2);
    int best_dist = 0;
    for(int x = 0; x < N; x++)
      for(int y = 0; y < N; y++) 
        if(T[x][y]) {
          int d = 1000;
          for(int i = 0; i < NBW; i++) if(dist(W[i].pos, Point(x,y)) < d) d = dist(W[i].pos, Point(x,y));
          if(d > best_dist) {
            best_dist = d;
            best_pos.x = x;
            best_pos.y = y;
          } 
        }
    return best_pos;
  }

  void hire_first_worker() {
    Point P = choose_hire_pos();
    make_hire();
    W[0].path.push_back(P);
    init_greedy_path();
  }


  void move_node_end(int w1, int pos1, int w2) {

    int step = 0;
    int cumulative_step = 0;
    if(W[w2].path.size() > 1) {
      cumulative_step = W[w2].path.back().cumulative_step;
      step = dist(W[w2].path.back(), W[w1].path[pos1]);
      cumulative_step += step;
    }

    W[w2].path.push_back(W[w1].path[pos1]);
    W[w2].path.back().step = step;
    W[w2].path.back().cumulative_step = cumulative_step;
    W[w1].path.erase(W[w1].path.begin() + pos1);
    score(W[w1]);
    W[w1].best_permutation = false;
  }


  void insert_new_worker(int w) {
    score();
    int best_remove_gain = 1000000000;
    int best_i, best_j;
    for(int i = 0; i < NBW; i++) if(i != w) 
      for(int j = 1; j < W[i].path.size(); j++) 
        if(W[i].path[j].remove_gain < best_remove_gain) {
          best_remove_gain = W[i].path[j].remove_gain;
          best_i = i;
          best_j = j;
        }
    move_node_end(best_i, best_j, w);
    while(true) {
      best_remove_gain = 1000000000;
      for(int i = 0; i < NBW; i++) if(i != w) 
        for(int j = 1; j < W[i].path.size(); j++) {
          int gain = dist(W[w].path.back(), W[i].path[j]) - W[i].path[j].remove_gain;
          if(gain < best_remove_gain) {
            best_remove_gain = gain;
            best_i = i;
            best_j = j;
          }
        }
      if(best_remove_gain + W[w].path.back().cumulative_step < 0) move_node_end(best_i, best_j, w);
      else break;
    }
    score(W[w]);
  }

  void last_day_hire() {
    if(salary < snowfine)
      for(int x = 0; NBW < 100 && x < N; x++)
        for(int y = 0; NBW < 100 && y < N; y++)
          if(T[x][y]) {
            NBW++;
            ostringstream S;
            S << "H " << x << " " << y;
            actions.push_back(S.str());
          }
  }



  bool decide_hire(int cost, double FF) {
    if(nb_snow_day == 0) return false;
    if(NBW == 0) return true;
    double proba_snow = nb_snow_day / double(step);
    double snow_per_step = total_snow / double(step + 20);
    double snow_per_snow_day = total_snow / double(nb_snow_day);

    int cleaning_time = 0;
    int cumul_cleanning_step = 0;
    for(int i = 0; i < NBW; i++) {
      cumul_cleanning_step += W[i].path.back().cumulative_step;
      if(W[i].path.back().cumulative_step > cleaning_time) cleaning_time = W[i].path.back().cumulative_step;
    }
    double current_cleanning_rate = nb_current_snow / double(cumul_cleanning_step);

    int best_reduc = 0;
    for(int i = 0; i < NBW; i++) {
      for(int j = 1; j < W[i].path.size(); j++) {
        int red = W[i].path[j].cumulative_step * (W[i].path.size() - j);
        if(red > best_reduc) best_reduc = red;
      }
    }

/*
    cerr << "proba_snow = " << proba_snow << endl;
    cerr << "NBW = " << NBW << endl;
    cerr << "cost = " << cost << endl;
    cerr << "snow_per_step = " << snow_per_step << endl;
    cerr << "nb_current_snow = " << nb_current_snow << endl;
    cerr << "snowfine = " << snowfine << endl;
    cerr << "salary = " << salary << endl;
    cerr << "cumul_cleanning_step = " << cumul_cleanning_step << endl;
    cerr << "mean_cleaning_step = " << cumul_cleanning_step / double(NBW) << endl;

    cerr << "current snow per worker = " << nb_current_snow/double(NBW) << endl;

    cerr << cost << " " << cost/double(nb_current_snow) << " " << cost/double(nb_current_snow)*snow_per_step << " " << cost/double(nb_current_snow)*snow_per_step*snowfine << " " << salary << " " << current_cleanning_rate*NBW << " " << 5*snow_per_step << endl; 
*/

//    cerr << best_reduc << " " << best_reduc*snowfine << " " << (2001 - step)*salary << endl;
    if(1.9*best_reduc*snowfine >= (2001 - step)*salary) {
//      cerr << "HHHHAAHAA" << endl;
      return true;
    }

    if(cost/double(nb_current_snow)*snow_per_step*snowfine < 2*salary) return false;
    return (FF > 35);
  }



  vector <string> nextDay(const vector<int> &S) {
    start_step();
    vector<Point> new_snow;
    for(int i = 0; i < S.size(); i+=2) 
      if(T[S[i]][S[i+1]] == 0) 
        new_snow.push_back(Point(S[i],S[i+1]));
    init_stat(S);
    if(S.size() > 0) {
      step_with_computation++;
      if(NBW == 0) hire_first_worker();
      else insert_new_snow(new_snow);

      int cost = improve_path(1);
      total_cost += cost;
      double cc = cost + total_cost/double(step);

      for(int i = 0; i < 3 && decide_hire(cost, (cc/2 * snowfine) / (salary * NBW)); i++) {
        if(!make_hire()) break;
        //cerr << step << " hire" << endl;
        insert_new_worker(NBW-1);
        cost = improve_path(i+2);
        total_cost += cost;
        cc = cost + total_cost/double(step);
      }

    }
    compute_deployment();

    for(int i = 0; i < NBW; i++) {
      if(W[i].hired) make_hire(i);
      else if(W[i].path.size() > 1) make_move(i);      
    }
    /*
       print_path();
       for(int x = 0; x < N; x++)
       for(int y = 0; y < N; y++) 
       if(T[x][y])
       cerr << "(" << x << "," << y << ") ";
       cerr << endl;
       */

    make_cleaning();
    end_step();
    //  if(step == 2000) last_day_hire();
    return actions;
  }
};

int main(int argc, char ** argv) {
    int boardSize;
    int salary;
    int snowFine;

    cin >> boardSize;
    cin >> salary;
    cin >> snowFine;

    SnowCleaning sn;
    sn.init(boardSize, salary, snowFine);
    for (int  t = 0; t < 2000; t++) {
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
};
