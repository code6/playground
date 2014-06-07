// TopCoder Marathon - soybean 4
// author: elder1g
#define LOCAL
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <conio.h>
using namespace std;

double strtodouble(string& str)
{
	stringstream se(str);
	double v=0;
	se>>v;
	return v;
}
int strtoint(string& str)
{
	stringstream se(str);
	int v=0;
	se>>v;
	return v;
}
string inttostr(int num)
{
	stringstream se;
	se<<num;
	return se.str();
}
string doubletostr(double num)
{
	stringstream se;
	se<<num;
	return se.str();
}

#ifdef LOCAL
vector<double> correct_ans;
vector<int> test_mids;
#endif

double t_begin;
double c_time;
void starttime()
{
    unsigned long long time;
    __asm__ volatile ("rdtsc":"=A"(time));
    t_begin=time/3.6e9;
}
double gettime() {
    unsigned long long time;
    __asm__ volatile ("rdtsc":"=A"(time));
    c_time = time/3.6e9-t_begin;
    return c_time;
}

double getdouble(double l,double r){
    return l+(rand()%10000/10000.)*(r-l);
}

int NP,NQ,NLOC,NYEAR,NRM,N_TRAIN_REP,NPDT;

struct Material
{
	int mid;
	string pedi;
	int herb;
	double rm;
	vector<pair<int,double> > pedi_comp;
	Material()
	{
		rm=-1;
	}
};

struct Query
{
	int loccd;
	int year;
	int month;
	int day;
	string pedi;
	
	int pid;
	int qid;
	int yearid;
	int locid;
	double grm;
	vector<pair<int,double> > pedi_comp;
	Query()
	{
	}
	Query(int loccd,int year,int month,int day,string pedi)
	{
		this->loccd=loccd;
		this->year=year;
		this->month=month;
		this->day=day;
		this->pedi=pedi;
	}
	void output_str()
	{
		//cerr<<eid<<","<<loccd<<","<<repno<<","<<mid<<","<<herb<<","<<rm<<","<<year<<"-"<<month<<"-"<<day<<endl;
	}
};

struct Record
{
	int eid;
	int loccd;
	int repno;
	int mid;
	double ygsmn;
	double mrtyn;
	int year;
	int month;
	int day;
		
	int pid;
	int qid;
	int yearid;
	int locid;
	int rep_id;
	Record()
	{
	}
	void set_value(string str)
	{
		for (int i=0;i<str.size();++i)
			 if (str[i]==',')
				str[i]=' ';
		char t_loccd[100];
		char t_repno[100];
		char t_mrtyn[100];
		char t_plantdate[100];
		sscanf(str.c_str(),"%d %s %s %d %lf %s %s",&eid,t_loccd,t_repno,&mid,&ygsmn,t_mrtyn,t_plantdate);
		if (ygsmn<0||ygsmn>160)
			cerr<<"Input Error(Ygsmn outside)"<<endl;
		string loccd_str=string(t_loccd);
		string repno_str=string(t_repno);
		string mrtyn_str=string(t_mrtyn);
		if (loccd_str=="NULL")
		{
			loccd=1000000;
			//cerr<<"NULL LOCCD"<<endl;
		}
		else
			sscanf(t_loccd,"%d",&loccd);
		if (repno_str=="NULL")
		{
			repno=1000;
			cerr<<"NULL REPNO"<<endl;
		}
		else
			sscanf(t_repno,"%d",&repno);
		if (mrtyn_str=="NULL")
			mrtyn=-1;
		else
			sscanf(t_mrtyn,"%lf",&mrtyn);
		string plantdate_str=string(t_plantdate);
		if (plantdate_str=="NULL")
			year=month=day=-1;
		else
		{
			if (plantdate_str.size()!=10) cerr<<str<<" ERR"<<endl;
			
			year=(plantdate_str[0]-'0')*1000+(plantdate_str[1]-'0')*100+(plantdate_str[2]-'0')*10+(plantdate_str[3]-'0');
			
			if (plantdate_str[5]=='X')
				month=-1;
			else
				month=(plantdate_str[5]-'0')*10+(plantdate_str[6]-'0');
				
			if (plantdate_str[8]=='X')
				day=-1;
			else
				day=(plantdate_str[8]-'0')*10+(plantdate_str[9]-'0');
		}
		/*
		int len1=strlen(t_herb);
		int len2=strlen(t_mrtyn);
		int len3=strlen(t_rm);
		int len4=strlen(t_plantdate);
		if (len1<0||len2<0||len3<0||len4<0||len1>50||len2>50||len3>50||len4>50)
		{
			cerr<<len1<<" "<<len2<<" "<<len3<<" "<<len4<<endl;
			
		}
		*/
	}
	void output_str()
	{
		//cerr<<eid<<","<<loccd<<","<<repno<<","<<mid<<","<<herb<<","<<ygsmn<<","<<mrtyn<<","<<rm<<","<<year<<"-"<<month<<"-"<<day<<endl;
	}
};

struct Pedi
{
	vector<int> herb_cnt;
	double herb_tot_cnt;
	double sum_nonnull_rms;
	int tot_nonnull_rms;
	int tot_null_rms;
	double avg_rm;
	Pedi()
	{
		herb_cnt.resize(4);
		herb_tot_cnt=0;
		sum_nonnull_rms=0;
		tot_nonnull_rms=0;
		tot_null_rms=0;
		avg_rm=0;
	}
};

struct RepInfo
{
	double tot_yield;
	int count;
	double avg_yield;
	double avg_rm;
	int non_null_rm;
	int null_rm;
	RepInfo()
	{
		tot_yield=0;
		count=0;
		avg_yield=0;
		avg_rm=0;
		non_null_rm=0;
		null_rm=0;
	}
};

void clear_data()
{
}

//map<pair<int,pair<int,pair<int,int> > >,int> mapidx;
vector<Record> all_data_records;
//map<long long,vector<int> > locyearmid_to_index;
//map<int,vector<int> > mid_to_index;
//map<int,double> mid_yield;
//map<int,double> mid_yield2;
//map<int,int> mid_cnts;
//map<int,double> mid_mean;
//map<int,double> mid_stddif;
//map<long long,double> rep_tot_off;
//map<long long,double> rep_tot_cnt;
//map<long long,int> rep_tot_pure_cnt;
vector<Query> all_queries;
double g_avg_yield;
vector<Material> all_materials;
double lastloss;
vector<Pedi> pedis_info;
vector<RepInfo> reps_info;

