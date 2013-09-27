/* --- Author: Vladimir Smykalov, enot.1.10@gmail.com --- */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include <ctime>
#include <cassert>

using namespace std;

#define fs first
#define sc second
#define pb push_back
#define mp make_pair
#define range(i, n) for (int i=0; i<(n); ++i)
#define forit(it,v) for(typeof((v).begin()) it = v.begin() ; it != (v).end() ; ++it)
#define eprintf(...) fprintf(stderr, __VA_ARGS__),fflush(stderr)
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(),a.end()

typedef long long ll;
typedef vector<int> VI;
typedef pair<int, int> PII;

int main() {
    int n;

    while (cin >> n) {
        priority_queue<double> pq;
        range(i, n) {
            int v;
            cin >>  v;
            pq.push(v);
        }
        while (pq.size() > 1) {
            double x, y;
            x = pq.top(); pq.pop();
            y = pq.top(); pq.pop();
            pq.push(2.0 * sqrt(x * y));
        }
        printf("%.3lf\n", pq.top());
    }
    return 0;
}
