#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

const int MAX=1000+5;

int bad[1<<7];
int type[10][MAX];
int n,m;
char buffer[100];
int mask[20];
int dp[1005][1<<7];

void DFS(int pos,int dep,int val,int cs,int ps)
{   
    if (bad[cs]) return; 
    
    if (dep==7)
    {
        dp[pos][cs]=max(dp[pos][cs],val);
        return;
    }    
    
    switch(type[dep][pos])
    {
        case 0:
            DFS(pos,dep+1,val,cs,ps);  //no push
            break;
        case 1:
            DFS(pos,dep+1,val,cs,ps);  //no push
            DFS(pos,dep+1,val+1,cs|mask[dep],ps);  //push
            break;
        case 2:
            if (type[dep][pos-1]!=2) //begin
            {
                DFS(pos,dep+1,val,cs,ps);//no push
                DFS(pos,dep+1,val+1,cs|mask[dep],ps);//push
            }                     
            else
            {
                DFS(pos,dep+1,val,cs,ps);//no push
                if (ps&mask[dep])
                    DFS(pos,dep+1,val,cs|mask[dep],ps);//push                         
            }    
            break;
        case 3:   
            //no push
            if (ps&mask[dep])
               DFS(pos,dep+1,val+1,cs,ps);
            else
                DFS(pos,dep+1,val,cs,ps);              
            DFS(pos,dep+1,val,cs|mask[dep],ps);//push                 
            break;
    }                                                                                                              
}    

int main()
{       
    int t,cas=0;
    int i,j,k;
    int tot;
    int a,b;
    
//    freopen("36767.in","r",stdin);
//    freopen("36767.out","w",stdout);

    
    mask[0]=1;
    for (i=1;i<20;i++) mask[i]=mask[i-1]*2;
    
    scanf("%d",&t);
    while (t--)
    {
        
        memset(type,0,sizeof(type));
        
        cas++;
        scanf("%d",&n);
        for (i=0;i<7;i++)
        {
            scanf("%d",&tot);
          //  printf("i=%d,tot=%d\n",i,tot);
            while (tot--)
            {
                scanf("%s",buffer);
                if (strchr(buffer,'-'))
                {
                    sscanf(buffer,"%d-%d",&a,&b);
                  //  printf("i=%d a=%d,b=%d\n",i,a,b);
                    for (j=a;j<b;j++) type[i][j]=2;
                    type[i][b]=3;
                }
                else    
                {                    
                    sscanf(buffer,"%d",&a);
                 //   printf("i=%d,a=%d\n",i,a);
                    type[i][a]=1;
                }    
            }    
        }
        
        memset(bad,0,sizeof(bad));
        scanf("%d",&m);
        for (i=0;i<m;i++)                
        {
            scanf("%s",buffer);
            a=0;
            for (j=6;j>=0;j--) a=a*2+buffer[j]-'0';            
            bad[a]=1;            
        }    

        
        for (i=0;i<mask[7];i++)
          for (j=0;j<mask[7];j++)
             if ( (i&j)==j)
                bad[i]|=bad[j];   
        
  //      for (i=0;i<mask[7];i++)
//         if (bad[i])
//          printf("bad=%d\n",i);  
                
        memset(dp,-1,sizeof(dp));
        
        dp[0][0]=0;
        for (i=0;i<n;i++)
          for (j=0;j<mask[7];j++)
             if (dp[i][j]!=-1)
               DFS(i+1,0,dp[i][j],0,j);     
       
       int ans=0;
       for (i=0;i<mask[7];i++)                                                                                                                                                             
          ans=max(ans,dp[n][i]);
          
       printf("Case #%d: %d\n",cas,ans); 
       
    }     
    return 0;
}