int get_herb_value(string str)
{
	if (str=="RR1") return 0;
	if (str=="conv") return 1;
	if (str=="RR2Y") return 2;
	return 3;
}

void set_material_value(string str)
{
	for (int i=0;i<str.size();++i)
		if (str[i]==',')
			str[i]=' ';
	int mid;
	char t_pedi[200];
	char t_herb[100];
	char t_rm[100];
	sscanf(str.c_str(),"%d %s %s %s",&mid,t_pedi,t_herb,t_rm);
	//if (all_materials[mid].mid==mid) cerr<<"DUP"<<mid<<endl;
	all_materials[mid].mid=mid;
	all_materials[mid].pedi=string(t_pedi);
	all_materials[mid].herb=get_herb_value(string(t_herb));
	string rm_str(t_rm);
	if (rm_str=="NULL")
		//all_materials[mid].rm=-1;
		;
	else
		sscanf(t_rm,"%lf",&all_materials[mid].rm);
}

void set_material_value2(string str,vector<string>& tstr)
{
	for (int i=0;i<str.size();++i)
		if (str[i]==',')
			str[i]=' ';
	int mid;
	char t_pedi[200];
	char t_herb[100];
	char t_rm[100];
	sscanf(str.c_str(),"%d %s %s %s",&mid,t_pedi,t_herb,t_rm);
	string pedi(t_pedi);
	int herb=get_herb_value(string(t_herb));
	string rm_str(t_rm);
	double rm;
	if (rm_str=="NULL")
		rm=-1;
	else
		sscanf(t_rm,"%lf",&rm);
	
	int pedi_idx=lower_bound(tstr.begin(),tstr.end(),pedi)-tstr.begin();
	pedis_info[pedi_idx].herb_cnt[herb]++;
	pedis_info[pedi_idx].herb_tot_cnt++;
	if (rm<0)
		pedis_info[pedi_idx].tot_null_rms++;
	else
	{
		pedis_info[pedi_idx].sum_nonnull_rms+=rm;
		pedis_info[pedi_idx].tot_nonnull_rms++;
	}
	
}

int get_rm_index(double rm)
{
	if (rm<0) return 0;
	return min(((int)(rm/0.5))+1,NRM-1);
}

vector<int> res_type;
vector<int> ans_lens;
const double eps=1e-7;

long long loc_year_mid_to_ll(long long loccd,long long year,long long mid)
{
	if (year<0) year=0;
	else year=year-1990;
	long long ret=mid+(loccd<<25)+(year<<50);
	return ret;
}

long long eid_loccd_rep_to_ll(long long eid,long long loccd,long long rep)
{
	long long ret=eid+(loccd<<25)+(rep<<50);
	return ret;
}

long long loccd_year_to_ll(long long loccd,int year)
{
	long long ret=(loccd<<32)+year;
	return ret;
}

struct svdFeature{
    vector<pair<int,double> > fg,fu,fi;
    double rate;
    svdFeature(){init();}
    void init(){
        rate=0;
        fg.clear();
        fu.clear();
        fi.clear();
    }
    inline void setrate(double r){rate=r;}
    inline void addglobal(int i,double w){fg.push_back(make_pair(i,w));}
    inline void adduser(int i,double w){fu.push_back(make_pair(i,w));}
    inline void additem(int i,double w){fi.push_back(make_pair(i,w));}
};

vector<svdFeature> train;

struct SVD{
    int K;
    double lambda,bias_lambda;
    double gamma;
    int ng,nu,ni;
    double loss,rmse;
    vector<double> global;
    vector<pair<double,vector<double> > > user,item;
    
