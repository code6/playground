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


using namespace std;



  vector<float> YP;
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
  int ExperimentID;
  int LOCCD;
  int REPNO;
  int MaterialId;
  int HERB;
  int RM;
  int SRM;
  int PlantDate;
  Key(string ExperimentID, string LOCCD, string REPNO, string MaterialID, string HERB, string RM, string PlantDate) : index(-1) {
    this->ExperimentID = atoi(ExperimentID.c_str());
    this->LOCCD = atoi(LOCCD.c_str());
    this->REPNO = atoi(REPNO.c_str());
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
  return Key(T[0], T[1], T[2], T[3], T[4], T[7], T[8]);
}

struct Extractor {
  int* BUFFER;
  int pos;

  virtual int _extract(const Key &K) = 0;

  unsigned int extract(const Key &K) {
    if(BUFFER && K.index != -1) return BUFFER[K.index];
    else return _extract(K);
  };

  Extractor() : BUFFER(0), pos(-1) {}
  
  virtual string _print()  = 0;
  string print() {
    if(pos != -1) {
      stringstream S;
      S << "EXTR[" << pos << "]";
      return S.str();
    }
    else return _print();
  }

  virtual ~Extractor() {}
  void bufferize() {
    if(BUFFER) return;
    BUFFER = new int[TRAINKEY.size()];
    for(int i = 0; i < TRAINKEY.size(); i++) BUFFER[i] = _extract(TRAINKEY[i]);
  }
};


class Bucket {
  public:
  int M;

  int* N;
  float* S;
  float* P;
 float alpha;
  Extractor *E;

  void compute_pred() {
    for(int i = 0; i < M; i++) P[i] = alpha * S[i] / float(N[i]+1);
  }

  void clear() {
    delete[] N; N = 0;
    delete[] S; S = 0;
    delete[] P; P = 0;
  }
  
  Bucket(Extractor *E, int M, float alpha = 1.) : E(E), M(M), N(0), S(0), P(0), alpha(alpha) {}

  Bucket(const Bucket& B) {
    M = B.M;
    alpha = B.alpha;
    if(B.N) {N = new int[M]; memcpy(N, B.N, M*sizeof(int));} else N = 0;
    if(B.S) {S = new float[M]; memcpy(S, B.S, M*sizeof(float));} else S = 0;
    if(B.P) {P = new float[M]; memcpy(P, B.P, M*sizeof(float));} else P = 0;
  }


  inline unsigned int get_value(const Key& K) {
    return (E->extract(K) % M);
  }

  void init() {
    delete[] N; N = new int[M];   memset(N, 0, M*sizeof(int));
    delete[] S; S = new float[M]; memset(S, 0, M*sizeof(float));
    delete[] P; P = new float[M]; memset(P, 0, M*sizeof(float));
  }

  void train(const Key &K, float obs) {
    unsigned int k = get_value(K);
    N[k]++;
    S[k] += obs;
  }

  float predict(const Key &K) {
    return P[get_value(K)];
  }

  string print() {
    ostringstream S;
    S << "Bucket(new " << E->print() << "," << M << "," << alpha << ")";
    return S.str();
  }

  ~Bucket() {clear();}



};


struct _EMPTY : public Extractor {
  int _extract(const Key &K) {return 0;}
  string _print() {return "_EMPTY()";}
};

struct _REPNO : public Extractor {
  int _extract(const Key &K) {return K.REPNO;}
  string _print() {return "_REPNO()";}
};

struct _ExperimentID : public Extractor {
  int _extract(const Key &K) {return K.ExperimentID;}
  string _print() {return "_ExperimentID()";}
};

struct _ExpRep : public Extractor {
  int _extract(const Key &K) {return K.ExperimentID*8 + K.REPNO;}
  string _print() {return "_ExpRep()";}
};


struct _LOCID : public Extractor {
  int _extract(const Key &K) {return K.LOCCD;}
  string _print() {return "_LOCID()";}
};

struct _LOCID2 : public Extractor {
  int _extract(const Key &K) {return K.LOCCD/1000;}
  string _print() {return "_LOCID2()";}
};

struct _MaterialId : public Extractor {
  int _extract(const Key &K) {return K.MaterialId;}
  string _print() {return "_MaterialId()";}
};

struct _HERB : public Extractor {
  int _extract(const Key &K) {return K.HERB;}
  string _print() {return "_HERB()";}
};

struct _RM : public Extractor {
  int _extract(const Key &K) {return K.RM;}
  string _print() {return "_RM()";}
};

struct _SRM : public Extractor {
  int _extract(const Key &K) {return K.SRM;}
  string _print() {return "_SRM()";}
};

struct _YEAR : public Extractor {
  int _extract(const Key &K) {return K.PlantDate / 10000;}
  string _print() {return "_YEAR()";}
};

struct _DAY : public Extractor {
  int _extract(const Key &K) {return K.PlantDate % 100;}
  string _print() {return "_DAY()";}
};

struct _MONTH : public Extractor {
  int _extract(const Key &K) {return (K.PlantDate / 100) % 100;}
  string _print() {return "_MONTH()";}
};

struct _DAYOFYEAR : public Extractor {
  int _extract(const Key &K) {
    int dayOfYear = _DAY().extract(K);
    int month = _MONTH().extract(K);
    for(int i = 0; i < month - 1; i++) dayOfYear += MONTH[i];
    return dayOfYear;
  }
  string _print() {return "_DAYOFYEAR()";}
};

struct _CLIMATE : public Extractor {
  const int source;
  const int pos;
  const int length;
  const int offset;
  const int relative;
  const int div;
  const map<int, map< int, vector<int> > > &MAP;

  _CLIMATE(int source, int pos, int length, int offset, int relative = 1, int div = 1) 
    : Extractor(), source(source), pos(pos), length(length), offset(offset), relative(relative), div(div), MAP((source == 0)?LOC_NOAA:LOC_DMonitor) {}

  int _extract(const Key &K) {
    int year = _YEAR().extract(K);
    int loc = _LOCID().extract(K);
    int date;

    if(source == 0) 
      date = year*100 + _MONTH().extract(K);
    else 
      date = K.PlantDate;
   
    if(!relative) {
      if(source == 0) date = year*100 + 1;
      else date = year*10000 + 7;
    }

    if(MAP.find(loc) == MAP.end()) loc = 1000*(loc/1000);
    if(MAP.find(loc) == MAP.end()) return -9999;

    const map<int, vector<int> > &M = MAP.find(loc)->second;
    map<int, vector<int> >::const_iterator it = M.lower_bound(date);
/*    if(it == M.end()) {
      cerr << "bubu1 " << loc << " " << year << " " << source << "," << pos << "," << length << "," << offset << "," << relative << "," << div << " # " << (it->second).size() << endl;
      return -9999;
    }*/

    if(offset < 0) for(int k = 0; k < -offset; k++) --it;
    else if(offset > 0) for(int k = 0; k < offset && it != M.end(); k++) ++it;


    int nb = 0, sum = 0;
    for(; nb < length && it != M.end(); ++it) {
  /*    if((it->second).size() <= pos) {
        cerr << "bubu2 " << loc << " " << year << " "  << source << "," << pos << "," << length << "," << offset << "," << relative << "," << div << " # " << (it->second).size() <<  " " << nb << endl;
        break;

      }*/
      sum += (it->second)[pos];
      nb++;
    }
    if(nb > 0) return (sum / nb) / div;
    else return 0;
  }

  string _print() {
    ostringstream S;
    S << "_CLIMATE(" << source << "," << pos << "," << length << "," << offset << "," << relative << "," << div << ")";
    return S.str();
  }
};


struct _LOCVAR : public Extractor {
  int index;
  _LOCVAR(int index) : Extractor(), index(index) {} 

  int _extract(const Key &K) {
    int loc = _LOCID().extract(K);
    if(LOC.find(loc) == LOC.end()) loc = 1000*(loc/1000);
    map<int, vector<int> >::iterator it = LOC.find(loc);
    if(it == LOC.end()) return 0;
    else return (it->second)[index];
  }

  string _print() {
    ostringstream S;
    S << "_LOCVAR(" << index << ")";
    return S.str();
  }
};



struct _PAIR : public Extractor {
  Extractor* E1;
  Extractor* E2;
  int A1, A2, d1, d2;

  _PAIR(Extractor *E1, Extractor *E2, int A1, int A2, int d1 = 1, int d2 = 1) : Extractor(), E1(E1), E2(E2), A1(A1), A2(A2), d1(d1), d2(d2) {}

