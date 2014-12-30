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

#define Dump(x) cerr<<#x<<" = "<<(x)<<endl;

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

const int INF=1000000000;
const int MAX=2000000+5;

int n,m,s;
int pa[MAX];
int ans[MAX];
int dp[MAX];

int cbr[MAX];  //count for bricks at present
int bef[MAX];  //point to pre empty pos
int lae;       //point to last zero
int lab;       //count for bricks
int csum;	   //cur sum

void swap_arr(int arr[],int len)
{
	int i;
	for (i=0;i<len/2;i++) swap(arr[i],arr[len-1-i]);
}


void dumpArr(int arr[],int len)
{
	int i;
	printf("Dump:\n");
	for (i=0;i<len;i++) printf("%d ",arr[i]);putchar('\n');
}


void calc(int pa[MAX],int s,int dp[])  //from left to right
{
    int i,j,k;
    int tmpe,tmpb,tmp;

    csum=lae=-1;
    lab=0;

//	printf("dump pa:\n");
//	dumpArr(pa,s);


    for (j=0; j<s; j++)
    {
        if (pa[j]==0)  //empty pos
        {
            csum++;
			dp[csum]=0;
            cbr[csum]=lab;
            bef[csum]=lae;
            lae=csum;
        }
        else
        {
            lab++;
            tmpe=lae;
            tmpb=lab;
            tmp=0;
            for (k=csum+pa[j]; k>csum; k--)
            {
                if (tmpe<0) break;
                tmp+=tmpb-cbr[tmpe];
                dp[k]=min(dp[k],tmp);
                tmpb=cbr[tmpe];
                tmpe=bef[tmpe];				
            }
            csum+=pa[j];
        }
    }
}



int main()
{
    int i,j,k;
    int t;

//	freopen("k1.in","r",stdin);
//	freopen("out","w",stdout);

    scanf("%d",&t);
    while (t--)
    {
        memset(ans,0,sizeof(ans));

        scanf("%d%d",&n,&m);
        for (i=0; i<n; i++)
        {
            scanf("%d",&s);
            for (j=0; j<s; j++) scanf("%d",&pa[j]);

			//printf("row=%d\n",i);

			//Init
            for (j=0; j<m; j++) dp[j]=INF;			

			//calc

			//from left to right
			calc(pa,s,dp);

			//printf("from left to right:\n");
			//dumpArr(dp,m);

			swap_arr(dp,m);
			swap_arr(pa,s);

			//from right to left
			calc(pa,s,dp);


			swap_arr(dp,m);

			//printf("from right to left:\n");
			//dumpArr(dp,m);
         
            //update
            for (j=0; j<m; j++) 
				if (dp[j]!=INF)
					ans[j]+=dp[j];
				else
					ans[j]=INF;
        }

		//printf("dump ans:\n");
		//dumpArr(ans,m);

		int best=INF;
		int cnt=0;
		bool first=true;

		for (i=0;i<m;i++)
			best=min(best,ans[i]);
		printf("%d\n",best);
		for (i=0;i<m;i++)
			if (ans[i]==best)
			{
				if (first) first=false; else putchar(' ');
				printf("%d",i);
			}
		putchar('\n');
    }
    return 0;
}
