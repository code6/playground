#include<iostream>
#include<stdio.h>
#include<string.h>
#include<set>
#include<map>
#include<string>
#include<math.h>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX = 1000+5;

vector<int>g[MAX];
int n;

int mat[MAX];
bool vis[MAX];

int hungry_aug(int cur)
{
	if (vis[cur]) return 0;
	vis[cur]=1;
	int i;
	for (i=0;i<g[cur].size();i++)
		if (mat[g[cur][i]]==-1 || hungry_aug(mat[g[cur][i]]))
		{
			mat[g[cur][i]]=cur;
			return true;
		}
	return false;
}

int hungry()
{
	int i,ans;
	ans=0;
	memset(mat,-1,sizeof(mat));
	for (i=0;i<n;i++)
	{
		memset(vis,0,sizeof(vis));
		ans+=hungry_aug(i);
	}
	return ans;
}

char Name[MAX][50];
int ty[MAX];
int rank[MAX];
bool show[MAX];

int main()
{
	scanf("%d",&n);
	//while (scanf("%d",&n)!=EOF)
	{
		int i,j;
		char buffer[25];
		for (i=0;i<n;i++)
			g[i].clear();

		for (i=0;i<n;i++)
		{
			scanf("%s%s%d",Name[i],buffer,&rank[i]);
			if (buffer[0]=='a') ty[i]=3;
			else
				if (buffer[0]=='t') ty[i]=2;
				else
					ty[i]=1;
		}

		for (i=0;i<n;i++)
			for (j=i+1;j<n;j++)
				if (abs(rank[i]-rank[j])==2)
					if (ty[i]==3 || ty[j]==3 || (ty[i]+ty[j]==3))
					{
						g[i].push_back(j);
						g[j].push_back(i);
					}

		int ans=hungry()/2;
		memset(show,0,sizeof(show));
		printf("%d\n",ans);
		for (i=0;i<n;i++)
			if (mat[i]!=-1 && !show[i])
			{
				if (ty[i]==1)
				{
					printf("%s %s\n",Name[i],Name[mat[i]]);
				}
				else
				{
					if (ty[mat[i]]==1)
						printf("%s %s\n",Name[mat[i]],Name[i]);
					else
					{
						if (ty[i]==3)
							printf("%s %s\n",Name[i],Name[mat[i]]);
						else
							printf("%s %s\n",Name[mat[i]],Name[i]);
					}
				}
				show[i]=show[mat[i]]=true;
			}
	}

	return 0;
}