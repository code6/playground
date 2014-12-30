#include<iostream>
#include<algorithm>

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


int arr[MAXL],ptr;

bool ok(int L)
{
	int i,j,k;


	for (i=0;i<SAT.n;i++)
		if (SAT.hi[i]>=L)
	{
		ptr=1;arr[0]=SAT.sa[i-1];
		for (j=i;j<SAT.n && SAT.hi[j]>=L;j++)
			arr[ptr++]=SAT.sa[j];
		sort(arr,arr+ptr);
	//	printf("L=%d\n",L);
	//	for (k=0;k<ptr;k++) printf("%d ",arr[k]);putchar('\n');
		if (arr[0]==0) arr[0]=arr[1];
		if (ptr>=2 && arr[0]+L<arr[ptr-1]) return true;
		i=j;
	}
//	printf("L=%d false\n",L);
	return false;
}

int main()
{
	int i,j;
	int le;

	
	while (scanf("%d",&SAT.n)!=EOF)
	{
		if (!SAT.n) break;
		for (i=0;i<SAT.n;i++)
		{
			scanf("%d",&SAT.st[i]);		
		}
		SAT.st[i]=0;
		SAT.n++;
		for (i=SAT.n-1;i>=1;i--)
			SAT.st[i]=SAT.st[i]-SAT.st[i-1]+100;
		SAT.st[0]+=100;

	//	for (i=0;i<SAT.n;i++) printf("%d ",SAT.st[i]);putchar('\n');

		SAT.SA();
		SAT.CH();

	//	for (i=0;i<SAT.n;i++) printf("%d ",SAT.sa[i]);putchar('\n');

		int lo,hi,mi;
		lo=1;hi=SAT.n/2;
		while (lo<=hi)
		{
			mi=(lo+hi)/2;
			if (ok(mi))
				lo=mi+1;
			else
				hi=mi-1;
		}
		hi++;
		if (hi<5) hi=0;
		printf("%d\n",hi);
	}

	return 0;
}
