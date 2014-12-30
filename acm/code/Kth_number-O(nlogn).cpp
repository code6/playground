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

using namespace std;
typedef long long ll;

const double PI=acos(-1.0);
const double eps=1e-11;

#define dump(x) cerr<<#x<<" = "<<(x)<<endl;

int countbit(int n) {return (n==0)?0:1+countbit(n&(n-1));}
int lowbit(int n) {return n&(n^(n-1));}
string toString(ll v) { ostringstream sout;sout<<v;return sout.str();}
string toString(int v) { ostringstream sout;sout<<v;return sout.str();}
int Rand16(){return rand();}
int Rand32(){return rand()*rand();}
double DRand(){return (double)rand()/RAND_MAX;}
int RandRange(int f,int r){return f+(int)(DRand()*(r-f)+0.5);} 

const int MAX=100000*2+100;

struct SegNode
{
	int b,e;
	int l,r;
	int mid()
	{
		return (b+e)/2;
	}            
};    

int lc[20][100000+10];
int val[20][100000+10];
int sorted[100000+10];
int dup[100000+10];
int n,m;

struct SegTree
{
	SegNode s[MAX];
	int len;

	void Init()
	{
		len=0;     
		int i;
		for (i=0;i<n;i++)
			sorted[i]=val[0][i];

		sort(sorted,sorted+n);

		dup[0]=0;
		for (i=1;i<n;i++)
			if (sorted[i]==sorted[i-1]) 
				dup[i]=dup[i-1]+1;
			else 
				dup[i]=0;
	}    

	void Build(int f,int r,int dep)
	{
		int cur=++len;
		s[cur].b=f;
		s[cur].e=r;
		int mid=(f+r)/2; 
		int cv=sorted[mid];            
		int ct=0;

		if (sorted[f]==sorted[mid]) 
			ct=mid-f;
		else
			ct=dup[mid];

		//construction
		int i;		                                                                                                                                                                    
		for (i=f;i<r;i++)
		{                
			if (i>f) 
				lc[dep][i]=lc[dep][i-1];
			else 
				lc[dep][i]=0;                

			if (val[dep][i]<cv)
			{                                                           
				val[dep+1][f+lc[dep][i]]=val[dep][i];
				lc[dep][i]++;
			}
			else
			{
				if (val[dep][i]>cv)
				{
					val[dep+1][mid+(i-f-lc[dep][i])]=val[dep][i];                        
				}
				else
				{
					if (ct)
					{
						ct--;
						val[dep+1][f+lc[dep][i]]=val[dep][i];
						lc[dep][i]++;
					}
					else
					{
						val[dep+1][mid+(i-f-lc[dep][i])]=val[dep][i];           
					}        
				}        
			}        
		}               

		if (f+1<r)
		{                                                                             
			s[cur].l=len+1;
			Build(f,mid,dep+1);
			s[cur].r=len+1;
			Build(mid,r,dep+1);            
		}
	} 

	int Query(int dep,int cur,int f,int r,int kth)
	{
		if (f+1==r)
		{
			return val[dep][f];
		}    

		int sf=s[cur].b;
		int sr=s[cur].e;
		int sm=s[cur].mid();
		int olc;  
		int clc;  

		if (f==sf) 
		{
			olc=0;
			clc=lc[dep][r-1];
		}    
		else
		{
			olc=lc[dep][f-1];
			clc=lc[dep][r-1]-olc;
		}

		int nf,nr;

		if (clc>=kth)  //left
		{            
			nf=sf+olc;
			nr=nf+clc;
			return Query(dep+1,s[cur].l,nf,nr,kth);                                    
		}
		else  //right
		{
			nf=sm+(f-sf-olc);
			nr=nf+r-f-clc;
			return Query(dep+1,s[cur].r,nf,nr,kth-clc);
		}                                                                                                                                                       
	}                  
};    

SegTree T;

int main()
{
	int t;
	int i,j,k,a,b;

//	freopen("36727.in","r",stdin);
//	freopen("36727.out","w",stdout);

	while (scanf("%d%d",&n,&m)!=EOF)
	{
		
		for (i=0;i<n;i++) scanf("%d",&val[0][i]);
		T.Init();
		T.Build(0,n,0);
	//	for (i=0;i<10;i++)
//		{
//			printf("dep=%d\n",i);
//			for (j=0;j<n;j++)printf("%d ",val[i][j]);
//			putchar('\n');
//		}
//	
		for (i=0;i<m;i++)
		{
			scanf("%d%d%d",&a,&b,&k);
			printf("%d\n",T.Query(0,1,a-1,b,k));
		} 
		
	}    
	return 0;
}
