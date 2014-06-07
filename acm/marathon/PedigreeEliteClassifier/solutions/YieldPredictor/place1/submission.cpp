#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <cstring>
#include <sys/time.h>
#include <set>

using namespace std;



int MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

vector<string> tokenize(string str, char delim = ',') {
  vector<string> T;
  string token;
  istringstream S(str);
  while(getline(S, token, delim)) T.push_back(token);
  return T;
}


// 0: PCP (100 .. 3200)
// 1: TMP (-200 .. 10000)
// 2: PDSI (-1000 .. 1000)
// 3: ZNDX (-1000 .. 1000)
// 4: CCD  (-600 .. 2000)
// 5: HDD  (-1000 .. 1000)
// 6: SP01  (-300 .. 300)
// 7: SP02  (-300 .. 300)
// 8: SP03  (-300 .. 300)
// 9: SP06  (-300 .. 300)
// 10: SP09 (-300 .. 300)
// 11: SP12 (-300 .. 300)
// 12: SP24 (-300 .. 300)
map<int, map<int, vector<int> > > NOAA;
map<int, map<int, vector<int> > > LOC_NOAA;
void init_NOAA(vector<string> V) {
  for(int i = 0; i < V.size(); i++) {
    vector<string> T = tokenize(V[i]);
    if(T.size() != 18) continue;
    int loc = 100*atoi(T[0].c_str()) + atoi(T[1].c_str());
    int date = atoi(T[2].c_str());
    
    vector<int> R;
    for(int i = 3; i < 18; i++) R.push_back((int) (atof(T[i].c_str())*100.));
    R[6] /= 100;
    R[7] /= 100;
    NOAA[loc][date] = R;
  }
}


map<int, map<int, vector<int> > > DMonitor;
map<int, map<int, vector<int> > > LOC_DMonitor;
void init_DMonitor(vector<string> V) {
  for(int i = 0; i < V.size(); i++) {
    vector<string> T = tokenize(V[i]);
    if(T.size() != 8) continue;
    int fips = atoi(T[1].c_str());
    int date = atoi(T[0].c_str());
    vector<int> R;
    for(int i = 2; i < 8; i++) R.push_back((int) (atof(T[i].c_str())*100.));
    DMonitor[fips][date] = R;
  }
}

// 0: X (27 .. 49)
// 1: Y (-101 .. -75)
// 2: maturity (3 .. 12)
// 3: submaturity (1 .. 3)
// 4: maturityband (1 .. 5)
map<int, vector<int> > LOC;
void init_location(vector<string> V) {
  map<int, int> NB;

  for(int i = 0; i < V.size(); i++) {
    vector<string> T = tokenize(V[i]);
    if(T.size() != 10) continue;
    int loc = atoi(T[0].c_str());
    NB[loc]++;

    vector<int> R;
    R.push_back(int(atof(T[1].c_str()) * 10)); // X
    R.push_back(int(atof(T[2].c_str()) * 10)); // Y
    R.push_back(3 + atoi(T[4].c_str()));       // Maturity
    if(T[5] == "Early") R.push_back(1); // Sub maturity
    else if(T[5] == "Mid") R.push_back(2);
    else if (T[5] == "Late") R.push_back(3);
    else R.push_back(0);   
    R.push_back(atoi(T[6].c_str())); // Maturity Band


    R.push_back(atoi(T[7].c_str())); // Maturity Band
    R.push_back(atoi(T[8].c_str())); // Maturity Band
    R.push_back(atoi(T[9].c_str())/1000); // Maturity Band


    if(LOC[loc].size() == 0) LOC[loc] = R;
    else for(int i = 0; i < LOC[loc].size(); i++) LOC[loc][i] += R[i];

    int noaa_id = atoi(T[7].c_str()) * 100 + atoi(T[8].c_str());
    for(map<int, vector<int> >::iterator it = NOAA[noaa_id].begin(); it != NOAA[noaa_id].end(); ++it) {
      if(LOC_NOAA[loc][it->first].size() == 0) LOC_NOAA[loc][it->first] = it->second;
      else for(int i = 0; i < LOC_NOAA[loc][it->first].size(); i++)
        LOC_NOAA[loc][it->first][i] += (it->second)[i];
    }
    int fips = atoi(T[9].c_str());
    for(map<int, vector<int> >::iterator it = DMonitor[fips].begin(); it != DMonitor[fips].end(); ++it) {
      if(LOC_DMonitor[loc][it->first].size() == 0) LOC_DMonitor[loc][it->first] = it->second;
      else for(int i = 0; i < LOC_DMonitor[loc][it->first].size(); i++)
        LOC_DMonitor[loc][it->first][i] += (it->second)[i];
    }

    loc = 1000 * (loc/1000);
    NB[loc]++;

    if(LOC[loc].size() == 0) LOC[loc] = R;
    else for(int i = 0; i < LOC[loc].size(); i++) LOC[loc][i] += R[i];

    for(map<int, vector<int> >::iterator it = NOAA[noaa_id].begin(); it != NOAA[noaa_id].end(); ++it) {
      if(LOC_NOAA[loc][it->first].size() == 0) LOC_NOAA[loc][it->first] = it->second;
      else for(int i = 0; i < LOC_NOAA[loc][it->first].size(); i++)
        LOC_NOAA[loc][it->first][i] += (it->second)[i];
    }
    for(map<int, vector<int> >::iterator it = DMonitor[fips].begin(); it != DMonitor[fips].end(); ++it) {
      if(LOC_DMonitor[loc][it->first].size() == 0) LOC_DMonitor[loc][it->first] = it->second;
      else for(int i = 0; i < LOC_DMonitor[loc][it->first].size(); i++)
        LOC_DMonitor[loc][it->first][i] += (it->second)[i];
    }
  }

  for(map<int,int>::iterator it = NB.begin(); it != NB.end(); ++it) {
    int loc = it->first;
    int nb = it->second;
    for(int i = 0; i < LOC[loc].size(); i++) 
      LOC[loc][i] = (int) (0.5 + double(LOC[loc][i]) / double(nb));
    for(map<int, vector<int> >::iterator it = LOC_NOAA[loc].begin(); it != LOC_NOAA[loc].end(); ++it)
      for(int i = 0; i < (it->second).size(); i++) (it->second)[i] = (int) (0.5 + double((it->second)[i]) / double(nb));
    for(map<int, vector<int> >::iterator it = LOC_DMonitor[loc].begin(); it != LOC_DMonitor[loc].end(); ++it)
      for(int i = 0; i < (it->second).size(); i++) (it->second)[i] = (int) (0.5 + double((it->second)[i]) / double(nb));

  }
}



