// TopCoder Marathon - soybean 1
// author: elder1g

#include <cctype>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
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

const double eps = 1e-8;
#define MAX_VARS_IN_EXP 100

int year_suc[2500];
int year_tot[2500];
double year_ratio[2500];

int trialcnt_suc[50];
int trialcnt_tot[50];
double trialcnt_ratio[50];

int cnt_sta_suc[50];
int cnt_sta_tot[50];
double cnt_sta_ratio[50];

void init_info()
{
    year_suc[2000]=1;year_tot[2000]=3000;year_ratio[2000]=0.000333333;
    year_suc[2001]=28;year_tot[2001]=4980;year_ratio[2001]=0.00562249;
    year_suc[2002]=104;year_tot[2002]=6952;year_ratio[2002]=0.0149597;
    year_suc[2003]=113;year_tot[2003]=10096;year_ratio[2003]=0.0111926;
    year_suc[2004]=60;year_tot[2004]=9364;year_ratio[2004]=0.00640752;
    year_suc[2005]=98;year_tot[2005]=13696;year_ratio[2005]=0.00715537;
    year_suc[2006]=104;year_tot[2006]=6336;year_ratio[2006]=0.0164141;
    year_suc[2007]=168;year_tot[2007]=15012;year_ratio[2007]=0.011191;
    year_suc[2008]=113;year_tot[2008]=15120;year_ratio[2008]=0.00747354;
    
    trialcnt_suc[1]=18;trialcnt_tot[1]=3892;trialcnt_ratio[1]=0.00462487;
    trialcnt_suc[2]=29;trialcnt_tot[2]=11452;trialcnt_ratio[2]=0.00253231;
    trialcnt_suc[3]=29;trialcnt_tot[3]=11588;trialcnt_ratio[3]=0.00250259;
    trialcnt_suc[4]=87;trialcnt_tot[4]=9936;trialcnt_ratio[4]=0.00875604;
    trialcnt_suc[5]=99;trialcnt_tot[5]=9164;trialcnt_ratio[5]=0.0108031;
    trialcnt_suc[6]=100;trialcnt_tot[6]=7984;trialcnt_ratio[6]=0.0125251;
    trialcnt_suc[7]=82;trialcnt_tot[7]=5688;trialcnt_ratio[7]=0.0144163;
    trialcnt_suc[8]=98;trialcnt_tot[8]=7212;trialcnt_ratio[8]=0.0135885;
    trialcnt_suc[9]=94;trialcnt_tot[9]=5364;trialcnt_ratio[9]=0.0175242;
    trialcnt_suc[10]=84;trialcnt_tot[10]=7056;trialcnt_ratio[10]=0.0119048;
    trialcnt_suc[11]=22;trialcnt_tot[11]=1872;trialcnt_ratio[11]=0.0117521;
    trialcnt_suc[12]=35;trialcnt_tot[12]=2772;trialcnt_ratio[12]=0.0126263;
    trialcnt_suc[13]=3;trialcnt_tot[13]=72;trialcnt_ratio[13]=0.0416667;
    trialcnt_suc[14]=2;trialcnt_tot[14]=180;trialcnt_ratio[14]=0.0111111;
    trialcnt_suc[15]=4;trialcnt_tot[15]=72;trialcnt_ratio[15]=0.0555556;
    trialcnt_suc[16]=3;trialcnt_tot[16]=108;trialcnt_ratio[16]=0.0277778;
    trialcnt_suc[17]=0;trialcnt_tot[17]=72;trialcnt_ratio[17]=0;
    trialcnt_suc[19]=0;trialcnt_tot[19]=36;trialcnt_ratio[19]=0;
    trialcnt_suc[28]=0;trialcnt_tot[28]=36;trialcnt_ratio[28]=0;
    
    cnt_sta_suc[36]=768;cnt_sta_tot[36]=49135;cnt_sta_ratio[36]=0.0156304;
    cnt_sta_suc[40]=21;cnt_sta_tot[40]=25496;cnt_sta_ratio[40]=0.000823659;
    
    for (int i=0;i<50;++i)
        if (trialcnt_tot[i]<200) trialcnt_ratio[i]=0;
}

struct Trial
{
    int loccd;
    int rep;
    int rep_tot;
    bool mn_ava;
    double yields[MAX_VARS_IN_EXP];
    int mns[MAX_VARS_IN_EXP];
};



