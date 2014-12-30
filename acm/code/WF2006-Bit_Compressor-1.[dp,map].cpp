#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<map>

using namespace std;
typedef long long ll;
typedef pair<int,int>PII;
typedef map<PII,int>::iterator MIT;

#define MP make_pair

int n,m;
int len;
char st[100];
int flag;

map<PII,int>dp[50];

ll tot_z;  //tot_zero
ll tot_o;  //tot_one
ll tmp_z;  //tmp_zero
ll tmp_o;  //tmp_one
ll new_z;  //new_zero
ll new_o;  //new_one

void update(int pre,int cur,ll tz,ll to)
{    
    MIT it;
    for (it=dp[pre].begin();it!=dp[pre].end();it++)                      
    {                           
          new_z=(it->first).first+tz;                           
          new_o=(it->first).second+to;
                                                                                 
          if (new_z>tot_z || new_o>tot_o) continue;
                           
          // printf("new_z=%d,new_o=%d\n",int(new_z),int(new_o));
                           
          dp[cur][MP((int)new_z,(int)new_o)]+=it->second;                                                                                                                                                                                                                                                          
    }               
}

int main()
{
  //  freopen("36729.in","r",stdin);
  //  freopen("36728.out","w",stdout);
    
    int i,j,k,u,v;
    int cas=0;
    int cnt;
    
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (!n && !m) break;
        cas++;                
        scanf("%s",st);
        scanf("%s",st);
        printf("Case #%d: ",cas);   
        
        len=strlen(st);
        tot_o=m;
        tot_z=n-m;

        if (!tot_z)  //no zero
        {    
            if (st[0]=='0')
            {
                puts("NO");
            }
            else
            {
                if (len==2)
                {
                    if (st[1]=='0')
                        puts("NO");
                    else
                    {
                        if (n==2 || n==3)
                            puts("YES");
                        else
                            puts("NO");
                    }
                }
                else
                {
                 tmp_o=0;
                 for (j=0;j<len;j++) tmp_o=tmp_o*2+st[j]-'0';   
                 if (tmp_o==tot_o)
                     puts("YES");
                 else
                     puts("NO");                
                }
            }
             continue;
        }

        for (i=0;i<len && st[i]=='1';i++);
        if (i==len)  //no zero
        {
            puts("NO");
            continue;                
        }
                
        for (i=0;i<=len;i++) dp[i].clear();                
        dp[0][MP(0,0)]=1;
        
        for (i=0;i<len;i++)                                                                                                                     
          if (st[i]=='0')
          {
              if (i+1<len && st[i+1]=='0') continue;                            
              
              tmp_z=0;
              //j>0
              for (j=i;j>0;j--)  
              {                  
                  if (st[j]=='1') break;
                  
                  tmp_z++;                  
                  if (tmp_z>tot_z) break;                                                                                                                                       
                  
                  for (k=j-1;k>=0;k--)
                  {
                     if (st[k]=='0') continue;
                     if (k>0 && st[k-1]=='1') continue;                                                                   
                     if (j-k==2)
                     {
                          if (st[k+1]=='0') continue ;  //10 is illegal       
                          //for '11',it maybe '11' or '111'...
                          update(k,i+1,tmp_z,2);
                          update(k,i+1,tmp_z,3);
                     }
                     else
                     {                         
                        tmp_o=0;  
                        for (u=k;u<j;u++) tmp_o=tmp_o*2+st[u]-'0';                         
                        update(k,i+1,tmp_z,tmp_o);
                     }                                                                                                                                                                                                                                                                                          
                  }                                                                       
              }    
                            
              //j=0
              if (j==0)  dp[i+1][MP(i+1,0)]++;
          }
          
          int found=0;
          
          if (st[len-1]=='0')  found+=dp[len][(MP(tot_z,tot_o))];
          
          for (i=len-2;i>=0;i--)
            if (st[i]=='0' && st[i+1]=='1')
            {
                if (len-i-1==2)
                {
                  if (st[i+2]=='0') continue;
                  tmp_o=3;
                  if (tmp_o<=tot_o)
                    found+=dp[i+1][(MP(tot_z,tot_o-tmp_o))];    
                  tmp_o=2;
                  if (tmp_o<=tot_o)
                    found+=dp[i+1][(MP(tot_z,tot_o-tmp_o))];    
                }    
                else
                {
                   tmp_o=0;
                   for (j=i+1;j<len;j++) tmp_o=tmp_o*2+st[j]-'0';   
                   if (tmp_o<=tot_o)
                    found+=dp[i+1][(MP(tot_z,tot_o-tmp_o))];   
                }                                                                                                                              
            }    
          
          if (found==1)
            puts("YES");
          else
            if (found==0)
              puts("NO");
            else
              puts("NOT UNIQUE");                                        
    }    
    return 0;
}