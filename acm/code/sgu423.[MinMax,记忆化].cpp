#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstdlib>
#include<map>

using namespace std;

const int MAX=20;
const int INF=100000000;

int n,s,t;
int mask[MAX];
int g[MAX][MAX];
int v[MAX];
int se[MAX];
int ne[1<<20];
int tot[1<<20];

struct Node
{
    int who,sa,sb;
    Node(int w,int s1,int s2):who(w),sa(s1),sb(s2){}
    bool operator<(const Node&rhs) const
    {
        if (who!=rhs.who) return who<rhs.who;
        if (sa!=rhs.sa) return sa<rhs.sa;
        return sb<rhs.sb;
    }    
};    
map<Node,int>M;

int MinMax(int who,int sa,int sb)
{
   // printf("who=%d,sa=%d,sb=%d\n",who,sa,sb);
    
    if (M.find(Node(who,sa,sb))!=M.end())
       return M[Node(who,sa,sb)];
       
    int &ret=M[Node(who,sa,sb)];
    int i,j,tmp;
    
    for (i=0;i<mask[n];i++)
      if ( (!(i&sa)) && (!(i&sb)) )
      {
           if (tot[sa&ne[i]]>tot[i]+tot[sb&ne[i]]) break;
            if (tot[sb&ne[i]]>tot[i]+tot[sa&ne[i]]) break;
      }              
      
    if (i==mask[n])  //no legal move exist
    { 
       // printf("sa=%d,sb=%d val=%d\n",sa,sb,tot[sa]-tot[sb]);
        return ret=(tot[sa]-tot[sb]);       
    }    
                    
    if (who==0) //s
    {
        ret=-INF;         
        for (i=0;i<mask[n];i++)
          if ( (!(i&sa)) && (!(i&sb)) )
          {
              if (tot[sa&ne[i]]>tot[i]+tot[sb&ne[i]]) //can eat
              {
                  tmp=MinMax(1-who,sa|i,sb);
                  if (ret<tmp) ret=tmp;                                    
              }    
          }      
          
       if (ret==-INF)
          ret=MinMax(1-who,sa,sb);         
    }
    else  //t
    {
        ret=INF;
        for (i=0;i<mask[n];i++)
          if ( (!(i&sa)) && (!(i&sb)) )
          {
               if (tot[sb&ne[i]]>tot[i]+tot[sa&ne[i]]) //can eat
              {
                  tmp=MinMax(1-who,sa,sb|i);
                  if (ret>tmp) ret=tmp;                                    
              }    
          }      
        if (ret==INF)
          ret=MinMax(1-who,sa,sb);     //no move
    }   
    
    return ret;     
}    

int main()
{
    int i,j;
    
    mask[0]=1;
    for(i=1;i<MAX;i++) mask[i]=mask[i-1]*2;
    
//    freopen("36727.in","r",stdin);
//    freopen("36727.out","w",stdout);

    
    while (scanf("%d%d%d",&n,&s,&t)!=EOF)
    {
        s--;t--;
        for (i=0;i<n;i++)
        {
            se[i]=0;
          for (j=0;j<n;j++)
          {
            scanf("%1d",&g[i][j]);
            se[i]|=g[i][j]*mask[j];
          }    
        }                                                                              
                            
        for (i=0;i<n;i++) scanf("%d",&v[i]);
                        
        for (i=0;i<mask[n];i++)
        {
            tot[i]=0;
            ne[i]=0;
            
            for (j=0;j<n;j++)        
              if (mask[j]&i)
              {
                tot[i]+=v[j];
                ne[i]|=se[j];
              }                                                
            ne[i]&=~i;                           
        //    printf("ne[%d]=%d\n",i,ne[i]);
        }       
        
        M.clear();
        
        int ans= MinMax(0,mask[s],mask[t]);
        
        printf("%d\n",ans);                                                                                                                                                                                                                                                                                                                                                                          
    }    
    
    return 0;
}    