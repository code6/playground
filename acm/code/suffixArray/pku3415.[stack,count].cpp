#include<iostream>
#include<algorithm>


using namespace std;


const int MAXL=200000+500;
const int INF = 1000000;


typedef long long ll;


typedef pair<int,int>PII;
#define mp make_pair
#define two(x) (1<<(x))

int max(int a,int b)
{
	return a>b?a:b;
}
int min(int a,int b)
{
	return a>b?b:a;
}


struct Node
{
    int id;
    int v[2];
};


struct SuffixArray
{
    Node  r[MAXL],br[MAXL];
    int st[MAXL],sa[MAXL],ra[MAXL],hi[MAXL],ct[MAXL];
    int rm[18][MAXL];
    int n;
	
	
    void RS()
    {
        int at,i;
        for (at=1; at>=0; at--)
        {
            memset(ct,0,sizeof(ct));
            for (i=0; i<n; i++) ct[r[i].v[at]]++;
            for (i=1; i<MAXL; i++) ct[i]+=ct[i-1];
            for (i=n-1; i>=0; i--) br[--ct[r[i].v[at]]]=r[i];
            for (i=0; i<n; i++) r[i]=br[i];
        }
		
		
        ra[r[0].id]=1;
        for (i=1; i<n; i++)
        {
            ra[r[i].id]=ra[r[i-1].id];
            if (r[i].v[0]!=r[i-1].v[0] || r[i].v[1]!=r[i-1].v[1])
                ra[r[i].id]++;
        }
    }
	
	
    void SA()
    {
        int i,m;
        for (i=0; i<n; i++)
        {
            r[i].id=i;
            r[i].v[0]=st[i];
            r[i].v[1]=0;
        }
        RS();
        for (m=1; m<n; m<<=1)
        {
            for (i=0; i<n; i++)
            {
                r[i].id=i;
                r[i].v[0]=ra[i];
                r[i].v[1]=(i+m<n)?ra[i+m]:0;
            }
            RS();
        }
        for (i=0; i<n; i++)
            sa[--ra[i]]=i;
    }
    void CH()
    {
        int i,k,h=0;
        for (i=0; i<n; i++)
        {
            if (!ra[i]) h=0;
            else
            {
                k=sa[ra[i]-1];
                h=max(h-1,0);
                for (; st[i+h]==st[k+h]; h++);
            }
            hi[ra[i]]=h;
        }
    }
	
	
    void RM()
    {
        int i,j,lev;
		
		
        for (lev=1; two(lev)<=n; lev++);
        for (i=0; i<n; i++) rm[0][i]=hi[i];
        for (i=1; i<lev; i++)
            for (j=0; j+two(i)<=n; j++)
                rm[i][j]=min(rm[i-1][j],rm[i-1][j+two(i-1)]);
    }
	
	
    int QH(int i,int j)
    {
        if (i>j) swap(i,j);
        i++;
        int lev;
        for (lev=0; i+two(lev)-1<=j; lev++);
        lev--;
        return min(rm[lev][i],rm[lev][j-two(lev)+1]);
    }
} SA;


int m;
char A[MAXL],B[MAXL];
int bsa[MAXL];
int la,lb;








ll calc1()
{
    ll ans=0;
    int ret=0;
    int tp;
	
	
    int i,pos;
    for (pos=0; pos<la; pos++)
    {
        ret=0;
        for (i=0; i<lb; i++)
        {
            tp=SA.QH(SA.ra[pos],SA.ra[la+1+i]);
            if (tp<m) continue;
            ret+=tp-m+1;
        }
        ans+=ret;
    }
	// printf("pos=%d,ret=%d\n",pos,ret);
    return ans;
}




PII S[MAXL];
int ps;


ll calc2()
{
    ll ans=0;
    int i,j,k;
	int cnt,all;
    ll tot;

	//printf("sa:");for (i=0;i<SA.n;i++) printf("%d ",SA.sa[i]);putchar('\n');
	//printf("hi:");for (i=0;i<SA.n;i++) printf("%d ",SA.hi[i]);putchar('\n');
    
    for (i=2; i<SA.n; i++)
		if(SA.hi[i]>=m)
		{
			for (j=i;j<SA.n && SA.hi[j]>=m;j++);

		//	printf("i=%d,j=%d\n",i,j);
		//	for (k=i-1;k<j;k++) printf("%d ",SA.sa[k]);putchar('\n');

			ps=0;
			tot=0;
			all=0;
			for (k=i-1;k<j;k++)
			{
				cnt=0;
				while (ps && S[ps-1].first>SA.hi[k])
				{
					tot-=(ll)(S[ps-1].first-SA.hi[k])*S[ps-1].second;
					cnt+=S[ps-1].second;					
					ps--;
				}
				S[ps++]=mp(SA.hi[k],cnt);
				if (SA.sa[k]<la) //A					
				{
					all++;
					tot+=INF;	
					S[ps++]=mp(INF,1);
				}
				else //B
					ans+=tot-(ll)all*(m-1);		
			}
		
	//		printf("first pass,ans=%I64d\n",ans);
			
			ps=0;
			tot=0;
			all=0;
			for (k=i-1;k<j;k++)
			{
				cnt=0;
				while (ps && S[ps-1].first>SA.hi[k])
				{
					tot-=(ll)(S[ps-1].first-SA.hi[k])*S[ps-1].second;
					cnt+=S[ps-1].second;					
					ps--;
				}
				S[ps++]=mp(SA.hi[k],cnt);
				if (SA.sa[k]>la) //A					
				{
					all++;
					tot+=INF;	
					S[ps++]=mp(INF,1);
				}
				else //B
					ans+=tot-(ll)all*(m-1);		
			}

//			printf("second pass,ans=%I64d\n",ans);

			i=j;
		}
			
		return ans;
}




int main()
{
    int i;
    int np;
	
	
    while (scanf("%d",&m)!=EOF)
    {
        if (!m) break;
        scanf("%s%s",A,B);
        la=strlen(A);
        lb=strlen(B);
        SA.n=0;
        for (i=0; i<la; i++) SA.st[SA.n++]=A[i];
        SA.st[SA.n++]=1;
        for (i=0; i<lb; i++) SA.st[SA.n++]=B[i];
        SA.st[SA.n++]=0;
		
		
        SA.SA();
        SA.CH();
        SA.RM();
		
		
		
		
        np=0;
        for (i=1; i<SA.n; i++)
            if (SA.sa[i]>la)
                bsa[np++]=SA.sa[i];
			
			
			// assert(np==lb);
			
			
			/*
			for (i=0;i<np;i++)
			printf("%d ",bsa[i]);putchar('\n');
			
			  
				for (i=0;i<SA.n;i++) printf("%d ",SA.sa[i]);putchar('\n');
				for (i=0;i<SA.n;i++) printf("%d ",SA.hi[i]);putchar('\n');
			*/
			
			
			
		ll ans;			
		//	 ans=calc1();
		//	printf("%I64d\n",ans);
			ans=calc2();
			printf("%I64d\n",ans);
			
    }
	
	
    return 0;
}