	//vector<int> pid_cnt;
	//vector<int> qid_cnt;
    SVD(const SVD &t){
        K=t.K;
        lambda=t.lambda;
        bias_lambda=t.bias_lambda;
        ng=t.ng;
        nu=t.nu;
        ni=t.ni;
        loss=t.loss;
        global=t.global;
        user=t.user;
        item=t.item;
        //train=t.train;
		//pid_cnt=t.pid_cnt;
		//qid_cnt=t.qid_cnt;
    }
    SVD(){}
    SVD(int K,double lambda,double bias_lambda,double gamma,int ng,int nu,int ni):K(K),lambda(lambda),bias_lambda(bias_lambda),gamma(gamma),ng(ng),nu(nu),ni(ni){
        global=vector<double>(ng,0);
        user.clear();
        for (int i=0;i<nu;i++){
            vector<double> t;
            for (int j=0;j<K;j++) t.push_back(getdouble(-1,1));
            user.push_back(make_pair(0.,t));
        }
        item.clear();
        for (int i=0;i<ni;i++){
            vector<double> t;
            for (int j=0;j<K;j++) t.push_back(getdouble(-1,1));
            item.push_back(make_pair(0.,t));
        }
        //train.clear();
		//pid_cnt.clear();
		//pid_cnt.resize(nu);
		//qid_cnt.clear();
		//qid_cnt.resize(ni);
		//global[0]=g_avg_yield;
    }
    void addTrain(svdFeature t){
        //t.fg.shrink_to_fit();
		//t.fu.shrink_to_fit();
		//t.fi.shrink_to_fit();
		train.push_back(t);
		//pid_cnt[t.fu[0].first]++;
		//qid_cnt[t.fi[0].first]++;
    }
    vector<double> evaluate(vector<svdFeature>& query){
        vector<double> res;
        res.clear();
        for (int i=0;i<query.size();i++) res.push_back(evaluate(query[i]));
        return res;
    }
    void shuffle(){
        random_shuffle(train.begin(),train.end());
    }
    void Train(){
        loss=0;
        rmse=0;
        for (int i=0;i<train.size();i++){
            Stochastic(train[i]);
            if (loss!=loss) return;
			if (loss>lastloss) return;
        }
        for (int k=0;k<K;k++){
            for (int i=0;i<user.size();i++) loss+=/*pid_cnt[i]*/lambda*user[i].second[k]*user[i].second[k];
            for (int i=0;i<item.size();i++) loss+=/*qid_cnt[i]*/lambda*item[i].second[k]*item[i].second[k];
        }
        for (int i=0;i<user.size();i++) loss+=/*pid_cnt[i]*/bias_lambda*user[i].first*user[i].first;
        for (int i=0;i<item.size();i++) loss+=/*qid_cnt[i]*/bias_lambda*item[i].first*item[i].first;
        rmse=sqrt(rmse/train.size());
    }
    double evaluate(svdFeature& t){
        //if (pid_cnt[t.fu[0].first]==0) return 55;
		double sum=0;
        for (int i=0;i<t.fg.size();i++) sum+=global[t.fg[i].first]*t.fg[i].second;
        vector<double> U=vector<double>(K,0);
        vector<double> V=vector<double>(K,0);
        double swu=0,swi=0;
        
        for (int z=0;z<t.fu.size();z++){
            int i=t.fu[z].first;
            double w=t.fu[z].second;
            sum+=user[i].first*w;
            for (int j=0;j<K;j++) U[j]+=user[i].second[j]*w;
            swu+=w;
        }
        for (int z=0;z<t.fi.size();z++){
            int i=t.fi[z].first;
            double w=t.fi[z].second;
            sum+=item[i].first*w;//
            for (int j=0;j<K;j++) V[j]+=item[i].second[j]*w;
            swi+=w;
        }
        
        for (int i=0;i<K;i++) sum+=U[i]*V[i]/swu/swi;
        //if (rand()%100000==0) printf("%.3f %.3f %.3f\n",sg,tsg-sg,sum-tsg);
		/*
		if (sum<0 || sum>160)
		{
			cerr<<sum<<endl;
			for (int i=0;i<K;++i)
			{
				cerr<<"("<<U[i]<<" "<<V[i]<<") ";
			}
			
		}
		*/
		if (sum<-500) sum=-500;
		if (sum>500) sum=500;
        return sum;
    }
    void Stochastic(svdFeature& t){
        double e=evaluate(t);
		//loss+=(t.rate-e)*(t.rate-e);
		loss+=min(625.0,(t.rate-e)*(t.rate-e)); //may improve
        rmse+=min(625.0,(t.rate-e)*(t.rate-e));
        double g=t.rate-e;
        vector<double> U=vector<double>(K,0);
        vector<double> V=vector<double>(K,0);
        double swu=0,swi=0;
		//double pidw=1;//sqrt(pid_cnt[t.fu[0].first]*1.0);
		//double qidw=1;//sqrt(qid_cnt[t.fi[0].first]*1.0);
        for (int z=0;z<t.fu.size();z++){
            int i=t.fu[z].first;
            double w=t.fu[z].second;
            for (int j=0;j<K;j++) U[j]+=user[i].second[j]*w;
            swu+=w;
        }
        for (int z=0;z<t.fi.size();z++){
            int i=t.fi[z].first;
            double w=t.fi[z].second;
            for (int j=0;j<K;j++) V[j]+=item[i].second[j]*w;
            swi+=w;
        }
        for (int z=0;z<t.fu.size();z++){
            int i=t.fu[z].first;
            double w=t.fu[z].second;
            for (int j=0;j<K;j++) user[i].second[j]+=(V[j]*g-user[i].second[j]*lambda)*gamma*w/swu;
            user[i].first+=(g-user[i].first*bias_lambda)*gamma*w/swu;
        }
        for (int z=0;z<t.fi.size();z++){
            int i=t.fi[z].first;
            double w=t.fi[z].second;
            for (int j=0;j<K;j++) item[i].second[j]+=(U[j]*g-item[i].second[j]*lambda)*gamma*w/swi;
            item[i].first+=(g-item[i].first*bias_lambda)*gamma*w/swi;//
        }
        for (int z=0;z<t.fg.size();z++){
            int i=t.fg[z].first;
            global[i]+=g*gamma*t.fg[z].second;
        }
    }
    double getloss(){return loss;}
    double getrmse(){return rmse;}
};

int get_rm2_index(double srm,double grm)
{
	if (grm<0) return 0;
	if (srm<0) return 1;
	if (grm<=srm)
	{	
		double dif=srm-grm;
		dif=min(2.0,dif);
		return ((int)(dif/0.2))+2;
	}
	else
	{
		double dif=grm-srm;
		dif=min(2.0,dif);
		return ((int)(dif/0.2))+15;
	}
	//return 2;
}

svdFeature toSVDFeature(Record& t){
        svdFeature svd;
        svd.setrate(t.ygsmn-reps_info[t.rep_id].avg_yield);
        svd.addglobal(0,1);
        
		svd.adduser(t.pid,0.5);
		//int therb=all_materials[t.mid].herb;
		//svd.adduser(NP+therb,1);
		for (int i=0;i<4;++i)
			if (pedis_info[t.pid].herb_cnt[i]!=0)
				svd.adduser(NP+i,pedis_info[t.pid].herb_cnt[i]/pedis_info[t.pid].herb_tot_cnt);
		svd.adduser(NP+4+get_rm_index(pedis_info[t.pid].avg_rm),1);
		//svd.adduser(NP+4+get_rm_index(all_materials[t.mid].rm),1);//old
		
		//double srm=pedis_info[t.pid].avg_rm;
		//double grm=reps_info[t.rep_id].avg_rm;
		//int rmidx=get_rm2_index(srm,grm);
		//svd.adduser(NP+4+rmidx,0.5);
		
		for (int i=0;i<all_materials[t.mid].pedi_comp.size();++i)
			svd.adduser(NP+4+NRM+all_materials[t.mid].pedi_comp[i].first,all_materials[t.mid].pedi_comp[i].second);
												
        svd.additem(t.qid,1);
		svd.additem(NQ+t.locid,1);
		svd.additem(NQ+NLOC+t.yearid,1);
        return svd;
}
svdFeature toSVDFeature(Query& t){
        svdFeature svd;
        svd.addglobal(0,1);
        
		svd.adduser(t.pid,0.5);
		for (int i=0;i<4;++i)
			if (pedis_info[t.pid].herb_cnt[i]!=0)
				svd.adduser(NP+i,pedis_info[t.pid].herb_cnt[i]/pedis_info[t.pid].herb_tot_cnt);
		svd.adduser(NP+4+get_rm_index(pedis_info[t.pid].avg_rm),1);
		//double srm=pedis_info[t.pid].avg_rm;
		//double grm=t.grm;
		//int rmidx=get_rm2_index(srm,grm);
		//svd.adduser(NP+4+rmidx,0.5);
		//cerr<<selfrm<<" "<<grm<<endl;
		
		for (int i=0;i<t.pedi_comp.size();++i)
			svd.adduser(NP+4+NRM+t.pedi_comp[i].first,t.pedi_comp[i].second);
		
		svd.additem(t.qid,1);
		svd.additem(NQ+t.locid,1);
		svd.additem(NQ+NLOC+t.yearid,1);
        return svd;
}