  int _extract(const Key &K) {
    int v1 = E1->extract(K);
    int v2 = E2->extract(K);
    return A1*(v1/d1) + A2*(v2/d2);
  }
  string _print() {
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


Extractor* EXTR[19] = {new _ExperimentID(),new _ExpRep(),new _LOCID(),new _MaterialId(),new _LOCVAR(0),new _LOCVAR(1),new _REPNO(),new _HERB(),new _RM(),new _SRM(),new _YEAR(),new _MONTH(),new _DAY(),new _DAYOFYEAR(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _LOCVAR(2),new _LOCVAR(3),new _LOCVAR(4)};
int NBB = 2103;
int NBA = 19;
Extractor* EXTR2[2103] = {
7,1,2,1),new _PAIR(EXTR[2],EXTR[3],88,7,3,1),new _PAIR(EXTR[2],EXTR[3],1808,4,2,1),new _PAIR(EXTR[3],EXTR[2],1798,5,1,4),new _PAIR(EXTR[3],EXTR[4],1853,7,1,5),new _PAIR(EXTR[3],EXTR[2],842,5,1,3),new _PAIR(EXTR[3],EXTR[2],1345,1,1,6),new _PAIR(EXTR[2],EXTR[3],820,1,3,1),new _PAIR(EXTR[3],EXTR[2],1867,3,1,6),new _PAIR(EXTR[3],new _CLIMATE(0,1,3,0,1,127),926,8,1,2),new _PAIR(EXTR[3],EXTR[2],739,7,1,8),new _PAIR(EXTR[3],EXTR[2],1192,8,1,2),new _PAIR(EXTR[3],EXTR[2],191,3,1,7),new _PAIR(EXTR[3],new _CLIMATE(1,2,2,0,1,92),144,4,1,4),new _PAIR(EXTR[3],EXTR[2],1237,2,1,2),new _PAIR(EXTR[3],EXTR[2],783,6,1,8),new _PAIR(EXTR[2],EXTR[3],1277,8,8,2),new _PAIR(EXTR[2],EXTR[3],22,7,3,1),new _PAIR(EXTR[5],EXTR[3],1008,5,6,1),new _PAIR(EXTR[3],EXTR[2],387,4,5,3),new _PAIR(EXTR[2],EXTR[3],1035,1,8,1),new _PAIR(EXTR[3],EXTR[12],1388,1,1,5),new _PAIR(EXTR[2],EXTR[3],1712,7,4,1),new _PAIR(EXTR[3],EXTR[2],934,5,2,2),new _PAIR(EXTR[2],EXTR[3],837,1,7,1),new _PAIR(EXTR[2],EXTR[3],1887,4,5,1),new _PAIR(EXTR[2],EXTR[3],484,4,6,1),new _PAIR(EXTR[2],EXTR[3],1133,4,6,1),new _PAIR(EXTR[3],EXTR[2],32,6,1,7),new _PAIR(EXTR[3],new _CLIMATE(0,4,6,-2,1,11),1187,4,1,2),new _PAIR(EXTR[2],EXTR[3],1574,3,5,2),new _PAIR(EXTR[3],EXTR[2],1791,8,1,1),new _PAIR(EXTR[2],EXTR[3],886,6,1,1),new _PAIR(EXTR[2],EXTR[3],739,2,2,1),new _PAIR(EXTR[3],new _CLIMATE(0,1,1,2,1,24),675,7,1,2),new _PAIR(EXTR[3],EXTR[2],1347,7,1,5),new _PAIR(EXTR[3],EXTR[2],991,4,1,1),new _PAIR(EXTR[3],EXTR[2],1393,5,1,6),new _PAIR(EXTR[3],new _CLIMATE(0,3,3,-2,1,8),582,7,1,8),new _PAIR(EXTR[3],EXTR[4],646,5,1,1),new _PAIR(EXTR[3],EXTR[4],135,4,1,2),new _PAIR(EXTR[5],EXTR[3],257,8,1,1),new _PAIR(EXTR[3],EXTR[5],1689,3,1,1),new _PAIR(EXTR[3],EXTR[13],85,8,1,2),new _PAIR(EXTR[2],EXTR[3],645,6,3,1),new _PAIR(EXTR[1],EXTR[2],327,4,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,5,3,-4,1,49),714,5,1,1),new _PAIR(EXTR[3],EXTR[2],1823,8,1,8),new _PAIR(EXTR[2],EXTR[3],1593,2,7,1),new _PAIR(EXTR[3],EXTR[2],776,5,5,1),new _PAIR(EXTR[3],new _CLIMATE(1,1,12,-7,1,163),190,5,3,5),new _PAIR(EXTR[3],EXTR[0],489,4,1,2),new _PAIR(EXTR[3],EXTR[2],51,6,1,2),new _PAIR(EXTR[5],EXTR[3],329,8,5,1),new _PAIR(EXTR[2],EXTR[3],257,8,6,1),new _PAIR(EXTR[5],EXTR[3],1735,2,2,1),new _PAIR(EXTR[3],EXTR[2],1947,6,1,4),new _PAIR(EXTR[3],new _CLIMATE(0,2,2,-2,1,9),1670,3,1,5),new _PAIR(EXTR[3],EXTR[2],219,3,1,6),new _PAIR(EXTR[13],EXTR[3],1153,3,1,5),new _PAIR(EXTR[3],new _CLIMATE(1,0,10,-11,1,44),893,2,3,4),new _PAIR(EXTR[2],EXTR[3],1642,7,3,1),new _PAIR(EXTR[2],EXTR[3],1536,2,8,4),new _PAIR(EXTR[2],EXTR[3],245,7,2,1),new _PAIR(EXTR[3],EXTR[2],388,1,6,1),new _PAIR(EXTR[3],EXTR[2],1643,2,2,1),new _PAIR(EXTR[3],EXTR[13],741,4,3,1),new _PAIR(EXTR[3],EXTR[2],822,4,1,8),new _PAIR(EXTR[3],EXTR[0],10,1,1,1),new _PAIR(EXTR[2],EXTR[3],1714,3,1,1),new _PAIR(EXTR[4],EXTR[3],1804,7,1,1),new _PAIR(EXTR[2],EXTR[3],1651,2,1,1),new _PAIR(EXTR[2],EXTR[3],760,1,6,1),new _PAIR(EXTR[3],EXTR[2],209,4,1,6),new _PAIR(EXTR[2],EXTR[3],1861,8,7,1),new _PAIR(EXTR[13],EXTR[3],1635,5,2,1),new _PAIR(EXTR[3],EXTR[12],1614,5,1,2),new _PAIR(EXTR[2],EXTR[3],233,2,1,2),new _PAIR(EXTR[2],EXTR[3],1817,6,8,2),new _PAIR(EXTR[3],new _CLIMATE(0,1,1,-2,1,10),26,1,1,1),new _PAIR(EXTR[1],EXTR[2],1802,8,1,1),new _PAIR(EXTR[3],EXTR[2],320,3,1,2),new _PAIR(EXTR[3],EXTR[5],988,2,1,1),new _PAIR(EXTR[2],EXTR[3],1491,2,8,3),new _PAIR(EXTR[2],EXTR[3],1072,4,3,3),new _PAIR(EXTR[3],EXTR[2],1441,7,1,1),new _PAIR(EXTR[3],EXTR[2],804,6,6,7),new _PAIR(EXTR[2],EXTR[3],1899,2,1,1),new _PAIR(EXTR[2],EXTR[3],319,4,3,1),new _PAIR(EXTR[3],EXTR[2],1299,1,4,1),new _PAIR(EXTR[2],EXTR[3],1586,6,4,1),new _PAIR(EXTR[3],EXTR[1],365,1,1,3),new _PAIR(EXTR[3],EXTR[5],1405,4,1,8),new _PAIR(EXTR[14],EXTR[3],1208,7,1,1),new _PAIR(EXTR[3],EXTR[2],1172,3,1,5),new _PAIR(EXTR[2],EXTR[3],1363,7,6,1),new _PAIR(EXTR[3],EXTR[2],1378,3,4,1),new _PAIR(EXTR[3],EXTR[2],283,8,1,5),new _PAIR(EXTR[3],new _CLIMATE(1,1,12,-9,1,151),633,7,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,3,3,-2,1,10),365,3,8,4),new _PAIR(EXTR[1],EXTR[3],927,4,8,1),new _PAIR(EXTR[3],EXTR[4],927,4,1,3),new _PAIR(EXTR[3],new _CLIMATE(0,1,4,-3,1,120),1692,2,3,4),new _PAIR(EXTR[1],EXTR[3],969,3,7,1),new _PAIR(EXTR[3],EXTR[2],944,2,1,7),new _PAIR(EXTR[3],EXTR[4],280,3,1,2),new _PAIR(EXTR[2],EXTR[3],773,3,4,1),new _PAIR(EXTR[3],new _CLIMATE(0,2,4,-2,1,26),557,7,1,2),new _PAIR(EXTR[3],new _CLIMATE(0,5,3,1,1,6),486,6,1,3),new _PAIR(EXTR[2],EXTR[3],750,4,8,1),new _PAIR(EXTR[2],EXTR[3],202,2,6,2),new _PAIR(EXTR[2],EXTR[3],1382,2,7,1),new _PAIR(EXTR[2],EXTR[3],1501,2,7,2),new _PAIR(EXTR[2],EXTR[3],53,2,2,1),new _PAIR(EXTR[3],EXTR[13],1680,2,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,1,6,-3,1,39),1497,5,1,2),new _PAIR(EXTR[3],new _CLIMATE(0,0,5,-2,1,49),1719,2,1,7),new _PAIR(EXTR[2],EXTR[3],886,4,8,1),new _PAIR(EXTR[2],EXTR[1],1091,3,1,1),new _PAIR(EXTR[2],EXTR[3],70,5,8,1),new _PAIR(EXTR[2],EXTR[3],1466,7,2,1),new _PAIR(EXTR[2],EXTR[3],573,8,4,1),new _PAIR(EXTR[3],EXTR[2],753,6,1,1),new _PAIR(EXTR[3],EXTR[2],160,5,1,1),new _PAIR(EXTR[2],EXTR[1],1880,2,2,1),new _PAIR(EXTR[3],new _CLIMATE(0,4,3,-2,1,42),229,1,1,1),new _PAIR(EXTR[13],EXTR[3],1921,4,1,1),new _PAIR(EXTR[2],EXTR[3],372,7,6,1),new _PAIR(EXTR[2],EXTR[3],1761,2,1,1),new _PAIR(EXTR[3],EXTR[2],387,3,1,1),new _PAIR(EXTR[3],EXTR[2],1908,3,7,1),new _PAIR(EXTR[2],EXTR[3],307,4,1,1),new _PAIR(EXTR[3],new _CLIMATE(1,0,3,-4,1,40),1494,4,1,2),new _PAIR(EXTR[3],EXTR[12],214,2,1,1),new _PAIR(EXTR[3],EXTR[5],1802,3,1,2),new _PAIR(EXTR[2],EXTR[3],1321,7,7,1),new _PAIR(EXTR[3],EXTR[2],47,3,1,1),new _PAIR(EXTR[2],EXTR[3],1303,2,4,1),new _PAIR(EXTR[3],EXTR[2],52,5,2,1),new _PAIR(EXTR[3],EXTR[2],1623,8,1,2),new _PAIR(EXTR[3],EXTR[5],1930,5,1,3),new _PAIR(EXTR[3],EXTR[2],139,8,1,1),new _PAIR(EXTR[2],EXTR[3],1393,4,7,1),new _PAIR(EXTR[5],EXTR[3],175,1,2,1),new _PAIR(EXTR[2],EXTR[3],1594,6,2,1),new _PAIR(EXTR[4],EXTR[3],1069,6,3,1),new _PAIR(EXTR[3],EXTR[1],1059,7,1,1),new _PAIR(EXTR[3],EXTR[5],417,3,1,8),new _PAIR(EXTR[3],new _CLIMATE(1,1,6,-7,1,18),1557,7,7,2),new _PAIR(EXTR[3],new _CLIMATE(0,11,4,-2,1,20),1778,3,2,2),new _PAIR(EXTR[5],EXTR[3],1575,5,7,1),new _PAIR(EXTR[3],EXTR[0],1957,5,1,2),new _PAIR(EXTR[2],EXTR[3],905,4,3,1),new _PAIR(EXTR[3],EXTR[13],1469,1,5,2),new _PAIR(EXTR[2],EXTR[3],1813,8,1,1),new _PAIR(EXTR[2],EXTR[3],1383,8,1,5),new _PAIR(EXTR[2],EXTR[3],911,2,2,1),new _PAIR(EXTR[3],EXTR[2],1093,7,1,1),new _PAIR(EXTR[2],EXTR[3],1342,3,2,1),new _PAIR(EXTR[3],EXTR[2],1808,2,6,2),new _PAIR(EXTR[5],EXTR[3],597,7,6,1),new _PAIR(EXTR[3],EXTR[5],403,5,1,7),new _PAIR(EXTR[3],EXTR[2],1442,1,1,2),new _PAIR(EXTR[2],EXTR[3],1165,7,8,1),new _PAIR(EXTR[3],EXTR[2],353,5,1,4),new _PAIR(EXTR[3],EXTR[1],838,1,1,1),new _PAIR(EXTR[3],EXTR[4],1173,3,1,5),new _PAIR(EXTR[5],EXTR[3],885,8,1,1),new _PAIR(EXTR[1],EXTR[2],832,6,1,1),new _PAIR(EXTR[3],EXTR[13],1275,7,1,1),new _PAIR(EXTR[3],EXTR[13],884,1,1,1),new _PAIR(EXTR[2],EXTR[3],1863,8,3,1),new _PAIR(EXTR[2],EXTR[3],428,7,1,1),new _PAIR(EXTR[3],EXTR[2],467,7,1,4),new _PAIR(EXTR[3],EXTR[5],195,7,1,7),new _PAIR(EXTR[5],EXTR[3],337,6,1,1),new _PAIR(EXTR[2],EXTR[3],714,1,3,1),new _PAIR(EXTR[3],EXTR[2],1826,1,1,4),new _PAIR(EXTR[2],EXTR[3],750,8,5,1),new _PAIR(EXTR[3],EXTR[2],841,1,1,1),new _PAIR(EXTR[3],EXTR[2],1701,4,1,1),new _PAIR(EXTR[4],EXTR[3],507,8,2,1),new _PAIR(EXTR[3],EXTR[2],1248,8,3,7),new _PAIR(EXTR[2],EXTR[3],888,4,1,5),new _PAIR(EXTR[3],EXTR[2],1078,7,2,2),new _PAIR(EXTR[3],EXTR[2],1490,4,1,6),new _PAIR(EXTR[3],EXTR[2],1470,1,1,2),new _PAIR(EXTR[3],EXTR[2],1649,5,1,6),new _PAIR(EXTR[2],EXTR[3],97,6,8,1),new _PAIR(EXTR[2],EXTR[3],985,1,1,1),new _PAIR(EXTR[3],EXTR[5],577,4,1,6),new _PAIR(EXTR[3],EXTR[2],66,3,1,6),new _PAIR(EXTR[3],EXTR[4],1379,6,1,4),new _PAIR(EXTR[2],EXTR[3],794,1,2,1),new _PAIR(EXTR[3],EXTR[2],1709,7,1,2),new _PAIR(EXTR[2],EXTR[3],1153,1,1,7),new _PAIR(EXTR[2],EXTR[3],72,8,3,5),new _PAIR(EXTR[2],EXTR[3],112,7,1,1),new _PAIR(EXTR[2],EXTR[3],836,2,4,1),new _PAIR(EXTR[3],EXTR[2],155,5,2,4),new _PAIR(EXTR[2],EXTR[3],1729,6,3,1),new _PAIR(EXTR[1],EXTR[3],1343,4,7,1),new _PAIR(EXTR[2],EXTR[1],1508,7,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,10,3,-2,1,11),1591,7,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,1,3,-3,1,18),1879,7,1,7),new _PAIR(EXTR[3],new _CLIMATE(0,1,5,-4,1,68),1547,2,2,1),new _PAIR(EXTR[3],EXTR[12],1684,5,1,2),new _PAIR(EXTR[1],EXTR[3],64,3,1,1),new _PAIR(EXTR[3],EXTR[2],1944,7,1,1),new _PAIR(EXTR[3],EXTR[2],1564,7,3,1),new _PAIR(EXTR[3],EXTR[1],153,2,1,1),new _PAIR(EXTR[3],EXTR[2],129,8,1,2),new _PAIR(EXTR[3],EXTR[2],1784,3,1,7),new _PAIR(EXTR[3],EXTR[2],601,6,1,5),new _PAIR(EXTR[2],EXTR[3],1164,1,3,1),new _PAIR(EXTR[3],EXTR[2],2003,2,1,5),new _PAIR(EXTR[2],EXTR[3],1101,6,4,1),new _PAIR(EXTR[3],EXTR[2],853,4,1,2),new _PAIR(EXTR[2],EXTR[3],313,2,3,1),new _PAIR(EXTR[3],EXTR[2],1073,7,1,1),new _PAIR(EXTR[0],EXTR[3],557,1,1,1),new _PAIR(EXTR[1],EXTR[2],654,5,1,1),new _PAIR(EXTR[3],EXTR[2],176,6,1,2),new _PAIR(EXTR[3],EXTR[2],1680,1,1,8),new _PAIR(EXTR[2],EXTR[3],834,7,2,1),new _PAIR(EXTR[3],EXTR[2],479,4,1,1),new _PAIR(EXTR[5],EXTR[3],177,7,1,1),new _PAIR(EXTR[0],EXTR[3],1384,7,1,1),new _PAIR(EXTR[3],EXTR[2],1107,7,1,4),new _PAIR(EXTR[3],new _CLIMATE(0,1,4,-2,1,80),1733,3,1,1),new _PAIR(EXTR[3],EXTR[5],911,1,1,1),new _PAIR(EXTR[3],EXTR[1],1334,7,1,2),new _PAIR(EXTR[3],EXTR[2],343,8,1,2),new _PAIR(EXTR[2],EXTR[3],294,6,5,1),new _PAIR(EXTR[3],EXTR[2],969,4,1,4),new _PAIR(EXTR[1],EXTR[3],340,8,1,1),new _PAIR(EXTR[2],EXTR[3],307,7,6,1),new _PAIR(EXTR[2],EXTR[3],1727,1,2,1),new _PAIR(EXTR[3],EXTR[2],1647,3,2,1),new _PAIR(EXTR[3],new _CLIMATE(0,7,1,-2,1,19),1119,7,1,2),new _PAIR(EXTR[2],EXTR[3],153,6,1,2),new _PAIR(EXTR[2],EXTR[3],13,6,2,1),new _PAIR(EXTR[3],new _CLIMATE(1,3,6,0,1,100),1152,7,1,6),new _PAIR(EXTR[3],EXTR[5],540,5,1,7),new _PAIR(EXTR[2],EXTR[3],56,3,1,2),new _PAIR(EXTR[2],EXTR[3],1219,4,5,1),new _PAIR(EXTR[3],EXTR[2],1719,1,1,7),new _PAIR(EXTR[1],EXTR[3],626,3,1,1),new _PAIR(EXTR[3],EXTR[2],1904,8,1,5),new _PAIR(EXTR[3],EXTR[0],626,1,1,7),new _PAIR(EXTR[2],EXTR[3],1105,7,3,1),new _PAIR(EXTR[3],EXTR[2],970,1,1,4),new _PAIR(EXTR[3],EXTR[2],1417,3,1,5),new _PAIR(EXTR[2],EXTR[3],873,7,1,1),new _PAIR(EXTR[1],EXTR[2],1527,8,1,1),new _PAIR(EXTR[2],EXTR[3],754,3,2,2),new _PAIR(EXTR[5],EXTR[3],1660,2,1,1),new _PAIR(EXTR[1],EXTR[2],1238,2,1,1),new _PAIR(EXTR[2],EXTR[3],1785,5,1,1),new _PAIR(EXTR[2],EXTR[3],1895,1,1,1),new _PAIR(EXTR[3],EXTR[2],381,4,1,6),new _PAIR(EXTR[3],new _CLIMATE(1,0,12,-7,1,191),197,1,1,4),new _PAIR(EXTR[3],EXTR[2],541,8,1,8),new _PAIR(EXTR[3],EXTR[2],358,6,1,7),new _PAIR(EXTR[3],EXTR[2],1513,8,2,1),new _PAIR(EXTR[3],EXTR[4],387,2,1,1),new _PAIR(EXTR[1],EXTR[3],1791,8,1,1),new _PAIR(EXTR[3],EXTR[13],133,3,1,1),new _PAIR(EXTR[3],EXTR[1],1055,7,1,2),new _PAIR(EXTR[3],EXTR[4],483,5,1,2),new _PAIR(EXTR[5],EXTR[3],367,6,1,1),new _PAIR(EXTR[2],EXTR[3],1369,8,5,1),new _PAIR(EXTR[3],EXTR[13],840,1,1,1),new _PAIR(EXTR[4],EXTR[3],1391,8,2,1),new _PAIR(EXTR[2],EXTR[3],1439,3,2,2),new _PAIR(EXTR[3],EXTR[2],1571,6,1,2),new _PAIR(EXTR[2],EXTR[3],1051,3,1,1),new _PAIR(EXTR[1],EXTR[3],135,2,5,1),new _PAIR(EXTR[4],EXTR[3],599,8,3,1),new _PAIR(EXTR[2],EXTR[3],1163,5,1,1),new _PAIR(EXTR[3],EXTR[1],1371,6,1,1),new _PAIR(EXTR[2],EXTR[3],50,1,1,1),new _PAIR(EXTR[2],EXTR[3],904,3,1,3),new _PAIR(EXTR[3],EXTR[2],1915,4,1,3),new _PAIR(EXTR[3],EXTR[2],1791,8,1,6),new _PAIR(EXTR[2],EXTR[3],986,8,1,2),new _PAIR(EXTR[3],EXTR[2],1976,3,1,3),new _PAIR(EXTR[3],EXTR[2],1777,3,1,2),new _PAIR(EXTR[2],EXTR[3],1717,2,3,1),new _PAIR(EXTR[2],EXTR[3],189,2,1,1),new _PAIR(EXTR[1],EXTR[3],1399,5,1,1),new _PAIR(EXTR[2],EXTR[3],264,1,5,1),new _PAIR(EXTR[3],EXTR[1],1743,6,1,1),new _PAIR(EXTR[3],EXTR[5],1173,7,1,4),new _PAIR(EXTR[3],EXTR[2],989,1,1,1),new _PAIR(EXTR[3],EXTR[2],225,5,3,1),new _PAIR(EXTR[2],EXTR[3],816,1,3,1),new _PAIR(EXTR[1],EXTR[2],331,7,1,1),new _PAIR(EXTR[3],EXTR[2],1435,2,1,3),new _PAIR(EXTR[3],EXTR[1],152,3,1,1),new _PAIR(EXTR[3],EXTR[2],744,8,3,2),new _PAIR(EXTR[2],EXTR[3],142,2,2,1),new _PAIR(EXTR[3],EXTR[2],437,5,1,5),new _PAIR(EXTR[2],EXTR[3],1465,4,6,1),new _PAIR(EXTR[2],EXTR[3],141,6,1,1),new _PAIR(EXTR[3],EXTR[1],1054,1,1,2),new _PAIR(EXTR[2],EXTR[3],1657,3,3,1),new _PAIR(EXTR[3],EXTR[2],605,3,1,2),new _PAIR(EXTR[3],EXTR[2],167,6,6,3),new _PAIR(EXTR[2],EXTR[1],427,5,1,1),new _PAIR(EXTR[3],EXTR[1],581,2,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,5,6,-5,1,60),263,4,1,1),new _PAIR(EXTR[3],EXTR[1],797,4,2,2),new _PAIR(EXTR[1],EXTR[3],1983,4,1,1),new _PAIR(EXTR[2],EXTR[3],1616,1,5,1),new _PAIR(EXTR[3],EXTR[2],1596,8,1,4),new _PAIR(EXTR[3],EXTR[1],948,3,1,1),new _PAIR(EXTR[3],EXTR[2],1208,7,2,4),new _PAIR(EXTR[3],EXTR[2],796,2,1,3),new _PAIR(EXTR[3],EXTR[5],1280,3,1,1),new _PAIR(EXTR[2],EXTR[3],1245,4,1,1),new _PAIR(EXTR[3],EXTR[2],1508,3,1,4),new _PAIR(EXTR[3],EXTR[2],2007,6,1,1),new _PAIR(EXTR[3],EXTR[2],986,7,1,6),new _PAIR(EXTR[3],EXTR[2],202,3,1,4),new _PAIR(EXTR[2],EXTR[3],1027,4,1,1),new _PAIR(EXTR[3],EXTR[2],1043,2,1,5),new _PAIR(EXTR[3],EXTR[2],1580,7,1,1),new _PAIR(EXTR[5],EXTR[3],1896,7,1,2),new _PAIR(EXTR[2],EXTR[3],1631,8,7,1),new _PAIR(EXTR[2],EXTR[3],1068,8,6,1),new _PAIR(EXTR[2],EXTR[3],1753,7,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,1,5,-3,1,44),763,4,1,4),new _PAIR(EXTR[2],EXTR[3],323,5,4,1),new _PAIR(EXTR[3],new _CLIMATE(1,0,11,-9,1,126),273,2,1,2),new _PAIR(EXTR[3],EXTR[2],430,2,1,3),new _PAIR(EXTR[3],EXTR[2],1332,5,1,4),new _PAIR(EXTR[2],EXTR[3],861,4,7,1),new _PAIR(EXTR[3],EXTR[2],1668,4,1,7),new _PAIR(EXTR[3],EXTR[2],300,8,1,1),new _PAIR(EXTR[3],EXTR[2],1220,3,1,3),new _PAIR(EXTR[3],EXTR[2],1459,8,1,8),new _PAIR(EXTR[5],EXTR[3],1343,6,1,1),new _PAIR(EXTR[3],EXTR[2],1657,2,1,4),new _PAIR(EXTR[3],EXTR[2],1197,7,1,5),new _PAIR(EXTR[2],EXTR[3],528,1,1,1),new _PAIR(EXTR[2],EXTR[3],1159,4,7,1),new _PAIR(EXTR[2],EXTR[3],933,4,7,1),new _PAIR(EXTR[5],EXTR[3],1193,1,7,1),new _PAIR(EXTR[3],EXTR[1],1422,6,1,2),new _PAIR(EXTR[1],EXTR[3],1604,8,1,1),new _PAIR(EXTR[3],EXTR[2],1071,7,1,2),new _PAIR(EXTR[2],EXTR[3],1949,2,1,1),new _PAIR(EXTR[3],EXTR[2],578,2,1,1),new _PAIR(EXTR[3],EXTR[2],1761,6,1,2),new _PAIR(EXTR[2],EXTR[3],1576,2,2,1),new _PAIR(EXTR[3],EXTR[1],1770,5,1,2),new _PAIR(EXTR[2],EXTR[3],359,8,8,1),new _PAIR(EXTR[2],EXTR[3],191,8,4,1),new _PAIR(EXTR[3],EXTR[2],211,6,1,2),new _PAIR(EXTR[3],EXTR[1],1486,1,1,2),new _PAIR(EXTR[1],EXTR[3],131,8,1,2),new _PAIR(EXTR[2],EXTR[3],97,8,5,1),new _PAIR(EXTR[3],EXTR[2],676,7,1,1),new _PAIR(EXTR[3],EXTR[2],1260,7,1,7),new _PAIR(EXTR[1],EXTR[3],862,5,1,1),new _PAIR(EXTR[3],EXTR[2],1378,3,1,3),new _PAIR(EXTR[1],EXTR[3],834,5,2,1),new _PAIR(EXTR[1],EXTR[2],989,1,1,1),new _PAIR(EXTR[3],new _CLIMATE(0,1,6,-4,1,47),373,3,1,4),new _PAIR(EXTR[3],EXTR[4],484,3,1,2),new _PAIR(EXTR[3],new _CLIMATE(0,1,6,-4,1,199),1375,6,3,1),new _PAIR(EXTR[2],EXTR[3],1456,5,7,1),new _PAIR(EXTR[2],EXTR[3],879,7,8,1),new _PAIR(EXTR[3],EXTR[1],266,1,1,2),new _PAIR(EXTR[3],new _CLIMATE(1,2,8,1,1,82),644,1,1,4),new _PAIR(EXTR[3],new _CLIMATE(1,0,11,-12,1,108),1026,8,1,4),new _PAIR(EXTR[3],EXTR[1],1791,4,1,1),new _PAIR(EXTR[1],EXTR[2],1997,3,1,1),new _PAIR(EXTR[3],EXTR[2],323,3,1,2),new _PAIR(EXTR[2],EXTR[3],1254,3,7,1),new _PAIR(EXTR[2],EXTR[3],993,4,7,1),new _PAIR(EXTR[2],EXTR[3],208,2,1,1),new _PAIR(EXTR[3],EXTR[5],1878,1,1,8),new _PAIR(EXTR[3],EXTR[1],1735,5,1,1),new _PAIR(EXTR[3],EXTR[2],931,5,1,1),new _PAIR(EXTR[3],EXTR[1],1531,8,1,1),new _PAIR(EXTR[3],EXTR[2],847,7,1,8),new _PAIR(EXTR[3],EXTR[1],660,7,3,1),new _PAIR(EXTR[3],EXTR[2],1242,3,1,1),new _PAIR(EXTR[2],EXTR[3],1350,1,7,1),new _PAIR(EXTR[1],EXTR[3],561,7,1,1),new _PAIR(EXTR[3],EXTR[2],895,8,1,3),new _PAIR(EXTR[2],EXTR[3],1124,8,1,1),new _PAIR(EXTR[3],EXTR[2],397,3,1,6),new _PAIR(EXTR[3],new _CLIMATE(0,1,5,-5,1,133),1230,3,1,1),new _PAIR(EXTR[3],EXTR[2],471,1,2,4),new _PAIR(EXTR[3],EXTR[2],322,1,7,1),new _PAIR(EXTR[3],EXTR[2],702,3,1,1),new _PAIR(EXTR[3],EXTR[2],491,1,3,1),new _PAIR(EXTR[3],new _CLIMATE(0,3,4,-3,1,9),483,3,5,3),new _PAIR(EXTR[2],EXTR[3],1511,2,1,8),new _PAIR(EXTR[3],EXTR[1],1110,2,1,2),new _PAIR(EXTR[3],EXTR[2],990,4,1,4),new _PAIR(EXTR[2],EXTR[3],408,1,3,1),new _PAIR(EXTR[3],EXTR[2],1469,4,1,3),new _PAIR(EXTR[2],EXTR[3],355,1,1,1),new _PAIR(EXTR[3],EXTR[2],55,5,1,8),new _PAIR(EXTR[5],EXTR[3],287,8,1,1),new _PAIR(EXTR[3],EXTR[2],939,3,1,3),new _PAIR(EXTR[3],EXTR[2],1961,8,1,5),new _PAIR(EXTR[2],EXTR[3],1206,6,6,1),new _PAIR(EXTR[3],new _CLIMATE(1,1,8,-9,1,56),223,8,1,4),new _PAIR(EXTR[2],EXTR[3],1902,1,4,1),new _PAIR(EXTR[2],EXTR[3],1753,1,2,1),new _PAIR(EXTR[2],EXTR[3],1096,5,2,1),new _PAIR(EXTR[2],EXTR[3],1517,7,2,1),new _PAIR(EXTR[3],EXTR[2],949,2,1,1),new _PAIR(EXTR[2],EXTR[3],676,5,5,1),new _PAIR(EXTR[3],new _CLIMATE(1,0,9,-8,1,30),734,2,1,2),new _PAIR(EXTR[3],EXTR[13],774,2,2,1)};
int BM[2103] = {
41,56,61,63,69,70,83,79,77,94,97,106,109,109,89,120,131,139,141,147,152,150,144,147,168,158,151,182,167,189,199,203,209,193,210,217,233,236,238,225,247,257,262,221,263,266,274,278,276,281,302,309,284,317,323,327,323,335,334,337,345,314,354,366,374,351,375,379,375,366,370,403,414,412,388,388,407,421,423,429,444,455,464,459,445,477,474,487,485,454,483,506,473,517,520,512,530,492,541,547,535,535,556,564,555,568,551,585,582,597,556,589,604,601,591,610,604,619,597,645,626,653,639,656,648,678,682,689,691,676,701,685,704,713,719,729,696,717,719,745,751,718,742,763,765,755,763,778,770,767,797,806,797,799,801,818,820,799,832,808,814,835,826,867,867,879,867,867,846,882,875,889,891,894,911,880,924,931,925,923,952,935,938,952,948,959,943,982,988,988,989,1004,999,1011,1024,1025,1003,1019,1043,1036,1046,1059,1056,1066,1050,1076,1076,1082,1090,1094,1100,1107,1104,1117,1116,1083,1118,1125,1140,1143,1139,1115,1122,1159,1153,1178,1169,1179,1187,1178,1201,1190,1213,1212,1218,1227,1202,1215,1238,1244,1211,1257,1253,1268,1254,1261,1259,1289,1285,1283,1297,1308,1300,1298,1305,1327,1295,1338,1312,1347,1327,1310,1316,1358,1356,1330,1379,1379,1386,1394,1375,1388,1409,1410,1415,1408,1424,1439,1436,1449,1406,1419,1439,1467,1463,1441,1454,1473,1473,1493,1495,1503,1466,1505,1493,1529,1507,1529,1522,1525,1554,1541,1533,1531,1552,1540,1579,1579,1561,1589,1601,1585,1602,1609,1610,1598,1622,1608,1628,1602,1649,1638,1660,1669,1656,1675,1675,1683,1663,1674,1695,1683,1709,1687,1689,1701,1703,1715,1719,1728,1742,1758,1753,1738,1738,1775,1783,1780,1751,1799,1796,1794,1813,1787,1807,1823,1830,1817,1833,1845,1853,1850,1862,1866,1826,1835,1867,1857,1852,1872,1885,1881,1911,1899,1914,1921,1909,1905,1903,1941,1937,1933,1960,1954,1954,1974,1970,1962,1989,1999,1996,1989,1971,2015,2001,1996,2031,1998,2029,2023,2053,2023,2027,2062,2069,2063,2083,2047,2093,2061,2087,2076,2088,2093,2079,2119,2108,2137,2129,2147,2149,2119,2161,2128,2156,2159,2169,2168,2154,2161,2179,2191,2209,2209,2223,2219,2200,2239,2206,2217,2245,2223,2235,2262,2238,2258,2272,2279,2247,2260,2282,2308,2309,2307,2321,2309,2293,2312,2307,2341,2312,2356,2341,2323,2374,2373,2378,2363,2360,2379,2401,2381,2379,2401,2393,2398,2406,2429,2424,2444,2443,2415,2446,2464,2470,2435,2470,2481,2464,2488,2467,2491,2477,2490,2512,2503,2532,2498,2521,2503,2545,2558,2543,2523,2565,2565,2563,2578,2594,2588,2598,2588,2569,2612,2594,2603,2593,2626,2631,2649,2637,2619,2651,2657,2651,2657,2684,2663,2678,2686,2699,2692,2702,2707,2708,2726,2717,2698,2743,2748,2743,2754,2739,2751,2769,2766,2777,2786,2794,2782,2769,2771,2797,2800,2802,2784,2831,2825,2834,2829,2854,2827,2830,2848,2851,2872,2884,2888,2864,2856,2855,2907,2904,2912,2881,2925,2924,2896,2936,2947,2943,2943,2930,2959,2974,2945,2950,2968,2953,2987,2967,2991,2977,3005,3013,3005,3009,3000,2997,3036,3011,3055,3017,3067,3074,3066,3053,3085,3079,3075,3089,3103,3072,3119,3095,3119,3114,3136,3138,3147,3127,3151,3123,3127,3144,3151,3159,3159,3177,3191,3166,3207,3201,3210,3191,3221,3204,3210,3228,3205,3236,3217,3256,3245,3232,3242,3269,3268,3261,3266,3281,3293,3288,3317,3292,3309,3326,3319,3334,3326,3340,3349,3355,3366,3359,3334,3381,3361,3375,3383,3378,3402,3408,3390,3409,3428,3388,3429,3444,3411,3438,3435,3448,3452,3451,3461,3456,3462,3474,3482,3483,3475,3500,3494,3476,3524,3533,3529,3516,3540,3543,3559,3553,3521,3533,3541,3581,3571,3577,3595,3563,3583,3574,3589,3618,3587,3628,3634,3641,3622,3629,3643,3633,3643,3666,3661,3654,3641,3685,3674,3701,3701,3703,3686,3702,3710,3728,3718,3711,3735,3711,3751,3760,3761,3750,3773,3778,3780,3782,3756,3759,3783,3766,3797,3789,3828,3811,3832,3809,3833,3816,3834,3837,3848,3872,3835,3840,3878,3894,3857,3885,3909,3894,3916,3889,3899,3924,3911,3927,3905,3950,3938,3961,3935,3967,3972,3977,3984,3972,3997,4003,3975,4006,3988,3980,4018,4023,4018,4042,4005,4037,4019,4033,4069,4073,4034,4082,4052,4083,4059,4101,4089,4107,4118,4077,4096,4131,4117,4136,4119,4153,4155,4121,4126,4152,4158,4163,4153,4150,4174,4188,4198,4213,4172,4189,4187,4200,4207,4218,4231,4241,4236,4255,4261,4241,4273,4262,4282,4289,4264,4299,4308,4265,4297,4290,4307,4329,4309,4337,4336,4344,4357,4363,4355,4361,4358,4353,4371,4365,4379,4393,4402,4409,4376,4420,4428,4409,4393,4412,4443,4433,4439,4423,4454,4470,4479,4462,4476,4478,4486,4499,4496,4496,4475,4499,4495,4520,4538,4532,4509,4550,4559,4532,4536,4551,4538,4571,4589,4590,4593,4572,4606,4610,4617,4617,4603,4633,4624,4610,4632,4617,4626,4657,4658,4661,4661,4679,4672,4659,4679,4703,4694,4681,4717,4718,4722,4711,4730,4732,4749,4728,4759,4719,4727,4760,4778,4761,4780,4790,4771,4800,4785,4785,4778,4792,4819,4824,4806,4803,4821,4834,4859,4843,4861,4842,4878,4842,4889,4894,4895,4869,4908,4913,4895,4910,4884,4934,4901,4898,4942,4946,4955,4921,4955,4969,4950,4977,4989,4987,4971,4995,5005,4990,5015,4987,5027,5017,5028,5030,5045,5016,5046,5040,5048,5069,5047,5042,5073,5075,5052,5101,5108,5096,5115,5085,5083,5109,5123,5107,5145,5145,5127,5163,5127,5127,5176,5164,5186,5174,5180,5201,5178,5173,5214,5214,5210,5229,5222,5235,5243,5221,5245,5229,5268,5274,5243,5281,5277,5249,5252,5255,5296,5298,5315,5304,5328,5332,5332,5330,5324,5334,5345,5336,5333,5363,5332,5338,5377,5352,5381,5382,5401,5377,5407,5400,5396,5405,5411,5426,5415,5440,5417,5437,5436,5459,5450,5449,5476,5458,5489,5488,5502,5498,5477,5510,5506,5515,5496,5509,5500,5527,5548,5521,5526,5529,5531,5541,5574,5588,5581,5565,5572,5571,5584,5577,5626,5620,5637,5607,5645,5653,5627,5615,5669,5662,5644,5678,5689,5665,5666,5700,5694,5707,5695,5677,5708,5719,5730,5714,5721,5742,5737,5748,5756,5741,5765,5750,5740,5751,5779,5782,5808,5814,5773,5810,5782,5817,5802,5831,5843,5816,5858,5846,5822,5874,5860,5842,5879,5847,5895,5860,5903,5879,5909,5917,5906,5921,5926,5911,5949,5940,5941,5940,5950,5940,5975,5961,5976,5983,5991,6003,5968,5977,6010,6005,6027,5998,6023,6027,6040,6012,6050,6019,6037,6064,6035,6071,6061,6055,6096,6082,6084,6084,6082,6105,6098,6117,6139,6143,6139,6141,6143,6117,6166,6152,6161,6154,6158,6178,6159,6197,6204,6211,6184,6216,6215,6207,6222,6226,6242,6243,6216,6219,6233,6271,6264,6261,6244,6254,6267,6295,6270,6289,6295,6319,6305,6331,6337,6329,6323,6341,6340,6324,6334,6359,6365,6338,6375,6373,6380,6380,6405,6371,6410,6401,6405,6406,6421,6438,6435,6413,6447,6417,6467,6463,6458,6477,6460,6463,6456,6486,6467,6499,6496,6489,6506,6522,6525,6503,6543,6513,6539,6562,6536,6552,6538,6564,6579,6570,6578,6564,6604,6590,6589,6620,6615,6597,6637,6598,6602,6612,6656,6616,6625,6660,6667,6662,6681,6654,6691,6682,6684,6699,6700,6699,6697,6702,6721,6740,6746,6753,6752,6759,6761,6766,6755,6754,6766,6765,6793,6779,6775,6789,6785,6777,6820,6810,6829,6809,6814,6812,6831,6847,6838,6853,6833,6839,6877,6875,6861,6896,6866,6891,6887,6896,6904,6891,6923,6936,6904,6906,6930,6924,6957,6961,6948,6972,6980,6991,6993,6955,7005,7006,7018,6983,7020,7024,7032,7003,7032,7043,7058,7035,7050,7055,7073,7063,7086,7078,7076,7080,7107,7099,7113,7120,7104,7096,7091,7099,7109,7144,7127,7163,7143,7162,7161,7173,7177,7145,7185,7184,7191,7171,7191,7187,7211,7233,7212,7237,7238,7250,7238,7219,7258,7245,7247,7256,7254,7288,7285,7285,7268,7312,7311,7311,7295,7292,7307,7328,7301,7341,7345,7351,7338,7332,7361,7363,7352,7385,7378,7391,7363,7373,7416,7415,7412,7420,7408,7432,7426,7414,7428,7464,7453,7472,7435,7444,7472,7492,7474,7470,7465,7511,7491,7484,7501,7502,7517,7531,7534,7552,7516,7528,7523,7558,7565,7538,7586,7553,7579,7583,7606,7585,7581,7597,7621,7629,7607,7600,7649,7653,7634,7631,7620,7671,7667,7683,7681,7652,7681,7679,7677,7706,7678,7710,7700,7727,7729,7715,7703,7751,7719,7730,7751,7771,7772,7739,7748,7760,7795,7785,7795,7793,7792,7805,7791,7800,7807,7801,7817,7807,7813,7862,7825,7831,7858,7866,7872,7849,7862,7879,7883,7912,7905,7886,7927,7918,7893,7899,7936,7928,7913,7957,7934,7972,7975,7972,7947,7958,7953,7987,8007,8009,8004,8009,8024,7992,8008,8004,8030,8032,8015,8036,8063,8035,8031,8061,8087,8085,8071,8099,8107,8098,8072,8092,8111,8134,8121,8114,8128,8137,8151,8156,8129,8172,8169,8173,8187,8146,8175,8198,8170,8214,8212,8216,8192,8188,8220,8232,8230,8225,8243,8239,8244,8252,8269,8248,8247,8293,8250,8281,8291,8300,8270,8321,8307,8285,8332,8295,8329,8333,8341,8327,8361,8364,8378,8378,8364,8355,8395,8379,8370,8368,8379,8377,8421,8402,8421,8438,8446,8418,8451,8444,8432,8469,8451,8483,8453,8454,8480,8475,8483,8509,8505,8479,8493,8528,8516,8499,8541,8546,8515,8542,8531,8529,8576,8538,8585,8569,8595,8577,8593,8586,8598,8585,8627,8587,8636,8611,8640,8612,8621,8628,8630,8671,8630,8672,8671,8659,8687,8687,8706,8698,8716,8714,8700,8697,8718,8702,8702,8735,8751,8759,8763,8769,8737,8768,8764,8762,8799,8798,8809,8808,8784,8819,8818,8808,8799,8823,8839,8834,8855,8831,8866,8829,8876,8869,8881,8855,8884,8881,8868,8883,8882,8902,8902,8925,8899,8934,8945,8940,8957,8946,8927,8955,8933,8953,8968,8948,8986,8983,8991,9003,9013,9019,9022,9005,9034,9030,9023,9049,9024,9045,9060,9053,9032,9081,9072,9079,9079,9097,9077,9091,9115,9099,9105,9104,9113,9113,9118,9152,9133,9117,9129,9148,9144,9179,9162,9173,9196,9171,9205,9179,9200,9178,9217,9224,9196,9201,9217,9241,9249,9219,9243,9261,9251,9263,9268,9248,9296,9283,9289,9288,9307,9296,9294,9334,9328,9330,9307,9345,9352,9316,9340,9355,9351,9374,9389,9362,9352,9380,9377,9379,9415,9408,9382,9397,9406,9405,9440,9441,9452,9436,9433,9470,9447,9462,9448,9466,9470,9472,9498,9474,9480,9519,9515,9523,9507,9515,9528,9552,9547,9564,9561,9563,9572,9573,9570,9555,9590,9597,9560,9603,9601,9576,9619,9594,9629,9598,9645,9626,9636,9644,9645,9654,9667,9675,9641,9658,9695,9669,9707,9689,9692,9707,9680,9709,9728,9721,9743,9732,9752,9730,9763,9749,9743,9745,9768,9758,9785,9788,9786,9784,9803,9817,9813,9825,9825,9831,9847,9848,9849,9863,9852,9863,9841,9865,9845,9848,9898,9877,9876,9879,9910,9905,9896,9919,9934,9914,9910,9920,9947,9961,9963,9945,9946,9962,9966,9961,9997,10003,9973,10007,10012,9986,10026,9998,10017,10004,10032,10037,10018,10036,10068,10057,10039,10051,10088,10079,10076,10073,10085,10103,10092,10104,10088,10121,10127,10140,10144,10123,10117,10149,10151,10172,10166,10139,10189,10167,10161,10199,10201,10205,10201,10199,10225,10207,10213,10229,10201,10250,10231,10264,10228,10225,10277,10272,10248,10253,10264,10272,10266,10307,10318,10309,10329,10330,10324,10305,10303,10347,10338,10363,10322,10363,10374,10359,10369,10360,10376,10400,10397,10401,10373,10395,10409,10431,10432,10429,10441,10424,10411,10423,10446,10465,10457,10435,10450,10447,10498,10498,10505,10491,10517,10505,10524,10491,10500,10512,10533,10531,10535,10557};
float BA[2103] = {
0.225,0.223,0.22102,0.21906,0.217119,0.215198,0.213296,0.211413,0.209549,0.207703,0.205876,0.204068,0.202277,0.200504,0.198749,0.197012,0.195292,0.193589,0.191903,0.190234,0.188581,0.186946,0.185326,0.183723,0.182136,0.180564,0.179009,0.177469,0.175944,0.174434,0.17294,0.171461,0.169996,0.168546,0.167111,0.16569,0.164283,0.16289,0.161511,0.160146,0.158794,0.157456,0.156132,0.154821,0.153522,0.152237,0.150965,0.149705,0.148458,0.147223,0.146001,0.144791,0.143593,0.142407,0.141233,0.140071,0.13892,0.137781,0.136653,0.135537,0.134431,0.133337,0.132254,0.131181,0.130119,0.129068,0.128027,0.126997,0.125977,0.124967,0.123968,0.122978,0.121998,0.121028,0.120068,0.119117,0.118176,0.117244,0.116322,0.115409,0.114505,0.11361,0.112723,0.111846,0.110978,0.110118,0.109267,0.108424,0.10759,0.106764,0.105946,0.105137,0.104336,0.103542,0.102757,0.101979,0.101209,0.100447,0.0996929,0.0989459,0.0982065,0.0974744,0.0967497,0.0960322,0.0953218,0.0946186,0.0939224,0.0932332,0.0925509,0.0918754,0.0912066,0.0905446,0.0898891,0.0892402,0.0885978,0.0879618,0.0873322,0.0867089,0.0860918,0.0854809,0.0848761,0.0842773,0.0836845,0.0830977,0.0825167,0.0819416,0.0813721,0.0808084,0.0802503,0.0796978,0.0791509,0.0786093,0.0780732,0.0775425,0.0770171,0.0764969,0.075982,0.0754721,0.0749674,0.0744677,0.0739731,0.0734833,0.0729985,0.0725185,0.0720433,0.0715729,0.0711072,0.0706461,0.0701896,0.0697377,0.0692904,0.0688475,0.068409,0.0679749,0.0675451,0.0671197,0.0666985,0.0662815,0.0658687,0.06546,0.0650554,0.0646548,0.0642583,0.0638657,0.0634771,0.0630923,0.0627114,0.0623343,0.0619609,0.0615913,0.0612254,0.0608631,0.0605045,0.0601495,0.059798,0.05945,0.0591055,0.0587644,0.0584268,0.0580925,0.0577616,0.057434,0.0571096,0.0567885,0.0564707,0.0561559,0.0558444,0.0555359,0.0552306,0.0549283,0.054629,0.0543327,0.0540394,0.053749,0.0534615,0.0531769,0.0528951,0.0526162,0.05234,0.0520666,0.0517959,0.051528,0.0512627,0.0510001,0.0507401,0.0504827,0.0502278,0.0499756,0.0497258,0.0494785,0.0492338,0.0489914,0.0487515,0.048514,0.0482789,0.0480461,0.0478156,0.0475875,0.0473616,0.047138,0.0469166,0.0466974,0.0464804,0.0462656,0.046053,0.0458425,0.045634,0.0454277,0.0452234,0.0450212,0.044821,0.0446228,0.0444265,0.0442323,0.0440399,0.0438495,0.043661,0.0434744,0.0432897,0.0431068,0.0429257,0.0427465,0.042569,0.0423933,0.0422194,0.0420472,0.0418767,0.0417079,0.0415409,0.0413755,0.0412117,0.0410496,0.0408891,0.0407302,0.0405729,0.0404172,0.040263,0.0401104,0.0399593,0.0398097,0.0396616,0.039515,0.0393698,0.0392261,0.0390838,0.038943,0.0388036,0.0386655,0.0385289,0.0383936,0.0382597,0.0381271,0.0379958,0.0378658,0.0377372,0.0376098,0.0374837,0.0373589,0.0372353,0.0371129,0.0369918,0.0368719,0.0367532,0.0366356,0.0365193,0.0364041,0.03629,0.0361771,0.0360654,0.0359547,0.0358452,0.0357367,0.0356294,0.0355231,0.0354178,0.0353137,0.0352105,0.0351084,0.0350073,0.0349073,0.0348082,0.0347101,0.034613,0.0345169,0.0344217,0.0343275,0.0342342,0.0341419,0.0340504,0.0339599,0.0338703,0.0337816,0.0336938,0.0336069,0.0335208,0.0334356,0.0333512,0.0332677,0.0331851,0.0331032,0.0330222,0.032942,0.0328625,0.0327839,0.0327061,0.032629,0.0325527,0.0324772,0.0324024,0.0323284,0.0322551,0.0321826,0.0321107,0.0320396,0.0319692,0.0318995,0.0318305,0.0317622,0.0316946,0.0316277,0.0315614,0.0314958,0.0314308,0.0313665,0.0313029,0.0312398,0.0311774,0.0311156,0.0310545,0.0309939,0.030934,0.0308747,0.0308159,0.0307578,0.0307002,0.0306432,0.0305868,0.0305309,0.0304756,0.0304208,0.0303666,0.0303129,0.0302598,0.0302072,0.0301551,0.0301036,0.0300526,0.030002,0.029952,0.0299025,0.0298535,0.0298049,0.0297569,0.0297093,0.0296622,0.0296156,0.0295694,0.0295237,0.0294785,0.0294337,0.0293894,0.0293455,0.029302,0.029259,0.0292164,0.0291743,0.0291325,0.0290912,0.0290503,0.0290098,0.0289697,0.02893,0.0288907,0.0288518,0.0288133,0.0287751,0.0287374,0.0287,0.028663,0.0286264,0.0285901,0.0285542,0.0285187,0.0284835,0.0284486,0.0284142,0.02838,0.0283462,0.0283128,0.0282796,0.0282468,0.0282144,0.0281822,0.0281504,0.0281189,0.0280877,0.0280568,0.0280263,0.027996,0.027966,0.0279364,0.027907,0.0278779,0.0278492,0.0278207,0.0277925,0.0277645,0.0277369,0.0277095,0.0276824,0.0276556,0.027629,0.0276028,0.0275767,0.027551,0.0275255,0.0275002,0.0274752,0.0274504,0.0274259,0.0274017,0.0273777,0.0273539,0.0273304,0.027307,0.027284,0.0272611,0.0272385,0.0272161,0.027194,0.027172,0.0271503,0.0271288,0.0271075,0.0270865,0.0270656,0.0270449,0.0270245,0.0270042,0.0269842,0.0269644,0.0269447,0.0269253,0.026906,0.0268869,0.0268681,0.0268494,0.0268309,0.0268126,0.0267945,0.0267765,0.0267588,0.0267412,0.0267238,0.0267065,0.0266895,0.0266726,0.0266558,0.0266393,0.0266229,0.0266067,0.0265906,0.0265747,0.0265589,0.0265433,0.0265279,0.0265126,0.0264975,0.0264825,0.0264677,0.026453,0.0264385,0.0264241,0.0264099,0.0263958,0.0263818,0.026368,0.0263543,0.0263408,0.0263274,0.0263141,0.026301,0.0262879,0.0262751,0.0262623,0.0262497,0.0262372,0.0262248,0.0262126,0.0262004,0.0261884,0.0261766,0.0261648,0.0261531,0.0261416,0.0261302,0.0261189,0.0261077,0.0260966,0.0260857,0.0260748,0.0260641,0.0260534,0.0260429,0.0260325,0.0260221,0.0260119,0.0260018,0.0259918,0.0259819,0.025972,0.0259623,0.0259527,0.0259432,0.0259337,0.0259244,0.0259152,0.025906,0.0258969,0.025888,0.0258791,0.0258703,0.0258616,0.025853,0.0258445,0.025836,0.0258276,0.0258194,0.0258112,0.0258031,0.025795,0.0257871,0.0257792,0.0257714,0.0257637,0.0257561,0.0257485,0.025741,0.0257336,0.0257263,0.025719,0.0257118,0.0257047,0.0256977,0.0256907,0.0256838,0.0256769,0.0256702,0.0256635,0.0256568,0.0256503,0.0256438,0.0256373,0.025631,0.0256246,0.0256184,0.0256122,0.0256061,0.0256,0.025594,0.0255881,0.0255822,0.0255764,0.0255706,0.0255649,0.0255593,0.0255537,0.0255481,0.0255427,0.0255372,0.0255319,0.0255265,0.0255213,0.0255161,0.0255109,0.0255058,0.0255007,0.0254957,0.0254908,0.0254859,0.025481,0.0254762,0.0254714,0.0254667,0.025462,0.0254574,0.0254529,0.0254483,0.0254438,0.0254394,0.025435,0.0254307,0.0254264,0.0254221,0.0254179,0.0254137,0.0254096,0.0254055,0.0254014,0.0253974,0.0253934,0.0253895,0.0253856,0.0253817,0.0253779,0.0253741,0.0253704,0.0253667,0.025363,0.0253594,0.0253558,0.0253522,0.0253487,0.0253452,0.0253418,0.0253384,0.025335,0.0253316,0.0253283,0.025325,0.0253218,0.0253186,0.0253154,0.0253122,0.0253091,0.025306,0.0253029,0.0252999,0.0252969,0.0252939,0.025291,0.0252881,0.0252852,0.0252824,0.0252795,0.0252767,0.025274,0.0252712,0.0252685,0.0252658,0.0252632,0.0252606,0.0252579,0.0252554,0.0252528,0.0252503,0.0252478,0.0252453,0.0252429,0.0252404,0.025238,0.0252356,0.0252333,0.0252309,0.0252286,0.0252264,0.0252241,0.0252218,0.0252196,0.0252174,0.0252153,0.0252131,0.025211,0.0252089,0.0252068,0.0252047,0.0252027,0.0252006,0.0251986,0.0251966,0.0251947,0.0251927,0.0251908,0.0251889,0.025187,0.0251851,0.0251833,0.0251815,0.0251796,0.0251778,0.0251761,0.0251743,0.0251726,0.0251708,0.0251691,0.0251674,0.0251658,0.0251641,0.0251625,0.0251608,0.0251592,0.0251576,0.0251561,0.0251545,0.025153,0.0251514,0.0251499,0.0251484,0.0251469,0.0251455,0.025144,0.0251426,0.0251411,0.0251397,0.0251383,0.0251369,0.0251356,0.0251342,0.0251329,0.0251315,0.0251302,0.0251289,0.0251276,0.0251264,0.0251251,0.0251239,0.0251226,0.0251214,0.0251202,0.025119,0.0251178,0.0251166,0.0251154,0.0251143,0.0251131,0.025112,0.0251109,0.0251098,0.0251087,0.0251076,0.0251065,0.0251055,0.0251044,0.0251034,0.0251023,0.0251013,0.0251003,0.0250993,0.0250983,0.0250973,0.0250963,0.0250954,0.0250944,0.0250935,0.0250925,0.0250916,0.0250907,0.0250898,0.0250889,0.025088,0.0250871,0.0250863,0.0250854,0.0250845,0.0250837,0.0250829,0.025082,0.0250812,0.0250804,0.0250796,0.0250788,0.025078,0.0250772,0.0250765,0.0250757,0.0250749,0.0250742,0.0250734,0.0250727,0.025072,0.0250713,0.0250705,0.0250698,0.0250691,0.0250685,0.0250678,0.0250671,0.0250664,0.0250658,0.0250651,0.0250644,0.0250638,0.0250632,0.0250625,0.0250619,0.0250613,0.0250607,0.0250601,0.0250595,0.0250589,0.0250583,0.0250577,0.0250571,0.0250566,0.025056,0.0250554,0.0250549,0.0250543,0.0250538,0.0250532,0.0250527,0.0250522,0.0250517,0.0250511,0.0250506,0.0250501,0.0250496,0.0250491,0.0250486,0.0250482,0.0250477,0.0250472,0.0250467,0.0250463,0.0250458,0.0250453,0.0250449,0.0250444,0.025044,0.0250435,0.0250431,0.0250427,0.0250423,0.0250418,0.0250414,0.025041,0.0250406,0.0250402,0.0250398,0.0250394,0.025039,0.0250386,0.0250382,0.0250378,0.0250375,0.0250371,0.0250367,0.0250363,0.025036,0.0250356,0.0250353,0.0250349,0.0250346,0.0250342,0.0250339,0.0250335,0.0250332,0.0250329,0.0250325,0.0250322,0.0250319,0.0250316,0.0250313,0.0250309,0.0250306,0.0250303,0.02503,0.0250297,0.0250294,0.0250291,0.0250288,0.0250286,0.0250283,0.025028,0.0250277,0.0250274,0.0250272,0.0250269,0.0250266,0.0250263,0.0250261,0.0250258,0.0250256,0.0250253,0.0250251,0.0250248,0.0250246,0.0250243,0.0250241,0.0250238,0.0250236,0.0250234,0.0250231,0.0250229,0.0250227,0.0250224,0.0250222,0.025022,0.0250218,0.0250215,0.0250213,0.0250211,0.0250209,0.0250207,0.0250205,0.0250203,0.0250201,0.0250199,0.0250197,0.0250195,0.0250193,0.0250191,0.0250189,0.0250187,0.0250185,0.0250183,0.0250182,0.025018,0.0250178,0.0250176,0.0250174,0.0250173,0.0250171,0.0250169,0.0250168,0.0250166,0.0250164,0.0250163,0.0250161,0.0250159,0.0250158,0.0250156,0.0250155,0.0250153,0.0250152,0.025015,0.0250149,0.0250147,0.0250146,0.0250144,0.0250143,0.0250141,0.025014,0.0250138,0.0250137,0.0250136,0.0250134,0.0250133,0.0250132,0.025013,0.0250129,0.0250128,0.0250126,0.0250125,0.0250124,0.0250123,0.0250122,0.025012,0.0250119,0.0250118,0.0250117,0.0250116,0.0250114,0.0250113,0.0250112,0.0250111,0.025011,0.0250109,0.0250108,0.0250107,0.0250106,0.0250105,0.0250103,0.0250102,0.0250101,0.02501,0.0250099,0.0250098,0.0250097,0.0250096,0.0250095,0.0250095,0.0250094,0.0250093,0.0250092,0.0250091,0.025009,0.0250089,0.0250088,0.0250087,0.0250086,0.0250085,0.0250085,0.0250084,0.0250083,0.0250082,0.0250081,0.025008,0.025008,0.0250079,0.0250078,0.0250077,0.0250077,0.0250076,0.0250075,0.0250074,0.0250074,0.0250073,0.0250072,0.0250071,0.0250071,0.025007,0.0250069,0.0250069,0.0250068,0.0250067,0.0250066,0.0250066,0.0250065,0.0250065,0.0250064,0.0250063,0.0250063,0.0250062,0.0250061,0.0250061,0.025006,0.025006,0.0250059,0.0250058,0.0250058,0.0250057,0.0250057,0.0250056,0.0250055,0.0250055,0.0250054,0.0250054,0.0250053,0.0250053,0.0250052,0.0250052,0.0250051,0.0250051,0.025005,0.025005,0.0250049,0.0250049,0.0250048,0.0250048,0.0250047,0.0250047,0.0250046,0.0250046,0.0250045,0.0250045,0.0250044,0.0250044,0.0250044,0.0250043,0.0250043,0.0250042,0.0250042,0.0250041,0.0250041,0.0250041,0.025004,0.025004,0.0250039,0.0250039,0.0250039,0.0250038,0.0250038,0.0250037,0.0250037,0.0250037,0.0250036,0.0250036,0.0250036,0.0250035,0.0250035,0.0250035,0.0250034,0.0250034,0.0250034,0.0250033,0.0250033,0.0250033,0.0250032,0.0250032,0.0250032,0.0250031,0.0250031,0.0250031,0.025003,0.025003,0.025003,0.0250029,0.0250029,0.0250029,0.0250029,0.0250028,0.0250028,0.0250028,0.0250027,0.0250027,0.0250027,0.0250027,0.0250026,0.0250026,0.0250026,0.0250026,0.0250025,0.0250025,0.0250025,0.0250025,0.0250024,0.0250024,0.0250024,0.0250024,0.0250023,0.0250023,0.0250023,0.0250023,0.0250022,0.0250022,0.0250022,0.0250022,0.0250022,0.0250021,0.0250021,0.0250021,0.0250021,0.0250021,0.025002,0.025002,0.025002,0.025002,0.025002,0.0250019,0.0250019,0.0250019,0.0250019,0.0250019,0.0250018,0.0250018,0.0250018,0.0250018,0.0250018,0.0250017,0.0250017,0.0250017,0.0250017,0.0250017,0.0250017,0.0250016,0.0250016,0.0250016,0.0250016,0.0250016,0.0250016,0.0250015,0.0250015,0.0250015,0.0250015,0.0250015,0.0250015,0.0250015,0.0250014,0.0250014,0.0250014,0.0250014,0.0250014,0.0250014,0.0250014,0.0250013,0.0250013,0.0250013,0.0250013,0.0250013,0.0250013,0.0250013,0.0250013,0.0250012,0.0250012,0.0250012,0.0250012,0.0250012,0.0250012,0.0250012,0.0250012,0.0250011,0.0250011,0.0250011,0.0250011,0.0250011,0.0250011,0.0250011,0.0250011,0.0250011,0.025001,0.025001,0.025001,0.025001,0.025001,0.025001,0.025001,0.025001,0.025001,0.025001,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250009,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250008,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250007,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250006,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250005,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250004,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250003,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250002,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.0250001,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025,0.025};
//TEMPLATE 

