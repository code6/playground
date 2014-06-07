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

using namespace std;


#include "Common.cpp"


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


void init() {
 /*
   * Load and init data structure that store Drought and Location Data.
   */
  vector<string> V = readfile("DroughtNOAA.csv", 1);
  init_NOAA(V);
  cerr << "init NOAA OK" << endl;

  V = readfile("DroughtMonitor.csv", 1);
  init_DMonitor(V);
  cerr << "init DroughtMonitor OK" << endl;

  V = readfile("Locations.csv", 0);
  init_location(V);
  cerr << "init Locations OK" << endl;

  // Load the training data into Key object 
  // and observed yield int YIELD vector  
  V = readfile("DataTraining.csv", 0);
  for(int i = 0; i < V.size(); i++) {
    float Y;    
    Key K = parse_training(V[i], Y);
    K.index = i;
    TRAINKEY.push_back(K);
    YIELD.push_back(Y);
  }


}




int main() {
  init();
  cerr << "init OK" << endl;

   // We define basic variables
   // See Extractor for their respective meaning
  vector<Extractor*> V1;
  V1.push_back(new _LOCID());
  V1.push_back(new _MaterialId());
  V1.push_back(new _HERB());
  V1.push_back(new _RM());
  V1.push_back(new _SRM());
  V1.push_back(new _YEAR());
  V1.push_back(new _MONTH());
  V1.push_back(new _DAY());
  V1.push_back(new _DAYOFYEAR());
  V1.push_back(new _PAIR(new _DAYOFYEAR(), new _DAYOFYEAR(), 1, 0, 5, 5));
  V1.push_back(new _PAIR(new _DAY(), new _DAY(), 1, 0, 3, 3));
  for(int i = 0; i < 5; i++) V1.push_back(new _LOCVAR(i));


   // mean variable in column 'pos' (0 to 5) in DroughtNOAA from plantDate + offset to plantDate + offset + length
   // manage to cover period before and during soy growth
   // Not all possible combination to reduce complexity
  vector<Extractor*> V2;
  for(int pos = 0; pos < 6; pos++)
    for(int length = 1; length < 12; length += 2)
      for(int offset = -length - 1; offset + length <= 6; offset++ )
        V2.push_back(new _CLIMATE(1, pos, length, offset, 1));

   // mean variable in column 'pos' (0 to 5) in DroughtNOAA from january + ofset to january + offset + length of the plant Year
   // Not all possible combination to reduce complexity
  for(int pos = 0; pos < 6; pos++)
    for(int length = 2; length < 10; length *= 2)
      for(int offset = 0; offset + length <= 12; offset += length/2)
        V2.push_back(new _CLIMATE(1, pos, length, offset, 0));

   // mean variable in columnn 'pos' (6 to 12) in DroughtNOAA for plantDate + offset date
   // As these variables are already cumulative vars, no need to make means.
   // Not all possible combination to reduce complexity
   vector<Extractor*> V3;
  for(int pos = 6; pos < 13; pos++)
    for(int offset = -6; offset < 6; offset += pos - 5 )
      V3.push_back(new _CLIMATE(1, pos, 1, offset, 1));

   // mean variable in column 'pos' (0 to 4) in DroughtMonitor from plantDate + offset to plantDate + offset + length
   // manage to cover period before and during soy growth
   // Not all possible combination to reduce complexity
  vector<Extractor*> V4;
  for(int pos = 0; pos < 5; pos++)
    for(int length = 1; length <= 16; length *= 2)
      for(int offset = -length - 1; offset + length < 20; offset += length)
        V4.push_back(new _CLIMATE(0, pos, length, offset, 1));

   // Special combination of the 4 vars of DroughtMonitor = D0 + 2 * D1 + 3 * D2 + 4 * D3
   // of different length and offset.
    for(int length = 1; length <= 16; length *= 2)
      for(int offset = -length - 1; offset + length < 20; offset += length)
        V4.push_back(new _PAIR(
              new _PAIR(new _CLIMATE(0, 1, length, offset, 1), new _CLIMATE(0, 2, length, offset, 1), 1, 1, 1, 1),
              new _PAIR(new _CLIMATE(0, 3, length, offset, 1), new _CLIMATE(0, 4, length, offset, 1), 1, 1, 1, 1),
              1, 1, 1, 1));


    /** 
     * Now we generate a Pool of basic candidates predictor to be combined.
     */

  vector<Bucket*> Cand;

  // First predictor that use basic and climate vars alone
  for(int i = 0; i < V1.size(); i++) {
    Cand.push_back(new Bucket(5000 + rand()%1000, V1[i]));
  }
  for(int i = 0; i < V2.size(); i++) {
    Cand.push_back(new Bucket(5000 + rand()%1000, V2[i]));
  }
  for(int i = 0; i < V3.size(); i++) {
    Cand.push_back(new Bucket(5000 + rand()%1000, V3[i]));
  }

  // Then a set of predictor for all pairs of basic variables.
  for(int i = 0; i <  V1.size(); i++) 
    for(int j = 0; j <  V1.size(); j++) 
      if(i != j) 
        Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[i], V1[j], 100 + rand()%100, 1, 1, 1)));

  // Then a set of pairs between basic vars and climate vars
  // _LOCID, _DAY, _MaterialId seems to provide good correlation with climate, so add more of them.
  for(int i = 0; i < V2.size(); i++) {
   if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _LOCID(), V2[i], 100 + rand()%100, 1, 1, 80 + rand() % 50)));
   if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _DAY(), V2[i], 100 + rand()%100, 1, 2,  80 + rand() % 50)));
   if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _MaterialId(), V2[i], 100 + rand()%100, 1, 2,  80 + rand() % 50)));
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[rand()%V1.size()], V2[i], 100 + rand()%100, 1, 1,  80 + rand() % 50)));
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[rand()%V1.size()], V2[i], 100 + rand()%100, 1, 1,  80 + rand() % 50)));
  }
  for(int i = 0; i < V3.size(); i++) {
    if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _LOCID(), V3[i], 100 + rand()%100, 1, 1, 5 + rand() % 5)));
    if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _DAY(), V3[i], 100 + rand()%100, 1, 2, 5 + rand() % 5)));
    if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _MaterialId(), V3[i], 100 + rand()%100, 1, 2, 5 + rand() % 5)));
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[rand()%V1.size()], V3[i], 100 + rand()%100, 1, 1, 5 + rand() % 5)));
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[rand()%V1.size()], V3[i], 100 + rand()%100, 1, 1, 5 + rand() % 5)));
  }
  for(int i = 0; i < V4.size(); i++) {
    if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _LOCID(), V4[i], 100 + rand()%100, 1, 1, 30 + rand()%20)));
    if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _DAY(), V4[i], 100 + rand()%100, 1, 2,  30 + rand()%20)));
    if(rand()%4) Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(new _MaterialId(), V4[i], 100 + rand()%100, 1, 2,  30 + rand()%20)));
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[rand()%V1.size()], V4[i], 100 + rand()%100, 1, 1, 30 + rand()%20)));
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V1[rand()%V1.size()], V4[i], 100 + rand()%100, 1, 1, 30 + rand()%20)));
  }

  // Add some random pairs of climate variable.
  for(int i = 0; i < 100; i++)
    Cand.push_back(new Bucket(5000 + rand()%1000, new _PAIR(V2[rand()%V2.size()], V4[rand()%V4.size()], 100 + rand()%100, 1, 80 + rand() % 50, 30 + rand()%20)));

  cerr << "Vsize: " << V1.size() << " " << V2.size() << " " << V3.size() << " " << V4.size() << endl;
  cerr << "Candidates: " << Cand.size() << endl;


  // Bufferize computation of bucketized variables (AS we will use them a lot of time during training). Not necessary on validation.
  for(int i = 0; i < Cand.size(); i++) {
    if(i % 100 == 0) cerr << "Bufferize: " << i << endl;
    Cand[i]->bufferize();
  }

  // This is the vector of the successive basic predictor that will be compined.
  // Init with a first predictor that is just the mean of all yields (only 1 bucket, any var instead of V1[0] will give same result, alpha = 1).
  // We will greedily add some more Predictor that will learn on the previous prediction error. 
  // This provide an aggregated predictor (Boosting in Machine learning: http://en.wikipedia.org/wiki/Boosting)
  vector<Bucket*> Selection;
  Selection.push_back(new Bucket(1, V1[0], 1.));



  // YP (Yield Prediction) will be the vector of predicted yield with the first current aggregated predictor
  vector<float> YP(TRAINKEY.size());


  // Train the first algorithm (only one in our case, but we could have manualy initialized with more basic predictors)
  for(int k = 0; k < Selection.size(); k++) {
    for(int i = 0; i < TRAINKEY.size(); i++) 
        Selection[k]->train(TRAINKEY[i], YIELD[i] - YP[i]);

    // update YP with current prediction.
    for(int i = 0; i < TRAINKEY.size(); i++) YP[i] += Selection[k]->predict(TRAINKEY[i]);
  }


  // Make a lot of step/
  for(int step = Selection.size(); step < 500; step++) {
    cerr << "step: " << step << endl;

    // reset all candidate predictor that will learn on new error from current aggregated predictor.
    for(int i = 0; i < Cand.size(); i++) Cand[i]->reset();
    cerr << "reset: OK" << endl;

    // Train all the basic predictor to predict the error (YIELD[i] - YP[i]) of the current aggregated predictor.
    for(int i = 0; i < TRAINKEY.size(); i++) {
      if(i % 10000 == 0) cerr << "training: " << i << endl;
          for(int j = 0; j < Cand.size(); j++) Cand[j]->train(TRAINKEY[i], YIELD[i] - YP[i]);
    }
    cerr << "train: OK" << endl;


    // we will compute the RMSE of all candidates.
    vector<double> MSE(Cand.size());

    for(int i = 0; i < TRAINKEY.size(); i++) {
      if(i % 10000 == 0) cerr << "rmse: " << i << endl;

      for(int j = 0; j < Cand.size(); j++) {
        float err = (YP[i] + Cand[j]->predict(TRAINKEY[i]) - YIELD[i]);
        err *= err;
        if(step > 100 && err > 30*30) err = 30*30;  // Do not optimize after 100 step on cases that we will surely never have an error < 25.
        MSE[j] += err;
      }
    }

    cerr << "rmse: OK" << endl;

    // Choose and add to aggregation the 2 best Predictor. (1 would be better but 2 reduce the training time by a factor 2...)
    for(int k = 0; k < 2; k++) {

      int best_i = 0;
      for(int i = 0; i < Cand.size(); i++)
        if(MSE[i] < MSE[best_i]) best_i = i;
      cout << step << " " << Cand[best_i]->print() << endl;

  
      // re-train the chosen predictor (necessary for k > 0)
      if(k > 0) {
        Cand[best_i]->reset();
        for(int i = 0; i < TRAINKEY.size(); i++)
          Cand[best_i]->train(TRAINKEY[i], YIELD[i] - YP[i]); 
      }


      // Add the Predictor, update YP and make sure that we don't choose it twice
      Selection.push_back(new Bucket(*Cand[best_i]));
      for(int i = 0; i < TRAINKEY.size(); i++) YP[i] += Cand[best_i]->predict(TRAINKEY[i]);
      MSE[best_i] = 1e40;

    }
  }
}



