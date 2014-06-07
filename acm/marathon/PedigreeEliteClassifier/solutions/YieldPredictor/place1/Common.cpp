

int MONTH[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; 

vector<string> tokenize(string str, char delim = ',') {
  vector<string> T;
  string token;
  istringstream S(str);
  while(getline(S, token, delim)) T.push_back(token);
  return T;
}



/**
 * Init NOAA : 
 * NOAA[location][date][i] contains var i for location and date, on integer :
 */
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

/**
 * Init DMonitor : 
 * DMonitor[location][date][i] contains var i for location and date, on integer :
 */
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


/**
 * Init LOC : 
 * LOC[i][j] contains var i for location on integer :
 */
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


    // Init LOC_NOAA, make sums to cumpute the mean of NOAA variables for different location sharing the same LOCID.

    int noaa_id = atoi(T[7].c_str()) * 100 + atoi(T[8].c_str());
    for(map<int, vector<int> >::iterator it = NOAA[noaa_id].begin(); it != NOAA[noaa_id].end(); ++it) {
      if(LOC_NOAA[loc][it->first].size() == 0) LOC_NOAA[loc][it->first] = it->second;
      else for(int i = 0; i < LOC_NOAA[loc][it->first].size(); i++)
        LOC_NOAA[loc][it->first][i] += (it->second)[i];
    }

    // Init LOC_DMonitor, make sums to cumpute the mean of DMonitor variables for different location sharing the same LOCCD.
    int fips = atoi(T[9].c_str());
    for(map<int, vector<int> >::iterator it = DMonitor[fips].begin(); it != DMonitor[fips].end(); ++it) {
      if(LOC_DMonitor[loc][it->first].size() == 0) LOC_DMonitor[loc][it->first] = it->second;
      else for(int i = 0; i < LOC_DMonitor[loc][it->first].size(); i++)
        LOC_DMonitor[loc][it->first][i] += (it->second)[i];
    }

    // For cases without data for a given LOCCD
    // We will use the first digit (loc/1000) to assign them mean of NOAA and DMonitor of all location starting with the same digit.
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

  // compute the means by divinding by the number of location per loccd.

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


/*
 * This class is a key for prediction (this contains all the 5 variables provided for prediction
 */


class Key {
  public: 
  int index;  // only used for bufferization on training
  int LOCCD;
  int MaterialId;
  int HERB;
  int RM;    // first part of relative maturity
  int SRM;   // second part of relative maturity
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

// GLOBAL variable containing training data.
vector<Key> TRAINKEY;
vector<float> YIELD; // Not used for prediction...

Key parse_training(string line, float &yield) {
  istringstream S(line);
  vector<string> T;
  string token;
  while(getline(S, token, ',')) T.push_back(token);
  while(T.size() < 9) T.push_back("");

  yield = atof(T[5].c_str());
  return Key(T[1], T[3], T[4], T[7], T[8]);
}


/*
 * Interface of an Extractor.
 * An extractor extract a new variable from the 5 variables provited in a prediction key.
 * It transform a key into an int. (for example temperature a plantDate, material_id, X coordiante, combination of different ofther variables.
 */
struct Extractor {
  virtual int extract(const Key &K) = 0;
  virtual string print() = 0;   // Usefull to generate the code that will initialize the submitted solution.
  virtual ~Extractor() {}
};


/*
 * A basic prediction algorithm tha but keys into buckets according to the value of on variable extracted from the key.
 * The prediction of a given key is just the mean of the training key that are in the same bucket.
 */
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



  void bufferize() { // Used to speed training
    vector<int> TMP(TRAINKEY.size());
    for(int i = 0; i < TRAINKEY.size(); i++) TMP[i] = get_key(TRAINKEY[i]);
    BUFFER = new unsigned short[TRAINKEY.size()];
    for(int i = 0; i < TRAINKEY.size(); i++) BUFFER[i] = TMP[i];
  }

  // initialise prediction that are just means (SUM/NB) * alpha.
  // in the case of predicting an error, (YIELD - previous prediction), is not to correct the full error but just of part of the error.
  // new prediction = prev_prediction + alpha * predicted_error.
  // this reduce dramatically the overfitting but we will have to use more step to converge to a better prediction.
  void compute_pred() {
    double M = 0;
    int nb = 0;
    for(int i = 0; i < N; i++) {M += SUM[i]; nb += NB[i];}
    M /= double(nb);
    for(int i = 0; i < N; i++) PRED[i] = alpha * (SUM[i] + M) / double(NB[i] + 1);
    ready = true;
  }

  // find in which bucket a key is (just basic modulo)
  int get_key(const Key &K) {
    if(BUFFER) return BUFFER[K.index];
    int k = E->extract(K);
    k %= N;
    if(k < 0) k += N;
    return k;
  }

  /*
   * Constructor :
   * E : extractor (that will exctrat a variable from the key)
   * N : number of bucket : hox many class of key can we differentiate.
   * alpha : multiplicative factor applied to the prediction (this factor is here for implementation conveinience but has nothing to do with the basic predictor)
   */

  Bucket(int N, Extractor *E, float alpha = 0.05) : E(E), N(N), alpha(alpha), SUM(N), NB(N), PRED(N), BUFFER(0) { reset(); }

  // Train the Algo on one (key, observation). Observation is YIELD or a prediction error (YIELD - previous prediction)
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

  // Usefull to generate the code that will initialize the submitted solution.
  string print() {
    ostringstream S;
    S << "Bucket(" << N << ", new " << E->print() << "," << alpha << ")";
    return S.str();
  }

  // return the prediction for a key.
  float predict(const Key &K) {
    if(!ready) compute_pred();
    return PRED[get_key(K)];
  }

};

/*
 * Implementation of Extractors
 * Base extractors.
 */
struct _LOCID : public Extractor {
  int extract(const Key &K) {return K.LOCCD;}
  string print() {return "_LOCID()";}
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



/*
 * This extractor takes a location LOCCD and extract an mean of a NOAA or Drought monitor on a given period.
 * The priod can be relative to the plantDate or absolute int the plant Year
 * for NOAA offset and length are month
 * for NOAA offset and length are weeks
 * This extractor uses preloaded data stored by loccd from LOC_NOAA and LOC_DMonitor
 *
 * If the LOCCD of the key is unknow (no data on it) we will use only the first digit of it (there are aggregated data per first digit in LOC_NOAA and LOC_DMonitor
 */
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

/**
 * Extract a given varaible from Locations.csv.
 * If the LOCCD of the key is unknow (no data on it) we will use only the first digit
 */
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

/**
 * Make a new variable as a combination of two other variables.
 * Usefull to caputre correleation between variable.
 *
 * New_varaible = A1 * (var1 / d1) + A2 * (var2 / d2);
 * integer division (/d1 and /d2) allow to reduce the number of modalities of a given variable (for exemple temperature from -200 to 10000 can by mpped to -2 to 100
 *
 * In practice we mainly used : 
 *  - d2 chosen to reduce the number of modalities (two much modalities ==> few cases per modaliti ==> overfitting)
 *  - d1 = 1
 *  - A1 : same order as d1 to avoid too much collision of different pairs
 *  - A2 = 1
 */

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