vector<svdFeature> svdquery;
SVD svd,last_svd;

vector<pair<int,double> > analyze_pedi(vector<int> nums,vector<pair<int,int> > ops)
{
	vector<pair<int,double> > res;
	if (ops.size()==0)
	{
		res.push_back(make_pair(nums[0],1.0));
		return res;
	}
	int max_ct=ops[0].first;
	int max_pos=0;
	for (int i=1;i<ops.size();++i)
	{
		if (ops[i].first>max_ct)
		{
			max_ct=ops[i].first;
			max_pos=i;
		}
	}
	int max_dup=ops[max_pos].second;
	vector<int> nums1,nums2;
	vector<pair<int, int> > ops1,ops2;
	for (int i=0;i<=max_pos;++i)
		nums1.push_back(nums[i]);
	for (int i=0;i<max_pos;++i)
		ops1.push_back(ops[i]);
	for (int i=max_pos+1;i<nums.size();++i)
		nums2.push_back(nums[i]);
	for (int i=max_pos+1;i<ops.size();++i)
		ops2.push_back(ops[i]);
	double totw=(1<<max_dup);
	double leftw=(totw-1)/totw;
	double rightw=1.0/totw;
	res=analyze_pedi(nums1,ops1);
	for (int i=0;i<res.size();++i)
		res[i].second*=leftw;
	vector<pair<int,double> > res2=analyze_pedi(nums2,ops2);
	for (int i=0;i<res2.size();++i)
	{
		bool fd=false;
		for (int j=0;j<res.size();++j)
			if (res[j].first==res2[i].first)
			{
				fd=true;
				res[j].second+=res2[i].second*rightw;
				break;
			}
		if (!fd)
		{
			res.push_back(make_pair(res2[i].first,res2[i].second*rightw));
		}
	}
	return res;
}

vector<pair<int,double> > parse_pedi(string pedi)
{
	vector<pair<int,double> > res;
	if (pedi=="NULL"||pedi=="") return res;
	bool valid=true;
	for (int i=0;i<pedi.size();++i)
		if (!isdigit(pedi[i])&&pedi[i]!='/'&&pedi[i]!='('&&pedi[i]!=')')
		{
			valid=false;
			break;
		}
	if (!valid) return res;
	vector<int> nums;
	vector<pair<int,int> > ops;
	int pos=0;
	while(pos<pedi.size())
	{
		if (isdigit(pedi[pos]))
		{
			int cn=pedi[pos]-'0';
			pos++;
			while(pos<pedi.size()&&isdigit(pedi[pos]))
			{
				cn=cn*10+(pedi[pos]-'0');
				pos++;
			}
			nums.push_back(cn);
		}
		else
		{
			int dup=1;
			if (pedi[pos]=='(')
			{
				pos++;
				int cn=0;
				while(pos<pedi.size()&&isdigit(pedi[pos]))
				{
					cn=cn*10+(pedi[pos]-'0');
					pos++;
				}
				if (cn!=0)
					dup=min(cn,10);
				if (pos>=pedi.size()||pedi[pos]!=')')
					valid=false;
				pos++;
			}
			int sc=0;
			while(pos<pedi.size()&&pedi[pos]=='/')
			{
				sc++;
				pos++;
			}
			if (sc==0) valid=false;
			ops.push_back(make_pair(sc,dup));
		}
		if (!valid) break;
	}
	if (!valid) return res;
	if (ops.size()+1!=nums.size()) return res;
	return analyze_pedi(nums,ops);
}

