#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<map>

using namespace std;
typedef long long ll;
typedef map<int,int>::iterator MIT;

#define MP make_pair

int n,m;
int len;
char st[100];
int flag;
int tot_o,tot_z;

map<int,int>dp[45][45][2];

void update(int pre,int prez,int pty,int cur,int curz,int cty,int cadd)
{
	MIT it;
	int tmp;
	for (it=dp[pre][prez][pty].begin();it!=dp[pre][prez][pty].end();it++)
    {
		tmp=cadd+it->first;
		if (tmp>tot_o) break;
		dp[cur][curz][cty][tmp]+=it->second;
	}
}

int main()
{
  //  freopen("36729.in","r",stdin);
  //  freopen("36727.out","w",stdout);
    
    int i,j,k,u;
    int cas=0;	
	 ll last;
    
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        if (!n && !m) break;
        cas++;                
        scanf("%s",st);
        printf("Case #%d: ",cas);   
        
        len=strlen(st);
        tot_o=m;
        tot_z=n-m;      
                
        for (i=0;i<len;i++)
		  for (j=0;j<=tot_z;j++)
			 for (k=0;k<2;k++)
			  dp[i][j][k].clear();

		//init 
		if (st[0]=='0')	
		{
			dp[0][1][0][0]=1;
		}
		else  //st[0]==1
		{
			//j=0		
			dp[0][0][1][1]=1;
			last=1;
			for (i=1;i<len;i++)
			{
				 last=last*2+st[i]-'0';

				 //need some modification
				 if (i==1 && st[i]=='0') continue; // 10 is illegal
				 if (i==1 && st[i]=='1')           // '11' maybe '11','111'
				 {
					 dp[i][0][1][2]=dp[i][0][1][3]=1;
				 }
				 else 
				 {
				   if (last>tot_o) break;
				   dp[i][0][1][(int)last]=1;
				 }
			}			
		}

		//Process
		for (i=1;i<len;i++)
		{			
			for (j=1;j<=min(i+1,tot_z);j++)
				if (st[i]=='0')
				{					
					//turly zero
					update(i-1,j-1,0,i,j,0,0);
					update(i-1,j-1,1,i,j,0,0);


					//part of 1

					//k=i-1 is illegal for '10'
					//k=0 has been calc before
					for (k=i-2;k>0;k--)  
					  if (st[k]=='1')
					  {
						  last=0;
						  for (u=k;u<=i;u++) last=last*2+st[u]-'0';						 						  
						  if (last>tot_o) break;
						  update(k-1,j,0,i,j,1,(int)last);
					  }
				}
				else  //st[i]==1
				{
					for (k=i;k>0;k--)
					  if (st[k]=='1')
					  {										
						 //need some modification		
						 if (k==i-1)  // '11' maybe '11','111'
						 {
							 update(k-1,j,0,i,j,1,2);
							 update(k-1,j,0,i,j,1,3);
						 }
						 else
						 {
							 last=0;
							 for (u=k;u<=i;u++) last=last*2+st[u]-'0';
							 if (last>tot_o) break;
							 update(k-1,j,0,i,j,1,(int)last);
						 }
					  }										
				}
		}
             
		int found=dp[len-1][tot_z][1][tot_o]+dp[len-1][tot_z][0][tot_o];
      // printf("found=%d\n",found);   
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
