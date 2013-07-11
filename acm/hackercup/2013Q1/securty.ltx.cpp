#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <string.h>

using namespace std;

typedef long long int64;
typedef unsigned long long uint64;
#define two(X) (1<<(X))
#define twoL(X) (((int64)(1))<<(X))
#define contain(S,X) (((S)&two(X))!=0)
#define containL(S,X) (((S)&twoL(X))!=0)
const double pi=acos(-1.0);
const double eps=1e-11;
template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> inline T sqr(T x){return x*x;}
typedef pair<int,int> ipair;
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define PB(X) push_back(X)

const int maxn=100+5;

int n,L;
char a[maxn],b[maxn];

const int maxnode=2000+5;
const int maxedge=10000+5;

int nleft,nright,nedge;
int head[maxnode],point[maxedge],next[maxedge];
int p1[maxnode],p2[maxnode];
bool visited[maxnode];

void clear()
{
    for (int i=0;i<nleft;i++) p1[i]=-1;
    for (int i=0;i<nright;i++) p2[i]=-1;
}
void init(int _nleft,int _nright)
{
    nleft=_nleft;
    nright=_nright;
    nedge=0;
    for (int i=0;i<nleft;i++) head[i]=-1;
    clear();
}
void addedge(int u,int v)
{
    point[nedge]=v,next[nedge]=head[u],head[u]=(nedge++);
}
bool find_path(int v)
{
    for (int k=head[v];k>=0;k=next[k])
    {
        int p=point[k];
        if (!visited[p])
        {
            visited[p]=true;
            if (p2[p]<0 || find_path(p2[p]))
            {
                p1[v]=p;
                p2[p]=v;
                return true;
            }
        }
    }
    return false;
}
int doMatch()
{
    for (int i=0;i<nleft;i++)
        for (int k=head[i];p1[i]<0 && k>=0;k=next[k])
            if (p2[point[k]]<0)
            {
                p1[i]=point[k];
                p2[point[k]]=i;
            }
    for (int i=0;i<nleft;i++) if (p1[i]<0)
    {
        for (int k=0;k<nright;k++) visited[k]=false;
        find_path(i);
    }
    int result=0;
    for (int i=0;i<nleft;i++) if (p1[i]>=0) result++;
    return result;
}

bool solve()
{
    init(n,n);
    for (int i=0;i<n;i++) for (int j=0;j<n;j++)
    {
        bool ok=true;
        for (int k=0;k<L;k++)
        {
            char c1=a[i*L+k];
            char c2=b[j*L+k];
            if (c1!='?' && c2!='?' && c1!=c2) { ok=false; break; }
        }
        if (ok) addedge(i,j);
    }
    return doMatch()==n;
}
int main()
{
    //freopen("input.txt","r",stdin);
    freopen("security.txt","r",stdin); 
    freopen("security.ltx.out","w",stdout);
    int testcase;
    scanf("%d",&testcase);
    for (int case_id=1;case_id<=testcase;case_id++)
    {
        scanf("%d%s%s",&n,a,b);
        L=strlen(a)/n;
        printf("Case #%d: ",case_id);
        if (!solve())
        {
            printf("IMPOSSIBLE\n");
            continue;
        }
        for (int i=0;a[i];i++) if (a[i]=='?')
            for (char c='a';c<='f';c++)
            {
                a[i]=c;
                if (solve()) break;
            }
        printf("%s\n",a);
    }
    return 0;
}

