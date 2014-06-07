#include <iostream>
#include <sstream>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#define PB push_back
#define MP make_pair
using namespace std;


double getdouble(double l,double r){
    return l+(rand()%10000/10000.)*(r-l);
}

struct svdFeature{
    vector<pair<int,double> > fg,fu,fi;
    double weight;
    double rate;
    svdFeature(){init();}
    void init(){
        rate=0;
        fg.clear();
        fu.clear();
        fi.clear();
        weight=1;
    }
    inline void setweight(double w){weight=w;}
    inline void setrate(double r){rate=r;}
    inline void addglobal(int i,double w){fg.push_back(make_pair(i,w));}
    inline void adduser(int i,double w){fu.push_back(make_pair(i,w));}
    inline void additem(int i,double w){fi.push_back(make_pair(i,w));}
};

struct SVD{
    int K;
    double lambda,bias_lambda;
    double gamma;
    int ng,nu,ni;
    double loss,rmse;
    vector<double> global;
    vector<pair<double,vector<double> > > user,item;
    vector<svdFeature> train;
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
        train=t.train;
    }
    SVD(){}
    SVD(int K,double lambda,double gamma,int ng,int nu,int ni):K(K),lambda(lambda),bias_lambda(lambda/200),gamma(gamma),ng(ng),nu(nu),ni(ni){
        global=vector<double>(ng,0);
        user.clear();
        for (int i=0;i<nu;i++){
            vector<double> t;
            for (int j=0;j<K;j++) t.push_back(getdouble(-1,1));
            user.push_back(make_pair(0.,t));
        }
        item.clear();
        for (int i=0;i<nu;i++){
            vector<double> t;
            for (int j=0;j<K;j++) t.push_back(getdouble(-1,1));
            item.push_back(make_pair(0.,t));
        }
        train.clear();
    }
    void addTrain(svdFeature t){
        train.push_back(t);
    }
    vector<double> evaluate(vector<svdFeature> query){
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
        }
        for (int k=0;k<K;k++){
            for (int i=0;i<user.size();i++) loss+=lambda*user[i].second[k]*user[i].second[k];
            for (int i=0;i<item.size();i++) loss+=lambda*item[i].second[k]*item[i].second[k];
        }
        for (int i=0;i<user.size();i++) loss+=bias_lambda*user[i].first*user[i].first;
        for (int i=0;i<item.size();i++) loss+=bias_lambda*item[i].first*item[i].first;
        rmse=sqrt(rmse/train.size());
    }
    inline double evaluate(svdFeature t){
        double sum=0;
        for (int i=0;i<t.fg.size();i++) sum+=global[t.fg[i].first]*t.fg[i].second;
        vector<double> U=vector<double>(K,0);
        vector<double> V=vector<double>(K,0);
        double swu=0,swi=0;
        double sg=sum;
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
            sum+=item[i].first*w;
            for (int j=0;j<K;j++) V[j]+=item[i].second[j]*w;
            swi+=w;
        }
        double tsg=sum;
        for (int i=0;i<K;i++) sum+=U[i]*V[i]/swu/swi;
        //if (rand()%100000==0) printf("%.3f %.3f %.3f\n",sg,tsg-sg,sum-tsg);
        return sum;
    }
    inline void Stochastic(svdFeature t){
        double e=evaluate(t);
        loss+=(t.rate-e)*(t.rate-e)*t.weight;
        rmse+=min(625.,(t.rate-e)*(t.rate-e))*t.weight;
        double g=(t.rate-e)*t.weight;
        vector<double> U=vector<double>(K,0);
        vector<double> V=vector<double>(K,0);
        double swu=0,swi=0;
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
            item[i].first+=(g-item[i].first*bias_lambda)*gamma*w/swi;
        }
        for (int z=0;z<t.fg.size();z++){
            int i=t.fg[z].first;
            global[i]+=g*gamma*t.fg[z].second;
        }
    }
    double getloss(){return loss;}
    double getrmse(){return rmse;}
};

