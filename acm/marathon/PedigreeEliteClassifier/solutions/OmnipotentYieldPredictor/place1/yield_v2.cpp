#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int gDebug = 1; 

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
	void Summarize() { avg=sum/(count+1e-6); }
	void Print(const char* name) { printf("%s : (%7.3f %.1f)\n", name, avg, count); }
	double avg;
	double sum;
	double count;
};

struct ExpData {
	int    exp;
	int    loc;  
	int    rep;
	int    mid;   
	int    year;  
	int    herb;
	double yield; 

	int    uid;
	int    tid[3];

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
		rep   = atoi(cols[2]);
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
		rep  = atoi(cols[2]);
		mid  = atoi(cols[3]);
		year = atoi(cols[6]);
		herb = GetHerb(cols[4]);
		
		yield = gDebug ? atof(cols[7]) : 0.0f;
	}

	void UpdateYear(int y) { if (year == 0) year = y; }
};

double rand_double(double l, double r){ return l+(rand()%10000/10000.)*(r-l); }

vector<double> rand_vector(double l, double r, int n) {
	vector<double> res(n);
	for (int i = 0; i < n; i++) res[i] = rand_double(l, r);
	return res;
}


double squ(double f) { return f*f; }

double inner_product(const vector<double>& a, const vector<double>& b) {
	double sum = 0;
	for (int i = 0; i < (int)a.size(); i++) sum += a[i] * b[i];
	return sum;
}

struct Sample {
    int    user; 
	int    item[3];
    double y;

    Sample(double v, int u, int i1, int i2, int i3)
	{
		y = v; 
		user = u; 
		item[0] = i1; item[1] = i2; item[2] = i3;
	}
};

// est(u,i) = bias + b(u) + b(i) + p(u)*q(i)
// loss     = (r(u,i) - est(u,i))^2 
//            + lamda       * (p(u)^2 + p(q)^2)
//		      + bias_lambda * (b(u)^2 + b(i)^2)
// e(u,i) = r(u,i) - est(u,i) 
// q(i)   = q(i) + lrate * (e(u,i)*p(u) - lamda*qi)
// b(i)   = b(i) + lrate * (e(u,i) - bias_lambda*b(i))
struct MFMachine 
{
    int    factor;
    double lambda, bias_lambda;
    double lrate_;
    int nu_;
	int nu2_;
	int ni_[3];
    double loss_;
	double rmse_;
    
	double bias;
	vector<double> user_bias;
	vector<double> item_bias[3];
	
	vector<vector<double> > user[3];
	vector<vector<double> > item[3];
	
	vector<Sample> train;

    MFMachine(){}
	
