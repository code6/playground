//#define LOCAL

// TODO:
// 1. add bound check, failed
// 2. add month to year, failed
// 3. add drought data
// 4. iterate the average power

#ifdef LOCAL

#define RUN_TEST
#define ADJUST_AVG
#define GEN_PARAM
//#define GEN_PARAM_FOR_LOCCD_YEAR
//#define GEN_PARAM_FOR_VARIETY_YEAR

#endif

//#define EUCLIDEAN_DISTANCE
//#define NORMALIZE
//#define RATED_SUM
#define TRIM_RECORD
//#define STRONG_GUESS
using namespace std;
#include <algorithm>
#include <cmath>
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <map>
#include <vector>

//By chyx111
#define forE(elem,v) \
    for(__typeof__(v.begin()) _it = v.begin(); _it != v.end(); ++_it)\
for(int _once=1, _done=0; _once; (!_done) ? (_it=v.end(), --_it) : _it )\
for(__typeof__(*_it) & elem = * _it; _once && !(_once=0); _done=1) 
#define ALL(a) (a).begin(),(a).end()
template<class T> void inline checkMax(T& a, T b){if(a < b) a = b;};
#define DBG(a) cerr << #a << ": " << (a) << endl
typedef long long ll;
template<class T> void inline checkMin(T& a, T b){if(a > b) a = b;};
template<class T> void inline checkNan(T& a, T b){if(isnan(a)) a = b;};
#define Rep(i,n) for(int n_ = (n), i = 0; i< n_; ++i)
#define forI(it,v) for(__typeof__((v).begin()) it = (v).begin(); it != (v).end(); ++it)
#define SZ(a) ((int)(a).size())
template<class S, class T> 
ostream& operator<<(ostream& os, pair<S, T> p){
    return os << "(" << p.first << ", " << p.second << ")";
};
template<class T> 
ostream& operator<<(ostream& os, vector<T> v){
    Rep(i, v.size()){
        if(i){
            os << ' ';
        }
        os << v[i];
    }
    return os;
};
double inf = 1e20;
double eps = 1e-20;
double RATE = 0.01;

double get_midpiont(double a, double b, double xa, double xb)
{
    if(fabs(xa + xb) < eps){
        return (a + b) / 2;
    }
    return (a * xa + b * xb) / (xa + xb);
}
double double_equals(double a, double b)
{
    if(fabs(a - b) < eps){
        return true;
    }
    return fabs(a - b) / (max(fabs(a), fabs(b) + eps)) < eps;
}

set<int> frequent_vid;

double encode_yield(double yield)
{
    return powf(yield, 1 / 0.5);
    //return exp(yield / 50.);
}
double decode_yield(double yield)
{
    //return log(yield) * 50.;
    return powf(yield, 0.5);
}
int trim_year(int fullyear){
    return fullyear / 100;
}


struct Metric{
    int id;
    void set_id(int _id)
    {
        id = _id;
    }
    int get_id()
    {
        return id;
    }
    virtual double get_dist(int eid, Metric* other) = 0;
};

int get_combine_year_by_year_month(int year, int month)
{
    return year * 100 + month;
}

struct SimpleAccumulator{
    double sum;
    double sum2;
    int sz;

    double sum_exp;
    double den;
    double rate;

    double minv;
    double maxv;

    SimpleAccumulator()
        :sum(0), sum2(0), sz(0),
        sum_exp(0), den(0), rate(1)
    {
        minv = 1e10;
        maxv = -1e10;
    }
    double get_avg()
    {
        if(sz == 0){
            return 0;
        }
        return sum / sz;
    }
    double get_variance()
    {
        if(sz == 0){
            return 0;
        }
        return sqrt(sum2 / sz) - get_avg();
    }
    double get_rmse()
    {
        return sqrt(sum2 / sz);
    }
    void add(double v)
    {
        sum += v;
        sum2 += v * v;
        sz++;
        checkMin(minv, v);
        checkMax(maxv, v);

#ifdef RATED_SUM
        sum_exp += v * rate;
        den += rate;
        rate *= 0.9;
#endif
    }
    double denormalize(double ret, double cand = 0)
    {
        double avg = get_avg();

        double v = avg * ret;
        if(isnan(v) || sz == 0){
            v = cand;
        }
        return v;
    }
    void add_with_quantity(double v, int c)
    {
        sum += v * c;
        sum2 += v * v * c;
        sz += c;
    }
    double get_min()
    {
        return minv;
    }
    double get_max()
    {
        return maxv;
    }

};

struct Accumulator{ // {{{
    struct Value{
        double value;
        Metric* m;
        double d;
        int record_id;
        bool operator<(Value const& other)const{
            if(isnan(d) || isnan(other.d)){
                return false;
            }
            return d + eps < other.d;
        }
    };
    private:
    static Value work[100000];
    int sz;
    double sum, sum2;
    vector<Metric*> items;
    vector<double> values;
    vector<int> item_eid;
    vector<int> record_ids;

    map<int, double> sum_by_eid;
    map<int, double> sum2_by_eid;
    map<int, int> sz_by_eid;
    double prev_avg;
    int prev_eid;
    static int const INVALID_EID = -334;

    public:
    Accumulator(int n = 0)
        :sz(0), sum(0), sum2(0), prev_eid(INVALID_EID)
    {
    }
    double get_sum(int eid)
    {
#ifdef ADJUST_AVG
        return sum - sum_by_eid[eid];
#else
        return sum;
#endif
    }
    double get_sum2(int eid)
    {
#ifdef ADJUST_AVG
        return sum2 - sum2_by_eid[eid];
#else
        return sum2;
#endif
    }
    int get_size(int eid)
    {
#ifdef ADJUST_AVG
        return sz - sz_by_eid[eid];
#else
        return sz;
#endif
    }

    double get_avg(int eid, double cand = 0)
    {
        if(prev_eid == eid){
            return prev_avg;
        }
        prev_eid = eid;
        if(get_size(eid) == 0){
            prev_avg = cand;
        }else{
            prev_avg = get_sum(eid) / get_size(eid);
        }
        if(isnan(prev_avg) || fabs(prev_avg) > 1e5){
            prev_avg = cand;
        }
        return prev_avg;
    }
    double get_variance(int eid)
    {
        if(get_size(eid) == 0){
            return 0;
        }
        return sqrt(get_sum2(eid) / get_size(eid)) - get_avg(eid);
    }
    vector<pair<double, int> > get_all(int eid)
    {
        Rep(i, sz){
            work[i].value = values[i];
            work[i].m = items[i];
        }
        int curr_sz = sz;
#ifdef ADJUST_AVG
        for(int i = sz - 1; i >= 0; --i){
            if(item_eid[i] == eid){
                swap(work[curr_sz - 1], work[i]);
                --curr_sz;
            }
        }
#endif
        vector<pair<double, int> > nearest_cand;
        Rep(i, curr_sz){
            nearest_cand.push_back(make_pair(work[i].value, work[i].m->get_id()));
        }
        return nearest_cand;
    }
    vector<pair<double, int> > get_all_with_record_id(int eid)
    {
        Rep(i, sz){
            work[i].value = values[i];
            work[i].m = items[i];
            work[i].record_id = record_ids[i];
        }
        int curr_sz = sz;
#ifdef ADJUST_AVG
        for(int i = sz - 1; i >= 0; --i){
            if(item_eid[i] == eid){
                swap(work[curr_sz - 1], work[i]);
                --curr_sz;
            }
        }
#endif
        vector<pair<double, int> > nearest_cand;
        Rep(i, curr_sz){
            nearest_cand.push_back(make_pair(work[i].value, work[i].record_id));
        }
        return nearest_cand;
    }


    vector<pair<double, int> > get_knn(int eid, Metric* curr, int bnd)
    {
        Rep(i, sz){
            work[i].value = values[i];
            work[i].m = items[i];
            work[i].d = curr->get_dist(eid, items[i]);
        }
        int curr_sz = sz;
#ifdef ADJUST_AVG
        for(int i = sz - 1; i >= 0; --i){
            if(item_eid[i] == eid){
                swap(work[curr_sz - 1], work[i]);
                --curr_sz;
            }
        }
#endif
        checkMin(bnd, curr_sz);
        sort(work, work + curr_sz);
        while(bnd > 0 && bnd < curr_sz && double_equals(work[bnd - 1].d, work[bnd].d)){
            bnd++;
        }
        vector<pair<double, int> > nearest_cand;
        Rep(i, bnd){
            nearest_cand.push_back(make_pair(work[i].value, work[i].m->get_id()));
        }
        return nearest_cand;
        //SimpleAccumulator temp_accumulator;
        //Rep(i, bnd){
        //    temp_accumulator.add(work[i].value);
        //}
        //return temp_accumulator;
    }

    double get_normlize(int eid, double v)
    {
        double avg = get_avg(eid);
#define RATE 0.01
#ifdef NORMALIZE
        double var = get_variance(eid);
        checkMax(var, avg * RATE);
        double ret = (v - avg) / var;
#else
        double ret = v / avg;
#endif
        if(isnan(ret)){
            ret = 0;
        }
        return ret;
    }

    double denormalize(int eid, double ret, double cand)
    {
        double avg = get_avg(eid);
#ifdef NORMALIZE
        double var = get_variance(eid);
        checkMax(var, avg * RATE);
        double v = avg + var * ret;
#else
        double v = ret * avg;
#endif
        if(get_size(eid) == 0 || isnan(v)){
            return cand;
        }
        return v;
    }

