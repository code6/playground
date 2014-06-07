#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <set>
using namespace std;

const int gDebug = 0; 
const int gTrainSel = 10;

const int kMidPerRep = 36;

void parse_line(const char* line, const char* out[], int col) {
    const char* p = line;

    out[0] = p;
    for (int j = 1; j < col; j++) {
        if (p) p = strstr(p, ",");
        if (p) p++;
        out[j] = p;
    }
}

void load_file(const char* filename, vector<string>& out) {
    FILE* file = fopen(filename, "r");
    {
        char buf[1024];
        while (fgets(buf, sizeof(buf), file)) {
            int len = strlen(buf);
            buf[len-1] = 0;
            out.push_back(buf);
        }
    }
    fclose(file);
}

struct Tuple2 {
    Tuple2(int a, int b) : y1(a), y2(b) {}
    bool operator < (const Tuple2& t) const {
        if (y1 < t.y1) return true; if (y1 > t.y1) return false;
        return y2 < t.y2;
    }
    int y1,y2; 
};

struct Tuple3 {
    Tuple3(int a, int b, int c) : y1(a), y2(b), y3(c) {}
    bool operator < (const Tuple3& t) const {
        if (y1 < t.y1) return true; if (y1 > t.y1) return false;
        if (y2 < t.y2) return true; if (y2 > t.y2) return false;
        return y3 < t.y3;
    }
    int y1,y2,y3; 
};

struct ExpData {
    int    exp;
    int    loc;  
    int    rep;
    int    mid;   
    float  yield; 
    int    year;  

    int    uid;
    int    tid;

    int GetHerb(const char* field) {
        if (strncasecmp(field, "conv", 4) == 0) {
            return 1;
        } else if (strncasecmp(field, "rr1", 3)==0) {
            return 2;
        } else if (strncasecmp(field, "rr2y", 4)==0) {
            return 3;
        }
        return 0;
    }

    void ParseTrain(const char* line) {
        const char* cols[7];
        parse_line(line, cols, 7);

        exp   = atoi(cols[0]);
        loc   = atoi(cols[1]);	
        rep   = atoi(cols[2]);
        mid   = atoi(cols[3]);
        yield = atof(cols[4]);
        year  = atoi(cols[6]);
    }

    void UpdateYear(int y) { if (year == 0) year = y; }
};

struct StatValue {
    StatValue(): avg(0), sum(0), count(0) { }
    void Update(float v) { sum += v; count += 1; }
    void ClearSumCount()  { sum = 0; count = 0; }
    void Summarize() { avg=sum/count; }
    void Print(const char* name) { printf("%s : (%7.3f %.1f)\n", name, avg, count); }
    float avg;
    float sum;
    float count;
};

float rand_float(float l, float r){ return l+(rand()%10000/10000.)*(r-l); }

float squ(float f) { return f*f; }

float inner_product(const vector<float>& a, const vector<float>& b) {
    float sum = 0;
    for (int i = 0; i < (int)a.size(); i++) sum += a[i] * b[i];
    return sum;
}

void print_some_elem(vector<string>& in, const char* name, int num = 1) {
    printf("%s : %d\n", name, (int)in.size());
    for (int i = 0; i < num && i < (int)in.size(); i++) { printf("\t%s\n", in[i].c_str()); }
    fflush(stdout);
}       

void parse_pedigree(const string& ped, vector<int>& parent) {
    const char* p = ped.c_str();
    while (*p) {
        int mid = atoi(p);
        if (mid!=0) parent.push_back(mid);

        while (*p && *p != '/') p++;
        while (*p && !isdigit(*p)) p++;
    }
}

void load_material(const vector<string>& material, 
                   map<string, vector<int> >& parent2mid,
                   map<int, set<int> >& mid2parent,
                   map<int, set<int> >& mid2child) {
    const char* cols[4];
    char line[256];

    for (int i = 0; i < (int)material.size(); i++) {
        parse_line(material[i].c_str(), cols, 4);

        int mid = atoi(cols[0]);
        int len = cols[2] - cols[1] - 1;
        strncpy(line, cols[1], len);
        line[len] = 0;

        parent2mid[line].push_back(mid);

        vector<int> parent;
        parse_pedigree(line, parent);

        for (int j = 0; j < (int)parent.size(); j++) {
            mid2parent[mid].insert(parent[j]);
            mid2child[parent[j]].insert(mid);
        }
    }
}

