#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <map>
#include <cstring>
#include <sys/time.h>
#include <set>

using namespace std;

#include "Common.cpp"

timeval BEGIN; 
inline double time() {
  timeval NOW; gettimeofday(&NOW, NULL);
  return NOW.tv_sec - BEGIN.tv_sec + (NOW.tv_usec - BEGIN.tv_usec)/1000000.;    
}

vector<float> TRUE;

class YieldPredictor {
set<int> Var;
  public:
    vector<Bucket*> Predictor;
    void init_predictor() {
      Predictor.push_back(new Bucket(1, new _LOCID(), 1.));
      double alpha = 0.1;

/*
 * This list is genrated by Train.cpp
 * Values of Bucket multiplication factor = 0.01 + (alpha *= 0.99) have been tuned namually after.
 */
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5294, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-2,1),167,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5294, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-2,1),167,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5171, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,1,3,-4,1),183,1,1,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5993, new _PAIR(new _LOCID(),new _YEAR(),155,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5917, new _PAIR(new _LOCID(),new _CLIMATE(1,6,1,0,1),190,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,9,1,-6,1),136,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5171, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,1,3,-4,1),183,1,1,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,9,1,-6,1),136,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5957, new _PAIR(new _LOCID(),new _CLIMATE(1,6,1,2,1),178,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5845, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,2,-3,1),199,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5866, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,1,6,1),137,1,2,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5847, new _PAIR(new _DAY(),new _CLIMATE(1,7,1,-2,1),124,1,1,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5171, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,1,3,-4,1),183,1,1,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5950, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,1,0,1),179,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5989, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,11,-7,1),154,1,2,89), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,1,6,1),199,1,2,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5845, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,2,-3,1),199,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5822, new _PAIR(new _LOCID(),new _CLIMATE(1,9,1,-2,1),102,1,1,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _LOCID(),new _CLIMATE(1,7,1,-4,1),112,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5981, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,7,-2,1),161,1,2,126), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5963, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,11,-9,1),105,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5683, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,1,1,1),167,1,2,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5473, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,-5,1),132,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5682, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,10,1),190,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5977, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,2,15,1),105,1,2,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5938, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,2,0),143,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5768, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,4,4,0),154,1,2,123), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5852, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,9,-3,1),104,1,2,106), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,8,4,0),101,1,2,81), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5763, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,16,-17,1),110,1,2,45), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5809, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,5,0),103,1,2,113), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5919, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,13,1),180,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5878, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,10,0),121,1,2,109), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5797, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,11,-10,1),108,1,2,111), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5955, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,5,-5,1),131,1,2,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5974, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,5,-3,1),114,1,2,118), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _DAYOFYEAR(),new _CLIMATE(1,9,1,-6,1),136,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,2,5,0),105,1,2,123), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5987, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,5,0,1),169,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5959, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,11,1),107,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5788, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,3,-2,1),101,1,2,106), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5868, new _PAIR(new _YEAR(),new _MaterialId(),164,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5871, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,9,-3,1),183,1,2,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5696, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,7,-3,1),126,1,2,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5844, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,3,-2,1),164,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5923, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-5,1),179,1,2,129), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,8,4,0),185,1,2,129), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5969, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,-1,1),new _CLIMATE(0,2,2,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,-1,1),new _CLIMATE(0,4,2,-1,1),1,1,1,1),1,1,1,1),143,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5721, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,2,2,0),165,1,2,115), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5932, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,3,1),151,1,2,123), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,2,1),144,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5836, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,8,1),118,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,0,1),171,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5998, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,0,1),111,1,2,114), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5776, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,-1,1),109,1,2,91), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5150, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),150,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5997, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,1,10,1),105,1,2,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5956, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,-6,1),183,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5784, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-7,1),188,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5783, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,5,-2,1),185,1,2,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5954, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,17,1),new _CLIMATE(0,2,1,17,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,17,1),new _CLIMATE(0,4,1,17,1),1,1,1,1),1,1,1,1),141,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5697, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,2,1),171,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5966, new _PAIR(new _SRM(),new _MaterialId(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5201, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,11,-11,1),133,1,2,121), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5894, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),104,1,2,125), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5808, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-8,1),124,1,2,107), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5721, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,15,1),108,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5930, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-9,1),new _CLIMATE(0,2,8,-9,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-9,1),new _CLIMATE(0,4,8,-9,1),1,1,1,1),1,1,1,1),117,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5915, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-5,1),110,1,2,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5947, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,4,1),163,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5739, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,5,1,1),145,1,2,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5958, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,1,-1,1),161,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5901, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,4,1),159,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,9,0),176,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5984, new _PAIR(new _MONTH(),new _MaterialId(),111,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5801, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,4,-5,1),174,1,1,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5883, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,1,1),124,1,2,113), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5424, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,15,1),198,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5890, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,-6,1),113,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5737, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,8,7,1),192,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5969, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-3,1),172,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5780, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,1,0),113,1,2,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5791, new _PAIR(new _MaterialId(),new _LOCVAR(2),175,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5919, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,13,1),180,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5676, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,9,-6,1),138,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5936, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,0,1),172,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5548, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,3,1),197,1,2,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,16,-1,1),146,1,2,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5770, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,0,1),175,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-1,1),168,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5641, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,7,1),new _CLIMATE(0,2,2,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,7,1),new _CLIMATE(0,4,2,7,1),1,1,1,1),1,1,1,1),172,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5909, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,5,1,1),184,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5677, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-6,1),187,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5845, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,0,0),160,1,2,90), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-2,1),108,1,1,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5734, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-7,1),124,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,-1,1),157,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5919, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,2,8,0),112,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),100,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5931, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,1,1),139,1,1,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5320, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,5,0),100,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5934, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,4,1),176,1,2,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5381, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,15,1),new _CLIMATE(0,2,4,15,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,15,1),new _CLIMATE(0,4,4,15,1),1,1,1,1),1,1,1,1),173,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5982, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,3,1),111,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5990, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,1,1),104,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5943, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,6,0),138,1,2,100), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5846, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-1,1),new _CLIMATE(0,2,8,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-1,1),new _CLIMATE(0,4,8,-1,1),1,1,1,1),1,1,1,1),195,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5643, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-9,1),175,1,2,95), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5781, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-6,1),148,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,17,1),177,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5654, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,1,1),180,1,2,81), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5917, new _PAIR(new _LOCID(),new _CLIMATE(1,6,1,0,1),190,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5696, new _PAIR(new _LOCID(),new _CLIMATE(1,10,1,-1,1),156,1,1,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,2,1),168,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5672, new _PAIR(new _MaterialId(),new _CLIMATE(1,8,1,3,1),129,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5893, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,5,1),new _CLIMATE(0,2,1,5,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,5,1),new _CLIMATE(0,4,1,5,1),1,1,1,1),1,1,1,1),111,1,1,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5527, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-11,1),191,1,2,124), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5930, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,11,-6,1),131,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5821, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,8,4,0),102,1,2,110), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5701, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,9,0),165,1,2,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,1,1),187,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5463, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,3,0),138,1,2,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5573, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,3,1),154,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5613, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,3,1),new _CLIMATE(0,2,4,3,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,3,1),new _CLIMATE(0,4,4,3,1),1,1,1,1),1,1,1,1),106,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5579, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),179,1,1,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5508, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-7,1),142,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5561, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,7,1),new _CLIMATE(0,2,8,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,7,1),new _CLIMATE(0,4,8,7,1),1,1,1,1),1,1,1,1),123,1,2,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5730, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-4,1),178,1,1,83), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5711, new _PAIR(new _LOCVAR(3),new _MaterialId(),159,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5592, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),170,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5956, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,-6,1),183,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5945, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,4,2,0),197,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5683, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,4,0,0),162,1,1,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5150, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),150,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,2,1),144,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,7,-2,1),111,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5881, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,9,-9,1),169,1,2,107), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,18,1),147,1,2,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),138,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5438, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),134,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5720, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-6,1),121,1,2,93), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5795, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),102,1,1,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5692, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,3,2,1),173,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5649, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,1,1),138,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5598, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,0,1),141,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5534, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,0,1),139,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5497, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-2,1),144,1,2,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5611, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-4,1),154,1,2,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5612, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,1,14,1),162,1,1,49), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5697, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,2,1),171,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5485, new _PAIR(new _LOCVAR(0),new _MaterialId(),120,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5947, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-2,1),151,1,2,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5789, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-8,1),123,1,2,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5875, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,5,1,1),165,1,1,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5289, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,17,1),156,1,2,33), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5667, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,14,1),new _CLIMATE(0,2,1,14,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,14,1),new _CLIMATE(0,4,1,14,1),1,1,1,1),1,1,1,1),191,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,1,1),109,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5653, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,3,1,1),100,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5844, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,8,4,0),124,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5424, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,15,1),198,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5889, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,7,-1,1),127,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5814, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,8,0),195,1,2,91), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-1,1),168,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5901, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,4,1),159,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5928, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,0,1),154,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5708, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,11,-7,1),187,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5319, new _PAIR(new _MaterialId(),new _CLIMATE(1,8,1,-6,1),132,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,0,1),114,1,1,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5596, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,4,8,0),110,1,1,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5832, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,4,3,1),114,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5320, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-2,1),159,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5828, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,7,-6,1),125,1,1,82), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5230, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,1,1),191,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5982, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,3,1),111,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5145, new _PAIR(new _LOCVAR(1),new _MaterialId(),122,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,16,-1,1),new _CLIMATE(0,2,16,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,16,-1,1),new _CLIMATE(0,4,16,-1,1),1,1,1,1),1,1,1,1),184,1,2,34), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-2,1),108,1,1,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5923, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-5,1),179,1,2,129), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5900, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,5,1),155,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5952, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-9,1),102,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5608, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,16,-1,1),168,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5653, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,9,-10,1),112,1,1,127), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5890, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,-6,1),113,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5954, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,17,1),new _CLIMATE(0,2,1,17,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,17,1),new _CLIMATE(0,4,1,17,1),1,1,1,1),1,1,1,1),141,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5090, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,11,1),new _CLIMATE(0,2,4,11,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,11,1),new _CLIMATE(0,4,4,11,1),1,1,1,1),1,1,1,1),125,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5776, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,-1,1),109,1,2,91), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5575, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,14,1),102,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5687, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,2,5,0),126,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5489, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,1,1),110,1,2,118), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5579, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),179,1,1,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5747, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,0,1),193,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5931, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,1,1),139,1,1,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5677, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-6,1),187,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5758, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,2,7,1),136,1,1,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,16,-1,1),146,1,2,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5441, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,2,0),180,1,2,121), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5791, new _PAIR(new _MaterialId(),new _LOCVAR(2),175,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5802, new _PAIR(new _DAYOFYEAR(),new _LOCID(),104,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5374, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,9,1),new _CLIMATE(0,2,1,9,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,9,1),new _CLIMATE(0,4,1,9,1),1,1,1,1),1,1,1,1),157,1,2,45), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5492, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,11,-11,1),114,1,1,102), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5222, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,3,1),192,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5663, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,5,1),172,1,2,102), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5373, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,3,1),184,1,1,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5592, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),170,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5322, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,0,1),163,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5687, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-1,1),147,1,2,81), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5054, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,-2,1),130,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5015, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,3,1),154,1,1,124), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5894, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),104,1,2,125), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5412, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,4,-1,1),159,1,1,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5478, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,1,1),170,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5287, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,0,1),135,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5234, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,5,1),143,1,1,33), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5268, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,17,1),new _CLIMATE(0,2,2,17,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,17,1),new _CLIMATE(0,4,2,17,1),1,1,1,1),1,1,1,1),194,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5944, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,0,1),171,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5438, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),134,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5044, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,16,-17,1),188,1,1,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5293, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,1,5,1),120,1,2,90), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5485, new _PAIR(new _LOCVAR(0),new _MaterialId(),120,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5567, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),179,1,2,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),138,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,2,1),168,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5388, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-8,1),124,1,2,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5325, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,-1,1),new _CLIMATE(0,2,2,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,-1,1),new _CLIMATE(0,4,2,-1,1),1,1,1,1),1,1,1,1),197,1,1,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5584, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,8,-1,1),182,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5478, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,1,-2,1),159,1,2,83), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5639, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,9,-7,1),125,1,1,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5846, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-1,1),new _CLIMATE(0,2,8,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-1,1),new _CLIMATE(0,4,8,-1,1),1,1,1,1),1,1,1,1),195,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5191, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,7,1),124,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5381, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-4,1),122,1,2,115), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5711, new _PAIR(new _LOCVAR(3),new _MaterialId(),159,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5508, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,11,-7,1),142,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5251, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,0,1),139,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5593, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,8,1),new _CLIMATE(0,2,1,8,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,8,1),new _CLIMATE(0,4,1,8,1),1,1,1,1),1,1,1,1),108,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5721, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,15,1),108,1,2,46), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5613, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,5,1),153,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5529, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,3,3,1),116,1,2,89), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5234, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-10,1),164,1,2,90), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5770, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,0,1),175,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5577, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,-1,1),180,1,2,110), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5730, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-4,1),178,1,1,83), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5893, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,5,1),new _CLIMATE(0,2,1,5,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,5,1),new _CLIMATE(0,4,1,5,1),1,1,1,1),1,1,1,1),111,1,1,40), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5145, new _PAIR(new _LOCVAR(1),new _MaterialId(),122,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5784, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-7,1),188,1,2,86), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5152, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,4,11,1),148,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5628, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,3,-3,1),138,1,1,100), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5795, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),102,1,1,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5672, new _PAIR(new _MaterialId(),new _CLIMATE(1,8,1,3,1),129,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5998, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,0,1),111,1,2,114), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5573, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,3,1),154,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5537, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,-3,1),189,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5136, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,2,3,0),110,1,1,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5000, new _PAIR(new _MaterialId(),new _LOCVAR(3),146,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,16,1),100,1,2,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5181, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,-6,1),135,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5844, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,8,4,0),124,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5226, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,8,4,0),168,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5514, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,13,1),154,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5106, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),164,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5521, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,9,-8,1),103,1,1,103), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5982, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,3,3,1),111,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5956, new _PAIR(new _MaterialId(),new _CLIMATE(1,11,1,-6,1),183,1,2,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5534, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,0,1),139,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5381, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,15,1),new _CLIMATE(0,2,4,15,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,15,1),new _CLIMATE(0,4,4,15,1),1,1,1,1),1,1,1,1),173,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,7,-5,1),123,1,1,114), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5579, new _PAIR(new _MaterialId(),new _CLIMATE(1,12,1,-6,1),179,1,1,7), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5333, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-4,1),177,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5875, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,5,1,1),165,1,1,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5424, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,15,1),198,1,2,41), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-2,1),108,1,1,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5965, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,9,0),176,1,2,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5686, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,4,-1,1),103,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5612, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,1,14,1),162,1,1,49), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5343, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,-2,1),145,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5022, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,7,1),174,1,2,37), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5451, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,16,-17,1),127,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5945, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,4,2,0),197,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5683, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,4,0,0),162,1,1,98), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5026, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,17,1),186,1,2,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5607, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,9,-3,1),113,1,2,101), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5975, new _PAIR(new _MaterialId(),new _CLIMATE(1,6,1,2,1),144,1,2,5), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5168, new _PAIR(new _MaterialId(),new _CLIMATE(1,4,1,-1,1),106,1,2,109), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5896, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,8,-1,1),168,1,2,44), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5871, new _PAIR(new _MaterialId(),new _CLIMATE(0,4,4,7,1),100,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5592, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,2,1,1),new _CLIMATE(0,2,2,1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,2,1,1),new _CLIMATE(0,4,2,1,1),1,1,1,1),1,1,1,1),170,1,1,31), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5749, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,5,1,1),101,1,2,80), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5969, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-3,1),172,1,2,92), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5312, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,0,0),121,1,2,128), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5054, new _PAIR(new _MaterialId(),new _CLIMATE(1,7,1,-2,1),130,1,1,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5972, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,7,-2,1),111,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5116, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,16,1),new _CLIMATE(0,2,1,16,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,16,1),new _CLIMATE(0,4,1,16,1),1,1,1,1),1,1,1,1),178,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5150, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),150,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5485, new _PAIR(new _LOCVAR(0),new _MaterialId(),120,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5604, new _PAIR(new _MaterialId(),new _DAYOFYEAR(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5289, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,2,17,1),156,1,2,33), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5734, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-7,1),124,1,2,84), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5850, new _PAIR(new _DAYOFYEAR(),new _MaterialId(),177,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5905, new _PAIR(new _LOCID(),new _DAY(),129,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5984, new _PAIR(new _MONTH(),new _MaterialId(),111,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5548, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,1,3,1),197,1,2,105), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5758, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,2,7,1),136,1,1,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5936, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,5,0,1),172,1,2,104), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5598, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,1,0,1),141,1,1,119), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5438, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,4,7,1),new _CLIMATE(0,2,4,7,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,4,7,1),new _CLIMATE(0,4,4,7,1),1,1,1,1),1,1,1,1),134,1,1,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5481, new _PAIR(new _MaterialId(),new _LOCVAR(1),180,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5591, new _PAIR(new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),new _MaterialId(),100,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5947, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,4,1),163,1,2,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5832, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,4,3,1),114,1,2,32), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5931, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,1,1,1),139,1,1,96), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5427, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,4,0,0),173,1,1,108), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5490, new _PAIR(new _MaterialId(),new _LOCID(),116,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5480, new _PAIR(new _MaterialId(),new _PAIR(new _DAY(),new _DAY(),1,0,3,3),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5451, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,2,17,1),110,1,2,38), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5044, new _PAIR(new _MaterialId(),new _CLIMATE(0,1,16,-17,1),188,1,1,30), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5828, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,7,-6,1),125,1,1,82), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5808, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-8,1),124,1,2,107), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5111, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,1,11,1),171,1,1,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5653, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,9,-10,1),112,1,1,127), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5901, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,4,1),159,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5360, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,12,1),new _CLIMATE(0,2,1,12,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,12,1),new _CLIMATE(0,4,1,12,1),1,1,1,1),1,1,1,1),102,1,2,36), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5351, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,2,10,0),154,1,1,117), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5605, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,-2,1),138,1,1,112), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5412, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,4,-1,1),159,1,1,42), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5222, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,3,1),192,1,1,97), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5840, new _PAIR(new _DAY(),new _MaterialId(),113,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5551, new _PAIR(new _MaterialId(),new _CLIMATE(0,0,1,-1,1),175,1,2,45), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5708, new _PAIR(new _MaterialId(),new _CLIMATE(1,2,11,-7,1),187,1,1,87), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5145, new _PAIR(new _LOCVAR(1),new _MaterialId(),122,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5220, new _PAIR(new _MaterialId(),new _CLIMATE(1,0,3,-2,1),179,1,1,121), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5780, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,4,15,1),167,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5890, new _PAIR(new _MaterialId(),new _CLIMATE(1,10,1,-6,1),113,1,2,8), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5781, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,7,-6,1),148,1,2,85), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5608, new _PAIR(new _MaterialId(),new _CLIMATE(0,3,16,-1,1),168,1,2,48), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5697, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,2,1),171,1,2,6), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5302, new _PAIR(new _MaterialId(),new _CLIMATE(1,5,11,-10,1),115,1,1,113), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5930, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,8,-9,1),new _CLIMATE(0,2,8,-9,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,8,-9,1),new _CLIMATE(0,4,8,-9,1),1,1,1,1),1,1,1,1),117,1,2,43), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5320, new _PAIR(new _MaterialId(),new _CLIMATE(1,9,1,-2,1),159,1,2,9), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5098, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,16,-1,1),new _CLIMATE(0,2,16,-1,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,16,-1,1),new _CLIMATE(0,4,16,-1,1),1,1,1,1),1,1,1,1),184,1,2,34), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5872, new _PAIR(new _MaterialId(),new _PAIR(new _DAYOFYEAR(),new _DAYOFYEAR(),1,0,5,5),105,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5401, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,2,8,0),174,1,2,94), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5155, new _PAIR(new _LOCID(),new _MaterialId(),171,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5625, new _PAIR(new _MaterialId(),new _PAIR(new _PAIR(new _CLIMATE(0,1,1,2,1),new _CLIMATE(0,2,1,2,1),1,1,1,1),new _PAIR(new _CLIMATE(0,3,1,2,1),new _CLIMATE(0,4,1,2,1),1,1,1,1),1,1,1,1),161,1,2,47), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5979, new _PAIR(new _MaterialId(),new _LOCVAR(0),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5939, new _PAIR(new _MaterialId(),new _CLIMATE(0,2,2,1,1),187,1,1,35), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5858, new _PAIR(new _HERB(),new _LOCID(),126,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5037, new _PAIR(new _LOCID(),new _DAYOFYEAR(),197,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5864, new _PAIR(new _MaterialId(),new _CLIMATE(1,3,1,0,1),114,1,1,122), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5374, new _PAIR(new _MaterialId(),new _CLIMATE(1,1,1,0,1),134,1,2,116), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5148, new _PAIR(new _PAIR(new _DAY(),new _DAY(),1,0,3,3),new _MaterialId(),117,1,1,1), 0.01 + (alpha *= 0.99)));
Predictor.push_back(new Bucket(5090, new _PAIR(new _LOCVAR(2),new _MaterialId(),174,1,1,1), 0.01 + (alpha *= 0.99)));

    }

    void init_traindata(vector <string> &trainingData) {
      TRAINKEY.clear();
      YIELD.resize(trainingData.size());
      for(int i = 0; i < trainingData.size(); i++) TRAINKEY.push_back(parse_training(trainingData[i], YIELD[i]));
    }

    // Init all the Bucket with training data
    void train() {
      vector<float> YP(TRAINKEY.size());
      for(int i = 0; i < Predictor.size(); i++) {
        for(int j = 0; j < TRAINKEY.size(); j++) 
          if(i < 100 || abs(YIELD[j] - YP[j]) < 30) // Do not learn on cases that are hard to predict after 100 step (cases that looks like them are likely to have big error capped to 25. Theses cases are also more noisy.
            if(i < 100 || Var.find(TRAINKEY[j].MaterialId) != Var.end()) // After 100 step do not learn on varieties that won't be asked.
              Predictor[i]->train(TRAINKEY[j], YIELD[j] - YP[j]);
        
        // print training error.
        double MSE = 0.;
        double MSE2 = 0.;
        for(int j = 0; j < TRAINKEY.size(); j++) {
          YP[j] += Predictor[i]->predict(TRAINKEY[j]);
          double err = (YIELD[j] - YP[j])*(YIELD[j] - YP[j]);
          MSE += err;
          MSE2 += (err > 25*25) ? 25*25:err;
        }
        cerr << "train " << i << ": " << " " << time() << "s " << sqrt(MSE/TRAINKEY.size()) << " " << sqrt(MSE2/TRAINKEY.size()) << endl;
      }
    }

    void init_var( vector<string> &varieties) {
      for(int i = 0; i < varieties.size(); i++) Var.insert(atoi(varieties[i].c_str()));
    }


    vector <double> predictYield(vector <string> &trainingData, vector <string> &droughtMonitor, vector <string> &droughtNOAA, vector <string> &locations, vector <string> &varieties, vector <string> &queries) {
      gettimeofday(&BEGIN, NULL);

      // init
      init_var(varieties);
      init_traindata(trainingData);
      init_NOAA(droughtNOAA);
      init_DMonitor(droughtMonitor);
      init_location(locations);
      init_predictor();


      // train the model on training data
      train();


//      predict on queries...
      vector<Key> K;
      for(int i = 0; i < queries.size(); i++) {
        vector<string> T = tokenize(queries[i]);
        while(T.size() < 5) T.push_back("");
        K.push_back(Key(T[0], T[1], T[2], T[3], T[4]));
      }

      vector<double> R(queries.size());
      for(int j = 0; j < Predictor.size(); j++) {
        double MSE = 0.;
        double MSE2 = 0.;
        for(int i = 0; i < queries.size(); i++) {        
          R[i] += Predictor[j]->predict(K[i]);
          double err = R[i] - TRUE[i];
          err *= err;
          MSE += err;
          if(err > 25*25) err = 25*25;
          MSE2 += err;
        }
        cerr << "prediction: " << j << " " << sqrt(MSE/queries.size()) << " " << sqrt(MSE2/queries.size()) << endl;
      }
      cerr << "end: " <<  time() << "s" << endl;
      return R;
    }
};