class Key {
  public: 
  int index;
  int LOCCD;
  int MaterialId;
  int HERB;
  int RM;
  int SRM;
  int PlantDate;
  Key(string LOCCD, string MaterialID, string HERB, string RM, string PlantDate) {
    this->LOCCD = atoi(LOCCD.c_str());
    this->MaterialId = atoi(MaterialID.c_str());
    if(HERB == "conv") this->HERB = 1;
    else if(HERB == "RR1") this->HERB = 2;
    else if(HERB == "RR2Y") this->HERB = 3;
    else this->HERB = 0;

    for(int i = 0; i < RM.length(); i++) if(RM[i] == '.') {RM.erase(i,1); break;}
    if(RM.find("000") == 0)     {this->RM = 1; RM.erase(0, 3);}
    else if(RM.find("00") == 0) {this->RM = 2; RM.erase(0, 2);}
    else if(RM.find("0") == 0)  {this->RM = 3; RM.erase(0, 1);}
    else if(RM.find("10") == 0) {this->RM = 13; RM.erase(0, 2);}
    else if(RM.find("1") == 0)  {this->RM = 4; RM.erase(0, 1);}
    else if(RM.find("2") == 0)  {this->RM = 5; RM.erase(0, 1);}
    else if(RM.find("3") == 0)  {this->RM = 6; RM.erase(0, 1);}
    else if(RM.find("4") == 0)  {this->RM = 7; RM.erase(0, 1);}
    else if(RM.find("5") == 0)  {this->RM = 8; RM.erase(0, 1);}
    else if(RM.find("6") == 0)  {this->RM = 9; RM.erase(0, 1);}
    else if(RM.find("7") == 0)  {this->RM = 10; RM.erase(0, 1);}
    else if(RM.find("8") == 0)  {this->RM = 11; RM.erase(0, 1);}
    else if(RM.find("9") == 0)  {this->RM = 12; RM.erase(0, 1);}
    else {this->RM = 0; RM = "";}

    if(RM.length() > 0) this->SRM = (RM[0] - '0');
    else this->SRM = 0;

    this->PlantDate = 0;
    for(int i = 0; i < PlantDate.length(); i++) 
      if(PlantDate[i] >= '0' && PlantDate[i] <= '9') 
        this->PlantDate = this->PlantDate*10 + PlantDate[i] - '0';

  }
};


