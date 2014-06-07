#include <algorithm>
#include <cmath>
#include <ctime>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#define DATA_NOT_AVAILABLE    -1

enum MaturitySubZone
{
    Early,
    Mid,
    Late
};

enum VarietyType
{
    Unknown,
    Conventional,
    RoundupReady,
    RoundupReadyToYield
};

struct VarietyStats
{
    double averageYield;
    double averageYieldFixed;
    double maxYield;
    double maxYieldFixed;
    double yieldDeviation;

    int maturityCount;
    double averageMaturity;
    double earliestMaturity;
    double maturityDeviation;

    map<int, int> podColorsCount;
    map<int, int> pubescenceColorsCount;
    map<int, int> flowerColorsCount;
    map<int, int> emergencesCount;
    map<int, int> plantHeightsCount;
    map<int, int> harvestLodgingsCount;

    double score;
};

struct Trail
{
    string loccd;
    int rep;
    double yield;
    double yieldFixed;
    double maturityNumber;
    int podColor;
    int pubescenceColor;
    int flowerColor;
    int emergence;
    int plantHeight;
    int harvestLodging;
};

struct Variety
{
    int varietyId;
    VarietyType type;
    double relativeMaturity;
    int isCheck;
    int isElite;
    vector<Trail> trails;
    VarietyStats stats;
};

struct Experiment
{
    int experimentId;
    int year;
    map<int, Variety> varieties;
};

struct PhysicalLocation
{
    string loccd;
    int year;
    int zone;
    int band;
    MaturitySubZone subZone;
};

struct AttributeStat
{
    int total;
    int elite;
};

class AdvancedEliteClassifier
{
public:
    vector<int> classify(vector<string> testData,
        vector<string> trainingData, vector<string> locations);

private:
    void loadRealExperiments(vector<string>& testData);
    void classifyMethod();

    void reset();
    void train(vector<string>& trainingData, vector<string>& locations);
    void buildVarietyStats(Variety& v);

    static int cmpByScore(const pair<int, double>& x, const pair<int, double>& y);
    int convertStringAsInt(string data);
    int convertNullableStringAsInt(string data);
    int getPrimaryIntFromMap(map<int, int>& m);
    bool findIntInMap(map<int, int>& m, int n);
    bool locationDataExists(string loccd, int year);

    // data containers
    vector<int> classified;
    map<int, Experiment> experiments;
    map<int, Experiment> realExperiments;
    map<string, map<int, PhysicalLocation> > physicalLocations;

    // stats
    int totalNonCheckTrials;
    int totalVarieties;
    int checkVarieties;
    int eliteVarieties;

    map<int, AttributeStat> years;
    map<VarietyType, AttributeStat> types;
    map<int, AttributeStat> trailCounts;
    map<int, AttributeStat> maturityZones;
    map<int, AttributeStat> maturityBands;
    map<int, AttributeStat> podColors;
    map<int, AttributeStat> pubescenceColors;
    map<int, AttributeStat> flowerColors;
    map<int, AttributeStat> emergences;
    map<int, AttributeStat> plantHeights;
    map<int, AttributeStat> harvestLodgings;

    double minEliteYield;
    double maxEliteYield;
    double minEliteYieldFixed;
    double maxEliteYieldFixed;
    double earliestEliteMaturity;
    double latestEliteMaturity;

    double totalYield;
    double totalYieldFixed;
    int totalMaturityCount;
    double totalMaturity;
    double averageYield;
    double averageYieldFixed;
    double averageMaturity;
};


vector<int> AdvancedEliteClassifier::classify(vector<string> testData,
    vector<string> trainingData, vector<string> locations)
{
    reset();
    train(trainingData, locations);

    time_t startTime = time(NULL);

    cout << "Constructing the varieties in the test data..." << endl;
    loadRealExperiments(testData);
    cout << "Test data parsing completed." << endl;

    cout << "Analyzing and classifying the varieties..." << endl;
    classifyMethod();

    time_t timeSpan = time(NULL) - startTime;
    cout << "Classifying completed within " << timeSpan << " second(s)." << endl;

    return classified;
}