void generate_data(vector<string>& trainingData,vector<string>& droughtMonitor,vector<string>& droughtNOAA,
		vector<string>& locations,vector<string>& material,vector<string>& reps)
{
	NRM=30;
	all_materials.resize(260000);
	for (int i=0;i<material.size();++i)
		set_material_value(material[i]);
			
	vector<Record> pre_records;
	pre_records.reserve(trainingData.size());
	double maxyield=-1;
	double minyield=999;
	map<long long, int> rcount;
	for (int i=0;i<trainingData.size();++i)
	{
		Record rcd;
		rcd.set_value(trainingData[i]);
		rcount[eid_loccd_rep_to_ll(rcd.eid,rcd.loccd,rcd.repno)]++;
		if (rcd.loccd==1000000||rcd.repno==1000)
			rcount[eid_loccd_rep_to_ll(rcd.eid,rcd.loccd,rcd.repno)]=100;
		maxyield=max(maxyield,rcd.ygsmn);
		minyield=min(minyield,rcd.ygsmn);
		pre_records.push_back(rcd);
	}
	all_data_records.reserve(trainingData.size());
	for (int i=0;i<pre_records.size();++i)
	{
		Record& rcd=pre_records[i];
		if (rcount[eid_loccd_rep_to_ll(rcd.eid,rcd.loccd,rcd.repno)]==36)
			all_data_records.push_back(rcd);
	}
	cerr<<minyield<<" "<<maxyield<<endl;
	cerr<<"S1:"<<all_data_records.size()<<endl;
	
	all_queries.reserve(reps.size()*36);
	for (int i=0;i<reps.size();++i)
	{
		int loccd=1000000;
		int year=-1;
		int month=-1;
		int day=-1;
		string str=reps[i];
		for (int i=0;i<str.size();++i)
			 if (str[i]==',')
				str[i]=' ';
		string loccd_str;
		string plantdate_str;
		stringstream sst(str);
		sst>>loccd_str;
		if (loccd_str!="NULL")
			loccd=strtoint(loccd_str);
		sst>>plantdate_str;
		if (plantdate_str!="NULL")
		{
			year=(plantdate_str[0]-'0')*1000+(plantdate_str[1]-'0')*100+(plantdate_str[2]-'0')*10+(plantdate_str[3]-'0');
			
			if (plantdate_str[5]=='X')
				month=-1;
			else
				month=(plantdate_str[5]-'0')*10+(plantdate_str[6]-'0');
			
			if (plantdate_str[8]=='X')
				day=-1;
			else
				day=(plantdate_str[8]-'0')*10+(plantdate_str[9]-'0');
		}
		string tstr;
		for (int j=0;j<36;++j)
		{
			sst>>tstr;
			all_queries.push_back(Query(loccd,year,month,day,tstr));
		}
	}
	int szm=0;
	int szq=0;
	for (int i=0;i<all_materials.size();++i)
	{	
		all_materials[i].pedi_comp=parse_pedi(all_materials[i].pedi);
		/*
		if (all_materials[i].pedi_comp.size()==0)
			all_materials[i].pedi_comp.push_back(make_pair(i,1));
		*/
		//if (all_materials[i].pedi_comp.size()==1&&all_materials[i].pedi_comp[0].first==i)
		//	all_materials[i].pedi_comp.clear();
		szm+=all_materials[i].pedi_comp.size();
	}
	for (int i=0;i<all_queries.size();++i)
	{
		all_queries[i].pedi_comp=parse_pedi(all_queries[i].pedi);
		szq+=all_queries[i].pedi_comp.size();
	}
	cerr<<"ORI SZ:"<<szm<<" "<<szq<<endl;
	/*
	for (int i=0;i<0;++i)
	{
		
		int chg_count=0;
		for (int j=0;j<all_materials.size();++j)
		{
			vector<pair<int,double> >& ocom=all_materials[j].pedi_comp;
			vector<pair<int,double> > ncom;
			bool chg=false;
			for (int k=0;k<ocom.size();++k)
			{
				pair<int,double>& pr=ocom[k];
				if (pr.first<260000&&all_materials[pr.first].pedi_comp.size()!=0)
				{
					for (int m=0;m<all_materials[pr.first].pedi_comp.size();++m)
					{
						bool fd=false;
						for (int u=0;u<ncom.size();++u)
						{
							if (ncom[u].first==all_materials[pr.first].pedi_comp[m].first)
							{
								ncom[u].second+=pr.second*all_materials[pr.first].pedi_comp[m].second;
								fd=true;
								break;
							}
						}
						if (!fd)
							ncom.push_back(make_pair(all_materials[pr.first].pedi_comp[m].first,pr.second*all_materials[pr.first].pedi_comp[m].second));
					}
					chg=true;
				}
				else
				{
					bool fd=false;
					for (int u=0;u<ncom.size();++u)
					{
						if (ncom[u].first==pr.first)
						{
							ncom[u].second+=pr.second;
							fd=true;
							break;
						}
					}
					if (!fd)
						ncom.push_back(make_pair(pr.first,pr.second));
				}
			}
			if (chg)
			{	
				chg_count++;
				ocom=ncom;
			}
		}
		int tsz=0;
		for (int j=0;j<all_materials.size();++j)
			tsz+=all_materials[j].pedi_comp.size();
		cerr<<"Iter "<<i<<":"<<chg_count<<" "<<tsz<<endl;
		
		chg_count=0;
		for (int j=0;j<all_queries.size();++j)
		{
			vector<pair<int,double> >& ocom=all_queries[j].pedi_comp;
			vector<pair<int,double> > ncom;
			bool chg=false;
			for (int k=0;k<ocom.size();++k)
			{
				pair<int,double>& pr=ocom[k];
				if (pr.first<260000&&all_materials[pr.first].pedi_comp.size()!=0)
				{
					for (int m=0;m<all_materials[pr.first].pedi_comp.size();++m)
					{
						bool fd=false;
						for (int u=0;u<ncom.size();++u)
						{
							if (ncom[u].first==all_materials[pr.first].pedi_comp[m].first)
							{
								ncom[u].second+=pr.second*all_materials[pr.first].pedi_comp[m].second;
								fd=true;
								break;
							}
						}
						if (!fd)
							ncom.push_back(make_pair(all_materials[pr.first].pedi_comp[m].first,pr.second*all_materials[pr.first].pedi_comp[m].second));
					}
					chg=true;
				}
				else
				{
					bool fd=false;
					for (int u=0;u<ncom.size();++u)
					{
						if (ncom[u].first==pr.first)
						{
							ncom[u].second+=pr.second;
							fd=true;
							break;
						}
					}
					if (!fd)
						ncom.push_back(make_pair(pr.first,pr.second));
				}
			}
			if (chg)
			{	
				chg_count++;
				ocom=ncom;
			}
		}
		tsz=0;
		for (int j=0;j<all_queries.size();++j)
			tsz+=all_queries[j].pedi_comp.size();
		cerr<<"Iter "<<i<<":"<<chg_count<<" "<<tsz<<endl;
	}
	*/	
	vector<int> pdt;
	for (int i=0;i<all_materials.size();++i)
		for (int j=0;j<all_materials[i].pedi_comp.size();++j)
			pdt.push_back(all_materials[i].pedi_comp[j].first);
	for (int i=0;i<all_queries.size();++i)
		for (int j=0;j<all_queries[i].pedi_comp.size();++j)
			pdt.push_back(all_queries[i].pedi_comp[j].first);
	sort(pdt.begin(),pdt.end());
	pdt.erase(unique(pdt.begin(),pdt.end()),pdt.end());
	for (int i=0;i<all_materials.size();++i)
		for (int j=0;j<all_materials[i].pedi_comp.size();++j)
		all_materials[i].pedi_comp[j].first=lower_bound(pdt.begin(),pdt.end(),all_materials[i].pedi_comp[j].first)-pdt.begin();
	for (int i=0;i<all_queries.size();++i)
		for (int j=0;j<all_queries[i].pedi_comp.size();++j)
		all_queries[i].pedi_comp[j].first=lower_bound(pdt.begin(),pdt.end(),all_queries[i].pedi_comp[j].first)-pdt.begin();
	NPDT=pdt.size();
	cerr<<"NPDT:"<<NPDT<<endl;
	
	
	/*
	//int pt=0;
	for (map<int,double>::iterator itr=mid_yield.begin();itr!=mid_yield.end();++itr)
	{
		//pt++;
		//cerr<<mid_mean.size()<<endl;
		mid_mean[itr->first]=(itr->second)/mid_cnts[itr->first];
		mid_stddif[itr->first]=sqrt((mid_yield2[itr->first]/mid_cnts[itr->first])-(mid_mean[itr->first]*mid_mean[itr->first])+eps);
		#ifdef LOCAL
		logger<<"mid:"<<itr->first<<"cnts:"<<mid_cnts[itr->first]<<"mean:"<<mid_mean[itr->first]<<"stddif:"<<mid_stddif[itr->first]<<endl;
		#endif
		if(mid_stddif[itr->first]<0.1) mid_stddif[itr->first]=0.1;
		//mid_stddif[itr->first]=1;
		//mid_stddif[itr->first]=mid_mean[itr->first];
	}
	
	for (int i=0;i<all_data_records.size();++i)
	{
		Record& rcd=all_data_records[i];
		long long maskid=eid_loccd_rep_to_ll(rcd.eid,rcd.loccd,rcd.repno);
		double offstd=(rcd.ygsmn-mid_mean[rcd.mid])/mid_stddif[rcd.mid];
		dealstd(offstd);
		double wt=calwt(mid_cnts[rcd.mid]);
		rep_tot_off[maskid]+=offstd*wt;
		rep_tot_cnt[maskid]+=wt;
		rep_tot_pure_cnt[maskid]++;
		pair<int,pair<int,pair<int,int> > > pr=make_pair(rcd.eid,make_pair(rcd.loccd,make_pair(rcd.repno,rcd.mid)));
		mapidx[pr]=i;
	}
	*/
	/*
	for (int i=0;i<queries.size();++i)
	{
		all_queries.push_back(Query(queries[i]));
	}
	*/
	
	vector<string> tstr;
	for (int i=0;i<all_data_records.size();++i)
		tstr.push_back(all_materials[all_data_records[i].mid].pedi);
	for (int i=0;i<all_queries.size();++i)
		tstr.push_back(all_queries[i].pedi);
	sort(tstr.begin(),tstr.end());
	tstr.erase(unique(tstr.begin(),tstr.end()),tstr.end());
	NP=tstr.size();
	pedis_info.resize(NP);
	for (int i=0;i<material.size();++i)
		set_material_value2(material[i],tstr);
	
	for (int i=0;i<all_data_records.size();++i)
		all_data_records[i].pid=lower_bound(tstr.begin(),tstr.end(),all_materials[all_data_records[i].mid].pedi)-tstr.begin();
	for (int i=0;i<all_queries.size();++i)
		all_queries[i].pid=lower_bound(tstr.begin(),tstr.end(),all_queries[i].pedi)-tstr.begin();
	
	for (int i=0;i<all_data_records.size();++i)
	{
		Record& rcd=all_data_records[i];
		int pedi_idx=all_data_records[i].pid;
		pedis_info[pedi_idx].herb_cnt[all_materials[rcd.mid].herb]++;
		pedis_info[pedi_idx].herb_tot_cnt++;
		if (all_materials[rcd.mid].rm<0)
			pedis_info[pedi_idx].tot_null_rms++;
		else
		{
			pedis_info[pedi_idx].sum_nonnull_rms+=all_materials[rcd.mid].rm;
			pedis_info[pedi_idx].tot_nonnull_rms++;
		}
	}
	
	for (int i=0;i<pedis_info.size();++i)
	{	
		if (pedis_info[i].tot_nonnull_rms!=0)
			pedis_info[i].avg_rm=pedis_info[i].sum_nonnull_rms/pedis_info[i].tot_nonnull_rms;
		else
			pedis_info[i].avg_rm=-1;
		//cerr<<pedis_info[i].avg_rm<<" ";
	}
	
	
	
	vector<long long> t;
	for (int i=0;i<all_data_records.size();++i)
		t.push_back(loccd_year_to_ll(all_data_records[i].loccd,all_data_records[i].year));
	for (int i=0;i<all_queries.size();++i)
		t.push_back(loccd_year_to_ll(all_queries[i].loccd,all_queries[i].year));
	sort(t.begin(),t.end());
	t.erase(unique(t.begin(),t.end()),t.end());
	for (int i=0;i<all_data_records.size();++i)
		all_data_records[i].qid=lower_bound(t.begin(),t.end(),loccd_year_to_ll(all_data_records[i].loccd,all_data_records[i].year))-t.begin();
	for (int i=0;i<all_queries.size();++i)
		all_queries[i].qid=lower_bound(t.begin(),t.end(),loccd_year_to_ll(all_queries[i].loccd,all_queries[i].year))-t.begin();
	NQ=t.size();
	t.clear();
	
	for (int i=0;i<all_queries.size();i+=36)
	{
		double tarm=0;
		int valid_rms=0;
		for (int j=i;j<i+36;++j)
		{
			if (pedis_info[all_queries[i].pid].avg_rm>=0)
			{
				valid_rms++;
				tarm+=pedis_info[all_queries[i].pid].avg_rm;
			}
		}
		for (int j=i;j<i+36;++j)
		{
			if (valid_rms==0)
				all_queries[j].grm=-1;
			else
				all_queries[j].grm=tarm/valid_rms;
		}
	}
	
	for (int i=0;i<all_data_records.size();++i)
		t.push_back(eid_loccd_rep_to_ll(all_data_records[i].eid,all_data_records[i].loccd,all_data_records[i].repno));
	sort(t.begin(),t.end());
	t.erase(unique(t.begin(),t.end()),t.end());
	N_TRAIN_REP=t.size();
	reps_info.resize(N_TRAIN_REP);
	
	for (int i=0;i<all_data_records.size();++i)
	{	
		all_data_records[i].rep_id=lower_bound(t.begin(),t.end(),eid_loccd_rep_to_ll(all_data_records[i].eid,all_data_records[i].loccd,all_data_records[i].repno))
		-t.begin();
		reps_info[all_data_records[i].rep_id].count++;
		reps_info[all_data_records[i].rep_id].tot_yield+=all_data_records[i].ygsmn;
		double rm=pedis_info[all_data_records[i].pid].avg_rm;//all_materials[all_data_records[i].mid].rm;
		if (rm<0)
			reps_info[all_data_records[i].rep_id].null_rm++;
		else
		{
			reps_info[all_data_records[i].rep_id].non_null_rm++;
			reps_info[all_data_records[i].rep_id].avg_rm+=rm;
		}
	}
	for (int i=0;i<reps_info.size();++i)
	{
		if (reps_info[i].non_null_rm==0)
			reps_info[i].avg_rm=-1;
		else
			reps_info[i].avg_rm/=reps_info[i].non_null_rm;
	}
	t.clear();
	for (int i=0;i<N_TRAIN_REP;++i)
	{	
		reps_info[i].avg_yield=reps_info[i].tot_yield/reps_info[i].count;
	}
		
	vector<int> ti;
	for (int i=0;i<all_data_records.size();++i)
		ti.push_back(all_data_records[i].loccd);
	for (int i=0;i<all_queries.size();++i)
		ti.push_back(all_queries[i].loccd);
	sort(ti.begin(),ti.end());
	ti.erase(unique(ti.begin(),ti.end()),ti.end());
	for (int i=0;i<all_data_records.size();++i)
		all_data_records[i].locid=lower_bound(ti.begin(),ti.end(),all_data_records[i].loccd)-ti.begin();
	for (int i=0;i<all_queries.size();++i)
		all_queries[i].locid=lower_bound(ti.begin(),ti.end(),all_queries[i].loccd)-ti.begin();
	NLOC=ti.size();
	ti.clear();
	
	for (int i=0;i<all_data_records.size();++i)
		ti.push_back(all_data_records[i].year);
	for (int i=0;i<all_queries.size();++i)
		ti.push_back(all_queries[i].year);
	sort(ti.begin(),ti.end());
	ti.erase(unique(ti.begin(),ti.end()),ti.end());
	for (int i=0;i<all_data_records.size();++i)
		all_data_records[i].yearid=lower_bound(ti.begin(),ti.end(),all_data_records[i].year)-ti.begin();
	for (int i=0;i<all_queries.size();++i)
		all_queries[i].yearid=lower_bound(ti.begin(),ti.end(),all_queries[i].year)-ti.begin();
	NYEAR=ti.size();
	ti.clear();
	
	cerr<<NP<<" "<<NQ<<" "<<NLOC<<" "<<NYEAR<<endl;
	
	g_avg_yield=0;
	for (int i=0;i<all_data_records.size();++i)
		g_avg_yield+=all_data_records[i].ygsmn;
	g_avg_yield/=all_data_records.size();
}

