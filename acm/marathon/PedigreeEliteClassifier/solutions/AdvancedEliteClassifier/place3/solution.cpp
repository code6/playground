#include <vector>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
using namespace std;
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

struct EliteClassifier1
{
    vector<int> classify(vector<string> data, vector<string> locations)
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
                        //evalue1-=PAR1*exps[i].vars[k].rm;
                        //evalue2-=PAR1*exps[i].vars[m].rm;
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
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int gStat  = 0;
int gDebug = 0;

const int   kMaxYear = 20;
const float kAvg     = 51.2;
const float kAvgMn   = 150.0f;
const float kSmooth  = 0.01;
const float kMnSmooth = 50.0f;
const float kYLSmooth = 90.0f;
//50 26.9613 26.69413
//60 27.1963 26.93826
//70 27.3261 27.0613
//75 27.361
//80 27.391 27.1263
//90 27.4259 27.1255
//100 27.422 27.1158
//110 27.402 27.1515

double year_ratioo[100];
map<int, float> year_loc_avg[20];
map<int, float> year_loc_sum[20];

map<int, float> year_row_avg[20];
map<int, float> year_row_sum[20];

map<int, int> loc2row;

struct VidScore
{
    VidScore() { memset(this, 0, sizeof(VidScore)); }

    void Read(const char** col)
    {
        eid   = atoi(col[0]);
        id    = atoi(col[5]);
        check = atoi(col[9]);
        type  = (col[4][0] == 'R');
        
        year  = atoi(col[1]);   if (year>=2000) year -= 2000;
        yield = atof(col[6]);   if (yield > 80) yield = 80;
        mn    = atof(col[7]);   if (mn < 100) mn = kAvgMn;  if (mn > 200) mn = kAvgMn;
    rm    = atof(col[8]); 
    yield-=0.6*rm;
    //0   27.4259 27.1255
    //-0.6  27.618 27.388 

        
        if (gStat) elite = atoi(col[10]);
    }

    int eid;
    int id;
    int check;
    int elite;
    int year;
    int type;
    float yield;
    float mn;
    double rm;

    float avg;
    float avg_sum;
    float sum;
    float count;
    float score;
    int   rank;
    int   grank;

    bool operator<(const VidScore& b) const { return score > b.score; }
};

class Expriment
{
public:
    Expriment() {}

    void Add(const VidScore& vid, float avg) {
        int id = vid.id;

        if (vids.find(id)==vids.end()) { vids[id] = vid; }
//cg
        vids[id].sum     += vid.yield * kAvgMn/(vid.mn+kMnSmooth);
//cg
        //vids[id].sum     += vid.yield;

        vids[id].avg_sum += avg;
        vids[id].count   += 1;
    }

    void CalcScore()
    {
        for (map<int, VidScore>::iterator it = vids.begin(); it!=vids.end(); ++it)
        {
            VidScore& vid = it->second;

            vid.yield = vid.sum / (vid.count + kSmooth);
            vid.avg   = vid.avg_sum / (vid.count + kSmooth);
            vid.score = (vid.sum - vid.avg_sum) / (vid.count<4?(vid.count+2):vid.count+0.5);
            //vid.yield = vid.sum / (vid.count + kSmooth);
            //vid.avg   = vid.avg_sum / (vid.count + kSmooth);
            //vid.score = (vid.sum - vid.avg_sum) / (vid.count<4?(vid.count+2):vid.count+0.5);
#ifdef TYZCERR
        cerr<< vid.id<< " " << vid.score<<endl;
#endif
        //if(vid.check)
            //vid.score=-100000;
        //add check 15.2
        }
    //cerr<<" Len " << vids.size()<<endl;
//cg
    //13.26
    //10.59 using new ratio

        vector<VidScore> vid_list;
        for (map<int, VidScore>::iterator it = vids.begin(); it!=vids.end(); ++it)
        {
            vid_list.push_back(it->second);
        }
        sort(vid_list.begin(), vid_list.end());

        float check_avg = 0;
        float check_num = 0;
        float check_yield = 0;
        for (int i = 0; i < vid_list.size(); i++) {
            if (vid_list[i].check) {
                check_num ++;
                check_avg += vid_list[i].score;
                check_yield += vid_list[i].yield;
            }
        }
        check_avg /= (check_num + kSmooth);
        check_yield /= (check_num + 0.01);

        for (int i = 0; i < vid_list.size(); i++)
        {
            VidScore& vid = vids[vid_list[i].id];

            vid.rank = i;

            vid.score += -10000*(vid.check);
        //11.712
    
            vid.score += (vid.score - check_avg);
            vid.score += -0.25*(vid.yield - check_yield);
            vid.score += (check_num - 2*vid.rank);
            vid.score += 6*(vid.type);

            vid.score += pow(double(vid.count > 15 ? 15 : vid.count), 0.8);
        //15, count    27.6189 27.388
        //7.5 count/2  27.968  27.680
        // pow(count,0.5)  27.7676  27.5235
        // pow(count,0.7)  27.954  27.667
        // pow(count,0.8)  27.969  27.694
        // pow(count,0.9)  27.862  27.596

        vid.score *=(1+11*pow(year_ratioo[vid.year], 0.8 ));
        //1 28.9 27.7
        //5 29.05 27.78
        //10 29.19 27.80
        //15 29.14 27.82
        //20 29.10 27.69
        //
        //without  27.969  27.694
        //5*
        //with 0.1   28.13 27.86
        //with 0.2   28.18 27.89
        //with 0.3   28.19 27.88
        //with 0.4   28.19 27.87
        //with 0.5   28.19 27.89
        //with 0.6   28.19 27.90
        //with 0.7   28.20 27.90
        //with 0.8   28.15 27.88
        
        }
    }

    map<int, VidScore>* GetVids() { return &vids; } 

private:
    map<int, VidScore> vids;
};

void ParseLine(const char* line, const char* out[], int col)
{
    const char* p = line;

    out[0] = p;
    for (int j = 1; j < col; j++) 
    {
        if (p) p = strstr(p, ",");
        if (p) p++;
        out[j] = p;
    }
}

class EliteClassifier2
{
public:
    void parse_data(vector<string>& data)
    {
        for (int i = 0; i < data.size(); i++)
        {
            const char* col[11];

            ParseLine(data[i].c_str(), col, gStat ? 11:10);

            int   year  = atoi(col[1]);  if (year>=2000) year -= 2000;
            float yield = atof(col[6]);
            int   loc   = atoi(col[2]);
            int   check = atoi(col[9]);

            if (year >= 0 && year < kMaxYear)
            {
                year_loc_avg[year][loc] += yield;
                year_loc_sum[year][loc] += 1;
            }

            if (loc2row.find(loc)!=loc2row.end())
            {
                int row = loc2row[loc];
                year_row_avg[year][row] += yield;
                year_row_sum[year][row] += 1;
            }
        }

        for (int i = 0; i < kMaxYear; i++)
        {
            for (map<int, float>::iterator it = year_loc_avg[i].begin(); it!=year_loc_avg[i].end(); ++it)
            {
                int loc = it->first;
                year_loc_avg[i][loc] /=  year_loc_sum[i][loc] + kYLSmooth;
            }
            
            for (map<int, float>::iterator it = year_row_avg[i].begin(); it != year_row_avg[i].end(); ++it)
            {
                int row = it->first;
                year_row_avg[i][row] /= year_row_sum[i][row];
            }
        }
    }

    void parse_loc(vector<string>& loc)
    {
        for (int i = 0; i < loc.size(); i++)
        {
            const char* col[4];

            ParseLine(loc[i].c_str(), col, 4);

            int loc = atoi(col[0]);
            int row = atoi(col[2]);

            loc2row[loc] = row;
        }
    }


    vector<int> classify(vector<string> data, vector<string> loc)
    {
        init_param();
    
        vector<int> res;
        map<int, VidScore> table;
        vector<VidScore> vids;
        map<int, Expriment> exps;

        parse_loc(loc);
        parse_data(data);

        for (int i = 0; i < data.size(); i++)
        {
            const char* col[11];
            ParseLine(data[i].c_str(), col, gStat?11:10);

            VidScore vid;
            vid.Read(col);

            int eid = atoi(col[0]);
            int loc = atoi(col[2]);
    
            float avg = kAvg;
            
            if (vid.year >= 0 && vid.year <= kMaxYear) {
                avg = year_loc_avg[vid.year][loc];

//cg
                if (loc2row.find(loc)!=loc2row.end()) {
                    int row = loc2row[loc];
                    avg = avg*1.5 - 0.5*year_row_avg[vid.year][row];
                }
            }

            exps[eid].Add(vid, avg);
        }

        for (map<int, Expriment>::iterator it = exps.begin(); it!=exps.end(); ++it)
        {
            it->second.CalcScore();
        }

        for (map<int, Expriment>::iterator it = exps.begin(); it!=exps.end(); ++it)
        {
            map<int, VidScore>* vids = it->second.GetVids();

            for (map<int, VidScore>::iterator it2 = vids->begin(); it2!=vids->end(); ++it2)
            {
                int id = it2->second.id;
                table[id] = it2->second;
            }
        }

        for (map<int, VidScore>::iterator it = table.begin(); it!=table.end(); ++it)
        {
            vids.push_back(it->second);
        }

        sort(vids.begin(), vids.end());

        for (int i = 0; i < vids.size(); i++)
        {
            res.push_back(vids[i].id);
        }

        if (gStat)
        {    
            float score = 0;
            int   elite_count = 0;
            double avg_rank = 0;

            for (int i = 0; i < vids.size(); i++)
            {
                if (vids[i].elite)
                {
                    elite_count++;
                    avg_rank += vids[i].rank;
                    score += (float)elite_count/(i+1);
                }
            }

            score /= elite_count + 0.001;
            avg_rank /= elite_count + 0.001;
            //printf("elite_num\t%d\tvid_num\t%d\tavg_rank\t%.3f\tfinal score\t%.3f\n", elite_count, vids.size(), avg_rank, score);
        }

        if (gDebug)
        {
            FILE* out = fopen("out.csv", "w");
            FILE* outr = fopen("outr.csv", "w");
            FILE* yl = fopen("yl.csv", "w");
            
            if (out && outr && yl) {
                fprintf(outr, "eid,vid,yield,count,avg,score,rank,grank,check,elite\n");
                fprintf(out, "eid,vid,yield,count,avg,score,rank,grank,check,elite\n");

                for (int i = 0; i < vids.size(); i++) {
                    vids[i].grank = i;
                    fprintf(out, "%d,%d,%.3f,%.3f,%.3f,%.3f,%d,%d,%d,%d\n",
                            vids[i].eid, vids[i].id, vids[i].yield, vids[i].count, vids[i].avg, vids[i].score,vids[i].rank, vids[i].grank, vids[i].check, vids[i].elite);

                    if (vids[i].elite || i%10==0) {
                        fprintf(outr, "%d,%d,%.3f,%.3f,%.3f,%.3f,%d,%d,%d,%d\n", 
                                vids[i].eid, vids[i].id, vids[i].yield, vids[i].count, vids[i].avg, vids[i].score,vids[i].rank, vids[i].grank, vids[i].check, vids[i].elite);

                    }
                }
                
                for (int i = 0; i < kMaxYear; i++) {
                    for (map<int, float>::iterator it = year_loc_avg[i].begin(); it!=year_loc_avg[i].end(); ++it) {
                        int j = it->first;
                        fprintf(yl, "%d\t%d\t%.3f\t%.3f\n", i, j, year_loc_avg[i][j], year_loc_sum[i][j]);
                    }
                }

                fclose(yl);
                fclose(out);
                fclose(outr);
            }
        }

        return res;
    }
    