struct Variety
{
    int vid;
    string type;
    double rm;
    int ischeck;
    int iselite;
    //Performance
    double wins_cnt;
    double tot_cnt;
    double square_sum;
    double estimate;
    double mins;
    Variety()
    {
        wins_cnt=0;
        tot_cnt=0;
        estimate=0;
        square_sum=0;
        mins=10000;
    }
};

struct Experiment
{
    int id;
    int year;
    vector<Trial> trials;
    vector<Variety> vars;
    int loccds_cnt;
    int elite_count;
    int check_count;
    double avg_rm;
    Trial& find_trial(int loccd, int rep)
    {
        for (int i=0;i<trials.size();++i)
            if (trials[i].loccd==loccd && trials[i].rep==rep) return trials[i];
        Trial newtrial;
        newtrial.loccd=loccd;
        newtrial.rep=rep;
        trials.push_back(newtrial);
        return trials.back();
    }
};

//analyze use, shared by main part
map<int, int> eid_to_pos;
vector<Experiment> exps;
map<int, int> vid_to_eid;
map<int, int> vid_to_pos;
map<pair<int, int>, int> exp_loc_cnt;

//real analyze
int exp_year_count[3000];

double overall_estimate(Variety& var)
{
    double estimate=0;
    if (var.ischeck) estimate-=(1e+10);//elite is not check
    if (var.tot_cnt<eps) estimate-=(1e+9);//no compare at all,quite bad
    else
    {
        estimate+=var.wins_cnt/var.tot_cnt*(1e+7);
        if (var.type=="RR2Y") estimate-=(1e+9);
        if (estimate>0)
        {
            Experiment& exper=exps[eid_to_pos[vid_to_eid[var.vid]]];
            int tct=(int)exper.trials.size();
            double mna_cnt=0;
            for (int i=0;i<tct;++i)
                if (exper.trials[i].mn_ava) mna_cnt++;
            double mna_ratio=mna_cnt/tct;
            
            if (mna_ratio<0.1) estimate*=0.7;
            else if (mna_ratio>0.9) estimate*=1.05;
            int year=exper.year;
            if (var.type=="conv")
            {
                if (year<=2001) estimate-=(1e+9);
                else if (year!=2005) estimate*=0.85;
            }
            //ensure top ones don't contain vars from unstable(too small) exps.
            if (tct==1) estimate*=0.7;
            if (tct==2) estimate*=0.7;
            if (tct>=7 && tct<=9) estimate*=1.03;
            estimate*=(1+trialcnt_ratio[tct]);
            
            /*
            double ex2=var.square_sum/tct;
            double ex_2=(var.wins_cnt*var.wins_cnt/var.tot_cnt/var.tot_cnt);
            double dx=ex2-ex_2;
            if (dx>0.05) estimate*=(1-0.1*dx);
            */
                        
            if (exper.vars.size()==40)
                estimate*=0.7;
            if (exper.vars.size()==36 && exper.check_count==4) estimate*=1.1;
            if (exper.vars.size()==36 && exper.check_count==5 /*&& var.type!="conv"*/) estimate*=1.15;
            if (exper.vars.size()==36 && exper.check_count>=6 && exper.check_count<=11) estimate*=1.1;
                                    
            
            estimate*=(1+5*pow(year_ratio[year],0.3));
            
            if ((year==2002 || year==2006) && var.type=="RR1") estimate*=1.05;
            
            //int rm_index=(int)(exper.avg_rm*2+0.5);
            //if (rm_index==7) estimate*=1.00;
            
        }
    }
    return estimate;
}


