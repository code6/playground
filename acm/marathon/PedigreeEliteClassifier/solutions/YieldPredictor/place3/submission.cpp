#include <string>
#include <vector>
#include <algorithm>
#include <string.h> 
#include <math.h>
#ifndef __GNUC__
  #include <float.h>
#endif

//#define OS_PRED_BY_YEARS

//#define PRINT_PROGRESS
//#define OVERPASS_BREAK
//#define READ_QUERY_TARGETS

#define MIN_YIELD 9.0
#define MAX_YIELD 115.0

#define P1_FOLD_COUNT 30
#define MAX_DESIGN_ROWS (20*1024)

#define CAP_VALUE 25.0

#define USE_NS

using namespace std;

#ifdef USE_NS
  #define NS_BEGIN namespace SoybeanPMM2 {
  #define NS_END };
  #define NS_REF SoybeanPMM2::
#else
  #define NS_BEGIN
  #define NS_END
  #define NS_REF
#endif

NS_BEGIN

#define NULL_STR "NULL"

#ifdef __GNUC__
  inline bool IsDoubleFinite(const double AValue) {
    return finite(AValue) != 0;
  };
  #define RESTRICT_PTR * __restrict__
  #define ALIGN(AAlignSize) __attribute__((aligned(AAlignSize)))
#else
  inline bool IsDoubleFinite(const double AValue) {
    return _finite(AValue) != 0;
  };
  #define RESTRICT_PTR * __restrict
  #define ALIGN(AAlignSize) __declspec(align(AAlignSize))
#endif

const static union TDoubleRec {
  unsigned long long i;
  double d;
} NaNDouble = {0xfff8000000000000ULL};

static class TRandGen {
  private:
    static const long long msk = (long long)0xFFFFFFFFFFFFLL;
    static const long long ade = (long long)0xBLL;
    static const long long mlp = (long long)0x5DEECE66DLL;
    long long seed;
    double g;
    bool haveg;
    int get(int bits) {
      long long n = (seed * mlp + ade) & msk;
      seed = n;
      return int(n >> (48 - bits));
    }
  public:
    TRandGen() {
      seed = 22969564825760LL;
      haveg = false;
    }
    int GetInt(int ABound) {
      if (ABound <= 1)
        return 0;
      if ((-ABound & ABound) == ABound)
        return (int)((ABound * (long long)get(31)) >> 31);
      int b, v;
      do {
        b = get(31);
        v = b % ABound;
      } while(b - v + (ABound-1) < 0);
      return v;
    }
    double GetDouble() {
      static const double m = 1.0 / double(65536.0*0x2000000000LL);
      long long l = get(26);
      return double((l << 27) + get(27))*m;
    }
    double GetGauss() {
      if(haveg) {
        haveg = false;
        return g;
      }
      double a, b, s;
      do { 
        a = 2.0 * GetDouble() - 1.0;
        b = 2.0 * GetDouble() - 1.0;
        s = a * a + b * b;
      } while (s >= 1.0 || s == 0.0);
      s = sqrt(-2.0 * log(s)/s);
      g = b * s;
      haveg = true;
      return a * s;
    }
} RGen;

struct TMonRec {
  int year, month, day, fips;
  double d[6]; // 0 Nothing, 1 D0, 2 D1, 3 D2, 4 D3, 5 D4
  int row;
  TMonRec() {
    fips = day = month = year = 0;
    for(unsigned int i = 0; i < sizeof(d)/sizeof(d[0]); ++i)
      d[i] = NaNDouble.d;
    row = -1;
  }
};
struct TNoaRec {
  int state, division, year, month;
  double d[15]; // 0 PCP, 1 TMP, 2 PDSI, 3 PHDI, 4 ZNDX, 5 PMDI, 6 CDD, 7 HDD
                // 8 SP01, 9 SP02, 10 SP03, 11 SP06, 12 SP09, 13 SP12, 14 SP24
  int row;
  TNoaRec() {
    month = year = division = state = 0;
    for(unsigned int i = 0; i < sizeof(d)/sizeof(d[0]); ++i)
      d[i] = NaNDouble.d;
    row = -1;
  }
};
struct TLocRec {
  int code, state, division, fips;
  double lat, lon, zone, szone, band;
  int row;
  int lzone;
  TLocRec() {
    fips = division = state = code = 0;
    band = szone = zone = lon = lat = NaNDouble.d;
    row = -1;
    lzone = 0;
  }
};
struct TFactPoint {
  int row; // code,rep,year,month,day
  int col; // var
  double targ;
  TFactPoint() {
    col = row = -1;
    targ = NaNDouble.d;
  }
};
struct TDatRec {

  int id, code, rep, var;
  double type, yield, mat, rmat;
  int year, month, day;
  int row;

  TFactPoint fpnt;

  TDatRec *nextvar;
  int fold;
  int env;

