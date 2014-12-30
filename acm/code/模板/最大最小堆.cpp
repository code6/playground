//fzu 1209 最小权无前缀语言问题
#include<iostream>
#include<algorithm>
#include<queue>
#include<functional>
#include <set>
#include <map>

using namespace std;

const int MAXM = 5000 + 5;
const int INF = 100000000;

struct MinMumQueue
{
    map<int,int>mp;
	int sz;

    MinMumQueue()
    {
		sz=0;
    }

    bool empty()
    {
        return sz==0;
    }

    int size()
    {
        return sz;
    }

    void erase(int v)
    {
        map<int,int>::iterator it;
        it=mp.find(v);
        if (it!=mp.end())
        {
			sz--;
            it->second--;
            if (!(it->second))
                mp.erase(it);
        }
    }

    void insert(int v)
    {
        mp[v]++;
		sz++;
    }

    int min()
    {
        return (mp.begin())->first;
    }

    int max()
    {
        return (--mp.end())->first;
    }

    void Clear()
    {
        mp.clear();
		sz=0;
    }

    int sum()
    {
        map<int,int>::iterator it;
        int res = 0;
        for (it = mp.begin(); it != mp.end(); it++)
            res += it->first;
        return res;
    }
};

int v[MAXM];
int n, m;
int ans, best;
MinMumQueue que;

int main()
{
    int i;
    int val;

    //  freopen("in","r",stdin);
    //   freopen("out","w",stdout);

    while (scanf("%d%d", &n, &m) != EOF)
    {
        for (i = 0; i < m; i++) scanf("%d", &v[i]);
        sort(v, v + m);
        que.Clear();
        que.insert(0);
        int res=0;
        int best=INF;
        while (true)
        {
            val=que.min();
            que.erase(val);
            res-=val;
            for (i=0;i<m;i++)
            {
                que.insert(val+v[i]);
                res+=val+v[i];
            }
            
            while (que.size()>n)
            {
                val=que.max();
                res-=val;
                que.erase(val);
            }

            if (que.size()<n) continue;
            if (best>res) best=res;
            else break;
        }
        

        printf("%d\n", best);
    }
    return 0;
}