    void init_param(){

    year_ratioo[0]=0.000333333;
    year_ratioo[1]=0.00562249;
    year_ratioo[2]=0.0149597;
    year_ratioo[3]=0.0111926;
    year_ratioo[4]=0.00640752;
    year_ratioo[5]=0.00715537;
    year_ratioo[6]=0.0164141;
    year_ratioo[7]=0.011191;
    year_ratioo[8]=0.00747354;

        year_loc_avg[5][1110]=57706.100; year_loc_sum[5][1110]=1098;
        year_loc_avg[8][1120]=14718.800; year_loc_sum[8][1120]=379;
        year_loc_avg[6][2520]=20521.900; year_loc_sum[6][2520]=378;
        year_loc_avg[8][5220]=43846.800; year_loc_sum[8][5220]=794;
        year_loc_avg[8][1130]=5768.600; year_loc_sum[8][1130]=124;
        year_loc_avg[8][5230]=4672.600; year_loc_sum[8][5230]=96;
        year_loc_avg[1][1597]=3841.000; year_loc_sum[1][1597]=72;
        year_loc_avg[8][2170]=26224.300; year_loc_sum[8][2170]=446;
        year_loc_avg[6][3430]=1549.900; year_loc_sum[6][3430]=32;
        year_loc_avg[4][1540]=16561.700; year_loc_sum[4][1540]=256;
        year_loc_avg[8][5241]=5097.800; year_loc_sum[8][5241]=96;
        year_loc_avg[8][5240]=78632.800; year_loc_sum[8][5240]=1568;
        year_loc_avg[1][7699]=1017.000; year_loc_sum[1][7699]=36;
        year_loc_avg[6][510]=6179.800; year_loc_sum[6][510]=124;
        year_loc_avg[0][4599]=1753.000; year_loc_sum[0][4599]=36;
        year_loc_avg[8][3150]=3229.400; year_loc_sum[8][3150]=62;
        year_loc_avg[5][5240]=19465.300; year_loc_sum[5][5240]=367;
        year_loc_avg[5][5220]=11496.400; year_loc_sum[5][5220]=237;
        year_loc_avg[8][1111]=29940.700; year_loc_sum[8][1111]=861;
        year_loc_avg[8][1110]=68942.800; year_loc_sum[8][1110]=1581;
        year_loc_avg[3][6520]=1589.000; year_loc_sum[3][6520]=33;
        year_loc_avg[8][5210]=10834.000; year_loc_sum[8][5210]=288;
        year_loc_avg[6][2530]=23818.700; year_loc_sum[6][2530]=401;
        year_loc_avg[1][7798]=18154.000; year_loc_sum[1][7798]=288;
        year_loc_avg[1][7796]=14207.500; year_loc_sum[1][7796]=252;
        year_loc_avg[1][7797]=2164.000; year_loc_sum[1][7797]=36;
        year_loc_avg[4][4586]=4035.000; year_loc_sum[4][4586]=71;
        year_loc_avg[5][3380]=22456.300; year_loc_sum[5][3380]=480;
        year_loc_avg[5][11]=2897.700; year_loc_sum[5][11]=64;
        year_loc_avg[4][5791]=25556.900; year_loc_sum[4][5791]=361;
        year_loc_avg[4][5790]=4447.600; year_loc_sum[4][5790]=72;
        year_loc_avg[8][3121]=23977.300; year_loc_sum[8][3121]=320;
        year_loc_avg[8][3120]=46544.600; year_loc_sum[8][3120]=638;
        year_loc_avg[8][3130]=31432.500; year_loc_sum[8][3130]=414;
        year_loc_avg[8][2310]=12130.000; year_loc_sum[8][2310]=224;
        year_loc_avg[3][3410]=2682.100; year_loc_sum[3][3410]=64;
        year_loc_avg[4][5793]=10068.200; year_loc_sum[4][5793]=140;
        year_loc_avg[0][2498]=1664.000; year_loc_sum[0][2498]=32;
        year_loc_avg[1][2598]=16449.300; year_loc_sum[1][2598]=324;
        year_loc_avg[8][1251]=65936.500; year_loc_sum[8][1251]=1499;
        year_loc_avg[8][1250]=81002.600; year_loc_sum[8][1250]=1864;
        year_loc_avg[3][6595]=6431.500; year_loc_sum[3][6595]=144;
        year_loc_avg[5][5330]=8783.100; year_loc_sum[5][5330]=161;
        year_loc_avg[5][5340]=10171.400; year_loc_sum[5][5340]=161;
        year_loc_avg[8][3311]=49685.000; year_loc_sum[8][3311]=820;
        year_loc_avg[8][3310]=72946.300; year_loc_sum[8][3310]=1279;
        year_loc_avg[5][1240]=8292.100; year_loc_sum[5][1240]=125;
        year_loc_avg[8][1260]=11312.800; year_loc_sum[8][1260]=217;
        year_loc_avg[5][3270]=16237.300; year_loc_sum[5][3270]=402;
        year_loc_avg[1][5795]=8988.500; year_loc_sum[1][5795]=179;
        year_loc_avg[3][6610]=17527.100; year_loc_sum[3][6610]=430;
        year_loc_avg[5][6203]=3907.700; year_loc_sum[5][6203]=64;
        year_loc_avg[3][6612]=14945.100; year_loc_sum[3][6612]=252;
        year_loc_avg[8][1270]=13222.200; year_loc_sum[8][1270]=247;
        year_loc_avg[3][6614]=13849.500; year_loc_sum[3][6614]=288;
        year_loc_avg[3][2520]=5633.300; year_loc_sum[3][2520]=120;
        year_loc_avg[3][2593]=5009.900; year_loc_sum[3][2593]=108;
        year_loc_avg[8][3320]=42746.300; year_loc_sum[8][3320]=697;
        year_loc_avg[2][3320]=2162.800; year_loc_sum[2][3320]=32;
        year_loc_avg[5][1270]=3899.500; year_loc_sum[5][1270]=64;
        year_loc_avg[3][2530]=6317.100; year_loc_sum[3][2530]=118;
        year_loc_avg[4][2210]=4112.300; year_loc_sum[4][2210]=64;
        year_loc_avg[8][3270]=18161.600; year_loc_sum[8][3270]=286;
        year_loc_avg[8][3140]=2220.800; year_loc_sum[8][3140]=32;
        year_loc_avg[3][4583]=15845.800; year_loc_sum[3][4583]=432;
        year_loc_avg[3][4586]=4098.800; year_loc_sum[3][4586]=72;
        year_loc_avg[8][5320]=11487.700; year_loc_sum[8][5320]=224;
        year_loc_avg[1][5790]=12032.800; year_loc_sum[1][5790]=216;
        year_loc_avg[8][1230]=14624.600; year_loc_sum[8][1230]=279;
        year_loc_avg[5][3320]=18265.700; year_loc_sum[5][3320]=320;
        year_loc_avg[1][5789]=11579.500; year_loc_sum[1][5789]=216;
        year_loc_avg[8][5330]=12274.200; year_loc_sum[8][5330]=256;
        year_loc_avg[6][4270]=5160.600; year_loc_sum[6][4270]=96;
        year_loc_avg[3][8692]=13265.500; year_loc_sum[3][8692]=324;
        year_loc_avg[5][1251]=5473.200; year_loc_sum[5][1251]=96;
        year_loc_avg[5][3310]=71940.400; year_loc_sum[5][3310]=1170;
        year_loc_avg[4][7798]=29726.700; year_loc_sum[4][7798]=505;
        year_loc_avg[5][1260]=1937.500; year_loc_sum[5][1260]=31;
        year_loc_avg[8][1240]=22565.300; year_loc_sum[8][1240]=411;
        year_loc_avg[4][3699]=11193.300; year_loc_sum[4][3699]=216;
        year_loc_avg[3][510]=2863.800; year_loc_sum[3][510]=96;
        year_loc_avg[5][3230]=4232.800; year_loc_sum[5][3230]=64;
        year_loc_avg[6][2320]=6026.600; year_loc_sum[6][2320]=128;
        year_loc_avg[3][4497]=10186.900; year_loc_sum[3][4497]=180;
        year_loc_avg[3][4499]=2994.400; year_loc_sum[3][4499]=72;
        year_loc_avg[3][8598]=9910.100; year_loc_sum[3][8598]=144;
        year_loc_avg[6][2310]=6413.100; year_loc_sum[6][2310]=160;
        year_loc_avg[5][3210]=88449.600; year_loc_sum[5][3210]=1386;
        year_loc_avg[8][3260]=21239.100; year_loc_sum[8][3260]=448;
        year_loc_avg[8][5250]=4288.800; year_loc_sum[8][5250]=96;
        year_loc_avg[6][4410]=3695.000; year_loc_sum[6][4410]=66;
        year_loc_avg[8][3211]=48402.700; year_loc_sum[8][3211]=791;
        year_loc_avg[8][3210]=177621.200; year_loc_sum[8][3210]=2966;
        year_loc_avg[5][3260]=21381.500; year_loc_sum[5][3260]=318;
        year_loc_avg[8][5260]=9541.700; year_loc_sum[8][5260]=192;
        year_loc_avg[6][2340]=3084.500; year_loc_sum[6][2340]=64;
        year_loc_avg[8][3230]=14179.600; year_loc_sum[8][3230]=318;
        year_loc_avg[3][2240]=2497.300; year_loc_sum[3][2240]=96;
        year_loc_avg[3][6210]=16654.200; year_loc_sum[3][6210]=398;
        year_loc_avg[6][2270]=14278.600; year_loc_sum[6][2270]=258;
        year_loc_avg[5][3410]=7585.700; year_loc_sum[5][3410]=160;
        year_loc_avg[8][3430]=9118.300; year_loc_sum[8][3430]=318;
        year_loc_avg[8][2530]=22040.300; year_loc_sum[8][2530]=442;
        year_loc_avg[6][2260]=13169.000; year_loc_sum[6][2260]=220;
        year_loc_avg[5][3420]=30890.900; year_loc_sum[5][3420]=673;
        year_loc_avg[4][2010]=10682.800; year_loc_sum[4][2010]=194;
        year_loc_avg[3][6230]=4317.400; year_loc_sum[3][6230]=60;
        year_loc_avg[2][1210]=3851.000; year_loc_sum[2][1210]=63;
        year_loc_avg[3][1220]=2774.600; year_loc_sum[3][1220]=64;
        year_loc_avg[2][3240]=2341.600; year_loc_sum[2][3240]=62;
        year_loc_avg[2][6501]=841.100; year_loc_sum[2][6501]=24;
        year_loc_avg[7][2450]=2980.600; year_loc_sum[7][2450]=62;
        year_loc_avg[6][2291]=24226.300; year_loc_sum[6][2291]=727;
        year_loc_avg[6][2290]=37781.300; year_loc_sum[6][2290]=846;
        year_loc_avg[8][3410]=10251.900; year_loc_sum[8][3410]=160;
        year_loc_avg[8][7510]=2542.900; year_loc_sum[8][7510]=64;
        year_loc_avg[2][6799]=21143.100; year_loc_sum[2][6799]=396;
        year_loc_avg[6][4330]=10562.200; year_loc_sum[6][4330]=191;
        year_loc_avg[1][5899]=8072.500; year_loc_sum[1][5899]=180;
        year_loc_avg[0][7796]=2299.600; year_loc_sum[0][7796]=36;
        year_loc_avg[2][2310]=3591.300; year_loc_sum[2][2310]=64;
        year_loc_avg[8][3420]=10904.500; year_loc_sum[8][3420]=311;
        year_loc_avg[8][5410]=12663.300; year_loc_sum[8][5410]=256;
        year_loc_avg[0][4590]=8251.900; year_loc_sum[0][4590]=180;
        year_loc_avg[0][4589]=14809.900; year_loc_sum[0][4589]=252;
        year_loc_avg[8][3370]=19367.800; year_loc_sum[8][3370]=350;
        year_loc_avg[6][140]=2908.500; year_loc_sum[6][140]=61;
        year_loc_avg[5][3330]=104042.400; year_loc_sum[5][3330]=2231;
        year_loc_avg[5][2520]=17596.400; year_loc_sum[5][2520]=275;
        year_loc_avg[5][1280]=9676.800; year_loc_sum[5][1280]=216;
        year_loc_avg[8][3385]=7342.200; year_loc_sum[8][3385]=128;
        year_loc_avg[0][2596]=6328.300; year_loc_sum[0][2596]=104;
        year_loc_avg[3][4725]=4810.000; year_loc_sum[3][4725]=144;
        year_loc_avg[6][2330]=8575.600; year_loc_sum[6][2330]=159;
        year_loc_avg[8][3330]=1773.900; year_loc_sum[8][3330]=32;
        year_loc_avg[8][1280]=11933.500; year_loc_sum[8][1280]=310;
        year_loc_avg[2][8543]=1269.700; year_loc_sum[2][8543]=36;
        year_loc_avg[8][1290]=11548.500; year_loc_sum[8][1290]=217;
        year_loc_avg[7][1550]=6799.500; year_loc_sum[7][1550]=126;
        year_loc_avg[6][2230]=17443.200; year_loc_sum[6][2230]=311;
        year_loc_avg[2][6699]=7415.700; year_loc_sum[2][6699]=144;
        year_loc_avg[2][6698]=5440.400; year_loc_sum[2][6698]=108;
        year_loc_avg[6][4260]=15884.600; year_loc_sum[6][4260]=316;
        year_loc_avg[5][3370]=28774.500; year_loc_sum[5][3370]=709;
        year_loc_avg[6][2210]=22121.800; year_loc_sum[6][2210]=407;
        year_loc_avg[5][3250]=3251.000; year_loc_sum[5][3250]=62;
        year_loc_avg[8][1510]=10293.400; year_loc_sum[8][1510]=221;
        year_loc_avg[1][2270]=1535.500; year_loc_sum[1][2270]=31;
        year_loc_avg[3][2250]=2729.200; year_loc_sum[3][2250]=65;
        year_loc_avg[2][6697]=1747.600; year_loc_sum[2][6697]=36;
        year_loc_avg[3][1240]=2719.400; year_loc_sum[3][1240]=63;
        year_loc_avg[8][1521]=48186.300; year_loc_sum[8][1521]=1117;
        year_loc_avg[8][1520]=26193.000; year_loc_sum[8][1520]=711;
        year_loc_avg[3][4310]=2896.000; year_loc_sum[3][4310]=63;
        year_loc_avg[2][2592]=8937.100; year_loc_sum[2][2592]=144;
        year_loc_avg[2][2594]=19959.800; year_loc_sum[2][2594]=324;
        year_loc_avg[6][6210]=15963.800; year_loc_sum[6][6210]=417;
        year_loc_avg[5][1520]=25417.000; year_loc_sum[5][1520]=408;
        year_loc_avg[6][2170]=9809.000; year_loc_sum[6][2170]=192;
        year_loc_avg[3][4330]=1075.600; year_loc_sum[3][4330]=32;
        year_loc_avg[2][530]=1464.900; year_loc_sum[2][530]=32;
        year_loc_avg[2][2581]=11453.100; year_loc_sum[2][2581]=216;
        year_loc_avg[5][1510]=2084.800; year_loc_sum[5][1510]=33;
        year_loc_avg[2][520]=2852.200; year_loc_sum[2][520]=64;
        year_loc_avg[2][2598]=2175.900; year_loc_sum[2][2598]=36;
        year_loc_avg[5][5410]=3516.600; year_loc_sum[5][5410]=64;
        year_loc_avg[6][6240]=2565.600; year_loc_sum[6][6240]=62;
        year_loc_avg[7][401]=2611.000; year_loc_sum[7][401]=73;
        year_loc_avg[8][3491]=51814.100; year_loc_sum[8][3491]=857;
        year_loc_avg[8][3490]=109329.600; year_loc_sum[8][3490]=1754;
        year_loc_avg[6][6320]=1369.900; year_loc_sum[6][6320]=62;
        year_loc_avg[2][4725]=3935.500; year_loc_sum[2][4725]=72;
        year_loc_avg[5][3480]=58723.000; year_loc_sum[5][3480]=964;
        year_loc_avg[6][2450]=7700.000; year_loc_sum[6][2450]=126;
        year_loc_avg[3][2210]=3274.400; year_loc_sum[3][2210]=93;
        year_loc_avg[8][3460]=15887.000; year_loc_sum[8][3460]=320;
        year_loc_avg[6][2101]=2694.400; year_loc_sum[6][2101]=61;
        year_loc_avg[6][2102]=2684.900; year_loc_sum[6][2102]=61;
        year_loc_avg[3][2220]=3974.200; year_loc_sum[3][2220]=124;
        year_loc_avg[4][5789]=11926.700; year_loc_sum[4][5789]=180;
        year_loc_avg[5][3492]=52814.400; year_loc_sum[5][3492]=961;
        year_loc_avg[5][3490]=1324.100; year_loc_sum[5][3490]=32;
        year_loc_avg[3][2230]=3307.300; year_loc_sum[3][2230]=62;
        year_loc_avg[8][6203]=3454.700; year_loc_sum[8][6203]=64;
        year_loc_avg[0][4799]=1925.900; year_loc_sum[0][4799]=36;
        year_loc_avg[7][1120]=11527.100; year_loc_sum[7][1120]=240;
        year_loc_avg[7][3450]=6115.200; year_loc_sum[7][3450]=93;
        year_loc_avg[0][2699]=1570.600; year_loc_sum[0][2699]=32;
        year_loc_avg[4][3310]=44674.500; year_loc_sum[4][3310]=768;
        year_loc_avg[4][1260]=5729.700; year_loc_sum[4][1260]=130;
        year_loc_avg[0][6799]=2022.800; year_loc_sum[0][6799]=36;
        year_loc_avg[1][5792]=1867.000; year_loc_sum[1][5792]=35;
        year_loc_avg[2][4497]=4215.200; year_loc_sum[2][4497]=72;
        year_loc_avg[4][1250]=29364.000; year_loc_sum[4][1250]=710;
        year_loc_avg[2][8598]=9370.900; year_loc_sum[2][8598]=180;
        year_loc_avg[7][3410]=8355.100; year_loc_sum[7][3410]=155;
        year_loc_avg[4][3320]=7250.300; year_loc_sum[4][3320]=128;
        year_loc_avg[7][3420]=10715.800; year_loc_sum[7][3420]=347;
        year_loc_avg[4][1270]=3648.300; year_loc_sum[4][1270]=64;
        year_loc_avg[4][3210]=62649.700; year_loc_sum[4][3210]=1028;
        year_loc_avg[7][5410]=3535.200; year_loc_sum[7][5410]=96;
        year_loc_avg[2][510]=2548.800; year_loc_sum[2][510]=64;
        year_loc_avg[2][8692]=11317.800; year_loc_sum[2][8692]=288;
        year_loc_avg[5][1540]=11804.400; year_loc_sum[5][1540]=206;
        year_loc_avg[5][2280]=4059.200; year_loc_sum[5][2280]=62;
        year_loc_avg[2][2530]=1680.500; year_loc_sum[2][2530]=32;
        year_loc_avg[2][4583]=12177.100; year_loc_sum[2][4583]=216;
        year_loc_avg[2][2520]=1598.100; year_loc_sum[2][2520]=31;
        year_loc_avg[8][1540]=11775.600; year_loc_sum[8][1540]=254;
        year_loc_avg[2][6610]=14337.500; year_loc_sum[2][6610]=252;
        year_loc_avg[2][6612]=16388.000; year_loc_sum[2][6612]=288;
        year_loc_avg[2][1540]=2394.700; year_loc_sum[2][1540]=63;
        year_loc_avg[8][11]=14179.200; year_loc_sum[8][11]=442;
        year_loc_avg[1][4699]=6867.300; year_loc_sum[1][4699]=143;
        year_loc_avg[0][6699]=1582.100; year_loc_sum[0][6699]=36;
        year_loc_avg[0][6698]=7797.900; year_loc_sum[0][6698]=144;
        year_loc_avg[7][1510]=4538.700; year_loc_sum[7][1510]=93;
        year_loc_avg[2][4410]=2612.600; year_loc_sum[2][4410]=64;
        year_loc_avg[0][2595]=26882.600; year_loc_sum[0][2595]=427;
        year_loc_avg[0][6690]=4225.800; year_loc_sum[0][6690]=108;
        year_loc_avg[0][6695]=6722.100; year_loc_sum[0][6695]=144;
        year_loc_avg[0][2597]=14310.900; year_loc_sum[0][2597]=283;
        year_loc_avg[0][6692]=4577.300; year_loc_sum[0][6692]=108;
        year_loc_avg[7][1520]=34566.400; year_loc_sum[7][1520]=826;
        year_loc_avg[4][1110]=5919.000; year_loc_sum[4][1110]=126;
        year_loc_avg[1][5796]=9904.500; year_loc_sum[1][5796]=180;
        year_loc_avg[4][5230]=4148.800; year_loc_sum[4][5230]=68;
        year_loc_avg[2][2210]=2161.700; year_loc_sum[2][2210]=31;
        year_loc_avg[4][5220]=7246.200; year_loc_sum[4][5220]=140;
        year_loc_avg[4][6610]=2490.800; year_loc_sum[4][6610]=35;
        year_loc_avg[7][3260]=10765.400; year_loc_sum[7][3260]=186;
        year_loc_avg[4][5240]=31310.500; year_loc_sum[4][5240]=623;
        year_loc_avg[1][3210]=8591.400; year_loc_sum[1][3210]=188;
        year_loc_avg[2][6520]=1240.700; year_loc_sum[2][6520]=24;
        year_loc_avg[7][3490]=65889.900; year_loc_sum[7][3490]=1216;
        year_loc_avg[1][1250]=5058.600; year_loc_sum[1][1250]=93;
        year_loc_avg[3][2310]=1044.400; year_loc_sum[3][2310]=31;
        year_loc_avg[1][3310]=6042.100; year_loc_sum[1][3310]=126;
        year_loc_avg[8][4260]=10405.400; year_loc_sum[8][4260]=256;
        year_loc_avg[7][3480]=35301.800; year_loc_sum[7][3480]=716;
        year_loc_avg[7][5220]=13150.300; year_loc_sum[7][5220]=275;
        year_loc_avg[7][5230]=12808.600; year_loc_sum[7][5230]=337;
        year_loc_avg[3][2498]=10164.900; year_loc_sum[3][2498]=252;
        year_loc_avg[4][5599]=1986.300; year_loc_sum[4][5599]=35;
        year_loc_avg[2][2220]=4085.300; year_loc_sum[2][2220]=63;
        year_loc_avg[4][1494]=12581.500; year_loc_sum[4][1494]=396;
        year_loc_avg[4][1492]=4532.600; year_loc_sum[4][1492]=108;
        year_loc_avg[7][5240]=71789.200; year_loc_sum[7][5240]=1245;
        year_loc_avg[5][6540]=2137.100; year_loc_sum[5][6540]=60;
        year_loc_avg[4][1510]=3174.000; year_loc_sum[4][1510]=64;
        year_loc_avg[7][1110]=28218.900; year_loc_sum[7][1110]=729;
        year_loc_avg[7][1111]=49628.100; year_loc_sum[7][1111]=1070;
        year_loc_avg[2][4599]=5067.000; year_loc_sum[2][4599]=108;
        year_loc_avg[7][5210]=10129.200; year_loc_sum[7][5210]=263;
        year_loc_avg[4][1520]=20620.500; year_loc_sum[4][1520]=388;
        year_loc_avg[6][7510]=3224.400; year_loc_sum[6][7510]=62;
        year_loc_avg[7][2130]=16478.300; year_loc_sum[7][2130]=279;
        year_loc_avg[3][520]=3795.200; year_loc_sum[3][520]=96;
        year_loc_avg[4][5699]=7232.300; year_loc_sum[4][5699]=108;
        year_loc_avg[2][4330]=1755.300; year_loc_sum[2][4330]=32;
        year_loc_avg[7][3120]=106316.600; year_loc_sum[7][3120]=1480;
        year_loc_avg[2][4320]=2215.200; year_loc_sum[2][4320]=62;
        year_loc_avg[7][3130]=15117.600; year_loc_sum[7][3130]=217;
        year_loc_avg[3][2594]=9034.300; year_loc_sum[3][2594]=252;
        year_loc_avg[3][2596]=20796.300; year_loc_sum[3][2596]=432;
        year_loc_avg[3][550]=6105.500; year_loc_sum[3][550]=128;
        year_loc_avg[3][6697]=9970.600; year_loc_sum[3][6697]=250;
        year_loc_avg[3][6699]=7697.500; year_loc_sum[3][6699]=144;
        year_loc_avg[2][4310]=4635.200; year_loc_sum[2][4310]=95;
        year_loc_avg[2][2250]=1585.600; year_loc_sum[2][2250]=32;
        year_loc_avg[6][2240]=10366.400; year_loc_sum[6][2240]=155;
        year_loc_avg[7][1250]=188261.500; year_loc_sum[7][1250]=3745;
        year_loc_avg[7][1251]=16600.400; year_loc_sum[7][1251]=352;
        year_loc_avg[7][1260]=11743.300; year_loc_sum[7][1260]=247;
        year_loc_avg[7][3310]=135411.000; year_loc_sum[7][3310]=2219;
        year_loc_avg[7][7401]=3143.800; year_loc_sum[7][7401]=64;
        year_loc_avg[7][7402]=1979.100; year_loc_sum[7][7402]=32;
        year_loc_avg[7][7403]=1644.500; year_loc_sum[7][7403]=29;
        year_loc_avg[7][1270]=18998.400; year_loc_sum[7][1270]=363;
        year_loc_avg[6][2505]=3168.100; year_loc_sum[6][2505]=60;
        year_loc_avg[5][1120]=9248.700; year_loc_sum[5][1120]=219;
        year_loc_avg[7][3320]=26152.100; year_loc_sum[7][3320]=603;
        year_loc_avg[4][3410]=3116.900; year_loc_sum[4][3410]=64;
        year_loc_avg[1][7597]=4415.100; year_loc_sum[1][7597]=72;
        year_loc_avg[7][1220]=16849.400; year_loc_sum[7][1220]=274;
        year_loc_avg[4][6697]=8349.800; year_loc_sum[4][6697]=143;
        year_loc_avg[5][1550]=4413.100; year_loc_sum[5][1550]=72;
        year_loc_avg[4][3430]=7522.400; year_loc_sum[4][3430]=128;
        year_loc_avg[7][1230]=32473.900; year_loc_sum[7][1230]=516;
        year_loc_avg[0][5699]=1874.800; year_loc_sum[0][5699]=36;
        year_loc_avg[3][7797]=7425.400; year_loc_sum[3][7797]=144;
        year_loc_avg[7][5330]=4362.800; year_loc_sum[7][5330]=254;
        year_loc_avg[7][5340]=1662.900; year_loc_sum[7][5340]=64;
        year_loc_avg[7][1240]=66675.400; year_loc_sum[7][1240]=1034;
        year_loc_avg[7][3290]=2358.100; year_loc_sum[7][3290]=66;
        year_loc_avg[7][3240]=8969.900; year_loc_sum[7][3240]=182;
        year_loc_avg[3][6799]=18210.500; year_loc_sum[3][6799]=360;
        year_loc_avg[2][4586]=6760.400; year_loc_sum[2][4586]=108;
        year_loc_avg[6][520]=6136.300; year_loc_sum[6][520]=124;
        year_loc_avg[7][3250]=3377.000; year_loc_sum[7][3250]=62;
        year_loc_avg[2][1270]=4135.200; year_loc_sum[2][1270]=62;
        year_loc_avg[7][1210]=21182.200; year_loc_sum[7][1210]=363;
        year_loc_avg[1][1494]=3302.500; year_loc_sum[1][1494]=108;
        year_loc_avg[7][5250]=14589.700; year_loc_sum[7][5250]=242;
        year_loc_avg[2][2280]=3402.600; year_loc_sum[2][2280]=63;
        year_loc_avg[7][5260]=8245.400; year_loc_sum[7][5260]=192;
        year_loc_avg[8][1220]=13257.100; year_loc_sum[8][1220]=247;
        year_loc_avg[7][3210]=161977.900; year_loc_sum[7][3210]=3222;
        year_loc_avg[1][3020]=2845.700; year_loc_sum[1][3020]=64;
        year_loc_avg[3][3699]=1566.800; year_loc_sum[3][3699]=36;
        year_loc_avg[7][3230]=9549.700; year_loc_sum[7][3230]=186;
        year_loc_avg[6][550]=10068.300; year_loc_sum[6][550]=188;
        year_loc_avg[3][2581]=23041.000; year_loc_sum[3][2581]=432;
        year_loc_avg[8][2320]=5894.900; year_loc_sum[8][2320]=128;
        year_loc_avg[8][6240]=16945.500; year_loc_sum[8][6240]=288;
        year_loc_avg[6][6540]=7250.200; year_loc_sum[6][6540]=124;
        year_loc_avg[8][110]=1569.000; year_loc_sum[8][110]=31;
        year_loc_avg[1][5791]=1436.100; year_loc_sum[1][5791]=36;
        year_loc_avg[1][2594]=22862.200; year_loc_sum[1][2594]=432;
        year_loc_avg[1][2592]=6197.500; year_loc_sum[1][2592]=144;
        year_loc_avg[5][6210]=12203.100; year_loc_sum[5][6210]=389;
        year_loc_avg[1][6695]=6725.500; year_loc_sum[1][6695]=143;
        year_loc_avg[1][6698]=11529.900; year_loc_sum[1][6698]=216;
        year_loc_avg[1][6699]=6356.200; year_loc_sum[1][6699]=143;
        year_loc_avg[8][6210]=65109.900; year_loc_sum[8][6210]=1248;
        year_loc_avg[4][6890]=1865.200; year_loc_sum[4][6890]=36;
        year_loc_avg[8][2120]=24374.600; year_loc_sum[8][2120]=541;
        year_loc_avg[6][1520]=40851.200; year_loc_sum[6][1520]=727;
        year_loc_avg[5][120]=1986.100; year_loc_sum[5][120]=64;
        year_loc_avg[4][2592]=3736.100; year_loc_sum[4][2592]=72;
        year_loc_avg[8][2130]=4138.400; year_loc_sum[8][2130]=64;
        year_loc_avg[3][2508]=1087.800; year_loc_sum[3][2508]=25;
        year_loc_avg[8][6230]=3724.600; year_loc_sum[8][6230]=96;
        year_loc_avg[5][1250]=92710.000; year_loc_sum[5][1250]=1604;
        year_loc_avg[6][1510]=7392.200; year_loc_sum[6][1510]=124;
        year_loc_avg[4][6799]=38997.700; year_loc_sum[4][6799]=613;
        year_loc_avg[3][2592]=1567.900; year_loc_sum[3][2592]=36;
        year_loc_avg[3][3330]=1634.000; year_loc_sum[3][3330]=32;
        year_loc_avg[2][1240]=1538.000; year_loc_sum[2][1240]=31;
        year_loc_avg[4][7597]=5056.400; year_loc_sum[4][7597]=70;
        year_loc_avg[3][2270]=1411.400; year_loc_sum[3][2270]=31;
        year_loc_avg[8][3290]=13778.000; year_loc_sum[8][3290]=350;
        year_loc_avg[8][2110]=11207.300; year_loc_sum[8][2110]=217;
        year_loc_avg[3][5410]=1356.400; year_loc_sum[3][5410]=34;
        year_loc_avg[4][7796]=24852.800; year_loc_sum[4][7796]=396;
        year_loc_avg[3][2598]=6240.800; year_loc_sum[3][2598]=108;
        year_loc_avg[8][10]=9727.200; year_loc_sum[8][10]=279;
        year_loc_avg[8][4110]=9702.800; year_loc_sum[8][4110]=186;
        year_loc_avg[1][6799]=16500.000; year_loc_sum[1][6799]=360;
        year_loc_avg[2][7796]=8851.800; year_loc_sum[2][7796]=216;
        year_loc_avg[8][5340]=8470.100; year_loc_sum[8][5340]=128;
        year_loc_avg[7][3370]=4607.700; year_loc_sum[7][3370]=91;
        year_loc_avg[8][30]=4089.800; year_loc_sum[8][30]=124;
        year_loc_avg[6][3490]=35038.500; year_loc_sum[6][3490]=599;
        year_loc_avg[5][4310]=16387.500; year_loc_sum[5][4310]=444;
        year_loc_avg[6][3420]=16205.100; year_loc_sum[6][3420]=258;
        year_loc_avg[5][2260]=9195.900; year_loc_sum[5][2260]=131;
        year_loc_avg[8][4320]=9708.200; year_loc_sum[8][4320]=160;
        year_loc_avg[4][1550]=5588.600; year_loc_sum[4][1550]=128;
        year_loc_avg[5][2270]=36469.400; year_loc_sum[5][2270]=658;
        year_loc_avg[8][4330]=15813.300; year_loc_sum[8][4330]=288;
        year_loc_avg[8][2280]=3926.100; year_loc_sum[8][2280]=93;
        year_loc_avg[0][7798]=4679.300; year_loc_sum[0][7798]=72;
        year_loc_avg[3][6530]=1226.800; year_loc_sum[3][6530]=32;
        year_loc_avg[6][3410]=4991.200; year_loc_sum[6][3410]=124;
        year_loc_avg[8][2291]=41703.400; year_loc_sum[8][2291]=860;
        year_loc_avg[8][2290]=67773.200; year_loc_sum[8][2290]=1359;
        year_loc_avg[8][160]=982.100; year_loc_sum[8][160]=31;
        year_loc_avg[3][1492]=9457.100; year_loc_sum[3][1492]=252;
        year_loc_avg[3][1494]=21863.300; year_loc_sum[3][1494]=612;
        year_loc_avg[5][2292]=70341.300; year_loc_sum[5][2292]=1403;
        year_loc_avg[8][2240]=11340.900; year_loc_sum[8][2240]=256;
        year_loc_avg[5][2290]=19090.600; year_loc_sum[5][2290]=375;
        year_loc_avg[5][2291]=5800.700; year_loc_sum[5][2291]=106;
        year_loc_avg[3][1510]=1153.300; year_loc_sum[3][1510]=32;
        year_loc_avg[8][2250]=14918.200; year_loc_sum[8][2250]=288;
        year_loc_avg[3][1520]=27880.900; year_loc_sum[3][1520]=566;
        year_loc_avg[2][5899]=7087.400; year_loc_sum[2][5899]=108;
        year_loc_avg[8][4311]=26465.300; year_loc_sum[8][4311]=634;
        year_loc_avg[8][4310]=81140.000; year_loc_sum[8][4310]=1504;
        year_loc_avg[5][4320]=18266.600; year_loc_sum[5][4320]=348;
        year_loc_avg[8][2260]=20706.800; year_loc_sum[8][2260]=448;
        year_loc_avg[0][3698]=1400.600; year_loc_sum[0][3698]=36;
        year_loc_avg[4][4725]=25744.800; year_loc_sum[4][4725]=396;
        year_loc_avg[8][4312]=10819.500; year_loc_sum[8][4312]=256;
        year_loc_avg[5][4330]=31681.800; year_loc_sum[5][4330]=503;
        year_loc_avg[8][2270]=30364.200; year_loc_sum[8][2270]=736;
        year_loc_avg[2][5895]=1353.300; year_loc_sum[2][5895]=36;
        year_loc_avg[8][2210]=45031.900; year_loc_sum[8][2210]=758;
        year_loc_avg[8][3240]=12948.200; year_loc_sum[8][3240]=256;
        year_loc_avg[4][520]=1943.800; year_loc_sum[4][520]=66;
        year_loc_avg[8][2220]=6297.700; year_loc_sum[8][2220]=155;
        year_loc_avg[5][130]=2903.900; year_loc_sum[5][130]=64;
        year_loc_avg[8][2230]=16711.900; year_loc_sum[8][2230]=318;
        year_loc_avg[2][2240]=1864.200; year_loc_sum[2][2240]=32;
        year_loc_avg[8][6330]=21299.000; year_loc_sum[8][6330]=480;
        year_loc_avg[6][1280]=7676.400; year_loc_sum[6][1280]=152;
        year_loc_avg[6][3330]=18104.500; year_loc_sum[6][3330]=438;
        year_loc_avg[5][2230]=4233.200; year_loc_sum[5][2230]=62;
        year_loc_avg[8][130]=6299.700; year_loc_sum[8][130]=186;
        year_loc_avg[4][6699]=13659.400; year_loc_sum[4][6699]=215;
        year_loc_avg[8][3250]=10892.600; year_loc_sum[8][3250]=192;
        year_loc_avg[4][550]=5902.600; year_loc_sum[4][550]=130;
        year_loc_avg[4][2596]=9941.600; year_loc_sum[4][2596]=252;
        year_loc_avg[4][2594]=5452.300; year_loc_sum[4][2594]=108;
        year_loc_avg[4][2593]=1696.900; year_loc_sum[4][2593]=36;
        year_loc_avg[8][140]=9035.700; year_loc_sum[8][140]=247;
        year_loc_avg[8][150]=4786.600; year_loc_sum[8][150]=124;
        year_loc_avg[6][3370]=2738.200; year_loc_sum[6][3370]=62;
        year_loc_avg[5][4270]=25256.800; year_loc_sum[5][4270]=417;
        year_loc_avg[8][2200]=12111.800; year_loc_sum[8][2200]=192;
        year_loc_avg[6][5340]=9565.800; year_loc_sum[6][5340]=158;
        year_loc_avg[6][1240]=2359.800; year_loc_sum[6][1240]=61;
        year_loc_avg[8][6510]=719.900; year_loc_sum[8][6510]=32;
        year_loc_avg[5][4420]=15833.600; year_loc_sum[5][4420]=256;
        year_loc_avg[8][2420]=14079.500; year_loc_sum[8][2420]=224;
        year_loc_avg[6][1220]=6112.600; year_loc_sum[6][1220]=118;
        year_loc_avg[6][3270]=11519.700; year_loc_sum[6][3270]=186;
        year_loc_avg[4][2581]=10006.300; year_loc_sum[4][2581]=180;
        year_loc_avg[2][3430]=2630.400; year_loc_sum[2][3430]=63;
        year_loc_avg[6][120]=6387.900; year_loc_sum[6][120]=120;
        year_loc_avg[2][5790]=24975.400; year_loc_sum[2][5790]=468;
        year_loc_avg[6][1270]=11036.000; year_loc_sum[6][1270]=207;
        year_loc_avg[3][5230]=1496.100; year_loc_sum[3][5230]=32;
        year_loc_avg[6][3310]=71519.900; year_loc_sum[6][3310]=1080;
        year_loc_avg[3][5240]=34231.400; year_loc_sum[3][5240]=735;
        year_loc_avg[8][4440]=11842.300; year_loc_sum[8][4440]=256;
        year_loc_avg[6][1251]=4960.800; year_loc_sum[6][1251]=95;
        year_loc_avg[6][1250]=78162.400; year_loc_sum[6][1250]=1525;
        year_loc_avg[7][550]=6612.300; year_loc_sum[7][550]=228;
        year_loc_avg[6][3230]=8293.400; year_loc_sum[6][3230]=130;
        year_loc_avg[8][2340]=1912.500; year_loc_sum[8][2340]=32;
        year_loc_avg[8][2345]=2299.800; year_loc_sum[8][2345]=64;
        year_loc_avg[5][2330]=1276.500; year_loc_sum[5][2330]=30;
        year_loc_avg[0][5899]=3319.700; year_loc_sum[0][5899]=72;
        year_loc_avg[5][2310]=17447.400; year_loc_sum[5][2310]=428;
        year_loc_avg[6][3210]=97128.300; year_loc_sum[6][3210]=1792;
        year_loc_avg[8][4410]=1473.000; year_loc_sum[8][4410]=32;
        year_loc_avg[6][3260]=6176.900; year_loc_sum[6][3260]=97;
        year_loc_avg[4][6530]=2413.100; year_loc_sum[4][6530]=68;
        year_loc_avg[3][5220]=6731.200; year_loc_sum[3][5220]=135;
        year_loc_avg[5][4410]=9948.100; year_loc_sum[5][4410]=160;
        year_loc_avg[6][3250]=10146.900; year_loc_sum[6][3250]=190;
        year_loc_avg[5][2340]=16338.300; year_loc_sum[5][2340]=286;
        year_loc_avg[0][5599]=1391.200; year_loc_sum[0][5599]=36;
        year_loc_avg[6][3240]=5553.700; year_loc_sum[6][3240]=130;
        year_loc_avg[8][2330]=18284.800; year_loc_sum[8][2330]=317;
        year_loc_avg[0][1495]=1172.000; year_loc_sum[0][1495]=32;
        year_loc_avg[7][2340]=20397.100; year_loc_sum[7][2340]=370;
        year_loc_avg[2][1597]=4867.000; year_loc_sum[2][1597]=108;
        year_loc_avg[6][5210]=4267.900; year_loc_sum[6][5210]=64;
        year_loc_avg[5][1210]=13521.200; year_loc_sum[5][1210]=218;
        year_loc_avg[6][1111]=25779.700; year_loc_sum[6][1111]=546;
        year_loc_avg[6][1110]=16770.700; year_loc_sum[6][1110]=504;
        year_loc_avg[3][1230]=4064.100; year_loc_sum[3][1230]=124;
        year_loc_avg[8][510]=2981.400; year_loc_sum[8][510]=64;
        year_loc_avg[5][2505]=3541.300; year_loc_sum[5][2505]=62;
        year_loc_avg[3][1250]=25779.900; year_loc_sum[3][1250]=629;
        year_loc_avg[3][1251]=1598.100; year_loc_sum[3][1251]=32;
        year_loc_avg[6][5240]=25548.700; year_loc_sum[6][5240]=518;
        year_loc_avg[2][2260]=1883.200; year_loc_sum[2][2260]=32;
        year_loc_avg[3][7402]=1764.300; year_loc_sum[3][7402]=33;
        year_loc_avg[3][1260]=6555.400; year_loc_sum[3][1260]=125;
        year_loc_avg[4][1597]=7448.400; year_loc_sum[4][1597]=144;
        year_loc_avg[3][3310]=11018.300; year_loc_sum[3][3310]=221;
        year_loc_avg[6][5230]=1343.600; year_loc_sum[6][5230]=31;
        year_loc_avg[5][2530]=18176.100; year_loc_sum[5][2530]=293;
        year_loc_avg[2][1550]=1694.500; year_loc_sum[2][1550]=63;
        year_loc_avg[3][3320]=1655.700; year_loc_sum[3][3320]=31;
        year_loc_avg[6][5220]=7835.400; year_loc_sum[6][5220]=135;
        year_loc_avg[8][2520]=7242.100; year_loc_sum[8][2520]=128;
        year_loc_avg[6][1120]=7816.100; year_loc_sum[6][1120]=269;
        year_loc_avg[3][5250]=1718.100; year_loc_sum[3][5250]=32;
        year_loc_avg[5][2450]=2765.600; year_loc_sum[5][2450]=94;
        year_loc_avg[3][3210]=25472.900; year_loc_sum[3][3210]=499;
        year_loc_avg[2][7797]=6161.100; year_loc_sum[2][7797]=144;
        year_loc_avg[2][7798]=9516.200; year_loc_sum[2][7798]=216;
        year_loc_avg[2][2010]=2203.000; year_loc_sum[2][2010]=32;
        year_loc_avg[3][2410]=2700.500; year_loc_sum[3][2410]=63;
        year_loc_avg[3][3240]=1443.300; year_loc_sum[3][3240]=32;
        year_loc_avg[8][2441]=10165.100; year_loc_sum[8][2441]=256;
        year_loc_avg[8][2440]=15043.800; year_loc_sum[8][2440]=416;
        year_loc_avg[8][2450]=9332.900; year_loc_sum[8][2450]=159;
        year_loc_avg[6][5410]=1282.700; year_loc_sum[6][5410]=32;
        year_loc_avg[8][2460]=1453.900; year_loc_sum[8][2460]=64;
        year_loc_avg[5][7510]=1703.900; year_loc_sum[5][7510]=60;
        year_loc_avg[0][5795]=8358.700; year_loc_sum[0][5795]=180;
        year_loc_avg[0][5794]=5883.000; year_loc_sum[0][5794]=144;
        year_loc_avg[7][6510]=2693.100; year_loc_sum[7][6510]=62;
        year_loc_avg[4][2240]=4050.000; year_loc_sum[4][2240]=64;
        year_loc_avg[7][2420]=6350.500; year_loc_sum[7][2420]=122;
        year_loc_avg[4][2270]=18594.400; year_loc_sum[4][2270]=318;
        year_loc_avg[2][7597]=3449.000; year_loc_sum[2][7597]=72;
        year_loc_avg[4][4310]=3176.300; year_loc_sum[4][4310]=64;
        year_loc_avg[4][2260]=3513.200; year_loc_sum[4][2260]=62;
        year_loc_avg[7][6520]=15813.400; year_loc_sum[7][6520]=336;
        year_loc_avg[8][1550]=14861.600; year_loc_sum[8][1550]=313;
        year_loc_avg[7][4420]=577.200; year_loc_sum[7][4420]=27;
        year_loc_avg[4][2280]=4176.300; year_loc_sum[4][2280]=64;
        year_loc_avg[4][4320]=3046.800; year_loc_sum[4][4320]=64;
        year_loc_avg[2][9611]=1344.900; year_loc_sum[2][9611]=36;
        year_loc_avg[0][5790]=9890.700; year_loc_sum[0][5790]=180;
        year_loc_avg[0][5789]=21122.300; year_loc_sum[0][5789]=324;
        year_loc_avg[2][550]=2607.900; year_loc_sum[2][550]=64;
        year_loc_avg[8][3315]=8295.000; year_loc_sum[8][3315]=128;
        year_loc_avg[6][4310]=12866.800; year_loc_sum[6][4310]=254;
        year_loc_avg[8][550]=22076.100; year_loc_sum[8][550]=469;
        year_loc_avg[2][1520]=7183.200; year_loc_sum[2][1520]=189;
        year_loc_avg[3][5899]=4847.900; year_loc_sum[3][5899]=108;
        year_loc_avg[2][5250]=1920.000; year_loc_sum[2][5250]=32;
        year_loc_avg[7][1280]=6947.600; year_loc_sum[7][1280]=189;
        year_loc_avg[7][2270]=33820.100; year_loc_sum[7][2270]=826;
        year_loc_avg[7][4410]=18582.300; year_loc_sum[7][4410]=440;
        year_loc_avg[7][2310]=10020.300; year_loc_sum[7][2310]=190;
        year_loc_avg[4][2220]=6028.500; year_loc_sum[4][2220]=128;
        year_loc_avg[7][3330]=10805.500; year_loc_sum[7][3330]=188;
        year_loc_avg[4][3240]=7223.100; year_loc_sum[4][3240]=128;
        year_loc_avg[2][1492]=1810.400; year_loc_sum[2][1492]=36;
        year_loc_avg[2][1494]=3260.500; year_loc_sum[2][1494]=108;
        year_loc_avg[6][1230]=3258.800; year_loc_sum[6][1230]=62;
        year_loc_avg[4][2230]=3380.900; year_loc_sum[4][2230]=64;
        year_loc_avg[8][520]=7245.500; year_loc_sum[8][520]=128;
        year_loc_avg[7][3270]=22102.900; year_loc_sum[7][3270]=438;
        year_loc_avg[6][2250]=3586.900; year_loc_sum[6][2250]=62;
        year_loc_avg[4][6210]=19442.900; year_loc_sum[4][6210]=413;
        year_loc_avg[4][6230]=8834.600; year_loc_sum[4][6230]=138;
        year_loc_avg[3][2010]=1789.500; year_loc_sum[3][2010]=33;
        year_loc_avg[0][7695]=1534.600; year_loc_sum[0][7695]=36;
        year_loc_avg[2][3350]=1909.200; year_loc_sum[2][3350]=32;
        year_loc_avg[4][2310]=7852.900; year_loc_sum[4][2310]=128;
        year_loc_avg[0][7699]=1876.700; year_loc_sum[0][7699]=36;
        year_loc_avg[7][2320]=9109.100; year_loc_sum[7][2320]=156;
        year_loc_avg[8][1210]=17347.400; year_loc_sum[8][1210]=340;
        year_loc_avg[2][3330]=3547.400; year_loc_sum[2][3330]=64;
        year_loc_avg[7][2520]=9288.600; year_loc_sum[7][2520]=190;
        year_loc_avg[4][3330]=3713.800; year_loc_sum[4][3330]=64;
        year_loc_avg[2][5789]=12124.400; year_loc_sum[2][5789]=216;
        year_loc_avg[0][7799]=1180.100; year_loc_sum[0][7799]=36;
        year_loc_avg[2][6595]=9863.900; year_loc_sum[2][6595]=180;
        year_loc_avg[0][7797]=1821.500; year_loc_sum[0][7797]=36;
        year_loc_avg[6][3320]=16452.700; year_loc_sum[6][3320]=290;
        year_loc_avg[7][6540]=5580.500; year_loc_sum[7][6540]=296;
        year_loc_avg[7][2440]=22624.200; year_loc_sum[7][2440]=374;
        year_loc_avg[7][2330]=7294.000; year_loc_sum[7][2330]=124;
        year_loc_avg[2][6614]=5052.500; year_loc_sum[2][6614]=108;
        year_loc_avg[3][5699]=6642.600; year_loc_sum[3][5699]=142;
        year_loc_avg[7][110]=9385.800; year_loc_sum[7][110]=186;
        year_loc_avg[2][5230]=397.200; year_loc_sum[2][5230]=32;
        year_loc_avg[4][6595]=5088.800; year_loc_sum[4][6595]=71;
        year_loc_avg[5][6520]=4374.200; year_loc_sum[5][6520]=124;
        year_loc_avg[4][2520]=3735.300; year_loc_sum[4][2520]=64;
        year_loc_avg[4][6614]=8747.200; year_loc_sum[4][6614]=179;
        year_loc_avg[5][1230]=3342.900; year_loc_sum[5][1230]=62;
        year_loc_avg[4][6612]=19254.800; year_loc_sum[4][6612]=287;
        year_loc_avg[7][120]=5597.000; year_loc_sum[7][120]=120;
        year_loc_avg[7][2170]=24282.500; year_loc_sum[7][2170]=348;
        year_loc_avg[7][2530]=11454.200; year_loc_sum[7][2530]=248;
        year_loc_avg[7][6210]=48663.600; year_loc_sum[7][6210]=1083;
        year_loc_avg[6][1260]=7368.700; year_loc_sum[6][1260]=124;
        year_loc_avg[4][4583]=27043.700; year_loc_sum[4][4583]=504;
        year_loc_avg[5][2420]=2972.700; year_loc_sum[5][2420]=64;
        year_loc_avg[7][2120]=3452.000; year_loc_sum[7][2120]=62;
        year_loc_avg[4][2530]=2176.900; year_loc_sum[4][2530]=62;
        year_loc_avg[4][510]=4144.300; year_loc_sum[4][510]=66;
        year_loc_avg[2][3210]=22111.000; year_loc_sum[2][3210]=381;
        year_loc_avg[3][7796]=22841.200; year_loc_sum[3][7796]=468;
        year_loc_avg[3][7798]=9174.600; year_loc_sum[3][7798]=180;
        year_loc_avg[2][2596]=6709.900; year_loc_sum[2][2596]=144;
        year_loc_avg[2][1220]=1496.200; year_loc_sum[2][1220]=31;
        year_loc_avg[4][8691]=11012.300; year_loc_sum[4][8691]=179;
        year_loc_avg[6][2280]=5295.900; year_loc_sum[6][2280]=126;
        year_loc_avg[3][1540]=6850.800; year_loc_sum[3][1540]=160;
        year_loc_avg[0][2599]=1962.200; year_loc_sum[0][2599]=32;
        year_loc_avg[6][7402]=3913.100; year_loc_sum[6][7402]=62;
        year_loc_avg[3][1550]=6629.500; year_loc_sum[3][1550]=160;
        year_loc_avg[3][5795]=3204.600; year_loc_sum[3][5795]=72;
        year_loc_avg[2][1260]=2342.100; year_loc_sum[2][1260]=63;
        year_loc_avg[2][3310]=18503.500; year_loc_sum[2][3310]=318;
        year_loc_avg[4][8598]=4034.100; year_loc_sum[4][8598]=70;
        year_loc_avg[2][1250]=12556.800; year_loc_sum[2][1250]=221;
        year_loc_avg[4][4499]=2161.500; year_loc_sum[4][4499]=35;
        year_loc_avg[4][4497]=31201.800; year_loc_sum[4][4497]=431;
        year_loc_avg[7][6203]=6711.500; year_loc_sum[7][6203]=120;
        year_loc_avg[7][6280]=757.000; year_loc_sum[7][6280]=64;
        year_loc_avg[7][4110]=20965.300; year_loc_sum[7][4110]=414;
        year_loc_avg[0][2496]=1582.300; year_loc_sum[0][2496]=32;
        year_loc_avg[7][10]=35639.000; year_loc_sum[7][10]=687;
        year_loc_avg[6][4320]=3947.300; year_loc_sum[6][4320]=65;
        year_loc_avg[3][1597]=8209.200; year_loc_sum[3][1597]=252;
        year_loc_avg[4][5899]=17325.900; year_loc_sum[4][5899]=253;
        year_loc_avg[7][2280]=2698.400; year_loc_sum[7][2280]=62;
        year_loc_avg[7][4330]=10320.000; year_loc_sum[7][4330]=191;
        year_loc_avg[4][8543]=2607.600; year_loc_sum[4][8543]=35;
        year_loc_avg[7][2290]=65406.900; year_loc_sum[7][2290]=1584;
        year_loc_avg[7][2291]=44763.900; year_loc_sum[7][2291]=988;
        year_loc_avg[7][510]=2798.900; year_loc_sum[7][510]=98;
        year_loc_avg[1][4498]=7254.100; year_loc_sum[1][4498]=252;
        year_loc_avg[7][2240]=11009.700; year_loc_sum[7][2240]=216;
        year_loc_avg[3][1110]=2964.300; year_loc_sum[3][1110]=63;
        year_loc_avg[0][5895]=6228.800; year_loc_sum[0][5895]=144;
        year_loc_avg[7][2250]=2721.800; year_loc_sum[7][2250]=64;
        year_loc_avg[7][2260]=34411.500; year_loc_sum[7][2260]=724;
        year_loc_avg[7][4310]=29526.400; year_loc_sum[7][4310]=1082;
        year_loc_avg[7][4311]=3515.500; year_loc_sum[7][4311]=246;
        year_loc_avg[7][4320]=2530.700; year_loc_sum[7][4320]=62;
        year_loc_avg[1][498]=1259.200; year_loc_sum[1][498]=36;
        year_loc_avg[2][5240]=2843.900; year_loc_sum[2][5240]=56;
        year_loc_avg[1][4599]=2387.300; year_loc_sum[1][4599]=72;
        year_loc_avg[7][2210]=34735.800; year_loc_sum[7][2210]=561;
        year_loc_avg[7][2220]=1188.300; year_loc_sum[7][2220]=30;
        year_loc_avg[3][3230]=1359.300; year_loc_sum[3][3230]=31;
        year_loc_avg[7][2230]=16271.000; year_loc_sum[7][2230]=340;
        year_loc_avg[6][1550]=2980.800; year_loc_sum[6][1550]=62;
        year_loc_avg[1][4583]=10856.100; year_loc_sum[1][4583]=360;
        year_loc_avg[3][5789]=7636.600; year_loc_sum[3][5789]=144;
        year_loc_avg[3][5790]=10363.600; year_loc_sum[3][5790]=214;
        year_loc_avg[3][5791]=20972.500; year_loc_sum[3][5791]=396;
        year_loc_avg[2][6210]=2860.700; year_loc_sum[2][6210]=56;
        year_loc_avg[5][2210]=14203.200; year_loc_sum[5][2210]=270;
        year_loc_avg[3][5260]=1486.000; year_loc_sum[3][5260]=28;
        year_loc_avg[7][140]=8680.000; year_loc_sum[7][140]=182;
        year_loc_avg[2][1110]=2211.100; year_loc_sum[2][1110]=63;
        year_loc_avg[1][6595]=8410.400; year_loc_sum[1][6595]=144;
        year_loc_avg[7][150]=1569.000; year_loc_sum[7][150]=31;
        year_loc_avg[4][4410]=7055.500; year_loc_sum[4][4410]=128;
        year_loc_avg[4][8498]=2350.700; year_loc_sum[4][8498]=35;
    }
};

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<set>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>

//#define LOCAL_TEST

using namespace std;

class Line {
    public:
        int expID;
        int year;
        int loccd;
        int rep;
        int type;     // NULL
        int varID;
        float yield;  // NULL
        int mn;       // NULL
        float rm;     // NULL
        int isCheck;
        int isElite;