struct MaterialInfo {
    string pedigree; 
    vector<int> mid;
    vector<int> parent;

    void AddUid(int u, float w) { uid.push_back(u); wei.push_back(w); }

    void ParsePedigree(const string& ped) {
        pedigree = ped;
        parse_pedigree(pedigree, parent);
    }

    vector<float> wei;
    vector<int>   uid;
};

struct Rep {
    int loc;
    int year;
    vector<MaterialInfo> materials;

    int tid;
    string raw_string;

    void Print() {
        printf("Raw: %s\n", raw_string.c_str());
        printf("%d, %d, ", loc, year);
        for (int i = 0; i < (int)materials.size(); i++) {
            const MaterialInfo& minfo = materials[i];
            printf("%s : ,", minfo.pedigree.c_str());
            for (int j = 0; j < (int)minfo.mid.size(); j++) {
                printf("%d,", minfo.mid[j]);
            }
        }
        printf("\n");
    }
};

class PedigreeYieldPredictor {
public:
    void parse_rep(const vector<string>& raw_reps, map<string, vector<int> >& parent2mid, vector<Rep>& all_rep) {
        int mid_count = 0;
        int mid_null_count = 0;
        int mid_known_count = 0;

        const int kColNum = 2 + kMidPerRep;
        const char* cols[1+kColNum];
        char line[256];
        for (int i = 0; i < (int)raw_reps.size(); i++) {
            parse_line(raw_reps[i].c_str(), cols, 2+kMidPerRep);

            cols[kColNum] = cols[kColNum-1];
            while (*cols[kColNum]!=',' && *cols[kColNum]!=0) cols[kColNum]++;
            cols[kColNum]++;

            Rep rep;
            rep.loc  = atoi(cols[0]);
            rep.year = atoi(cols[1]);
            rep.raw_string = raw_reps[i];

            for (int j = 0; j < kMidPerRep; j++) {
                int len = cols[j+3] - cols[j+2] - 1;
                strncpy(line, cols[j+2], len);
                line[len] = 0;

                MaterialInfo material;
                material.ParsePedigree(line);

                if (strcasecmp(line, "NULL")==0) {
                    mid_null_count++;
                } else {
                    if (parent2mid.find(line)!=parent2mid.end()) {
                        mid_known_count++;
                        material.mid = parent2mid[line];
                    }
                }

                rep.materials.push_back(material);
            }

            all_rep.push_back(rep);

            mid_count += kMidPerRep;
        }

        printf("mid_count : %d, mid_null_count : %d %.3f, mid_known_count : %d %.3f\n",
                mid_count, mid_null_count, (float)mid_null_count/mid_count, 
                mid_known_count, (float)mid_known_count/mid_count);

    }

    void parse_train(vector<string>& train_data, vector<ExpData>& data) {
        for (int i = 0; i < (int)train_data.size(); i++) {
            ExpData exp;
            exp.ParseTrain(train_data[i].c_str());

            data.push_back(exp);
        }
    }

    // yield(l,y,v) = bias + bias(l,y) + bias(v)
    void learn_model_ly_v(vector<ExpData>&    train, 
                          float&              bias,  
                          map<Tuple2, float>& bias_ly,      
                          map<int, float>&    bias_mid,
                          map<int, int>&      mid_fix) {
        const float lrate = 1e-2;

        for (int r = 0; r < 4; r++) {
            float rmse = 0;
            float rate = lrate/(1.0 + 10*lrate*r);

            random_shuffle(train.begin(), train.end());

            for (int i = 0; i < (int)train.size(); i++) {
                ExpData& d = train[i];

                Tuple2 t(d.loc, d.year);

                float g = d.yield - (bias + bias_ly[t]+ bias_mid[d.mid]);

                bias            += g*rate*0.1;
                bias_ly[t]      += rate*(g - bias_ly[t]*0.001);
                bias_mid[d.mid] += rate*(g - bias_mid[d.mid]*0.001);

                rmse += squ(g);
            }

            rmse = sqrt(rmse/(train.size() + 1e-3));

            printf("ROUND : %d, BIAS : %.3f, RMSE : %.3f, RATE : %.3f\n", r, bias, rmse, rate);
        }

        for (map<int, float>::iterator it = bias_mid.begin(); it != bias_mid.end(); ++it) {
            mid_fix[it->first] = 1;
        }
    }

