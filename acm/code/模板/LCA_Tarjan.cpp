#include<iostream>
#include<vector>

using namespace std;

const int MAXN=10000+5;
const int MAXM=1000000+5;

struct Edge
{
    int a,v;
    Edge(int a1,int v1):a(a1),v(v1){}
};    

struct Query
{
    int p,id;    
    Query(int x,int y):p(x),id(y){}
};    


//Union-Find Set
int parent[MAXN];
int rank[MAXN];
int ancestor[MAXN];
int n,m,c;
vector<Edge>G[MAXN];
vector<Query>Q[MAXN];
bool vis[MAXN];
bool Finish[MAXN];
int dis[MAXN]; 
int ans[MAXM];


void Init(int n)
{
    int i;
    for (i=0;i<n;i++)
    {
        parent[i]=i;
        rank[i]=1;
        ancestor[i]=i;
    }    
}    

int Find(int a)
{
    int b=a,tmp;
    while (a!=parent[a]) a=parent[a];
    while (b!=a)
    {
        tmp=parent[b];
        parent[b]=a;
        b=tmp;
    }    
    return a;
}    

void Union(int a,int b)
{
    a=Find(a);
    b=Find(b);
    if (a==b) return;
    if (rank[a]<rank[b])
    {
        parent[a]=b;
    }    
    else
    {
        parent[b]=a;
        if (rank[a]==rank[b]) rank[a]++;
    }    
}    

//Union-Find Set




void Tarjan(int cur)
{
    vis[cur]=true;        
    int i;
    int v;
    
    for (i=0;i<G[cur].size();i++)
        if (!vis[G[cur][i].a])
        {
            v=G[cur][i].a;  
            dis[v]=dis[cur]+G[cur][i].v;
            Tarjan(v);
            Union(cur,v);
            ancestor[Find(cur)]=cur;
        }    
    Finish[cur]=true;
    for (i=0;i<Q[cur].size();i++)
        if (Finish[Q[cur][i].p])
        {
            v=ancestor[Find(Q[cur][i].p)];           
            if (v!=0)
                ans[Q[cur][i].id]=dis[Q[cur][i].p]+dis[cur]-2*dis[v];                        
            else
                ans[Q[cur][i].id]=-1;
        }    
}    

int main()
{
   // freopen("in","r",stdin);
   // freopen("out","w",stdout);
    
    while (scanf("%d%d%d",&n,&m,&c)!=EOF)
    {
        n++;
        int i,j;        
        int a,b,v;
        
        for (i=0;i<n;i++)
        {
             G[i].clear();
             Q[i].clear();
             vis[i]=Finish[i]=false;
        }    
         
        for (i=1;i<n;i++)
        {
            G[0].push_back(Edge(i,0));
            G[i].push_back(Edge(0,0));
        }   
         
        for (i=0;i<m;i++)
        {
            scanf("%d%d%d",&a,&b,&v);
            G[a].push_back(Edge(b,v));
            G[b].push_back(Edge(a,v)); 
        }                                   
        
        for (i=0;i<c;i++)
        {
            scanf("%d%d",&a,&b);
            Q[a].push_back(Query(b,i));
            Q[b].push_back(Query(a,i));
        }    
        
       // printf("c=%d\n",c);
        
        Init(n);
        dis[0]=0;
        Tarjan(0); 
        for (i=0;i<c;i++)
        {
            if (ans[i]==-1) puts("Not connected");
            else printf("%d\n",ans[i]);
        }                                                                                   
    }
        
    return 0;
}    