  TDatRec() {
    var = rep = code = id = 0;
    rmat = mat = yield = type = NaNDouble.d;
    day = month = year = 0;
    row = -1;

    nextvar = NULL;
    env = fold = 0;
  }
};
struct TAskRec {

  int code, var;
  double type, rmat;
#ifdef PRINT_PROGRESS
  double targ;
#endif
  int year, month, day;
  int row;

  double yield_p1, yield_f;

  TAskRec* nextvar;
  int env;

  int fcol;          // var
  vector<int> frows; // code,rep,year,month,day

  TAskRec() {
    var = code = 0;
    rmat = type = NaNDouble.d;
#ifdef PRINT_PROGRESS
    targ = NaNDouble.d;
#endif
    day = month = year = 0;
    row = -1;
    yield_f = yield_p1 = NaNDouble.d;
    nextvar = NULL;
    env = 0;
    fcol = -1;
  }
};

static vector<int> PredVars;
static vector<TMonRec> Mon;
static vector<TNoaRec> Noa;
static vector<TLocRec> Loc;
static vector<TDatRec> Dat;
static vector<TAskRec> Ask;

static vector<TDatRec*> PredVarsLut;

static double GlobalMeanYield;

static ALIGN(64) int DesignFolds[MAX_DESIGN_ROWS];

void SplitTokens(const char *AStr, vector<string> &ATokens) {
  unsigned int n = 0;
  char *p = (char*)AStr;
  char *pp = (char*)AStr;
  while(*p != 0) {
    if(*p == ',') {
      if(n >= ATokens.size())
        ATokens.resize(n+1);
      ATokens[n++].assign(pp, p-pp);
      pp = p+1;
    }
    ++p;
  }
  ATokens.resize(n+1);
  ATokens[n].assign(pp, p-pp);
}