vector<float> TRUE;

class OmnipotentYieldPredictor {
  vector<Key> K;
  vector<double> R;

  public:

  vector<Bucket*> Predictor;
  void init_predictor() {
    Predictor.push_back(new Bucket(new _EMPTY(), 1, 1.));
    for(int i = 0; i < NBA; i++) 
      EXTR[i]->bufferize();
    for(int i = 0; i < NBB; i++)
      Predictor.push_back(new Bucket(EXTR2[i], BM[i], 0.055));
  }

  void init_traindata(vector <string> &trainingData) {
    TRAINKEY.clear();
    YIELD.resize(trainingData.size());
    for(int i = 0; i < trainingData.size(); i++) {      
      TRAINKEY.push_back(parse_training(trainingData[i], YIELD[i]));
      TRAINKEY[TRAINKEY.size()-1].index = TRAINKEY.size()-1;
    }
    YP.resize(TRAINKEY.size());
    YP.clear();
  }

  void train(int i) {
    Predictor[i]->init();
    for(int j = 0; j < TRAINKEY.size(); j++) {
      float r = YIELD[j] - YP[j];
      if(r < -15) r = -15; 
      else if(r > 15) r = 15;
      Predictor[i]->train(TRAINKEY[j], r);
    }

    Predictor[i]->compute_pred();

    double MSE = 0.;
    double MSE2 = 0.;
    for(int j = 0; j < TRAINKEY.size(); j++) {
      YP[j] += Predictor[i]->predict(TRAINKEY[j]);
      double err = (YIELD[j] - YP[j])*(YIELD[j] - YP[j]);
      MSE += err;
      MSE2 += (err > 25*25) ? 25*25:err;
    }
    if(i%10 == 0) cout << "train " << i << ": " << " " << time() << "s " << sqrt(MSE/TRAINKEY.size()) << " " << sqrt(MSE2/TRAINKEY.size()) << endl;
  }


