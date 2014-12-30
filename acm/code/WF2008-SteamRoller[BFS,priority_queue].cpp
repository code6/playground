#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<queue>

using namespace std;

const int MAX=100+5;
const int INF=1000000000;

const int dir[][2]=
{
    {-1,0},{0,1},{1,0},{0,-1}   
};   

int n,m,r1,c1,r2,c2;
int x[MAX][MAX],y[MAX][MAX];
int cost[MAX][MAX][4];

struct Node
{
    int x,y,d;
    int v;
   
    Node (int a1=0,int b1=0,int c1=0,int e1=0):x(a1),y(b1),d(c1),v(e1){}
       
    bool operator<(const Node&rhs)const
    {
        return v>rhs.v;       
    }               
};   

priority_queue<Node>que;
int vis[MAX][MAX][5];
int ans;
    
int Dij()
{
    ans=INF;
   
    while (!que.empty()) que.pop();   
    memset(vis,-1,sizeof(vis));        
    
	vis[r1][c1][4]=0;
    que.push(Node(r1,c1,4,0));
   
    int i,j;
    int x,y;
    Node cur,tmp;           
    int tmp_ans,last;
   
       
    while (!que.empty())
    {
        cur=que.top();
        que.pop();        
                                    
        if (vis[cur.x][cur.y][cur.d]<cur.v) continue;                               
		
		
        for (i=0;i<4;i++)
         if (i!=cur.d && cost[cur.x][cur.y][i])
		{
		//	printf("Cur.x=%d,cur.y=%d,cur.d=%d,cur.v=%d i=%d\n",cur.x,cur.y,cur.d,cur.v,i);
			tmp.x=cur.x+dir[i][0];
			tmp.y=cur.y+dir[i][1];
			tmp.d=i;
			tmp.v=cur.v+2*cost[cur.x][cur.y][i];
			
			last=0;
			for (j=1;;j++)
			{
			//	printf("tmp.x=%d,tmp.y=%d,tmp.d=%d,tmp.v=%d\n",tmp.x,tmp.y,tmp.d,tmp.v);
				if (vis[tmp.x][tmp.y][tmp.d]==-1 || vis[tmp.x][tmp.y][tmp.d]>tmp.v)
				{
					vis[tmp.x][tmp.y][tmp.d]=tmp.v;
					if (tmp.x==r2 && tmp.y==c2)					
					    ans=min(ans,tmp.v);
					else
						que.push(tmp);		
				}
				
			//	printf("cost=%d\n",cost[tmp.x][tmp.y][tmp.d]);
				if (!cost[tmp.x][tmp.y][tmp.d]) break;
				tmp.v+=2*cost[tmp.x][tmp.y][i]-last;				
				last=cost[tmp.x][tmp.y][i];
				tmp.x+=dir[i][0];
				tmp.y+=dir[i][1];
			}
		}                                                                                                                                                                                                  
    }   
   
    return ans;
}   

int main()
{
    int i,j;
    int cas=0;
   
    freopen("in","r",stdin);
    freopen("out","w",stdout);
   
    while (scanf("%d%d%d%d%d%d",&n,&m,&r1,&c1,&r2,&c2)!=EOF)
    {
        if (!n && !m && !r1 && !c1 && !r2 && !c2) break;               
        cas++;
       
        memset(x,0,sizeof(x));
        memset(y,0,sizeof(y));
       
        for (i=1;i<=n;i++)
        {
            for (j=1;j<m;j++)
              scanf("%d",&y[i][j]);
            if (i<n)
              for (j=1;j<=m;j++)
               scanf("%d",&x[i][j]);              
        } 
       
        memset(cost,0,sizeof(cost));                                                                                                                           
       
        for (i=1;i<=n;i++)
          for (j=1;j<=m;j++)
          {
              cost[i][j][0]=x[i-1][j];
              cost[i][j][1]=y[i][j];
              cost[i][j][2]=x[i][j];
              cost[i][j][3]=y[i][j-1];             
           //   printf("i=%d,j=%d:%d %d %d %d\n",i,j,cost[i][j][0],cost[i][j][1],cost[i][j][2],cost[i][j][3]);
          }   
       
        printf("Case %d: ",cas);
        int ans=Dij();
        if (ans==INF)
          puts("Impossible");
        else
         printf("%d\n",ans);
    }   
    return 0;
}
