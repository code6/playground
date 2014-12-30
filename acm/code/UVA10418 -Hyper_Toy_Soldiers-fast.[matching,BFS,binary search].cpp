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
const int INF=100000;
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
	int bo[MAX][MAX];
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

queue<Point>que,expand;

void BFS(int id)
{
	int i,j;
	int step,ty;
	Point cur,nei,tmp;
	//int debug_cnt=1;

	for (i=0;i<n;i++) for (j=0;j<m;j++) vis[id].bo[i][j]=INF;
	vis[id].bo[p[id].x][p[id].y]=0;


	while (!que.empty()) que.pop();
	que.push(Point(p[id].x,p[id].y));	

	while (!que.empty())		
	{
		cur=que.front();
		que.pop();		

		//printf("at now cnt=%d\n",debug_cnt);

		step=vis[id].bo[cur.x][cur.y];
		ty=((id/u)+step)%2;

		while (!expand.empty()) expand.pop();
		expand.push(cur);

		while (!expand.empty())
		{
			nei=expand.front();
			expand.pop();

			for (i=0;i<4;i++)
			{
				tmp.x=nei.x+dir[i][0];
				tmp.y=nei.y+dir[i][1];
				if (!in(tmp) || vis[id].bo[tmp.x][tmp.y]<=step) continue;
				if (match(h[nei.x][nei.y],h[tmp.x][tmp.y],ty))
				{
						vis[id].bo[tmp.x][tmp.y]=step;
						expand.push(tmp);
				}
				else
				{
					if (vis[id].bo[tmp.x][tmp.y]==INF)
					{
						vis[id].bo[tmp.x][tmp.y]=step+1;
						que.push(tmp);
					}
					//debug_cnt++;
				}
			}
		}
	}
	//printf("%d is done.\n",id);
}

//hungry

int X[MAXS];
int y[MAXS];
int hf[MAXS];
int gid;

void BuildG(int mag)
{
	int i,j,k;
	for (i=0;i<2*u;i++)
	{
		G[i].clear();
		for (j=0;j<n;j++)
			for (k=0;k<m;k++)
				if (vis[i].bo[j][k]<=mag)
					addedge(i,id[j][k]);
	}
}

bool hungry_aug(int nx)
{
	if (hf[nx]==gid) return false;
	hf[nx]=gid;
	int i;
	for (i=0;i<G[nx].size();i++)
	{
		int ny=G[nx][i];
		if (y[ny]==-1 || hungry_aug(y[ny]) )
		{
			y[ny]=nx;
			X[nx]=ny;
			return true;
		}
	}
	return false;
}

int hungry()
{
	memset(X,-1,sizeof(X));
	memset(y,-1,sizeof(y));	
	int res=0;
	int i;
	for (i=0;i<2*u;i++)
		if (X[i]==-1)
	{
		gid++;
		res+=hungry_aug(i);
	}
	return res;
}

void Dump(int id)
{
	printf("id=%d,pos=(%d,%d)\n",id,p[id].x,p[id].y);
	int i,j;
	for (i=0;i<n;i++,putchar('\n'))
		for (j=0;j<m;j++)
			printf("%d ",vis[id].bo[i][j]);
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

		for (i=0;i<2*u;i++)
		{
			BFS(i);
			//Dump(i);
		}

		

		
		int f,r;

		f=0;r=2*u;
		while (f<=r)
		{
			mag=(f+r)/2;
			BuildG(mag);
			tmp=hungry();
			if (2*u-tmp<=mag) //ok
				r=mag-1;
			else
				f=mag+1;
		}
		printf("%d\n",f);
		

		/*						
		for (mag=0;;mag++)
		{
			BuildG(mag);
			if (2*u-hungry()<=mag) break;
		}

		printf("%d\n",mag);
		*/
	
	}

	return 0;
}