  void predict(int i) {
    double MSE = 0.;
    double MSE2 = 0.;
    for(int j = 0; j < K.size(); j++) {  
      R[j] += Predictor[i]->predict(K[j]);
/*      double err = R[j] - TRUE[j];
      err *= err;
      MSE += err;
      if(err > 25*25) err = 25*25;
      MSE2 += err;*/
    }
//    cout << "prediction: " << i << " " << sqrt(MSE/K.size()) << " " << sqrt(MSE2/K.size()) << endl;
  }



  vector <double> predictYield(vector <string> &trainingData, vector <string> &droughtMonitor, vector <string> &droughtNOAA, vector <string> &locations, vector <string> &queries, vector <string> &experimentData) {
    gettimeofday(&BEGIN, NULL);

    for(int i = 0; i < experimentData.size(); i++) 
      trainingData.push_back(experimentData[i]);

    init_traindata(trainingData);
    init_NOAA(droughtNOAA);
    init_DMonitor(droughtMonitor);
    init_location(locations);
    init_predictor();

    for(int i = 0; i < queries.size(); i++) {
      vector<string> T = tokenize(queries[i]);
      while(T.size() < 7) T.push_back("");
      K.push_back(Key(T[0], T[1], T[2], T[3], T[4], T[5], T[6]));
    }
    R.resize(queries.size());

    for(int i = 0; i < Predictor.size(); i++) {
      train(i);
      predict(i);
      Predictor[i]->clear();
      if(time() >= 595) break;
    }

    cout << "end: " <<  time() << "s" << endl;
    return R;
  }
};