        Line(const char *str) {
            if (str == NULL) {
                expID = year = loccd = rep -1;
                return;
            }
            const char *p = str;
            sscanf(p, "%d,%d,%d,%d", &expID, &year, &loccd, &rep);
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;

            if (strncmp(p, "NULL", 4) == 0) {
                type = -1;
            } if (strncmp(p, "conv", 4) == 0) {
                type = 0;
            } else if (strncmp(p, "RR1", 3) == 0) {
                type = 1;
            } else if (strncmp(p, "RR2Y", 4) == 0) {
                type = 2;
            }
            p = strchr(p, ',')+1;

            sscanf(p, "%d", &varID);
            p = strchr(p, ',')+1;

            if (*p == 'N') {
                yield = -1;
            } else {
                sscanf(p, "%f", &yield);
            }
            p = strchr(p, ',')+1;

            if (*p == 'N') {
                mn = -1;
            } else {
                sscanf(p, "%d", &mn);
                if (mn < 50 || mn > 200)
                    mn = -1;
            }
            p = strchr(p, ',')+1;

            if (*p == 'N') {
                rm = -1;
            } else {
                sscanf(p, "%f", &rm);
            }
            p = strchr(p, ',')+1;

            isCheck = *p - '0';

            if (*(p+1) == ',') {
                p = strchr(p, ',')+1;
                isElite = *p - '0';
            } else
                isElite = 0;
        }
};

class EliteClassifier4 {
    public: 

