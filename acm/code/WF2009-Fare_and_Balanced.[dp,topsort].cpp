#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
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
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>
#include <assert.h>

using namespace std;
typedef long long ll;

const double PI=acos(-1.0);
const double eps=1e-11;

#define dump(x) cerr<<#x<<" = "<<(x)<<endl;
#define mp make_pair

int countbit(int n)
{
    return (n==0)?0:1+countbit(n&(n-1));
}
int lowbit(int n)
{
    return n&(n^(n-1));
}
string toString(ll v)
{
    ostringstream sout;
    sout<<v;
    return sout.str();
}
string toString(int v)
{
    ostringstream sout;
    sout<<v;
    return sout.str();
}
int Rand16()
{
    return rand();
}
int Rand32()
{
    return rand()*rand();
}
double DRand()
{
    return (double)rand()/RAND_MAX;
}
int RandRange(int f,int r)
{
    return f+(int)(DRand()*(r-f)+0.5);
}
void shuffle(int cards[], int n)
{
    while (n > 1)
    {
        int  k;
        int  tmp;
        // Swap a random unshuffled card with the top-most card
        k = rand() % n;
        n--;
        tmp = cards[n];
        cards[n] = cards[k];
        cards[k] = tmp;
    }
}

const int MAX=50000+5;

struct Edge
{
    int b,v,id;
    Edge(int b=0,int v=0,int id=0):b(b),v(v),id(id) {}
};

struct Node
{
    bool tag; //first differ point tag
    int max_v;  //max dis from cur to end
    void init()
    {
        tag=0;
        max_v=-1;
    }
};


int n,m;
vector<Edge>G[MAX];
int min_dis[MAX],max_dis[MAX];
Node dp[MAX];

int ol[MAX];
int c_in[MAX];
queue<int>que;

vector<pair<int,int> >ans;


void Topsort()  //from p0
{
    int i,j;
    memset(c_in,0,sizeof(c_in));
    for (i=0; i<n; i++)
        for (j=0; j<G[i].size(); j++)
            c_in[G[i][j].b]++;

    while (!que.empty()) que.pop();

    //assert
    for (i=1; i<n; i++)
        if (!c_in[i])  while (1);// assert(1==0);
    if (c_in[0]>0) while (1);    //assert(1==0);

    //push start
    que.push(0);

    memset(min_dis,-1,sizeof(min_dis));
    memset(max_dis,-1,sizeof(max_dis));
    min_dis[0]=max_dis[0]=0;

    j=0;
    while (!que.empty())
    {
        int cur=que.front();
        que.pop();
        ol[j++]=cur;
        for (i=0; i<G[cur].size(); i++)
        {
            if (min_dis[G[cur][i].b]==-1 || min_dis[G[cur][i].b]>min_dis[cur]+G[cur][i].v) min_dis[G[cur][i].b]=min_dis[cur]+G[cur][i].v;
            if (max_dis[G[cur][i].b]<max_dis[cur]+G[cur][i].v) max_dis[G[cur][i].b]=max_dis[cur]+G[cur][i].v;
            c_in[G[cur][i].b]--;
            if (!c_in[G[cur][i].b]) que.push(G[cur][i].b);
        }
    }
    if (j!=n) while (1);
    //printf("In Topsort ,ol sz=%d\n",j);
}

bool Solve()
{
    int i,j;
    int cv;
    int tv,ts;

    dp[n-1].init();
    dp[n-1].max_v=0;


    for (i=n-2; i>=0; i--)
    {
        cv=ol[i];
        dp[cv].init();
        for (j=0; j<G[cv].size(); j++)
        {
            tv=G[cv][j].b;
            ts=G[cv][j].v+dp[tv].max_v;

			if (dp[tv].tag)
				dp[cv].tag=true;

            if (dp[cv].max_v==-1) dp[cv].max_v=ts;
            else
            {
                if (dp[cv].max_v!=ts) //first differ
                {
                    //dis from sta to cv not unique
                    if (min_dis[cv]!=max_dis[cv]) return false;
                    dp[cv].max_v=max(dp[cv].max_v,ts);
                    dp[cv].tag=true;
                }
            }
        }
    }

    return true;
}


int main()
{
    int i,j;
    int a,b,v,le;
    int cas=0;

   // freopen("in","r",stdin);
   // freopen("out","w",stdout);

    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (!n && !m) break;
        cas++;

        for (i=0; i<n; i++) G[i].clear();
        for (i=0; i<m; i++)
        {
            scanf("%d%d%d",&a,&b,&v);
            a--;
            b--;
            G[a].push_back(Edge(b,v,i));
        }

        Topsort();

        printf("Case %d: ",cas);
        if (Solve())
        {
            int fmod=0;
            int fdis=dp[0].max_v;

            ans.clear();
            for (i=0; i<n; i++)
                if (dp[i].tag)
                {
                    for (j=0; j<G[i].size(); j++)												
						if (!dp[G[i][j].b].tag)
                    {
                        le=fdis-min_dis[i]-G[i][j].v-dp[G[i][j].b].max_v;
                        //assert(le>=0);
                        if (le<0) while (1);
                        if (le>0)
                        {
                            fmod++;
                            ans.push_back(mp(G[i][j].id+1,le));
                        }
                    }
                }
            printf("%d %d\n",fmod,fdis);
            for (i=0; i<fmod; i++)
                printf("%d %d\n",ans[i].first,ans[i].second);

        }
        else
            puts("No solution");
    }
    return 0;
}
