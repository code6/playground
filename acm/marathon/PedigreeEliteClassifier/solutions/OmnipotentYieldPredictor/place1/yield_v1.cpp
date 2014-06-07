#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int gDebug = 0;

void parse_line(const char* line, const char* out[], int col) {
	const char* p = line;

	out[0] = p;
	for (int j = 1; j < col; j++) {
		if (p) p = strstr(p, ",");
		if (p) p++;
		out[j] = p;
	}
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

struct StatValue {
	StatValue(): avg(0), sum(0), count(0) { }
	void Update(double v) { sum += v; count += 1; }
	void ClearSumCount()  { sum = 0; count = 0; }
	void Summarize() { avg=sum/count; }
	void Print(const char* name) { printf("%s : (%7.3f %.1f)\n", name, avg, count); }
	double avg;
	double sum;
	double count;
};

struct ExpData {
	int    exp;
	int    loc;   
	int    mid;   
	int    year;  
	int    herb;
	double yield; 

	int    uid;
	int    tid;

	int GetHerb(const char* field)
	{
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
		const char* cols[9];
		parse_line(line, cols, 9);

		exp   = atoi(cols[0]);
		loc   = atoi(cols[1]);	
		mid   = atoi(cols[3]);
		year  = atoi(cols[8]);
		herb  = GetHerb(cols[4]);
		yield = atof(cols[5]);
	}

	void ParseQuery(const char* line) {
		const char* cols[8];
		parse_line(line, cols, gDebug?8:7);

		exp  = atoi(cols[0]);
		loc  = atoi(cols[1]);
		mid  = atoi(cols[3]);
		year = atoi(cols[6]);
		herb = GetHerb(cols[4]);
		
		yield = gDebug ? atof(cols[7]) : 0.0f;
	}


	void UpdateYear(int y) { if (year == 0) year = y; }

};

double rand_double(double l,double r){ return l+(rand()%10000/10000.)*(r-l); }

double squ(double f) { return f*f; }

double inner_product(const vector<double>& a, const vector<double>& b) {
	double sum = 0;
	for (int i = 0; i < (int)a.size(); i++) sum += a[i] * b[i];
	return sum;
}

struct Sample {
    int    user, item;
    double y;

    Sample(double v, int u, int i) { y = v; user = u; item = i; }
};

// est(u,i) = bias + b(u) + b(i) + p(u)*q(i)
// loss     = (r(u,i) - est(u,i))^2 
//            + lamda       * (p(u)^2 + p(q)^2)
//		      + bias_lambda * (b(u)^2 + b(i)^2)
// e(u,i)   = r(u,i) - est(u,i) 
// q(i)     <- q(i) + lrate * (e(u,i)*p(u) - lamda*qi)
// b(i)     <- b(i) + lrate * (e(u,i) - bias_lambda*b(i))
struct MFMachine 
{
    int    factor;
    double lambda, bias_lambda;
    double lrate;
    int    nu, ni;
    double loss_;
	double rmse_;
    
	double bias;
	vector<double> bias_user, bias_item;
	vector<vector<double> > user, item;
    
	vector<Sample> train;

    MFMachine(){}
	
    MFMachine(int factor,double lambda,double lrate,int nu,int ni)
		: factor(factor), lambda(lambda), bias_lambda(lambda*0.01), lrate(lrate), nu(nu), ni(ni)
	{
        bias=0;
       
        for (int i=0; i<nu; i++) {
            vector<double> t;
            for (int j=0;j<factor;j++) t.push_back(rand_double(-1, 1));
            user.push_back(t);
			bias_user.push_back(rand_double(-1, 1));
        }
		
        for (int i=0; i<ni; i++) {
            vector<double> t;
            for (int j=0;j<factor;j++) t.push_back(rand_double(-1, 1));
            item.push_back(t);
			bias_item.push_back(rand_double(-1, 1));
        }
    }
	
    void AddSample(const Sample& t) { train.push_back(t); }

    vector<double> Evaluate(vector<Sample>& query){
        vector<double> res;
        for (int i = 0; i < (int)query.size(); i++) res.push_back(EvaluateSample(query[i]));
        return res;
    }

    void Shuffle() { random_shuffle(train.begin(), train.end()); }

	void Train(int round) {
		MFMachine last_mat;
		double    last_loss = 1e100;
	
		double    lr0 = lrate;
	
		for (int r = 1; r <= round; r++){
			last_mat = (*this);
			lrate    = lr0/(1.0 + r*lr0);
	
			Shuffle();
			Train();

			printf("Round = %d RMSE(Train) = %.3f time = %6.3f bias=%.3f lrate=%.3f\n",
					r, rmse(), clock()/(double)CLOCKS_PER_SEC, bias, lrate);

			if (loss() != loss() || loss() > last_loss) {
				(*this) = last_mat;
				lrate *= 0.8;
			} else {
				last_loss = loss();
			}
		}
	}

    void Train() {
        loss_ = 0;
        rmse_ = 0;
		
        for (int i = 0; i < (int)train.size(); i++) {
            Stochastic(train[i]);
            if (loss_ != loss_) {
				printf("STOP : %d, %.3f\n", i, loss_);
				return;
			}
        }
		
		for (int i = 0; i < (int)user.size(); i++) {
			loss_ += bias_lambda * squ(bias_user[i]);
			loss_ += lambda * inner_product(user[i], user[i]);
		}
		
		for (int i = 0; i < (int)item.size(); i++) { 
			loss_ += bias_lambda * squ(bias_item[i]);
			loss_ += lambda * inner_product(item[i], item[i]);
		}

		rmse_ = sqrt(rmse_/train.size());
    }

    inline double EvaluateSample(Sample& t) {
        return bias + bias_user[t.user]+ bias_item[t.item] 
		       + inner_product(user[t.user], item[t.item]);
    }

    inline void Stochastic(Sample& t) {
        double e = EvaluateSample(t);
		double g = t.y - e;
		
		loss_ += g*g;
        rmse_ += min(625., g*g);
      
		int uid = t.user;
		int tid = t.item;

		vector<double> U = user[uid];
		vector<double> V = item[tid];

		for (int j=0; j<factor; j++) user[uid][j] += lrate * (V[j]*g-user[uid][j]*lambda); 
		bias_user[uid] += lrate * (g - bias_user[uid]*bias_lambda);

		for (int j=0; j<factor; j++) item[tid][j] += lrate * (U[j]*g-item[tid][j]*lambda);
		bias_item[tid] += lrate * (g - bias_item[tid]*bias_lambda);
	
		bias += lrate * g;
    }

    double loss() { return loss_; }
    double rmse() { return rmse_; }
};


// Yield(loc, mid, year) = F(loc, year) + F(mid)
class OmnipotentYieldPredictor {
public:
	map<Tuple3, StatValue> lmy; 
	map<Tuple3, StatValue> lme;
	map<Tuple2, StatValue> ly;
	map<int,    StatValue> smid;
	map<int,    StatValue> sloc;
	map<int,    StatValue> syear;
	StatValue    avg;
	StatValue    m_avg[4];

	map<int,    int>       exp2year;

	map<int, int> loc2lati;
	map<Tuple2, StatValue> latiy;

	int lym_count;
	int ly_count[3];
	int m_count[2];

	void print_some_elem(vector<string>& in, const char* name) {
		printf("%s : %d\n", name, (int)in.size());
		if (in.size() > 0) { printf("\t%s\n", in[0].c_str()); }
		fflush(stdout);
	}

	void parse_train(vector<string>& train_data, vector<ExpData>& data) {
		const char* cols[9];
		
		for (int i = 0; i < (int)train_data.size(); i++) {
			parse_line(train_data[i].c_str(), cols, 9);
			
			ExpData exp;
			exp.ParseTrain(train_data[i].c_str());
			
			data.push_back(exp);
		}
	}
	
	void parse_query(vector<string>& queries, vector<ExpData>& data) {
		for (int i = 0; i < (int)queries.size(); i++) { 
			ExpData exp;
			exp.ParseQuery(queries[i].c_str());
			data.push_back(exp);
		}
	}

	vector<double> LearnMF(vector<ExpData>& train, vector<ExpData>& test) {
		int mid_num = 0;
		map<int, int> mid2uid;

		int ly_num = 0;
		map<Tuple2, int> ly2tid;

		vector<ExpData>* data[2] = {&train, &test};
	
		for (int t = 0; t < 2; t++) {
			for (int i = 0; i < (int)data[t]->size(); i++) {
				ExpData& d = (*data[t])[i];

				if (mid2uid.find(d.mid) == mid2uid.end()) {
					mid2uid[d.mid] = mid_num;
					mid_num++;
				}

				if (ly2tid.find(Tuple2(d.loc, d.exp)) == ly2tid.end()) {
					ly2tid[Tuple2(d.loc, d.exp)] = ly_num;
					ly_num++;
				}
			}
		}

		for (int t = 0; t < 2; t++) {
			for (int i = 0; i < (int)data[t]->size(); i++) {
				ExpData& d = (*data[t])[i];
				d.uid      = mid2uid[d.mid];
				d.tid      = ly2tid[Tuple2(d.loc, d.exp)];
			}
		}

		printf("MID : %d, LY : %d\n", mid_num, ly_num);

		MFMachine mf(15, 1.2, 1e-2, mid_num, ly_num);

		for (int i = 0; i < (int)train.size(); i++) {
			mf.AddSample(Sample(train[i].yield, train[i].uid, train[i].tid));
		}

		mf.Train(20);

		vector<Sample> test_sample;
		for (int i = 0; i < (int)test.size(); i++) {
			test_sample.push_back(Sample(test[i].yield, test[i].uid, test[i].tid));
		}

		return mf.Evaluate(test_sample);
	}

	void ExtractExpYear(vector<ExpData>& data) {
		for (int i = 0; i <(int)data.size(); i++) {
			if (exp2year[data[i].exp] == 0) {
				exp2year[data[i].exp] = data[i].year;
			}
		}
	}

	void SmoothExpYear() {
		vector<pair<int, int> > exp_year_list;
		for (map<int, int>::iterator it = exp2year.begin(); it != exp2year.end(); ++it) {
			int id   = it->first;
			int year = it->second;

			exp_year_list.push_back(make_pair(id, year));
		}

		sort(exp_year_list.begin(), exp_year_list.end());

		for (int i = 0; i < (int)exp_year_list.size(); i++) {
			int id   = exp_year_list[i].first;
			int year = exp_year_list[i].second;

			if (year == 0) {
				int j1 = i-1;
				while (j1 >= 0) {
					if (exp_year_list[j1].second == 0) j1--;
					else break;
				}
			
				int j2 = i+1;
				while (j2 < (int)exp_year_list.size()) {
					if (exp_year_list[j2].second == 0) j2++;
					else break;
				}

				if (j1 >= 0 && j2 < (int)exp_year_list.size()) {
					if (i - j1 < j2 - i) {
						year = exp_year_list[j1].second;
					} else {
						year = exp_year_list[j2].second;
					}
				} else if (j1 >= 0) {
					year = exp_year_list[j1].second;
				} else if (j2 < (int)exp_year_list.size()) {
					year = exp_year_list[j2].second;
				}
			
				exp2year[id] = year;
			}
		}
		
		for (map<int, int>::iterator it = exp2year.begin(); it != exp2year.end(); ++it) {
			// printf("%d, %d\n", it->first, it->second);
		}
	}

	void UpdateYear(vector<ExpData>& data) {
		for (int i = 0; i <(int)data.size(); i++) {
			data[i].UpdateYear(exp2year[data[i].exp]);
		}
	}

	vector<double> predictYield(vector <string> trainingData, 
			vector <string> droughtMonitor, 
			vector <string> droughtNOAA, 
			vector <string> locations, 
			vector <string> queries,
			vector <string> experimentData) 
	{
		vector<ExpData> train;
		vector<ExpData> test;
	
		vector<string>  all_data = trainingData;
		all_data.insert(all_data.end(), experimentData.begin(), experimentData.end());
	
		parse_train(all_data, train);
		parse_query(queries,  test);
		
		ExtractExpYear(train);
		ExtractExpYear(test);	

		SmoothExpYear();

		UpdateYear(train);
		UpdateYear(test);

		{
			print_some_elem(trainingData, "trainingData");
			print_some_elem(droughtMonitor, "droughtMonitor");
			print_some_elem(droughtNOAA, "droughtNOAA");
			print_some_elem(locations, "locations");
			print_some_elem(experimentData, "experimentData");
			print_some_elem(queries, "queries");

			lym_count = 0;
			ly_count[0] = ly_count[1] = ly_count[2] = 0;
			m_count[0]  = m_count[1]  = 0;
		}

		vector<double> result = LearnMF(train, test);
	
		return result;
	}
};
