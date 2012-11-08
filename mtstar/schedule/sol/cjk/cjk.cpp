#include <stdio.h>
#include <algorithm>
#include <vector>

using namespace std;

#define NM 1009
#define PP 30

int N,R,P,J,total,T[NM],sum[NM];
int in[NM],use[NM];
int ans, ans_n[PP], ans_val[PP], ans_id[PP][NM];
vector<int> v[NM],w[NM];

void bfs()
{
    int i,j;
    use[J] = 1;
    int op=0, cl=1, p[NM];
    p[0] = J; sum[J] = 0;
    while (op < cl) {
        int x = p[op]; op++;
        for (i=0;i<v[x].size();i++)
        {
            int y = v[x][i];
            sum[y] = sum[x] + T[y];
            p[cl++] = y;
            use[y] = 1;
        }
    }
}

int getMaxUse()
{
    int i,ret=-1,val=-1;
    for (i=0;i<NM;i++)
        if (use[i]==1 && in[i] == 0 && sum[i] > val)
        {
            val = sum[i];
            ret = i;
        }
    return ret;
}

int getMinNoUse()
{
    int i,ret=-1,val=2000000000;
    for (i=0;i<NM;i++)
        if (use[i] == 0 && in[i] == 0 && T[i] < val)
        {
            val = T[i];
            ret = i;
        }
    return ret;
}

void solve()
{
    int i,j,k,l,isnew[PP], now;
    for (i=0;i<P;i++) {
        ans_n[i] = 0;
        ans_val[i] = 0;
        isnew[i] = 1;
    }

  //  for (i=1;i<=N;i++) printf("in %d %d\n", i, in[i]);

    now = 0;
    for (i=0;i<N;)
    {
        int x = -1, val=2000000000;
        for (j=0;j<P;j++)
            if (isnew[j] == 1 && ans_val[j] < val && ans_val[j] >= now) {
                x = j;
                val = ans_val[j];
            }

        isnew[x] = 0;
        if (x >= 0 && ans_n[x] > 0)
        {
            now = ans_val[j];
            int y = ans_id[x][ans_n[x]-1];
            for (j=0;j<w[y].size();j++)
                in[w[y][j]]--;
        }

        k = getMaxUse();
        int getMax = 1;
        if (k < 0) {
            k = getMinNoUse();
            getMax = 0;
        }
        
        if (k > 0 && x >= 0)
        {
            int y = 0;
            for (j=0;j<P;j++) if (isnew[j] == 0 && ans_val[j] < ans_val[y]) y = j;
            if (getMax == 1) y = x;

            ans_val[y] = val+T[k];
            ans_id[y][ans_n[y]] = k;
            ans_n[y] ++;
            in[k] = -1;
            if (k == J)
                ans = ans_val[y];
            isnew[y] = 1;
            i++;
        }
    }
}

void out()
{
    int i,j,k;
    printf("%d\n", ans);
    for (i=0;i<P;i++)
    {
        for (j=0;j<ans_n[i];j++)
        {
            if (j > 0) printf(" ");
            printf("%d", ans_id[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int i,j,k,l;
    freopen("schedule.in", "r", stdin);
    freopen("schedule.out", "w", stdout);
    scanf("%d %d %d %d", &N,&R,&P,&J);
    for (i=0;i<NM;i++) {
        use[i] = -1;
        v[i].clear();
        w[i].clear();
        T[i] = sum[i] = in[i] = 0;
    }
    for (i=1;i<=N;i++) {
        scanf("%d %d", &j,&k);
        T[j] = k;
        use[j] = 0;
    }
    for (i=0;i<R;i++) {
        scanf("%d %d", &j, &k);
        in[k]++;
        w[j].push_back(k);
        v[k].push_back(j);
    }
    bfs();
    solve();
    out();
    return 0;
}
