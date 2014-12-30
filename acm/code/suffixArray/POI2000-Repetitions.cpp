/*
多串LCS
*/
#include<iostream>

using namespace std;

const int MAXL=40000;

struct SuffixNode
{
	int id;
	int v[2];
};

struct SuffixArray
{
	SuffixNode r[MAXL],br[MAXL];
	int n;
	int st[MAXL],sa[MAXL],ra[MAXL],hi[MAXL],ct[MAXL];
	void RS()
	{
		int at,i;
		for (at=1;at>=0;at--)
		{
			memset(ct,0,sizeof(ct));
			for (i=0;i<n;i++) ct[r[i].v[at]]++;
			for (i=1;i<MAXL;i++) ct[i]+=ct[i-1];
			for (i=n-1;i>=0;i--) br[--ct[r[i].v[at]]]=r[i];
			for (i=0;i<n;i++) r[i]=br[i];
		}
		ra[r[0].id]=1;
		for (i=1;i<n;i++)
		{
			ra[r[i].id]=ra[r[i-1].id];
			if (r[i].v[0]!=r[i-1].v[0] || r[i].v[1]!=r[i-1].v[1])
				ra[r[i].id]++;
		}
	}

	void SA()
	{
		int i,j,k;
		for (i=0;i<n;i++)
		{
			r[i].v[0]=st[i];
			r[i].v[1]=0;
			r[i].id=i;
		}
		RS();
		for (k=1;k<n;k*=2)
		{
			for (i=0;i<n;i++)
			{
				r[i].id=i;
				r[i].v[0]=ra[i];
				r[i].v[1]=i+k<n?ra[i+k]:0;
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
			if (!ra[i]) h=0;
			else
			{
				k=sa[ra[i]-1];
				h=max(h-1,0);
				for (;st[i+h]==st[k+h];h++);
			}
			hi[ra[i]]=h;
		}
	}
}SAT;

char buffer[3000];
int pos[20];
int n;

bool ok(int L)
{
	int i,j,k;
	bool vis[20];
	for (i=1;i<SAT.n;i++)
		if (SAT.hi[i]>=L)
	{
		memset(vis,0,sizeof(vis));
		for (k=0;pos[k]<=SAT.sa[i-1];k++);
		vis[k]=true;
		for (j=i;j<SAT.n && SAT.hi[j]>=L;j++)
		{
			for (k=0;pos[k]<=SAT.sa[j];k++);
			vis[k]=true;
		}
		/*
		printf("L=%d\n",L);
		for (k=0;k<n;k++)
			if (vis[k]) printf("%d ",k);putchar('\n');
		*/
		for (k=0;k<n;k++)
			if (!vis[k]) break;
		if (k==n) return true;
		i=j;
	}
	return false;
}

int main()
{
	int i,j;
	int le;

	freopen("pow.in","r",stdin);
	freopen("pow.out","w",stdout);

	SAT.n=0;
	scanf("%d",&n);


	for (i=0;i<n;i++)
	{
		scanf("%s",buffer);
		le=strlen(buffer);
		for (j=0;j<le;j++)
			SAT.st[SAT.n++]=buffer[j];
		SAT.st[SAT.n++]=i;
		pos[i]=SAT.n;
	}

	//for (i=0;i<n;i++) printf("%d ",pos[i]);putchar('\n');

	if (n==1)
	{
		cout<<pos[0]<<endl;
		return 0;
	}

	SAT.SA();
	SAT.CH();

	//for (i=0;i<SAT.n;i++) printf("%d ",SAT.hi[i]);putchar('\n');

	int lo,hi,mi;
	lo=1;hi=2000;
	while (lo<=hi)
	{
		mi=(lo+hi)/2;
		if (ok(mi))
			lo=mi+1;
		else
			hi=mi-1;
	}
	
	cout<<hi<<endl;

	return 0;
}
