#include<iostream>
#include<assert.h>

using namespace std;

typedef long long ll;
const int MAX=100000+50;
const int MSZ=4;
typedef ll Matrix[MSZ][MSZ];


char st[MAX];
ll n,m,mod, ba,ca,cb,cc,ce,cf;
ll Ca[MAX];

ll mod_mul(ll a,ll b)
{
    a%=mod;
    b%=mod;
    return ((a*b)%mod+mod)%mod;
}

ll mod_add(ll a,ll b)
{
    a%=mod;
    b%=mod;
    return ((a+b)%mod+mod)%mod;
}

ll mod_sub(ll a,ll b)
{
    a%=mod;
    b%=mod;
    return ((a-b)%mod+mod)%mod;
}

ll ext_gcd(ll a, ll b, ll &x, ll &y)
{
    ll t, d;
    if (b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    d = ext_gcd(b, a % b, x, y);
    t = x;
    x = y;
    y = t - a / b*y;
    return d;
}

ll inv(ll v)
{
	ll x,y,d;
	d=ext_gcd(v,mod,x,y);
	assert(d==1) ;
	return mod_add(x,0);
}


ll pw(ll a,ll b,ll c)
{
    ll ret=1;
    a%=c;
    while (b)
    {
        if (b&1)
        {
            ret=((ll)ret*a)%c;
        }
        a=((ll)a*a)%c;
        b>>=1;
    }
    return ret;
}

void Show(Matrix a)
{
    int i,j;
    puts("dump:");
    for (i=0; i<MSZ; i++,putchar('\n'))
        for (j=0; j<MSZ; j++)
            cout<<a[i][j]<<" ";
}

void mu_M(Matrix a,Matrix b)
{
    Matrix c;
    int i,j,k;
    for (i=0; i<MSZ; i++)
        for (j=0; j<MSZ; j++)
        {
            c[i][j]=0;
            for (k=0; k<MSZ; k++)
                c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
        }

    memcpy(a,c,sizeof(c));

}


void pw_M(Matrix a,ll T)
{
    Matrix b;
    memset(b,0,sizeof(b));
    b[0][0]=b[1][1]=b[2][2]=1;
    while (T)
    {
        if (T&1) mu_M(b,a);
        mu_M(a,a);
        T>>=1;
    }
    memcpy(a,b,sizeof(b));
}

Matrix ma;

//(sigma ba^i)%mod  i=0..T
ll solve_ca(ll ba,ll T)
{
    memset(ma,0,sizeof(ma));
    ma[0][0]=ma[0][1]=1;
    ma[1][1]=ba;
//	Show(ma);
    pw_M(ma,T);
//	Show(ma);
    ll ret=(ma[0][0]+ma[0][1]*ba)%mod;
    return ret;
}


//(sigma i*ba^i)%mod  i=0..T
ll solve_cb(ll ba,ll T)
{
    memset(ma,0,sizeof(ma));
    ma[0][0]=ma[0][1]=1;
    ma[1][1]=ba;
    ma[1][2]=1;
    ma[2][2]=ba;
    //Show(ma);
    pw_M(ma,T);
//	Show(ma);
    ll ret=(ma[0][1]*ba+(ma[0][2]*ba%mod)*ba)%mod;
    return ret;
}


//(sigma i*i*ba^i)%mod  i=0..T
ll solve_cc(ll ba,ll T)
{
    memset(ma,0,sizeof(ma));
    ma[0][0]=ma[0][1]=1;
    ma[1][1]=ba;
    ma[1][2]=1;
    ma[2][2]=ba;
    ma[2][3]=1;
    ma[3][3]=ba;
//	Show(ma);
    pw_M(ma,T);
//	Show(ma);
    ll cof[4];
    cof[0]=0;
    cof[1]=ba%mod;
    cof[2]=(cof[1]*cof[1])%mod;
    cof[3]=(2*cof[1]*cof[2])%mod;
    cof[2]=(cof[2]*3)%mod;

    ll ret=0;

    int i;
    for (i=0; i<4; i++) ret=(ret+cof[i]*ma[0][i])%mod;

    return ret;
}



ll solve_ce()
{
    if (m==1) return 0;
    return mod_sub((m-1)*ca,cb);
}

ll solve_cf()
{
    if (m==1) return 0;
    ll ret=(((m*(m-1)%mod)*ca-cb-cc)%mod+mod)%mod;
    if (ret%2==0) ret/=2;
    else
    {
        ret=mod_mul(ret,inv(2));
    }
    return ret;
}

ll F(int i)
{
	if (m==1) return Ca[i];
	else
		return mod_add(Ca[i]*ca,Ca[n-1]*ce);
}

ll G(int i)
{
	if (m==1) return 0;
	else
		return mod_add(Ca[i]*cb,Ca[n-1]*cf);
}


int main()
{
    int i,j;

 //   freopen("in","r",stdin);
 //   freopen("out","w",stdout);

    scanf("%s",st);
    n=strlen(st);
    for (i=0; i<n/2; i++) swap(st[i],st[n-1-i]);

    //scanf("%d%d",&m,&mod);
    cin>>m>>mod;

    ba=pw(10,n,mod);


    ca=solve_ca(ba,m-1);
    cb=solve_cb(ba,m-1);
    cc=solve_cc(ba,m-1);
    ce=solve_ce();
    cf=solve_cf();

	/*
    cout<<"ca="<<ca<<endl;
    cout<<"cb="<<cb<<endl;
    cout<<"cc="<<cc<<endl;
	cout<<"ce="<<ce<<endl;
	cout<<"cf="<<cf<<endl;
	*/


    ll res,cur,tmp;
    ll v,cv,da,db;

    Ca[0]=1;
    cv=1;
    for (i=1; i<n; i++)
    {
        cv=mod_mul(cv,10);
        Ca[i]=mod_add(Ca[i-1],cv);
    }

    res=0;
    for (i=0; i<n; i++)
    {
        //cout<<"i="<<i<<endl;

        cur=st[i]-'0';       
        da=mod_sub(n*m,i);
		db=n;

       // cout<<"da="<<da<<" "<<"db="<<db<<endl;
		tmp=mod_sub(da*F(i),db*G(i));
	//	cout<<"F="<<F(i)<<" G="<<G(i)<<endl;

		cur=mod_mul(cur,tmp);
       // cout<<"cur="<<cur<<endl;

        res=mod_add(res,cur);

    }

    cout<<res<<endl;

    return 0;
}

/*
Periodic Sum
*/