#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <queue>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include <cctype>

using namespace std;
typedef long long ll;

//for debug
const int NLIMIT=50000;
const int MLIMIT=50000;

const int INF=100000000;
const int MAXN=50000+100;
const int WHITE=0;
const int MUL=-1;
const int COVER=1;

struct SegNode
{
    int b,e;//begin,end
    int l,r;   //lptr rptr
    int best; //best continuous size
    int lf,rf;    //lfree,rfree
    int tag;     //±ê?? 

	int cnt;   //count 1
	bool empty; 
};    

SegNode tree[2*MAXN];
int ps;
int N,M; 

void Init()
{
    ps=0;
}    

void Build(int f,int r)
{
    ps++;
    int cur=ps;
    tree[cur].b=f;
    tree[cur].e=r;
    tree[cur].lf=tree[cur].rf=tree[cur].best=r-f;    
    tree[cur].tag=WHITE; 

    tree[cur].cnt=0;
	tree[cur].empty=true;
    if (f+1<r)
    {
        int mid=(f+r)/2;
        tree[cur].l=ps+1;
        Build(f,mid);
        tree[cur].r=ps+1;
        Build(mid,r);        
    }    
} 

inline void SetState(int cur,int state)
{
    tree[cur].tag=state;
    if (state==WHITE)
    {
        tree[cur].lf=tree[cur].rf=tree[cur].best=tree[cur].e-tree[cur].b;    
        return;
    }
    if (state==COVER)
    {
        tree[cur].lf=tree[cur].rf=tree[cur].best=0;    
        return;        
    }            
}    

void Spread(int cur)
{
    int lt=tree[cur].l;
    int rt=tree[cur].r;
    int state=tree[cur].tag;
    
    if (state!=MUL)
    {
        SetState(lt,state);
        SetState(rt,state);      
    }                    
}    

void Update(int cur)
{
    int lt=tree[cur].l;
    int rt=tree[cur].r;    
    
    if (tree[lt].tag==tree[rt].tag && tree[lt].tag!=MUL)
    {
        if (tree[lt].tag==WHITE)
            SetState(cur,WHITE);                             
        else
            SetState(cur,COVER);                          
    }    
    else
    {
		tree[cur].lf=(tree[lt].tag==WHITE)? tree[lt].lf+tree[rt].lf:tree[lt].lf;	   
		tree[cur].rf=(tree[rt].tag==WHITE)? tree[lt].rf+tree[rt].rf:tree[rt].rf;	   
        tree[cur].best=max(tree[lt].rf+tree[rt].lf,max(tree[lt].best,tree[rt].best));
        tree[cur].tag=MUL;
    }    
}    

void Insert(int cur,int f,int r)
{
    if (tree[cur].b>=f && tree[cur].e<=r)  //cover all
    {
        SetState(cur,COVER);
        return;              
    }    
    
    if (tree[cur].tag!=MUL)  Spread(cur);  //?ò??′?μY 
    int mid=(tree[cur].b+tree[cur].e)/2;
    if (f<mid)
        Insert(tree[cur].l,f,r);
    if (r>mid)
        Insert(tree[cur].r,f,r);        
    Update(cur);        
}

void Delete(int cur,int f,int r)
{
    if (tree[cur].b>=f && tree[cur].e<=r)  //cover all
    {
        SetState(cur,WHITE);
        return;              
    }    
    
     if (tree[cur].tag!=MUL)  Spread(cur);  //?ò??′?μY 
    int mid=(tree[cur].b+tree[cur].e)/2;
    if (f<mid)
        Delete(tree[cur].l,f,r);
    if (r>mid)
        Delete(tree[cur].r,f,r);        
    Update(cur);        
}


//μ??è?D?? ê?·?óD?a! 
int query(int cur,int sz)
{
    if (tree[cur].b+1==tree[cur].e)  //leaf
            return tree[cur].b;
        
     if (tree[cur].tag!=MUL)  Spread(cur);                                            
            
    int lt=tree[cur].l;
    int rt=tree[cur].r;
        
    if (tree[lt].best>=sz)
            return query(lt,sz);
        
    if (tree[lt].rf+tree[rt].lf>=sz)
        return tree[lt].e-tree[lt].rf;                        
            
    return query(rt,sz);
}   