void AdvancedEliteClassifier::loadRealExperiments(vector<string>& testData)
{
    for (size_t i = 0; i < testData.size(); ++i) {
        replace(testData[i].begin(), testData[i].end(), ',', ' ');

        Experiment e;
        Variety v;
        Trail t;

        // parsing data from string

        istringstream iss(testData[i]);
        string tmpStr;

        iss >> e.experimentId;
        iss >> t.loccd;
        iss >> t.rep;
        iss >> v.varietyId;

        iss >> tmpStr;
        e.year = convertStringAsInt(tmpStr.substr(0, 4));

        iss >> tmpStr;
        if (0 == tmpStr.compare("NULL")) {
            v.type = Unknown;
        } else if (0 == tmpStr.compare("conv")) {
            v.type = Conventional;
        } else if (0 == tmpStr.compare("RR1")) {
            v.type = RoundupReady;
        } else if (0 == tmpStr.compare("RR2Y")) {
            v.type = RoundupReadyToYield;
        }

        iss >> t.yield;

        iss >> tmpStr;
        t.maturityNumber = convertNullableStringAsInt(tmpStr);

        iss >> v.relativeMaturity;

        iss >> tmpStr;
        t.podColor = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.pubescenceColor = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.flowerColor = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.emergence = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.plantHeight = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.harvestLodging = convertNullableStringAsInt(tmpStr);

        iss >> v.isCheck;
        if (!(iss >> v.isElite)) {
            v.isElite = DATA_NOT_AVAILABLE;
        }

        // storing data and generating stats

        const double yieldFixingFactor = 6.0;
        t.yieldFixed = t.yield + v.relativeMaturity * yieldFixingFactor;

        map<int, Experiment>::iterator ite = realExperiments.find(e.experimentId);
        if (ite == realExperiments.end()) {
            realExperiments[e.experimentId] = e;
            ite = realExperiments.find(e.experimentId);
        }

        map<int, Variety>::iterator itv = ite->second.varieties.find(v.varietyId);
        if (itv == ite->second.varieties.end()) {
            ite->second.varieties[v.varietyId] = v;
            itv = ite->second.varieties.find(v.varietyId);
        }

        itv->second.trails.push_back(t);
    }
}

