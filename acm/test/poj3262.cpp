#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 100000 + 50;

#define mp make_pair

typedef pair<int, int> PII;

int n;
vector<PII> arr;

bool cmp(const PII & lhs, const PII & rhs) {
//    if (lhs.first != rhs.first) return lhs.first < rhs.first;
 //   return lhs.second > rhs.second;
    return (long long)lhs.first * rhs.second < (long long)lhs.second * rhs.first;
}

int main() {
    while (scanf("%d", &n) != EOF) {
       arr.clear();
      int total_d = 0;
       for (int i = 0; i < n; i++) {
            int t, d;
            scanf("%d%d", &t, &d);
            arr.push_back(mp(t,d));
           total_d += d;
       }
       sort(arr.begin(), arr.end(), cmp);
      long long ans = 0;
       for (int i = 0; i < n; i++) {
            total_d -= arr[i].second;
           ans += (long long)2 * arr[i].first * total_d;
            //cout << "value = " << arr[i].first<< ' ' << arr[i].second << " score = " << arr[i].first * total_d  * 2<< endl;
       }
       cout<<ans<<endl;
   }
     return 0;
}
