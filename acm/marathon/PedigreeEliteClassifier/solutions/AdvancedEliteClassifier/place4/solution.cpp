#include <cctype>
#include <cstring>
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
#include <numeric>

using namespace std;

//#define LOCAL

#define MAX_VARS_IN_EXP 100
struct Trial
{
    int loccd;
    int rep;
    int rep_tot;
    bool mn_ava;
    double yields[MAX_VARS_IN_EXP];
    int mns[MAX_VARS_IN_EXP];
    int pdcrs[MAX_VARS_IN_EXP];
    int pbcrs[MAX_VARS_IN_EXP];
    int flcrs[MAX_VARS_IN_EXP];
    int emrgrs[MAX_VARS_IN_EXP];
    int plhtns[MAX_VARS_IN_EXP];
    int hldgrs[MAX_VARS_IN_EXP];
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
    int rank_in_exp;
    Variety()
    {
        wins_cnt=0;
        tot_cnt=0;
        estimate=0;
        square_sum=0;
        mins=10000;
        rank_in_exp = 0;
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
        for (unsigned int i=0;i<trials.size();++i)
            if (trials[i].loccd==loccd && trials[i].rep==rep) return trials[i];
        Trial newtrial;
        newtrial.loccd=loccd;
        newtrial.rep=rep;
        trials.push_back(newtrial);
        return trials.back();
    }
};


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

int year_suc[2500];
int year_tot[2500];
double year_ratio[2500];

int trialcnt_suc[50];
int trialcnt_tot[50];
double trialcnt_ratio[50];

int cnt_sta_suc[50];
int cnt_sta_tot[50];
double cnt_sta_ratio[50];

//analyze use, shared by main part
map<int, int> eid_to_pos;
vector<Experiment> exps;
map<int, int> vid_to_eid;
map<int, int> vid_to_pos;
map<pair<int, int>, int> exp_loc_cnt;

//real analyze
int exp_year_count[3000];

