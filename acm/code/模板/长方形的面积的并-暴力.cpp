#include <iostream>
#include<algorithm>

using namespace std;

const int MAX=1000;

struct Node
{
    int l, r, y;
    bool flag;
    
    bool operator<(const Node&obj)const
    {
        return y<obj.y;
    }
    
};

Node line[2*MAX];
int x[2*MAX];
int n;
int len;

int main()
{
    int x1, y1, x2, y2;
    int i, j;
    
    
    //freopen("in.txt","r",stdin);
    
    while (true)
    {
        n=0;
        while (true)
        {
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            if (x1==-1 && y1==-1 && x2==-1 && y2==-1)
                break;
            line[2*n].l=x1;
            line[2*n].r=x2;
            line[2*n+1].l=x1;
            line[2*n+1].r=x2;
            line[2*n].y=y1;
            line[2*n+1].y=y2;
            line[2*n].flag=false;
            line[2*n+1].flag=true;
            x[2*n]=x1;
            x[2*n+1]=x2;
            n++;
        }
        if (!n)
            break;
        len=2*n;
        
       // printf("len=%d\n",len);
        
        sort(x, x+len);
        sort(line, line+len);
        
        int cnt;
        int now_y;
        int ans=0;
        
        for (i=0;i<len-1;i++)
        {
            cnt=0;
            for (j=0;j<len;j++)
            {
                if (line[j].l<=x[i] && line[j].r>=x[i+1])
                {
                    if (!cnt)
                    {
                        now_y=line[j].y;
                        cnt++;
                    }
                    else
                        if (!line[j].flag)
                        {
                            cnt++;
                        }
                        else
                            cnt--;
                    if (!cnt)
                        ans+=(line[j].y-now_y)*(x[i+1]-x[i]);
                }
            }
        }
        
        printf("%d\n",ans);
        
    }
    return 0;
}