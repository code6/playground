#include<iostream>
#include<queue>

using namespace std;

typedef long long ll;

//AC Machine
const int TSIZE=100+5;
const int CN=4;

struct Trie
{
    int c[CN];
    int fail;
    bool flag;
    void init()
    {
        memset(c,0,sizeof(c));
        fail=-1;
        flag=0;
    }
};

Trie trie[TSIZE];
int len;

void PreProcess()
{
    trie[0].init();
    len=1;
}

int Get(char ch)
{
    switch (ch)
    {
        case 'A':return 0;break;
        case 'T':return 1;break;
        case 'C':return 2;break;
        case 'G':return 3;break;
    }
}

void Insert(char *str,bool id)
{
    int r,no;
    int i;
    r=0;
    for (i=0;str[i];i++)
    {
        no=Get(str[i]);
        if (!trie[r].c[no])
        {
            trie[len].init();
            trie[r].c[no]=len++;
        }
        r=trie[r].c[no];
    }
    trie[r].flag=id;
}

queue<int>que;

void BFS()
{
    while (!que.empty()) que.pop();
    que.push(0);
    int cur,fail,pos;
    int i;
    while (!que.empty())
    {
        cur=que.front();
        que.pop();
        for (i=0;i<CN;i++)
            if (trie[cur].c[i])
            {
                pos=trie[cur].c[i];
                que.push(pos);
                fail=trie[cur].fail;
                while (fail!=-1 && !trie[fail].c[i]) fail=trie[fail].fail;
                if (fail!=-1)
                    trie[pos].fail=trie[fail].c[i];  //very important!
                else
                    trie[pos].fail=0;

                trie[pos].flag|=trie[trie[pos].fail].flag;
            }
            else
            {
                 if (trie[cur].fail!=-1)
                     trie[cur].c[i]=trie[trie[cur].fail].c[i];
            }
    }
}

//AC Machine

const int MOD=100000;

struct Matrix
{
    int mat[TSIZE][TSIZE];
    int n;
    Matrix(int N=1):n(N){}
    void Zero()
    {
        memset(mat,0,sizeof(mat));
    }
    void One()
    {
        int i,j;
        for (i=0;i<n;i++)
            for (j=0;j<n;j++)
                mat[i][j]=(i==j)?1:0;
    }
    void mul(const Matrix &rhs)
    {
        Matrix res(n);
        int i,j,k;
         for (i=0;i<n;i++)
            for (j=0;j<n;j++)
            {
                res.mat[i][j]=0;
                for (k=0;k<n;k++)
                    res.mat[i][j]=(res.mat[i][j]+(ll)mat[i][k]*rhs.mat[k][j])%MOD;
            }
        *this=res;
    }

    void pow(int T)
    {
        Matrix res(n);
        res.One();
        while (T)
        {
            if (T&1) res.mul(*this);
            mul(*this);
            T>>=1;
        }
        *this=res;
    }

    void dump()
    {
        puts("dump");
        int i,j;
        for (i=0;i<n;i++)
        {
            for (j=0;j<n;j++)
                printf("%d ",mat[i][j]);
            putchar('\n');
        }
    }
};

int n,m;
char str[1005];
Matrix M;


int main()
{
    int i,j;
    int cas=0;
  //  freopen("in","r",stdin);
//    freopen("out","w",stdout);
    while (scanf("%d%d",&n,&m)!=EOF)
    {
        cas++;
        PreProcess();
        for (i=0;i<n;i++)
        {
            scanf("%s",str);
            Insert(str,true);
        }
        BFS();
        M.n=len;
        M.Zero();
        for (i=0;i<len;i++)
            if (!trie[i].flag)
            for (j=0;j<CN;j++)
            {
                if (!trie[trie[i].c[j]].flag)
                {
                    M.mat[i][trie[i].c[j]]++;
                }
            }
            
    //  M.dump();
       M.pow(m);
    //  M.dump();
       int ans=0;
       //for (i=0;i<len;i++)
           for (j=0;j<len;j++)
               ans=(ans+M.mat[0][j])%MOD;
       
       printf("%d\n",ans);
    }
    return 0;
}