        float m_mnAve;
        float m_yieldPerMN;
        float m_emptyLocScale;
        float m_trialScale;
        vector<int> m_yearlist;
        map<int, int> m_years;
        map<int, int> m_expIDs;
        map<int, int> m_types;
        map<int, int> m_bands;
        map<int, int> m_checks;
        map<int, int> m_elites;
        map<int, float> m_varID2MNs;
        map<int, int> m_varID2MNValidNum;
        map<int, float> m_varID2Weights;
        map<int, float> m_varID2MNWeights;
        set<int> m_LOCCDs;
        map<int, float> m_yearScale;
        map<int, float> m_typeScale;
        map<int, float> m_bandScale;

        void randInitPara()
        {
            for (int i=2000; i<=2008; i++)
                m_yearScale[i] = 1.0 + (0.2 * (random() / (RAND_MAX + 1.0)));
            for (int i=0; i<=2; i++)
                m_typeScale[i] = 1.0 + (0.2 * (random() / (RAND_MAX + 1.0)));
            for (int i=0; i<=9; i++)
                m_bandScale[i] = 1.0 + (0.2 * (random() / (RAND_MAX + 1.0)));
        }

        void initPara()
        {
            m_mnAve = 135;
            m_yieldPerMN = 0.2;
            m_emptyLocScale = 0.95;
            m_trialScale = 3.0;

            setParas(0);
        }

