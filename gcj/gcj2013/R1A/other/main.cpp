#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
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
#include <cstring>
#include <ctime>
#include <queue>

using namespace std;

#define	sqr(a)		((a)*(a))
#define	rep(i,a,b)	for(int i=(a);i<(int)(b);i++)
#define	per(i,a,b)	for(int i=((a)-1);i>=(int)(b);i--)
#define	PER(i,n)	per(i,n,0)
#define	REP(i,n)	rep(i,0,n)
#define	clr(a)		memset((a),0,sizeof (a))
#define	SZ(a)		((int)((a).size()))
#define	ALL(x)		x.begin(),x.end()
#define	mabs(a)		((a)>0?(a):(-(a)))
#define	inf			(0x7fffffff)
#define	eps			1e-6

#define	MAXN		
#define MODN		(1000000007)

typedef long long ll;
long long v[10005];

int main()
{
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);

	int CASE;
	scanf("%d",&CASE);
	rep(K,1,CASE + 1)
	{
		long long e,r,n;
		scanf("%I64d %I64d %I64d",&e,&r,&n);
		r = min(e,r);
		long long t_v = 0;
		long long res = 0;
		
		long long dp[15][15];

		clr(dp);

		REP(i,n)
		{
			scanf("%I64d",&v[i]);
		}

		REP(i,n)
		{
			REP(j,e + 1)
			{
				REP(k,j + 1)
				{
					int x = min(e,j - k + r);
					dp[i + 1][x] = max(dp[i + 1][x],dp[i][j] + k * v[i]);
					res = max(res,dp[i + 1][x]);
				}
			}
		}

		printf("Case #%d: ",K);
		printf("%I64d\n",res);
	}

	return 0;
}
