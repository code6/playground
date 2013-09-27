#include <cstdio>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <vector>
#include <bitset>
#include <algorithm>

using namespace std;

#define mp make_pair

typedef long long ll;
const int MAX = 100 + 50;

int R, N, M, K;
int v[MAX][MAX];

map<set<int>, string> MM;

void dfs(int dep, int cval, string num, set<int> S) {
    //printf("dep = %d, cval = %d, num = %s\n", dep, cval, num.c_str());
    if (dep == 3) {
        MM[S] = num;
        return;
    }
    dfs(dep + 1, cval, num, S);
    int nval = cval * (int)(num[dep]);
    S.insert(nval);
    dfs(dep + 1, nval, num, S);
}

void init() {
    MM.clear();
    int i, j, k;
    for (i = 1; i <= 5; i++) 
    for (j = 1; j <= 5; j++) 
    for (k = 1; k <= 5; k++) 
    {
        stringstream ssin;
        ssin << i << j << k;
        string v;
        ssin >> v;
        set<int> S;
        S.insert(1);
        dfs(0, 1, v, S);
    }
}

void process(int cas) {
    init();
    int i;
    int j;
    cout<<"Case #"<<cas<<":\n";
    for (i = 0; i < R; i++) {
        set<int> s;
        string ans;
        map<set<int>, string>::iterator it;
        for (it = MM.begin(); it != MM.end(); it++) {
            set<int> ori = it->first;
            for (it = ori.begin(); it != ori.end(); it++) {
            }
            for (j = 0; j < K; j++) {
                if (ori.find(v[i][j]) == ori.end()) {
                    break;
                }
            }
            if (j == K) {
                ans = it->second;
                break;
            }
        }
        cout<<ans<<endl;
    }
}

void read() {
    cin >> R >> N >> M >> K;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < K; j++) {
            scanf("%d", &v[i][j]);
        }
    }
}

void run(int cas) {
    read();
    process(cas);
}

int main() {
    freopen("C.in", "r", stdin);
//    freopen("C.out", "w", stdout);
    int T;
    scanf("%d", &T);
    for (int cas  = 1; cas <= T; cas++) {
        run(cas);
    }

    return 0;
}