vector<Key> TRAINKEY;
vector<float> YIELD;

Key parse_training(string line, float &yield) {
  istringstream S(line);
  vector<string> T;
  string token;
  while(getline(S, token, ',')) T.push_back(token);
  while(T.size() < 9) T.push_back("");

  yield = atof(T[5].c_str());
  return Key(T[1], T[3], T[4], T[7], T[8]);
}

struct Extractor {
  virtual int extract(const Key &K) = 0;
  virtual string print() = 0;
  virtual ~Extractor() {}
};

class Bucket {
  unsigned short *BUFFER;

  int N;
  Extractor *E;
  bool ready;
  vector<double> SUM;
  vector<int> NB;
  vector<float> PRED;
  float alpha;
  public:


  //TODO
  void bufferize() {
    vector<int> TMP(TRAINKEY.size());
    for(int i = 0; i < TRAINKEY.size(); i++) TMP[i] = get_key(TRAINKEY[i]);
    BUFFER = new unsigned short[TRAINKEY.size()];
    for(int i = 0; i < TRAINKEY.size(); i++) BUFFER[i] = TMP[i];
  }

  void compute_pred() {
    double M = 0;
    int nb = 0;
    for(int i = 0; i < N; i++) {M += SUM[i]; nb += NB[i];}
    M /= double(nb);
    for(int i = 0; i < N; i++) PRED[i] = alpha * (SUM[i] + M) / double(NB[i] + 1);
    ready = true;
  }

  int get_key(const Key &K) {
    if(BUFFER) return BUFFER[K.index];
//    int k = E->buffer_extract(K); // TODO remove buffer !!!
      int k = E->extract(K); // TODO remove buffer !!!
    k %= N;
    if(k < 0) k += N;
    return k;
  }


  Bucket(int N, Extractor *E, float alpha = 0.05) : E(E), N(N), alpha(alpha), SUM(N), NB(N), PRED(N), BUFFER(0) { reset(); }
  void train(const Key &K, float obs) {
    ready = false;
    int k = get_key(K);
    SUM[k] += obs;
    NB[k]++;
  }

  void reset() {
    ready = false;
    memset(&SUM[0], 0, N*sizeof(double));
    memset(&NB[0], 0, N*sizeof(int));
  }

  string print() {
    ostringstream S;
    S << "Bucket(" << N << ", new " << E->print() << "," << alpha << ")";
    return S.str();
  }

  float predict(const Key &K) {
    if(!ready) compute_pred();
    return PRED[get_key(K)];
  }

};


struct _LOCID : public Extractor {
  int extract(const Key &K) {return K.LOCCD;}
  string print() {return "_LOCID()";}
};

struct _LOCID2 : public Extractor {
  int extract(const Key &K) {return K.LOCCD/1000;}
  string print() {return "_LOCID2()";}
};

struct _MaterialId : public Extractor {
  int extract(const Key &K) {return K.MaterialId;}
  string print() {return "_MaterialId()";}
};

struct _HERB : public Extractor {
  int extract(const Key &K) {return K.HERB;}
  string print() {return "_HERB()";}
};

struct _RM : public Extractor {
  int extract(const Key &K) {return K.RM;}
  string print() {return "_RM()";}
};

struct _SRM : public Extractor {
  int extract(const Key &K) {return K.SRM;}
  string print() {return "_SRM()";}
};

struct _YEAR : public Extractor {
  int extract(const Key &K) {return K.PlantDate / 10000;}
  string print() {return "_YEAR()";}
};

struct _DAY : public Extractor {
  int extract(const Key &K) {return K.PlantDate % 100;}
  string print() {return "_DAY()";}
};

struct _MONTH : public Extractor {
  int extract(const Key &K) {return (K.PlantDate / 100) % 100;}
  string print() {return "_MONTH()";}
};

struct _DAYOFYEAR : public Extractor {
  int extract(const Key &K) {
    int dayOfYear = _DAY().extract(K);
    int month = _MONTH().extract(K);
    for(int i = 0; i < month - 1; i++) dayOfYear += MONTH[i];
    return dayOfYear;
  }
  string print() {return "_DAYOFYEAR()";}
};

struct _CLIMATE : public Extractor {
  const int source;
  const int pos;
  const int length;
  const int offset;
  const int relative;
  const map<int, map< int, vector<int> > > &MAP;

  _CLIMATE(int source, int pos, int length, int offset, int relative = 1) 
    : source(source), pos(pos), length(length), offset(offset), relative(relative), MAP((source == 1)?LOC_NOAA:LOC_DMonitor) {}

