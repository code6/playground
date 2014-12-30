//pku 2201
#include<iostream>
#include<algorithm>
using namespace std;

const int MAX=50000+5;

struct Node
{
    int x,y;
};    

Node data[MAX];
int pos[MAX],rp[MAX];
int n;

bool cmp_x(int a,int b)
{
    return data[a].x<data[b].x;
}

struct Treap
{
    int lf,rf,fa;
};    

Treap tr[MAX];
int root,ins;

void Print(int v)
{
    printf("(");
    if (tr[v].lf!=-1) Print(tr[v].lf);
    printf("%d/%d",data[pos[v]].x,data[pos[v]].y);
    if (tr[v].rf!=-1) Print(tr[v].rf);
    printf(")");
}    

int main()
{
    int i;
    
 //  freopen("F:\\mytest\\Test\\in.txt","r",stdin);
  //  freopen("F:\\mytest\\Test\\out.txt","w",stdout);
    
    scanf("%d",&n);
    for (i=0;i<n;i++)
    {    
        scanf("%d%d",&data[i].x,&data[i].y);
        pos[i]=i;
    }    
    sort(pos,pos+n,cmp_x);
    for (i=0;i<n;i++) rp[pos[i]]=i;
    tr[0].lf=tr[0].rf=-1;
    tr[0].fa=-1;
    root=ins=0;
    for (i=1;i<n;i++)
    {
        if (data[pos[i]].y<data[pos[root]].y)
        {
            tr[i].lf=root;
            tr[i].rf=-1;
            tr[i].fa=-1;
            tr[root].fa=i;
            root=ins=i;
        }
        else
        {
            while (data[pos[i]].y<data[pos[ins]].y) ins=tr[ins].fa;
            tr[i].fa=ins;
            tr[i].lf=tr[i].rf=-1;
            if (tr[ins].rf!=-1)
            {
                tr[i].lf=tr[ins].rf;
                tr[tr[ins].rf].fa=i;
            }                        
            tr[ins].rf=i;
            ins=i;            
        }        
    } 
    
 //   Print(root);printf("\n");         
    
    printf("YES\n");
    for (i=0;i<n;i++)
    {        
        int id=rp[i];
      //  printf("rp[%d]=%d,pos[%d]=%d, (%d %d):%d %d %d\n",i,rp[i],i,pos[i],data[pos[id]].x,data[pos[id]].y,tr[id].fa,tr[id].lf,tr[id].rf);
        if (tr[id].fa!=-1) printf("%d ",pos[tr[id].fa]+1); else printf("0 ");
       if (tr[id].lf!=-1) printf("%d ",pos[tr[id].lf]+1); else printf("0 ");
       if (tr[id].rf!=-1) printf("%d\n",pos[tr[id].rf]+1); else printf("0\n");
        
    } 
    
    return 0;
}    