#ifdef LOCAL
double compare(double a,double b)
{
	if (a<b) return 0;
	if (a>b) return 1;
	return 0.5;
}

double get_quality(vector<double>& a,vector<double>& b)
{
	double ans=0;
	for (int i=0;i<36;++i)
	{
		for (int j=i+1;j<36;++j)
		{
			double cmp_real=compare(a[i],a[j]);
			double cmp_pre=compare(b[i],b[j]);
			if (cmp_real==0.5||cmp_pre==0.5)
				ans+=0.5;
			else
				ans+=1.0-fabs(cmp_real-cmp_pre);
		}
	}
	ans=ans/35.0/36.0*2000000.0;
	return ans;
}

double cal_score(vector<double> a, vector<double> b)
{
	double tqual=0;
	for (int i=0;i<a.size();i+=36)
	{
		vector<double> ta(36);
		vector<double> tb(36);
		for (int j=i;j<i+36;++j)
		{
			ta[j-i]=a[j];
			tb[j-i]=b[j];
		}
		double qual=get_quality(ta,tb);
		tqual+=qual;
	}
	tqual/=(a.size()/36);
	return tqual;
}
#endif

struct PedigreeYieldPredictor
{
	vector<string> predictYield(vector<string>& trainingData,vector<string>& droughtMonitor,vector<string>& droughtNOAA,
		vector<string>& locations,vector<string>& material,vector<string>& reps)
	{
		starttime();
				
		clear_data();
		generate_data(trainingData,droughtMonitor,droughtNOAA,locations,material,reps);
		svd=SVD(50,0.15,0,1e-2,1,NP+4+NRM+NPDT,NQ+NLOC+NYEAR);
		cerr<<svd.K<<" "<<svd.lambda<<" "<<svd.bias_lambda<<" "<<svd.gamma<<endl;
		train.reserve(all_data_records.size());
        for (int i=0;i<all_data_records.size();i++)
			svd.addTrain(toSVDFeature(all_data_records[i]));
		svdquery.clear();
		svdquery.reserve(all_queries.size());
        vector<pair<int,double> > qq;
		qq.reserve(all_queries.size());
		for (int i=0;i<all_queries.size();i++)
		{
			svdquery.push_back(toSVDFeature(all_queries[i]));
			qq.push_back(make_pair(all_queries[i].pid,all_queries[i].grm));
		}
				
		{
			vector<Record>(0).swap(all_data_records);
			vector<Query>(0).swap(all_queries);
		}
		/*
		for (int i=0;i<svdquery.size();++i)
		{	
			svdquery[i].fg.shrink_to_fit();
			svdquery[i].fu.shrink_to_fit();
			svdquery[i].fi.shrink_to_fit();
		}
		*/
		
        lastloss=1e100;
        for (int z=1;gettime()<7*60;z++){
            last_svd=svd;
            svd.shuffle();
            svd.Train();
            if (z%1==0){
                vector<double> tres=svd.evaluate(svdquery);
                printf("Round = %d RMSE(Train) = %.3f time = %.3f\n",z,svd.getrmse(),gettime());
				
				#ifdef LOCAL
					double te=cal_score(svd.evaluate(svdquery),correct_ans);
					printf("Real Score=%.3f Loss=%.3f Gamma=%.3f\n",te,svd.getloss(),svd.gamma);
				#endif
            }
            if (svd.getloss()!=svd.getloss()||svd.getloss()>lastloss) {
                svd=last_svd;
                svd.gamma/=2;
            }
            else {
                lastloss=svd.getloss();
                svd.gamma*=1.3;
            }
        }
		//////////
		vector<double> vres=svd.evaluate(svdquery);
		
		for (double p=-3.0;p<=3.0;p+=0.2)
		{
			vector<double> tres=vres;
			for (int i=0;i<tres.size();++i)
			{
				double srm=pedis_info[qq[i].first].avg_rm;
				double grm=qq[i].second;
				if (srm>0&&grm>0)
				{
					tres[i]+=(srm-grm)*p;
				}
			}
			cerr<<"P="<<p<<":"<<cal_score(tres,correct_ans)<<endl;
		}
		
		//need adjust
		for (int i=0;i<vres.size();++i)
		{
			double srm=pedis_info[qq[i].first].avg_rm;
			double grm=qq[i].second;
			if (srm>0&&grm>0)
			{
				vres[i]+=(srm-grm)*0.4;
			}
		}
		
		vector<string> res;
		res.reserve(vres.size()/36);
		for (int i=0;i<vres.size()/36;++i)
		{
			int from=i*36;
			int to=(i+1)*36;
			vector<pair<double,int> > vdc;
			for (int j=from;j<to;++j)
				vdc.push_back(make_pair(vres[j],j-from));
			sort(vdc.begin(),vdc.end());
			vector<int> vr(36);
			for (int j=0;j<36;++j)
				vr[vdc[j].second]=j;
			string str;
			for (int j=0;j<36;++j)
			{
				if (j!=0)
					str+=',';
				str+=inttostr(vr[j]);
			}
			res.push_back(str);
		}
		return res;
		//////////
	}
};

