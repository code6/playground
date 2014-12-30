#include<iostream>
#include<cstring>
#include<map>

using namespace std;

#define MAX 500005

int next[MAX];

void Init(int n)
{
	int i;
	for (i=0;i<n;i++) next[i]=i;
}

int Find(int a)
{
	int b=a,tmp;
	while (a!=next[a]) a=next[a];
	while (b!=a) 
	{
		tmp=next[b];
		next[b]=a;
		b=tmp;
	}
	return a;
}

void Del(int a)
{
	if (next[a]!=a) return;
	next[a]=next[a-1];
}

char S[MAX];
int A[MAX];
int len;

int main()
{
	//freopen("36767.in","r",stdin);
	int i,j,k;

    while (scanf("%s",S)!=EOF)
    {     
        len=strlen(S);
        A[0]=len;
        j=0;
        while (S[0+j]==S[1+j]) j++;
        A[1]=j;

        k=1;
        for (i=2; i<len; i++)
        {
            if (i+A[i-k]-1<k+A[k]-1)
                A[i]=A[i-k];
            else
            {
                j=max(0,k+A[k]-i);
                while (S[0+j]==S[i+j]) j++;
                A[i]=j;
                k=i;
            }
        }

		Init(len);

		int cnt=0;
		int pos;

		for (i=1;i<=len;i++)
		//	if (A[len-i]==i)
		{			
			int last=i;
			while (last<len)
			{
				cnt++;
				pos=Find(last);
				while (A[pos]<i)
				{
					Del(pos);
					pos=Find(pos);
				}

				if (pos+i>last)
					last=pos+i;
				else
					break;			
			}
			if (last>=len) break;
		}

		printf("%d\n",i);
		//printf("times=%d\n",cnt);
    }

    return 0;
}
