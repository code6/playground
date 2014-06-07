#include <algorithm>
#include <cassert>
#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<int> Ids;
typedef std::vector<std::string> Strings;
typedef std::set<int> Id_Set;

// ---------------------------------------------------------
// HELPERS

#define FOR_EACH(T,I,C) \
  for (T I=C.begin(), I ## _end=C.end(); I!=I ## _end; ++I)

#define LOG(M) \
  std::cerr << "[XXX] " << M << std::endl

#define FATAL_ERROR(M) \
{ LOG(M); std::terminate(); }

// Read the stream `in' as a sequence of lines.
void read(Strings& strings, std::istream& in) {
  std::string s;
  while (true) {
    std::getline(in, s);
    if (in.eof())
      return;
    strings.push_back(s);
  }
}

void read(Strings& s, std::string const& file) {
  LOG("Reading from: " << file);
  std::ifstream in(file.c_str());
  read(s, in);
}

// Represents any value of `T' or `NULL'.
template <typename T>
struct Lift {
  bool available;
  T value;
  Lift() : available(false), value(T()) {}
};

template <typename T>
std::istream& operator>>(std::istream& in, Lift<T>& lifted) {
  static std::istringstream in2;
  std::string s;
  in >> s;
  lifted.available = (s != "NULL");
  if (lifted.available) {
    in2.str(s);
    in2.clear();
    in2 >> lifted.value;
  }
  return in;
}

// ---------------------------------------------------------
// DATA STRUCTURES

struct Sample {
  int experiment_id;
  int year;
  int location_id;
  int repetition;
  enum Type {
    CONVENTIONAL,
    RR,
    RR2Y
  };
  Lift<Type> type;
  int variety_id;
  Lift<double> yield;
  Lift<double> maturity;
  Lift<double> relative_maturity;
  bool is_check;
  bool is_elite;
};

typedef std::deque<Sample> Samples;
typedef Samples::iterator I;

struct Raw_Location {
  int id;
  int row;
  int column;
  enum Sub_Row {
    EARLY,
    MID,
    LATE
  } sub_row;
};

typedef std::deque<Raw_Location> Raw_Locations;

struct Location {
  double row;
  double column;
  Location() : row(0), column(0) {}
};

typedef std::map<int, Location> Locations;

// ---------------------------------------------------------
// I/O

// Drop any space and replace commas with spaces.
void normalize_csv(std::string& out, std::string const& in) {
  out.clear();
  out.reserve(in.size());
  FOR_EACH(std::string::const_iterator, i, in) {
    if (std::isspace(*i))
      /* do nothing */;
    else if (*i == ',')
      out.push_back(' ');
    else
      out.push_back(*i);
  }
}

std::istream& operator>>(std::istream& in, Sample::Type& type) {
  std::string s;
  in >> s;
  if (s == "conv")
    type = Sample::CONVENTIONAL;
  else if (s == "RR" || s == "RR1")
    type = Sample::RR;
  else if (s == "RR2Y")
    type = Sample::RR2Y;
  else
    FATAL_ERROR("Unexpected Variety Type: " << s);
  return in;
}

std::istream& operator>>(std::istream& in, Sample& s) {
  in >> s.experiment_id
     >> s.year
     >> s.location_id
     >> s.repetition
     >> s.type
     >> s.variety_id
     >> s.yield
     >> s.maturity
     >> s.relative_maturity
     >> s.is_check
     >> s.is_elite;
  return in;
}

std::istream& operator>>(std::istream& in, Raw_Location::Sub_Row& r) {
  std::string s;
  in >> s;
  if (s == "Early")
    r = Raw_Location::EARLY;
  else if (s == "Mid")
    r = Raw_Location::MID;
  else if (s == "Late")
    r = Raw_Location::LATE;
  else
    FATAL_ERROR("Unknown Sub_Row constant: " << s);
  return in;
}

std::istream& operator>>(std::istream& in, Raw_Location& l) {
  in >> l.id
     >> l.row
     >> l.sub_row
     >> l.column;
  return in;
}

template <typename T>
void parse(T& t, Strings const& raw_data) {
  std::istringstream in;
  std::string s;
  FOR_EACH(Strings::const_iterator, i, raw_data) {
    t.push_back(typename T::value_type());
    normalize_csv(s, *i);
    in.str(s);
    in.clear();
    in >> t.back();
  }
}

struct Raw_Location_Less {
  bool operator()(Raw_Location const& a, Raw_Location const& b) const
  { return a.id < b.id; }
};

void make_locations(Locations& ls, Raw_Locations& rs) {
  // Sort locations by their id.
  std::sort(rs.begin(), rs.end(), Raw_Location_Less());
  // The same location (id) may occur several times with different
  // parameters (row, column, sub_row). For simplicity I compute a
  // mean of these occurrences.
  for (Raw_Locations::iterator i(rs.begin()), e(rs.end()); i!=e;) {
    int id = i->id;
    int count = 0;
    Location& l = ls[id];
    for (; i!=e && i->id == id; ++i) {
      // I consider the `sub_row' as the fractional part of the `row'.
      l.row += i->row + i->sub_row/2.0;
      l.column += i->column;
      ++ count;
    }
    l.row /= count;
    l.column /= count;
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& o, Lift<T> const& l) {
  o        << l.available
    << ' ' << l.value;
  return o;
}

std::ostream& operator<<(std::ostream& o, Lift<Sample::Type> const& t) {
  o        << (t.available && t.value == Sample::CONVENTIONAL)
    << ' ' << (t.available && t.value == Sample::RR)
    << ' ' << (t.available && t.value == Sample::RR2Y);
  return o;
}

std::ostream& operator<<(std::ostream& o, Location const& l) {
  o        << l.row
    << ' ' << l.column;
  return o;
}

std::ostream& operator<<(std::ostream& o, Sample const& s) {
  o        << s.type
    << ' ' << s.yield
    << ' ' << s.maturity
    << ' ' << s.relative_maturity;
  return o;
}

// ---------------------------------------------------------
// UTILS

bool is_valid_solution(Ids const& ids, Samples const& samples) {
  Id_Set id_set;
  FOR_EACH(Ids::const_iterator, i, ids) {
    if (!id_set.insert(*i).second) {
      LOG("Repeated id " << *i);
      return false;
    }
  }
  FOR_EACH(Samples::const_iterator, i, samples) {
    if (id_set.count(i->variety_id) == 0) {
      LOG("Missing id " << i->variety_id);
      return false;
    }
  }
  return true;
}

void get_elites(Id_Set& elites, Samples const& samples) {
  FOR_EACH(Samples::const_iterator, i, samples)
    if (i->is_elite)
      elites.insert(i->variety_id);
}

void dump_solution(Ids const& ids, Id_Set const& elites) {
  FOR_EACH(Ids::const_iterator, i, ids)
    std::cerr << (elites.count(*i) ? 'o' : '.');
  std::cerr << std::endl;
}

double score(Ids const& ids, Samples const& samples) {
  double res = 0;
  int total = 0;
  int correct = 0;
  Id_Set elites;
  get_elites(elites, samples);
  LOG("Total varieties: " << ids.size());
  LOG("Total elite varieties: " << elites.size());
  LOG("Elite/Total ratio: " << (1.0*elites.size())/ids.size());
  FOR_EACH(Ids::const_iterator, i, ids) {
    ++ total;
    if (elites.count(*i)) {
      ++ correct;
      res += (1000000.0 / elites.size()) * (1.0 * correct / total);
    }
  }
  dump_solution(ids, elites);
  return res;
}

// ---------------------------------------------------------
// THE ALGORITHM

// See query4.sql
double prob_elite_known_yield_avg_rank_arr[] = {
  0.13179448994787788533
  ,0.07759197324414715719
  ,0.06034482758620689655
  ,0.04075605434140578854
  ,0.03177257525083612040
  ,0.02448313384113166485
  ,0.01685097419694576093
  ,0.01296680497925311203
  ,0.00618556701030927835
  ,0.01080802882141019043
  ,0.00801603206412825651
  ,0.00791687283523008412
  ,0.00347567030784508441
  ,0.00542406311637080868
  ,0.00389863547758284600
  ,0.00535019455252918288
  ,0.00577478344562078922
  ,0.00194741966893865628
  ,0.00144717800289435601
  ,0.00144648023143683703
  ,0.00237868696479543292
  ,0.00237416904083570750
  ,0.00188412623645784268
  ,0.00141709966934341049
  ,0.00046794571829667759
  ,0.00047214353163361662
  ,0.00235515779557230334
  ,0.00094428706326723324
  ,0.00141376060320452403
  ,0.00046860356138706654
  ,0.00093240093240093240
  ,0.00139664804469273743
  ,0.00093196644920782852
  ,0.00140515222482435597
  ,0.00093984962406015038
  ,0.00189843379212149976
  ,0.00000000000000000000
  ,0.00000000000000000000
  ,0.00000000000000000000
  ,0.00000000000000000000
};

double prob_elite_known_yield_avg_rank(int rank) {
  assert(rank >= 0);
  if (rank <= 38)
    return prob_elite_known_yield_avg_rank_arr[rank];
  else
    return 0;
}

// See query6.sql
double prob_elite_known_ym_ratio_avg_rank_arr[] = {
  0.12690707350901525659
  ,0.07817385866166353971
  ,0.05836341756919374248
  ,0.03822372119168071951
  ,0.03266888150609080842
  ,0.01781857451403887689
  ,0.01339764201500535906
  ,0.01507276507276507277
  ,0.00940438871473354232
  ,0.00858152448258455326
  ,0.00955253896430367019
  ,0.00395647873392680514
  ,0.00593765462642256309
  ,0.00638506876227897839
  ,0.00447093889716840537
  ,0.00637254901960784314
  ,0.00341796875000000000
  ,0.00146842878120411160
  ,0.00145772594752186589
  ,0.00335570469798657718
  ,0.00047641734159123392
  ,0.00194647201946472019
  ,0.00237981913374583532
  ,0.00093984962406015038
  ,0.00047080979284369115
  ,0.00093896713615023474
  ,0.00047348484848484848
  ,0.00140646976090014065
  ,0.00188501413760603205
  ,0.00047846889952153110
  ,0.00282087447108603667
  ,0.00047036688617121355
  ,0.00000000000000000000
  ,0.00093808630393996248
  ,0.00094117647058823529
  ,0.00142112742775935576
  ,0.00000000000000000000
  ,0.00151285930408472012
  ,0.00156250000000000000
  ,0.00152671755725190840
};

double prob_elite_known_ym_ratio_avg_rank(int rank) {
  assert(rank >= 0);
  if (rank <= 39)
    return prob_elite_known_ym_ratio_avg_rank_arr[rank];
  else
    return 0;
}

struct Variety {
  Variety(Sample const& s)
  : experiment_id(s.experiment_id)
  , year(s.year)
  , variety_id(s.variety_id)
  , type(s.type)
  , yield_count(0)
  , yield_avg(0)
  , maturity_count(0)
  , maturity_avg(0)
  , is_check(s.is_check)
  , is_elite(s.is_elite)
  {}

  int experiment_id;
  int year;
  int variety_id;
  Lift<Sample::Type> type;
  int yield_count;
  double yield_avg;
  int maturity_count;
  double maturity_avg;
  int yield_avg_rank;
  int ym_ratio_rank;
  bool is_check;
  bool is_elite;
};

typedef std::deque<Variety> Varieties;

double prob_elite_known_ym_ratio(Variety const& v) {
  if (v.maturity_count)
    return prob_elite_known_ym_ratio_avg_rank(v.ym_ratio_rank);
  else
    // See query9.sql for the case when all maturity are null.
    return 0.00132998374464312103;
}

// See query5.sql
double prob_elite_known_type(Lift<Sample::Type> const& type) {
  if (type.available) {
    switch (type.value) {
      case Sample::CONVENTIONAL:
        return 0.00698593177876276739;
      case Sample::RR:
        return 0.01198875588733548039;
    }
  }
  return 0;
}

std::ostream& operator<<(std::ostream& o, Variety const& v) {
  o         << v.experiment_id
    << '\t' << v.is_elite
    << '\t' << v.is_check
    << '\t' << v.yield_avg_rank
    << '\t' << v.yield_avg
    << '\t' << v.ym_ratio_rank
    << '\t' << v.yield_avg / v.maturity_avg
    << '\t' << v.maturity_avg;
  return o;
}

typedef std::pair<int /* location_id */, int /* repetition */> Trial;
typedef std::set<Trial> Trials;

struct Experiment {
  Experiment()
  : check_count(0), non_check_count(0) {}
  int check_count;
  int non_check_count;
  Trials trials;
};

typedef std::map<int, Experiment> Experiments;

std::ostream& operator<<(std::ostream& o, Experiments::value_type const& e) {
  o         << e.first
    << '\t' << e.second.check_count
    << '\t' << e.second.check_count + e.second.non_check_count
    << '\t' << e.second.trials.size();
  return o;
}

std::ostream& operator<<(std::ostream& o, Experiments const& e) {
  FOR_EACH(Experiments::const_iterator, i, e)
    o << *i << '\n';
  return o;
}

void make_experiments(Experiments& es, Varieties const& vs,
    Samples const& ss) {
  FOR_EACH(Varieties::const_iterator, i, vs) {
    Experiment& e = es[i->experiment_id];
    if (i->is_check)
      ++ e.check_count;
    else
      ++ e.non_check_count;
  }
  FOR_EACH(Samples::const_iterator, i, ss)
    es[i->experiment_id].trials.insert(Trial(i->location_id, i->repetition));
#if 0
  std::cerr << es << std::endl;
  exit(0);
#endif
}

typedef std::map<int, double> Probs;

Probs prob_elite_known_check_count_arr;
Probs prob_elite_known_total_count_arr;
Probs prob_elite_known_trial_count_arr;
Probs prob_elite_known_year_arr;

void init() {
  {
    // See query7.sql (A)
    Probs& p(prob_elite_known_check_count_arr);
    p[2] = 0.00762527233115468410;
    p[3] = 0.01451666116793137578;
    p[4] = 0.00790236005793644032;
    p[5] = 0.01807847702526878039;
    p[6] = 0.00934579439252336449;
    p[7] = 0.02647975077881619938;
    p[8] = 0.01991150442477876106;
    p[9] = 0.02564102564102564103;
    p[10] = 0.03846153846153846154;
    p[11] = 0.03428571428571428571;
    p[12] = 0.02027027027027027027;
    p[15] = 0.01587301587301587302;
    p[17] = 0.05263157894736842105;
  }
  {
    // See query7.sql (B)
    Probs& p(prob_elite_known_total_count_arr);
    p[36] = 0.01563040602421898850;
    p[40] = 0.00082365861311578287;
  }
  {
    // See query8.sql
    Probs& p(prob_elite_known_trial_count_arr);
    p[1] = 0.00507042253521126761;
    p[2] = 0.00278846153846153846;
    p[3] = 0.00280301565822540112;
    p[4] = 0.00995081779709481871;
    p[5] = 0.01231802911534154535;
    p[6] = 0.01441753171856978085;
    p[7] = 0.01658240647118301314;
    p[8] = 0.01566997121842021106;
    p[9] = 0.02010695187165775401;
    p[10] = 0.01356370095268851930;
    p[11] = 0.01346389228886168911;
    p[12] = 0.01454696591853699086;
    p[13] = 0.04687500000000000000;
    p[14] = 0.01250000000000000000;
    p[15] = 0.06250000000000000000;
    p[16] = 0.03092783505154639175;
  }
  {
    // See query2.sql
    Probs& p(prob_elite_known_year_arr);
    p[2000] = 0.00037216226274655750;
    p[2001] = 0.00628084342754598475;
    p[2002] = 0.01677689949991934183;
    p[2003] = 0.01242577523641961733;
    p[2004] = 0.00708633518365418684;
    p[2005] = 0.00813953488372093023;
    p[2006] = 0.01869158878504672897;
    p[2007] = 0.01310350206692145698;
    p[2008] = 0.00849560183444853770;
  }
};

#define TESTING 1

double prob_elite_known_year(int year) {
  Probs::iterator i(prob_elite_known_year_arr.find(year));
  if (i == prob_elite_known_year_arr.end()) {
#if TESTING
    //FATAL_ERROR("Year never seen before");
#endif
    return 0.01015247146449148246;
  }
  else
    return i->second;
}

double prob_elite_known_experiment(Experiments const& es,
  int experiment_id) {
  assert(es.count(experiment_id));
  Experiment const& e(es.find(experiment_id)->second);
  int total = e.check_count + e.non_check_count;
#if TESTING
  //assert(prob_elite_known_total_count_arr.count(total));
  //assert(prob_elite_known_trial_count_arr.count(e.trials.size()));
#endif
  return prob_elite_known_total_count_arr[total]
    * prob_elite_known_trial_count_arr[e.trials.size()];
    //* prob_elite_known_check_count_arr[e.check_count];
}

void iota(Ids& ids) {
  int unsigned c = 0;
  FOR_EACH(Ids::iterator, i, ids)
    *i = c++;
}

struct By_Variety {
  bool operator()(Sample const& x, Sample const& y) const
  { return x.variety_id < y.variety_id; }
};

void compute_averages(Varieties& vs, Samples& s) {
  vs.clear();
  if (s.empty())
    return;
  std::sort(s.begin(), s.end(), By_Variety());
  vs.push_back(Variety(s.front()));
  FOR_EACH(Samples::const_iterator, i, s) {
    if (i->variety_id != vs.back().variety_id)
      vs.push_back(Variety(*i));
    Variety& v = vs.back();
    if (i->yield.available) {
      v.yield_avg += i->yield.value;
      ++ v.yield_count;
    }
    if (i->maturity.available) {
      v.maturity_avg += i->maturity.value;
      ++ v.maturity_count;
    }
  }
  FOR_EACH(Varieties::iterator, i, vs) {
    i->yield_avg /= i->yield_count;
    i->maturity_avg /= i->maturity_count;
  }
}

template <typename By_Next>
struct By_Experiment {
  By_Experiment(Varieties const& v_) : by_next(v_) {}

  bool operator()(int x, int y) const {
    return by_next.v[x].experiment_id < by_next.v[y].experiment_id
      || (by_next.v[x].experiment_id == by_next.v[y].experiment_id
          && by_next(x, y));
  }

  By_Next by_next;
};

struct By_Yield_Avg {
  By_Yield_Avg(Varieties const& v_) : v(v_) {}

  bool operator()(int x, int y) const
  { return v[x].yield_avg > v[y].yield_avg; }

  Varieties const& v;

  static int& get(Variety& v)
  { return v.yield_avg_rank; }
};

struct By_Ym_Ratio {
  By_Ym_Ratio(Varieties const& v_) : v(v_) {}

  bool operator()(int x, int y) const {
    return v[x].yield_avg * v[y].maturity_avg
      > v[y].yield_avg * v[x].maturity_avg;
  }

  Varieties const& v;

  static int& get(Variety& v)
  { return v.ym_ratio_rank; }
};

template <typename Field>
void compute_rank(Varieties& v) {
  Ids ids(v.size());
  iota(ids);
  std::sort(ids.begin(), ids.end(), By_Experiment<Field>(v));
  int experiment_id = v[ids[0]].experiment_id;
  int unsigned rank = 0;
  FOR_EACH(Ids::iterator, i, ids) {
    if (v[*i].experiment_id != experiment_id) {
      rank = 0;
      experiment_id = v[*i].experiment_id;
    }
    Field::get(v[*i]) = rank++;
  }
}

std::ostream& operator<<(std::ostream& o, Varieties const& v) {
  Ids ids(v.size());
  iota(ids);
  std::sort(ids.begin(), ids.end(), By_Experiment<By_Yield_Avg>(v));
  FOR_EACH(Ids::iterator, i, ids)
    o << v[*i] << "\n";
  return o;
}

void make_varieties(Varieties& v, Samples& s) {
  compute_averages(v, s);
  compute_rank<By_Yield_Avg>(v);
  compute_rank<By_Ym_Ratio>(v);
#if 0
  std::cerr << v << std::endl;
#endif
}

void prepare_data(Samples& s, Locations& l,
    Strings const& samples_text, Strings const& locations_text) {
  LOG("Parsing samples.");
  parse(s, samples_text);
  LOG("Parsing locations.");
  Raw_Locations raw_locations;
  parse(raw_locations, locations_text);
  make_locations(l, raw_locations);
}

struct By_Elites {
  By_Elites(Varieties const& v_, Experiments const& e_)
  : v(v_), e(e_) {}

  double prob_elite(Variety const& v) const {
    if (v.is_check)
      return 0;
    return prob_elite_known_year(v.year)
      * prob_elite_known_yield_avg_rank(v.yield_avg_rank)
      * prob_elite_known_ym_ratio(v)
      * prob_elite_known_experiment(e, v.experiment_id)
      * prob_elite_known_type(v.type)
      ;
  }

  bool operator()(int x, int y) const {
    return prob_elite(v[x]) > prob_elite(v[y]);
  }

  Varieties const& v;
  Experiments const& e;
};

void make_solution(Ids& ids, Samples& samples,
    Locations const& /* locations */) {
  LOG("Collecting varieties statistics.");
  Varieties varieties;
  make_varieties(varieties, samples);
  Experiments experiments;
  make_experiments(experiments, varieties, samples);
  init();
  LOG("Computing elite varieties.");
  ids.resize(varieties.size());
  iota(ids);
  std::sort(ids.begin(), ids.end(),
      By_Elites(varieties, experiments));
  for (int unsigned i=0, e=ids.size(); i!=e; ++i)
    ids[i] = varieties[ids[i]].variety_id;
}

struct EliteClassifier {
  Ids classify(Strings const& samples_text,
      Strings const& locations_text) {
    Samples samples;
    Locations locations;
    prepare_data(samples, locations, samples_text,
        locations_text);
    Ids res;
    make_solution(res, samples, locations);
#if 1
    assert(is_valid_solution(res, samples));
    LOG("score: " << score(res, samples)/10000.0 << " %");
#endif
    return res;
  }
};

// ---------------------------------------------------------