// Load local files
vector<string> readfile(const char* filename, int skip = 0) {
  vector<string> R;
  ifstream F;
  F.open(filename);
  string L;
  for(int i = 0; i < skip; i++) getline(F, L);
  while(!F.eof()) {
    getline(F, L);
    if(F.fail()) break;
    R.push_back(L);
  }
  return R;
}



/*
 * Make K-fold validation on the aggregated model.
 * This allows to have an estimation of the prediction error.
 * This is usefull to mannualy choose the best parameters : 
 *  - alpha
 *  - number of basic predictor to keep (too few we don't get the optimum, to many we overfit)
 *  - number of test before ignoring some training data (varieties not used in validation)
 *  -
 *
 *  SPlit the data in 5 folds, learn on 4 and validate on one.
 *  make it 5 times (running 5 times this program) am make a mean of RMSE
 */

int main(int argc, char** argv) {
  int fold = -1;
  if(argc > 1) fold = atoi(argv[1]);
  cerr << "fold: " << fold << endl;

  vector<string> trainingData = readfile("DataTraining.csv", 0);
  vector<string> droughtMonitor = readfile("DroughtMonitor.csv", 1);
  vector<string> droughtNOAA = readfile("DroughtNOAA.csv", 1);
  vector<string> locations = readfile("Locations.csv", 0);
  vector<string> varieties = readfile("Varieties.csv", 0);

  vector <string> queries;
  vector <string> train;


  // create the training and queries set
  for(int i = 0; i < trainingData.size(); i++) {
    if(i % 5 == fold || fold == -1) {
      vector<string> T = tokenize(trainingData[i]);
      if(find(varieties.begin(), varieties.end(), T[3]) != varieties.end()) {
        queries.push_back(T[1] + "," + T[3] + "," + T[4] + "," + T[7] + "," + T[8]);
        TRUE.push_back(atof(T[5].c_str()));
      }
    }
    if(i % 5 != fold) train.push_back(trainingData[i]);
  }


  YieldPredictor YPred;
  vector<double> Pred = YPred.predictYield(train, droughtMonitor, droughtNOAA, locations, varieties, queries);

  double MSE = 0.;
  double MSE2 = 0.;

  for(int i = 0; i < Pred.size(); i++) {
    double err = (Pred[i] - TRUE[i])*(Pred[i] - TRUE[i]);
    MSE += err;
    if(err > 25*25) err = 25*25;
    MSE2 += err;      
  }

  cerr << "MSE = " << sqrt(MSE/Pred.size()) << endl;
  cerr << "MSE2 = " << sqrt(MSE2/Pred.size()) << endl;




}

