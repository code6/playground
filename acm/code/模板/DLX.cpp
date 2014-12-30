#include<vector>
#include<list>
#include<map>
#include<set>
#include<deque>
#include<queue>
#include<stack>
#include<bitset>
#include<algorithm>
#include<functional>
#include<numeric>
#include<utility>
#include<iostream>
#include<iomanip>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<cctype>
#include<string>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<cstdlib>
#include<ctime>
using namespace std;
#define MAXROW 400
#define MAXCOL 100
const double eps=1e-8;
struct DLX
{
    int r,c;
    DLX *U,*D,*L,*R;
};
struct DLX node[MAXROW*MAXCOL];   
struct DLX row[MAXROW];
struct DLX col[MAXCOL];
struct DLX head;
int cnt;
int size[MAXCOL];
int m,n;
int flag;
inline void addNode(int r,int c)
{
    struct DLX *ptr=&node[cnt++];
    ptr->r=r;
    ptr->c=c;
    ptr->R=&row[r];
    ptr->L=row[r].L;
    ptr->L->R=ptr->R->L=ptr;
    ptr->U=&col[c];
    ptr->D=col[c].D;
    ptr->U->D=ptr->D->U=ptr;
    ++size[c];
}
void init(int r,int c)//row col
{
    int i;
    cnt=0;
    head.r=r;
    head.c=c;
    head.L=head.R=head.U=head.D=&head;
    for(i=0;i<c;++i)
    {
        col[i].r=r;
        col[i].c=i;
        col[i].L=&head;
        col[i].R=head.R;
        col[i].L->R=col[i].R->L=&col[i];
        col[i].U=col[i].D=&col[i];
        size[i]=0;
    }
    for(i=r-1;i>-1;--i)
    {
        row[i].r=i;
        row[i].c=c;
        row[i].U=&head;
        row[i].D=head.D;
        row[i].U->D=row[i].D->U=&row[i];
        row[i].L=row[i].R=&row[i];
    }
}
void remove(DLX *p)
{
    for (DLX *i=p->D; i!=p; i=i->D) {
        i->R->L=i->L;
        i->L->R=i->R;
    }
}
void resume(DLX *p)
{
    for (DLX *i=p->U;i!=p;i=i->U)
    {
        i->R->L=i;
        i->L->R=i;
    }
}
int h()
{
    int an=0;
    DLX *i,*j,*k;
    bool hash[MAXCOL]={0};
    for (i=head.L;i!=&head;i=i->L)
    {
        if (hash[i->c]) continue;
        hash[i->c]=1;
        an++;
        for (j=i->D;j!=i;j=j->D) 
        {
            for (k=j->R;k!=j;k=k->R)
                hash[k->c]=1;
        }
    }
    return an;
}
int ans;
int dfs(int x)
{
    if (x>=ans|x+h()>=ans) return 0;
    if (head.L==&head)
    {
        ans=x;
        return 1;
    }
    DLX *i,*j;
    int mi=1<<30,tc;
    for (i=head.L;i!=&head;i=i->L)
        if (size[i->c]<mi) mi=size[i->c],tc=i->c;
    if (mi==0) return 0;
    for (i=col[tc].D;i!=&col[tc];i=i->D)
    {
        remove(i);
        for (j=i->L;j!=i;j=j->L)
            remove(j);
        if (dfs(x+1))return 1;
        for (j=i->R;j!=i;j=j->R)
            resume(j);
        resume(i);
        if (x+1>=ans)return 0;
    }
    return 0;
}
struct point
{
    double x,y;
    point(){}
    point(double a,double b):x(a),y(b){}
};
int nn,lim;
point aa[20];
vector<point>c;
double dis(point a,point b)
{
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
void findd(point a,point b,double r)
{
    point temp,mid,an;
    double ang,cc;
    mid.x=(a.x+b.x)/2;
    mid.y=(a.y+b.y)/2;
    temp.x=a.x-b.x;
    temp.y=a.y-b.y;
    double ty=dis(a,mid);
    if (r*r<=ty)return;
    cc=sqrt(r*r-ty);
    if(fabs(temp.y)<eps)
    {
        an.x=mid.x;
        an.y=mid.y+cc;
        c.push_back(an);
        an.x=mid.x;
        an.y=mid.y-cc;
        c.push_back(an);
        return;
    }
    ang=atan(temp.x/temp.y);
    an.x=mid.x+cc*cos(ang);
    an.y=mid.y-cc*sin(ang);
    c.push_back(an);
    an.x=mid.x-cc*cos(ang);
    an.y=mid.y+cc*sin(ang);
    c.push_back(an);
}
int check(double md)
{
    int i,j,k;
    c.clear();
    for (i=0;i<nn;i++)
    {
        for (j=i+1;j<nn;j++)
        {
            findd(aa[i],aa[j],md);
        }
    }
    int tmp=c.size();
    int vis[30]={0};
    init(n=tmp+nn,m=nn);
    for (i=0;i<tmp;i++)
    {
    //    printf("%lf %lf\n",c[i].x,c[i].y);
        for (j=0;j<m;j++)
        {
            if (sqrt(dis(c[i],aa[j]))<=md+eps)
            {
                addNode(i,j);
                vis[j]=1;
            }
        }
    }
    for (i=0;i<m;i++)
    {
        if (!vis[i])
        {
            addNode(tmp++,i);
        }
    }
    for (i=0;i<n;i++)
    {
        row[i].L->R=row[i].R;
        row[i].R->L=row[i].L;
    }
    ans=lim+1;
    return dfs(0);
}
int main()
{
    int i,j,k,cas;
    scanf("%d",&cas);
    while (cas--)
    {
        scanf("%d%d",&nn,&lim);
        for (i=0;i<nn;i++)
        {
            scanf("%lf%lf",&aa[i].x,&aa[i].y);
        }
        //printf("%d\n",check(1));
        double high=20,mid,low=0;
        while (fabs(low-high)>=eps)
        {
            mid=(low+high)/2.0;
            if (check(mid))high=mid;
            else low=mid;
        }
        printf("%lf\n",mid);
    }
    return 0;
}