void AdvancedEliteClassifier::classifyMethod()
{
    vector< pair<int, double> > scores;
    map<int, Experiment>::iterator ite;
    for (ite = realExperiments.begin(); ite != realExperiments.end(); ++ite) {
        Experiment *e = &ite->second;

        map<int, Variety>::iterator itv;
        for (itv = e->varieties.begin(); itv != e->varieties.end(); ++itv) {
            buildVarietyStats(itv->second);
        }

        for (itv = e->varieties.begin(); itv != e->varieties.end(); ++itv) {
            Variety *v = &itv->second;
            VarietyStats *vs = &v->stats;
            vs->score = 0.0;

            double winAccumulation = 0.0;
            double totalAccumulation = 0.0;
            for (size_t i = 0; i < 1; ++i) {
                if (v->isCheck) {
                    vs->score -= (1e+10);
                    break;
                }

                if (v->type == RoundupReadyToYield ||
                    (v->type == Conventional && e->year <= 2001) ||
                    v->type == Unknown) {
                    vs->score -= (1e+9);
                    break;
                }

                bool badPlantHeight = false;
                for (map<int, int>::iterator mapIt = vs->plantHeightsCount.begin();
                    mapIt != vs->plantHeightsCount.end(); ++mapIt) {
                        if (mapIt->first != DATA_NOT_AVAILABLE && mapIt->first < 40) {
                            badPlantHeight = true;
                            break;
                        }
                }
                if (badPlantHeight) {
                    vs->score -= (1e+8);
                    break;
                }

                if (findIntInMap(vs->emergencesCount, 7) || findIntInMap(vs->emergencesCount, 8)) {
                    vs->score -= (1e+8);
                    break;
                }

                if (findIntInMap(vs->podColorsCount, 3) || findIntInMap(vs->podColorsCount, 4) ||
                    findIntInMap(vs->podColorsCount, 5) || findIntInMap(vs->podColorsCount, 7)) {
                        vs->score -= (1e+8);
                        break;
                }

                if (findIntInMap(vs->pubescenceColorsCount, 5) ||
                    findIntInMap(vs->pubescenceColorsCount, 6)) {
                        vs->score -= (1e+8);
                        break;
                }

                if (findIntInMap(vs->flowerColorsCount, 4)) {
                    vs->score -= (1e+8);
                    break;
                }

                int checkCount = 0;
                map<int, Variety>::iterator itv2;
                for (itv2 = e->varieties.begin(); itv2 != e->varieties.end(); ++itv2) {
                    Variety *v2 = &itv2->second;
                    VarietyStats *vs2 = &v2->stats;

                    double weight = 1.0;
                    if (v2->isCheck) {
                        weight = 3.0;
                        ++checkCount;
                    }

                    double rmDiff = abs(v->relativeMaturity - v2->relativeMaturity);
                    if (rmDiff >= 1.5) {
                        weight *= 0.0;
                    } else if (rmDiff >= 1.0) {
                        weight *= 0.1;
                    } else if (rmDiff >= 0.5) {
                        weight *= 0.25;
                    }

                    if (vs->averageYield > vs2->averageYield) {
                        if (vs->averageYield / vs2->averageYield > 1.06) {
                            if (vs->averageMaturity < vs2->averageMaturity) {
                                winAccumulation += weight * 2.0;
                            } else {
                                winAccumulation += weight * 1.7;
                            }
                        } else if (vs->averageYield / vs2->averageYield > 1.03) {
                            if (vs->averageMaturity < vs2->averageMaturity) {
                                winAccumulation += weight * 1.8;
                            } else {
                                winAccumulation += weight * 1.5;
                            }
                        } else {
                            if (vs->averageMaturity < vs2->averageMaturity) {
                                winAccumulation += weight * 1.2;
                            } else {
                                winAccumulation += weight;
                            }
                        }
                    } else if (vs2->averageYield - vs->averageYield < 0.05) {
                        winAccumulation += weight / 3;
                    }
                    totalAccumulation += weight;
                }
                winAccumulation = pow(winAccumulation, 1.5);
                totalAccumulation = pow(totalAccumulation, 1.5);

                if (totalAccumulation > 0.0) {
                    vs->score += winAccumulation / totalAccumulation * (1e+7);

                    if (v->type == Conventional && e->year != 2005) {
                        vs->score *= 0.85;
                    }
                    if (v->type == RoundupReady && (e->year == 2002 || e->year == 2006)) {
                        vs->score *= 1.05;
                    }

                    if (e->year == 2003) {
                        vs->score *= 1.03;
                    }

                    if (v->trails.size() < 3) {
                        vs->score *= 0.7;
                    } else if (v->trails.size() >= 7 && v->trails.size() <= 9) {
                        vs->score *= 1.03;
                    }

                    size_t tc = v->trails.size();
                    double trailCountRatio = (trailCounts[tc].total > 1000) ?
                        ((double)trailCounts[tc].elite / trailCounts[tc].total) : 0.0;
                    vs->score *= 1.0 + trailCountRatio * (tc < 6 ? 0.5 : 1.0);

                    double mnCountRatio = (double)vs->maturityCount / v->trails.size();
                    if (mnCountRatio <= 0.1) {
                        vs->score *= 0.7;
                    } else if (mnCountRatio >= 0.9) {
                        vs->score *= 1.05;
                    }

                    if (checkCount == 4) {
                        vs->score *= 1.1;
                    } else if (checkCount == 5) {
                        vs->score *= 1.15;
                    } else if (checkCount > 5 && checkCount < 12) {
                        vs->score *= 1.1;
                    }

                    double yearEliteRatio = (double)years[e->year].elite / years[e->year].total;
                    vs->score *= 1 + 5 * pow(yearEliteRatio, 0.3);

                    if (findIntInMap(vs->podColorsCount, 9)) {
                        vs->score *= 0.95;
                    }

                    if (vs->maturityCount > 0) {
                        double yieldPerMaturity = vs->averageYield / vs->averageMaturity;
                        if (yieldPerMaturity < 0.4) {
                            vs->score *= 0.9;
                        }
                    }
                }
            }

            pair<int, double> p(v->varietyId, vs->score);
            scores.push_back(p);
        }
    }

    sort(scores.begin(), scores.end(), AdvancedEliteClassifier::cmpByScore);

    for (size_t i = 0; i < scores.size(); ++i) {
        classified.push_back(scores[i].first);
    }
}