void init_info()
{

    eid_to_pos.clear();
    exps.clear();
    vid_to_eid.clear();
    vid_to_pos.clear();
    exp_loc_cnt.clear();
    memset(exp_year_count, 0, sizeof(exp_year_count));

    year_suc[2001]=39;year_tot[2001]=900;year_ratio[2001]=0.0433333;
    year_suc[2002]=190;year_tot[2002]=3384;year_ratio[2002]=0.0561466;
    year_suc[2003]=148;year_tot[2003]=4788;year_ratio[2003]=0.0309106;
    year_suc[2004]=120;year_tot[2004]=5256;year_ratio[2004]=0.0228311;
    year_suc[2005]=158;year_tot[2005]=17640;year_ratio[2005]=0.00895692;
    year_suc[2006]=181;year_tot[2006]=11196;year_ratio[2006]=0.0161665;
    year_suc[2007]=276;year_tot[2007]=22896;year_ratio[2007]=0.0120545;
    year_suc[2008]=165;year_tot[2008]=22320;year_ratio[2008]=0.00739247;

    trialcnt_suc[1]=40;trialcnt_tot[1]=4428;trialcnt_ratio[1]=0.00903342;
    trialcnt_suc[2]=45;trialcnt_tot[2]=6732;trialcnt_ratio[2]=0.00668449;
    trialcnt_suc[3]=65;trialcnt_tot[3]=3744;trialcnt_ratio[3]=0.0173611;
    trialcnt_suc[4]=156;trialcnt_tot[4]=8568;trialcnt_ratio[4]=0.0182073;
    trialcnt_suc[5]=144;trialcnt_tot[5]=8532;trialcnt_ratio[5]=0.0168776;
    trialcnt_suc[6]=123;trialcnt_tot[6]=9468;trialcnt_ratio[6]=0.0129911;
    trialcnt_suc[7]=133;trialcnt_tot[7]=8460;trialcnt_ratio[7]=0.015721;
    trialcnt_suc[8]=179;trialcnt_tot[8]=11844;trialcnt_ratio[8]=0.0151131;
    trialcnt_suc[9]=128;trialcnt_tot[9]=7776;trialcnt_ratio[9]=0.0164609;
    trialcnt_suc[10]=150;trialcnt_tot[10]=10800;trialcnt_ratio[10]=0.0138889;
    trialcnt_suc[11]=44;trialcnt_tot[11]=2772;trialcnt_ratio[11]=0.015873;
    trialcnt_suc[12]=54;trialcnt_tot[12]=4248;trialcnt_ratio[12]=0.0127119;
    trialcnt_suc[13]=5;trialcnt_tot[13]=144;trialcnt_ratio[13]=0.0347222;
    trialcnt_suc[14]=4;trialcnt_tot[14]=252;trialcnt_ratio[14]=0.015873;
    trialcnt_suc[15]=0;trialcnt_tot[15]=144;trialcnt_ratio[15]=0;
    trialcnt_suc[16]=4;trialcnt_tot[16]=180;trialcnt_ratio[16]=0.0222222;
    trialcnt_suc[17]=0;trialcnt_tot[17]=36;trialcnt_ratio[17]=0;
    trialcnt_suc[18]=0;trialcnt_tot[18]=108;trialcnt_ratio[18]=0;
    trialcnt_suc[19]=1;trialcnt_tot[19]=36;trialcnt_ratio[19]=0.0277778;
    trialcnt_suc[25]=2;trialcnt_tot[25]=36;trialcnt_ratio[25]=0.0555556;
    trialcnt_suc[28]=0;trialcnt_tot[28]=36;trialcnt_ratio[28]=0;
    trialcnt_suc[29]=0;trialcnt_tot[29]=36;trialcnt_ratio[29]=0;

    cnt_sta_suc[36]=1277;cnt_sta_tot[36]=77369;cnt_sta_ratio[36]=0.0165053;

    for (int i=0;i<50;++i)
        if (trialcnt_tot[i]<200) trialcnt_ratio[i]=0;
}

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
                else if (year!=2005 && year!=2004) estimate*=0.80;
            }
            //ensure top ones don't contain vars from unstable(too small) exps.
            if (tct==1) estimate*=0.7;
            if (tct==2) estimate*=0.7;
            if (tct>=7 && tct<=9) estimate*=1.03;
            estimate*=(1+trialcnt_ratio[tct]);
            
            if (exper.vars.size()==40) estimate*=0.7;
            if (exper.vars.size()==36 && exper.check_count==4) estimate*=1.1;
            if (exper.vars.size()==36 && exper.check_count==5
                //&& var.type!="conv"
                ) estimate*=1.15;
            if (exper.vars.size()==36 && exper.check_count>=6 && exper.check_count<=11) estimate*=1.1;
                                    
            estimate*=(1+5*pow(year_ratio[year],0.3));

            estimate *= 0.0 + (50-var.rank_in_exp)/200.0;
            
            //if ((year==2002 || year==2003) && var.type=="RR1") estimate/=1.10;
        }
    }
    return estimate;
}