#ifdef LOCAL

void fill_data(vector<string>& trainingData,vector<string>& droughtMonitor,vector<string>& droughtNOAA,
		vector<string>& locations,vector<string>& material,vector<string>& reps,string td_filename)
{
	set<long long> valid_rep_ids;
	string str;
	ifstream valid_rep_ids_file("ValidReps.csv");
	while(getline(valid_rep_ids_file,str))
	{
		for (int i=0;i<str.size();++i)
			if(str[i]==',')
				str[i]=' ';
		int eid,loccd,repno;
		sscanf(str.c_str(),"%d %d %d",&eid,&loccd,&repno);
		long long rep_id=eid_loccd_rep_to_ll(eid,loccd,repno);
		valid_rep_ids.insert(rep_id);
	}
	cerr<<"valid_reps_size:"<<valid_rep_ids.size()<<endl;
	
	material.reserve(260000);
	vector<string> mat_pedi_str(260000,"");
	ifstream mat_file("Material.csv");
	char t_pedi[200];
	while(getline(mat_file,str))
	{
		material.push_back(str);
		for (int i=0;i<str.size();++i)
			if(str[i]==',')
				str[i]=' ';
		int mid;
		sscanf(str.c_str(),"%d %s",&mid,t_pedi);
		mat_pedi_str[mid]=string(t_pedi);
	}
		
	ifstream td_file(td_filename.c_str());
	trainingData.reserve(1200000);
	reps.reserve(40000);
	correct_ans.reserve(1200000);
		
	int eid,loccd,repno,mid;
	double ygsmn;
	string herb,mrtyn,rm,plant_date;
	char t_loccd[100];
	char t_repno[100];
	char t_mrtyn[100];
	char t_plantdate[100];
	
	map<long long,string> rep_strs;
	map<long long,vector<double> > exp_ans;
	map<int, int> eid_use;
	
	while(getline(td_file,str))
	{	
		string sbak=str;
		for (int i=0;i<sbak.size();++i)
			if(sbak[i]==',')
				sbak[i]=' ';
		sscanf(sbak.c_str(),"%d %s %s %d %lf %s %s",&eid,t_loccd,t_repno,&mid,&ygsmn,t_mrtyn,t_plantdate);
		string loccd_str(t_loccd);
		string repno_str(t_repno);
		string mrtyn_str(t_mrtyn);
		string plantdate_str(t_plantdate);
		
		if (loccd_str=="NULL")
			loccd=1000000;
		else
			sscanf(t_loccd,"%d",&loccd);
		if (repno_str=="NULL")
			repno=1000;
		else
			sscanf(t_repno,"%d",&repno);
		long long rep_id=eid_loccd_rep_to_ll(eid,loccd,repno);
		if (eid_use.count(eid)==0)
		{
			int ut=rand()%100;
			if (ut>=99&&ut<100)
				eid_use[eid]=0;
			else
				eid_use[eid]=1;
		}
		if (rep_strs.count(rep_id)==0)
		{
			if (eid_use[eid]==0)
			{
				if (valid_rep_ids.count(rep_id)!=0)
					rep_strs[rep_id]=loccd_str+","+plantdate_str;
			}
			else
				rep_strs[rep_id]="TRAIN";
		}
		if (rep_strs.count(rep_id)!=0)
		{
			if (rep_strs[rep_id]=="TRAIN")
				trainingData.push_back(str);
			else
			{
				//trainingData.push_back(str);//
				rep_strs[rep_id]+=(","+mat_pedi_str[mid]);
				exp_ans[rep_id].push_back(ygsmn);
			}	
		}
	}
	for (map<long long,string>::iterator itr=rep_strs.begin();itr!=rep_strs.end();++itr)
	{
		if (itr->second!="TRAIN")
		{
			reps.push_back(itr->second);
			/*
			cerr<<itr->second<<endl;
			
			*/
			vector<double>& vds=exp_ans[itr->first];
			for (int i=0;i<vds.size();++i)
				correct_ans.push_back(vds[i]);
		}
	}
	
	for (int i=0;i<correct_ans.size();i+=36)
	{
		double aans=0;
		for (int j=i;j<i+36;++j)
			aans+=correct_ans[j];
		aans/=36;
		for (int j=i;j<i+36;++j)
			correct_ans[j]-=aans;
	}
	
		
	cerr<<"q_rep_size:"<<reps.size()<<endl;
	cerr<<"csize:"<<correct_ans.size()<<endl;
	cerr<<"tsize:"<<trainingData.size()<<endl;
			
	ifstream loc_file("Locations.csv");
	locations.reserve(400);
	while(getline(loc_file,str))
		locations.push_back(str);
	cerr<<"lsize:"<<locations.size()<<endl;
	
	ifstream monitor_file("DroughtMonitor.csv");
	droughtMonitor.reserve(180000);
	getline(monitor_file,str);
	while(getline(monitor_file,str))
		droughtMonitor.push_back(str);
	cerr<<"dsize:"<<droughtMonitor.size()<<endl;
}

