#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

typedef pair<int,int> PII ;
#define mp make_pair

const int MAXL=300000;

struct RadixNode
{
	int id;
	int v[2];
};

struct SuffixArray
{	
	RadixNode r[MAXL],br[MAXL];
	int ct[MAXL];	
	int n,st[MAXL],sa[MAXL],ra[MAXL],hi[MAXL];
	int dif;
	void RS() 
	{
		int at,i;
		for (at=1;at>=0;at--)  //only 2 pass
		{
			memset(ct,0,sizeof(int)*dif);
			for (i=0;i<n;i++)	ct[r[i].v[at]]++;
			for (i=1;i<dif;i++)	ct[i]+=ct[i-1];
			for (i=n-1;i>=0;i--) br[--ct[r[i].v[at]]]=r[i];
			for (i=0;i<n;i++) r[i]=br[i];
		}

		//compute rank
		ra[r[0].id]=1;
		for (i=1;i<n;i++)
		{
			ra[r[i].id]=ra[r[i-1].id];
			if (r[i].v[0]!=r[i-1].v[0] || r[i].v[1]!=r[i-1].v[1])
				ra[r[i].id]++;
		}
		dif=ra[r[n-1].id]+1;
	}

	void SA()
	{
		int i,k;
		//int tp=0;
		for (i=0;i<n;i++)
		{
			r[i].id=i;
			r[i].v[0]=st[i];
			r[i].v[1]=0;
		}
		dif=500;
		RS();

		/*
		printf("pass %d,rank:\n",tp);
		for (i=0;i<n;i++)
			printf("%d ",ra[i]);putchar('\n');
		*/

		for (k=1;k<n;k*=2)
		{
			//tp++;
			for (i=0;i<n;i++)
			{
				r[i].id=i;
				r[i].v[0]=ra[i];
				r[i].v[1]=i+k<n?ra[i+k]:0;
			}
			RS();

			/*
			printf("pass %d,rank:\n",tp);
			for (i=0;i<n;i++)
				printf("%d ",ra[i]);putchar('\n');
			*/

		}
		for (i=0;i<n;i++)
			sa[--ra[i]]=i;
	}

	void CH()
	{
		int i,h=0,k;
		for (i=0;i<n;i++)
		{			
			if (ra[i]==0) h=0;
			else
			{
				k=sa[ra[i]-1];
				h=max(h-1,0);
				for (;st[i+h]==st[k+h];h++);
			}
			hi[ra[i]]=h;
			
		}
		
		/*
		printf("Height:\n");
		for (i=0;i<n;i++)
			printf("%d ",hi[ra[i]]);putchar('\n');
		*/
	}
};

SuffixArray SAT;
char A[MAXL],B[MAXL];


void build(char *A,char *B)
{
	int i;
	SAT.n=0;
	for (i=0;A[i];i++) SAT.st[SAT.n++]=A[i];
	SAT.st[SAT.n++]=1;
	for (i=0;B[i];i++) SAT.st[SAT.n++]=B[i];
	SAT.st[SAT.n++]=0;
}

int main()
{
	int la,lb,op;
	int i;
	while (scanf("%s%s",A,B)!=EOF)
	{
		la=strlen(A);
		build(A,B);
		SAT.SA();
		SAT.CH();
		int ans=0;
		for (i=1;i<SAT.n;i++)
		{
			op=(SAT.sa[i-1]<la)+(SAT.sa[i]<la);
			if (op==1)
				ans=max(ans,SAT.hi[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
