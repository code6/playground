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
typedef int ll;

const double PI=acos(-1.0);
const double eps=1e-8;

#define dump(x) cerr<<#x<<" = "<<(x)<<endl;

int countbit(int n) {return (n==0)?0:1+countbit(n&(n-1));}
int lowbit(int n) {return n&(n^(n-1));}
int Rand16(){return rand();}
int Rand32(){return rand()*rand();}
double DRand(){return (double)rand()/RAND_MAX;}
int RandRange(int f,int r){return f+(int)(DRand()*(r-f)+0.5);} 
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

ll gcd(ll a,ll b)
{
	return b?gcd(b,a%b):a;
}

ll ext_gcd(ll a,ll b,ll&x,ll&y)
{
	ll t, d;
	if (b == 0) { x = 1; y = 0; return a; }
	d = ext_gcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - a / b*y;
	return d;
}

struct RESULT
{
	int ok;
	ll f,s;
};


ll A[4];
ll ans;

RESULT MIES(ll a,ll b,ll n)
{
	ll x,y,d;
	RESULT res;
	d=ext_gcd(a,n,x,y);
	if (b%d!=0)
	{
		res.ok=0;
		return res;
	}
	res.s=n/d;
	res.f=((x*(b/d))%res.s+res.s)%res.s;
	
	res.ok=1;
	return res;
}


int main()
{
	int t;
	int i,j;
	double v;
	ll sx,sy,ex,ey;
	ll dx,dy,d;
	ll ca,cb,da,db,ea,eb,ec;
	RESULT ra,rb,rc;

//	freopen("in","r",stdin);
//	freopen("out","w",stdout);
	
	scanf("%d",&t);
	while (t--)
	{
		for (i=0;i<4;i++) 
		{
			scanf("%lf",&v);	
		//	printf("%lf ",v);
			if (v>=0)
				A[i]=(ll)(10*(v+eps));
			else
				A[i]=(ll)(10*(v-eps));
		}
		//putchar('\n');
		sx=A[0];sy=A[1];ex=A[2];ey=A[3];
		//printf("sx=%I64d,sy=%I64d,ex=%I64d,ey=%I64d\n",sx,sy,ex,ey);

		dx=abs(sx-ex);dy=abs(sy-ey);

		if (!dx && !dy)
		{
			if (sx%10==0 && sy%10==0) ans=1;else ans=0;
			printf("%d\n",ans);
			//cout<<ans<<endl;
			continue;
		}

		d=gcd(dx,dy);

		dx/=d;
		dy/=d;
		if (ex-sx<0) dx*=-1;
		if (ey-sy<0) dy*=-1;

		//printf("dx=%I64d,dy=%I64d,d=%I64d\n",dx,dy,d);

		ca=(dx%10+10)%10;
		cb=((-sx)%10+10)%10;
		ra=MIES(ca,cb,10);

		//printf("ca=%I64d,cb=%I64d,cc=%I64d\n",ca,cb,10);
		//printf("ra.ok=%d,ra.f=%I64d,ra.s=%I64d\n",ra.ok,ra.f,ra.s);
		
		da=(dy%10+10)%10;
		db=((-sy)%10+10)%10;
		rb=MIES(da,db,10);

	//	printf("da=%I64d,db=%I64d,dc=%I64d\n",da,db,10);
	//	printf("rb.ok=%d,rb.f=%I64d,rb.s=%I64d\n",rb.ok,rb.f,rb.s);
		

		if (!ra.ok || !rb.ok) ans=0;
		else
		{
			ec=rb.s;
			ea=(ra.s%ec+ec)%ec;
			eb=((rb.f-ra.f)%ec+ec)%ec;
			rc=MIES(ea,eb,ec);
			//printf("rc.ok=%d,rc.f=%I64d,rc.s=%I64d\n",rc.ok,rc.f,rc.s);
			if (!rc.ok) ans=0;
			else
			{
				ll tmp=d-(ra.f+rc.f*ra.s);
			//	printf("tmp=%I64d\n",tmp);
				if (tmp<0)
					ans=0;
				else
					ans=tmp/ra.s/rc.s+1;
			}
		}

		//cout<<ans<<endl;
		printf("%d\n",ans);
	}
	return 0;
}