void AdvancedEliteClassifier::reset()
{
    const double VERY_BIG_NUM = 100000000.0;
    const double VERY_SMALL_NUM = 0.0;

    classified.clear();
    experiments.clear();
    realExperiments.clear();
    physicalLocations.clear();

    totalNonCheckTrials = 0;
    totalVarieties = 0;
    checkVarieties = 0;
    eliteVarieties = 0;

    years.clear();
    types.clear();
    trailCounts.clear();
    maturityZones.clear();
    maturityBands.clear();
    podColors.clear();
    pubescenceColors.clear();
    flowerColors.clear();
    emergences.clear();
    plantHeights.clear();
    harvestLodgings.clear();

    minEliteYield = VERY_BIG_NUM;
    maxEliteYield = VERY_SMALL_NUM;
    minEliteYieldFixed = VERY_BIG_NUM;
    maxEliteYieldFixed = VERY_SMALL_NUM;

    earliestEliteMaturity = VERY_BIG_NUM;
    latestEliteMaturity = VERY_SMALL_NUM;

    totalYield = 0.0;
    totalYieldFixed = 0.0;
    totalMaturityCount = 0;
    totalMaturity = 0.0;
    averageYield = 0.0;
    averageYieldFixed = 0.0;
    averageMaturity = 0.0;
}

void AdvancedEliteClassifier::train(vector<string>& trainingData,
    vector<string>& locations)
{
    time_t startTime = time(NULL);
    cout << "Training with provided data..." << endl;

    for (size_t i = 0; i < locations.size(); ++i) {
        replace(locations[i].begin(), locations[i].end(), ',', ' ');

        PhysicalLocation pl;

        istringstream iss(locations[i]);
        string tmpStr;

        iss >> pl.loccd;
        iss >> pl.year;

        iss >> tmpStr;
        if (0 == tmpStr.compare("000")) {
            pl.zone = -2;
        } else if (0 == tmpStr.compare("00")) {
            pl.zone = -1;
        } else {
            pl.zone = convertStringAsInt(tmpStr);
        }

        iss >> pl.band;

        iss >> tmpStr;
        if (0 == tmpStr.compare("Early")) {
            pl.subZone = Early;
        } else if (0 == tmpStr.compare("Mid")) {
            pl.subZone = Mid;
        } else if (0 == tmpStr.compare("Late")) {
            pl.subZone = Late;
        }

        physicalLocations[pl.loccd][pl.year] = pl;
    }

    for (size_t i = 0; i < trainingData.size(); ++i) {
        replace(trainingData[i].begin(), trainingData[i].end(), ',', ' ');

        Experiment e;
        Variety v;
        Trail t;

        // parsing data from string

        istringstream iss(trainingData[i]);
        string tmpStr;

        iss >> e.experimentId;
        iss >> t.loccd;
        iss >> t.rep;
        iss >> v.varietyId;

        iss >> tmpStr;
        e.year = convertStringAsInt(tmpStr.substr(0, 4));

        iss >> tmpStr;
        if (0 == tmpStr.compare("NULL")) {
            v.type = Unknown;
        } else if (0 == tmpStr.compare("conv")) {
            v.type = Conventional;
        } else if (0 == tmpStr.compare("RR1")) {
            v.type = RoundupReady;
        } else if (0 == tmpStr.compare("RR2Y")) {
            v.type = RoundupReadyToYield;
        }

        iss >> t.yield;

        iss >> tmpStr;
        t.maturityNumber = convertNullableStringAsInt(tmpStr);

        iss >> v.relativeMaturity;

        iss >> tmpStr;
        t.podColor = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.pubescenceColor = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.flowerColor = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.emergence = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.plantHeight = convertNullableStringAsInt(tmpStr);
        iss >> tmpStr;
        t.harvestLodging = convertNullableStringAsInt(tmpStr);

        iss >> v.isCheck;
        if (!(iss >> v.isElite)) {
            v.isElite = DATA_NOT_AVAILABLE;
        }

        // storing data and generating stats

        const double yieldFixingFactor = 6.0;
        t.yieldFixed = t.yield + v.relativeMaturity * yieldFixingFactor;

        map<int, Experiment>::iterator ite = experiments.find(e.experimentId);
        if (ite == experiments.end()) {
            experiments[e.experimentId] = e;
            ite = experiments.find(e.experimentId);
        }

        map<int, Variety>::iterator itv = ite->second.varieties.find(v.varietyId);
        if (itv == ite->second.varieties.end()) {
            ite->second.varieties[v.varietyId] = v;
            itv = ite->second.varieties.find(v.varietyId);

            ++totalVarieties;

            if (v.isCheck) {
                ++checkVarieties;
            } else {
                ++years[e.year].total;
                ++types[v.type].total;

                if (v.isElite) {
                    ++eliteVarieties;
                    ++years[e.year].elite;
                    ++types[v.type].elite;
                }
            }
        }

        if (!v.isCheck) {
            ++totalNonCheckTrials;
            totalYield += t.yield;
            totalYieldFixed += t.yieldFixed;
            if (t.maturityNumber != DATA_NOT_AVAILABLE) {
                totalMaturity += t.maturityNumber;
                ++totalMaturityCount;
            }
            if (locationDataExists(t.loccd, e.year)) {
                ++maturityZones[physicalLocations[t.loccd][e.year].zone].total;
                ++maturityBands[physicalLocations[t.loccd][e.year].band].total;
            }
            ++podColors[t.podColor].total;
            ++pubescenceColors[t.pubescenceColor].total;
            ++flowerColors[t.flowerColor].total;
            ++emergences[t.emergence].total;
            ++plantHeights[t.plantHeight].total;
            ++harvestLodgings[t.harvestLodging].total;

            if (v.isElite)
            {
                if (locationDataExists(t.loccd, e.year)) {
                    ++maturityZones[physicalLocations[t.loccd][e.year].zone].elite;
                    ++maturityBands[physicalLocations[t.loccd][e.year].band].elite;
                }
                ++podColors[t.podColor].elite;
                ++pubescenceColors[t.pubescenceColor].elite;
                ++flowerColors[t.flowerColor].elite;
                ++emergences[t.emergence].elite;
                ++plantHeights[t.plantHeight].elite;
                ++harvestLodgings[t.harvestLodging].elite;

                if (t.yield < minEliteYield) {
                    minEliteYield = t.yield;
                } else if (t.yield > maxEliteYield) {
                    maxEliteYield = t.yield;
                }
                if (t.yieldFixed < minEliteYieldFixed) {
                    minEliteYieldFixed = t.yieldFixed;
                } else if (t.yieldFixed > maxEliteYieldFixed) {
                    maxEliteYieldFixed = t.yieldFixed;
                }
                if (t.maturityNumber != DATA_NOT_AVAILABLE) {
                    if (t.maturityNumber < earliestEliteMaturity) {
                        earliestEliteMaturity = t.maturityNumber;
                    } else if (t.maturityNumber > latestEliteMaturity) {
                        latestEliteMaturity = t.maturityNumber;
                    }
                }
            }
        }

        itv->second.trails.push_back(t);
    }

    averageYield = totalYield / totalNonCheckTrials;
    averageYieldFixed = totalYieldFixed / totalNonCheckTrials;
    averageMaturity = totalMaturity / totalMaturityCount;

    for (map<int, Experiment>::iterator ite = experiments.begin(); ite != experiments.end(); ++ite) {
        Experiment *e = &ite->second;
        for (map<int, Variety>::iterator itv = e->varieties.begin(); itv != e->varieties.end(); ++itv) {
            Variety *v = &itv->second;
            if (!v->isCheck) {
                int trailCount = v->trails.size();
                ++trailCounts[trailCount].total;
                if (v->isElite) {
                    ++trailCounts[trailCount].elite;
                }
            }
        }
    }

    time_t timeSpan = time(NULL) - startTime;
    cout << "Training completed within " << timeSpan << " second(s)." << endl;
}