    // yield = bias + bias(mid, loc, year) + bias(exp, loc, year)
    void learn_model_mly(vector<ExpData>&    train,
                         const float         bias,
                         map<Tuple3, float>& bias_mly) {
        map<Tuple3, float> ely;

        const float lrate = 1e-1;

        for (int r = 0; r < 5; r++) {
            float rmse = 0;
            float rate = lrate/(1.0 + 10*lrate*r);

            random_shuffle(train.begin(), train.end());

            for (int i = 0; i < (int)train.size(); i++) {
                ExpData& d = train[i];

                Tuple3 t1(d.mid, d.loc, d.year);
                Tuple3 t2(d.exp, d.loc, d.year);

                float g = d.yield - (bias + bias_mly[t1]+ ely[t2]);

                bias_mly[t1] += rate*(g - bias_mly[t1]*0.001);
                ely[t2] += rate*(g - ely[t2]*0.001);

                rmse += squ(g);
            }

            rmse = sqrt(rmse/(train.size() + 1e-3));

            printf("ROUND : %d, BIAS : %.3f, RMSE : %.3f, RATE : %.3f\n", r, bias, rmse, rate);
        }
    }

    void smooth_bias_mid(map<int, float>&     bias_mid,
                         map<int, set<int> >& mid2parent,
                         map<int, int>&       mid_fix) {
        for (int r = 0; r < 4; r++) {
            float rmse = 0;
            float rate = 0.1;

            for (map<int, set<int> >::iterator it = mid2parent.begin(); it != mid2parent.end(); ++it) {
                float left  = bias_mid[it->first];
                float right = 0;
                float inv   = 1.0/(it->second.size()+1e-3);

                for (set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                    right += bias_mid[*it2];
                }
                right *= inv;

                float g = left - right;

                // update
                if (mid_fix[it->first] == 0) bias_mid[it->first] += -g*rate;
                for (set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                    if (mid_fix[*it2] == 0)  bias_mid[*it2] += g*rate*inv;
                }
                
                rmse += squ(g);
            }
            rmse = sqrt(rmse/(mid2parent.size()+1e-3));
            printf("ROUND : %d, RMSE : %.3f, MID : %d\n", r, rmse, (int)mid2parent.size());
        }
    }

    int predict_y1(MaterialInfo&        material,
                   map<int, set<int> >& mid2parent,
                   const float          bias,  
                   map<int, float>&     bias_mid,
                   map<int, int>&       mid_fix) {

        float v   = 0;
        float w   = 1e-2;
        float wei = 0;

        // consider brothers
        for (int k = 0; k < (int)material.mid.size(); k++) {
            int mid = material.mid[k];

            if (bias_mid.find(mid) != bias_mid.end() && mid_fix[mid] == 1) {
                wei = 1.0f;

                v += wei * bias_mid[mid];
                w += wei;
            }
        }

        // consider parents
        for (int k = 0; k < (int)material.parent.size(); k++) {
            int mid = material.parent[k];

            wei = 0.1f/(material.parent.size()+1e-3);

            if (bias_mid.find(mid) != bias_mid.end()) {
                v += wei * bias_mid[mid];
                w += wei;
            }

            // consider grandparent
            { 
                set<int>& parent = mid2parent[mid];
                wei = 0.1f/(parent.size()+1e-3);
                for (set<int>::iterator it = parent.begin(); it != parent.end(); ++it) {
                    if (bias_mid.find(*it) != bias_mid.end()) {
                        v += wei * bias_mid[*it];
                        w += wei;
                    }
                }
            }
        }

        // prior
        v += -2 * 0.1;
        w += 0.1;

        int score = (int)(100*(v/w + bias));
        return score;
    }
    