void real_analyze(string filename)
{
    string afilename = "ana.txt";
    ofstream out(afilename.c_str());
    out<<"Exp count:"<<exps.size()<<endl;
    for (unsigned int i=0;i<exps.size();++i)
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
    for (unsigned int i=0;i<exps.size();++i)
    {
        tot_vars+=exps[i].vars.size();
        for (unsigned int j=0;j<exps[i].vars.size();++j)
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
    for (unsigned int i=0;i<exps.size();++i)
    {
        int var_cnt=exps[i].vars.size();
        for (unsigned int t=0;t<exps[i].trials.size();++t)
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

    map<int, pair<int, int> > pdcr_cnt;
    map<int, pair<int, int> > pbcr_cnt;
    map<int, pair<int, int> > flcr_cnt;
    map<int, pair<int, int> > emrgr_cnt;
    map<int, pair<int, int> > hldgr_cnt;
    map<int, pair<int, int> > plhtn_cnt;
    for (unsigned int i=0;i<exps.size();++i)
    {
        int var_cnt=exps[i].vars.size();
        for (unsigned int t=0;t<exps[i].trials.size();++t)
        {
            for (int j=0;j<var_cnt;++j)
            {
                if (exps[i].vars[j].ischeck) continue;
                int p=vid_to_pos[exps[i].vars[j].vid];
                pdcr_cnt[exps[i].trials[t].pdcrs[p]].second++;
                pbcr_cnt[exps[i].trials[t].pbcrs[p]].second++;
                flcr_cnt[exps[i].trials[t].flcrs[p]].second++;
                emrgr_cnt[exps[i].trials[t].emrgrs[p]].second++;
                hldgr_cnt[exps[i].trials[t].hldgrs[p]].second++;
                plhtn_cnt[exps[i].trials[t].plhtns[p]/10].second++;
                if(exps[i].vars[j].iselite) {
                    pdcr_cnt[exps[i].trials[t].pdcrs[p]].first++;
                    pbcr_cnt[exps[i].trials[t].pbcrs[p]].first++;
                    flcr_cnt[exps[i].trials[t].flcrs[p]].first++;
                    emrgr_cnt[exps[i].trials[t].emrgrs[p]].first++;
                    hldgr_cnt[exps[i].trials[t].hldgrs[p]].first++;
                    plhtn_cnt[exps[i].trials[t].plhtns[p]/10].first++;
                }
            }
        }
    }
    for(map<int,pair<int,int> >::iterator it=pdcr_cnt.begin();it!=pdcr_cnt.end();++it)
    {
        out<<"pdcr_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"pdcr_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"pdcr_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=pbcr_cnt.begin();it!=pbcr_cnt.end();++it)
    {
        out<<"pbcr_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"pbcr_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"pbcr_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=flcr_cnt.begin();it!=flcr_cnt.end();++it)
    {
        out<<"flcr_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"flcr_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"flcr_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=emrgr_cnt.begin();it!=emrgr_cnt.end();++it)
    {
        out<<"emrgr_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"emrgr_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"emrgr_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=hldgr_cnt.begin();it!=hldgr_cnt.end();++it)
    {
        out<<"hldgr_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"hldgr_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"hldgr_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;
    for(map<int,pair<int,int> >::iterator it=plhtn_cnt.begin();it!=plhtn_cnt.end();++it)
    {
        out<<"plhtn_suc["<<it->first<<"]="<<it->second.first<<";";
        out<<"plhtn_tot["<<it->first<<"]="<<it->second.second<<";";
        out<<"plntn_ratio["<<it->first<<"]="<<it->second.first*1.0/it->second.second<<";";
        out<<endl;
    }
    out<<"----------"<<endl;

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
    for (unsigned int i=0;i<exps.size();++i)
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
    for (unsigned int i=0;i<exps.size();++i)
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
        int loccd;
        int rep;
        int variety_id;
        int year;
        string type;
        double yield;
        int mn;
        double rm;
        int pdcr;
        int pbcr;
        int flcr;
        int emrgr;
        int plhtn;
        int hldgr;
        int ischeck;
        int iselite;
        string str;
        for (unsigned int i=0;i<data.size();++i)
        {
            for (unsigned int p=0;p<data[i].size();++p)
                if(data[i][p]==',') data[i][p]=' ';
            stringstream se(data[i]);
            se>>experiment_id>>loccd>>rep>>variety_id;
            se>>str;
            string yearstr = str.substr(0, 4);
            year = strtoint(yearstr);
            se>>type;
            se>>str;
            if(str=="NULL") yield=-1; else yield=strtodouble(str);
            se>>str;
            if(str=="NULL") mn=-1; else mn=strtoint(str);
            se>>str;
            if(str=="NULL") rm=-1; else rm=strtodouble(str);
            se>>str;
            if(str=="NULL") pdcr=0; else pdcr=strtoint(str);
            se>>str;
            if(str=="NULL") pbcr=0; else pbcr=strtoint(str);
            se>>str;
            if(str=="NULL") flcr=0; else flcr=strtoint(str);
            se>>str;
            if(str=="NULL") emrgr=0; else emrgr=strtoint(str);
            se>>str;
            if(str=="NULL") plhtn=0; else plhtn=strtoint(str);
            se>>str;
            if(str=="NULL") hldgr=0; else hldgr=strtoint(str);
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
            trial.pdcrs[pos]=pdcr;
            trial.pbcrs[pos]=pbcr;
            trial.flcrs[pos]=flcr;
            trial.emrgrs[pos]=emrgr;
            trial.plhtns[pos]=plhtn;
            trial.hldgrs[pos]=hldgr;
        }
        for (unsigned int i=0;i<exps.size();++i)
        {
            set<int> loccds;
            for (unsigned int j=0;j<exps[i].trials.size();++j)
            {    
                loccds.insert(exps[i].trials[j].loccd);
                exp_loc_cnt[make_pair(exps[i].id,exps[i].trials[j].loccd)]++;
            }
            exps[i].loccds_cnt=loccds.size();
        }
        for (unsigned int i=0;i<exps.size();++i)
        {
            for (unsigned int j=0;j<exps[i].trials.size();++j)
            {
                exps[i].trials[j].rep_tot=exp_loc_cnt[make_pair(exps[i].id,exps[i].trials[j].loccd)];
            }
        }
        for (unsigned int i=0;i<exps.size();++i)
        {
            exps[i].elite_count=0;
            exps[i].check_count=0;
            exps[i].avg_rm=0;
            int valid_rms=0;
            for (unsigned int j=0;j<exps[i].vars.size();++j)
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
    int year;
    int band;
    string sub_band;
    int zone;
    for (unsigned int i=0;i<locations.size();++i)
    {
        string& str=locations[i];
        for (unsigned int p=0;p<str.size();++p)
            if(str[p]==',') str[p]=' ';
        stringstream se(str);
        se>>loccd>>year>>band>>zone>>sub_band;
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
        for (unsigned int i=0;i<exps.size();++i)
        {
            for (unsigned int j=0;j<exps[i].trials.size();++j)
            {
                for (unsigned int k=0;k<exps[i].vars.size();++k)
                {
                    if (exps[i].vars[k].ischeck) continue;
                    int p1=vid_to_pos[exps[i].vars[k].vid];
                    if (exps[i].trials[j].yields[p1]<0) continue;
                    bool mn_available=(exps[i].trials[j].mns[p1]>0);
                    exps[i].trials[j].mn_ava=mn_available;
                    double s1=0;
                    double s2=0;
                    for (unsigned int m=0;m<exps[i].vars.size();++m)
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
                    bool loccdEmp = false;
                    if (location_info.count(exps[i].trials[j].loccd)==0)
                    {
                        rwt*=1.0;
                        cout<<"loccd not found"<<endl;
                        loccdEmp = true;
                    }
                    else
                    {
                        //double band=location_info[exps[i].trials[j].loccd].first;
                        //int zone=location_info[exps[i].trials[j].loccd].second;
                        //if (zone==1) rwt*=1;
                        //if (zone==2) rwt*=1;
                        //if (zone==3) rwt*=1;
                        //if (zone==4) rwt*=0.5;
                        //if (zone==5) rwt*=1;
                    }
                    //if (!mn_available) rwt=0.95;
                    rwt/=(15+exps[i].trials[j].rep_tot);
                    double pm=1.3;
                    //exps[i].vars[k].wins_cnt+=rwt*pow(s1,pm);//pow possible??
                    if (loccdEmp)
                        exps[i].vars[k].wins_cnt+=rwt*pow(s1,pm)*0.1;//pow possible??
                    else
                        exps[i].vars[k].wins_cnt+=rwt*pow(s1,pm);//pow possible??
                    exps[i].vars[k].tot_cnt+=rwt*pow(s2,pm);
                    exps[i].vars[k].mins=min(exps[i].vars[k].mins,pm);
                    exps[i].vars[k].square_sum+=pow(s1/s2,pm);
                }
            }
        }

        // set rank_in_exp
        for (unsigned int i=0;i<exps.size();++i)
        {
            vector<pair<double, int> > vp;
            for (unsigned int k=0;k<exps[i].vars.size();++k)
            {
                double score;
                if (exps[i].vars[k].ischeck) score = 0.0;
                else if (exps[i].vars[k].tot_cnt<eps) score = 0.0;
                else score = exps[i].vars[k].wins_cnt/exps[i].vars[k].tot_cnt;
                vp.push_back(make_pair(score, k));
            }
            sort(vp.begin(), vp.end());
            for (unsigned int k=0; k<vp.size(); k++)
                exps[i].vars[vp[k].second].rank_in_exp = vp.size()-1-k;
        }

        vector<pair<double,int> > svid;
        for (unsigned int i=0;i<exps.size();++i)
            for (unsigned int j=0;j<exps[i].vars.size();++j)
            {
                exps[i].vars[j].estimate=overall_estimate(exps[i].vars[j]);
                svid.push_back(make_pair(-exps[i].vars[j].estimate,exps[i].vars[j].vid));
            }
        sort(svid.begin(), svid.end());
        vector<int> ret(svid.size());
        for (unsigned int i=0;i<svid.size();++i)
            ret[i]=svid[i].second;
        return ret;
    }
};

// place4
class Line {
    public:
        int expID;
        int loccd;
        int rep;
        int varID;
        int year;
        int type;     // NULL
        float yield;  // NULL
        int mn;       // NULL
        float rm;     // NULL
        int pd_cr;
        int pb_cr;
        int fl_cr;
        int emrgr;
        int plhtn;
        int hldgr;
        int isCheck;
        int isElite;

        Line(const char *str) {
            if (str == NULL) {
                expID = year = loccd = rep -1;
                return;
            }
            const char *p = str;
            sscanf(p, "%d,%d,%d,%d", &expID, &loccd, &rep, &varID);
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;

            sscanf(p, "%d", &year);
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

            if (*p == 'N') {
                pd_cr = 0;
            } else {
                sscanf(p, "%d", &pd_cr);
            }
            p = strchr(p, ',')+1;

            if (*p == 'N') {
                pb_cr = 0;
            } else {
                sscanf(p, "%d", &pb_cr);
            }

            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
            p = strchr(p, ',')+1;
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
            m_mnAve = 150;
            m_yieldPerMN = 0.25;
            m_emptyLocScale = 0.95;
            m_trialScale = 3.0;

            setParas(0);
        }

        void setParas(int idx)
        {
            float yearscales[4][9] = {
                {1.199,1.236,1.213,1.192,1.109,1.118,1.115,1.135,1.119,},
                {1.271,1.200,1.211,1.182,1.104,1.106,1.101,1.112,1.101,},
                {1.149,1.145,1.178,1.154,1.093,1.088,1.073,1.097,1.067,},
                {1.114,1.195,1.191,1.165,1.099,1.099,1.090,1.098,1.076,},
            };
            float typescales[4][3] = {
                {0.987,1.030,0.945,},
                {1.071,1.118,0.914,},
                {1.124,1.158,1.100,},
                {1.048,1.090,1.057,},
            };
            float bandscales[4][10] = {
                {0.938,1.107,1.107,1.110,1.105,1.064,1.033,1.075,1.204,1.126,},
                {1.088,1.131,1.131,1.144,1.143,1.110,1.056,1.051,1.238,1.190,},
                {0.926,1.130,1.144,1.145,1.134,1.089,1.042,1.076,1.276,1.124,},
                {1.074,1.086,1.105,1.100,1.101,1.056,1.029,1.068,1.242,1.217,},
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
                int id, year;
                const char *p = locations[i].c_str();
                sscanf(p, "%d,%d", &id, &year);
                loccds.insert(id*10000+year);;
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
                    sort(scores.begin(), scores.end());


                    for (unsigned int i=0; i<scores.size(); i++) {
                        float score = scores[i].first;
                        int id = scores[i].second;

                        double rankscale = 1 + (((double)i)-scores.size()/2)/400.0;
                        //rankscale *= sqrt(rankscale);
                        if (rankscale < 0.8 || rankscale > 1.3) {
                            cout<<rankscale<<endl;
                            cout<<scores.size()<<endl;
                            cout<<i<<" "<<(i-scores.size())<<" "<<(i-scores.size())/2<<endl;
                        }
                        score *= rankscale;

                        // signal: whether LOCCD in locations.csv
                        //if (m_LOCCDs.find(loccd) == m_LOCCDs.end()) {
                        if (m_LOCCDs.find(loccd*10000+year) == m_LOCCDs.end()) {
                            //cout<<"emp"<<endl;
                            score *= m_emptyLocScale;
                        }

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
            for (int i=0; i<4; i++) {
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
            int expTestNum = 700;
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
            int nIter = 5;
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

vector<int> sampleExpIDs(set<int> &expIDs, int testNum)
{
    vector<int> res;
    if (testNum > (int)expIDs.size()) {
        cerr<<"sampleExpIDs() error!"<<endl;
        return res;
    }
    vector<int> ids(expIDs.begin(), expIDs.end());
    for (int i=0; i<testNum; i++) {
        int idx = random()%(ids.size() - i);
        swap(ids[i], ids[idx]);
        res.push_back(ids[i]);
    }
    return res;
}

vector<int> mergePred(vector<int> pred1, vector<int> pred2)
{
    map<int, int> id2rank;
    for (unsigned int i=0; i<pred1.size(); i++) {
        id2rank[pred1[i]] += i;
        id2rank[pred2[i]] += i;
    }

    vector<pair<int, int> > vp;
    for (map<int,int>::iterator it=id2rank.begin(); it!=id2rank.end(); it++)
        vp.push_back(make_pair(it->second, it->first));
    sort(vp.begin(), vp.end());

    vector<int> pred;
    for (unsigned int i=0; i<vp.size(); i++)
        pred.push_back(vp[i].second);
    return pred;
}

class AdvancedEliteClassifier {
    public:
        vector<int> sampleExpIDsByYear(map<int, set<int> > &testYear2ExpIDs, map<int, set<int> > &trainYear2ExpIDs)
        {
            vector<int> res;
            double maxRatio = 0.0;
            for (map<int, set<int> >::iterator it=testYear2ExpIDs.begin(); it!=testYear2ExpIDs.end(); it++) {
                int year = it->first;
                set<int> &testExpIDs = it->second;
                set<int> &trainExpIDs = trainYear2ExpIDs[year];
                double ratio = 1.0*testExpIDs.size()/trainExpIDs.size();
                maxRatio = max(ratio, maxRatio);
            }
            //maxRatio = 1.0;

            for (map<int, set<int> >::iterator it=testYear2ExpIDs.begin(); it!=testYear2ExpIDs.end(); it++) {
                int year = it->first;
                set<int> &testExpIDs = it->second;
                set<int> &trainExpIDs = trainYear2ExpIDs[year];
                int expNum = (int)(testExpIDs.size()/maxRatio);
                vector<int> expIDs = sampleExpIDs(trainExpIDs, expNum);
                res.insert(res.end(), expIDs.begin(), expIDs.end());
            }

            //cout<<"sampleExpIDsByYear() "<<res.size()<<endl;
            return res;
        }
        vector<string> getDataByExpIDs(vector<int> &expIDs, map<int, vector<int> > &trainExpID2LineNums, vector<string> &trainingData)
        {
            vector<string> data;
            for (unsigned int i=0; i<expIDs.size(); i++) {
                vector<int> &lineNums = trainExpID2LineNums[expIDs[i]];
                for (unsigned int j=0; j<lineNums.size(); j++)
                    data.push_back(trainingData[lineNums[j]]);
            }
            return data;
        }
        double getScore(vector<int> &pred, map<int, int> &elites)
        {
            double score = 0.0;
            int total = 0;
            int correct = 0;
            int totElite = 0;

            for (unsigned int i=0; i<pred.size(); i++) {
                if (elites[pred[i]])
                    totElite++;
            }
            for (unsigned int i=0; i<pred.size(); i++) {
                total++;
                if (elites[pred[i]] == 1) {
                    correct++;
                    score += (1000000.0 / totElite) * correct / total;
                }
            }
            return score;
        }

        vector <int> classify(vector<string> testData, vector<string> trainingData, vector<string> locations)
        {
            //cout<<"testData.size() "<<testData.size()<<endl;
            //cout<<"trainingData.size() "<<trainingData.size()<<endl;
            //cout<<"total.size() "<<testData.size()+trainingData.size()<<endl;
            /*
            map<int, set<int> > testYear2ExpIDs;
            for (unsigned int i=0; i<testData.size(); i++) {
                Line line(testData[i].c_str());
                testYear2ExpIDs[line.year].insert(line.expID);
            }
            for (map<int, set<int> >::iterator it=testYear2ExpIDs.begin(); it!=testYear2ExpIDs.end(); it++)
                cout<<it->first<<" "<<it->second.size()<<endl;

            map<int, set<int> > trainYear2ExpIDs;
            map<int, vector<int> > trainExpID2LineNums;
            map<int, int> elites;
            for (unsigned int i=0; i<trainingData.size(); i++) {
                Line line(trainingData[i].c_str());
                trainYear2ExpIDs[line.year].insert(line.expID);
                trainExpID2LineNums[line.expID].push_back(i);
                elites[line.varID] = line.isElite;
            }

            int testNum = 1;
            vector<double> scores1, scores4;
            cout<<"sampleData:"<<endl;
            for (int i=0; i<testNum; i++) {
                vector<int> expIDs = sampleExpIDsByYear(testYear2ExpIDs, trainYear2ExpIDs);
                vector<string> data = getDataByExpIDs(expIDs, trainExpID2LineNums, trainingData);

                EliteClassifier1 ec1;
                EliteClassifier4 ec4;

                vector<int> pred1 = ec1.classify(data, locations);
                double score1 = getScore(pred1, elites);


                vector<int> pred4 = ec4.classify(data, locations);
                //vector<int> pred4 = ec4.classify(testData, locations);
                double score4 = getScore(pred4, elites);
                cout<<"pred.size() "<<pred1.size()<<" "<<pred4.size()<<endl;

                scores1.push_back(score1);
                scores4.push_back(score4);
                cout<<score1<<" "<<score4<<endl;
            }
            cout<<"average:"<<endl;
            double score1 = accumulate(scores1.begin(), scores1.end(), 0.0)/testNum;
            double score4 = accumulate(scores4.begin(), scores4.end(), 0.0)/testNum;
            cout<<score1<<" "<<score4<<" "<<score1/score4<<endl;
            if (score1 > score4) {
                EliteClassifier1 ec1;
                vector<int> pred1 = ec1.classify(testData, locations);
                return pred1;
            } else {
                EliteClassifier4 ec4;
                vector<int> pred4 = ec4.classify(testData, locations);
                return pred4;
            }
            */

            EliteClassifier1 ec1;
            vector<int> pred1 = ec1.classify(testData, locations);
            //double score1 = ec4.getScore(pred1);

            EliteClassifier4 ec4;
            vector<int> pred4 = ec4.classify(testData, locations);
            //double score4 = ec4.getScore(pred4);

            vector<int> pred = mergePred(pred1, pred4);
            return pred;
        }

};


#ifdef LOCAL

void getData(vector<string> &data, map<int,int> &elites)
{
    data.clear();
    elites.clear();
    char aline[200];
    FILE *f = fopen("../data/DataTraining.csv", "r");

    while (fgets(aline, sizeof(aline), f)) {
        Line ln(aline);
        elites[ln.varID] = ln.isElite;

        int len = strlen(aline);
        if (aline[len-1] == '\n')
            aline[len-1] = '\0';
        //aline[strlen(aline)-3] = '\0';
        data.push_back(string(aline));
    }
    fclose(f);
}

void getLocation(vector<string> &location)
{
    location.clear();
    char aline[200];
    FILE *f = fopen("../data/Locations.csv", "r");
    while (fgets(aline, sizeof(aline), f)) {
        aline[strlen(aline)-1] = '\0';
        location.push_back(string(aline));
    }
    fclose(f);
}

void sampleTestData(vector<string> &data, map<int, int> &elites, vector<string> &testData, map<int, int> &testDataElites, vector<string> &trainingData)
{
    int testNum = 50;
    set<int> expIDs;
    for (unsigned int i=0; i<data.size(); i++) {
        Line line(data[i].c_str());
        expIDs.insert(line.expID);
    }

    vector<int> testExpIDsList = sampleExpIDs(expIDs, testNum);
    set<int> testExpIDs(testExpIDsList.begin(), testExpIDsList.end());
    for (unsigned int i=0; i<data.size(); i++) {
        Line line(data[i].c_str());
        if (testExpIDs.find(line.expID) != testExpIDs.end()) {
            testData.push_back(data[i].substr(0, data[i].length()-2));
            int varID = line.varID;
            testDataElites[varID] = elites[varID];
        } else {
            trainingData.push_back(data[i]);
        }
    }
}

vector<int> mergePred1(vector<int> pred1, vector<int> pred2)
{
    map<int, int> id2rank;
    for (unsigned int i=0; i<pred1.size(); i++) {
        id2rank[pred1[i]] += i*i;
        id2rank[pred2[i]] += i*i;
    }

    vector<pair<int, int> > vp;
    for (map<int,int>::iterator it=id2rank.begin(); it!=id2rank.end(); it++)
        vp.push_back(make_pair(it->second, it->first));
    sort(vp.begin(), vp.end());

    vector<int> pred;
    for (unsigned int i=0; i<vp.size(); i++)
        pred.push_back(vp[i].second);
    return pred;
}

vector<int> mergePred2(vector<int> pred1, vector<int> pred2)
{
    map<int, int> id2rank;
    for (unsigned int i=0; i<pred1.size(); i++) {
        id2rank[pred1[i]] += i*3;
        id2rank[pred2[i]] += i*2;
    }

    vector<pair<int, int> > vp;
    for (map<int,int>::iterator it=id2rank.begin(); it!=id2rank.end(); it++)
        vp.push_back(make_pair(it->second, it->first));
    sort(vp.begin(), vp.end());

    vector<int> pred;
    for (unsigned int i=0; i<vp.size(); i++)
        pred.push_back(vp[i].second);
    return pred;
}


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
        for (unsigned int p=0;p<str.size();++p)
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
    for (unsigned int i=0;i<guess.size();++i)
    {
        total++;
        if (std_ans[guess[i]]==1)
        {
            correct++;
            score+=(1000000.0/tot_elite)*(correct/total);
        }
        /*
        else if (i<100)
        {
            cout<<i<<": "<<guess[i]<<endl;
        }
        */
    }
    return score;
}

#if 0
int main()
{
    //AdvancedEliteClassifier classifier;
    EliteClassifier1 classifier;
    
    vector<string> data;
    read_data("../data/DataTraining.csv",data);
    vector<string> locations;
    read_location("../data/Locations.csv",locations);
    vector<int> guess=classifier.classify(data,locations);
    double score=calculate_score(guess);
    cout<<"Score on train set:"<<score<<endl;
    
    //analyze("../data/DataTraining.csv");
    return 0;
}
#else
int main(void)
{
    srandom(time(NULL));

    vector<string> data;
    map<int,int> elites;
    getData(data, elites);

    vector<string> locations;
    getLocation(locations);

    for (int i=0; i<100; i++) {
    vector<string> testData, trainingData;
    map<int, int> testDataElites;
    sampleTestData(data, elites, testData, testDataElites, trainingData);

    AdvancedEliteClassifier aec;
    vector<int> pred = aec.classify(testData, trainingData, locations);
    double scoreaec = aec.getScore(pred, testDataElites);

    EliteClassifier4 ec4;
    ec4.setElites(testDataElites);


    vector<int> pred4 = ec4.classify(testData, locations);
    double score4 = ec4.getScore(pred4);

    EliteClassifier1 ec1;

    vector<int> pred1 = ec1.classify(testData, locations);
    double score1 = ec4.getScore(pred1);

    vector<int> preda = mergePred(pred1, pred4);
    vector<int> predb = mergePred1(pred1, pred4);
    vector<int> predc = mergePred2(pred1, pred4);
    double scorea = ec4.getScore(preda);
    double scoreb = ec4.getScore(predb);
    double scorec = ec4.getScore(predc);

    cout<<"score = "<<score1<<" "<<score4<<" "<<scorea<<" "<<scoreb<<" "<<scorec<<endl;
    }

    EliteClassifier4 ec4;
    ec4.setElites(elites);
    vector<int> pred4 = ec4.classify(data, locations);
    double score4 = ec4.getScore(pred4);
    cout<<"score4 = "<<score4<<endl;

    EliteClassifier1 ec1;
    vector<int> pred1 = ec1.classify(data, locations);
    double score1 = ec4.getScore(pred1);
    cout<<"score1 = "<<score1<<endl;

    return 0;
}
#endif

#endif
