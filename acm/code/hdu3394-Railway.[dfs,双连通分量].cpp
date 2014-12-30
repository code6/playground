#include<iostream>
#include<vector>

using namespace std;

const int MAXE=100000+50;
const int MAXN=10000+50;

struct Edge
{
    int a,b; 
    int oth(int v)
    {
        if (a==v) return b;
        return a;
    }
};

int n,m;
Edge E[MAXE];
vector<int>G[MAXN];

int vis[MAXN];
int low[MAXN],depth[MAXN];
int S[MAXE],ps;
int vet[MAXN],gv;
int ga,gb;


void dfs(int cur,int fa,int dep)
{
	vis[cur]=1;
	depth[cur]=dep;
	low[cur]=dep;

	int i,id,ne,et,vt;	
	for (i=0;i<G[cur].size();i++)
	{
		id=G[cur][i];
		ne=E[id].oth(cur);
		if (ne==fa) continue;			

		if (vis[ne]==0)
		{
			S[ps++]=id;
			dfs(ne,cur,dep+1);
			low[cur]=min(low[cur],low[ne]);

			if (low[ne]>depth[cur])  
				ga++;
		
			if (low[ne]>=depth[cur])
			{
				et=vt=0;
				gv++;
			//	printf("new pair:\n");
				while (true)
				{
					et++;
					//printf("id=%d,a=%d,b=%d\n",S[ps-1],E[S[ps-1]].a,E[S[ps-1]].b);
					if (vet[E[S[ps-1]].a]!=gv) 
					{
						vet[E[S[ps-1]].a]=gv;
						vt++;
					}
					if (vet[E[S[ps-1]].b]!=gv) 
					{
						vet[E[S[ps-1]].b]=gv;
						vt++;
					}				
					if (S[--ps]==id) break;
				}
			//	printf("et=%d,vt=%d\n",et,vt);
				
				if (et>vt) gb+=et;
			}
		}
		else
		{			
			if (vis[ne]==1) //back edge
			{
				S[ps++]=id;
				low[cur]=min(low[cur],depth[ne]);
			}
		}
	}
	vis[cur]=2;
}

int main()
{
    int i,j; 
    int a,b;
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (!n && !m) break;
        
        ga=gb=gv=0;
		memset(vet,0,sizeof(vet));
        for (i=0;i<n;i++) G[i].clear();
        for (i=0;i<m;i++)
        {
            scanf("%d%d",&a,&b);
            E[i].a=a;E[i].b=b;
            G[a].push_back(i);
            G[b].push_back(i);
        }
		
		ps=0;
		memset(vis,0,sizeof(vis));		
		for (i=0;i<n;i++)
			if (!vis[i])
				dfs(i,-1,0);        
        printf("%d %d\n",ga,gb);
    }
    return 0;
}

/*
12 17
0 1
0 2
1 2
3 4
3 5
4 5
6 7
6 8
7 8
9 10
9 11
10 11
2 8
8 11
11 5
5 2
2 11
*/

/*
9 11
8 1
8 2
1 2
2 3
3 4
2 4
2 7
2 5
5 7
6 7
6 5
*/