    // 124608
    static int const MIN_MAX_BOUND = 50; // 124347
    double check_min_max(int eid, double given)
    {
        if(get_size(eid) < MIN_MAX_BOUND){
            return given;
        }
        double minv = 1000;
        double maxv = -1000;
        Rep(i, sz){
            if(item_eid[i] == eid){
                continue;
            }
            checkMax(maxv, values[i]);
            checkMin(minv, values[i]);
        }
        checkMin(given, maxv);
        checkMax(given, minv);
        return given;
    }

    void add(int record_id, int eid, double v, Metric* item)
    {
        sum += v;
        sum2 += v * v;
        sz++;
        items.push_back(item);
        item_eid.push_back(eid);
        values.push_back(v);
        record_ids.push_back(record_id);
        prev_eid = INVALID_EID;
#ifdef ADJUST_AVG
        sum_by_eid[eid] += v;
        sz_by_eid[eid]++;
        sum2_by_eid[eid] += v * v;
#endif
    }

    void add_with_quantity(int eid, double v, int c, Metric* item)
    {
        sum += v * c;
        sum2 += v * v * c;
        sz += c;
        items.push_back(item);
        item_eid.push_back(eid);
        values.push_back(v);
        prev_eid = INVALID_EID;
#ifdef ADJUST_AVG
        sum_by_eid[eid] += v * c;
        sz_by_eid[eid] += c;
        sum2_by_eid[eid] += v * v * c;
#endif
    }


}; 
Accumulator::Value Accumulator::work[100000] = {};
// }}}

SimpleAccumulator cond_triple, cond_loccd_year, cond_cd_year, cond_loccd, cond_other, cond_loccd_drought;
struct StrongAssoc{
    int variety_id, loccd, year;
    bool operator<(StrongAssoc const& other)const{
        if(variety_id != other.variety_id){
            return variety_id < other.variety_id;
        }
        if(loccd != other.loccd){
            return loccd < other.loccd;
        }
        if(year != other.year){
            return year < other.year;
        }
        return false;
    }
};
map<StrongAssoc, Accumulator> strong_assoc_map;

map<pair<int, int>, double> mem_dist;
template<class T>
struct MetricWithType : Metric{
    //map<T, double> avg_value;
    map<T, Accumulator> avg_value_accumlator;
    double get_dist(int eid, Metric *_other)
    {
        int a = reinterpret_cast<int>(this);
        int b = reinterpret_cast<int>(_other);
        if(mem_dist.count(make_pair(a, b))){
            return mem_dist[make_pair(a, b)];
        }

        double &ret = mem_dist[make_pair(a, b)];
        ret = 0;
        MetricWithType<T>* other = static_cast<MetricWithType<T>* >(_other);
#ifdef EUCLIDEAN_DISTANCE
        int cnt = 0;
        forI(it, avg_value_accumlator){
            if(other->avg_value_accumlator.count(it->first) ){
                Accumulator acc = other->avg_value_accumlator[it->first];
                if(acc.get_size(eid) == 0){
                    continue;
                }
                double a = it->second.get_avg(eid);
                double b = acc.get_avg(eid);
                ret += (a - b) * (a - b);
                cnt++;
            }
        }
        if(cnt == 0){
            return ret = inf;
        }
        return ret = ret / cnt;
#else
        double la = 0;
        double lb = 0;
        int cnt = 0;
        forI(it, avg_value_accumlator){
            if(other->avg_value_accumlator.count(it->first) ){
                Accumulator acc = other->avg_value_accumlator[it->first];
                if(acc.get_size(eid) == 0){
                    continue;
                }
                double a = it->second.get_avg(eid);
                double b = acc.get_avg(eid);
                ret += a * b;
                la += a * a;
                lb += b * b;
                cnt++;
            }
        }
        int const DIST_TOLERANCE = 2;
        if(fabs(la) < eps || fabs(lb) < eps|| cnt < DIST_TOLERANCE){
            return ret = inf;
        }
        double tmp = fabs(ret / sqrt(fabs(la * lb)));
        checkMin(tmp, 1 - eps);
        checkMax(tmp,  -1 + eps);
        return ret = acos(tmp);
#endif
    }
    void set_stat_attribute(int eid, T key, double v)
    {
        avg_value_accumlator[key].add(-1, eid, v, NULL);
    }
    //void optimize()
    //{
    //    forI(it, avg_value_accumlator){
    //        T key = it->first;
    //        avg_value[key] = it->second.get_avg();
    //    }
    //}
};

int toInt(string s) { // {{{
    if (s == "NULL") return -1;
    stringstream ss(s);
    int ret;
    ss >> ret;
    return ret;
}

double toDouble(string s) {
    if (s == "NULL") return -1;
    stringstream ss(s);
    double ret;
    ss >> ret;
    return ret;
} 
string doubleToString(double d)
{
    if(d < 0){
        return "NULL";
    }
    stringstream ss;
    ss << d;
    return ss.str();
}
// }}}

struct Variety : MetricWithType<pair<int, int> >{
    //struct Variety : MetricWithType<int>{
};

struct VarietyCd : MetricWithType<pair<int, int> >{
    //struct Variety : MetricWithType<int>{
};

struct CdYear: MetricWithType<int>{
};

struct LocationYear: MetricWithType<int>{
};

//DATAS 10-1

// 7-1-2-2
int const LOCCD_TOLERATE = 20;

map<int, Variety> variety_stat;
map<int, VarietyCd> variety_cd_stat;
map<int, LocationYear> location_stat;
map<pair<int, int>, LocationYear> location_year_stat;
map<pair<int, int>, CdYear> cd_year_stat;

map<int, int> get_cd_by_loccd;
map<int, int> get_sc_by_loccd;
map<pair<int, int>, int> get_drought_code_by_loccd_year; // 2-1 definition
int const N_BY_CY = 3;
int const N_BY_LY = 2;
int const N_BY_L = 1;
int const N_BY_V = 1;
int const N_BY_LD = 4;
map<int, Accumulator> avg_variety[5]; // 0->normal, 1->loccd, 2->loccd,year, 3->cd,year, 4->loccd, drought
map<int, Accumulator> avg_variety_v2[4]; // 0->normal_loccd_year, 1->normal_loccd
map<int, Accumulator> avg_loccd[3]; // 0->normal, 1->var, 2->var, year
map<pair<int, int>, Accumulator> avg_cd_year[2]; // 0->normal, 1->var
map<pair<int, int>, Accumulator> avg_mb_year[2]; // 0->normal, 1->var
map<pair<int, int>, Accumulator> avg_loccd_year[2]; // 0->normal, 1->var
map<pair<int, int>, Accumulator> avg_loccd_drought[2]; // 0->normal, 1->var 1-1 definition
map<pair<int, int>, Accumulator> avg_variety_year[2]; // 0->normal, 1->var

int const MAX_ITER = 200;
map<int, SimpleAccumulator> iter_variety[MAX_ITER + 1]; 
map<pair<int, int>, SimpleAccumulator> iter_loccd_year[MAX_ITER + 1];
map<int, Accumulator> iter_variety_last;
map<pair<int, int>, Accumulator> iter_loccd_year_last;

map<int, Accumulator> iter_variety_3_last;
map<pair<int, int>, Accumulator> iter_cd_year_last;

map<int, Accumulator> iter_variety_with_loccd_last;
map<int, Accumulator> iter_loccd_last;

map<int, SimpleAccumulator> iter_variety_2[MAX_ITER + 1]; 
map<pair<int, int>, SimpleAccumulator> iter_loccd_drought[MAX_ITER + 1];
map<int, Accumulator> iter_variety_2_last;
map<pair<int, int>, Accumulator> iter_loccd_drought_last;


map<int, bool> ignore_record;

int const TRIPLE = 0;
int const LOCCD_YEAR = 1;
int const CD_YEAR = 2;
int const LOCCD = 3;
int const LOCCD_DROUGHT = 4;

// 7-1-2-1
map<int, int> loccd_set_size;

struct DataDrought{ // {{{
    int state_code;
    int climate_division;
    int year, month;

    double PCP;
    double TMP;
    double PDSI;
    double PHDI;

    double expect_yield;

    double e1, e2;

    bool operator<(DataDrought const& other)const{
        if(state_code != other.state_code){
            return state_code < other.state_code;
        }
        if(climate_division != other.climate_division){
            return climate_division < other.climate_division;
        }
        if(year != other.year){
            return year < other.year;
        }
        if(month != other.month){
            return month < other.month;
        }
        return false;
    }

    DataDrought()
    {
    }
    DataDrought(string str)
    {
        Rep(p, SZ(str)){
            if(str[p]==','){
                str[p]=' ';
            }else if(str[p] == ' '){
                str[p]='_';
            }
        }
        stringstream ss(str);
        string yearmonth;
        ss >> state_code 
            >> climate_division
            >> yearmonth
            >> PCP
            >> TMP
            >> PDSI
            >> PHDI;
        if(yearmonth.size() == 6){
            year = toInt(yearmonth.substr(0, 4));
            month = toInt(yearmonth.substr(4, 2));
        }else{
            year = month = -1;
        }

        expect_yield = -0.1931 * TMP + 0.4076 * PHDI + 64.3932;
        //e1 =  0.644 * PDSI+0.624 * PHDI+0.353 * PCP-0.266 * TMP;
        //e2 = -0.752* TMP-0.65 * PCP+0.096 * PHDI + -0.046 * PDSI;
        e1 = TMP;
        //e2 = PDSI;
        e2 = PHDI;
    }