void DecodeVar(vector<string> &AVar) {
  PredVars.resize(AVar.size());
  for(unsigned int i = 0; i < PredVars.size(); ++i)
    PredVars[i] = strtol(AVar[i].c_str(), NULL, 10);
}
void DecodeMon(vector<string> &AMon) {
  vector<string> tokens;
  Mon.clear();
  Mon.resize(AMon.size());
  for(unsigned int i = 0; i < Mon.size(); ++i) {
    Mon[i].row = (int)i;
    SplitTokens(AMon[i].c_str(), tokens);
    if(tokens.size() <= 0)
      continue;
    int v = strtol(tokens[0].c_str(), NULL, 10);
    Mon[i].year = v/10000;
    v -= Mon[i].year*10000;
    Mon[i].month = v/100;
    Mon[i].day = v-Mon[i].month*100;
    if(tokens.size() < 1)
      continue;
    Mon[i].fips = strtol(tokens[1].c_str(), 0, 10);
    for(unsigned int j = 2; (j < 2+6) && (j < tokens.size()); ++j)
      Mon[i].d[j-2] = strtod(tokens[j].c_str(), NULL);
  }
}
void DecodeNoa(vector<string> &ANoa) {
  vector<string> tokens;
  Noa.clear();
  Noa.resize(ANoa.size());
  for(unsigned int i = 0; i < Noa.size(); ++i) {
    Noa[i].row = (int)i;
    SplitTokens(ANoa[i].c_str(), tokens);
    if(tokens.size() <= 0)
      continue;
    Noa[i].state = strtol(tokens[0].c_str(), NULL, 10);
    if(tokens.size() <= 1)
      continue;
    Noa[i].division = strtol(tokens[1].c_str(), NULL, 10);
    if(tokens.size() <= 2)
      continue;
    int v = strtol(tokens[2].c_str(), NULL, 10);
    Noa[i].year = v/100;
    Noa[i].month = v-Noa[i].year*100;
    for(unsigned int j = 3; (j < 3+15) && (j < tokens.size()); ++j)
      Noa[i].d[j-3] = strtod(tokens[j].c_str(), NULL);
  }
}
void DecodeLoc(vector<string> &ALoc) {
  vector<string> tokens;
  Loc.clear();
  Loc.resize(ALoc.size());
  for(unsigned int i = 0; i < Loc.size(); ++i) {
    Loc[i].row = (int)i;
    SplitTokens(ALoc[i].c_str(), tokens);
    if(tokens.size() <= 0)
      continue;
    Loc[i].code = strtol(tokens[0].c_str(), NULL, 10);
    if(tokens.size() <= 1)
      continue;
    Loc[i].lat = strtod(tokens[1].c_str(), NULL);
    if(tokens.size() <= 2)
      continue;
    Loc[i].lon = strtod(tokens[2].c_str(), NULL);
    if(tokens.size() <= 4)
      continue;
    Loc[i].zone = strtod(tokens[4].c_str(), NULL);
    if(tokens.size() <= 5)
      continue;
    if(strcmp(tokens[5].c_str(), "Early") == 0)
      Loc[i].szone = 0.0;
    else if(strcmp(tokens[5].c_str(), "Mid") == 0)
      Loc[i].szone = 1.0;
    else if(strcmp(tokens[5].c_str(), "Late") == 0)
      Loc[i].szone = 2.0;
    if(tokens.size() <= 6)
      continue;
    Loc[i].band = strtod(tokens[6].c_str(), NULL);
    if(tokens.size() <= 7)
      continue;
    Loc[i].state = strtol(tokens[7].c_str(), NULL, 10);
    if(tokens.size() <= 8)
      continue;
    Loc[i].division = strtol(tokens[8].c_str(), NULL, 10);
    if(tokens.size() <= 9)
      continue;
    Loc[i].fips = strtol(tokens[9].c_str(), NULL, 10);
  }
}
double DecodeVarType(const char *AStr) {
  static const char *strs[4] = {NULL_STR, "RR2Y", "RR1", "conv"};
  static const double vals[4] = {-1.0, 0.0, 1.0, 2.0};
  double type = NaNDouble.d;
  for(int i = 0; i < (int)(sizeof(vals)/sizeof(vals[0])); ++i)
    if(strcmp(AStr, strs[i]) == 0) {
      type = vals[i];
      break;
    }
  return type;
}
void DecodeDat(vector<string> &ADat) {
  vector<string> tokens;
  Dat.clear();
  Dat.resize(ADat.size());
  for(unsigned int i = 0; i < Dat.size(); ++i) {
    Dat[i].row = (int)i;
    SplitTokens(ADat[i].c_str(), tokens);
    if(tokens.size() <= 0)
      continue;
    Dat[i].id = strtol(tokens[0].c_str(), NULL, 10);
    if(tokens.size() <= 1)
      continue;
    if(strcmp(tokens[1].c_str(), NULL_STR) != 0)
      Dat[i].code = strtol(tokens[1].c_str(), NULL, 10);
    if(tokens.size() <= 2)
      continue;
    Dat[i].rep = strtol(tokens[2].c_str(), NULL, 10);
    if(tokens.size() <= 3)
      continue;
    Dat[i].var = strtol(tokens[3].c_str(), NULL, 10);
    if(tokens.size() <= 4)
      continue;
    Dat[i].type = DecodeVarType(tokens[4].c_str());
    if(tokens.size() <= 5)
      continue;
    Dat[i].yield = strtod(tokens[5].c_str(), NULL);
    if(tokens.size() <= 6)
      continue;
    if(strcmp(tokens[6].c_str(), NULL_STR) != 0)
      Dat[i].mat = strtod(tokens[6].c_str(), NULL);
    if(tokens.size() <= 7)
      continue;
    if(strcmp(tokens[7].c_str(), NULL_STR) != 0)
      Dat[i].rmat = strtod(tokens[7].c_str(), NULL);
    if(tokens.size() <= 8)
      continue;
    char *e;
    Dat[i].year = strtol(tokens[8].c_str(), &e, 10);
    if(*e != '-')
      continue;
    Dat[i].month = strtol(e+1, &e, 10);
    if(*e != '-')
      continue;
    Dat[i].day = strtol(e+1, NULL, 10);
  }
}
void DecodeAsk(vector<string> &AQueries) {
  vector<string> tokens;
  Ask.clear();
  Ask.resize(AQueries.size());
  for(unsigned int i = 0; i < Ask.size(); ++i) {
    Ask[i].row = (int)i;
    SplitTokens(AQueries[i].c_str(), tokens);
    if(tokens.size() <= 0)
      continue;
    if(strcmp(tokens[0].c_str(), NULL_STR) != 0)
      Ask[i].code = strtol(tokens[0].c_str(), NULL, 10);
    if(tokens.size() <= 1)
      continue;
    if(strcmp(tokens[1].c_str(), NULL_STR) != 0)
      Ask[i].var = strtol(tokens[1].c_str(), NULL, 10);
    if(tokens.size() <= 2)
      continue;
    Ask[i].type = DecodeVarType(tokens[2].c_str());
    if(tokens.size() <= 3)
      continue;
    if(strcmp(tokens[3].c_str(), NULL_STR) != 0)
      Ask[i].rmat = strtod(tokens[3].c_str(), NULL);
    if(tokens.size() <= 4)
      continue;
    char *e;
    Ask[i].year = strtol(tokens[4].c_str(), &e, 10);
    if(*e != '-')
      continue;
    Ask[i].month = strtol(e+1, &e, 10);
    if(*e != '-')
      continue;
    Ask[i].day = strtol(e+1, NULL, 10);
#ifdef READ_QUERY_TARGETS
    if(tokens.size() <= 5)
      continue;
    if(strcmp(tokens[5].c_str(), NULL_STR) != 0)
      Ask[i].targ = strtod(tokens[5].c_str(), NULL);
#endif
  }
}

