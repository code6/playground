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

    vector<vector<int> > learn(vector<ExpData>& train, 
                               vector<Rep>& rep,
                               map<int, set<int> >& mid2parent,
                               map<int, set<int> >& mid2child) {
        float bias = 0;
        map<int, float>    smid;
        map<int, int>      mid_fix;
        map<Tuple2, float> ly;
        
        map<Tuple3, StatValue> mly;
        map<Tuple3, int>       mly2exp;

        {
            for (int i = 0; i < (int)train.size(); i++) {
                ExpData& d = train[i];
                mly[Tuple3(d.mid, d.loc, d.year)].Update(d.yield);
            }

            for (map<Tuple3, StatValue>::iterator it = mly.begin(); it!=mly.end(); it++) it->second.Summarize();
        }

        { 
            const float lrate = 1e-2;

            for (int r = 0; r < 4; r++) {
                float rmse = 0;
                float rate = lrate/(1.0 + 10*lrate*r);

                random_shuffle(train.begin(), train.end());

                for (int i = 0; i < (int)train.size(); i++) {
                    ExpData& d = train[i];

                    Tuple2 t(d.loc, d.year);

                    float g = d.yield - (bias + ly[t]+ smid[d.mid]);

                    bias        += g*rate*0.1;
                    ly[t]       += rate*(g - ly[t]*0.001);
                    smid[d.mid] += rate*(g - smid[d.mid]*0.001);

                    rmse += squ(g);
                }

                rmse = sqrt(rmse/(train.size() + 1e-3));

                printf("ROUND : %d, BIAS : %.3f, RMSE : %.3f, RATE : %.3f\n", r, bias, rmse, rate);
            }
            
            for (map<int, float>::iterator it = smid.begin(); it != smid.end(); ++it) {
                mid_fix[it->first] = 1;
            }
        }
        
        map<Tuple3, float> smly;
        map<Tuple3, float> sely;
     
        { 
            const float lrate = 1e-1;

            for (int r = 0; r < 5; r++) {
                float rmse = 0;
                float rate = lrate/(1.0 + 10*lrate*r);

                random_shuffle(train.begin(), train.end());

                for (int i = 0; i < (int)train.size(); i++) {
                    ExpData& d = train[i];

                    Tuple3 t1(d.mid, d.loc, d.year);
                    Tuple3 t2(d.exp, d.loc, d.year);

                    float g = d.yield - (bias + smly[t1]+ sely[t2]);

                    smly[t1] += rate*(g - smly[t1]*0.001);
                    sely[t2] += rate*(g - sely[t2]*0.001);

                    rmse += squ(g);
                }

                rmse = sqrt(rmse/(train.size() + 1e-3));

                printf("ROUND : %d, BIAS : %.3f, RMSE : %.3f, RATE : %.3f\n", r, bias, rmse, rate);
            }
        }
         
        {
           for (int r = 0; r < 4; r++) {
                float rmse = 0;
                float rmse_not_fix = 0;
                int   count = 0;
                float rate = 0.1;
                
                for (map<int, set<int> >::iterator it = mid2parent.begin(); it != mid2parent.end(); ++it) {
                    float left  = smid[it->first];
                    float right = 0;

                    bool all_fix = true;
                    if (mid_fix[it->first] == 0) all_fix = false;

                    for (set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                        right += smid[*it2];
                        if (mid_fix[*it2] == 0) all_fix = false;
                    }

                    float inv = 1.0/(it->second.size()+1e-3);
                    right *= inv; 

                    float g = left - right;
                    rmse += squ(g);

                    if (!all_fix) {
                        rmse_not_fix += squ(g);
                        count += 1;

                        if (mid_fix[it->first] == 0) smid[it->first] += -g*rate;
                        for (set<int>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
                            if (mid_fix[*it2] == 0)  smid[*it2] += g*rate*inv;
                        }
                    }
                }
                rmse = sqrt(rmse/(mid2parent.size()+1e-3));
                rmse_not_fix = sqrt(rmse_not_fix/(count+1e-3));
                printf("RMSE : %.3f %d RMSE_NOT_FIX : %.3f %d\n", rmse, (int)mid2parent.size(), rmse_not_fix, count);
            }
        }

        vector<vector<int> > result;

        for (int i = 0; i < (int)rep.size(); i++) {
            Rep& r = rep[i];

            vector<int> tr;

            float ly_bias = 0;

            if (ly.find(Tuple2(r.loc, r.year)) != ly.end()) {
                ly_bias = ly[Tuple2(r.loc, r.year)];
            }

            int mly_count = 0;
            {
                for (int j = 0; j < (int)r.materials.size(); j++) {
                    MaterialInfo& material = r.materials[j];

                    bool has_mly = false;
                    for (int k = 0; k < (int)material.mid.size(); k++) {
                        int mid = material.mid[k];

                        if (mly.find(Tuple3(mid, r.loc, r.year)) != mly.end()) {
                            has_mly = true;
                        }
                    }

                    if (has_mly) mly_count++;
                }

                if (gDebug) printf("REP %d MLY %d\n", i, mly_count);
            }

            for (int j = 0; j < (int)r.materials.size(); j++) {
                MaterialInfo& material = r.materials[j];

                float v   = 0;
                float w   = 1e-2;
                float wei = 0;

                float v_mly = 0;
                float w_mly = 0;

                if (gDebug) printf("REP : %d MAT : %d PED : %s\n", i, j, material.pedigree.c_str());

                for (int k = 0; k < (int)material.mid.size(); k++) {
                    int mid = material.mid[k];

                    if (smid.find(mid) != smid.end() && mid_fix[mid] == 1) {
                        wei = 1.0f;

                        if (smly.find(Tuple3(mid, r.loc, r.year)) != smly.end()) {
                            if (gDebug) printf("%d %d %d : (%d, %d, %d)\n", i, j, k, mid, r.loc, r.year);

                            v_mly += (smly[Tuple3(mid, r.loc, r.year)] + ly_bias + bias) * wei;
                            w_mly += wei;
                        }

                        v += wei * smid[mid];
                        w += wei;

                        if (gDebug) printf("ADD_MID : %d %.3f %.3f\n", mid, smid[mid], wei);
                    }
                }

                for (int k = 0; k < (int)material.parent.size(); k++) {
                    int mid = material.parent[k];

                    wei = 0.1f/(material.parent.size()+1e-3);

                    if (smid.find(mid) != smid.end()) {
                        v += wei * smid[mid];
                        w += wei;

                        if (gDebug) printf("ADD_PAR : %d %.3f %.3f\n", mid, smid[mid], wei);
                    }

                    { 
                        set<int>& parent = mid2parent[mid];
                        wei = 0.1f/(parent.size()+1e-3);
                        for (set<int>::iterator it = parent.begin(); it != parent.end(); ++it) {
                            if (smid.find(*it) != smid.end()) {
                                v += wei * smid[*it];
                                w += wei;
                                
                                if (gDebug) printf("ADD_PARPAR : %d %.3f %.3f\n", *it, smid[*it], wei);
                            }
                        }
                    }
                }

                // prior
                v += -2 * 0.1;
                w += 0.1;

                int score = (int)(100*(v/w + ly_bias + bias));

                if (w_mly > 0) {
                    int s2 = (int)(100*v_mly/w_mly); 
                    
                    if (gDebug) printf("SET S2: %d %d\n", score, s2);
 
                    score = (int)(s2*0.7 + score*0.3);
                }

                if (score < 0) score = 0;

                if (gDebug) printf("FNIAL_SCORE: %d %.3f %.3f\n", score, ly_bias, bias);

                tr.push_back(score);
            }

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

        if (gDebug) {
            for (map<int, set<int> >::iterator it = mid2parent.begin(); it != mid2parent.end(); ++it) {
                int mid = it->first;
                printf("MID : %d PARENT : ", mid);

                set<int>& parent = it->second;
                for (set<int>::iterator it2 = parent.begin(); it2!=parent.end(); ++it2) {
                    printf("%d,", *it2);
                }
                printf("\n");
            }

            for (map<int, set<int> >::iterator it = mid2child.begin(); it != mid2child.end(); ++it) {
                int mid = it->first;
                printf("MID : %d CHILD : ", mid);

                set<int>& child = it->second;
                for (set<int>::iterator it2 = child.begin(); it2!=child.end(); ++it2) {
                    printf("%d,", *it2);
                }
                printf("\n");
            }
        }

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