  int extract(const Key &K) {
    int year = _YEAR().extract(K);
    int loc = _LOCID().extract(K);
    int date;

    if(source == 1) 
      date = year*100 + _MONTH().extract(K);
    else 
      date = K.PlantDate;
   
    if(!relative) {
      if(source == 1) date = year*100 + 1;
      else date = year*10000 + 7;
    }

    if(MAP.find(loc) == MAP.end()) loc = 1000*(loc/1000);
    if(MAP.find(loc) == MAP.end()) return -9999;

    const map<int, vector<int> > &M = MAP.find(loc)->second;
    map<int, vector<int> >::const_iterator it = M.lower_bound(date);

    if(offset < 0) for(int k = 0; k < -offset; k++) --it;
    else if(offset > 0) for(int k = 0; k < offset && it != M.end(); k++) ++it;

    int nb = 0, sum = 0;
    for(; nb < length && it != M.end(); ++it) {
      sum += (it->second)[pos];
      nb++;
    }
    if(nb > 0) return sum / nb;
    else return 0;
  }

  string print() {
    ostringstream S;
    S << "_CLIMATE(" << source << "," << pos << "," << length << "," << offset << "," << relative << ")";
    return S.str();
  }
};


struct _LOCVAR : public Extractor {
  int index;
  _LOCVAR(int index) : index(index) {} 

  int extract(const Key &K) {
    int loc = _LOCID().extract(K);
    if(LOC.find(loc) == LOC.end()) loc = 1000*(loc/1000);
    map<int, vector<int> >::iterator it = LOC.find(loc);
    if(it == LOC.end()) return 0;
    else return (it->second)[index];
  }

  string print() {
    ostringstream S;
    S << "_LOCVAR(" << index << ")";
    return S.str();
  }
};



struct _PAIR : public Extractor {
  Extractor* E1;
  Extractor* E2;
  int A1, A2, d1, d2;

  _PAIR(Extractor *E1, Extractor *E2, int A1, int A2, int d1 = 1, int d2 = 1) : E1(E1), E2(E2), A1(A1), A2(A2), d1(d1), d2(d2) {}

  int extract(const Key &K) {
    int v1 = E1->extract(K);
    int v2 = E2->extract(K);
    return A1*(v1/d1) + A2*(v2/d2);
  }
  string print() {
    ostringstream S;
    S << "_PAIR(new " << E1->print() << ",new " << E2->print() << "," << A1 << "," << A2 << "," << d1 << "," << d2 << ")";
    return S.str();
  }


};



timeval BEGIN; 
inline double time() {
  timeval NOW; gettimeofday(&NOW, NULL);
  return NOW.tv_sec - BEGIN.tv_sec + (NOW.tv_usec - BEGIN.tv_usec)/1000000.;    
}


