// TopCoder Marathon - soybean 6
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
string inttostr(int num)
{
    stringstream se;
    se<<num;
    return se.str();
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
    /*
    year_suc[2000]=1;year_tot[2000]=3000;year_ratio[2000]=0.000333333;
    year_suc[2001]=28;year_tot[2001]=4980;year_ratio[2001]=0.00562249;
    year_suc[2002]=104;year_tot[2002]=6952;year_ratio[2002]=0.0149597;
    year_suc[2003]=113;year_tot[2003]=10096;year_ratio[2003]=0.0111926;
    year_suc[2004]=60;year_tot[2004]=9364;year_ratio[2004]=0.00640752;
    year_suc[2005]=98;year_tot[2005]=13696;year_ratio[2005]=0.00715537;
    year_suc[2006]=104;year_tot[2006]=6336;year_ratio[2006]=0.0164141;
    year_suc[2007]=168;year_tot[2007]=15012;year_ratio[2007]=0.011191;
    year_suc[2008]=113;year_tot[2008]=15120;year_ratio[2008]=0.00747354;
    */
    year_suc[2001]=39;year_tot[2001]=900;year_ratio[2001]=0.0433333;
    year_suc[2002]=190;year_tot[2002]=3384;year_ratio[2002]=0.0561466;
    year_suc[2003]=148;year_tot[2003]=4788;year_ratio[2003]=0.0309106;
    year_suc[2004]=120;year_tot[2004]=5256;year_ratio[2004]=0.0228311;
    year_suc[2005]=158;year_tot[2005]=17640;year_ratio[2005]=0.00895692;
    year_suc[2006]=181;year_tot[2006]=11196;year_ratio[2006]=0.0161665;
    year_suc[2007]=276;year_tot[2007]=22896;year_ratio[2007]=0.0120545;
    year_suc[2008]=165;year_tot[2008]=22320;year_ratio[2008]=0.00739247;
    
    /*
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
    */
    
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
    
    /*
    cnt_sta_suc[36]=768;cnt_sta_tot[36]=49135;cnt_sta_ratio[36]=0.0156304;
    cnt_sta_suc[40]=21;cnt_sta_tot[40]=25496;cnt_sta_ratio[40]=0.000823659;
    */
    cnt_sta_suc[36]=1277;cnt_sta_tot[36]=77369;cnt_sta_ratio[36]=0.0165053;
    
    /*
    for (int i=0;i<50;++i)
        if (trialcnt_tot[i]<200) trialcnt_ratio[i]=0;
    */
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
    double wins1;
    double tot1;
    double wins2;
    double tot2;
    int cr1[11];
    int cr2[11];
    int cr3[11];
    int emrgr[11];
    int hldgr[11];
    int most_cr1;
    int most_cr2;
    int most_cr3;
    int most_emrgr;
    int most_hldgr;
    double avg_height;
    int valid_height;
    int tot_height_cnt;
    double valid_height_ratio;
    Variety()
    {
        wins_cnt=0;
        tot_cnt=0;
        estimate=0;
        square_sum=0;
        wins1=tot1=wins2=tot2=0;
        mins=10000;
        memset(cr1,0,sizeof(cr1));
        memset(cr2,0,sizeof(cr2));
        memset(cr3,0,sizeof(cr3));
        memset(emrgr,0,sizeof(emrgr));
        memset(hldgr,0,sizeof(hldgr));
        avg_height=0;
        valid_height=tot_height_cnt=0;
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

int gettypeindex(string& type)
{
    if (type=="NULL") return 0;
    if (type=="RR2Y") return 1;
    if (type=="conv") return 2;
    return 3; // RR1
}

             
           
            
           

struct TreeNode
{
    vector<int> hold_id;
    int left; //right=left+1
    int split_index; //leaf -> -1
    double split_value; //leaf -> prediction
    int level;
};

int genrand()
{
    long long a1=rand();
    a1*=(rand()%10000);
    return (a1+rand())%(1<<30);
}

#define max_level 15
struct BinaryTree
{
    double mylog2(double v)
    {
        if (v<1e-10)
            return 0;
        return log2(v);
    }
    double cal_ent(int left0,int left1,int right0,int right1)
    {
        double leftn=left0+left1; // !=0
        double rightn=right0+right1; // !=0
        double v=-left0*mylog2(left0/leftn)
                 -left1*mylog2(left1/leftn)
                 -right0*mylog2(right0/rightn)
                 -right1*mylog2(right1/rightn);
        return v;
    }
    vector<TreeNode> nds;
    
    double make_decision(const vector<double>& properties)
    {
        int cur_node=0;
        while(nds[cur_node].split_index>=0)
        {
            double v0=nds[cur_node].split_value;
            double v1=properties[nds[cur_node].split_index];
            if (v1<v0) cur_node=nds[cur_node].left;
            else cur_node=nds[cur_node].left+1;
        }
        return nds[cur_node].split_value;
    }
    double get_prd(const vector<int>& fact,const vector<int>& hold_id)
    {
        double sum=0;
        for (int i=0;i<hold_id.size();++i)
            sum+=fact[hold_id[i]];
        return sum/hold_id.size();
    }
    void construct_tree(const vector<int>& fact,const vector<vector<double> > properties)
    {
        int todeal=0;
        nds.reserve(1<<max_level);
        nds.push_back(TreeNode());
        int row_size=fact.size();
        int col_size=properties[0].size();
        int sel_size=4;
        TreeNode& root=nds[0];
        for (int i=0;i<row_size;++i)
        {
            int ns=i;//genrand()%row_size;
            root.hold_id.push_back(ns);
        }
        root.level=1;
        while(todeal<nds.size())
        {
            vector<int> chs_from;
            TreeNode& node=nds[todeal];
            bool leaf=false;
            if (node.hold_id.size()<15 || node.level==max_level)
                leaf=true;
            else
            {
                //set<int> sets;
                for (int i=0;i<sel_size;++i)
                {
                    int ns=genrand()%col_size;
                    /*
                    while(sets.count(ns)!=0)
                        ns=genrand()%col_size;
                    sets.insert(ns);
                    */
                    chs_from.push_back(ns);
                }
                double min_entropy=1e+100;
                int min_id=-1;
                double min_sp_value=-1;
                int cnt0=0;
                for (int i=0;i<node.hold_id.size();++i)
                    if (fact[node.hold_id[i]]==0)
                        cnt0++;
                if (cnt0==0 || cnt0==node.hold_id.size())
                    leaf=true;
                else
                {
                    for (int i=0;i<chs_from.size();++i)
                    {
                        vector<pair<double,int> > sortlist;
                        int pro_id=chs_from[i];
                        for (int j=0;j<node.hold_id.size();++j)
                            sortlist.push_back(make_pair(properties[node.hold_id[j]][pro_id],fact[node.hold_id[j]]));
                        sort(sortlist.begin(),sortlist.end());
                        int left0=0;
                        int left1=0;
                        int right0=cnt0;
                        int right1=node.hold_id.size()-cnt0;
                        for (int j=0;j+1<sortlist.size();++j)
                        {
                            int v1=sortlist[j].second;
                            int v2=sortlist[j+1].second;
                            if (v1==0)
                            {
                                left0++;
                                right0--;
                            }
                            else
                            {
                                left1++;
                                right1--;
                            }
                            if (v1==v2) continue;
                            if (sortlist[j].first==sortlist[j+1].first) continue;
                            
                            double ent=cal_ent(left0,left1,right0,right1);
                            if (ent<min_entropy)
                            {
                                //cerr<<sortlist[j].first<<" "<<sortlist[j+1].first<<" "<<min_entropy<<endl;
                                //cerr<<left0<<" "<<left1<<" "<<right0<<" "<<right1<<endl;
                                min_sp_value=(sortlist[j].first+sortlist[j+1].first)*0.5;
                                min_entropy=ent;
                                min_id=pro_id;
                            }
                        }
                    }
                }
                if (min_entropy<1e+80)
                {
                    node.split_index=min_id;
                    node.split_value=min_sp_value;
                    node.left=nds.size();
                    TreeNode tleft,tright;
                    nds.push_back(tleft);
                    nds.push_back(tright);
                    nds[node.left].level=nds[node.left+1].level=node.level+1;
                    for (int i=0;i<node.hold_id.size();++i)
                        if (properties[node.hold_id[i]][node.split_index]<node.split_value)
                            nds[node.left].hold_id.push_back(node.hold_id[i]);
                        else
                            nds[node.left+1].hold_id.push_back(node.hold_id[i]);
                }
                else
                    leaf=true;
            }
            if (leaf)
            {
                node.split_index=-1;
                node.split_value=get_prd(fact,node.hold_id);
            }
            ++todeal;
        }
        //clear data
        for (int i=0;i<nds.size();++i)
        {
            vector<int> newv;
            nds[i].hold_id.swap(newv);
        }
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
//trees
#define TREES_COUNT 100
BinaryTree trees[TREES_COUNT+1];
void construct_trees(const vector<int>& fact,const vector<vector<double> > properties)
{
    for (int i=0;i<TREES_COUNT;++i)
    {
        trees[i].nds.clear();
        trees[i].construct_tree(fact,properties);
        cerr<<"Tree "<<i<<":"<<trees[i].nds.size()<<endl;
    }
}

double overall_estimate(Variety& var)
{
    double estimate=0;
    if (var.ischeck) estimate-=(1e+10);//elite is not check
    if (var.tot_cnt<eps) estimate-=(1e+9);//no compare at all,quite bad
    else
    {
        estimate+=var.wins_cnt/var.tot_cnt*(1e+7);
        if (var.type=="RR2Y"||var.type=="NULL") estimate-=(1e+9);
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
                else if (year!=2005 && year!=2004) estimate*=0.85;
            }
            //ensure top ones don't contain vars from unstable(too small) exps.
            if (tct==1) estimate*=0.7;
            if (tct==2) estimate*=0.7;
            //if (tct>=7 && tct<=9) estimate*=1.03;
            estimate*=(1+trialcnt_ratio[tct]);
            
            /*
            double ex2=var.square_sum/tct;
            double ex_2=(var.wins_cnt*var.wins_cnt/var.tot_cnt/var.tot_cnt);
            double dx=ex2-ex_2;
            if (dx>0.05) estimate*=(1-0.1*dx);
            */
                        
            if (exper.vars.size()==40)
                estimate*=0.7;
            /*
            if (exper.vars.size()==36 && exper.check_count==4) estimate*=1.1;
            if (exper.vars.size()==36 && exper.check_count==5) estimate*=1.15;
            if (exper.vars.size()==36 && exper.check_count>=6 && exper.check_count<=11) estimate*=1.1;
            */                      
            
            estimate*=(1+5*pow(year_ratio[year],0.3));
            
            if ((year==2002 || year==2001) && var.type=="RR1") estimate*=1.05;
            
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

void bound(int& num,int left,int right)
{
    if (num<left) num=left;
    if (num>right) num=right;
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
        string plant_date;
        int pd_cr;
        int pb_cr;
        int fl_cr;
        int emrgr;
        int plhtn;
        int hldgr;
        for (int i=0;i<data.size();++i)
        {
            for (int p=0;p<data[i].size();++p)
                if(data[i][p]==',') data[i][p]=' ';
            stringstream se(data[i]);
            se>>experiment_id>>loccd>>rep>>variety_id;
            
            se>>plant_date;
            for (int j=0;j<plant_date.size();++j)
                if(plant_date[j]=='-') plant_date[j]=' ';
            stringstream sp(plant_date);
            sp>>year;
            bound(year,2001,2008);
            
            se>>type;
            se>>str;
            if(str=="NULL") yield=-1; else yield=strtodouble(str);
            se>>str;
            if(str=="NULL") mn=-1; else mn=strtoint(str);
            se>>str;
            if(str=="NULL") rm=-1; else rm=strtodouble(str);
            
            se>>str;
            if(str=="NULL") pd_cr=-1; else pd_cr=strtoint(str);
            se>>str;
            if(str=="NULL") pb_cr=-1; else pb_cr=strtoint(str);
            se>>str;
            if(str=="NULL") fl_cr=-1; else fl_cr=strtoint(str);
            se>>str;
            if(str=="NULL") emrgr=-1; else emrgr=strtoint(str);
            se>>str;
            if(str=="NULL") plhtn=-1; else plhtn=strtoint(str);
            se>>str;
            if(str=="NULL") hldgr=-1; else hldgr=strtoint(str);
            bound(pd_cr,-1,9);
            bound(pb_cr,-1,9);
            bound(fl_cr,-1,9);
            bound(emrgr,-1,9);
            bound(hldgr,-1,9);
                    
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
            
            Variety& var=ex.vars[vid_to_pos[variety_id]];
            var.cr1[pd_cr+1]++;
            var.cr2[pb_cr+1]++;
            var.cr3[fl_cr+1]++;
            var.emrgr[emrgr+1]++;
            var.hldgr[hldgr+1]++;
            var.tot_height_cnt++;
            if (plhtn>=0)
            {
                var.avg_height+=plhtn;
                var.valid_height++;
            }
            
            
            
            int pos=vid_to_pos[variety_id];
            trial.yields[pos]=yield;
            trial.mns[pos]=mn;
        }
        for (int i=0;i<exps.size();++i)
        {
            Experiment& ex=exps[i];
            for (int j=0;j<ex.vars.size();++j)
            {
                Variety& var=ex.vars[j];
                var.most_cr1=0;
                for (int m=1;m<=9;++m)
                    if (var.cr1[m]>var.cr1[var.most_cr1])
                        var.most_cr1=m;
                var.most_cr2=0;
                for (int m=1;m<=9;++m)
                    if (var.cr2[m]>var.cr2[var.most_cr2])
                        var.most_cr2=m;
                var.most_cr3=0;
                for (int m=1;m<=9;++m)
                    if (var.cr3[m]>var.cr3[var.most_cr3])
                        var.most_cr3=m;
                var.most_emrgr=0;
                for (int m=1;m<=9;++m)
                    if (var.emrgr[m]>var.emrgr[var.most_emrgr])
                        var.most_emrgr=m;
                var.most_hldgr=0;
                for (int m=1;m<=9;++m)
                    if (var.hldgr[m]>var.hldgr[var.most_hldgr])
                        var.most_hldgr=m;
                var.valid_height_ratio=1.0*var.valid_height/var.tot_height_cnt;
                if (var.valid_height!=0)
                    var.avg_height/=var.valid_height;
            }
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
            if (valid_rms!=0)
                exps[i].avg_rm/=valid_rms;
        }
}

map<int, pair<double, int> > location_info;

//This is obsolete and useless.
void construct_location_data(vector<string>& locations)
{
    int loccd;
    int year;
    string zone;
    int band;
    string sub_zone;
    for (int i=0;i<locations.size();++i)
    {
        string& str=locations[i];
        for (int p=0;p<str.size();++p)
            if(str[p]==',') str[p]=' ';
        stringstream se(str);
        se>>loccd>>year>>zone>>band>>sub_zone;
        int zone_num=strtoint(zone);
        if (zone=="00") zone_num=-1;
        if (zone=="000") zone_num=-2;
        //one loccd many have several records....
        //if(sub_band=="Early" band_number+=0.33;
        //else if(sub_band=="Mid" band_number+=0.66;
        //else if(sub_band=="Late" band_number+=0.99;
        location_info[loccd]=make_pair(zone_num,band);
    }
}

void clear_data()
{
    location_info.clear();
    eid_to_pos.clear();
    exps.clear();
    vid_to_eid.clear();
    vid_to_pos.clear();
    exp_loc_cnt.clear();
}

struct     AdvancedEliteClassifier
{
    void gen_pro_fact(vector<string>& data,vector<string>& locations,vector<vector<double> >& pros,vector<int>& fact,vector<int>& vids,vector<int>& checks)
    {
        clear_data();
        init_info();
        construct_datastructure(data,true);
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
                    double s11=0;
                    double s12=0;
                    double s21=0;
                    double s22=0;
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
                        if (ind!=0)
                            s12++;
                        else
                            s22++;
                        double wts=1;
                        if (ind!=0) wts=5;
                        s2+=wts;
                        if (evalue1-eps>evalue2)
                        {
                            s1+=wts;
                            if (ind!=0) s11++;
                            else s21++;
                        }
                        else if (evalue1+eps>evalue2)
                        {
                            double cpt=1.0/3.0;
                            s1+=cpt*wts;
                            if (ind!=0) s11+=cpt;
                            else s21+=cpt;
                        }
                            
                    }
                    double rwt=1;
                    //if (!mn_available) rwt=0.95;
                    rwt/=(15+exps[i].trials[j].rep_tot);
                    double pm=1.3;
                    exps[i].vars[k].wins_cnt+=rwt*pow(s1,pm);
                    exps[i].vars[k].tot_cnt+=rwt*pow(s2,pm);
                    exps[i].vars[k].mins=min(exps[i].vars[k].mins,pm);
                    exps[i].vars[k].square_sum+=pow(s1/s2,pm);
                    exps[i].vars[k].wins1=s11;
                    exps[i].vars[k].tot1=s12;
                    exps[i].vars[k].wins2=s21;
                    exps[i].vars[k].tot2=s22;
                }
            }
        }
        pros.clear();
        fact.clear();
        vids.clear();
        checks.clear();
        pros.reserve(500000);
        fact.reserve(500000);
        vids.reserve(500000);
        vector<double> ischeck;
        for (int i=0;i<exps.size();++i)
        {
            Experiment& exp=exps[i];
            for (int j=0;j<exp.vars.size();++j)
            {
                Variety& var=exp.vars[j];
                if (var.ischeck)
                {
                    checks.push_back(var.vid);
                    continue;
                }
                vids.push_back(var.vid);
                vector<double> tpo;
                
                tpo.push_back(var.rm);
                tpo.push_back(var.tot_cnt);
                
                if (var.tot_cnt>1e-5)
                    tpo.push_back(var.wins_cnt/var.tot_cnt);
                else
                    tpo.push_back(-1);
                
                
                
                tpo.push_back(var.most_cr1);
                tpo.push_back(var.most_cr2);
                tpo.push_back(var.most_cr3);
                tpo.push_back(var.most_emrgr);
                tpo.push_back(var.most_hldgr);
                
                tpo.push_back(var.valid_height_ratio);
                tpo.push_back(var.avg_height);
                
                tpo.push_back(exp.trials.size());
                tpo.push_back(gettypeindex(var.type));
                int tct=exp.trials.size();
                double mna_cnt=0;
                for (int i=0;i<tct;++i)
                    if (exp.trials[i].mn_ava) mna_cnt++;
                double mna_ratio=mna_cnt/tct;
                tpo.push_back(mna_ratio);
                int year=exp.year;
                tpo.push_back((year<=2001)?1:0);
                tpo.push_back((year==2004 || year==2005)?1:0);
                tpo.push_back(year);
                tct=min(tct,45);
                tpo.push_back(trialcnt_ratio[tct]);
                tpo.push_back(tct);
                
                //exp.vars.size() always 36?
                tpo.push_back(year_ratio[year]);
                
                pros.push_back(tpo);
                fact.push_back(var.iselite);
            }
        }
    }
    vector<int> classify(vector<string>& testdata,vector<string>& trainingdata,vector<string>& locations)
    {
        vector<vector<double> > train_pros;
        vector<int> train_fact;
        vector<int> train_vids;
        vector<int> train_checks;
        gen_pro_fact(trainingdata,locations,train_pros,train_fact,train_vids,train_checks);
        construct_trees(train_fact,train_pros);
        
        vector<vector<double> > test_pros;
        vector<int> test_fact;
        vector<int> test_vids;
        vector<int> test_checks;
        gen_pro_fact(testdata,locations,test_pros,test_fact,test_vids,test_checks);
        int ncheck_size=test_pros.size();
        vector<pair<double,int> > tcs;
        for (int i=0;i<ncheck_size;++i)
        {
            double avg_s=0;
            for (int j=0;j<TREES_COUNT;++j)
                avg_s+=trees[j].make_decision(test_pros[i]);
            avg_s/=TREES_COUNT;
            tcs.push_back(make_pair(-avg_s,test_vids[i]));
        }
        for (int i=0;i<test_checks.size();++i)
            tcs.push_back(make_pair(1e+10,test_checks[i]));
        sort(tcs.begin(),tcs.end());
        vector<int> ret;
        for (int i=0;i<tcs.size();++i)
            ret.push_back(tcs[i].second);
        return ret;
    }
};
