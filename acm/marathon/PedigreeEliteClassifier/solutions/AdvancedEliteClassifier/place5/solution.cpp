// #define LOCAL
// TopCoder Marathon - soybean 6
// author: elder1g
// extended author: Lozy

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
int strtoint(string str)
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
    trialcnt_suc[1]=38;trialcnt_tot[1]=4820;trialcnt_ratio[1]=0.00788589;
    trialcnt_suc[2]=43;trialcnt_tot[2]=9151;trialcnt_ratio[2]=0.00470003;
    trialcnt_suc[3]=66;trialcnt_tot[3]=6616;trialcnt_ratio[3]=0.00997733;
    trialcnt_suc[4]=167;trialcnt_tot[4]=10415;trialcnt_ratio[4]=0.0160355;
    trialcnt_suc[5]=166;trialcnt_tot[5]=10131;trialcnt_ratio[5]=0.0163863;
    trialcnt_suc[6]=136;trialcnt_tot[6]=10694;trialcnt_ratio[6]=0.0127183;
    trialcnt_suc[7]=139;trialcnt_tot[7]=8891;trialcnt_ratio[7]=0.0156349;
    trialcnt_suc[8]=181;trialcnt_tot[8]=12280;trialcnt_ratio[8]=0.0147402;
    trialcnt_suc[9]=140;trialcnt_tot[9]=8201;trialcnt_ratio[9]=0.0170723;
    trialcnt_suc[10]=162;trialcnt_tot[10]=11684;trialcnt_ratio[10]=0.013866;
    trialcnt_suc[11]=39;trialcnt_tot[11]=2937;trialcnt_ratio[11]=0.0132823;
    trialcnt_suc[12]=53;trialcnt_tot[12]=4352;trialcnt_ratio[12]=0.0121806;
    trialcnt_suc[13]=6;trialcnt_tot[13]=149;trialcnt_ratio[13]=0.0403356;
    trialcnt_suc[14]=5;trialcnt_tot[14]=285;trialcnt_ratio[14]=0.0175789;
    trialcnt_suc[15]=4;trialcnt_tot[15]=176;trialcnt_ratio[15]=0.0227841;
    trialcnt_suc[16]=3;trialcnt_tot[16]=150;trialcnt_ratio[16]=0.0200667;
    trialcnt_suc[17]=0;trialcnt_tot[17]=62;trialcnt_ratio[17]=0.00016129;
    trialcnt_suc[18]=0;trialcnt_tot[18]=91;trialcnt_ratio[18]=0.00010989;
    trialcnt_suc[19]=1;trialcnt_tot[19]=57;trialcnt_ratio[19]=0.0177193;
    trialcnt_suc[25]=2;trialcnt_tot[25]=31;trialcnt_ratio[25]=0.0648387;
    trialcnt_suc[28]=0;trialcnt_tot[28]=58;trialcnt_ratio[28]=0.000172414;
    trialcnt_suc[29]=0;trialcnt_tot[29]=26;trialcnt_ratio[29]=0.000384615;
    //----------
    year_suc[2000]=1;year_tot[2000]=567;year_ratio[2000]=0.00176367;
    year_suc[2001]=47;year_tot[2001]=2314;year_ratio[2001]=0.0203111;
    year_suc[2002]=203;year_tot[2002]=5017;year_ratio[2002]=0.0404624;
    year_suc[2003]=170;year_tot[2003]=6955;year_ratio[2003]=0.0244428;
    year_suc[2004]=131;year_tot[2004]=7694;year_ratio[2004]=0.0170263;
    year_suc[2005]=163;year_tot[2005]=19297;year_ratio[2005]=0.00844691;
    year_suc[2006]=179;year_tot[2006]=11439;year_ratio[2006]=0.0156482;
    year_suc[2007]=285;year_tot[2007]=24157;year_ratio[2007]=0.0117978;
    year_suc[2008]=172;year_tot[2008]=23817;year_ratio[2008]=0.00722173;

    cnt_sta_suc[36]=1277;cnt_sta_tot[36]=77369;cnt_sta_ratio[36]=0.0165053;
    
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
                else if (year!=2005 && year != 2004) estimate*=0.85;
                else estimate*=1.01;  // XXX
            }

            //ensure top ones don't contain vars from unstable(too small) exps.
            if (tct == 1 || tct == 2) estimate*=0.618;
            if (tct>=7 && tct<=9) estimate*=1.1;
            estimate*=(1+trialcnt_ratio[tct]);
            
            // TODO
            // double ex2=var.square_sum/tct;
            // double ex_2=(var.wins_cnt*var.wins_cnt/var.tot_cnt/var.tot_cnt);
            // double dx=ex2-ex_2;
            // if (dx>0.05) estimate*=(1-0.1*dx);
            
                        
            if (exper.vars.size()==40) estimate*=0.7;
            else if (exper.vars.size()==36) {
                if (exper.check_count==3 || exper.check_count==2) estimate*=1.05;
                else if (exper.check_count==4) estimate*=1.1;
                else if (exper.check_count==5 /*&& var.type!="conv"*/) estimate*=1.15;
                else if (exper.check_count>=6 && exper.check_count<=11) estimate*=1.1;
            }
            
            estimate*=(1+5*pow(year_ratio[year],0.3));
            
            if (var.type == "RR1") {
                if (year == 2001) estimate*=1.0260181;
                else if (year == 2002) estimate*=1.0490299;
                else if (year == 2003) estimate *= 1.0295546;
                else if (year == 2004) estimate *= 1.0144082;
                else if (year == 2006) estimate*=1.00823287;
                else estimate *= 0.999;
            }
        }
    }
    return estimate;
}

