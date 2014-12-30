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

int countbit(int n) {return (n==0)?0:1+countbit(n&(n-1));}
int lowbit(int n) {return n&(n^(n-1));}
string toString(ll v) { ostringstream sout;sout<<v;return sout.str();}
string toString(int v) { ostringstream sout;sout<<v;return sout.str();}
int Rand16(){return rand();}
int Rand32(){return rand()*rand();}
double DRand(){return (double)rand()/RAND_MAX;}
int RandRange(int f,int r){return f+(int)(DRand()*(r-f)+0.5);} 

const int dir[][2]={ {1,0},{-1,0},{0,1},{0,-1}
};

const int MAX=100+5;
const int MAXS=200+1;
int n,m,u,v;
int h[MAX][MAX];
int id[MAX][MAX];
int sum[MAXS];

struct Point
{
	int x,y;
	Point(int x1=0,int y1=0):x(x1),y(y1){}
};

struct Node
{
	bool bo[MAX][MAX];
	int cnt;
};

Point p[MAXS];
Node vis[MAXS];

int mag;

vector<int> G[MAXS];

void addedge(int x,int id)
{
	int i;
	if (id==-1) return;
	for (i=sum[id];i<sum[id+1];i++)
		G[x].push_back(i);
}

bool in(Point p)
{
	return p.x>=0 && p.x<n && p.y>=0 && p.y<m;
}

bool match(int h1,int h2,int ty)
{
	if (!ty) return h1<=h2;else return h1>=h2;
}

queue<Point>que;

void BFS(int id)
{
	while (!que.empty()) que.pop();
	int ty=((id/u)+mag)%2;
	int i,j;
	Point cur,tmp;

	for (i=0;i<n;i++)
		for (j=0;j<m;j++)
			if (vis[id].bo[i][j])
			{
				que.push(Point(i,j));			
			}

	while (!que.empty())		
	{
		cur=que.front();
		que.pop();
		for (i=0;i<4;i++)
		{
			tmp.x=cur.x+dir[i][0];
			tmp.y=cur.y+dir[i][1];
			if (!in(tmp) || vis[id].bo[tmp.x][tmp.y] || !match(h[cur.x][cur.y],h[tmp.x][tmp.y],ty) ) continue;
			vis[id].bo[tmp.x][tmp.y]=true;
			vis[id].cnt++;
			addedge(id,::id[tmp.x][tmp.y]);
			que.push(tmp);
		}
	}
}

//hungry

int y[MAXS];
int hf[MAXS];
int gid;

bool hungry_aug(int x)
{
	if (hf[x]==gid) return false;
	hf[x]=gid;
	int i;
	for (i=0;i<G[x].size();i++)
	{
		int ny=G[x][i];
		if (y[ny]==-1 || hungry_aug(y[ny]) )
		{
			y[ny]=x;
			return true;
		}
	}
	return false;
}

int hungry()
{
	memset(y,-1,sizeof(y));	
	int res=0;
	int i;
	for (i=0;i<2*u;i++)
	{
		gid++;
		res+=hungry_aug(i);
	}
	return res;
}

int main()
{
	int t;
	int i,j;
	int x,y,cap;
	int tmp;


	//freopen("36728.in","r",stdin);
	//freopen("36728.out","w",stdout);

	scanf("%d",&t);
	while (t--)
	{
		scanf("%d%d%d%d",&n,&m,&u,&v);
		for (i=0;i<2*u+1;i++)
		{
			scanf("%d%d",&p[i].x,&p[i].y);
			p[i].x--;p[i].y--;
		}

		memset(id,-1,sizeof(id));
		sum[0]=0;
		for (i=0;i<v;i++) 
		{
			scanf("%d%d%d",&x,&y,&cap);
			x--;y--;
			id[x][y]=i;
			sum[i+1]=sum[i]+cap;
		}

		for (i=0;i<n;i++)
			for (j=0;j<m;j++)
				scanf("%d",&h[i][j]);
		
		for (i=0;i<2*u;i++) G[i].clear();		

		memset(vis,0,sizeof(vis));

		for (i=0;i<2*u;i++)
		{
			vis[i].bo[p[i].x][p[i].y]=true;
			vis[i].cnt=1;
			addedge(i,id[p[i].x][p[i].y]);			
		}

		for (mag=0;;mag++)
		{
			for (i=0;i<2*u;i++)
				if (vis[i].cnt<n*m) BFS(i);
			//??
			tmp=hungry();
		//	printf("mag=%d,tmp=%d\n",mag,tmp);
			if (2*u-tmp<=mag) break;
		}

		printf("%d\n",mag);
	}

	return 0;
}