    int predict_y2(MaterialInfo& material, 
                   int loc, int year,
                   const float bias,
                   map<Tuple3, float>& bias_mly) {
        float v = 0;
        float w = 0;

        for (int k = 0; k < (int)material.mid.size(); k++) {
            int   mid = material.mid[k];
            float wei = 1.0;

            if (bias_mly.find(Tuple3(mid, loc, year)) != bias_mly.end()) {
                v += (bias_mly[Tuple3(mid, loc, year)] + bias) * wei;
                w += wei;
            }
        }

        int score = 0;

        if (w> 0) {
            score = (int)(100*v/w); 
        }

        return score;
    }

    vector<int> predict_rep(Rep& r, 
                            map<int, set<int> >& mid2parent,
                            const float          bias,
                            map<int, float>&     bias_mid,
                            map<Tuple2, float>&  bias_ly,
                            map<Tuple3, float>&  bias_mly,
                            map<int, int>&       mid_fix) {
        vector<int> result;

        float b = bias + bias_ly[Tuple2(r.loc, r.year)];

        for (int j = 0; j < (int)r.materials.size(); j++) {
            MaterialInfo& material = r.materials[j];

            int y1 = predict_y1(material, mid2parent, b, bias_mid, mid_fix);
            int y2 = predict_y2(material, r.loc, r.year, b, bias_mly);

            int score = y1;
            if (y2> 0) {
                score = (int)(y2*0.7 + y1*0.3);
            }

            if (score < 0) score = 0;

            result.push_back(score);
        }

        return result;
    }

    vector<vector<int> > learn(vector<ExpData>& train, 
                               vector<Rep>& rep,
                               map<int, set<int> >& mid2parent,
                               map<int, set<int> >& mid2child) {
        float              bias = 0;
        map<int, float>    bias_mid;
        map<Tuple2, float> bias_ly;
        map<Tuple3, float> bias_mly;
        map<int, int>      mid_fix;

        learn_model_ly_v(train, bias, bias_ly, bias_mid, mid_fix);
       
        smooth_bias_mid(bias_mid, mid2parent, mid_fix); 
      
        learn_model_mly(train, bias, bias_mly);
      
        vector<vector<int> > result;

        for (int i = 0; i < (int)rep.size(); i++) {
            Rep& r = rep[i];
            
            vector<int> tr = predict_rep(r, mid2parent, bias, bias_mid, bias_ly, bias_mly, mid_fix);

            result.push_back(tr);
        }

        return result;
    }

    vector<string> predictYield(vector<string>& trainingData, 
                                vector<string>& droughtMonitor, 
                                vector<string>& droughtNOAA, 
                                vector<string>& locations, 
                                vector<string>& material, 
                                vector<string>& reps) {
        int rep_num = (int)reps.size();
        vector<string> result;

        {
            print_some_elem(trainingData,   "trainingData");
            print_some_elem(droughtMonitor, "droughtMonitor");
            print_some_elem(droughtNOAA,    "droughtNOAA");
            print_some_elem(locations,      "locations");
            print_some_elem(material,       "material");
            print_some_elem(reps,           "reps");
        }

        map<string, vector<int> > parent2mid;
        vector<Rep>      all_rep;
        vector<ExpData>  train;
        map<int, set<int> > mid2parent;
        map<int, set<int> > mid2child;

        load_material(material, parent2mid, mid2parent, mid2child);
        parse_rep(reps, parent2mid, all_rep);
        parse_train(trainingData, train);

        vector<vector<int> > total_est = learn(train, all_rep, mid2parent, mid2child);

        // transfer result to string
        {
            for (int i = 0; i < rep_num; i++) {
                char buffer[32];
                string res;
                for (int j = 0; j < kMidPerRep; j++) {
                    res += (sprintf(buffer, "%d,", total_est[i][j]), buffer);
                }
                result.push_back(res);
            }
        }

        return result;
    }
};