        void setParas(int idx)
        {
            float yearscales[5][9] = {
                {0.912,1.165,1.199,1.169,1.117,1.089,1.093,1.113,1.099,},
                {0.852,1.152,1.187,1.176,1.114,1.084,1.081,1.114,1.094,},
                {0.975,1.102,1.146,1.117,1.073,1.034,1.046,1.068,1.047,},
                {0.903,1.087,1.126,1.111,1.048,1.027,1.021,1.040,1.024,},
                {0.899,1.143,1.182,1.167,1.095,1.071,1.073,1.100,1.081,},
            };
            float typescales[5][3] = {
                {1.006,1.041,0.892,},
                {1.074,1.099,0.833,},
                {1.097,1.121,0.914,},
                {1.156,1.182,0.889,},
                {1.096,1.127,0.827,},
            };
            float bandscales[5][10] = {
                {0.835,1.145,1.149,1.149,1.142,1.091,1.028,1.089,0.835,0.873,},
                {0.842,1.116,1.122,1.115,1.109,1.041,0.981,1.049,0.933,0.837,},
                {0.853,1.114,1.118,1.114,1.108,1.052,0.988,1.047,0.805,0.890,},
                {0.952,1.135,1.123,1.118,1.124,1.051,0.995,1.064,0.905,0.948,},
                {0.987,1.155,1.154,1.148,1.155,1.077,1.024,1.077,0.846,0.916,},
            };

            for (int i=0; i<=8; i++) {
                m_yearScale[2000+i] = yearscales[idx][i];
            }
            for (int i=0; i<=2; i++) {
                m_typeScale[i] = typescales[idx][i];
            }
            for (int i=0; i<=9; i++) {
                m_bandScale[i] = bandscales[idx][i];
            }

            // fix para
            for (unsigned int i=0; i<m_yearlist.size(); i++) {
                int year = m_yearlist[i];
                if (m_yearScale.find(year) == m_yearScale.end()) {
                    if (year < 2000)
                        m_yearScale[year] = m_yearScale[2000];
                    else if (year > 2008)
                        m_yearScale[year] = m_yearScale[2008];
                }
            }
            m_typeScale[-1] = m_typeScale[1];
        }