void test_pro(string dt_filename)
{
	vector<string> trainingData;
	vector<string> droughtMonitor;
	vector<string> droughtNOAA;
	vector<string> locations;
	vector<string> material;
	vector<string> reps;
	fill_data(trainingData,droughtMonitor,droughtNOAA,locations,material,reps,dt_filename);
	PedigreeYieldPredictor predictor;
	vector<string> ans=predictor.predictYield(trainingData,droughtMonitor,droughtNOAA,locations,material,reps);
	cerr<<ans.size()<<endl;
	if (ans.size()!=reps.size())
		cerr<<"WARNING(B) "<<ans.size()<<" "<<reps.size()<<endl;
	double tot_qual=0;
	for (int i=0;i<ans.size();++i)
	{
		vector<double> as(36,0);
		string str=ans[i];
		for (int j=0;j<str.size();++j)
			if (str[j]==',')
				str[j]=' ';
		stringstream sst(str);
		for (int j=0;j<36;++j)
			sst>>as[j];
		vector<double> bs;
		for (int j=i*36;j<(i+1)*36;++j)
			bs.push_back(correct_ans[j]);
		double qual=get_quality(bs,as);
		tot_qual+=qual;
	}
	tot_qual/=ans.size();
	cerr<<"Score:"<<tot_qual<<endl;
	
}

void test_analyze(string pedi)
{
	vector<pair<int,double> > res=parse_pedi(pedi);
	for (int i=0;i<res.size();++i)
	{
		cerr<<"("<<res[i].first<<","<<res[i].second<<") ";
	}
	cerr<<endl;
}

int main()
{
	//test_pro("DataTraining.csv");
	return 0;
}
#endif


