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


struct Point
{
	int x,y;
	Point(int x1=0,int y1=0):x(x1),y(y1){}
};

int n;
int sta,end;
vector<int>hor[1000+5];

bool dfs(Point cur,int chance)
{
	//printf("(%d %d) chance=%d\n",cur.x,cur.y,chance);

	//end
	if ( ( (!hor[cur.x].size()) || hor[cur.x][hor[cur.x].size()-1]<cur.y) && ( (!cur.x) || hor[cur.x-1][hor[cur.x-1].size()-1]<cur.y) )
		return cur.x==end;

	int px,nx;
	int py,ny;

	int bx,by;
	int tx,ty;

	px=py=-1;
	if ((hor[cur.x].size()) && hor[cur.x][hor[cur.x].size()-1]>cur.y)
	{
		px=upper_bound(hor[cur.x].begin(),hor[cur.x].end(),cur.y)-hor[cur.x].begin();
		nx=hor[cur.x][px]+1;
	}

	if (cur.x && hor[cur.x-1][hor[cur.x-1].size()-1]>cur.y)
	{
		py=upper_bound(hor[cur.x-1].begin(),hor[cur.x-1].end(),cur.y)-hor[cur.x-1].begin();
		ny=hor[cur.x-1][py]+1;
	}
	
	bx=cur.x;
	if (px !=-1 && py!=-1)
	{
		by=ty=min(nx,ny);
		tx=nx<ny?cur.x+1:cur.x-1;
	}
	else
	{
		if (px!=-1)
		{
			by=ty=nx;
			tx=cur.x+1;
		}
		else
		{
			by=ty=ny;
			tx=cur.x-1;
		}
	}

	//printf("b(%d %d) t(%d,%d)\n",bx,by,tx,ty);

	//no use chance
	if (dfs(Point(tx,ty),chance)) return true;

	//use chance
	if (chance && dfs(Point(bx,by),0)) return true; 
	
	return false;
}

int main()
{
	int i,j,v;
	int m;
	Point cur;

	//freopen("36728.in","r",stdin);
	//freopen("36728.out","w",stdout);

	while (scanf("%d",&n)!=EOF)
	{
		for (i=0;i<n-1;i++)
		{
			scanf("%d",&m);
			hor[i].clear();
			for(j=0;j<m;j++) 
			{
				scanf("%d",&v);
				v=v*2;
				hor[i].push_back(v);
			}
			sort(hor[i].begin(),hor[i].end());
		}
		hor[n-1].clear();

		scanf("%d%d",&sta,&end);

		if (n==1) 
		{
			puts("Yes");
			continue;
		}

		sta--;end--;		
		cur.x=sta;
		cur.y=-1;
		if (dfs(cur,1)) puts("Yes");
		else puts("No");
	}
	return 0;
}