void save_file(const char* filename, vector<string>& out) {
    FILE* file = fopen(filename, "w");

    for (int i = 0; i < (int)out.size(); i++)
    {
        fprintf(file, "%s\n", out[i].c_str());	
    }

    fclose(file);
}


void build_reps(const vector<string>& valid_reps, 
        const vector<string>& train_data, 
        const vector<string>& material,
        vector<string>& sel_data, 
        vector<string>& reps,
        vector<string>& reps_wo_truth)
{
    {
        sel_data.clear();
        reps.clear();
    }

    map<int, int> selected_exp;
    // (exp, loc, rep) => (mid, yield, year)[]
    map<Tuple3, vector<string> > selected_reps;

    const char* cols[7];
    char line[256];

    for (int i = 0; i < (int)valid_reps.size(); i++) {
        parse_line(valid_reps[i].c_str(), cols, 3);

        int exp = atoi(cols[0]);
        int loc = atoi(cols[1]);
        int rep = atoi(cols[2]);

        if (rand()%40==0) {
            selected_reps[Tuple3(exp, loc, rep)];
            selected_exp[exp] = 1;
        }
    }

    int i = 0;
    while ( i < (int)train_data.size()) {
        parse_line(train_data[i].c_str(), cols, 7);

        int exp   = atoi(cols[0]);
        int start = i;

        for (; i < (int)train_data.size(); i++) {
            int tmp_exp_id = atoi(train_data[i].c_str());
            if (tmp_exp_id != exp) break;
        }

        if (selected_exp[exp]) {
            // ExperimentID, LOCCD, REPNO, MaterialID, HERB, YGSMN, MRTYN, RM and PlantDate
            for (int j = start; j < i; j++) {
                parse_line(train_data[j].c_str(), cols, 7);

                int exp = atoi(cols[0]);
                int loc = atoi(cols[1]);
                int rep = atoi(cols[2]);

                if (selected_reps.find(Tuple3(exp, loc, rep)) != selected_reps.end()) {
                    int l1 = cols[5]-cols[3];
                    int l2 = cols[0] + strlen(train_data[j].c_str())-cols[6];
                    strncpy(line, cols[3], l1);
                    strncpy(line+l1, cols[6], l2);
                    line[l1+l2] = 0;

                    selected_reps[Tuple3(exp, loc, rep)].push_back(line);
                } 
            }
        } else if (rand()%10 < gTrainSel) {
            for (int j = start; j < i; j++) {
                sel_data.push_back(train_data[j]);
            }
        }
    }

    map<int, string> mid2parent;
    for (int i = 0; i < (int)material.size(); i++) {
        parse_line(material[i].c_str(), cols, 4);

        int mid = atoi(cols[0]);
        int len = cols[2] - cols[1] - 1;
        strncpy(line, cols[1], len);
        line[len] = 0;

        mid2parent[mid] = line;
    }

    for (map<Tuple3, vector<string> >::iterator it = selected_reps.begin();
            it != selected_reps.end();
            ++it) {
        const Tuple3&         elr   = it->first;  // (exp,loc,rep)
        const vector<string>& minfo = it->second;

        string rep;
        string truth;

        // get loc
        rep += (sprintf(line, "%d,", elr.y2), line);

        if (minfo.size() != 36) {
            printf("WRONG MINFO SIZE %d\n", (int)minfo.size());
            continue;
        }

        for (int i = 0; i < (int)minfo.size(); i++) {
            parse_line(minfo[i].c_str(), cols, 3);

            // get year
            if (i==0) {
                rep += (snprintf(line, cols[0] + strlen(minfo[i].c_str())-cols[2], "%s", cols[2]), line);
            }

            int   mid   = atoi(cols[0]);
            float yield = atof(cols[1]);
            rep += (sprintf(line, ",%s", mid2parent[mid].c_str()), line);

            truth += (sprintf(line, ",%d,%f", mid, yield), line);
        }

        reps_wo_truth.push_back(rep);

        rep = (sprintf(line, "%d,%d,%d,", elr.y1, elr.y2, elr.y3), line) + rep;
        reps.push_back(rep+truth);
    }
}

