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
const float kYLSmooth = 50.0f;

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

        vids[id].sum     += vid.yield * kAvgMn/(vid.mn+kMnSmooth);
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
        }

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
    
            vid.score += (vid.score - check_avg);
            vid.score += -0.25*(vid.yield - check_yield);
            vid.score += (check_num - 2*vid.rank);
            vid.score += 6*(vid.type);
            vid.score += (vid.count > 15 ? 15 : vid.count);
        
            vid.score += -10000*(vid.check);
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

class EliteClassifier
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
            int row = atoi(col[1]);

            loc2row[loc] = row;
        }
    }


    vector<int> classify(vector<string>& data, vector<string>& loc)
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
            printf("elite_num\t%d\tvid_num\t%d\tavg_rank\t%.3f\tfinal score\t%.3f\n", elite_count, vids.size(), avg_rank, score);
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
    
    void init_param()
    {
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