inline bool cmp(pair<int, int> a, pair<int, int> b) {return a.second > b.second;}
inline bool pcmp(pair<pair<int,string> ,pair<int,int> > a, pair<pair<int,string> ,pair<int,int> > b) {
    return a.second.first * 1.0 / a.second.second > b.second.first * 1.0 / b.second.second;
}
inline bool icmp(pair<pair<int,int> ,pair<int,int> > a, pair<pair<int,int> ,pair<int,int> > b) {
    return a.second.first * 1.0 / a.second.second > b.second.first * 1.0 / b.second.second;
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
    cout << afilename.c_str() << endl;
    ofstream out (afilename.c_str());
    out<<"Exp count:"<<exps.size()<<endl;
    for (int i=0;i<exps.size();++i)
        exp_year_count[exps[i].year]++;
    vector<pair<int, int> > v;
    v.clear();
    for (int i=0;i<3000;++i)
        if (exp_year_count[i]!=0) {
            v.push_back(make_pair(i, exp_year_count[i]));
        }
    sort(v.begin(), v.end(), cmp);
    for (vector<pair<int, int> >::iterator it = v.begin(); it != v.end(); ++it)
            out<<"Year "<<it->first<<":"<<it->second<<endl;
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
    out << "elites ratio:" << (tot_elite * 1.0) / tot_vars << endl;
    out<<"----------"<<endl;
    std::vector<pair<pair<int,string> ,pair<int,int> > > vp;
    vp.clear();
    for(map<pair<int,string> ,pair<int,int> >::iterator it=year_type_cnt.begin();it!=year_type_cnt.end();++it) {
        vp.push_back(make_pair(it->first, it->second));
    }
    sort(vp.begin(), vp.end(), pcmp);
    for(vector<pair<pair<int,string> ,pair<int,int> > >::iterator it=vp.begin();it!=vp.end();++it)
        out<<"Year-Type "<<it->first.first<<" "<<it->first.second<<":"<<it->second.first<<"/"
            <<it->second.second<<"("<<it->second.first*1.0/it->second.second<<")"<<endl;
    out<<"----------"<<endl;
    for(map<string,pair<int,int> >::iterator it=type_cnt.begin();it!=type_cnt.end();++it)
        out<<"Type "<<it->first<<":"<<it->second.first<<"/"<<it->second.second<<"("<<it->second.first*1.0/it->second.second<<")"<<endl;
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=trials_count_cnt.begin();it!=trials_count_cnt.end();++it)
    {
        out<<"trialcnt_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"trialcnt_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"trialcnt_ratio["<<it->first<<"]="<<(it->second.first*1.0 + 0.01)/(it->second.second)<<";";
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
    vector<pair<pair<int, int>, pair<int, int> > > vii;
    vii.clear();
    for (map<pair<int,int>, pair<int, int> >::iterator itr=check_cnt_sta.begin();itr!=check_cnt_sta.end();++itr)
    {
        vii.push_back(make_pair(itr->first, itr->second));
    }
    sort(vii.begin(), vii.end(), icmp);
    for (vector<pair<pair<int, int>, pair<int, int> > >::iterator itr=vii.begin();itr!=vii.end();++itr)
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
            se>>experiment_id>>loccd>>rep>>variety_id>>str>>type;
            year = strtoint(str.substr(0, 4));
            se>>str;
            if(str=="NULL") yield=-1; else yield=strtodouble(str);
            se>>str;
            if(str=="NULL") mn=-1; else mn=strtoint(str);
            se>>str;
            if(str=="NULL") rm=-1; else rm=strtodouble(str);
            se>>str;
            se>>str;
            se>>str;
            se>>str;
            se>>str;
            se>>str;
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
        // if(sub_band=="Early") band_number+=0.33;
        // else if(sub_band=="Mid") band_number+=0.66;
        // else if(sub_band=="Late") band_number+=0.99;
        location_info[loccd]=make_pair(band_number,zone);
    }
}

struct AdvancedEliteClassifier
{
    vector<int> classify(vector<string>& data, vector<string>& trainData, vector<string>& locations)
    {
        init_info();
        construct_datastructure(data,false);
        construct_location_data(locations);
        for (int i=0;i<exps.size();++i)
        {
            if (i % 100 == 0) cout << i << endl;
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
                    // if (!mn_available) rwt=0.95; // XXX
                    rwt/=(1+exps[i].trials[j].rep_tot);
                    double pm=1.5;
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
        se>>variety_id;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
        se>>tmp_string;
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
    data.reserve(5000);
    string str;
    while(getline(input,str))
    {
        data.push_back(str);
    }
}
int r = 0;
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
        else if (i<500)
        {
            ++r;
            cout<<i<<": "<<guess[i]<<endl;
        }
    }
    cout << r << endl;
    return score;
}

int main()
{
    int test = 1;
    if (test) {
        AdvancedEliteClassifier classifier;
        
        vector<string> data;
        read_data("DataTraining.csv",data);
        vector<string> locations;
        read_location("Locations.csv",locations);
        cout << "begin" << endl;
        vector<int> guess=classifier.classify(data,data,locations);
        double score=calculate_score(guess);
        cout<<"Score on train set:"<<score<<endl;
    } else {
        analyze("train.csv");
    }
    return 0;
}
#endif