int CompareDat(TDatRec *ARec1, TDatRec *ARec2) {
  int c = ARec1->id-ARec2->id;
  if(c == 0) {
    c = ARec1->code-ARec2->code;
    if(c == 0) {
      c = ARec1->rep-ARec2->rep;
      if(c == 0) {
        c = ARec1->var-ARec2->var;
        if(c == 0) {
          c = int(ARec1->type-ARec2->type);
          if(c == 0) {
            c = int(ARec1->year-ARec2->year);
            if(c == 0) {
              c = int(ARec1->month-ARec2->month);
              if(c == 0)
                c = int(ARec1->day-ARec2->day);
            }
          }
        }
      }
    }
  }
  return c;
}

bool CompareDatRecs(TDatRec *ARec1, TDatRec *ARec2) {
  int c = CompareDat(ARec1, ARec2);
  if(c != 0)
    return c < 0;
  return ARec1->row < ARec2->row;
}

void CleanupData() {

  sort(PredVars.begin(),PredVars.end());
  unsigned int n = 0;
  for(unsigned int i = 1; i < PredVars.size(); ++i)
    if(PredVars[n] != PredVars[i])
      PredVars[++n] = PredVars[i];
  PredVars.resize(++n);

  for(unsigned int i = 0; i < Noa.size(); ++i) {
    if(Noa[i].d[6] == -9999.0) // CDD
      Noa[i].d[6] = 0.0;
    if(Noa[i].d[7] == -9999.0) // HDD
      Noa[i].d[7] = 0.0;
  }

  vector<TDatRec*> sdat(Dat.size());
  for(unsigned int i = 0; i < Dat.size(); ++i)
    sdat[i] = &Dat[i];
  sort(sdat.begin(), sdat.end(), CompareDatRecs);
  for(int i = 1, fi = 0; i <= (int)sdat.size(); ++i)
    if((i >= (int)sdat.size()) || (CompareDat(sdat[i], sdat[i-1]) != 0)) {
      if(fi < i-1) {
        double y = 0.0;
        double m = 0.0;
        double r = 0.0;
        int yc = 0; 
        int mc = 0; 
        int rc = 0; 
        for(int j = fi; j < i; ++j) {
          if(IsDoubleFinite(sdat[j]->yield)) {
            y += sdat[j]->yield;
            yc++;
          }
          if(IsDoubleFinite(sdat[j]->mat)) {
            m += sdat[j]->mat;
            mc++;
          }
          if(IsDoubleFinite(sdat[j]->rmat)) {
            r += sdat[j]->rmat;
            rc++;
          }
          if(j > fi)
            sdat[j]->row = -1;
        }
        if(yc > 0)
          sdat[fi]->yield = y/yc;
        if(mc > 0)
          sdat[fi]->mat = m/mc;
        if(rc > 0)
          sdat[fi]->rmat = r/rc;
      }
      fi = i;
    }
  n = 0;
  for(unsigned int i = 0; i < Dat.size(); ++i)
    if(Dat[i].row >= 0)
      Dat[n++] = Dat[i];
  Dat.resize(n);
}

inline int CompareMon(const TMonRec &ARec, int AFips, int AYear, int AMonth, int ADay) {
  int c = ARec.fips-AFips;
  if(c == 0) {
    c = ARec.year-AYear;
    if(c == 0) {
      c = ARec.month-AMonth;
      if(c == 0)
        c = ARec.day-ADay;
    }
  }
  return c;
}

bool CompareMonRecs(const TMonRec &ARec1, const TMonRec &ARec2) {
  int c = CompareMon(ARec1, ARec2.fips, ARec2.year, ARec2.month, ARec2.day);
  if(c != 0)
    return c < 0;
  return ARec1.row < ARec2.row;
}

inline int CompareNoa(const TNoaRec &ARec, int AState, int ADivision, int AYear, int AMonth) {
  int c = ARec.state-AState;
  if(c == 0) {
    c = ARec.division-ADivision;
    if(c == 0) {
      c = ARec.year-AYear;
      if(c == 0)
        c = ARec.month-AMonth;
    }
  }
  return c;
}

bool CompareNoaRecs(const TNoaRec &ARec1, const TNoaRec &ARec2) {
  int c = CompareNoa(ARec1, ARec2.state, ARec2.division, ARec2.year, ARec2.month);
  if(c != 0)
    return c < 0;
  return ARec1.row < ARec2.row;
}

inline void ShuffleInts(int ACount, int *AInts, TRandGen &ARGen) {
  while(--ACount > 0)
    swap(AInts[ACount], AInts[ARGen.GetInt(ACount+1)]);
}

