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
#define two(x) (1<<(x))

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

const int MAX=100+5;
const int MOD=10000007;

int n,m,s;
struct Point
{
    int x,y;
    bool operator<(const Point&rhs)const
    {
        return y<rhs.y || (y==rhs.y && x<rhs.x);
    }
};

Point p[MAX];
int G[16][16];

struct Node
{
    int s;
    int y;
};

struct Matrix
{
    int m[16][16];
    int n;

    Matrix() {}

    Matrix(int sz)
    {
        n=sz;
    }

    void One()
    {
        int i;
        memset(m,0,sizeof(m));
        for (i=0; i<n; i++)
            m[i][i]=1;
    }

    void Zero()
    {
        memset(m,0,sizeof(m));
    }

    Matrix mul(const Matrix&rhs)
    {
        Matrix ret(n);

        int i,j,k;
        for (i=0; i<n; i++)
            for (j=0; j<n; j++)
            {
                ret.m[i][j]=0;
                for (k=0; k<n; k++)
                    ret.m[i][j]=(ret.m[i][j]+(ll)m[i][k]*rhs.m[k][j])%MOD;
            }
        return ret;
    }

    Matrix pow(int L)
    {
        Matrix ret(n);
        Matrix coe(*this);
        ret.One();
        while (L)
        {
            if (L&1) ret=ret.mul(coe);
            coe=coe.mul(coe);
            L>>=1;
        }
        return ret;
    }

    void Dump()
    {
        int i,j;
        puts("dump:");
        for (i=0; i<n; i++,putchar('\n'))
            for (j=0; j<n; j++)
                printf("%d ",m[i][j]);
    }

};


int valid[]={0,3,6,12,15};

void BuildG(int n)
{
    int i,j;
    int ex;
    memset(G,0,sizeof(G));
    for (i=0; i<two(n); i++)
    {
        ex=two(n)-1-i;
        //printf("i=%d,ex=%d\n",i,ex);
        for (j=0; j<5 && valid[j]<two(n); j++)
            if (!(ex&valid[j]))
                G[i][ex|valid[j]]=1;
    }
}

void mul(int dp[],Matrix coe)
{
    int tmp[20];
    int i,j;

    //coe.Dump();

    memset(tmp,0,sizeof(tmp));
    for (i=0; i<two(n); i++)
    {
        //printf("dp[%d]=%d\n",i,dp[i]);
        for (j=0; j<two(n); j++)
        {
            tmp[j]=(tmp[j]+(ll)coe.m[i][j]*dp[i])%MOD;
            //printf("tmp[%d]=%d\n",j,tmp[j]);
        }

    }
    memcpy(dp,tmp,sizeof(tmp));
}

void mul(int dp[],int sta)
{
    int tmp[20];
    int i,j;
    int ex,ep;

    memset(tmp,0,sizeof(tmp));
    for (i=0; i<two(n); i++)
        if (dp[i])
        {
            ex=two(n)-1-i;
            for (j=0; j<5; j++)
                if ((valid[j]&sta)==0)
                {
                    ep=valid[j]|sta;
                    if (ex&ep) continue;
                    ep|=ex;
                    tmp[ep]=(tmp[ep]+dp[i])%MOD;
                }
        }
    memcpy(dp,tmp,sizeof(tmp));
}

int main()
{
    int i,j,k;
    int a,cas=0;
    Matrix T;
    int pre;
    int dp[20];

    //freopen("in","r",stdin);
    //freopen("out","w",stdout);

    /*
    T.n=1<<4;
    T.One();
    T.m[0][0]=2;
    T=T.pow(3);
    T.Dump();
    */

    while (scanf("%d%d%d",&n,&m,&s)!=EOF)
    {
        if (!n && !m && !s) break;
        cas++;

        T.n=1<<n;

        BuildG(n);  //build graph

        for (i=0; i<s; i++)
        {
            scanf("%d%d",&p[i].x,&p[i].y);
            p[i].y++;
        }
        sort(p,p+s);

        pre=0;
        memset(dp,0,sizeof(dp));
        dp[two(n)-1]=1;

        for (i=0; i<s; i=j+1)
        {
            for (j=i+1; j<s && p[j].y==p[i].y; j++);
            j--;

            a=0;
            for (k=i; k<=j; k++) a|=1<<p[k].x;

            memcpy(T.m,G,sizeof(G));
            T=T.pow(p[i].y-pre-1);
            //T.Dump();

            //printf("at lever=%d\n",p[i].y);

            mul(dp,T);
            //printf("after mul T\n");
            //for (k=0;k<two(n);k++) printf("dp[%d]=%d\n",k,dp[k]);
            mul(dp,a);
            //printf("after mul state=%d\n",a);
            //for (k=0;k<two(n);k++) printf("dp[%d]=%d\n",k,dp[k]);

            pre=p[i].y;
        }
        if (pre!=m)
        {
            memcpy(T.m,G,sizeof(G));
            T=T.pow(m-pre);
            mul(dp,T);
        }

        printf("Case %d: %d\n",cas,dp[two(n)-1]);
    }

    return 0;
}