float Compare(int a, int b) {
    if (a < b) return 0.0f;
    if (a > b) return 1.0f;
    return 0.5f;
}

float GetScore(int* est, float* truth) {
    float score = 0.0f;

    for (int i = 0; i < kMidPerRep; i++) {
        for (int j = i+1; j < kMidPerRep; j++) {
            float cmp_real = Compare((int)(truth[i]*10000.0), (int)(truth[j]*10000.0));
            float cmp_est  = Compare(est[i], est[j]);

            if (cmp_real == 0.5f || cmp_est == 0.5f) {
                score += 0.5f;            
            } else {
                score += 1.0 - fabs(cmp_real - cmp_est);
            }

            // printf("%.3f %.3f %.3f, %.3f %.3f\n", cmp_real, cmp_est, score, truth[i], truth[j]);
        }
    }

    score = score * 2.0f / (kMidPerRep*(kMidPerRep-1));

    return score;
}

int main(int argc, char* argv[]) {
    const char* train_file = "DataTraining.csv";
    const char* loc_file   = "Locations.csv";
    const char* valid_file = "ValidReps.csv";
    const char* material_file = "Material.csv";

    int kRound = 3;

    vector<string> train_data;
    vector<string> dry_mon;
    vector<string> dry_noaa;
    vector<string> locations;
    vector<string> material;
    vector<string> valid_reps;

    vector<string> train_data_sel[kRound];
    vector<string> reps[kRound];
    vector<string> reps_wo_truth[kRound];

    load_file(train_file, train_data);
    load_file(loc_file,   locations);
    load_file(valid_file, valid_reps);
    load_file(material_file, material);

    for (int r = 0; r < kRound; r++) {
        build_reps(valid_reps, train_data, material, train_data_sel[r], reps[r], reps_wo_truth[r]);
    }

    float total_err = 0;
    const char* cols[5+3*kMidPerRep];
    char line[256];

    for (int r = 0; r < kRound; r++) {
        printf("--------------------------------------\n");
        printf("ROUND : %d\n", r);

        PedigreeYieldPredictor yp;
        vector<string> result = yp.predictYield(train_data_sel[r], dry_mon, dry_noaa, locations, material, reps_wo_truth[r]);	

        float err = 0;
        for (int i = 0; i < (int)result.size(); i++) {
            int    est[kMidPerRep];
            int    mid[kMidPerRep];
            float  truth[kMidPerRep];
            string pedigree[kMidPerRep];

            parse_line(result[i].c_str(), cols, kMidPerRep);
            for (int j = 0; j < kMidPerRep; j++) {
                est[j] = atoi(cols[j]);
            }

            parse_line(reps[r][i].c_str(), cols, 5+3*kMidPerRep);
            for (int j = 0; j < kMidPerRep; j++) {
                truth[j] = atof(cols[5+kMidPerRep+2*j+1]); 
                mid[j]   = atoi(cols[5+kMidPerRep+2*j]);  

                int len = cols[j+6] - cols[j+5] - 1;
                strncpy(line, cols[j+5], len);
                line[len] = 0;
                pedigree[j] = line;
            }

            float terr = GetScore(est, truth);

           // printf("REP[%d] TERR %.3f %s\n", i, terr, reps[r][i].c_str());
            if (gDebug) {
                printf("RESULT : %s\n", result[i].c_str());
                printf("REPS   : %s\n", reps[r][i].c_str());
                printf("TERR   : %.5f\n", terr);

                for (int k = 0; k < kMidPerRep; k++) {
                    printf("%d, %s, %.3f, %d\n", mid[k], pedigree[k].c_str(), truth[k], est[k]);
                }
            }

            err += terr;
        }

        err /= (int)result.size();

        printf("ERROR : %.5f\n", err);

        {
            save_file("Train", train_data_sel[r]);	
        }

        total_err += err;
    }

    total_err /= kRound;
    printf("TOTAL_ERROR : %.4f\n", total_err);

    return 0;
}