void LinkData() {

  for(unsigned int i = 0; i < Loc.size(); ++i) {
    int z = Loc[i].code;
    while(z >= 10)
      z /= 10;
    Loc[i].lzone = z;
  }

  sort(Mon.begin(), Mon.end(), CompareMonRecs);

  sort(Noa.begin(), Noa.end(), CompareNoaRecs);

  vector<bool> lut(PredVars[PredVars.size()-1]-PredVars[0]+1);
  for(unsigned int i = 0; i < PredVars.size(); ++i)
    lut[PredVars[i]-PredVars[0]] = true;

  PredVarsLut.clear();
  PredVarsLut.resize(lut.size());
  for(int i = (int)Dat.size()-1; i >= 0; --i) {
    int j = Dat[i].var-PredVars[0];
    if((j >= 0) && (j < (int)lut.size()) && lut[j]) {
      Dat[i].nextvar = PredVarsLut[j];
      PredVarsLut[j] = &Dat[i];
    }
  }
  for(unsigned int i = 0; i < PredVars.size(); ++i) {
    TDatRec* f = PredVarsLut[PredVars[i]-PredVars[0]];
    int n = 0;
    for(TDatRec* p = f; p != NULL; p = p->nextvar)
      n++;
    int fc = min(n, P1_FOLD_COUNT);
    for(int i = 0, fi = fc; i < n; ++i, fi = (fi-1) | (fc & ((fi-2) >> 31)))
      DesignFolds[i] = fi;
    ShuffleInts(n, DesignFolds, RGen);
    for(TDatRec* p = f; p != NULL; p = p->nextvar)
      p->fold = DesignFolds[--n];
  }

  GlobalMeanYield = 0.0;
  int n = 0;
  for(unsigned int i = 0; i < Dat.size(); ++i) {
//    int j = Dat[i].var-PredVars[0];
//    if((j >= 0) && (j < (int)lut.size()) && lut[j]) {
      GlobalMeanYield += Dat[i].yield;
      n++;
//    }
  }
  GlobalMeanYield /= n;

#ifdef PRINT_PROGRESS
  for(unsigned int i = 0; i < Ask.size(); ++i)
    if(!IsDoubleFinite(Ask[i].targ))
      Ask[i].targ = GlobalMeanYield;
#endif
}

#define FACT_TRAIN_PASSES 200
#define FACT_CNT 512
#define FACT_INIT_DEV 0.1
#define FACT_LEARN_RATE (0.2/FACT_CNT)
#define FACT_MLEARN_RATE (0.3/FACT_CNT)
#define FACT_REG_RATIO (1.0-FACT_LEARN_RATE*0.45)
#define FACT_MREG_RATIO (1.0-FACT_MLEARN_RATE*0.0)

static int RowCount_F, ColCount_F, LastPredCol_F;
static ALIGN(64) double ColMeans_F[50*1024];
static ALIGN(64) double ColSpace_F[50*1024][FACT_CNT];
static ALIGN(64) int RowSups_F[2048];
static ALIGN(64) double RowMeans_F[2048];
static ALIGN(64) double RowSpace_F[2048][FACT_CNT];

inline bool IsPredVar(int AVar) {
  int i = AVar-PredVars[0];
  return (i >= 0) && (i < (int)PredVarsLut.size()) && (PredVarsLut[i] != NULL);
}

inline int CompareDatByFactCol(TDatRec *ARec, int AVar) {
  if(ARec->var != AVar) {
    if(IsPredVar(ARec->var) != IsPredVar(AVar))
      return IsPredVar(AVar) ? 1 : -1;
    return ARec->var-AVar;
  }
  return 0;
}

inline int CompareDatByFactRow(TDatRec *ARec, int ACode, int AYear, int AMonth, int ADay) {
  if(ARec->code != ACode)
    return ARec->code-ACode;
  if(ARec->year != AYear)
    return ARec->year-AYear;
  if(ARec->month != AMonth)
    return ARec->month-AMonth;
  if(ARec->day != ADay)
    return ARec->day-ADay;
  return 0;
}

inline int CompareDatByFactRow(TDatRec *ARec, int ACode, int AYear, int AMonth, int ADay, int ARep) {
  int c = CompareDatByFactRow(ARec, ACode, AYear, AMonth, ADay);
  if(c != 0)
    return c;
  if(ARec->rep != ARep)
    return ARec->rep-ARep;
  return 0;
}

bool CompareDatRecsByFactColRow(TDatRec *ARec1, TDatRec *ARec2) {
  int c = CompareDatByFactCol(ARec1, ARec2->var);
  if(c != 0)
    return c < 0;
  c = CompareDatByFactRow(ARec1, ARec2->code, ARec2->year, ARec2->month, ARec2->day, ARec2->rep);
  if(c != 0)
    return c < 0;
  return ARec1->row < ARec2->row;
}

bool CompareDatRecsByFactRowCol(TDatRec *ARec1, TDatRec *ARec2) {
  int c = CompareDatByFactRow(ARec1, ARec2->code, ARec2->year, ARec2->month, ARec2->day, ARec2->rep);
  if(c != 0)
    return c < 0;
  c = CompareDatByFactCol(ARec1, ARec2->var);
  if(c != 0)
    return c < 0;
  return ARec1->row < ARec2->row;
}

int SearchCol_F(int AVar, vector<TDatRec*> &APnts) {
  int low = 0;
  int high = (int)APnts.size()-1;
  while(low <= high) {
    int i = (low+high) >> 1;
    int c = CompareDatByFactCol(APnts[i], AVar);
    if(c < 0)
      low = i+1;
    else if(c == 0) 
      return APnts[i]->fpnt.col;
    else
      high = i-1;
  }
  return -1;
}

