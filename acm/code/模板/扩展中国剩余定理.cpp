#include<iostream>

using namespace std;

typedef long long ll;

ll A[15],B[15];
int n;

ll gcd(ll a,ll b)
{
    ll tmp;
    while (b)
    {
        tmp=a%b;
        a=b;
        b=tmp;
    }    
    return a;
}

ll ext_gcd(ll a,ll b, ll&x,ll&y)
{   
    if (!b)
    {
        x=1;y=0;return a;
    }     
    ll d=ext_gcd(b,a%b,x,y);
    ll tmp=x-a/b*y;
    x=y;
    y=tmp;
    return d;
}     

ll MLES(ll&res,ll A,ll B,ll N)
{
    ll x,y;
    ll d=ext_gcd(A,N,x,y);
    if (B%d==0)
    {
        res=B/d*x;
        N/=d;
        res=(res%N+N)%N;
        return d;
    }
    else
    return -1;        
}    


ll Solve(ll A[],ll B[],int n)
{
    ll ra,rb;
    int i; 
    
    ra=A[0];
    rb=B[0];
    
    for (i=1;i<n;i++)
    {
        ll Z=((B[i]-rb)%A[i]+A[i])%A[i];
        ll Y=ra;
        ll X;
        ll M=A[i];
        ll d=MLES(X,Y,Z,M);
        if (d==-1) return -1;
        M/=d; 
        rb=X*ra+rb;
        ra*=M;
        rb%=ra;
      //  cout<<ra<<" "<<rb<<endl;
    }    
    return rb;
}     

int main()
{
 //   freopen("F:\\mytest\\Test\\in.txt","r",stdin);
 //   freopen("F:\\mytest\\Test\\out.txt","w",stdout); 
    
    int i;
    while (scanf("%d",&n)!=EOF)
    {
        for (i=0;i<n;i++)
            scanf("%lld%lld",&A[i],&B[i]);
            
        ll res=Solve(A,B,n);
        if(res!=-1)
            cout<<res<<endl;
        else
            puts("No Solution!");         
    }    
    
    return 0;
}    