        vector<pair<float, int> > normScore(vector<pair<float, int> > &yields, int expID)
        {
            int n = yields.size();
            double sum = 0.0;
            float nsum = 0;
            for (int i=0; i<n; i++) {
                float yield = yields[i].first;
                int varID = yields[i].second;
                if (yield < 0)
                    continue;

                // signal: weight of varity when compute average yields per trial
                if (m_varID2Weights.find(varID) != m_varID2Weights.end()) {
                    float weight = m_varID2Weights[varID];
                    sum += yield*weight;
                    nsum += weight;
                } else {
                    sum += yield;
                    nsum++;
                }
            }

            vector<pair<float, int> > scores;
            if (nsum == 0) {
                for (int i=0; i<n; i++) {
                    scores.push_back(make_pair(100.0, yields[i].second));
                }
                return scores;
            }

            double ave = sum/nsum;
            for (int i=0; i<n; i++) {
                float score = yields[i].first/ave*100.0;
                if (score < 0)
                    score = 100.0;
                int id = yields[i].second;
                scores.push_back(make_pair(score, id));
            }
            return scores;
        }

        vector<Line> trans2Lines(vector<string> &data)
        {
            vector<Line> lines;
            for (unsigned int i=0; i<data.size(); i++)
                lines.push_back(Line(data[i].c_str()));
            return lines;
        }

        map<int, float> getMNs(vector<Line> &data)
        {
            map<int, float> mnSum;
            map<int, int> mnNum;
            map<int, float> mns;


            for (unsigned int k=0; k<data.size(); k++) {
                mns[data[k].varID] = m_mnAve;
            }
            for (unsigned int k=0; k<data.size(); k++) {
                if (data[k].mn != -1) {
                    int id = data[k].varID;
                    mnSum[id] += data[k].mn;
                    mnNum[id]++;
                }
            }
            for (map<int, float>::iterator it=mnSum.begin(); it!=mnSum.end(); it++) {
                mns[it->first] = it->second/mnNum[it->first];
            }
            return mns;
        }

        map<int, int> getMNValidNum(vector<Line> &data)
        {
            map<int, int> validNum;

            for (unsigned int k=0; k<data.size(); k++) {
                validNum[data[k].varID] = 0;
            }
            for (unsigned int k=0; k<data.size(); k++) {
                if (data[k].mn != -1) {
                    int id = data[k].varID;
                    validNum[id]++;
                }
            }
            return validNum;
        }

        void initVarFeature(vector<Line> &data)
        {
            set<int> yearSet;
            for (unsigned int i=0; i<=data.size(); i++) {
                Line &ln = data[i];
                m_expIDs[ln.varID] = ln.expID;
                m_years[ln.varID] = ln.year;
                m_types[ln.varID] = ln.type;
                m_bands[ln.varID] = ln.loccd/1000;
                m_checks[ln.varID] = ln.isCheck;
                yearSet.insert(ln.year);
            }
            for (set<int>::iterator it=yearSet.begin(); it!=yearSet.end(); it++)
                m_yearlist.push_back(*it);
        }

        set<int> getLoccdSet(vector<string> &locations)
        {
            set<int> loccds;
            for (unsigned int i=0; i<locations.size(); i++) {
                int id;
                const char *p = locations[i].c_str();
                sscanf(p, "%d", &id);
                loccds.insert(id);;
            }
            return loccds;
        }

        vector<pair<float, int> > getRawScore(vector<Line> &data)
        {
            int expID, year, loccd, rep;
            expID = year = loccd = rep = -1;

            vector<pair<float, int> > yields;
            map<int, vector<float> > id2scores;


            for (unsigned int k=0; k<=data.size(); k++) {
                Line &ln = data[k];
                if (k == data.size() || (k > 0 && (ln.expID != expID || ln.year != year || ln.loccd != loccd || ln.rep != rep))) {
                    vector<pair<float, int> > scores = normScore(yields, expID);

                    for (unsigned int i=0; i<scores.size(); i++) {
                        float score = scores[i].first;
                        int id = scores[i].second;

                        // signal: whether LOCCD in locations.csv
                        if (m_LOCCDs.find(loccd) == m_LOCCDs.end())
                            score *= m_emptyLocScale;

                        if (id2scores.find(id) == id2scores.end()) {
                            vector<float> values;
                            values.push_back(score);
                            id2scores[id] = values;
                        } else {
                            id2scores[id].push_back(score);
                        }
                    }
                    yields.clear();
                    if (k == data.size())
                        break;
                }
                // signal MN
                if (ln.mn == -1) {
                    float mnfix = 0.0;
                    mnfix = (m_mnAve - m_varID2MNs[ln.varID])*m_yieldPerMN;
                    yields.push_back(make_pair(ln.yield + mnfix, ln.varID));
                } else {
                    float mnfix = 0.0;
                    mnfix = (m_mnAve - ln.mn)*m_yieldPerMN;
                    yields.push_back(make_pair(ln.yield + mnfix, ln.varID));
                }

                expID = ln.expID;
                year = ln.year;
                loccd = ln.loccd;
                rep = ln.rep;
            }

            vector<pair<float, int> > scores;
            for (map<int, vector<float> >::iterator it=id2scores.begin(); it!=id2scores.end(); it++) {
                int id = it->first;
                vector<float> &s = it->second;
                float score = 0.0;
                if (m_checks[id] != 1) {
                    float sum = 0.0;
                    for (unsigned int i=0; i<s.size(); i++)
                        sum += s[i];
                    float ave = sum/s.size();
                    float var = 0.0;
                    for (unsigned int i=0; i<s.size(); i++)
                        var += (s[i]-ave)*(s[i]-ave);
                    var = sqrt(var/s.size());
                    score = ave;
                    // signal: trial per experiment
                    score += sqrt(s.size())*m_trialScale;
                    // signal: number of valid MN
                    score += sqrt(m_varID2MNValidNum[id])*1.5;
                }
                scores.push_back(make_pair(score, id));
            }

            return scores;
        }

        map<int, float> getVar2Weight(vector<Line> &data)
        {
            int expID, year, loccd, rep;
            expID = year = loccd = rep = -1;

            map<int, set<int> > expID2VarIDs;
            map<int, int> expID2TrialNum;

            vector<pair<float, int> > yields;
            map<int, vector<float> > id2scores;

            for (unsigned int k=0; k<=data.size(); k++) {
                Line &ln = data[k];
                if (k == data.size() || (k > 0 && (ln.expID != expID || ln.year != year || ln.loccd != loccd || ln.rep != rep))) {
                    vector<pair<float, int> > scores = normScore(yields, expID);

                    for (unsigned int i=0; i<scores.size(); i++) {
                        float score = scores[i].first;
                        int id = scores[i].second;
                        id2scores[id].push_back(score);
                    }
                    yields.clear();
                    expID2TrialNum[expID]++;
                    if (k == data.size())
                        break;
                }
                yields.push_back(make_pair(ln.yield, ln.varID));
                expID = ln.expID;
                year = ln.year;
                loccd = ln.loccd;
                rep = ln.rep;

                expID2VarIDs[expID].insert(ln.varID);
            }

            map<int, float> varID2Vars;
            for (map<int, vector<float> >::iterator it=id2scores.begin(); it!=id2scores.end(); it++) {
                int id = it->first;
                vector<float> &s = it->second;
                float sum = 0.0;
                for (unsigned int i=0; i<s.size(); i++)
                    sum += s[i];
                float ave = sum/s.size();
                float var = 0.0;
                for (unsigned int i=0; i<s.size(); i++)
                    var += (s[i]-ave)*(s[i]-ave);
                var = sqrt(var/s.size());
                varID2Vars[id] = ave;
            }

            map<int, float> varID2Weights;
            for (map<int, set<int> >::iterator it=expID2VarIDs.begin(); it!=expID2VarIDs.end(); it++) {
                set<int> &varIDs = it->second;
                vector<pair<float, int> > vars;
                for (set<int>::iterator itt=varIDs.begin(); itt!=varIDs.end(); itt++) {
                    int varID = *itt;
                    vars.push_back(make_pair(varID2Vars[varID], varID));
                }
                sort(vars.begin(), vars.end());
                int n = vars.size();
                for (int i=0; i<n; i++)
                    varID2Weights[vars[i].second] = powf(vars[i].first, 6.0);
            }

            return varID2Weights;
        }

        map<int, float> getVarID2MNWeight(vector<Line> &data)
        {
            int expID, year, loccd, rep;
            expID = year = loccd = rep = -1;

            vector<pair<int, int> > mns;
            map<int, vector<float> > id2mns;

            for (unsigned int k=0; k<=data.size(); k++) {
                Line &ln = data[k];
                if (k == data.size() || (k > 0 && (ln.expID != expID || ln.year != year || ln.loccd != loccd || ln.rep != rep))) {
                    if (mns.size() > 0) {
                        float mnSum = 0.0;
                        int mnNum = 0;
                        for (unsigned int i=0; i<mns.size(); i++) {
                            int varID = mns[i].second;
                            if (m_checks[varID]) {
                                mnSum += mns[i].first;
                                mnNum++;
                            }
                        }
                        if (mnNum != 0) {
                            float mnAve = mnSum/mnNum;
                            for (unsigned int i=0; i<mns.size(); i++) {
                                int varID = mns[i].second;
                                int mn = mns[i].first;
                                if (mn != -1) {
                                    id2mns[varID].push_back(mnAve - mn);
                                }
                            }
                        }
                        mns.clear();
                    }
                    if (k == data.size())
                        break;
                }
                if (ln.mn != -1) 
                    mns.push_back(make_pair(ln.mn, ln.varID));

                expID = ln.expID;
                year = ln.year;
                loccd = ln.loccd;
                rep = ln.rep;
            }

            map<int, float> varID2MNWeights;
            for (map<int, vector<float> >::iterator it=id2mns.begin(); it!=id2mns.end(); it++) {
                int id = it->first;
                vector<float> &s = it->second;
                float sum = 0.0;
                for (unsigned int i=0; i<s.size(); i++)
                    sum += s[i];
                float ave = sum/s.size();
                varID2MNWeights[id] = ave;
            }

            return varID2MNWeights;
        }