double getdouble(char *s,double def=0){
    double t;
    if (sscanf(s,"%lf",&t)!=1) return def;
    return t;
}
int getdate(char *s){
    int y,m,d;
    if (sscanf(s,"%d%*c%d%*c%d",&y,&m,&d)!=3) return 2000;
    return (y-2000)*100+m;
}
int getherb(string s){
    if (s=="NULL") return 0;
    if (s=="cov") return 1;
    if (s=="RR1") return 2;
    if (s=="RR2Y") return 3;
}
int getloc(string s){
    if (s=="NULL") return -1;
    return atoi(s.c_str());
}
struct Train{
    int eid,loc,repno,mid,herb;
    double yield;
    double m,rm;
    int date,year,month;
    int pid,qid,repid;
    Train(){}
    Train(string ts){
        char s[10000];
        sprintf(s,"%s",ts.c_str());
        char *p=strtok(s,",");eid=atoi(p);
        p=strtok(NULL,",");loc=getloc(p);
        p=strtok(NULL,",");repno=atoi(p);
        p=strtok(NULL,",");mid=atoi(p);
        p=strtok(NULL,",");herb=getherb(p);
        p=strtok(NULL,",");yield=getdouble(p);
        p=strtok(NULL,",");m=getdouble(p);
        p=strtok(NULL,",");rm=getdouble(p,9);
        p=strtok(NULL,",");date=getdate(p);year=date/100;month=date%100;
    }
};
struct Query{
    int loc,mid,herb,eid,repno;
    double rm;
    int date,year,month;
    int pid,qid,repid;
    Query(){}
    Query(string ts){
        char s[10000];
        sprintf(s,"%s",ts.c_str());
        char *p=strtok(s,",");eid=getloc(p);
        p=strtok(NULL,",");loc=getloc(p);
        p=strtok(NULL,",");repno=getloc(p);
        p=strtok(NULL,",");mid=atoi(p);
        p=strtok(NULL,",");herb=getherb(p);
        p=strtok(NULL,",");rm=getdouble(p,9);
        p=strtok(NULL,",");date=getdate(p);year=date/100;month=date%100;
    }
    Query(Train t){
        loc=t.loc;
        mid=t.mid;
        eid=t.eid;
        repno=t.repno;
        rm=t.rm;
        year=t.year;
        month=t.month;
        pid=t.pid;
        qid=t.qid;
        repid=t.repid;
    }
};
int NZONE;
map<int,int> mzone;
struct Location{
    double x,y;
    int locid;
    int mz;
    int col;
    int noaa1,noaa2;
    Location(){}
    int getsubzone(string s){
        if (s=="Late") return 2;
        if (s=="Mid") return 1;
        return 0;
    }
    Location(string ts){
        char s[10000];
        sprintf(s,"%s",ts.c_str());
        char *p=strtok(s,",");locid=atoi(p);
        p=strtok(NULL,",");x=getdouble(p);
        p=strtok(NULL,",");y=getdouble(p);
        p=strtok(NULL,",");
        int t1,t2;
        p=strtok(NULL,",");t1=atoi(p);
        p=strtok(NULL,",");t2=getsubzone(p);
        mz=t1*3+t2;
        NZONE=max(mz+1,NZONE);
        p=strtok(NULL,",");col=atoi(p);
        p=strtok(NULL,",");noaa1=atoi(p);
        p=strtok(NULL,",");noaa2=atoi(p);
    }
};
vector<Train> train;
vector<Query> query;
vector<Location> locs;
vector<pair<double,double> > pos;
vector<svdFeature> svdquery;
double b;
int NP,NQ,NMID,NLOC,NEXP,NREP;
int NTraining,NOriginalTraining;
map <pair<int,int>,int> pid,qid;
map <pair<int,pair<int,int> >,int > rep;
vector<int> PCNT,QCNT;
SVD svd,last_svd;
vector<vector<pair<int,int> > > NOAAcode;
vector<vector<double> > loc_noaa;
vector<int> EXP_CNT;