bool FindRow_F(int ACode, int AYear, int AMonth, int ADay, vector<TDatRec*> &APnts, int &AIndex) {
  bool res = false;
  int low = 0;
  int high = (int)APnts.size()-1;
  while(low <= high) {
    int i = (low+high) >> 1;
    int c = CompareDatByFactRow(APnts[i], ACode, AYear, AMonth, ADay);
    if(c < 0)
      low = i+1;
    else {
      high = i-1;
      if(c == 0)
        res = true;
    }
  }
  AIndex = low;
  return res;
}

void MakeFactPoints() {

  vector<TDatRec*> pnts(Dat.size());
  for(unsigned int i = 0; i < Dat.size(); ++i)
    pnts[i] = &Dat[i];

  sort(pnts.begin(), pnts.end(), CompareDatRecsByFactColRow);
  for(int i = 1, fi = 0; i <= (int)pnts.size(); ++i)
    if((i == (int)pnts.size()) || 
       (CompareDatByFactRow(pnts[fi], 
          pnts[i]->code, pnts[i]->year, pnts[i]->month, pnts[i]->day, pnts[i]->rep) != 0) ||
       (CompareDatByFactCol(pnts[fi], pnts[i]->var) != 0)) {
      double v = 0.0;
      for(int j = fi; j < i; ++j)
        v += pnts[j]->yield;
      v = v/(i-fi) - GlobalMeanYield;
      for(int j = fi; j < i; ++j)
        pnts[j]->fpnt.targ = v;
      fi = i;
    }

  ColCount_F = 0;
  pnts[0]->fpnt.col = 0;
  for(unsigned int i = 1; i < pnts.size(); ++i) {
    if(CompareDatByFactCol(pnts[i-1], pnts[i]->var) != 0)
      ColCount_F++;
    pnts[i]->fpnt.col = ColCount_F;
  }
  ColCount_F++;

  int LastPredCol_F = 0;
  for(int i = (int)PredVars.size()-1; (LastPredCol_F <= 0) && (i >= 0); --i)
    LastPredCol_F = SearchCol_F(PredVars[i], pnts);

  for(unsigned int i = 0; i < Ask.size(); ++i)
    Ask[i].fcol = SearchCol_F(Ask[i].var, pnts);

  sort(pnts.begin(), pnts.end(), CompareDatRecsByFactRowCol);
  RowCount_F = 0;
  pnts[0]->fpnt.row = 0;
  for(unsigned int i = 1; i < pnts.size(); ++i) {
    if(CompareDatByFactRow(pnts[i-1], 
         pnts[i]->code, pnts[i]->year, pnts[i]->month, pnts[i]->day, pnts[i]->rep) != 0)
      RowCount_F++;
    pnts[i]->fpnt.row = RowCount_F;
  }
  RowCount_F++;

  for(unsigned int i = 0; i < Ask.size(); ++i) {
    int j;
    int c = Ask[i].code;
    int y = Ask[i].year;
    int m = Ask[i].month;
    int d = Ask[i].day;
    Ask[i].frows.clear();
    if(!FindRow_F(c, y, m, d, pnts, j))
      continue;
    int r = pnts[j]->fpnt.row;
    Ask[i].frows.push_back(r);
    while(++j < (int)pnts.size()) {
      if(CompareDatByFactRow(pnts[j], c, y, m, d) != 0)
        break;
      if(r != pnts[j]->fpnt.row) {
        r = pnts[j]->fpnt.row;
        Ask[i].frows.push_back(r);
      }
    }
  }
}

void InitMeans_F(vector<TDatRec*> &ATrainPoints) {

  memset(RowSups_F, 0, RowCount_F*sizeof(int));
  memset(RowMeans_F, 0, RowCount_F*sizeof(double));
  for(unsigned int i = 0; i < ATrainPoints.size(); ++i) {
    RowSups_F[ATrainPoints[i]->fpnt.row]++;
    RowMeans_F[ATrainPoints[i]->fpnt.row] += ATrainPoints[i]->fpnt.targ;
  }
  const int kr = 0;
  for(int i = 0; i < RowCount_F; ++i)
    if(RowSups_F[i] > 0)
      RowMeans_F[i] = RowMeans_F[i]/(RowSups_F[i]+kr);

  memset(ColMeans_F, 0, ColCount_F*sizeof(double));
}

void InitFacts_F() {
  for(int i = 0; i < RowCount_F; ++i)
    for(unsigned int j = 0; j < FACT_CNT; ++j)
      RowSpace_F[i][j] = RGen.GetGauss()*FACT_INIT_DEV;
  for(int i = 0; i < ColCount_F; ++i)
    for(unsigned int j = 0; j < FACT_CNT; ++j)
      ColSpace_F[i][j] = RGen.GetGauss()*FACT_INIT_DEV;
}