    MFMachine(int factor, double lambda, double lrate, int nu, int ni0, int ni1, int ni2)
		: factor(factor), lambda(lambda), bias_lambda(lambda*0.01), lrate_(lrate)
	{
		nu_  = nu;
	
		ni_[0] = ni0; 
		ni_[1] = ni1; 
		ni_[2] = ni2;
	
        bias = 0;
      
		const double kR = 1e-2;
	
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < nu_; i++) user[r].push_back(rand_vector(-kR, kR, factor));
			for (int i = 0; i < ni_[r]; i++) item[r].push_back(rand_vector(-kR, kR, factor));
			item_bias[r] = rand_vector(-kR, kR, ni_[r]);
		}
		user_bias = rand_vector(-kR, kR, nu_);
    }
	
    void AddSample(const Sample& t) { train.push_back(t); }

    vector<double> Evaluate(vector<Sample>& query){
		vector<double> res;

        for (int i = 0; i < (int)query.size(); i++) {
			Sample& s   = query[i];
			double  est = EvaluateSample(s);

			res.push_back(est);
		}

		return res;
	}

    void Shuffle() { random_shuffle(train.begin(), train.end()); }

	double CalcRMSE(const vector<double>& est, vector<Sample>& test)
	{
		double test_rmse = 0;
		for (int i = 0; i < (int)test.size(); i++) {
			double g = est[i] - test[i].y;
			test_rmse += min(625.0, squ(g));
		}
		test_rmse = sqrt(test_rmse/test.size());
		return test_rmse;
	}

	void Train(int round, vector<Sample>& test) {
		MFMachine last_mat;
		double    last_loss = 1e100;
	
		double    lr0 = lrate_;
	
		for (int r = 1; r <= round; r++) {
			last_mat = (*this);
			
			lrate_   = lr0/(1.0 + r*lr0*20);

			Shuffle();
			Train();

			{
				double test_rmse = CalcRMSE(Evaluate(test), test);
				printf("Round = %d RMSE(Train) = %.3f time = %6.3f bias=%.3f lrate=%.3f test=%.3f\n",
						r, rmse(), clock()/(double)CLOCKS_PER_SEC, bias, lrate_, test_rmse);
			}

			if (loss() != loss() || loss() > last_loss) {
				(*this) = last_mat;
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
		
		for (int i = 0; i < nu_; i++) {
			loss_ += bias_lambda * squ(user_bias[i]);
		}
	
		for (int r = 0; r < 3; r++) {
			for (int i = 0; i < nu_; i++) {
				loss_ += lambda * inner_product(user[r][i], user[r][i]);
			}

			for (int i = 0; i < (int)item[r].size(); i++) { 
				loss_ += bias_lambda * squ(item_bias[r][i]);
				loss_ += lambda * inner_product(item[r][i], item[r][i]);
			}
		}

		rmse_ = sqrt(rmse_/train.size());
    }

    inline double EvaluateSample(Sample& t) {
        double res = bias + user_bias[t.user];
	
		for (int r = 0; r < 3; r++) {
			res += inner_product(user[r][t.user],  item[r][t.item[r]]) + item_bias[r][t.item[r]];
		}

		return res;
    }

    inline void Stochastic(Sample& t) {
        double e = EvaluateSample(t);
		double g = t.y - e;
		
		loss_ += g*g;
        rmse_ += min(625., g*g);
      
		{
			int uid = t.user;

			for (int r = 0; r < 3; r++) {
				int tid = t.item[r];

				vector<double> U = user[r][uid];
				vector<double> V = item[r][tid];

				for (int j=0; j<factor; j++) user[r][uid][j] += lrate_ * (V[j]*g-user[r][uid][j]*lambda); 
				for (int j=0; j<factor; j++) item[r][tid][j] += lrate_ * (U[j]*g-item[r][tid][j]*lambda);

				item_bias[r][tid] += lrate_ * (g - item_bias[r][tid]*bias_lambda);
			}

			user_bias[uid] += lrate_ * (g - user_bias[uid]*bias_lambda);
		}
		
		bias += lrate_ * g;
    }

    double loss() { return loss_; }
    double rmse() { return rmse_; }
};


// Yield(loc, mid, year) = F(loc, year) + F(mid)
class OmnipotentYieldPredictor {
public:
	map<int, int>  exp2year;

	void print_some_elem(vector<string>& in, const char* name) {
		printf("%s : %d\n", name, (int)in.size());
		if (in.size() > 0) { printf("\t%s\n", in[0].c_str()); }
		fflush(stdout);
	}

	void BuildTrain(vector<ExpData>& train_data, vector<ExpData>& exp_data, vector<ExpData>& data) {
		map<int, int> sel_exp;
	
		{
			for (int i = 0; i < (int)train_data.size(); i++) {
				sel_exp[train_data[i].exp] = 0;
			}

			for (map<int, int>::iterator it = sel_exp.begin(); it != sel_exp.end(); ++it) {
				if (rand()%100 < 15) sel_exp[it->first] = 1; 
			}
		}

		for (int i = 0; i < (int)train_data.size(); i++) {
			if (sel_exp[train_data[i].exp]) data.push_back(train_data[i]);
		}

		data.insert(data.end(), exp_data.begin(), exp_data.end());
	}
	
	void parse_train(vector<string>& input, vector<ExpData>& data) {
		for (int i = 0; i < (int)input.size(); i++) {
			ExpData exp;
			exp.ParseTrain(input[i].c_str());
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

	void ExtractYear(vector<ExpData>& data) {
		for (int i = 0; i <(int)data.size(); i++) {
			if (exp2year[data[i].exp] == 0 && data[i].year != 0) {
				exp2year[data[i].exp] = data[i].year;
			}
		}
	}

	void SmoothExpYear() {
		vector<pair<int, int> > year;
		for (map<int, int>::iterator it = exp2year.begin(); it != exp2year.end(); ++it) {
			int id = it->first;
			int y  = it->second;

			year.push_back(make_pair(id, y));
		}

		sort(year.begin(), year.end());

		for (int i = 0; i < (int)year.size(); i++) {
			int id = year[i].first;
			int y  = year[i].second;

			if (y == 0) {
				int j1 = i-1;
				while (j1 >= 0) {
					if (year[j1].second == 0) j1--;
					else break;
				}
			
				int j2 = i+1;
				while (j2 < (int)year.size()) {
					if (year[j2].second == 0) j2++;
					else break;
				}

				if (j1 >= 0 && j2 < (int)year.size()) {
					if (i- j1 < j2- i) {
						y = year[j1].second;
					} else {
						y = year[j2].second;
					}
				} else if (j1 >= 0) {
					y = year[j1].second;
				} else if (j2 < (int)year.size()) {
					y = year[j2].second;
				}
			
				exp2year[id] = y;
			}
		}
		
		for (map<int, int>::iterator it = exp2year.begin(); it != exp2year.end(); ++it) {
			//printf("%d, %d\n", it->first, it->second);
		}
	}

	void UpdateYear(vector<ExpData>& data) {
		for (int i = 0; i <(int)data.size(); i++) {
			data[i].UpdateYear(exp2year[data[i].exp]);
		}
	}
	
	vector<double> LearnMF(vector<ExpData>& train, vector<ExpData>& test) {
		int pnum = 0;
		map<Tuple2, int> uid;

		int qnum[3] = {0, 0, 0};
		map<Tuple3, int> tid[3];

		vector<ExpData>* data[2] = {&train, &test};
	
		for (int t = 0; t < 2; t++) {
			for (int i = 0; i < (int)data[t]->size(); i++) {
				ExpData& d = (*data[t])[i];

				if (uid.find(Tuple2(d.mid, d.year)) == uid.end()) {
					uid[Tuple2(d.mid, d.year)] = pnum;
					pnum++;
				}
				
				if (tid[0].find(Tuple3(d.loc, d.exp, d.rep)) == tid[0].end()) {
					tid[0][Tuple3(d.loc, d.exp, d.rep)] = qnum[0];
					qnum[0]++;
				}
				
				if (tid[1].find(Tuple3(d.loc, d.year, 1)) == tid[1].end()) {
					tid[1][Tuple3(d.loc, d.year, 1)] = qnum[1];
					qnum[1]++;
				}
				
				if (tid[2].find(Tuple3(d.loc, d.exp, 1)) == tid[2].end()) {
					tid[2][Tuple3(d.loc, d.exp, 1)] = qnum[2];
					qnum[2]++;
				}
			}
		}

		for (int t = 0; t < 2; t++) {
			for (int i = 0; i < (int)data[t]->size(); i++) {
				ExpData& d = (*data[t])[i];
				d.uid      = uid[Tuple2(d.mid, d.year)];
				d.tid[0]   = tid[0][Tuple3(d.loc, d.exp, d.rep)];
				d.tid[1]   = tid[1][Tuple3(d.loc, d.year, 1)];
				d.tid[2]   = tid[2][Tuple3(d.loc, d.exp, 1)];
			}
		}

		printf("MID : %d, TID : %d, %d, %d\n", pnum, qnum[0], qnum[1], qnum[2]);

		MFMachine mf(20, 0.5, 2e-2, pnum, qnum[0], qnum[1], qnum[2]);

		for (int i = 0; i < (int)train.size(); i++) {
			mf.AddSample(Sample(train[i].yield, train[i].uid, train[i].tid[0], train[i].tid[1], train[i].tid[2]));
		}

		vector<Sample> test_sample;
		for (int i = 0; i < (int)test.size(); i++) {
			test_sample.push_back(Sample(test[i].yield, test[i].uid, test[i].tid[0], test[i].tid[1], test[i].tid[2]));
		}

		mf.Train(25, test_sample);

		vector<double> result = mf.Evaluate(test_sample);
		return result;
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
		
		vector<ExpData> train_data, exp_data;
	
		parse_train(trainingData,   train_data);
		parse_train(experimentData, exp_data);
		parse_query(queries,        test);

		ExtractYear(train_data);
		ExtractYear(exp_data);
		ExtractYear(test);	

		SmoothExpYear();

		UpdateYear(train_data);
		UpdateYear(exp_data);
		UpdateYear(test);

		BuildTrain(train_data, exp_data, train);
		
		{
			print_some_elem(trainingData,   "trainingData");
			print_some_elem(droughtMonitor, "droughtMonitor");
			print_some_elem(droughtNOAA,    "droughtNOAA");
			print_some_elem(locations,      "locations");
			print_some_elem(experimentData, "experimentData");
			print_some_elem(queries,        "queries");
		}

		vector<double> result  = LearnMF(train, test);
		return result;
	}
};