    string toString()
    {
        stringstream ss;
        ss << state_code << " " 
            << climate_division << " "
            << year << " "
            << month << " "
            << PCP << " "
            << TMP << " "
            << PDSI << " "
            << PHDI << " ";
        return ss.str();
    }
    int get_drought_code()
    {
        int s, t;
        //if(PHDI < -0.5){
        //    s = 0;
        //}else if(PHDI < 3){
        //    s = 1;
        //}else{
        //    s = 2;
        //}
        //if(TMP < 60){
        //    t = 0;
        //}else if(TMP < 70){
        //    t = 1;
        //}else{
        //    t = 2;
        //}
        //return s * 3 + t;

        if(TMP < 65){
            s = 0;
        }else{
            s = 1;
        }
        if(PHDI < 1.1){
            t = 0;
        }else{
            t = 1;
        }
        return s * 2 + t;
    }
}; // }}}
map<DataDrought, double> get_expect_by_drought;
map<pair<int, int>, vector<int> > fill_missing_year;



struct DataRecord { // {{{
    int id;
    int experimentId, eid;
    int tyear; 
    int y;
    int month;
    int fullyear;
    int loccd; 
    int repno; //Number of the repetition of one trial.  
    string herb; 
    int variety_id; //ID of the variety within experiment. 
    double yield; 
    double yield_nby_variety;
    double yield_nby_variety_year;
    double yield_nby_loccd;
    double yield_nby_loccd_year;
    double yield_nby_cd_year;

    double maturiryNumber; //Maturity number of a variety.
    double relativeMaturity; //Relative maturity of a variety. It's given in case it's available and the variety is a check.
    string str; //Original String.

    int grp, grp_rel;

    int record_id;

    DataRecord()
    {
    }
    DataRecord(string str) 
    {
        for (int p=0;p<SZ(str);++p){
            if(str[p]==','){
                str[p]=' ';
            }else if(str[p] == ' '){
                str[p]='_';
            }
        }
        stringstream ss(str);
        string plantDate;
        string sMaturityNumber;
        string sRelativeMaturity;
        string sLoccd;
        ss >> experimentId >> sLoccd >> repno >> variety_id >> herb >> yield >> sMaturityNumber >> sRelativeMaturity >> plantDate;

        yield = encode_yield(yield);
        eid = experimentId;
        loccd = toInt(sLoccd);
        checkMax(repno, 1);
        if(loccd < 0){
            loccd = 0;
        }
        maturiryNumber = toDouble(sMaturityNumber);
        relativeMaturity = toDouble(sRelativeMaturity);
        tyear = toInt(plantDate.substr(0, 4));
        month = toInt(plantDate.substr(5, 2));
        fullyear = get_combine_year_by_year_month(tyear, month);
        y = trim_year(fullyear);

        int num = round(relativeMaturity * 10);
        grp = num / 10;
        grp_rel = num % 10;
        if(num < 0){
            grp = grp_rel = -1;
        }
    }
    string toString()
    {
        stringstream ss(str);
        char sMonth[10];
        sprintf(sMonth, "%02d", month);
        ss << experimentId << ","
            << loccd << ","
            << repno << ","
            << variety_id << ","
            << herb << ","
            << decode_yield(yield) << ","
            << maturiryNumber <<","
            << relativeMaturity << ","
            << tyear << "-" << sMonth;
        return ss.str();
    }

    string toQuery()
    {
        char sMonth[10];
        sprintf(sMonth, "%02d", month);

        stringstream ss;
        ss << loccd << "," << variety_id << "," 
            << herb << "," << relativeMaturity << ","
            << tyear << "-" << sMonth;
        return ss.str();
    }

    string toString_predict()
    {
        stringstream ss;
        ss 
            << loccd << ","
            << variety_id << ","
            << herb << ","
            << tyear << ","
            << yield << ","
            << yield_nby_variety << ","
            << yield_nby_loccd << ","
            << yield_nby_loccd_year;
        return ss.str();
    }

    void add_to_variety_cd_stat()
    {
        VarietyCd &stat = variety_cd_stat[variety_id];
        int cd = get_cd_by_loccd[loccd];
        stat.set_stat_attribute(eid, make_pair(cd, y), yield); 
    }
    void add_to_variety_stat()
    {
        Variety &stat = variety_stat[variety_id];
        //int cd = get_cd_by_loccd[loccd];
        //int drought_code = get_drought_code_by_loccd_year[make_pair(loccd, y)];
        //var.add(make_pair(cd, year), yield_nby_variety);
        stat.set_stat_attribute(eid, make_pair(loccd, y / 100), yield_nby_variety);  
        //stat.add(eid, make_pair(loccd, year), yield); // 111672
        //stat.add(eid, loccd, yield);
    }
    void add_to_location_stat()
    {
        //LocationYear &stat = location_stat[loccd];
        //stat.add(variety_id, yield_nby_loccd);
        //stat.eid = experimentId;
    }
    void add_to_location_year_stat()
    {
        //LocationYear &stat = location_year_stat[make_pair(loccd, year)];
        //int cd = get_cd_by_loccd[loccd];
        ////stat.add(variety_id, yield_nby_loccd_year);
        //stat.add(year + cd, yield);
        //stat.eid = experimentId;
    }
    void add_to_strong_association()
    {
        StrongAssoc strong_assoc = {variety_id, loccd, y};
        strong_assoc_map[strong_assoc].add(record_id, eid, yield, NULL);
        //strong_assoc_map[strong_assoc].add_with_quantity(eid, yield, repno, NULL);
    }

    bool operator<(DataRecord const& other)const{
        if(variety_id != other.variety_id){
            return variety_id > other.variety_id;
        }
        if(loccd != other.loccd){
            return loccd < other.loccd;
        }
        if(experimentId != other.experimentId){
            return experimentId < other.experimentId;
        }
        if(y != other.y){
            return y < other.y;
        }
        return false;
    }
    bool operator!=(DataRecord const& other)const{
        return *this < other || other < *this;
    }
    void add_to_avg_level0()
    {
        int cd = get_cd_by_loccd[loccd];
        int sc = get_sc_by_loccd[loccd];
        Metric *vstat = &(variety_stat[variety_id]);

        Metric *v_cd_year_stat = &(variety_cd_stat[variety_id]);

        avg_cd_year[0][make_pair(cd, y)].add(record_id, eid, yield, v_cd_year_stat);

        avg_mb_year[0][make_pair(sc, y)].add(record_id, eid, yield, vstat);
        avg_loccd[0][loccd].add(record_id, eid, yield, vstat);
        avg_loccd_year[0][make_pair(loccd, y)].add(record_id, eid, yield, vstat);

        int drought_code = get_drought_code_by_loccd_year[make_pair(loccd, fullyear)];
        avg_loccd_drought[0][make_pair(loccd, drought_code)].add(record_id, eid, yield, vstat); // 1-2 add to the accumulator

        Metric *location_year = &(location_year_stat[make_pair(loccd, y)]);
        //Metric *cd_year = &(cd_year_stat[make_pair(cd, year)]);

        avg_variety[0][variety_id].add(record_id, eid, yield, location_year);
        //avg_variety_and_cd_year[0][variety_id].add(eid, yield, cd_year);

        avg_variety_year[0][make_pair(variety_id, y)].add(record_id, eid, yield, NULL);

    }
    void calc_normal()
    {
        int cd = get_cd_by_loccd[loccd];
        yield_nby_variety = avg_variety[0][variety_id].get_normlize(-1, yield);
        yield_nby_variety_year = avg_variety_year[0][make_pair(variety_id, y)].get_normlize(-1, yield);
        yield_nby_loccd = avg_loccd[0][loccd].get_normlize(-1, yield);
        yield_nby_loccd_year = avg_loccd_year[0][make_pair(loccd, y)].get_normlize(-1, yield);
        yield_nby_cd_year = avg_cd_year[0][make_pair(cd, y)].get_normlize(-1, yield);
        checkNan(yield_nby_variety, 0.);
        checkNan(yield_nby_variety_year, 0.);
        checkNan(yield_nby_loccd, 0.);
        checkNan(yield_nby_loccd_year, 0.);
        checkNan(yield_nby_cd_year, 0.);
    }
    void add_to_avg()
    {
        int cd = get_cd_by_loccd[loccd];
        //int sc = get_sc_by_loccd[loccd];
        Metric *vstat = &(variety_stat[variety_id]);
        avg_cd_year[1][make_pair(cd, y)].add(record_id, eid, yield_nby_variety, vstat);
        //avg_sc_year[1][make_pair(sc, y)].add(record_id, eid, yield_nby_variety, vstat);
        avg_loccd_year[1][make_pair(loccd, y)].add(record_id, eid, yield_nby_variety, vstat);
        avg_variety_year[1][make_pair(variety_id, y)].add(record_id, eid, yield_nby_loccd, NULL);

        avg_loccd[1][loccd].add(record_id, eid, yield_nby_variety, vstat);
        avg_loccd[2][loccd].add(record_id, eid, yield_nby_variety_year, NULL);
        avg_variety[1][variety_id].add(record_id, eid, yield_nby_loccd, vstat);
        avg_variety[2][variety_id].add(record_id, eid, yield_nby_loccd_year, vstat);

        int drought_code = get_drought_code_by_loccd_year[make_pair(loccd, fullyear)];
        double yield_nby_loccd_drought = avg_loccd_drought[0][make_pair(loccd, drought_code)].get_normlize(-1, yield);
        avg_variety[N_BY_LD][variety_id].add(record_id, eid, yield_nby_loccd_drought, vstat); // 1-3 add relative avg

        avg_variety[3][variety_id].add(record_id, eid, yield_nby_cd_year, NULL);

        avg_variety_v2[0][variety_id].add(record_id, eid, yield / yield_nby_loccd_year, NULL);
        avg_variety_v2[1][variety_id].add(record_id, eid, yield / yield_nby_loccd, NULL);

    }

}; // }}}