        vector<int> getPred(vector<pair<float, int> > &rawScores)
        {
            vector<pair<float, int> > scores;
            for (unsigned int i=0; i<rawScores.size(); i++) {
                float score = rawScores[i].first;
                int id = rawScores[i].second;
                // signal: year
                score *= m_yearScale[m_years[id]];
                // signal: type
                score *= m_typeScale[m_types[id]];
                // signal: band
                score *= m_bandScale[m_bands[id]];
                // signal: number of days mn ahead of check var
                score += m_varID2MNWeights[id]*0.3;
                scores.push_back(make_pair(score, id));
            }

            sort(scores.begin(), scores.end());
            reverse(scores.begin(), scores.end());

            vector<int> pred;
            for (unsigned int i=0; i<scores.size(); i++)
                pred.push_back(scores[i].second);

            return pred;
        }

        vector<int> getPredAll(vector<pair<float, int> > &rawScores)
        {
            map<int, int> idOrders;
            for (int i=0; i<5; i++) {
                setParas(i);
                vector<int> pred = getPred(rawScores);
                for (unsigned int j=0; j<pred.size(); j++)
                    idOrders[pred[j]] += j;
            }

            vector<pair<int, int> > orderIDs;
            for (map<int, int>::iterator it=idOrders.begin(); it!=idOrders.end(); it++)
                orderIDs.push_back(make_pair(it->second, it->first));
            sort(orderIDs.begin(), orderIDs.end());
            vector<int> pred;
            for (unsigned int i=0; i<orderIDs.size(); i++)
                pred.push_back(orderIDs[i].second);
            return pred;
        }

        double getScore(vector<int> &pred)
        {
            double score = 0.0;
            int total = 0;
            int correct = 0;
            int totElite = 0;

            for (unsigned int i=0; i<pred.size(); i++) {
                if (m_elites[pred[i]])
                    totElite++;
            }
            for (unsigned int i=0; i<pred.size(); i++) {
                total++;
                if (m_elites[pred[i]] == 1) {
                    correct++;
                    score += (1000000.0 / totElite) * correct / total;
                }
            }
            return score;
        }

        void trainYear(vector<pair<float, int> > &rawScores, int niter, float *pstep)
        {
            float scale = 0.95;

            if (*pstep == 0.0)
                *pstep = 0.02;
            float ystep = *pstep;

            ystep = 0.02;

            vector<int> pred = getPred(rawScores);
            double bestScore = getScore(pred);

            for (int i=0; i<niter; i++) {
                for (int y=2000; y<=2008; y++) {
                    m_yearScale[y] += ystep;
                    vector<int> pred = getPred(rawScores);
                    double score = getScore(pred);
                    if (score < bestScore) {
                        m_yearScale[y] -= 2*ystep;
                        vector<int> pred = getPred(rawScores);
                        double score = getScore(pred);
                        if (score < bestScore) {
                            m_yearScale[y] += ystep;
                        } else {
                            bestScore = score;
                        }
                    } else {
                        bestScore = score;
                    }
                }
                ystep *= scale;
            }
            *pstep = ystep;
        }

        void trainType(vector<pair<float, int> > &rawScores, int niter, float *pstep)
        {
            float scale = 0.95;

            if (*pstep == 0.0)
                *pstep = 0.02;
            float tstep = *pstep;

            tstep = 0.02;

            vector<int> pred = getPred(rawScores);
            double bestScore = getScore(pred);

            for (int i=0; i<niter; i++) {
                for (int t=0; t<=2; t++) {
                    m_typeScale[t] += tstep;
                    vector<int> pred = getPred(rawScores);
                    double score = getScore(pred);
                    if (score < bestScore) {
                        m_typeScale[t] -= 2*tstep;
                        vector<int> pred = getPred(rawScores);
                        double score = getScore(pred);
                        if (score < bestScore) {
                            m_typeScale[t] += tstep;
                        } else {
                            bestScore = score;
                        }
                    } else {
                        bestScore = score;
                    }
                }
                tstep *= scale;
            }
            *pstep = tstep;
        }

        void trainBand(vector<pair<float, int> > &rawScores, int niter, float *pstep)
        {
            float scale = 0.95;

            if (*pstep == 0.0)
                *pstep = 0.02;
            float bstep = *pstep;

            bstep = 0.02;

            vector<int> pred = getPred(rawScores);
            double bestScore = getScore(pred);

            for (int i=0; i<niter; i++) {
                for (int b=0; b<=9; b++) {
                    m_bandScale[b] += bstep;
                    vector<int> pred = getPred(rawScores);
                    double score = getScore(pred);
                    if (score < bestScore) {
                        m_bandScale[b] -= 2*bstep;
                        vector<int> pred = getPred(rawScores);
                        double score = getScore(pred);
                        if (score < bestScore) {
                            m_bandScale[b] += bstep;
                        } else {
                            bestScore = score;
                        }
                    } else {
                        bestScore = score;
                    }
                }
                bstep *= scale;
            }

            *pstep = bstep;
        }

        void dumpYearScale()
        {
            fprintf(stderr, "m_yearScale {");
            for (int i=2000; i<=2008; i++) {
                fprintf(stderr, "%.3f,", m_yearScale[i]);
            }
            fprintf(stderr, "},\n");
        }

        void dumpTypeScale()
        {
            fprintf(stderr, "m_typeScale {");
            for (int i=0; i<=2; i++) {
                fprintf(stderr, "%.3f,", m_typeScale[i]);
            }
            fprintf(stderr, "},\n");
        }

        void dumpBandScale()
        {
            fprintf(stderr, "m_bandScale {");
            for (int i=0; i<=9; i++) {
                fprintf(stderr, "%.3f,", m_bandScale[i]);
            }
            fprintf(stderr, "},\n");
        }

        void trainMN(vector<pair<float, int> > &rawScores)
        {
            float mnstep = 5;
            float yieldstep = 0.2;
            float scale = 0.95;

            vector<int> pred = getPred(rawScores);
            double bestScore = getScore(pred);

            for (int i=0; i<10; i++) {
                cout<<"train "<<i<<endl;

                m_mnAve += mnstep;
                pred = getPred(rawScores);
                double score = getScore(pred);
                if (score < bestScore) {
                    m_mnAve -= 2*mnstep;
                    vector<int> pred = getPred(rawScores);
                    double score = getScore(pred);
                    if (score < bestScore) {
                        m_mnAve += mnstep;
                    } else {
                        bestScore = score;
                        cout<<"m_mnAve "<<m_mnAve<<" "<<bestScore<<endl;
                    }
                } else {
                    bestScore = score;
                    cout<<"m_mnAve "<<m_mnAve<<" "<<bestScore<<endl;
                }
                mnstep *= scale;

                m_yieldPerMN += yieldstep;
                pred = getPred(rawScores);
                score = getScore(pred);
                if (score < bestScore) {
                    m_yieldPerMN -= 2*yieldstep;
                    vector<int> pred = getPred(rawScores);
                    double score = getScore(pred);
                    if (score < bestScore) {
                        m_yieldPerMN += yieldstep;
                    } else {
                        bestScore = score;
                        cout<<"m_yieldPerMN "<<m_yieldPerMN<<" "<<bestScore<<endl;
                    }
                } else {
                    bestScore = score;
                    cout<<"m_yieldPerMN "<<m_yieldPerMN<<" "<<bestScore<<endl;
                }
                yieldstep *= scale;
            }
        }

        void splitData(map<int, vector<string> > &allData, map<int, vector<string> > &trainData, map<int, vector<string> > &testData, unsigned int testNum)
        {
            trainData.clear();
            testData.clear();

            vector<int> expIDs;
            for (map<int, vector<string> >::iterator it=allData.begin(); it!=allData.end(); it++) {
                expIDs.push_back(it->first);
            }
            int totalNum = expIDs.size();

            if (testNum < allData.size()) {
                while (testData.size() < testNum) {
                    int eID = expIDs[random()%totalNum];
                    if (testData.find(eID) == testData.end())
                        testData[eID] = allData[eID];
                }

                for (unsigned int i=0; i<expIDs.size(); i++) {
                    int eID = expIDs[i];
                    if (testData.find(eID) == testData.end()) {
                        trainData[eID] = allData[eID];
                    }
                }
            } else
                testData = allData;
        }

        vector<string> sampleData(map<int, vector<string> > &allData, unsigned int num)
        {
            if (num == allData.size()) {
                vector<string> data;
                for (map<int, vector<string> >::iterator it=allData.begin(); it!=allData.end(); it++) {
                    data.insert(data.end(), it->second.begin(), it->second.end());
                }
                return data;
            }

            vector<int> expIDs;
            for (map<int, vector<string> >::iterator it=allData.begin(); it!=allData.end(); it++) {
                expIDs.push_back(it->first);
            }
            int totalNum = expIDs.size();

            set<int> samples;
            while (samples.size() < num) {
                int eID = expIDs[random()%totalNum];
                samples.insert(eID);
            }

            vector<string> data;
            for (set<int>::iterator it=samples.begin(); it!=samples.end(); it++) {
                data.insert(data.end(), allData[*it].begin(), allData[*it].end());
            }
            return data;
        }

        void getSubsetScore(map<int, vector<string> > &allData, int expNum, int testCaseNum, double *aveScore, double *varScore)
        {
            double scoreSum = 0.0;
            vector<double> scores;
            for (int i=0; i<testCaseNum; i++) {
                //if (i > 0 && i%100 == 0) cout<<"number "<<i<<endl;
                vector<string> data = sampleData(allData, expNum);
                vector<Line> testLines = trans2Lines(data);
                vector<pair<float, int> > rawScores = getRawScore(testLines);
                vector<int> pred = getPred(rawScores);
                double score = getScore(pred);
                scoreSum += score;
                scores.push_back(score);
            }
            double ave = scoreSum/testCaseNum;
            double delta2 = 0.0;
            for (int i=0; i<testCaseNum; i++)
                delta2 += (scores[i]-ave)*(scores[i]-ave);
            *aveScore = ave;
            *varScore = sqrt(delta2/testCaseNum);
        }

        double getAveScore(vector<vector<vector<int> > > &predRoundIter, int iter)
        {
            map<int, int> idOrders;
            for (unsigned int j=0; j<predRoundIter.size(); j++) {
                vector<int> &pred = predRoundIter[j][iter];
                for (unsigned int k=0; k<pred.size(); k++)
                    idOrders[pred[k]] += k;
            }
            vector<pair<int, int> > orderIDs;
            for (map<int, int>::iterator it=idOrders.begin(); it!=idOrders.end(); it++)
                orderIDs.push_back(make_pair(it->second, it->first));
            sort(orderIDs.begin(), orderIDs.end());
            vector<int> pred;
            for (unsigned int i=0; i<orderIDs.size(); i++)
                pred.push_back(orderIDs[i].second);
            return getScore(pred);
        }

        // train yearscale, typescale, bandscale, these para have nothing to do with raw score
        void train1(vector<string> &data, vector<string> &locations)
        {
            vector<Line> lines = trans2Lines(data);
            initVarFeature(lines);
            m_LOCCDs = getLoccdSet(locations);
            initPara();
            m_varID2Weights = getVar2Weight(lines);
            m_varID2MNWeights = getVarID2MNWeight(lines);
            m_varID2MNs = getMNs(lines);
            m_varID2MNValidNum = getMNValidNum(lines);

            map<int, vector<string> > expAllData;
            for (unsigned int i=0; i<data.size(); i++) {
                Line ln(data[i].c_str());
                expAllData[ln.expID].push_back(data[i]);
            }

            map<int, vector<string> > expTrainData, expTestData;
            int expTestNum = 0;
            splitData(expAllData, expTrainData, expTestData, expTestNum);

            vector<string> trainData;
            for (map<int, vector<string> >::iterator it=expTrainData.begin(); it!=expTrainData.end(); it++)
                trainData.insert(trainData.end(), it->second.begin(), it->second.end());

            vector<string> testData;
            for (map<int, vector<string> >::iterator it=expTestData.begin(); it!=expTestData.end(); it++)
                testData.insert(testData.end(), it->second.begin(), it->second.end());

            vector<Line> trainLines = trans2Lines(trainData);
            vector<pair<float, int> > trainRawScores = getRawScore(trainLines);

            vector<Line> testLines = trans2Lines(testData);
            vector<pair<float, int> > testRawScores = getRawScore(testLines);

            vector<vector<vector<int> > > trainPredRoundIter, testPredRoundIter;
            int nRound = 5;
            int nIter = 10;
            for (int j=0; j<nRound; j++) {
                vector<vector<int> > trainPredIter, testPredIter;
                randInitPara();
                cout<<"round "<<j<<endl;

                float ystep, tstep, bstep;
                ystep = tstep = bstep = 0.02;
                for (int i=0; i<nIter; i++) {
                    trainYear(trainRawScores, 1, &ystep);
                    trainType(trainRawScores, 1, &tstep);
                    trainBand(trainRawScores, 1, &bstep);

                    vector<int> trainPred = getPred(trainRawScores);
                    double trainScore = getScore(trainPred);

                    vector<int> testPred = getPred(testRawScores);
                    double testScore = getScore(testPred);

                    int testCaseNum = 1;
                    double aveScore = 0.0, varScore = 0.0;
                    getSubsetScore(expTestData, 50, testCaseNum, &aveScore, &varScore);

                    trainPredIter.push_back(trainPred);
                    testPredIter.push_back(testPred);
                    printf("%d %8.0f %8.0f %8.0f %8.0f\n", i, trainScore, testScore, aveScore, varScore);
                }
                dumpYearScale();
                dumpTypeScale();
                dumpBandScale();

                trainPredRoundIter.push_back(trainPredIter);
                testPredRoundIter.push_back(testPredIter);
            }

            printf("average score:\n");
            for (int i=0; i<nIter; i++) {
                double trainScore = getAveScore(trainPredRoundIter, i);
                double testScore = 0.0;
                //double testScore = getAveScore(testPredRoundIter, i);
                printf("%d %8.0f %8.0f\n", i, trainScore, testScore);
            }

            vector<pair<float, int> > rawScores = getRawScore(lines);
            vector<int> pred = getPred(rawScores);
            double score = getScore(pred);
            printf("alldata score %f\n", score);
        }

