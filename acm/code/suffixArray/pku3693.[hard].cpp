#include<iostream>
#include<algorithm>

using namespace std;

const int MAXL=100000+500;

typedef pair<pair<int,int>,int >PIII;
#define mp make_pair
#define two(i) (1<<(i))

//Suffix Array
struct SuffixArray
{
	PIII r[MAXL];
	int n;
	int st[MAXL],sa[MAXL],ra[MAXL],hi[MAXL];	
	int rm[18][MAXL],ru[18][MAXL];

	
	void RS()
	{	
		sort(r,r+n);
		int i;
		ra[r[0].second]=1;
		for (i=1;i<n;i++)
		{
			ra[r[i].second]=ra[r[i-1].second];
			if (r[i].first!=r[i-1].first)
				ra[r[i].second]++;					
		}
	}

	void SA()
	{
		int i,m;
		for (i=0;i<n;i++)
		{
			r[i].first.first=st[i];
			r[i].first.second=0;
			r[i].second=i;
		}
		RS();
		for (m=1;m<n;m*=2)
		{
			for (i=0;i<n;i++)				
			{
				r[i].first.first=ra[i];
				r[i].first.second=i+m<n?ra[i+m]:0;
				r[i].second=i;
			}
			RS();
		}
		for (i=0;i<n;i++)
			sa[--ra[i]]=i;
	}

	void CH()
	{
		int i,k,h=0;
		for (i=0;i<n;i++)
		{
			if (!ra[i])
				h=0;
			else
			{
				k=sa[ra[i]-1];
				h=max(h-1,0);
				for (;st[i+h]==st[k+h];h++);
			}
			hi[ra[i]]=h;
		}
	}

	void LCP_INIT()
	{
		int i ,j;
		for (i=0;i<n;i++) rm[0][i]=hi[i];
		for (i=1;two(i)<=n;i++)
			for (j=0;j+two(i)<=n;j++)
					rm[i][j]=min(rm[i-1][j],rm[i-1][j+two(i-1)]);
	}

	int LCP(int x,int y)
	{
		x=ra[x],y=ra[y];
		if (x==y) return n-sa[x];
		if (x>y) swap(x,y);		
		x++;		
		int i;
		for (i=0;x+two(i)-1<=y;i++);i--;
		return min(rm[i][x],rm[i][y-two(i)+1]);
	}

	void PFX_INIT()
	{
		int i ,j;
		for (i=0;i<n;i++) ru[0][i]=ra[i];
		for (i=1;two(i)<=n;i++)
			for (j=0;j+two(i)<=n;j++)
					ru[i][j]=min(ru[i-1][j],ru[i-1][j+two(i-1)]);
	}

	int PFX(int x,int y)
	{
		if (x==y) return x;
		if (x>y) swap(x,y);						
		int i;
		for (i=0;x+two(i)-1<=y;i++);i--;
		return sa[min(ru[i][x],ru[i][y-two(i)+1])];
	}
}ST;


char S[MAXL];
int b_l,b_at,b_sz;

void update(int &b_l,int &b_at,int &b_sz,int t_l,int t_at,int t_sz)
{
	if (b_l<t_l || (b_l==t_l && ST.ra[b_at]>ST.ra[t_at]) )
	{
		b_l=t_l;
		b_at=t_at;
		b_sz=t_sz;
	}
}

void solve()
{
	int i ,j,jj;

	ST.n=0;
	for (i=0;S[i];i++) ST.st[ST.n++]=S[i];
	ST.st[ST.n]=0;
	ST.SA();
	ST.CH();
	ST.LCP_INIT();
	ST.PFX_INIT();

	b_l=1;
	b_at=ST.sa[0];
	b_sz=1;

	//printf("b_at=%d\n",b_at);

//	printf("Test\n");

	int t_l,t_at,f,r;
	int lo,hi,mi;
	int w,ww;
	int L;
	for (L=1;L<ST.n;L++)	
		for (j=0;j+L<ST.n;j+=L)
		{
			
			int w=ST.LCP(j,j+L);
			if (!w) continue;



		//	printf("L=%d,j=%d,j+L=%d,w=%d\n",L,j,j+L,w);
			jj=j-(L-w%L);
			if (jj<0 || (j-L==jj) ) 
				ww=0;
			else
				ww=ST.LCP(jj,jj+L);

		//	printf("L=%d,jj=%d,jj+L=%d,w=%d,ww=%d\n",L,jj,jj+L,w,ww);

			if (ww>=L) 
			{
				t_l=ww/L+1;
				f=j-L+1;
				r=jj;
			}
			else
			{
				t_l=w/L+1;
				f=max(jj+1,0);
				r=j;
			}

			

			if (f>r) continue;
			lo=f;hi=r;
			while (lo<=hi)
			{
				mi=(lo+hi)/2;
				w=ST.LCP(mi,mi+L);
				if (w<L) 
					lo=mi+1;
				else
					hi=mi-1;
			}
			
			t_at=ST.PFX(lo,r);
			//printf("f=%d,r=%d,t_l=%d,t_at=%d\n",f,r,t_l,t_at);
			update(b_l,b_at,b_sz,t_l,t_at,L);
		}	
}

void test_SA()
{
	int i,j;
	while (scanf("%s",S)!=EOF)
	{
		ST.n=0;
		for (i=0;S[i];i++) ST.st[ST.n++]=S[i];
		ST.st[ST.n++]=0;
		ST.SA();
		ST.CH();
		ST.LCP_INIT();
		ST.PFX_INIT();
		printf("sa:");
		for (i=0;i<ST.n;i++) printf("%d ",ST.sa[i]);putchar('\n');
		printf("ra:");
		for (i=0;i<ST.n;i++) printf("%d ",ST.ra[i]);putchar('\n');
		printf("LCP:\n");
		for (i=0;i<ST.n;i++,putchar('\n'))
			for (j=i+1;j<ST.n;j++)
				printf("lcp[%d,%d]=%d ",i,j,ST.LCP(i,j));
		printf("PFX:\n");
		for (i=0;i<ST.n;i++,putchar('\n'))
			for (j=i+1;j<ST.n;j++)
				printf("PFX[%d,%d]=%d ",i,j,ST.PFX(i,j));

	}
}


int main()
{
	//test_SA();
	int i,j;
	int cas=0;
	while (scanf("%s",S)!=EOF)
	{	
		if (S[0]=='#') break;		
		printf("Case %d: ",++cas);
		solve();
	//	printf("b_at=%d,b_l=%d,b_sz=%d\n",b_at,b_l,b_sz);
		for (i=b_at;i<b_at+b_l*b_sz;i++)
			putchar(S[i]);
		putchar('\n');
	}
	return 0;
}