struct DataLocation{ // {{{
    int loccd; 
    double latitude;
    double longitude;
    string country_name;
    int maturityZone;
    string maturitySubZone;
    int maturityBand;
    int state_code;
    int climate_division;
    int fips_code;

    DataLocation()
    {
    }
    DataLocation(string str) 
    {
        Rep(p, SZ(str)){
            if(str[p]==','){
                str[p]=' ';
            }else if(str[p] == ' '){
                str[p]='_';
            }
        }
        stringstream ss(str);
        ss >> loccd
            >> latitude
            >> longitude
            >> country_name
            >> maturityZone
            >> maturitySubZone
            >> maturityBand
            >> state_code
            >> climate_division
            >> fips_code;
    }
}; // }}}

void set_fill_missing_year()
{
    fill_missing_year.clear();
    forI(it, get_cd_by_loccd){
        int loccd = it->first;
        int cd = it->second;
        int sc = get_sc_by_loccd[loccd];
        DataDrought drought;
        drought.climate_division = cd;
        drought.state_code = sc;
        vector<pair<double, int> > cand;
        for(int year = 2004; year <= 2009; ++year){
            for(int month = 1; month <= 12; ++month){
                drought.year = year;
                drought.month = month;
                double expect = get_expect_by_drought[drought];
                cand.push_back(make_pair(expect, get_combine_year_by_year_month(year, month)));
            }
        }

        vector<pair<double, int> > neighbors;
        for(int year = 2004; year <= 2009; ++year){
            for(int month = 1; month <= 12; ++month){
                int curr = get_combine_year_by_year_month(year, month);
                drought.year = year;
                drought.month = month;
                double expect = get_expect_by_drought[drought];

                neighbors.clear();
                forE(c, cand){
                    neighbors.push_back(make_pair(fabs(c.first - expect), c.second));
                }
                sort(ALL(neighbors));
                Rep(i, SZ(neighbors)){
                    fill_missing_year[make_pair(loccd, curr)].push_back(neighbors[i].second);
                }
            }
        }
    }
}

int const NRecord = 300000;
DataRecord data_record[NRecord];
DataLocation data_locations[1000];
DataDrought data_drought[100000];

struct Query{ 
    // {{{
    int loccd;  // can be null
    int variety_id; 
    string herb; 
    double relativeMaturity; 
    int eid;
    int tyear;
    int month;
    int y;
    int fullyear;

    double yield; 
    double yield_nby_variety;
    double yield_nby_variety_year;
    double yield_nby_loccd;
    double yield_nby_loccd_year;

    int grp, grp_rel;

    Query(string str) {
        Rep(p, str.size()){
            if(str[p]==','){
                str[p]=' ';
            }else if(str[p] == ' '){
                str[p]='_';
            }
        }
        stringstream ss(str);
        string plantDate;
        string sRelativeMaturity;
        string sLoccd;
        ss >> sLoccd >> variety_id >> herb >> sRelativeMaturity >> plantDate;
        loccd = toInt(sLoccd);
        relativeMaturity = toDouble(sRelativeMaturity);
        tyear = toInt(plantDate.substr(0, 4));

        int num = round(relativeMaturity * 10);
        grp = num / 10;
        grp_rel = num % 10;
        if(num < 0){
            grp = grp_rel = -1;
        }

        month = toInt(plantDate.substr(5, 2));

        fullyear = get_combine_year_by_year_month(tyear, month);
        y = trim_year(fullyear);
    }
    //}}}

}; 
int nRecord, nLocations;
void init_map()
{
    variety_stat.clear();
    location_stat.clear();
    location_year_stat.clear();
    //cd_year_stat.clear();
    Rep(i, nRecord){
        int loccd = data_record[i].loccd;
        int year = data_record[i].y;

        variety_stat[data_record[i].variety_id];

        variety_stat[data_record[i].variety_id].set_id(data_record[i].variety_id);

        location_stat[loccd];
        location_stat[loccd].set_id(loccd);
        location_year_stat[make_pair(loccd, year)];
        //cd_year_stat[make_pair(cd, year)];
    }
}

//try to trim trainingData, call after add varieties
void trim_record(vector<string> &trainingData)
{
    //vector<string> tmp;
    int sz = trainingData.size();
    for(int i = sz - 1; i >= 0; --i){
        DataRecord record(trainingData[i]);
        if(frequent_vid.count(record.variety_id) == 0){
            swap(trainingData[i], trainingData[sz - 1]);
            sz--;
        }
    }
    trainingData.resize(sz);

    nRecord = trainingData.size();
    Rep(i, nRecord){
        data_record[i] = DataRecord(trainingData[i]);
    }
#ifdef TRIM_RECORD
    sort(data_record, data_record + nRecord);
    int curr = 0;
    double yield = 0;
    double sum = 0;
    int repno = 0;
    sz = 0;
    for(int i = 0; i < nRecord; ++i){
        yield += data_record[i].yield;
        repno += data_record[i].repno;
        sum += data_record[i].yield * data_record[i].repno;
        sz++;
        if(i == nRecord - 1 || data_record[i] != data_record[i + 1]){
            data_record[curr] = data_record[i];
            data_record[curr].yield = yield / sz;
            //data_record[curr].yield = sum / repno;
            //data_record[curr].repno = repno;
            data_record[curr].repno = 1;
            yield = 0;
            sum = 0;
            repno = 0;
            sz = 0;
            curr++;
        }
    }
    cerr << "trimed: ";
    DBG(nRecord - curr);
    nRecord = curr;
#endif
    Rep(i, nRecord){
        data_record[i].id = i;
        data_record[i].record_id = i;
        trainingData[i] = data_record[i].toString();
    }
    trainingData.resize(nRecord);
}

void insert_varieties(vector<string> &varieties)
{
    Rep(i, SZ(varieties)){
        frequent_vid.insert(toInt(varieties[i]));
    }
}
template<class TA, class TB>
struct MatrixRecord{
    TA ida;
    TB idb;
    double v;
};

    template<class TA, class TB>
void decompose(vector<MatrixRecord<TA, TB> >& records, map<TA, SimpleAccumulator> &resultA, map<TB, SimpleAccumulator> &resultB, int max_iter)
{
    map<TA, SimpleAccumulator> A, IA[2];
    map<TB, SimpleAccumulator> B, IB[2];
    forI(it, records){
        A[it->ida].add(it->v);
        B[it->idb].add(it->v);
    }
    forI(it, records){
        TB idb = it->idb;
        IA[0][it->ida].add(it->v);
        IB[0][idb].add(it->v / B[idb].get_avg());
    }
    for(int iter = 0; iter < max_iter; ++iter){
        int old = iter % 2;
        IA[1 - old].clear();
        IB[1 - old].clear();
        forI(it, records){
            TA ida = it->ida;
            TB idb = it->idb;
            double v = it->v;
            IA[1 - old][ida].add(v / IB[old][idb].get_avg());
            IB[1 - old][idb].add(v / IA[old][ida].get_avg());
        }
    }
    resultA = IA[max_iter % 2];
    resultB = IB[max_iter % 2];
}

int get_division_code(SimpleAccumulator acc, double v, int part)
{
    double minv = acc.get_min();
    double maxv = acc.get_max();
    for(int i = part - 1; i >= 1; --i){
        if(v < (minv * i + maxv * (part - i)) / part){
            return i;
        }
    }
    return 0;
}
// 10-2
struct Estimator{ // {{{
    static double normal_avg;
#ifdef NORMALIZE
    static double const normal_part = 0;
#else
    static double const normal_part = 1;
#endif
    static int const tolerance = 1;

    StrongAssoc strong_assoc;

    int eid, variety_id, loccd, year;
    Variety *vstat;
    int sz_local_year;
    int grp_rel;
    int cd;

    int drought_code; // 4-1
    int fullyear;

    int month;
    Estimator(int eid, int variety_id, int loccd, int year, int fullyear, int grp_rel)
        :eid(eid), variety_id(variety_id), loccd(loccd), year(year), grp_rel(grp_rel),
        fullyear(fullyear)
    {
        vstat = &(variety_stat[variety_id]);
        sz_local_year = avg_loccd_year[0][make_pair(loccd, year)].get_size(eid);
        strong_assoc.variety_id = variety_id;
        strong_assoc.loccd = loccd;
        strong_assoc.year= year;

        cd = get_cd_by_loccd[loccd];
        drought_code = get_drought_code_by_loccd_year[make_pair(loccd, fullyear)]; // 4-2
    }