        void trainEmptyLocScale(vector<Line> &lines, int niter, float *pstep)
        {
            float scale = 0.85;

            if (*pstep == 0.0)
                *pstep = 0.02;
            float step = *pstep;

            vector<pair<float, int> > rawScores = getRawScore(lines);
            vector<int> pred = getPredAll(rawScores);
            double bestScore = getScore(pred);

            for (int i=0; i<niter; i++) {
                    m_emptyLocScale += step;
                    vector<pair<float, int> > rawScores = getRawScore(lines);
                    vector<int> pred = getPredAll(rawScores);
                    double score = getScore(pred);

                    if (score < bestScore) {
                        m_emptyLocScale -= 2*step;
                        vector<pair<float, int> > rawScores = getRawScore(lines);
                        vector<int> pred = getPredAll(rawScores);
                        double score = getScore(pred);

                        if (score < bestScore) {
                            m_emptyLocScale += step;
                        } else {
                            bestScore = score;
                        }
                    } else {
                        bestScore = score;
                    }
                step *= scale;
            }
            *pstep = step;
        }

        void trainTrialScale(vector<Line> &lines, int niter, float *pstep)
        {
            float scale = 0.85;

            if (*pstep == 0.0)
                *pstep = 0.02;
            float step = *pstep;

            vector<pair<float, int> > rawScores = getRawScore(lines);
            vector<int> pred = getPredAll(rawScores);
            double bestScore = getScore(pred);

            for (int i=0; i<niter; i++) {
                    m_trialScale += step;
                    vector<pair<float, int> > rawScores = getRawScore(lines);
                    vector<int> pred = getPredAll(rawScores);
                    double score = getScore(pred);

                    if (score < bestScore) {
                        m_trialScale -= 2*step;
                        vector<pair<float, int> > rawScores = getRawScore(lines);
                        vector<int> pred = getPredAll(rawScores);
                        double score = getScore(pred);

                        if (score < bestScore) {
                            m_trialScale += step;
                        } else {
                            bestScore = score;
                        }
                    } else {
                        bestScore = score;
                    }
                step *= scale;
            }
            *pstep = step;
        }

        // train other para that used in getRawScore()
        void train2(vector<string> &data, vector<string> &locations)
        {
            vector<Line> lines = trans2Lines(data);
            initVarFeature(lines);
            m_LOCCDs = getLoccdSet(locations);
            initPara();
            m_varID2Weights = getVar2Weight(lines);
            m_varID2MNWeights = getVarID2MNWeight(lines);
            m_varID2MNs = getMNs(lines);
            m_varID2MNValidNum = getMNValidNum(lines);

            map<int, vector<string> > expAllData;
            for (unsigned int i=0; i<data.size(); i++) {
                Line ln(data[i].c_str());
                expAllData[ln.expID].push_back(data[i]);
            }

            map<int, vector<string> > expTrainData, expTestData;
            int expTestNum = 700;
            splitData(expAllData, expTrainData, expTestData, expTestNum);

            vector<string> trainData;
            for (map<int, vector<string> >::iterator it=expTrainData.begin(); it!=expTrainData.end(); it++)
                trainData.insert(trainData.end(), it->second.begin(), it->second.end());

            vector<string> testData;
            for (map<int, vector<string> >::iterator it=expTestData.begin(); it!=expTestData.end(); it++)
                testData.insert(testData.end(), it->second.begin(), it->second.end());

            vector<Line> trainLines = trans2Lines(trainData);
            vector<Line> testLines = trans2Lines(testData);

            vector<vector<vector<int> > > trainPredRoundIter, testPredRoundIter;
            int nRound = 5;
            int nIter = 10;
            for (int j=0; j<nRound; j++) {
                vector<vector<int> > trainPredIter, testPredIter;

                m_emptyLocScale = 0.9 + (0.2 * (random() / (RAND_MAX + 1.0)));
                m_trialScale = 6.0 + (0.2 * (random() / (RAND_MAX + 1.0)));

                cout<<"round "<<j<<endl;

                float elstep = 0.0;
                float trialstep = 0.0;
                for (int i=0; i<nIter; i++) {

                    trainEmptyLocScale(trainLines, 1, &elstep);
                    trainTrialScale(trainLines, 1, &trialstep);

                    vector<pair<float, int> > trainRawScores = getRawScore(trainLines);
                    vector<int> trainPred = getPredAll(trainRawScores);
                    double trainScore = getScore(trainPred);

                    vector<pair<float, int> > testRawScores = getRawScore(testLines);
                    vector<int> testPred = getPredAll(testRawScores);
                    double testScore = getScore(testPred);

                    int testCaseNum = 1;
                    double aveScore = 0.0, varScore = 0.0;
                    getSubsetScore(expTestData, 50, testCaseNum, &aveScore, &varScore);

                    trainPredIter.push_back(trainPred);
                    testPredIter.push_back(testPred);
                    printf("%d %8.0f %8.0f %8.0f %8.0f %2.3f %2.3f\n", i, trainScore, testScore, aveScore, varScore, m_emptyLocScale, m_trialScale);
                }
                printf("m_emptyLocScale: %.3f\n", m_emptyLocScale);
                printf("m_trialScale: %.3f\n", m_trialScale);
                //dumpBandScale();

                trainPredRoundIter.push_back(trainPredIter);
                testPredRoundIter.push_back(testPredIter);
            }

            printf("average score:\n");
            for (int i=0; i<nIter; i++) {
                double trainScore = getAveScore(trainPredRoundIter, i);
                double testScore = 0.0;
                testScore = getAveScore(testPredRoundIter, i);
                printf("%d %8.0f %8.0f\n", i, trainScore, testScore);
            }

            vector<pair<float, int> > rawScores = getRawScore(lines);
            vector<int> pred = getPredAll(rawScores);
            double score = getScore(pred);
            printf("alldata score %f\n", score);
        }

        void setElites(map<int, int> elites)
        {
            this->m_elites = elites;
        }

        vector <int> classify(vector<string> data, vector<string> locations)
        {
            vector<Line> lines = trans2Lines(data);
            initVarFeature(lines);
            initPara();
            m_LOCCDs = getLoccdSet(locations);
            m_varID2MNs = getMNs(lines);
            m_varID2MNValidNum = getMNValidNum(lines);
            m_varID2Weights = getVar2Weight(lines);
            m_varID2MNWeights = getVarID2MNWeight(lines);

            vector<pair<float, int> > rawScores = getRawScore(lines);
            vector<int> pred = getPredAll(rawScores);

            return pred;
        }
};

#ifdef LOCAL_TEST

void getData(vector<string> &data, map<int,int> &elites)
{
    data.clear();
    elites.clear();
    char aline[200];
    FILE *f = fopen("DataTraining.csv", "r");

    while (fgets(aline, sizeof(aline), f)) {
        Line ln(aline);
        elites[ln.varID] = ln.isElite;

        aline[strlen(aline)-3] = '\0';
        data.push_back(string(aline));
    }
    fclose(f);
}

void getLocation(vector<string> &location)
{
    location.clear();
    char aline[200];
    FILE *f = fopen("Locations.csv", "r");
    while (fgets(aline, sizeof(aline), f)) {
        aline[strlen(aline)-1] = '\0';
        location.push_back(string(aline));
    }
    fclose(f);
}

int main(void)
{
    //srandom(time(NULL));
    //srandom(1);
    //srandom(2);
    srandom(3);

    vector<string> data;
    map<int,int> elites;
    getData(data, elites);

    vector<string> locations;
    getLocation(locations);

    EliteClassifier ec;
    ec.setElites(elites);

    //ec.train1(data, locations);
    //ec.train2(data, locations);

    vector<int> pred = ec.classify(data, locations);
    double score = ec.getScore(pred);
    cout<<"score "<<score<<endl;

    return 0;
}

#endif
//#include "elder1g.h"
//#include "a.cpp"

void read_csv(string file, vector<string> &data){
    ifstream in(file.c_str());
    string s;
    data.clear();
    while(getline(in, s)){
        data.push_back(s);
    }
}


set<int> self_test_elite;
void gen_elite(vector<string> data){
    for(int i=0; i<(int)data.size(); i++){
        for(size_t j=0; j<data[i].size(); j++)
            if(data[i][j]==',' || data[i][j]=='-' ) data[i][j]=' ';
        string nouse;
        int variety_id;
        stringstream ss(data[i]);
        ss>> nouse >> nouse >> nouse >> variety_id;
        char c=data[i][data[i].size()-1];
        if(c=='1'){
            self_test_elite.insert(variety_id);
        }
    }
}
vector<string> train, locations, test;
void init(){
    //read_csv("DataTraining/datatraining.csv", train);
    //read_csv("locations.csv", locations);

    //gen_elite(train);
    ifstream x("elite");
    int t;
    while (x>>t){
        self_test_elite.insert(t);
    }
}
vector<string> parse(vector<string> & orig){
    vector<string> data;

    for(size_t i=0; i<orig.size(); i++){
        string s=orig[i];

        for(size_t j=0; j<s.size(); j++)
            if(s[j]==',' || s[j]=='-' ) s[j]=' ';
        string experiment_id, loccd, rep, variety_id, year, type, rm, ischeck, yield, mn;

        string str;
        stringstream ss(s);
        ss>> experiment_id >> loccd >> rep >> variety_id >> year;
        ss>> str;
        ss>> str;
        ss >> type;
        ss >> yield;
        ss >> mn;
        ss >> rm;
        ss >> str; //pd_cr=str_to_double(str);
        ss >> str; //pb_cr=str_to_double(str);
        ss >> str; //fl_cr=str_to_double(str);
        ss >> str; //emrgr=str_to_double(str);
        ss >> str; //plhtn=str_to_double(str);
        ss >> str; //hldgr=str_to_double(str);
        ss >> ischeck;

        string t=experiment_id+","+year+","+loccd+","+rep+","+type+","+variety_id+","+yield+","+mn+","+rm+","+ischeck;
        data.push_back(t);
    }
    return data;
}
class AdvancedEliteClassifier
{
    public:
    vector<int> classify(vector<string> test, vector<string> train, vector<string> locations){
        EliteClassifier1 t1;
        EliteClassifier2 t2;
        EliteClassifier4 t4;
        vector<string> p=parse(test);
        vector<int> res1=t1.classify(p, locations);
        //ratio 25.??
        vector<int> res2=t2.classify(p, locations);
        //ratio 26.96136
        vector<int> res4=t4.classify(p, locations);
        //ratio 24.91639
        //vector<int> res5=t5.classify(p, locations);
        //return res4;

        map<int, double> score;
        int n=res1.size();
        //ratio 27.97 total
        for(int i=0; i<n; i++){
            score[res1[i]]+=i;
            score[res2[i]]+=i;
            //score[res4[i]]+=i;
            //remove this 28.12
        }
        score.clear();
        //ratio 27.3 total with 1.5 power
        //ratio 27.9 total with 1.0 power
        //ratio 28.9 total with 0.5 power
        //ratio 29.2 total with 0.4 power
        //ratio 29.3 total with 0.3 power
        //ratio 29.0 total with 0.2 power
        for(int i=0; i<n; i++){
            //
            //ratio 28.6  with top 2, 0.5 pow
            //ratio 28.4  with top 2, 0.3 pow
            //ratio 29.4  with 0.3 0.4 0.3 pow
            //ratio 29.5  with 0.4 0.5 0.3 pow
            //ratio 29.25 with 0.4 0.6 0.3 pow


            //check linear
            double PAR1, PAR2, PAR3;
            PAR1=PAR2=PAR3=1;
            score[res1[i]]+=5*pow(i, 0.001);
            score[res2[i]]+=6*pow(i, 0.001);
            score[res4[i]]+=2*pow(i, 0.001);
        }

        vector<int> res;
        vector<pair< double,int> > res_tmp;
        for(map<int, double>::iterator iter=score.begin(); iter!=score.end(); iter++){
            res_tmp.push_back(make_pair(iter->second, iter->first));
            //cerr<<iter->second<<endl;
        }
        sort(res_tmp.begin(), res_tmp.end());
        for(size_t i=0; i<res_tmp.size(); i++){
            //if(i<20)
                //cerr<<res_tmp[i].first<< " " << res_tmp[i].second<<endl;
            res.push_back(res_tmp[i].second);
        }
        return res;
    }

};
void test_file(string testfile){

    read_csv(testfile, test);
    AdvancedEliteClassifier classifyer;
    vector<int > x=    classifyer.classify(test, train, locations);
    //for(size_t i=0; i<x.size(); i++){
        //cout<<x[i]<<endl;
    //}
    double correct=0;
    double total=0;
    double ans=0;
    double total_elite=0;
    for(size_t i=0; i<x.size(); i++){
        if(self_test_elite.count(x[i])){
            //cerr<<" elite " << x[i]<<endl;
            total_elite++;
        }
    }
    //cerr<<"total elite " <<total_elite<<endl;
    for(size_t i=0; i<x.size(); i++){
        total++;
        if(self_test_elite.count(x[i])){
            correct++;
            //cerr<< " correct total " << correct << " " << total << endl;
            ans+=correct/total/total_elite;
        }
    }
    cout<<ans<<endl;
}
