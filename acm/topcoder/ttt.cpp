#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

using namespace std;

#define two(i) (1<<(i))

int calc(vector<int> has, vector<int> used)
{
   int tot, tot_used;
   int i;
   tot = tot_used = 0;
   //cout <<"has: ";
   for (i = 0; i < has.size(); i++) {
     tot += has[i];
     //cout << has[i] << " ";
   }
   //cout<<endl;
   //cout<<"used: ";
   for (i = 0; i < used.size(); i++) {
     tot_used += used[i];
     //cout<<used[i]<<" ";
   }
  // cout<<endl;
   if (tot < tot_used) {
      return -1;
   }
   
   sort(has.begin(), has.end());
   sort(used.begin(), used.end());
   
   int ret = 0;
   int bad = 0;
   
   for (i = 0; i < used.size(); i++) {
      int cur = used[used.size() - 1 - i];
      if (has.size()) {
          int zero = min(cur, has.back());
          cur -= zero;
          bad += has.back() - zero;
          has.pop_back();
      }
      while (cur) {
          if (bad == 0 && has.size() > 0) {
             bad += min(cur, has[0]);
             has[0] -= bad;
             if (has[0] == 0) {             
                has.erase(has.begin());
             }
          }
          int one = min(cur, bad);
          cur -= one;
          bad -= one;
          ret += one;          
      }
   }
   
   return ret;
}

class ICPCBalloons
{
  public:
      int minRepaintings(vector<int> ballonCount, string ballonSize, vector<int> maxAccepted) {
      vector<int> vm, vl;
      int i, n, m;
      n = ballonCount.size();
      m = maxAccepted.size();
      for (i = 0; i < n; i++) {
         if (ballonSize[i] == 'M') {
            vm.push_back(ballonCount[i]);
         } else {
            vl.push_back(ballonCount[i]);
         }
      
      }
      int ans = -1;
      
      int j;
      for (i = 0; i < two(m); i++) {
         vector<int> ul, um;
         for (j = 0; j < m; j++) {
            if (i & two(j)) {
              ul.push_back(maxAccepted[j]); 
            } else {
              um.push_back(maxAccepted[j]);
            }
         }
         int bl = calc(vl, ul);
         int bm = calc(vm, um);
    //     cout <<"state = " << i << "bl = " << bl << " bm = " << bm << endl;
         if (bl == -1 || bm == -1) {
         } else {
            if (ans == -1) {
              ans = bl + bm;
            } else {
              ans = min(ans, bl + bm);
            }
         }
      }
      
      return ans;
  }  
};