    //10-3
    static int const HAS_TOLERANCE = 0;
    bool has_loccd_year()
    {
        return avg_loccd_year[0][make_pair(loccd, year)].get_size(eid) > HAS_TOLERANCE;
    }
    int size_loccd_year()
    {
        return avg_loccd_year[0][make_pair(loccd, year)].get_size(eid);
    }

    bool has_cd_year()
    {
        return avg_cd_year[0][make_pair(cd, year)].get_size(eid) > HAS_TOLERANCE;
    }
    int size_cd_year()
    {
        return avg_cd_year[0][make_pair(cd, year)].get_size(eid);
    }


    bool has_loccd_drought()
    {
        return avg_loccd_drought[0][make_pair(loccd, drought_code)].get_size(eid) > HAS_TOLERANCE;
    }
    int size_loccd_drought()
    {
        return avg_loccd_drought[0][make_pair(loccd, drought_code)].get_size(eid);
    }

    bool has_variety()
    {
        return avg_variety[0][variety_id].get_size(eid) > HAS_TOLERANCE;
    }
    int size_variety()
    {
        return avg_variety[0][variety_id].get_size(eid);
    }

    bool has_triple()
    {
        return strong_assoc_map.count(strong_assoc)
            && strong_assoc_map[strong_assoc].get_size(eid) > HAS_TOLERANCE;
    }
    int size_triple()
    {
        return strong_assoc_map[strong_assoc].get_size(eid);
    }


    //{{{
    double get_avg_variety()
    {
        Accumulator &acc = avg_variety[0][variety_id];
        double rel = avg_loccd_year[1][make_pair(loccd, year)].get_avg(eid, normal_part);
        return acc.denormalize(eid, rel, normal_avg);
    }

    double get_avg_variety_and_cd_year()
    {
        int cd = get_cd_by_loccd[loccd];
        Accumulator &acc = avg_variety[0][variety_id];
        double rel = avg_cd_year[1][make_pair(cd, year)].get_avg(eid, normal_part);
        return acc.denormalize(eid, rel, normal_avg);
    }

    double get_avg_loccd_year()
    {
        Accumulator &acc = avg_loccd_year[0][make_pair(loccd, year)];
        double rel = avg_variety[2][variety_id].get_avg(eid, normal_part);
        return acc.denormalize(eid, rel, normal_avg);
    }
    double get_avg_cd_year()
    {
        int cd = get_cd_by_loccd[loccd];
        Accumulator &acc = avg_cd_year[0][make_pair(cd, year)];
        double rel = avg_variety[3][variety_id].get_avg(eid, normal_part);
        return acc.denormalize(eid, rel, normal_avg);
    }

    double get_avg_cd_year_v2()
    {
        int cd = get_cd_by_loccd[loccd];
        Accumulator acc = avg_cd_year[0][make_pair(cd, year)];
        vector<pair<double, int> > nearest_cand = acc.get_all(eid);
        SimpleAccumulator avg_cd_year_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            avg_cd_year_by_cand.add(value / avg_variety[N_BY_CY][id].get_avg(eid, normal_part));
        }
        double rel = avg_variety[N_BY_CY][variety_id].get_avg(eid, normal_part);
        return avg_cd_year_by_cand.denormalize(rel, normal_avg);
    }

    double get_avg_loccd_v2()
    {
        Accumulator acc = avg_loccd[0][loccd];
        vector<pair<double, int> > nearest_cand = acc.get_all(eid);
        SimpleAccumulator avg_loccd_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            avg_loccd_by_cand.add(value / avg_variety[N_BY_L][id].get_avg(eid, normal_part));
        }
        double rel = avg_variety[N_BY_L][variety_id].get_avg(eid, normal_part);
        return avg_loccd_by_cand.denormalize(rel, normal_avg);
    }

    double get_avg_loccd_year_knn(int bnd)
    {
        Accumulator acc = avg_loccd_year[0][make_pair(loccd, year)];
        vector<pair<double, int> > nearest_cand = acc.get_knn(eid, vstat, bnd);
        SimpleAccumulator avg_loccd_year_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            assert(id >= 0);
            avg_loccd_year_by_cand.add(value / avg_variety[N_BY_LY][id].get_avg(eid, normal_part));
        }
        double rel = avg_variety[N_BY_LY][variety_id].get_avg(eid, normal_part);
        //return acc.denormalize_by(eid, vstat, bnd, rel, normal_avg);
        return avg_loccd_year_by_cand.denormalize(rel, normal_avg);
    }

    double get_avg_loccd_year_v2()
    {
        Accumulator acc = avg_loccd_year[0][make_pair(loccd, year)];
        vector<pair<double, int> > nearest_cand = acc.get_all(eid);
        SimpleAccumulator avg_loccd_year_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            avg_loccd_year_by_cand.add(value / avg_variety[N_BY_LY][id].get_avg(eid, normal_part));
        }
        double rel = avg_variety[N_BY_LY][variety_id].get_avg(eid, normal_part);
        return avg_loccd_year_by_cand.denormalize(rel, normal_avg);
    }
    double get_avg_loccd_year_v3()
    {
        return iter_loccd_year_last[make_pair(loccd, year)].get_avg(eid) * iter_variety_last[variety_id].get_avg(eid);
        //return iter_loccd_year[MAX_ITER - 1][make_pair(loccd, year)].get_avg() * iter_variety[MAX_ITER - 1][variety_id].get_avg();
    }
    double get_avg_loccd_v3()
    {
        return iter_loccd_last[loccd].get_avg(eid) * iter_variety_with_loccd_last[variety_id].get_avg(eid);
        //return iter_loccd_year[MAX_ITER - 1][make_pair(loccd, year)].get_avg() * iter_variety[MAX_ITER - 1][variety_id].get_avg();
    }

    double get_avg_cd_year_v3()
    {
        return iter_cd_year_last[make_pair(cd, year)].get_avg(eid) * iter_variety_3_last[variety_id].get_avg(eid);
        //return iter_loccd_year[MAX_ITER - 1][make_pair(loccd, year)].get_avg() * iter_variety[MAX_ITER - 1][variety_id].get_avg();
    }
    double get_avg_loccd_drought_v3() 
    {
        return iter_loccd_drought_last[make_pair(loccd, drought_code)].get_avg(eid) * iter_variety_2_last[variety_id].get_avg(eid);
    }

    double get_avg_loccd_drought_v2() // 3-1
    {
        Accumulator acc = avg_loccd_drought[0][make_pair(loccd, drought_code)];  // 3-1-1
        vector<pair<double, int> > nearest_cand = acc.get_all(eid);
        SimpleAccumulator avg_loccd_drought_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            avg_loccd_drought_by_cand.add(value / avg_variety[N_BY_LD][id].get_avg(eid, normal_part)); // 3-1-2
        }
        double rel = avg_variety[N_BY_LD][variety_id].get_avg(eid, normal_part);
        return avg_loccd_drought_by_cand.denormalize(rel, normal_avg);
    }
    double get_avg_loccd_drought_knn(int bnd) // 3-1
    {
        Accumulator acc = avg_loccd_drought[0][make_pair(loccd, drought_code)];  // 3-1-1
        //DBG(acc.get_size(eid));

        vector<pair<double, int> > nearest_cand;
        nearest_cand.clear();
        nearest_cand = acc.get_knn(eid, vstat, bnd);
        //DBG(SZ(nearest_cand));
        SimpleAccumulator avg_loccd_drought_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            avg_loccd_drought_by_cand.add(value / avg_variety[N_BY_LD][id].get_avg(eid, normal_part)); // 3-1-2
        }
        double rel = avg_variety[N_BY_LD][variety_id].get_avg(eid, normal_part);
        return avg_loccd_drought_by_cand.denormalize(rel, normal_avg);
    }

    double get_avg_variety_and_loccd_year_v2()
    {
        Accumulator acc = avg_variety_v2[0][variety_id];
        double rel = avg_loccd_year[N_BY_V][make_pair(loccd, year)].get_avg(eid, normal_part);
        return acc.denormalize(eid, rel, normal_avg);
    }
    double get_avg_variety_and_loccd_v2()
    {
        Accumulator acc = avg_variety_v2[0][variety_id];
        double rel = avg_loccd[N_BY_V][loccd].get_avg(eid, normal_part);
        return acc.denormalize(eid, rel, normal_avg);
    }

    double get_avg_loccd_knn(int bnd)
    {
        Accumulator acc = avg_loccd[0][loccd];
        vector<pair<double, int> > nearest_cand = acc.get_knn(eid, vstat, bnd);
        SimpleAccumulator avg_loccd_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            assert(id >= 0);
            avg_loccd_by_cand.add(value / avg_variety[N_BY_L][id].get_avg(eid, normal_part));
        }
        double rel = avg_variety[N_BY_L][variety_id].get_avg(eid, normal_part);
        return avg_loccd_by_cand.denormalize(rel, normal_avg);
    }

    double get_avg_cd_year_knn(int bnd)
    {
        Accumulator acc = avg_cd_year[0][make_pair(cd, year)];
        VarietyCd *v_cd_year_stat = &(variety_cd_stat[variety_id]);
        vector<pair<double, int> > nearest_cand = acc.get_knn(eid, v_cd_year_stat, bnd);
        SimpleAccumulator avg_cd_year_by_cand;
        forE(p_v_id, nearest_cand){
            double value = p_v_id.first;
            int id = p_v_id.second;
            assert(id >= 0);
            avg_cd_year_by_cand.add(value / avg_variety[N_BY_CY][id].get_avg(eid, normal_part));
        }
        double rel = avg_variety[N_BY_CY][variety_id].get_avg(eid, normal_part);
        return avg_cd_year_by_cand.denormalize(rel, normal_avg);
    }

    static int const BND = 0;
    int get_condition()
    {
        if(!has_variety()){
            return -1;
        }
        if(has_triple()){
            return TRIPLE;
        }
        if(has_loccd_year()){
            return LOCCD_YEAR;
        }
        if(has_loccd_drought()){
            return LOCCD_DROUGHT;
        }
        if(has_cd_year()){
            return CD_YEAR;
        }
        return LOCCD;
    }
    //}}}

    double harmonic_rate(double x)
    {
        //return min(inf, exp(x / 10 - 1) * 3);
        return x / 3;
    }
    //e-1
    double get_estimate(double actual_value)
    {
        int cond = get_condition();
        double ret;
        /*
         * 122640
         * 123418, x * x
         * 124049, e^(x-2)
         * 123654, e^(x/2)
         * 124252, e^(x/3-1)
         * 124253, e^(x/4-1)
         * 124523, e^(x/10-1) * 2
         * 124478, e^(x/10-1) * 3
         * 124844, x / 3
         * 124499, x / 8
         * 124271, x * x / 8
         * 124980, x / 2
         * 125322, x / 2
         * 125575, x / 3
         *
         cond_triple.get_rmse(): 6.78978
         cond_loccd_year.get_rmse(): 8.16204
         cond_cd_year.get_rmse(): 15.9839
         cond_loccd.get_rmse(): 14.12
         cond_loccd_drought.get_rmse(): 15.2184
         */
        if(cond == TRIPLE){
            ret = get_midpiont(get_triple_avg(), get_avg_loccd_year_v3(),
                    harmonic_rate(size_triple()), 1);
            cond_triple.add(fabs(ret -  actual_value));

        }else if(cond == LOCCD_YEAR){
            //ret = get_avg_loccd_year_knn(64); // ?
            //ret = get_avg_loccd_year_knn(32); // 8.64422
            //ret = get_avg_loccd_year_v2(); // 8.61591
            ret = get_midpiont(get_avg_loccd_year_v3(), get_avg_loccd_drought_v3(),
                    harmonic_rate(size_loccd_year()), 1);
            cond_loccd_year.add(fabs(ret -  actual_value));

        }else if(cond == LOCCD_DROUGHT){
            //ret = get_avg_loccd_drought_knn(64); // 14.8312
            //ret = get_avg_loccd_drought_knn(32); // 14.9413
            //ret = get_avg_loccd_drought_v2(); // 14.9341
            ret = get_midpiont(get_avg_loccd_drought_v3(), get_avg_cd_year_v3(),
                    harmonic_rate(size_loccd_drought()) / 8, 1);
            cond_loccd_drought.add(fabs(ret -  actual_value));

        }else if(cond == CD_YEAR){
            //ret = get_avg_cd_year_v2();// 15.5658
            ret = get_midpiont(get_avg_cd_year_v3(), get_avg_variety_and_loccd_v2(),
                    harmonic_rate(size_cd_year()) / 8, 1);
            cond_cd_year.add(fabs(ret -  actual_value));

        }else{
            ret = get_avg_variety_and_loccd_v2();
            //ret = get_avg_loccd_v3();
            cond_loccd.add(fabs(ret -  actual_value));
        }
        return ret;
    }

    double get_estimate_complex(double actual_value)
    {
        int cond = get_condition();
        double ret;
        if(cond == TRIPLE){
            ret = 
                0.8048 * get_triple_avg() +
                0.1861 * get_avg_loccd_year_v2() +
                0.5155;
            cond_triple.add(fabs(ret -  actual_value));

        }else if(cond == LOCCD_YEAR){
            ret = 0.8652 * get_avg_loccd_year_v2() +
                0.0913 * get_avg_variety_and_loccd_year_v2() +
                2.4359;
            cond_loccd_year.add(fabs(ret -  actual_value));

        }else if(cond == LOCCD_DROUGHT){
            ret = 
                0.8374 * get_avg_loccd_drought_v2() +
                0.0552 * get_avg_variety_and_loccd_v2() +
                5.999;
            cond_loccd_drought.add(fabs(ret -  actual_value));

        }else if(cond == CD_YEAR){
            ret = 
                0.5358 * get_avg_cd_year_v2() +
                0.5192 * get_avg_variety_and_loccd_v2() +
                -3.2212;
            cond_cd_year.add(fabs(ret -  actual_value));

        }else{
            ret = 0.6936 * get_avg_loccd_drought_v2() +
                0.3294 * get_avg_cd_year_v2() +
                0.0221 * get_avg_variety_and_loccd_v2() +
                -2.668;
            cond_loccd.add(fabs(ret -  actual_value));
        }
        return ret;
    }
    double get_triple_avg()
    {
        return strong_assoc_map[strong_assoc].get_avg(eid);
    }
};
//}}}
double Estimator::normal_avg = 0;

