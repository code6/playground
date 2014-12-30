#include <cstdio>
#include <cstring>



#define maxm 500*900
#define maxn 999

int R[maxm],L[maxm],U[maxm],D[maxm],col[maxm],row[maxm],sz;
int S[maxn];
void remove(int &c) {
    for(int i = D[c]; i != c ; i = D[i]) {
        L[R[i]] = L[i];
        R[L[i]] = R[i];
    }
}
void resume(int &c) {
    for(int i = U[c]; i != c ; i = U[i]) {
        L[R[i]] = i;
        R[L[i]] = i;
    }
}
int h() {
    bool hash[99] = {};
    memset(hash,false,sizeof(hash));
    int ret = 0;
    for(int c = R[0] ; c != 0 ; c = R[c]) {
        if(hash[c])    continue;
        ret ++;
        hash[c] = true;
        for(int i = D[c] ; i != c ; i = D[i]) {
            for(int j = R[i] ; j != i ; j = R[j]) {
                hash[col[j]] = true;
            }
        }
    }
    return ret;
}
bool dfs(int deep,int lim) {
    if(deep + h() > lim)    return false;
    if(R[0] == 0)    return true;
    int i,j,idx,MM = 99999;
    for(i = R[0] ; i != 0 ; i = R[i]) {
        if(S[i] < MM) {
            MM = S[i];
            idx = i;
        }
    }
    for(i = D[idx] ; i != idx; i = D[i]) {
        remove(i);
        for(j = R[i] ; j != i ; j = R[j]) {
            remove(j);
        }
        if(dfs(deep+1,lim)) {
            for(j = L[i] ; j != i ; j = L[j]) {
                resume(j);
            }
            resume(i);
            return true;
        }
        for(j = L[i] ; j != i ; j = L[j]) {
            resume(j);
        }
        resume(i);
    }
    return false;
}
void Insert(int j,int &first,int i = -1) {// 行数i通常用不到
    if(first == -1) {
        first = sz;
    }
    L[sz] = sz - 1;
    R[sz] = sz + 1;
    D[sz] = j;
    D[U[j]] = sz;
    U[sz] = U[j];
    U[j] = sz;
    col[sz] = j;
    row[sz] = i;
    S[j] ++;
    sz ++;
}
void init(int n) {//列数
    sz = 0;
    for(int i = 0 ; i <= n ; i ++) {
        U[i] = i;
        D[i] = i;
        L[i] = i - 1;
        R[i] = i + 1;
    }
    L[0] = n;
    R[n] = 0;
    sz = n + 1;
    memset(S,0,sizeof(S));
}
bool maze[66][66];
int main() {
    int n , m ;
    while(~scanf("%d%d",&n,&m)) {
        init(n);
        memset(maze , false , sizeof(maze));
        while(m --) {
            int a , b;
            scanf("%d%d",&a,&b);
            maze[a][b] = maze[b][a] = true;
        }
        for (int i = 1 ; i <= n ; i ++) {
            maze[i][i] = true;
        }
        for (int i = 1 ; i <= n ; i ++) {
            int first = -1;
            for (int j = 1 ; j <= n ; j ++) {
                if(maze[i][j]) {
                    Insert(j , first);
                }
            }
            if(first != -1) {
                L[first] = sz - 1;
                R[sz-1] = first;
            }
        }
        int lo = 1;
        int hi = n;
        while(lo <= hi) {
            int mid = (lo + hi) >> 1;
            if(dfs(0,mid)) {
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        printf("%d\n",hi+1);
    }
    return 0;
}