void AdvancedEliteClassifier::buildVarietyStats(Variety& v)
{
    VarietyStats *vs = &v.stats;
    int subtotalTrials = v.trails.size();
    double subtotalYield = 0.0;
    double subtotalYieldFixed = 0.0;
    double subtotalMaturity = 0.0;
    vs->maxYield = 0.0;
    vs->maxYieldFixed = 0.0;
    vs->earliestMaturity = 100000000.0;
    vs->maturityCount = 0;

    for (int i = 0; i < subtotalTrials; ++i)
    {
        Trail *t = &v.trails[i];
        subtotalYield += t->yield;
        subtotalYieldFixed += t->yieldFixed;
        if (t->maturityNumber != DATA_NOT_AVAILABLE)
        {
            ++vs->maturityCount;
            subtotalMaturity += t->maturityNumber;

            if (t->maturityNumber < vs->earliestMaturity) {
                vs->earliestMaturity = t->maturityNumber;
            }
        }

        if (t->yield > vs->maxYield) {
            vs->maxYield = t->yield;
        }

        if (t->yieldFixed > vs->maxYieldFixed) {
            vs->maxYieldFixed = t->yieldFixed;
        }

        map<int, int>::iterator mapIt;

        mapIt = vs->podColorsCount.find(t->podColor);
        if (mapIt == vs->podColorsCount.end()) {
            vs->podColorsCount[t->podColor] = 1;
        } else {
            ++vs->podColorsCount[t->podColor];
        }

        mapIt = vs->pubescenceColorsCount.find(t->pubescenceColor);
        if (mapIt == vs->pubescenceColorsCount.end()) {
            vs->pubescenceColorsCount[t->pubescenceColor] = 1;
        } else {
            ++vs->pubescenceColorsCount[t->pubescenceColor];
        }

        mapIt = vs->flowerColorsCount.find(t->flowerColor);
        if (mapIt == vs->flowerColorsCount.end()) {
            vs->flowerColorsCount[t->flowerColor] = 1;
        } else {
            ++vs->flowerColorsCount[t->flowerColor];
        }

        mapIt = vs->emergencesCount.find(t->emergence);
        if (mapIt == vs->emergencesCount.end()) {
            vs->emergencesCount[t->emergence] = 1;
        } else {
            ++vs->emergencesCount[t->emergence];
        }

        mapIt = vs->plantHeightsCount.find(t->plantHeight);
        if (mapIt == vs->plantHeightsCount.end()) {
            vs->plantHeightsCount[t->plantHeight] = 1;
        } else {
            ++vs->plantHeightsCount[t->plantHeight];
        }

        mapIt = vs->harvestLodgingsCount.find(t->harvestLodging);
        if (mapIt == vs->harvestLodgingsCount.end()) {
            vs->harvestLodgingsCount[t->harvestLodging] = 1;
        } else {
            ++vs->harvestLodgingsCount[t->harvestLodging];
        }
    }

    vs->averageYield = subtotalYield / subtotalTrials;
    vs->averageYieldFixed = subtotalYieldFixed / subtotalTrials;
    if (vs->maturityCount > 0) {
        vs->averageMaturity = subtotalMaturity / vs->maturityCount;
    } else {
        vs->averageMaturity = averageMaturity + 50.0; // penalty
    }

    double subtotalYieldDiff = 0.0;
    double subtotalMaturityDiff = 0.0;
    for (int i = 0; i < subtotalTrials; ++i)
    {
        Trail *t = &v.trails[i];
        subtotalYieldDiff += pow(t->yield - vs->averageYield, 2);
        subtotalMaturityDiff += pow(t->maturityNumber - vs->averageMaturity, 2);
    }

    vs->yieldDeviation = sqrt(subtotalYieldDiff / totalNonCheckTrials);
    vs->maturityDeviation = sqrt(subtotalMaturityDiff / totalNonCheckTrials);
}