// 7-1
void analysis(vector<string> &trainingData, vector<string> &locations, vector<string> &varieties, vector<string> &droughts) // {{{
{
    // insert varieties
    insert_varieties(varieties);
    // read record
    trim_record(trainingData);

    // read location
    nLocations = SZ(locations);
    get_cd_by_loccd.clear();
    get_sc_by_loccd.clear();
    get_drought_code_by_loccd_year.clear(); // 2-2 initialization

    // read drought
    int nDrought = SZ(droughts);
    map<DataDrought, DataDrought> get_drought;
    Rep(i, nDrought){
        data_drought[i] = DataDrought(droughts[i]);
        get_drought[data_drought[i]] = data_drought[i];
    }

    //count record by eid 7-1-1
    Rep(i, nRecord){
        int loccd = data_record[i].loccd;
        loccd_set_size[loccd]++;
    }
    //cerr << "stat for loccd" << endl;
    //map<int, int> reverse_loccd_set_size;
    //forI(it, loccd_set_size){
    //    reverse_loccd_set_size[it->second]++;
    //}
    //forI(it, reverse_loccd_set_size){
    //    cerr << *it << "\t";
    //}
    //cerr << endl;

    Rep(i, nLocations){
        data_locations[i] = DataLocation(locations[i]);

        int loccd = data_locations[i].loccd;
        int cd = data_locations[i].climate_division;
        int sc = data_locations[i].state_code;

        SimpleAccumulator acc_temperature, acc_PHDI;
        SimpleAccumulator acc_e1, acc_e2;
        DataDrought key;
        key.state_code = sc;
        key.climate_division = cd;
        for(int year = 2004; year <= 2009; ++year){
            for(int month = 1; month <= 12; ++month){
                key.year = year;
                key.month = month;
                DataDrought drought = get_drought[key];
                // 2-3 
                acc_temperature.add(drought.TMP);
                acc_PHDI.add(drought.PHDI);

                acc_e1.add(drought.e1);
                acc_e2.add(drought.e2);
            }
        }
        for(int year = 2004; year <= 2009; ++year){
            for(int month = 1; month <= 12; ++month){
                key.year = year;
                key.month = month;
                DataDrought drought = get_drought[key];

                // 2-4 set actual value
                int s, t, a, b;
                //a = acc_temperature.get_min();
                //b = acc_temperature.get_max();
                a = acc_e1.get_min();
                b = acc_e1.get_max();
                if(drought.e1 < (a * 2 + b * 1) / 3){
                    s = 0;
                }else if(drought.e1 < (a * 1 + b * 2) / 3){
                    s = 1;
                }else{
                    s = 2;
                }
                a = acc_e2.get_min();
                b = acc_e2.get_max();
                if(drought.e2 < (a * 2 + b * 1) / 3){
                    t = 0;
                }else if(drought.e2 < (a * 1 + b * 2) / 3){
                    t = 1;
                }else{
                    t = 2;
                }
                int drought_code = s * 3 + t;
                get_drought_code_by_loccd_year[make_pair(loccd, get_combine_year_by_year_month(year, month))] = drought_code;
            }
        }

        get_cd_by_loccd[loccd] = cd;
        get_sc_by_loccd[loccd] = sc;
    }
    set_fill_missing_year();
    //cerr << "first few missing year: " << endl;
    //Rep(i, 10){
    //    int pos = rand() % nRecord;
    //    DataRecord &dr = data_record[pos];
    //    int loccd = dr.loccd;
    //    int y = dr.y;
    //    forI(it, fill_missing_year[make_pair(loccd, y)]){
    //        cerr << *it << ", ";
    //    }
    //    cerr << endl;
    //}
    init_map();

    Rep(i, 3){
        avg_variety[i].clear();
        avg_loccd[i].clear();
    }
    Rep(i, 2){
        avg_cd_year[i].clear();
        avg_mb_year[i].clear();
        avg_loccd_year[i].clear();
        avg_variety_year[i].clear();
    }

    Rep(i, nRecord){
        data_record[i].add_to_avg_level0();
    }
    Rep(i, nRecord){
        data_record[i].calc_normal();
    }
    Rep(i, nRecord){
        data_record[i].add_to_avg();
    }
    Rep(i, nRecord){
        data_record[i].add_to_strong_association();
    }

    //feature vector for variety, location and location,year
    Rep(i, nRecord){
        data_record[i].add_to_variety_stat();
        data_record[i].add_to_variety_cd_stat();
        data_record[i].add_to_location_stat();
        data_record[i].add_to_location_year_stat();
    }

    vector<MatrixRecord<pair<int,int>, int> > record_for_loccd_year;
    vector<MatrixRecord<pair<int,int>, int> > record_for_cd_year;
    vector<MatrixRecord<int, int> > record_for_loccd;
    Rep(i, nRecord){
        int loccd = data_record[i].loccd;
        int cd = get_cd_by_loccd[loccd];
        int year = data_record[i].y;
        int variety_id = data_record[i].variety_id;
        double yield = data_record[i].yield;

        MatrixRecord<pair<int, int>, int> curr;
        curr.ida = make_pair(loccd, year);
        curr.idb = variety_id;
        curr.v = yield;
        record_for_loccd_year.push_back(curr);

        curr.ida = make_pair(cd, year);
        curr.idb = variety_id;
        curr.v = yield;
        record_for_cd_year.push_back(curr);

        MatrixRecord<int, int> curr2;
        curr2.ida = loccd;
        curr2.idb = variety_id;
        curr2.v = yield;
        record_for_loccd.push_back(curr2);
    }

    map<int, SimpleAccumulator> result_loccd;
    map<pair<int,int>, SimpleAccumulator> result_loccd_year;
    map<pair<int,int>, SimpleAccumulator> result_cd_year;
    map<int, SimpleAccumulator> result_variety;
    map<int, SimpleAccumulator> result_variety_with_cd;
    map<int, SimpleAccumulator> result_variety_with_loccd;

    decompose(record_for_loccd_year, result_loccd_year, result_variety, MAX_ITER);
    decompose(record_for_cd_year, result_cd_year, result_variety_with_cd, MAX_ITER);
    decompose(record_for_loccd, result_loccd, result_variety_with_loccd, MAX_ITER);

    Rep(i, nRecord){
        int loccd = data_record[i].loccd;
        int year = data_record[i].y;
        double yield = data_record[i].yield;
        int cd = get_cd_by_loccd[loccd];
        int variety_id = data_record[i].variety_id;
        double relative_yield = result_variety[variety_id].get_avg();
        int eid = data_record[i].eid;

        iter_variety_last[variety_id].add(i, eid, yield / result_loccd_year[make_pair(loccd, year)].get_avg(), NULL);
        iter_loccd_year_last[make_pair(loccd, year)].add(i, eid, yield / relative_yield, NULL);

        relative_yield = result_variety_with_cd[variety_id].get_avg();
        iter_variety_3_last[variety_id].add(i, eid, yield / result_cd_year[make_pair(cd, year)].get_avg(), NULL);
        iter_cd_year_last[make_pair(cd, year)].add(i, eid, yield / relative_yield, NULL);

        relative_yield = result_variety_with_loccd[variety_id].get_avg();
        iter_variety_with_loccd_last[variety_id].add(i, eid, yield / result_loccd[loccd].get_avg(), NULL);
        iter_loccd_last[loccd].add(i, eid, yield / relative_yield, NULL);
    }

    Rep(i, nRecord){
        double yield = data_record[i].yield;
        //int eid = data_record[i].eid;
        int loccd = data_record[i].loccd;
        int year = data_record[i].y;
        int fullyear = data_record[i].fullyear;
        int variety_id = data_record[i].variety_id;
        int drought_code = get_drought_code_by_loccd_year[make_pair(loccd, fullyear)];
        //iter_variety[0][variety_id].add(yield / avg_variety[0][variety_id].get_avg(-1));
        //iter_loccd_year[0][make_pair(loccd, year)].add(yield);

        iter_variety_2[0][variety_id].add(yield / avg_variety[0][variety_id].get_avg(-1));
        iter_loccd_drought[0][make_pair(loccd, drought_code)].add(yield);
    }
    for(int iter = 0; iter < MAX_ITER; ++iter){
        Rep(i, nRecord){
            if(i % 1000 == 0){
                cerr << "\r" << iter << " " << i;
            }
            //int eid = data_record[i].eid;
            int year = data_record[i].y;
            int fullyear = data_record[i].fullyear;
            double yield = data_record[i].yield;
            int loccd = data_record[i].loccd;
            int variety_id = data_record[i].variety_id;
            double relative_yield = iter_variety[iter][variety_id].get_avg();
            int drought_code = get_drought_code_by_loccd_year[make_pair(loccd, fullyear)];
            //iter_variety[iter + 1][variety_id].add(yield / iter_loccd_year[iter][make_pair(loccd, year)].get_avg());
            //iter_loccd_year[iter + 1][make_pair(loccd, year)].add(yield / relative_yield);

            relative_yield = iter_variety_2[iter][variety_id].get_avg();
            iter_variety_2[iter + 1][variety_id].add(yield / iter_loccd_drought[iter][make_pair(loccd, drought_code)].get_avg());
            iter_loccd_drought[iter + 1][make_pair(loccd, drought_code)].add(yield / relative_yield);
        }
    }
    Rep(i, nRecord){
        int eid = data_record[i].eid;
        int year = data_record[i].y;
        int fullyear = data_record[i].fullyear;
        double yield = data_record[i].yield;
        int loccd = data_record[i].loccd;
        int variety_id = data_record[i].variety_id;
        double relative_yield = iter_variety[MAX_ITER - 1][variety_id].get_avg();
        int drought_code = get_drought_code_by_loccd_year[make_pair(loccd, fullyear)];
        //iter_variety_last[variety_id].add(i, eid, yield / iter_loccd_year[MAX_ITER - 1][make_pair(loccd, year)].get_avg(), NULL);
        //iter_loccd_year_last[make_pair(loccd, year)].add(i, eid, yield / relative_yield, NULL);

        relative_yield = iter_variety_2[MAX_ITER - 1][variety_id].get_avg();
        iter_variety_2_last[variety_id].add(i, eid, yield / iter_loccd_drought[MAX_ITER - 1][make_pair(loccd, drought_code)].get_avg(), NULL);
        iter_loccd_drought_last[make_pair(loccd, drought_code)].add(i, eid, yield / relative_yield, NULL);
    }

} 
// }}}