class YieldPredictor {
set<int> Var;
  public:
    vector<Bucket*> Predictor;
    void init_predictor() {
      Predictor.push_back(new Bucket(1, new _LOCID(), 1.));
      double alpha = 0.1;
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5294, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-2,1),167,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5294, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-2,1),167,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5171, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,1,3,-4,1),183,1,1,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5993, new _PAIR(new _LOCID(),new _YEAR(),155,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5917, new _PAIR(new _LOCID(),new _CLIMATE(1,6,1,0,1),190,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,9,1,-6,1),136,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5171, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,1,3,-4,1),183,1,1,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,9,1,-6,1),136,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5957, new _PAIR(new _LOCID(),new _CLIMATE(1,6,1,2,1),178,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5845, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,2,-3,1),199,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5866, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,1,6,1),137,1,2,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5171, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,1,3,-4,1),183,1,1,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5950, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,1,0,1),179,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5989, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,11,-7,1),154,1,2,89), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,1,6,1),199,1,2,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5845, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,2,-3,1),199,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5981, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,7,-2,1),161,1,2,126), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5963, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,11,-9,1),105,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5683, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,1,1,1),167,1,2,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5473, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,-5,1),132,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5682, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,10,1),190,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5977, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,2,15,1),105,1,2,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5938, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,2,0),143,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5768, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,4,4,0),154,1,2,123), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5852, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,9,-3,1),104,1,2,106), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,8,4,0),101,1,2,81), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5763, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,16,-17,1),110,1,2,45), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5809, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,5,0),103,1,2,113), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5919, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,13,1),180,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5878, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,10,0),121,1,2,109), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5797, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,11,-10,1),108,1,2,111), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5955, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,5,-5,1),131,1,2,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5974, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,5,-3,1),114,1,2,118), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,9,1,-6,1),136,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,2,5,0),105,1,2,123), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5987, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,5,0,1),169,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5959, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,11,1),107,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5788, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,3,-2,1),101,1,2,106), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5868, new _PAIR(new _YEAR(),new _MaterialId(),164,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5871, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,9,-3,1),183,1,2,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5696, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,7,-3,1),126,1,2,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5844, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,3,-2,1),164,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5923, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-5,1),179,1,2,129), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,8,4,0),185,1,2,129), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5969, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,-1,1),new _CLIMATE(0,2,2,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,-1,1),new _CLIMATE(0,4,2,-1,1),1,1,1,1),1,1,1,1),143,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5721, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,2,2,0),165,1,2,115), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5932, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,3,1),151,1,2,123), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,2,1),144,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5836, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,8,1),118,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,0,1),171,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5998, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,0,1),111,1,2,114), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5776, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,-1,1),109,1,2,91), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5150, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),150,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5997, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,1,10,1),105,1,2,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5956, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,-6,1),183,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5784, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-7,1),188,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5783, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,5,-2,1),185,1,2,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5954, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,17,1),new _CLIMATE(0,2,1,17,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,17,1),new _CLIMATE(0,4,1,17,1),1,1,1,1),1,1,1,1),141,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5697, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,2,1),171,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5966, new _PAIR(new _SRM(),new _MaterialId(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5201, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,11,-11,1),133,1,2,121), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5894, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),104,1,2,125), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5808, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-8,1),124,1,2,107), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5721, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,15,1),108,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5930, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-9,1),new _CLIMATE(0,2,8,-9,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-9,1),new _CLIMATE(0,4,8,-9,1),1,1,1,1),1,1,1,1),117,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5915, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-5,1),110,1,2,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5947, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,4,1),163,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5739, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,5,1,1),145,1,2,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5958, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,1,-1,1),161,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5901, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,4,1),159,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,9,0),176,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5984, new _PAIR(new _MONTH(),new _MaterialId(),111,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5801, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,4,-5,1),174,1,1,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5883, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,1,1),124,1,2,113), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5424, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,15,1),198,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5890, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,-6,1),113,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5737, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,8,7,1),192,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5969, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-3,1),172,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5780, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,1,0),113,1,2,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5791, new _PAIR(new _MaterialId(),new _LOCVAR(2),175,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5919, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,13,1),180,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5676, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,9,-6,1),138,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5936, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,0,1),172,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5548, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,3,1),197,1,2,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,16,-1,1),146,1,2,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5770, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,0,1),175,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-1,1),168,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5641, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,7,1),new _CLIMATE(0,2,2,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,7,1),new _CLIMATE(0,4,2,7,1),1,1,1,1),1,1,1,1),172,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5909, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,5,1,1),184,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5677, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-6,1),187,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5845, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,0,0),160,1,2,90), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-2,1),108,1,1,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5734, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-7,1),124,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,-1,1),157,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5919, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,2,8,0),112,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),100,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5931, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,1,1),139,1,1,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5320, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,5,0),100,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5934, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,4,1),176,1,2,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5381, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,15,1),new _CLIMATE(0,2,4,15,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,15,1),new _CLIMATE(0,4,4,15,1),1,1,1,1),1,1,1,1),173,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5982, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,3,1),111,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5990, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,1,1),104,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5943, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,6,0),138,1,2,100), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5846, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-1,1),new _CLIMATE(0,2,8,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-1,1),new _CLIMATE(0,4,8,-1,1),1,1,1,1),1,1,1,1),195,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5643, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-9,1),175,1,2,95), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5781, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-6,1),148,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,17,1),177,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5654, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,1,1),180,1,2,81), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5917, new _PAIR(new _LOCID(),new _CLIMATE(1,6,1,0,1),190,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5696, new _PAIR(new _LOCID(),new _CLIMATE(1,10,1,-1,1),156,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,2,1),168,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5672, new _PAIR(new _MaterialId(),new _CLIMATE(1,8,1,3,1),129,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5893, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,5,1),new _CLIMATE(0,2,1,5,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,5,1),new _CLIMATE(0,4,1,5,1),1,1,1,1),1,1,1,1),111,1,1,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5527, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-11,1),191,1,2,124), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5930, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,11,-6,1),131,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5821, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,8,4,0),102,1,2,110), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5701, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,9,0),165,1,2,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,1,1),187,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5463, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,3,0),138,1,2,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5573, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,3,1),154,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5613, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,3,1),new _CLIMATE(0,2,4,3,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,3,1),new _CLIMATE(0,4,4,3,1),1,1,1,1),1,1,1,1),106,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5579, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),179,1,1,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5508, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-7,1),142,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5561, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,7,1),new _CLIMATE(0,2,8,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,7,1),new _CLIMATE(0,4,8,7,1),1,1,1,1),1,1,1,1),123,1,2,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5730, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-4,1),178,1,1,83), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5711, new _PAIR(new _LOCVAR(3),new _MaterialId(),159,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5592, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),170,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5956, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,-6,1),183,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5945, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,4,2,0),197,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5683, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,4,0,0),162,1,1,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5150, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),150,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,2,1),144,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,7,-2,1),111,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5881, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,9,-9,1),169,1,2,107), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,18,1),147,1,2,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),138,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5438, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),134,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5720, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-6,1),121,1,2,93), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5795, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),102,1,1,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5692, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,3,2,1),173,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5649, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,1,1),138,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5598, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,0,1),141,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5534, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,0,1),139,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5497, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-2,1),144,1,2,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5611, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-4,1),154,1,2,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5612, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,1,14,1),162,1,1,49), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5697, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,2,1),171,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5485, new _PAIR(new _LOCVAR(0),new _MaterialId(),120,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5947, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-2,1),151,1,2,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5789, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-8,1),123,1,2,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5875, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,5,1,1),165,1,1,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5289, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,17,1),156,1,2,33), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5667, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,14,1),new _CLIMATE(0,2,1,14,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,14,1),new _CLIMATE(0,4,1,14,1),1,1,1,1),1,1,1,1),191,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,1,1),109,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5653, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,3,1,1),100,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5844, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,8,4,0),124,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5424, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,15,1),198,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5889, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,7,-1,1),127,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5814, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,8,0),195,1,2,91), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-1,1),168,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5901, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,4,1),159,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5928, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,0,1),154,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5708, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,11,-7,1),187,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5319, new _PAIR(new _MaterialId(),new _CLIMATE(1,8,1,-6,1),132,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,0,1),114,1,1,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5596, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,4,8,0),110,1,1,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5832, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,4,3,1),114,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5320, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-2,1),159,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5828, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,7,-6,1),125,1,1,82), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5230, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,1,1),191,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5982, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,3,1),111,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5145, new _PAIR(new _LOCVAR(1),new _MaterialId(),122,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,16,-1,1),new _CLIMATE(0,2,16,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,16,-1,1),new _CLIMATE(0,4,16,-1,1),1,1,1,1),1,1,1,1),184,1,2,34), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-2,1),108,1,1,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5923, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-5,1),179,1,2,129), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5900, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,5,1),155,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5952, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-9,1),102,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5608, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,16,-1,1),168,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5653, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,9,-10,1),112,1,1,127), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5890, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,-6,1),113,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5954, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,17,1),new _CLIMATE(0,2,1,17,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,17,1),new _CLIMATE(0,4,1,17,1),1,1,1,1),1,1,1,1),141,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5090, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,11,1),new _CLIMATE(0,2,4,11,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,11,1),new _CLIMATE(0,4,4,11,1),1,1,1,1),1,1,1,1),125,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5776, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,-1,1),109,1,2,91), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5575, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,14,1),102,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5687, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,5,0),126,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5489, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,1,1),110,1,2,118), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5579, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),179,1,1,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5747, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,0,1),193,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5931, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,1,1),139,1,1,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5677, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-6,1),187,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5758, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,2,7,1),136,1,1,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,16,-1,1),146,1,2,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5441, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,2,0),180,1,2,121), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5791, new _PAIR(new _MaterialId(),new _LOCVAR(2),175,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5374, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,9,1),new _CLIMATE(0,2,1,9,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,9,1),new _CLIMATE(0,4,1,9,1),1,1,1,1),1,1,1,1),157,1,2,45), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5492, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,11,-11,1),114,1,1,102), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5222, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,3,1),192,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5663, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,5,1),172,1,2,102), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5373, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,3,1),184,1,1,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5592, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),170,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5322, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,0,1),163,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5687, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-1,1),147,1,2,81), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5054, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,-2,1),130,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5015, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,3,1),154,1,1,124), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5894, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),104,1,2,125), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5412, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,4,-1,1),159,1,1,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5478, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,1,1),170,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5287, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,0,1),135,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5234, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,5,1),143,1,1,33), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5268, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,17,1),new _CLIMATE(0,2,2,17,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,17,1),new _CLIMATE(0,4,2,17,1),1,1,1,1),1,1,1,1),194,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,0,1),171,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5438, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),134,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5044, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,16,-17,1),188,1,1,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5293, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,1,5,1),120,1,2,90), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5485, new _PAIR(new _LOCVAR(0),new _MaterialId(),120,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5567, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),179,1,2,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),138,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,2,1),168,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5388, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-8,1),124,1,2,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5325, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,-1,1),new _CLIMATE(0,2,2,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,-1,1),new _CLIMATE(0,4,2,-1,1),1,1,1,1),1,1,1,1),197,1,1,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5584, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,8,-1,1),182,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5478, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,1,-2,1),159,1,2,83), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5639, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,9,-7,1),125,1,1,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5846, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-1,1),new _CLIMATE(0,2,8,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-1,1),new _CLIMATE(0,4,8,-1,1),1,1,1,1),1,1,1,1),195,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5191, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,7,1),124,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5381, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-4,1),122,1,2,115), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5711, new _PAIR(new _LOCVAR(3),new _MaterialId(),159,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5508, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-7,1),142,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5251, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,0,1),139,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5593, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,8,1),new _CLIMATE(0,2,1,8,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,8,1),new _CLIMATE(0,4,1,8,1),1,1,1,1),1,1,1,1),108,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5721, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,15,1),108,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5613, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,5,1),153,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5529, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,3,3,1),116,1,2,89), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5234, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-10,1),164,1,2,90), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5770, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,0,1),175,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5577, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,-1,1),180,1,2,110), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5730, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-4,1),178,1,1,83), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5893, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,5,1),new _CLIMATE(0,2,1,5,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,5,1),new _CLIMATE(0,4,1,5,1),1,1,1,1),1,1,1,1),111,1,1,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5145, new _PAIR(new _LOCVAR(1),new _MaterialId(),122,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5784, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-7,1),188,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5152, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,4,11,1),148,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5628, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,3,-3,1),138,1,1,100), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5795, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),102,1,1,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5672, new _PAIR(new _MaterialId(),new _CLIMATE(1,8,1,3,1),129,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5998, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,0,1),111,1,2,114), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5573, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,3,1),154,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5537, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,-3,1),189,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5136, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,2,3,0),110,1,1,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5000, new _PAIR(new _MaterialId(),new _LOCVAR(3),146,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),100,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5181, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-6,1),135,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5844, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,8,4,0),124,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5226, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,8,4,0),168,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5514, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,13,1),154,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5106, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),164,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5521, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,9,-8,1),103,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5982, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,3,1),111,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5956, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,-6,1),183,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5534, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,0,1),139,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5381, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,15,1),new _CLIMATE(0,2,4,15,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,15,1),new _CLIMATE(0,4,4,15,1),1,1,1,1),1,1,1,1),173,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,7,-5,1),123,1,1,114), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5579, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),179,1,1,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5333, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-4,1),177,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5875, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,5,1,1),165,1,1,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5424, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,15,1),198,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-2,1),108,1,1,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,9,0),176,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5686, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,-1,1),103,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5612, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,1,14,1),162,1,1,49), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5343, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,-2,1),145,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5022, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,7,1),174,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5451, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,16,-17,1),127,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5945, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,4,2,0),197,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5683, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,4,0,0),162,1,1,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5026, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,17,1),186,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5607, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-3,1),113,1,2,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,2,1),144,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5168, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,1,-1,1),106,1,2,109), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-1,1),168,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5871, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,4,7,1),100,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5592, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),170,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5749, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,5,1,1),101,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5969, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-3,1),172,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5312, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,0,0),121,1,2,128), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5054, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,-2,1),130,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,7,-2,1),111,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5116, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,16,1),new _CLIMATE(0,2,1,16,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,16,1),new _CLIMATE(0,4,1,16,1),1,1,1,1),1,1,1,1),178,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5150, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),150,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5485, new _PAIR(new _LOCVAR(0),new _MaterialId(),120,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5289, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,17,1),156,1,2,33), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5734, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-7,1),124,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5905, new _PAIR(new _LOCID(),new _DAY(),129,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5984, new _PAIR(new _MONTH(),new _MaterialId(),111,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5548, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,3,1),197,1,2,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5758, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,2,7,1),136,1,1,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5936, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,0,1),172,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5598, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,0,1),141,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5438, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),134,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5947, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,4,1),163,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5832, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,4,3,1),114,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5931, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,1,1),139,1,1,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5427, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,4,0,0),173,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5451, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,17,1),110,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5044, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,16,-17,1),188,1,1,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5828, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,7,-6,1),125,1,1,82), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5808, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-8,1),124,1,2,107), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5111, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,11,1),171,1,1,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5653, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,9,-10,1),112,1,1,127), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5901, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,4,1),159,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5360, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,12,1),new _CLIMATE(0,2,1,12,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,12,1),new _CLIMATE(0,4,1,12,1),1,1,1,1),1,1,1,1),102,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5351, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,10,0),154,1,1,117), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),138,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5412, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,4,-1,1),159,1,1,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5222, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,3,1),192,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5551, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,-1,1),175,1,2,45), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5708, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,11,-7,1),187,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5145, new _PAIR(new _LOCVAR(1),new _MaterialId(),122,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5220, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-2,1),179,1,1,121), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5780, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,4,15,1),167,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5890, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,-6,1),113,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5781, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-6,1),148,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5608, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,16,-1,1),168,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5697, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,2,1),171,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5302, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,11,-10,1),115,1,1,113), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5930, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-9,1),new _CLIMATE(0,2,8,-9,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-9,1),new _CLIMATE(0,4,8,-9,1),1,1,1,1),1,1,1,1),117,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5320, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-2,1),159,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,16,-1,1),new _CLIMATE(0,2,16,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,16,-1,1),new _CLIMATE(0,4,16,-1,1),1,1,1,1),1,1,1,1),184,1,2,34), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5401, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,8,0),174,1,2,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5625, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,2,1),new _CLIMATE(0,2,1,2,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,2,1),new _CLIMATE(0,4,1,2,1),1,1,1,1),1,1,1,1),161,1,2,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,1,1),187,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,0,1),114,1,1,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5374, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,0,1),134,1,2,116), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5090, new _PAIR(new _LOCVAR(2),new _MaterialId(),174,1,1,1), 0.01 + (alpha *= 0.99)));

    }

    void init_traindata(vector <string> &trainingData) {
      TRAINKEY.clear();
      YIELD.resize(trainingData.size());
      for(int i = 0; i < trainingData.size(); i++) TRAINKEY.push_back(parse_training(trainingData[i], YIELD[i]));
    }

    void train() {
      vector<float> YP(TRAINKEY.size());
      for(int i = 0; i < Predictor.size(); i++) {
        for(int j = 0; j < TRAINKEY.size(); j++) 
          if(i < 100 || abs(YIELD[j] - YP[j]) < 30)
                        if(i < 100 || Var.find(TRAINKEY[j].MaterialId) != Var.end())
            Predictor[i]->train(TRAINKEY[j], YIELD[j] - YP[j]);
        double MSE = 0.;
        double MSE2 = 0.;
        for(int j = 0; j < TRAINKEY.size(); j++) {
          YP[j] += Predictor[i]->predict(TRAINKEY[j]);
          double err = (YIELD[j] - YP[j])*(YIELD[j] - YP[j]);
          MSE += err;
          MSE2 += (err > 25*25) ? 25*25:err;
        }
     /*   if(i % 50 == 0) */cerr << "train " << i << ": " << " " << time() << "s " << sqrt(MSE/TRAINKEY.size()) << " " << sqrt(MSE2/TRAINKEY.size()) << endl;
      }
    }

        void init_var( vector<string> &varieties) {
            for(int i = 0; i < varieties.size(); i++) Var.insert(atoi(varieties[i].c_str()));
        }


    vector <double> predictYield(vector <string> &trainingData, vector <string> &droughtMonitor, vector <string> &droughtNOAA, vector <string> &locations, vector <string> &varieties, vector <string> &queries) {
      gettimeofday(&BEGIN, NULL);

            init_var(varieties);
      init_traindata(trainingData);
      init_NOAA(droughtNOAA);
      init_DMonitor(droughtMonitor);
      init_location(locations);
      init_predictor();
      train();

      vector<Key> K;
      for(int i = 0; i < queries.size(); i++) {
        vector<string> T = tokenize(queries[i]);
        while(T.size() < 5) T.push_back("");
        K.push_back(Key(T[0], T[1], T[2], T[3], T[4]));
      }


      vector<double> R(queries.size());
      for(int j = 0; j < Predictor.size(); j++) {
        for(int i = 0; i < queries.size(); i++) {        
          R[i] += Predictor[j]->predict(K[i]);
        }
//        cerr << "prediction: " << j << " " << sqrt(MSE/queries.size()) << " " << sqrt(MSE2/queries.size()) << endl;
      }
      cerr << "end: " <<  time() << "s" << endl;
      return R;
    }
};