//for one only

void Spread_One(int cur)
{
	if (tree[cur].empty)  //spread
	{
		tree[tree[cur].l].cnt=tree[tree[cur].r].cnt=0;
		tree[tree[cur].l].empty=tree[tree[cur].r].empty=true;
	}
}

void 	ClearOne()
{
	tree[1].empty=true;
	tree[1].cnt=0;
}

//Modify One
void Modify_One(int cur,int pos,int delta)
{
    if (tree[cur].b==pos && tree[cur].e==pos+1)  //cover all
    {
		tree[cur].cnt+=delta;
		tree[cur].empty=(tree[cur].cnt==0);
         return;              
    }      
	
	Spread_One(cur);   //spread

    int mid=(tree[cur].b+tree[cur].e)/2;
    if (pos<mid)
        Modify_One(tree[cur].l,pos,delta);
	else
        Modify_One(tree[cur].r,pos,delta);        

	tree[cur].cnt=tree[tree[cur].l].cnt+tree[tree[cur].r].cnt;
	tree[cur].empty=(tree[cur].cnt==0);
}


int Find_One_In(int cur,int f,int r)
{
	if (f<=tree[cur].b && r>=tree[cur].e)
	{
		return tree[cur].cnt;
	}

	Spread_One(cur);   //spread

	int res=0;
	int mid=(tree[cur].b+tree[cur].e)/2;
	if (f<mid) res+=Find_One_In(tree[cur].l,f,r);
	if (mid<r) res+=Find_One_In(tree[cur].r,f,r);
	return res;
}


int Find_Kth_One(int cur,int k)
{
	if (tree[cur].cnt<k)
		return INF;

	if (tree[cur].b+1==tree[cur].e) //leaf
	{
		return tree[cur].b;
	}

	Spread_One(cur);   //spread

	if (tree[tree[cur].l].cnt>=k)
		return Find_Kth_One(tree[cur].l,k);
	else
		return Find_Kth_One(tree[cur].r,k-tree[tree[cur].l].cnt);
}

void ResetPro();
void NewPro();
void FreePro();
void GetPro();
   
int main()
{
	int i;
	char buffer[20];
    
    while (scanf("%d%d",&N,&M)!=EOF)
    {
        Init();
        Build(1,N+1);
	   for (i=0;i<M;i++)
	   {
		   scanf("%s",buffer);
		   switch (buffer[0])
		   {
		   case 'R':ResetPro();break;
		   case 'N':NewPro();break;
		   case 'F':FreePro();break;
		   case 'G':GetPro();break;
		   }
	   }
	   printf("\n");
    }    
    return 0;
}    


void ResetPro()
{
	Delete(1,1,N+1);
	ClearOne();
	puts("Reset Now");
}

void NewPro()
{
	int x;
	scanf("%d",&x);
	if (tree[1].best<x)
	{
		puts("Reject New");
		return;
	}
	int pos=query(1,x);
	printf("New at %d\n",pos);
	Insert(1,pos,pos+x);
	Modify_One(1,pos,1);
	Modify_One(1,pos+x-1,1);
}

void FreePro()
{
	int x;
	scanf("%d",&x);
	int cnt=Find_One_In(1,1,x);
	if (cnt%2==0) cnt++;
	int x1=Find_Kth_One(1,cnt);
	int x2=Find_Kth_One(1,cnt+1);
	if (x1==INF || (x<x1 && x1<=N) )
	{
		puts("Reject Free");
		return;
	}
	printf("Free from %d to %d\n",x1,x2);
	Delete(1,x1,x2+1);
	Modify_One(1,x1,-1);
	Modify_One(1,x2,-1);
}

void GetPro()
{
	int x;
	scanf("%d",&x);
	if (!(1<=x && x<=N))
	{
		puts("Error");
	}
	int x1=Find_Kth_One(1,2*x-1);
	if (x1<=N)
	{
		printf("Get at %d\n",x1);
		return;
	}
	puts("Reject Get");
}