struct YieldPredictor // {{{
{
    vector <double> predictYield(vector <string>& trainingData, 
            vector <string>& droughtMonitor, 
            vector <string>& droughtNOAA, 
            vector <string>& locations, 
            vector <string>& varieties, 
            vector <string>& queries)
    {
        Rep(i, SZ(queries)){
            Query query(queries[i]);
            frequent_vid.insert(query.variety_id);
        }

        analysis(trainingData, locations, varieties, droughtNOAA);

        DBG(trainingData.size());
        DBG(queries.size());

        vector<double> ret(SZ(queries));
        int cntNaN = 0;
        cerr << endl;
        Rep(i, SZ(queries)){
            Query query(queries[i]);
            query.eid = -1;
            double actual_value = -1;
#ifdef LOCAL
            query.eid = data_record[i].eid;
            actual_value = data_record[i].yield;
            if(ignore_record[i]){
                continue;
            }
            if(i % 100 == 0){
                cerr << "\r" << i;
            }
#endif
            Estimator estimator(query.eid, query.variety_id, query.loccd, query.y, query.fullyear, query.grp_rel);
#ifdef LOCAL
            //ret[i] = estimator.get_estimate_complex(actual_value);
            ret[i] = estimator.get_estimate(actual_value);
#else
            //ret[i] = estimator.get_estimate_complex(actual_value);
            ret[i] = estimator.get_estimate(actual_value);
#endif
            ret[i] = decode_yield(ret[i]);
            //assert(ret[i] > 1 || ignore_record[i]);
            if(isnan(ret[i]) || isnan(-ret[i])){
                ret[i] = Estimator::normal_avg;
                cntNaN++;
            }
        }
        DBG(cntNaN);
        return ret;
    }
};
//}}}

#ifdef LOCAL
vector<double> random_select;
double calculate_score(vector<double>& predicted_yield)
{
    SimpleAccumulator acc;
    double sum = 0;
    int sz = 0;
    Rep(i, predicted_yield.size()){
        if(frequent_vid.count(data_record[i].variety_id) == 0){
            continue;
        }
        if(ignore_record[i]){
            continue;
        }
        double diff = fabs(predicted_yield[i] - decode_yield(data_record[i].yield));
        if(diff > 25.0){
            diff = 25.0;
        }
        acc.add(diff);
        if(sz < 10){
            cout << predicted_yield[i] << ", " << data_record[i].yield << endl;
        }
        sum += diff * diff;
        sz++;
    }
    DBG(sum);
    DBG(sz);
    //double rmse = sqrt(sum / sz);
    double rmse = acc.get_rmse();
    return 1000000. / rmse;
}

void read_data(string filename, vector<string>& data, int ignore_line = 0)
{
    ifstream input(filename.c_str());
    data.reserve(2000000);

    string s;
    while(getline(input, s))
    {
        ignore_line--;
        if(ignore_line >= 0){
            continue;
        }
        data.push_back(s);
    }
}

bool endsWith(string text, string p){
    if(text.size() < p.size()) return false;
    return text.substr(text.size() - p.size()) == p;
}