bool CompareDatRecsByColRows_F(TDatRec *ARec1, TDatRec *ARec2) {
  if(ARec1->fpnt.col != ARec2->fpnt.col) 
    return ARec1->fpnt.col < ARec2->fpnt.col;
  if(ARec1->fpnt.row != ARec2->fpnt.row) 
    return ARec1->fpnt.row < ARec2->fpnt.row;
  return ARec1->row < ARec2->row;
}

void CountPreds_F() {
  double avgcolfacts[FACT_CNT], avgcolmean, avgrowfacts[FACT_CNT], avgrowmean, val;
  bool havecolavg = false;
  bool haverowavg = false;
  for(unsigned int i = 0; i < Ask.size(); ++i) {

    val = GlobalMeanYield;

    int ci = Ask[i].fcol;
    int rc = (int)Ask[i].frows.size();

    if((ci < 0) && !havecolavg) {
      havecolavg = true;
      avgcolmean = 0.0;
      memset(avgcolfacts, 0, FACT_CNT*sizeof(double));
      for(int k = 0; k <= LastPredCol_F; ++k) {
        double RESTRICT_PTR cf = ColSpace_F[k];
        avgcolmean += ColMeans_F[k];
        for(int j = 0; j < FACT_CNT; ++j)
          avgcolfacts[j] += cf[j];
      }
      double s = 1.0/(LastPredCol_F+1);
      avgcolmean *= s;
      for(int j = 0; j < FACT_CNT; ++j)
        avgcolfacts[j] *= s;
    }

    if((rc <= 0) && !haverowavg) {
      haverowavg = true;
      avgrowmean = 0.0;
      memset(avgrowfacts, 0, FACT_CNT*sizeof(double));
      for(int k = 0; k < RowCount_F; ++k) {
        double RESTRICT_PTR rf = RowSpace_F[k];
        avgrowmean += RowMeans_F[k];
        for(int j = 0; j < FACT_CNT; ++j)
          avgrowfacts[j] += rf[j];
      }
      double s = 1.0/RowCount_F;
      avgrowmean *= s;
      for(int j = 0; j < FACT_CNT; ++j)
        avgrowfacts[j] *= s;
    }

    if(ci < 0) {
      if(rc > 0) {

        double s = 0.0;
        for(int k = 0; k < rc; ++k) {
          int ri = Ask[i].frows[k];
          double RESTRICT_PTR rf = RowSpace_F[ri];
          s += RowMeans_F[ri];
          for(int j = 0; j < FACT_CNT; ++j)
            s += avgcolfacts[j]*rf[j];
        }
        val += avgcolmean + s/rc;

      }
    } else if(rc <= 0) {

#ifdef OS_PRED_BY_YEARS
      int c = 0;
      double s = 0.0;
      for(unsigned int di = 0; di < Dat.size(); ++di)
        if(Dat[di].year == Ask[i].year) {
          s += Dat[di].fpnt.targ;
          c++;
        }
      if(c > 0)
        val = 0.5*val+0.5*(val+s/c);
#endif

    } else {

      double RESTRICT_PTR cf = ColSpace_F[ci];
      double s = 0.0;
      for(int k = 0; k < rc; ++k) {
        int ri = Ask[i].frows[k];
        double RESTRICT_PTR rf = RowSpace_F[ri];
        s += RowMeans_F[ri];
        for(int j = 0; j < FACT_CNT; ++j)
          s += rf[j]*cf[j];
      }
      val += ColMeans_F[ci] + s/rc;

    }

    Ask[i].yield_f = val;
  }
}