int AdvancedEliteClassifier::cmpByScore(const pair<int, double>& x, const pair<int, double>& y)
{
    return x.second > y.second;
}

int AdvancedEliteClassifier::convertStringAsInt(string data)
{
    int result;
    istringstream iss(data);
    iss >> result;
    return result;
}

int AdvancedEliteClassifier::convertNullableStringAsInt(string data)
{
    int result;
    if (0 == data.compare("NULL")) {
        result = DATA_NOT_AVAILABLE;
    } else {
        istringstream iss(data);
        iss >> result;
    }
    return result;
}

int AdvancedEliteClassifier::getPrimaryIntFromMap(map<int, int>& m)
{
    int maxAmount = 0;
    int result = 0;
    for (map<int, int>::iterator it = m.begin(); it != m.end(); ++it) {
        if (it->second > maxAmount) {
            maxAmount = it->second;
            result = it->first;
        }
    }
    return result;
}

bool AdvancedEliteClassifier::findIntInMap(map<int, int>& m, int n)
{
    map<int, int>::iterator it = m.find(n);
    if (it == m.end()) {
        return false;
    }
    return true;
}

bool AdvancedEliteClassifier::locationDataExists(string loccd, int year)
{
    map<string, map<int, PhysicalLocation> >::iterator it = physicalLocations.find(loccd);
    if (it != physicalLocations.end()) {
        map<int, PhysicalLocation>::iterator it2 = physicalLocations[loccd].find(year);
        if (it2 != physicalLocations[loccd].end()) {
            return true;
        }
    }
    return false;
}
