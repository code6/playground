
//可删点即加一个映射数组

//Union-Find Set
int parent[MAXN];
int rank[MAXN];

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