struct Outputer{
    int curr;
    int started;
    ofstream *os;
    vector<string> attrs;
    Outputer(ofstream *os)
        :curr(0), started(0), os(os)
    {
    }
    void add_attribute(string attr)
    {
        if(started == 0){
            *os << "@relation xx" << endl;
            started = 1;
        }
        *os << "@attribute " << attr << " numeric" << endl;
        attrs.push_back(attr);
    }
    void add(string attr, double value)
    {
        if(started == 1){
            *os << "@data" << endl;
            started = 2;
        }
        if(!endsWith(attr, attrs[curr])){
            DBG(attrs[curr]);
            DBG(attr);
        }
        assert(endsWith(attr, attrs[curr]));
        curr++;
        *os << value;
        *os << ",";
    }
    void add_end(double value)
    {
        if(curr == SZ(attrs) - 1){
            *os << value << endl;
            curr = 0;
        }
    }
};

int main()
{
    YieldPredictor classifier;
    vector<string> varieties;
    read_data("Varieties.csv", varieties);
    insert_varieties(varieties);
    DBG(frequent_vid.size());

    // read trainingData
    vector<string> trainingData;
    read_data("DataTraining.csv", trainingData);
    random_shuffle(ALL(trainingData));
    //trainingData.resize(50000);
    trim_record(trainingData);
    cerr << "part of record:" << endl;
    Rep(i, 10){
        cerr << data_record[i].toString() << endl;
    }
    DBG(nRecord);

    // read locations
    vector<string> locations;
    read_data("Locations.csv", locations);
    Rep(i, SZ(locations)){
        data_locations[i] = DataLocation(locations[i]);
    }

    // read drought
    vector<string> droughtNOAA;
    read_data("DroughtNOAA.csv", droughtNOAA, 1);
    Rep(i, SZ(droughtNOAA)){
        data_drought[i] = DataDrought(droughtNOAA[i]);
    }
    cerr << "part of record:" << endl;
    Rep(i, 10){
        cerr << data_drought[i].toString() << endl;
    }

    analysis(trainingData, locations, varieties, droughtNOAA);
    cerr << "analysis finished" << endl;

    ignore_record.clear();
#ifdef RUN_TEST
    vector<string> queries;
    cerr << "First serveral query: " << endl;
    Rep(i, nRecord){
        queries.push_back(data_record[i].toQuery());
        if(i < 10){
            cerr << queries[i] << " " << Query(queries[i]).month << "vs" << data_record[i].month << endl;
        }
    }

    Rep(i, nRecord){
        /*
           if(i % 2 != 0){
           ignore_record[i] = true;
           }
           */
        int eid = data_record[i].eid;
        int variety_id = data_record[i].variety_id;
        if(avg_variety[0][variety_id].get_size(eid) == 0){
            ignore_record[i] = true;
        }
        //int loccd = data_record[i].loccd;
        //int cd = get_cd_by_loccd[loccd];
        //int year = data_record[i].y;

        //6-1
        // ignore local year not exist
        //if(avg_loccd_year[0][make_pair(loccd, year)].get_size(eid) == 0){
        //    ignore_record[i] = true;
        //}
        //// ignore cd year
        //if(avg_cd_year[0][make_pair(cd, year)].get_size(eid) == 0){
        //    ignore_record[i] = true;
        //}
        // ignore infrequent loccd
        //if(loccd_set_size[loccd] < LOCCD_TOLERATE){
        //    ignore_record[i] = true;
        //}
    }
    vector<string> droughtMonitor;

    vector<double> predicted_yield = classifier.predictYield(trainingData, droughtMonitor,
            droughtNOAA, locations, varieties, queries);

    double score = calculate_score(predicted_yield);
    cout<<"Score on train set:"<<score<<endl;

    DBG(cond_triple.sz);
    DBG(cond_loccd_year.sz);
    DBG(cond_cd_year.sz);
    DBG(cond_loccd.sz);
    DBG(cond_loccd_drought.sz);
    DBG(cond_other.sz);

    DBG(cond_triple.get_rmse());
    DBG(cond_loccd_year.get_rmse());
    DBG(cond_cd_year.get_rmse());
    DBG(cond_loccd.get_rmse());
    DBG(cond_loccd_drought.get_rmse());
    DBG(cond_other.get_rmse());
#else
    ofstream triple_data("train_triple.arff");
    ofstream loccd_year_data("train_loccd_year.arff");
    ofstream loccd_drought_data("train_loccd_drought.arff");
    ofstream cd_year_data("train_cd_year.arff");
    ofstream other_data("train_other.arff");
    Outputer output_triple(&triple_data);
    Outputer output_loccd_year(&loccd_year_data);
    Outputer output_loccd_drought(&loccd_drought_data);
    Outputer output_cd_year(&cd_year_data);
    Outputer output_other(&other_data);

    //    output_triple.add_attribute("get_avg_loccd_year_knn(64)");
    output_triple.add_attribute("get_triple_avg()*a");
    output_triple.add_attribute("get_avg_loccd_year_v3()*b");
    //output_triple.add_attribute("get_avg_variety_and_loccd_year_v3()");
    output_triple.add_attribute("yield");

    //    output_loccd_year.add_attribute("get_avg_loccd_year_knn(64)");
    output_loccd_year.add_attribute("get_avg_loccd_year_v3()*a");
    output_loccd_year.add_attribute("get_avg_loccd_drought_v3()*b");
    //output_loccd_year.add_attribute("get_avg_variety_and_loccd_year_v3()*c");
    output_loccd_year.add_attribute("yield");

    output_loccd_drought.add_attribute("get_avg_loccd_drought_v3()*a");
    output_loccd_drought.add_attribute("get_avg_cd_year_v3()*b");
    output_loccd_drought.add_attribute("yield");

    output_cd_year.add_attribute("get_avg_cd_year_v3()*a");
    output_cd_year.add_attribute("get_avg_loccd_v3()*b");
    output_cd_year.add_attribute("get_avg_cd_year_v3()");
    output_cd_year.add_attribute("get_avg_loccd_v3()");
    output_cd_year.add_attribute("get_avg_variety_and_loccd_v3()");
    output_cd_year.add_attribute("yield");

    output_other.add_attribute("get_avg_loccd_v3()");

    Rep(i, nRecord){
        if(i % 1000 == 0){
            cerr << "\r" << i;
        }
        //if(rand() % 100 != 0){
        //    continue;
        //}

        int variety_id = data_record[i].variety_id;
        int eid = data_record[i].eid;
        int loccd = data_record[i].loccd;
        int cd = get_cd_by_loccd[loccd];
        int year = data_record[i].y;
        int fullyear = data_record[i].fullyear;
        int month = data_record[i].month;
        double yield = data_record[i].yield;
        Estimator estimator(eid, variety_id, loccd, year, fullyear, data_record[i].grp_rel);

        if(!estimator.has_variety()){
            continue;
        }

#define ADD(a, b) do{a.add(#b, b);}while(0)
        if(estimator.has_triple()){
            double sz = estimator.size_triple() / 2.; // 1,6.548
            double a = get_midpiont(1, 0, sz, 1);
            double b = get_midpiont(0, 1, sz, 1);
            ADD(output_triple, estimator.get_triple_avg()*a);
            ADD(output_triple, estimator.get_avg_loccd_year_v3()*b);
        }if(estimator.has_loccd_year()){
            double sz = estimator.size_loccd_year() / 2.; //4,7.5418, 2,7.5339
            sz = sz * sz; // 4,7.5444, 7.5538
            double a = get_midpiont(1, 0, sz, 1);
            double b = get_midpiont(0, 1, sz, 1);

            ADD(output_loccd_year, estimator.get_avg_loccd_year_v3()*a);
            ADD(output_loccd_year, estimator.get_avg_loccd_drought_v3()*b);
        }if(estimator.has_loccd_drought()){
            double sz = estimator.size_loccd_drought() / 12.; // 8,9.5859, 16,9.6205
            sz = sz * sz; // 144,10.5748, 200, 10.6707
            double a = get_midpiont(1, 0, sz, 1);
            double b = get_midpiont(0, 1, sz, 1);
            ADD(output_loccd_drought, estimator.get_avg_loccd_drought_v3()*a);
            ADD(output_loccd_drought, estimator.get_avg_cd_year_v3()*b);
        }if(estimator.has_cd_year()){
            double sz = estimator.size_cd_year() / 1000.; // 16,11.3454, 32,11.287, 64,11.1996, 1000,10.9978
            sz = sz * sz;
            double a = get_midpiont(1, 0, sz, 1);
            double b = get_midpiont(0, 1, sz, 1);
            ADD(output_cd_year, estimator.get_avg_cd_year_v3()*a);
            ADD(output_cd_year, estimator.get_avg_loccd_v3()*b);
            ADD(output_cd_year, estimator.get_avg_cd_year_v3());
            ADD(output_cd_year, estimator.get_avg_loccd_v3());
            ADD(output_cd_year, estimator.get_avg_variety_and_loccd_v3());
        }{
            ADD(output_other, estimator.get_avg_loccd_v3()); 
            ADD(output_other, estimator.get_avg_variety_and_loccd_v2()); // 10.9708
            //ADD(output_other, estimator.get_avg_variety_and_loccd_v3()); // 11.0523
        }


#define PUSH(a) do{a.add_end(yield);}while(0)
        if(estimator.has_triple()){
            PUSH(output_triple);
        }if(estimator.has_loccd_year()){
            PUSH(output_loccd_year);
        }if(estimator.has_loccd_drought()){
            PUSH(output_loccd_drought);
        }if(estimator.has_cd_year()){
            PUSH(output_cd_year);
        }{
            PUSH(output_other);
        }
#undef PUSH

    }
#endif
    return 0;
}
#endif