void Predict_F() {

  MakeFactPoints();

  vector<TDatRec*> pnts(Dat.size());
  int n = 0;
  for(unsigned int i = 0; i < Dat.size(); ++i)
//    if(IsPredVar(Dat[i].var))
      pnts[n++] = &Dat[i];
  pnts.resize(n);
  sort(pnts.begin(), pnts.end(), CompareDatRecsByColRows_F);
  n = 0;
  for(unsigned int i = 1; i < pnts.size(); ++i)
    if((pnts[n]->fpnt.row != pnts[i]->fpnt.row) || (pnts[n]->fpnt.col != pnts[i]->fpnt.col))
      pnts[++n] = pnts[i];
  pnts.resize(++n);

  InitMeans_F(pnts);
  InitFacts_F();

#ifdef PRINT_PROGRESS
  double besterr = 1.0e20;
  double bestoserr = 1.0e20;
  double bestiserr = 1.0e20;
  int besterrpass = -1;
  int bestoserrpass = -1;
  int bestiserrpass = -1;
  const static char *BestFlags[3] = {" ","=","*"};
#ifdef OVERPASS_BREAK
  const int OverPasses = 20;
#endif
#endif

  for(int pass = 1; pass <= FACT_TRAIN_PASSES; ++pass) {

    n = (int)pnts.size();
    while(--n > 0)
      swap(pnts[n], pnts[RGen.GetInt(n+1)]);

#ifdef PRINT_PROGRESS
    double trainerr = 0.0;
#endif

    for(unsigned int i = 0; i < pnts.size(); ++i) {

      int ri = pnts[i]->fpnt.row;
      int ci = pnts[i]->fpnt.col;
      double RESTRICT_PTR rf = RowSpace_F[ri];
      double RESTRICT_PTR cf = ColSpace_F[ci];

      double e = pnts[i]->fpnt.targ - RowMeans_F[ri] - ColMeans_F[ci];
      for(int j = 0; j < FACT_CNT; ++j)
        e -= rf[j]*cf[j];

#ifdef PRINT_PROGRESS
      trainerr += e*e;
#endif

      e *= FACT_LEARN_RATE;
      for(int j = 0; j < FACT_CNT; ++j) {
        double v = cf[j];
        cf[j] = FACT_REG_RATIO*v + e*rf[j];
        rf[j] = FACT_REG_RATIO*rf[j] + e*v;
      }

      e *= FACT_MLEARN_RATE/FACT_LEARN_RATE;
      ColMeans_F[ci] = FACT_MREG_RATIO*ColMeans_F[ci] + e;
      RowMeans_F[ri] = FACT_MREG_RATIO*RowMeans_F[ri] + e;

    }

#ifdef PRINT_PROGRESS
    if(Ask.size() > 0) {
//    if((Ask.size() > 0) && ((pass-1) % 100 == 0)) {
      trainerr = sqrt(trainerr/(int)pnts.size());
      CountPreds_F();
      double oserr = 0.0;
      double iserr = 0.0;
      int oscnt = 0;
      int iscnt = 0;
      for(unsigned int k = 0; k < Ask.size(); ++k) {
        double v = min(CAP_VALUE, fabs(Ask[k].targ-Ask[k].yield_f));
        v *= v;
        if((Ask[k].fcol < 0) || (Ask[k].frows.size() == 0)) {
          oserr += v;
          oscnt++;
        } else {
          iserr += v;
          iscnt++;
        }
      }
      double askerr = sqrt((oserr+iserr)/max(1, oscnt+iscnt));
      oserr = sqrt(oserr/max(1, oscnt));
      iserr = sqrt(iserr/max(1, iscnt));
      fprintf(stderr, "pass %d, train err %g ask sup %d (os %d is %d)"
                      " ask err %g%s (os %g%s is %g%s)\n", 
        pass, trainerr, oscnt+iscnt, oscnt, iscnt, 
        askerr, BestFlags[besterr > askerr ? 2 : (besterr == askerr ? 1 : 0)],
        oserr, BestFlags[bestoserr > oserr ? 2 : (bestoserr == oserr ? 1 : 0)],
        iserr, BestFlags[bestiserr > iserr ? 2 : (bestiserr == iserr ? 1 : 0)]);
      fflush(stderr);
      if(besterr > askerr) {
        besterr = askerr;
        besterrpass = pass;
      }
      if(bestoserr > oserr) {
        bestoserr = oserr;
        bestoserrpass = pass;
      }
      if(bestiserr > iserr) {
        bestiserr = iserr;
        bestiserrpass = pass;
      }
#ifdef OVERPASS_BREAK
      if((pass-besterrpass >= OverPasses) && (pass-bestoserrpass >= OverPasses) &&
         (pass-bestiserrpass >= OverPasses)) {
        fprintf(stderr, "overpasses limit (%d) reached\n", OverPasses);
        fflush(stderr);
        break;
      }
#endif
    }
#endif
  }

  CountPreds_F();
#ifdef PRINT_PROGRESS
  if(Ask.size() > 0) {
    fprintf(stderr, "bests: ask err %g (pass %d), os err %g (pass %d), is err %g (pass %d) \n", 
      besterr, besterrpass, bestoserr, bestoserrpass, bestiserr, bestiserrpass);
    fflush(stderr);
  }
#endif
}

NS_END

struct YieldPredictor {
  vector<double> predictYield(vector<string> &trainingData, vector<string> &droughtMonitor, 
                              vector<string> &droughtNOAA, vector<string> &locations, 
                              vector<string> &varieties, vector<string> &queries) {

    NS_REF DecodeVar(varieties);
    NS_REF DecodeMon(droughtMonitor);
    NS_REF DecodeNoa(droughtNOAA);
    NS_REF DecodeLoc(locations);
    NS_REF DecodeDat(trainingData);
    NS_REF DecodeAsk(queries);

    NS_REF CleanupData();
    NS_REF LinkData();

    NS_REF Predict_F();

    vector<double> yields(queries.size());
    for(unsigned int i = 0; i < NS_REF Ask.size(); ++i)
      yields[NS_REF Ask[i].row] = max(MIN_YIELD, min(MAX_YIELD, 
        NS_REF IsDoubleFinite(NS_REF Ask[i].yield_f) ? 
          NS_REF Ask[i].yield_f : NS_REF GlobalMeanYield ));
    return yields;
  }
};