void real_analyze(string filename)
{
    string afilename="ana_";
    for (int i=0;i<filename.size();++i)
    {
        if (filename[i]=='.') break;
        afilename+=filename[i];
    }
    afilename+=".txt";
    ofstream out(afilename.c_str());
    out<<"Exp count:"<<exps.size()<<endl;
    for (int i=0;i<exps.size();++i)
        exp_year_count[exps[i].year]++;
    for (int i=0;i<3000;++i)
        if (exp_year_count[i]!=0)
            out<<"Year "<<i<<":"<<exp_year_count[i]<<endl;
    out<<"----------"<<endl;
    int tot_vars=0;
    int tot_elite=0;
    map<string, pair<int, int> > type_cnt;
    map<int, pair<int, int> > trials_count_cnt;
    map<int, pair<int, int> > year_cnt;
    map<int, pair<int, int> > loccds_count_cnt;
    map<pair<int,string>, pair<int, int> > year_type_cnt;
    for (int i=0;i<exps.size();++i)
    {
        tot_vars+=exps[i].vars.size();
        for (int j=0;j<exps[i].vars.size();++j)
        {
            type_cnt[exps[i].vars[j].type].second++;
            trials_count_cnt[exps[i].trials.size()].second++;
            year_cnt[exps[i].year].second++;
            loccds_count_cnt[exps[i].loccds_cnt].second++;
            year_type_cnt[make_pair(exps[i].year, exps[i].vars[j].type)].second++;
            if (exps[i].vars[j].iselite)
            {
                ++tot_elite;
                type_cnt[exps[i].vars[j].type].first++;
                trials_count_cnt[exps[i].trials.size()].first++;
                year_cnt[exps[i].year].first++;
                loccds_count_cnt[exps[i].loccds_cnt].first++;
                year_type_cnt[make_pair(exps[i].year, exps[i].vars[j].type)].first++;
            }
        }
    }
    out<<"Tot vars:"<<tot_vars<<endl;
    out<<"Tot elites:"<<tot_elite<<endl;
    out<<"----------"<<endl;
    for(map<pair<int,string> ,pair<int,int> >::iterator it=year_type_cnt.begin();it!=year_type_cnt.end();++it)
        out<<"Year-Type "<<it->first.first<<" "<<it->first.second<<":"<<it->second.first<<"/"<<it->second.second<<"("<<it->second.first*1.0/it->second.second<<")"<<endl;
    out<<"----------"<<endl;
    for(map<string,pair<int,int> >::iterator it=type_cnt.begin();it!=type_cnt.end();++it)
        out<<"Type "<<it->first<<":"<<it->second.first<<"/"<<it->second.second<<"("<<it->second.first*1.0/it->second.second<<")"<<endl;
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=trials_count_cnt.begin();it!=trials_count_cnt.end();++it)
    {
        out<<"trialcnt_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"trialcnt_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"trialcnt_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=year_cnt.begin();it!=year_cnt.end();++it)
    {
        out<<"year_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"year_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"year_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=loccds_count_cnt.begin();it!=loccds_count_cnt.end();++it)
        out<<"Loccd Cnt "<<it->first<<":"<<it->second.first<<"/"<<it->second.second<<"("<<it->second.first*1.0/it->second.second<<")"<<endl;
    out<<"----------"<<endl;
    double tot[2][2];//first dimension: is elite, second dimension: is check
    double sco[2][2];
    memset(tot,0,sizeof(tot));
    memset(sco,0,sizeof(sco));
    double mncnt=0;
    double mntot=0;
    for (int i=0;i<exps.size();++i)
    {
        int var_cnt=exps[i].vars.size();
        for (int t=0;t<exps[i].trials.size();++t)
        {
            for (int j=0;j<var_cnt;++j)
            {
                if (exps[i].vars[j].ischeck) continue;
                int p1=vid_to_pos[exps[i].vars[j].vid];
                if (exps[i].trials[t].yields[p1]<0) continue;
                int ind1=exps[i].vars[j].iselite;
                for (int k=0;k<var_cnt;++k)
                {
                    if (j==k) continue;
                    int p2=vid_to_pos[exps[i].vars[k].vid];
                    if (exps[i].trials[t].yields[p2]<0) continue;
                    int ind2=exps[i].vars[k].ischeck;
                    tot[ind1][ind2]++;
                    double s1=exps[i].trials[t].yields[p1];
                    double s2=exps[i].trials[t].yields[p2];
                    if (s1-eps>s2) sco[ind1][ind2]++;
                    else if (s1+eps>s2) sco[ind1][ind2]+=0.5;
                    
                    //////
                    if (ind2==0)
                    {
                        //both are not check
                        if (exps[i].trials[t].yields[p1]>0 && exps[i].trials[t].yields[p2]>0 &&
                            exps[i].trials[t].mns[p1]>0 && exps[i].trials[t].mns[p2]>0 &&
                                exps[i].trials[t].mns[p1]!=exps[i].trials[t].mns[p2])
                        {
                            double rt=(exps[i].trials[t].yields[p1]-exps[i].trials[t].yields[p2])
                                /(exps[i].trials[t].mns[p1]-exps[i].trials[t].mns[p2]);
                            mncnt++;
                            mntot+=rt;
                        }
                    }
                }
            }
        }
    }
    out<<"YIELD FOR PER MN:"<<mntot/mncnt<<endl;
    out<<"----------"<<endl;    
    for (int i=0;i<2;++i)
        for (int j=0;j<2;++j)
        {
            out<<"sco_cmp["<<i<<"]["<<j<<"]="<<sco[i][j]<<";";
            out<<"tot_cmp["<<i<<"]["<<j<<"]="<<tot[i][j]<<";";
            out<<"rto_cmp["<<i<<"]["<<j<<"]="<<sco[i][j]/tot[i][j]<<";";
            out<<endl;
        }
    out<<"----------"<<endl;
    map<int, pair<int, int> > cnt_sta;
    map<pair<int, int>, pair<int, int> > check_cnt_sta;
    for (int i=0;i<exps.size();++i)
    {
        int pa=exps[i].vars.size();
        int pb=exps[i].check_count;
        int pc=exps[i].elite_count;
        cnt_sta[pa].first+=pc;
        cnt_sta[pa].second+=(pa-pb);
        check_cnt_sta[make_pair(pa, pb)].first+=pc;
        check_cnt_sta[make_pair(pa, pb)].second+=(pa-pb);
    }
    for (map<int, pair<int, int> >::iterator itr=cnt_sta.begin();itr!=cnt_sta.end();++itr)
    {
        out<<"cnt_sta_suc["<<itr->first<<"]="<<itr->second.first<<";";
        out<<"cnt_sta_tot["<<itr->first<<"]="<<itr->second.second<<";";
        out<<"cnt_sta_ratio["<<itr->first<<"]="<<itr->second.first*1.0/itr->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for (map<pair<int,int>, pair<int, int> >::iterator itr=check_cnt_sta.begin();itr!=check_cnt_sta.end();++itr)
    {
        out<<"check_cnt_sta_suc["<<itr->first.first<<"]["<<itr->first.second<<"]="<<itr->second.first<<";";
        out<<"check_cnt_sta_tot["<<itr->first.first<<"]["<<itr->first.second<<"]="<<itr->second.second<<";";
        out<<"check_cnt_sta_ratio["<<itr->first.first<<"]["<<itr->first.second<<"]="<<itr->second.first*1.0/itr->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    int suc_cnt_sta[50];
    memset(suc_cnt_sta,0,sizeof(suc_cnt_sta));
    int rm_cnt_suc[500];
    int rm_cnt_tot[500];
    memset(rm_cnt_suc,0,sizeof(rm_cnt_suc));
    memset(rm_cnt_tot,0,sizeof(rm_cnt_tot));
    for (int i=0;i<exps.size();++i)
    {
        suc_cnt_sta[exps[i].elite_count]++;
        int rm_index=(int)(exps[i].avg_rm*2+0.5);
        if (rm_index>100) cout<<" "<<exps[i].avg_rm;
        rm_cnt_tot[rm_index]+=(exps[i].vars.size()-exps[i].check_count);
        rm_cnt_suc[rm_index]+=exps[i].elite_count;
    }
    for (int i=0;i<50;++i)
        if(suc_cnt_sta[i]!=0)
            out<<"Success "<<i<<": "<<suc_cnt_sta[i]<<endl;
    out<<"----------"<<endl;
    for (int i=0;i<500;++i)
        if (rm_cnt_tot[i]!=0)
        {
            out<<"rm_suc_rds["<<i<<"]="<<rm_cnt_suc[i]<<";";
            out<<"rm_tot_rds["<<i<<"]="<<rm_cnt_tot[i]<<";";
            out<<"rm_ratio_rds["<<i<<"]="<<rm_cnt_suc[i]*1.0/rm_cnt_tot[i]<<";"<<endl;
        }
            
}

void construct_datastructure(vector<string>& data, bool havelastcolumn)
{
        int experiment_id;
        int year;
        int loccd;
        int rep;
        string type;
        int variety_id;
        double yield;
        int mn;
        double rm;
        int ischeck;
        int iselite;
        string str;
        for (int i=0;i<data.size();++i)
        {
            for (int p=0;p<data[i].size();++p)
                if(data[i][p]==',') data[i][p]=' ';
            stringstream se(data[i]);
            se>>experiment_id>>year>>loccd>>rep>>type>>variety_id;
            se>>str;
            if(str=="NULL") yield=-1; else yield=strtodouble(str);
            se>>str;
            if(str=="NULL") mn=-1; else mn=strtoint(str);
            se>>str;
            if(str=="NULL") rm=-1; else rm=strtodouble(str);
            se>>ischeck;
            if (havelastcolumn) se>>iselite;
            if (eid_to_pos.count(experiment_id)==0)
            {
                Experiment ex;
                ex.id=experiment_id;
                ex.year=year;
                eid_to_pos[experiment_id]=exps.size();
                exps.push_back(ex);
            }
            Experiment& ex=exps[eid_to_pos[experiment_id]];
            Trial& trial=ex.find_trial(loccd,rep);
            if (vid_to_eid.count(variety_id)==0)
            {
                vid_to_eid[variety_id]=experiment_id;
                vid_to_pos[variety_id]=ex.vars.size();
                Variety var;
                var.vid=variety_id;
                var.type=type;
                var.rm=rm;
                var.ischeck=ischeck;
                var.iselite=iselite;
                ex.vars.push_back(var);
                ex.vars.back().wins_cnt=0;
                ex.vars.back().tot_cnt=0;
            }
            int pos=vid_to_pos[variety_id];
            trial.yields[pos]=yield;
            trial.mns[pos]=mn;
        }
        for (int i=0;i<exps.size();++i)
        {
            set<int> loccds;
            for (int j=0;j<exps[i].trials.size();++j)
            {    
                loccds.insert(exps[i].trials[j].loccd);
                exp_loc_cnt[make_pair(exps[i].id,exps[i].trials[j].loccd)]++;
            }
            exps[i].loccds_cnt=loccds.size();
        }
        for (int i=0;i<exps.size();++i)
        {
            for (int j=0;j<exps[i].trials.size();++j)
            {
                exps[i].trials[j].rep_tot=exp_loc_cnt[make_pair(exps[i].id,exps[i].trials[j].loccd)];
            }
        }
        for (int i=0;i<exps.size();++i)
        {
            exps[i].elite_count=0;
            exps[i].check_count=0;
            exps[i].avg_rm=0;
            int valid_rms=0;
            for (int j=0;j<exps[i].vars.size();++j)
            {
                if (exps[i].vars[j].iselite)
                    exps[i].elite_count++;
                if (exps[i].vars[j].ischeck)
                {
                    exps[i].check_count++;
                    if (exps[i].vars[j].rm>0)
                    {
                        valid_rms++;
                        exps[i].avg_rm+=exps[i].vars[j].rm;
                    }
                }
            }
            exps[i].avg_rm/=valid_rms;
        }
}

map<int, pair<double, int> > location_info;

void construct_location_data(vector<string>& locations)
{
    int loccd;
    int band;
    string sub_band;
    int zone;
    for (int i=0;i<locations.size();++i)
    {
        string& str=locations[i];
        for (int p=0;p<str.size();++p)
            if(str[p]==',') str[p]=' ';
        stringstream se(str);
        se>>loccd>>band>>sub_band>>zone;
        double band_number=band;
        //one loccd many have several records....
        //if(sub_band=="Early" band_number+=0.33;
        //else if(sub_band=="Mid" band_number+=0.66;
        //else if(sub_band=="Late" band_number+=0.99;
        location_info[loccd]=make_pair(band_number,zone);
    }
}

struct EliteClassifier
{
    vector<int> classify(vector<string>& data, vector<string>& locations)
    {
        init_info();
        construct_datastructure(data,false);
        construct_location_data(locations);
        for (int i=0;i<exps.size();++i)
        {
            for (int j=0;j<exps[i].trials.size();++j)
            {
                for (int k=0;k<exps[i].vars.size();++k)
                {
                    if (exps[i].vars[k].ischeck) continue;
                    int p1=vid_to_pos[exps[i].vars[k].vid];
                    if (exps[i].trials[j].yields[p1]<0) continue;
                    bool mn_available=(exps[i].trials[j].mns[p1]>0);
                    exps[i].trials[j].mn_ava=mn_available;
                    double s1=0;
                    double s2=0;
                    for (int m=0;m<exps[i].vars.size();++m)
                    {
                        if (m==k) continue;
                        int p2=vid_to_pos[exps[i].vars[m].vid];
                        if (exps[i].trials[j].yields[p2]<0) continue;
                        double evalue1=exps[i].trials[j].yields[p1];
                        double evalue2=exps[i].trials[j].yields[p2];
                        if (exps[i].trials[j].mns[p1]>0 && exps[i].trials[j].mns[p2]>0)
                        {
                            evalue1-=0.4*exps[i].trials[j].mns[p1];
                            evalue2-=0.4*exps[i].trials[j].mns[p2];
                        }
                        int ind=exps[i].vars[m].ischeck;
                        double wts=1;
                        if (ind!=0) wts=5;
                        s2+=wts;
                        if (evalue1-eps>evalue2)
                            s1+=wts;
                        else if (evalue1+eps>evalue2)
                            s1+=1.0/3.0*wts;
                    }
                    double rwt=1;
                    if (location_info.count(exps[i].trials[j].loccd)==0)
                        rwt*=1.0;
                    else
                    {
                        double band=location_info[exps[i].trials[j].loccd].first;
                        int zone=location_info[exps[i].trials[j].loccd].second;
                        //if (zone==1) rwt*=1;
                        //if (zone==2) rwt*=1;
                        //if (zone==3) rwt*=1;
                        //if (zone==4) rwt*=0.5;
                        //if (zone==5) rwt*=1;
                    }
                    //if (!mn_available) rwt=0.95;
                    rwt/=(15+exps[i].trials[j].rep_tot);
                    double pm=1.3;
                    exps[i].vars[k].wins_cnt+=rwt*pow(s1,pm);//pow possible??
                    exps[i].vars[k].tot_cnt+=rwt*pow(s2,pm);
                    exps[i].vars[k].mins=min(exps[i].vars[k].mins,pm);
                    exps[i].vars[k].square_sum+=pow(s1/s2,pm);
                }
            }
        }
        vector<pair<double,int> > svid;
        for (int i=0;i<exps.size();++i)
            for (int j=0;j<exps[i].vars.size();++j)
            {
                exps[i].vars[j].estimate=overall_estimate(exps[i].vars[j]);
                svid.push_back(make_pair(-exps[i].vars[j].estimate,exps[i].vars[j].vid));
            }
        sort(svid.begin(), svid.end());
        vector<int> ret(svid.size());
        for (int i=0;i<svid.size();++i)
            ret[i]=svid[i].second;
        return ret;
    }
};

#ifdef LOCAL

void analyze(string filename)
{
    ifstream input(filename.c_str());
    vector<string> data;
    data.reserve(2000000);
    string str;
    while(getline(input,str))
    {
        data.push_back(str);
    }
    construct_datastructure(data,true);
    real_analyze(filename);
}

map<int, int> std_ans;
int tot_elite;

void read_data(string filename, vector<string>& data)
{
    ifstream input(filename.c_str());
    data.reserve(2000000);
    string str;
    int tmp_int;
    string tmp_string;
    int variety_id;
    int iselite;
    tot_elite=0;
    std_ans.clear();
    while(getline(input,str))
    {
        data.push_back(str);
        for (int p=0;p<str.size();++p)
            if(str[p]==',') str[p]=' ';
        stringstream se(str);
        se>>tmp_int;
        se>>tmp_int;
        se>>tmp_int;
        se>>tmp_int;
        se>>tmp_string;
        se>>variety_id;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_int;
        se>>iselite;
        if (iselite)
        {
            if (std_ans.count(variety_id)==0)
                tot_elite++;
            else if (std_ans[variety_id]!=iselite)
                cerr<<"Error"<<endl;
        }
        std_ans[variety_id]=iselite;
    }
}

void read_location(string filename, vector<string>& data)
{
    ifstream input(filename.c_str());
    data.reserve(500);
    string str;
    while(getline(input,str))
    {
        data.push_back(str);
    }
}

double calculate_score(vector<int>& guess)
{
    double score=0;
    double total=0;
    double correct=0;
    for (int i=0;i<guess.size();++i)
    {
        total++;
        if (std_ans[guess[i]]==1)
        {
            correct++;
            score+=(1000000.0/tot_elite)*(correct/total);
        }
        else if (i<100)
        {
            cout<<i<<": "<<guess[i]<<endl;
        }
    }
    return score;
}

int main()
{
    EliteClassifier classifier;
    
    vector<string> data;
    read_data("train.csv",data);
    vector<string> locations;
    read_location("Locations.csv",locations);
    vector<int> guess=classifier.classify(data,locations);
    double score=calculate_score(guess);
    cout<<"Score on train set:"<<score<<endl;
    
    //analyze("train.csv");
    return 0;
}
#endif
