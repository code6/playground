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

class EliteClassifier {
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