class OmnipotentYieldPredictor{
    public:
    int NMID,NLOC;
    int getpid(int i,int j){
        if (pid.find(MP(i,j))==pid.end())
            return pid[MP(i,j)]=pid.size()-1;
        else return pid[MP(i,j)];
    }
    int getqid(int i,int j){
        if (qid.find(MP(i,j))==qid.end())
            return qid[MP(i,j)]=qid.size()-1;
        else return qid[MP(i,j)];
    }
    int getrepid(int e,int l,int r){
        if (rep.find(MP(e,MP(l,r)))==rep.end())
            return rep[MP(e,MP(l,r))]=rep.size()-1;
        else return rep[MP(e,MP(l,r))];
    }
    double loc_dist(int i,int j){
        return sqrt((pos[i].first-pos[j].first)*(pos[i].first-pos[j].first)+(pos[i].second-pos[j].second)*(pos[i].second-pos[j].second));
    }
    int ti_last[21];
    void fixtime_prep(vector<string> &a){
        for (int z=0;z<a.size();z++){
            Train t=Train(a[z]);
            ti_last[t.year]=max(ti_last[t.year],t.eid);
        }
    }
    int fixtimebyeid(int eid){
        for (int i=0;i<20;i++) if (ti_last[i]>=eid) return i;
        return 19;
    }
    void fixtime(){
        //for (int i=0;i<train.size();i++) ti_last[train[i].year]=max(ti_last[train[i].year],train[i].eid);
        //for (int i=0;i<query.size();i++) ti_last[query[i].year]=max(ti_last[query[i].year],query[i].eid);
        for (int i=0;i<train.size();i++)
            if (train[i].year==20) train[i].year=fixtimebyeid(train[i].eid);
        for (int i=0;i<query.size();i++)
            if (query[i].year==20) query[i].year=fixtimebyeid(query[i].eid);
    }
    void reid(){
        vector<int> t;t.clear();
        for (int i=0;i<train.size();i++) t.PB(train[i].mid);
        for (int i=0;i<query.size();i++) t.PB(query[i].mid);
        sort(t.begin(),t.end());
        t.erase(unique(t.begin(),t.end()),t.end());
        for (int i=0;i<train.size();i++) train[i].mid=lower_bound(t.begin(),t.end(),train[i].mid)-t.begin();
        for (int i=0;i<query.size();i++) query[i].mid=lower_bound(t.begin(),t.end(),query[i].mid)-t.begin();
        NMID=t.size();
        t.clear();
        for (int i=0;i<train.size();i++) t.PB(train[i].eid);
        for (int i=0;i<query.size();i++) t.PB(query[i].eid);
        sort(t.begin(),t.end());
        t.erase(unique(t.begin(),t.end()),t.end());
        for (int i=0;i<train.size();i++) train[i].eid=lower_bound(t.begin(),t.end(),train[i].eid)-t.begin();
        for (int i=0;i<query.size();i++) query[i].eid=lower_bound(t.begin(),t.end(),query[i].eid)-t.begin();
        NEXP=t.size();
        EXP_CNT=vector<int>(NEXP,0);
        for (int i=0;i<train.size();i++) EXP_CNT[train[i].eid]++;
        t.clear();
        for (int i=0;i<train.size();i++) t.PB(train[i].loc);
        for (int i=0;i<query.size();i++) t.PB(query[i].loc);
        for (int i=0;i<locs.size();i++) t.PB(locs[i].locid);
        sort(t.begin(),t.end());
        t.erase(unique(t.begin(),t.end()),t.end());
        for (int i=0;i<train.size();i++) train[i].loc=lower_bound(t.begin(),t.end(),train[i].loc)-t.begin();
        for (int i=0;i<query.size();i++) query[i].loc=lower_bound(t.begin(),t.end(),query[i].loc)-t.begin();
        mzone.clear();
        for (int i=0;i<locs.size();i++) {
            locs[i].locid=lower_bound(t.begin(),t.end(),locs[i].locid)-t.begin();
            mzone[locs[i].locid]=locs[i].mz;
        }
        NLOC=t.size();
        pos=vector<pair<double,double> >(NLOC);
        NOAAcode=vector<vector<pair<int,int> > >(NLOC);
        for (int i=0;i<locs.size();i++) {
            NOAAcode[locs[i].locid].PB(MP(locs[i].noaa1,locs[i].noaa2));
            pos[locs[i].locid]=MP(locs[i].x+pos[locs[i].locid].first,locs[i].y+pos[locs[i].locid].second);
        }
        for (int i=0;i<NLOC;i++) if (NOAAcode[i].size())
            pos[i]=MP(pos[i].first/NOAAcode[i].size(),pos[i].second/NOAAcode[i].size());
        pid.clear();
        qid.clear();
        rep.clear();
        int z=0;
        for (int i=0;i<train.size();i++) {
            train[i].pid=getpid(train[i].mid,train[i].herb);
            train[i].qid=getqid(train[i].loc,train[i].year);
            train[i].repid=getrepid(train[i].eid,train[i].loc,train[i].repno);
        }
        for (int i=0;i<query.size();i++) {
            query[i].pid=getpid(query[i].mid,query[i].herb);
            query[i].qid=getqid(query[i].loc,query[i].year);
            query[i].repid=getrepid(query[i].eid,query[i].loc,query[i].repno);
        }
        cout<<z<<endl;
        NP=pid.size();
        NQ=qid.size();
        NREP=rep.size();
        PCNT=vector<int>(NP,0);
        QCNT=vector<int>(NQ,0);
        for (int i=0;i<train.size();i++){
            PCNT[train[i].pid]++;
            QCNT[train[i].qid]++;
        }
        return;
        for (int i=0;i<query.size();i++){
            printf("(%d,%d) ",PCNT[query[i].pid],QCNT[query[i].qid]);
        }
    }
    void NOAAloader(vector<string> noaa){
        loc_noaa.clear();
        vector<int> qcnt=vector<int>(NQ,0);
        for (int i=0;i<NQ;i++) loc_noaa.PB(vector<double>(15,0));
        double sd[15],ma[15];
        memset(sd,0,sizeof(sd));
        memset(ma,0,sizeof(ma));
        int totcnt=0;
        for (int z=1;z<noaa.size();z++){
            char s[10000];
            sprintf(s,"%s",noaa[z].c_str());
            char *p=strtok(s,",");
            int noaa1=atoi(p);
            p=strtok(NULL,",");int noaa2=atoi(p);
            p=strtok(NULL,",");int ti=atoi(p);ti=ti/100-2000;
            if (ti<0||ti>5) continue;
            double d[15];
            for (int i=0;i<15;i++)
                p=strtok(NULL,","),d[i]=getdouble(p,0),sd[i]+=d[i],ma[i]=max(ma[i],fabs(d[i]));
            totcnt++;
            for (int loc=0;loc<NLOC;loc++){
                int cnt=0;
                for (int i=0;i<NOAAcode[loc].size();i++) cnt+=NOAAcode[loc][i]==MP(noaa1,noaa2);
                if (cnt==0) continue;
                int q=getqid(loc,ti);
                qcnt[q]++;
                for (int i=0;i<15;i++) 
                    loc_noaa[q][i]+=d[i]*cnt;
            }
        }
        for (int i=0;i<15;i++) sd[i]/=totcnt;
        for (int loc=0;loc<NLOC;loc++)
        for (int ti=0;ti<10;ti++)if (qcnt[getqid(loc,ti)]){
            int q=getqid(loc,ti);
            for (int i=0;i<15;i++) loc_noaa[q][i]=loc_noaa[q][i]/qcnt[q]/ma[i];
        }
        else{
            int q=getqid(loc,ti);
            for (int i=0;i<15;i++) loc_noaa[q][i]=sd[i]/ma[i];
        }
    }
    svdFeature toSVDFeature(Train t,double y){
        svdFeature svd;
        svd.setrate(y);
        
        svd.addglobal(0,1);
        
        svd.adduser(t.pid,1);
        svd.adduser(t.eid+NP,1);
        svd.adduser(t.herb+NP+NEXP,1);
        svd.adduser(t.repid+NP+NEXP+4,1);
        svd.adduser(t.year+NP+NEXP+4+NREP,1);
        //svd.adduser(t.month+NP+NEXP+4+NREP+20,1);
        
        svd.additem(t.qid,1);
        svd.additem(t.year+NQ,1);
        svd.additem(t.loc+NQ+20,1);
        svd.additem(t.repid+NQ+20+NLOC,1);
        svd.additem(t.eid+NQ+20+NLOC+NREP,1);
        //svd.additem(t.month+NQ+20+NLOC+NREP+NEXP,1);
        //svd.additem(t.herb+NQ+20+NLOC+NREP+NEXP+13,1);
        
        return svd;
    }
    svdFeature toSVDFeature(Query t,double y){
        svdFeature svd;
        svd.setrate(y);
        
        svd.addglobal(0,1);
        
        svd.adduser(t.pid,1);
        svd.adduser(t.eid+NP,1);
        svd.adduser(t.herb+NP+NEXP,1);
        svd.adduser(t.repid+NP+NEXP+4,1);
        svd.adduser(t.year+NP+NEXP+4+NREP,1);
        //svd.adduser(t.month+NP+NEXP+4+NREP+20,1);
        
        svd.additem(t.qid,1);
        svd.additem(t.year+NQ,1);
        svd.additem(t.loc+NQ+20,1);
        svd.additem(t.repid+NQ+20+NLOC,1);
        svd.additem(t.eid+NQ+20+NLOC+NREP,1);
        //svd.additem(t.month+NQ+20+NLOC+NREP+NEXP,1);
        //svd.additem(t.herb+NQ+20+NLOC+NREP+NEXP+13,1);
        
        return svd;
    }
    vector <double> predictYield(vector <string> Training, vector <string> droughtMonitor, vector <string> droughtNOAA, vector <string> locations, vector <string> queries, vector <string> experiment){
        train.clear();
        srand(12345);
        memset(ti_last,0,sizeof(ti_last));
        fixtime_prep(Training);
        fixtime_prep(experiment);
        NOriginalTraining=Training.size();
        Training.clear();
        for (int z=0;z<experiment.size();z++) Training.PB(experiment[z]);
        NTraining=Training.size();
        for (int i=0;i<Training.size();i++) train.PB(Train(Training[i]));
        query.clear();
        for (int i=0;i<queries.size();i++) query.PB(Query(queries[i]));
        locs.clear();
        for (int i=0;i<locations.size();i++) locs.PB(Location(locations[i]));
        fixtime();
        reid();
        //NOAAloader(droughtNOAA);
        printf("#Training = %d\n",train.size());
        printf("#Query = %d\n",query.size());
        printf("#<MID,HERB> = %d\n",NP);
        printf("#<LOC,TIME> = %d\n",NQ);
        printf("#MID = %d\n",NMID);
        printf("#LOC = %d\n",NLOC);
        printf("#NEXP = %d\n",NEXP);
        printf("#REP = %d\n",NREP);
        svd=SVD(100,0.8,1e-2,1,NP+NEXP+4+NREP+20+13,NQ+20+NLOC+NREP+NEXP+13+4);
        cout<<"SVD Constructed"<<endl;
        for (int i=0;i<train.size();i++) svd.addTrain(toSVDFeature(train[i],train[i].yield));
        svdquery.clear();
        for (int i=0;i<query.size();i++) svdquery.PB(toSVDFeature(query[i],-1));
        double lastloss=1e100;
        for (int z=1;clock()/(double)CLOCKS_PER_SEC<60*9;z++){
            last_svd=svd;
            svd.shuffle();
            svd.Train();
            if (z%1==0){
                vector<double> res=svd.evaluate(svdquery);
                printf("Round = %d RMSE = %.3f RMSE(Train) = %.3f loss = %.3f time = %.3f\n",z,evaluate(res),svd.getrmse(),svd.getloss(),clock()/(double)CLOCKS_PER_SEC);
                //for (int i=0;i<15;i++) printf("%.3f ",svd.global[1+NZONE+91+i]);puts("");
            }
            if (svd.getloss()!=svd.getloss()||svd.getloss()>lastloss) {
                svd=last_svd;
                svd.gamma/=2;
                printf("recovery with new gamma = %.10f and lastloss = %.3f\n",svd.gamma,lastloss);
            }
            else {
                lastloss=svd.getloss();
                svd.gamma*=1.3;
            }
        }
        vector<double> res=svd.evaluate(svdquery);
        return res;
    }
    double evaluate(vector<double> res){
        freopen("valid_result.csv","r",stdin);
        double sum=0;
        int cnt=0;
        for (double t;scanf("%lf",&t)==1;){
            sum+=min(625.,(t-res[cnt])*(t-res[cnt]));
            //printf("%.3f %.3f\n",t,res[cnt]);
            cnt++;
        }
        return sqrt(sum/cnt);
        return 0;
    }
};
