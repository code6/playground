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
#include <assert.h>

using namespace std;
typedef long long ll;

const double PI=acos(-1.0);
const double eps=1e-11;

#define dump(x) cerr<<#x<<" = "<<(x)<<endl;
#define foreach(c,itr) for (__typeof( (c).begin() ) itr=(c).begin();itr!=(c).end() ;itr++ )


int countbit(int n) {return (n==0)?0:1+countbit(n&(n-1));}
int lowbit(int n) {return n&(n^(n-1));}
string toString(ll v) { ostringstream sout;sout<<v;return sout.str();}
string toString(int v) { ostringstream sout;sout<<v;return sout.str();}
int Rand16(){return rand();}
int Rand32(){return rand()*rand();}
double DRand(){return (double)rand()/RAND_MAX;}
int RandRange(int f,int r){return f+(int)(DRand()*(r-f)+0.5);}

/*
初始时刻1到n个数排成一列,1<=n<=10^8.
1,2,3,...n.
Q(1<=Q<=50000)个询问,3种类型
1 Top x 将x掉到队头
2 Query x 询问x在那个位置
2.Rank x 查第x位是谁
*/

const int NULLNODE=0;
const int MAX=100000+50;

struct TreapNode
{
	int left,right;
	int key,pro;	
	int size,weight;

	void init(int v)
	{
		left=NULLNODE;
		right=NULLNODE;
		key=v;
		size=weight=1;
		pro=rand();
	}

} tnode[MAX];
int tcnt;

void TreapInit()
{
	srand(time(NULL));
	memset(&tnode[0],0,sizeof(tnode[0]));
	tcnt=1;
}

int getTreapNode(int v)
{
	tnode[tcnt].init(v);
	return tcnt++;
}

struct Treap
{
	int root;

	void init()
	{		
		root=NULLNODE;
	}

	bool empty()
	{
		return root==NULLNODE;
	}

	int size()
	{
		if (empty()) return 0;
		return tnode[root].size;
	}

	bool contain(int v)
	{
		return contain(root,v);
	}

	bool contain(int x,int v)  //尾递归...
	{
		if (x==NULLNODE)
			return false;

		if (v<tnode[x].key) 
			return contain(tnode[x].left,v);
		else
			if (v>tnode[x].key)
				return contain(tnode[x].right,v);
			else
				return true;
	}

	void insert(int v)
	{
		insert(root,v);
	}

	//insert at pos x with value v,assign new root to x
	void insert(int &x,int v)
	{
		if (x==NULLNODE)
		{
			x=getTreapNode(v);
			return;
		}

		tnode[x].size++;

		if (v<tnode[x].key)
		{
			insert(tnode[x].left,v);
			if (tnode[tnode[x].left].pro<tnode[x].pro)
				rotateWithLeftChild(x);
		}
		else
		{
			if (v>tnode[x].key)
			{
				insert(tnode[x].right,v);
				if (tnode[tnode[x].right].pro<tnode[x].pro)
					rotateWithRightChild(x);
			}
			else //already exist
			{
				tnode[x].weight++;
			}
		}
	}

	void remove(int v)
	{
		if (!contain(v)) return;
		remove(root,v);
	}

	//remove at pos x with val v,assign new root to x
	void remove(int &x,int v)
	{
		tnode[x].size--;

		if (v<tnode[x].key)
			remove(tnode[x].left,v);
		else
			if (v>tnode[x].key)
				remove(tnode[x].right,v);
			else
			{

				tnode[x].weight--;			

				if (tnode[x].weight==0) //truly remove
					erase(x);				
			}
	}

	//truly remove pos x
	void erase(int& x)
	{
		if (tnode[x].left==NULLNODE && 
			tnode[x].right==NULLNODE)  //leaf
			x=NULLNODE;
		else
			if (tnode[x].left==NULLNODE)
				x=tnode[x].right;
			else
				if (tnode[x].right==NULLNODE)
					x=tnode[x].left;
				else
				{
					if (tnode[tnode[x].left].pro<tnode[tnode[x].right].pro)
					{
						rotateWithLeftChild(x);
						erase(tnode[x].right);
					}
					else
					{
						rotateWithRightChild(x);
						erase(tnode[x].left);
					}
				}
	}

	int find_kth(int r)
	{
		if (r>size()) return -1; //no find
		return find_kth(root,r);
	}

	int find_kth(int x,int v)
	{
		if (tnode[x].size<v) return -1;

		if (tnode[tnode[x].left].size>=v)
			return find_kth(tnode[x].left,v);

		if (tnode[tnode[x].left].size+tnode[x].weight<v)
			return find_kth(tnode[x].right,v-(tnode[tnode[x].left].size+tnode[x].weight));

		return tnode[x].key;
	}

	int find_max(int x)
	{
		if (x==NULLNODE)
			return -1;
		if (tnode[x].right!=NULLNODE)
			return find_max(tnode[x].right);
		return tnode[x].key;
	}

	int rank(int v)
	{
		return rank(root,v);
	}

	int rank(int x,int v)
	{
		if (x==NULLNODE)
			return 0;
		if (v<tnode[x].key)
			return rank(tnode[x].left,v);
		else
			return tnode[tnode[x].left].size+tnode[x].weight+rank(tnode[x].right,v);
	}

	void rotateWithLeftChild(int &x)
	{
		int y=tnode[x].left;
		tnode[x].left=tnode[y].right;
		tnode[y].right=x;
		tnode[x].size=tnode[tnode[x].left].size+tnode[tnode[x].right].size+tnode[x].weight;
		tnode[y].size=tnode[tnode[y].left].size+tnode[tnode[y].right].size+tnode[y].weight;
		x=y;
	}

	void rotateWithRightChild(int &x)
	{
		int y=tnode[x].right;
		tnode[x].right=tnode[y].left;
		tnode[y].left=x;
		tnode[x].size=tnode[tnode[x].left].size+tnode[tnode[x].right].size+tnode[x].weight;
		tnode[y].size=tnode[tnode[y].left].size+tnode[tnode[y].right].size+tnode[y].weight;
		x=y;
	}

	void inorder(int x)
	{
		if (x==NULLNODE) return;
		inorder(tnode[x].left);
		//printf("at=%d,key=%d,pro=%d,size=%d,weight=%d,left=%d,right=%d\n",x,tnode[x].key,tnode[x].pro,tnode[x].size,
		//	tnode[x].weight,tnode[x].left,tnode[x].right);
		inorder(tnode[x].right);
	}
};



int n,Q;
Treap tra,trb;
map<int,int>M;
int rm[MAX];
int offset;

void top(int v)
{
	if (M.count(v)>0)
		tra.remove(M[v]);
	M[v]=--offset;
	tra.insert(M[v]);
	rm[MAX-1-offset]=v;
	if (!trb.contain(v))
		trb.insert(v);
}

int query(int v)
{
	int ans;
	if (M.count(v)>0) // at top area
	{
		ans=tra.rank(M[v]);
	}
	else //add those vi>v at top area
	{
		ans=v+(trb.size()-trb.rank(v));
	}
	return ans;
}

int rank(int v)
{
	int ans;
	if (v<=tra.size()) //at top area
	{
		ans=rm[MAX-1-tra.find_kth(v)];
	}
	else
	{
		if (tra.size()==0)
			ans=v;
		else
		{
			v-=tra.size();
			int lo=1,hi=n,mid;
			while (lo<=hi)
			{
				mid=(lo+hi)/2;
				int tmp=mid-trb.rank(mid);
				if (tmp>=v)
					hi=mid-1;
				else
					lo=mid+1;
			}
			ans=lo;
		}
	}
	return ans;
}

int main()
{
	/*TreapInit();
	tra.init();

	int i;
	for (int i=0;i<5;i++)
		tra.insert(i);
	tra.inorder(tra.root);
	puts("");

	tra.insert(4);
	tra.inorder(tra.root);
	puts("");

	tra.remove(2);
	tra.inorder(tra.root);
	puts("");

	for (i=1;i<=5;i++)
		printf("the %dth is %d\n",i,tra.find_kth(i));
	for (i=0;i<=5;i++)
		printf("rank of %d is %d\n",i,tra.rank(i));*/

	//freopen("in","r",stdin);
	//freopen("out","w",stdout);
	
	
	int t,cas=0;
	char buffer[20];
	int v;

	scanf("%d",&t);
	while (t--)
	{
		cas++;
		printf("Case %d:\n",cas);

		scanf("%d%d",&n,&Q);

		assert(1<=n && n<=100000000);
		assert(1<=Q && Q<=100000);

		TreapInit();
		tra.init();
		trb.init();
		M.clear();
		offset=MAX;
		int ans;

		while (Q--)
		{
			scanf("%s%d",buffer,&v);
			assert(1<=v && v<=n);
			switch(buffer[0])
			{
			case 'T':
				top(v);
				break;
			case 'Q':				
				ans=query(v);
				printf("%d\n",ans);
				break;
			case 'R':
				ans=rank(v);
				printf("%d\n",ans);
				break;
			}
		}
	}
	

	return 0;
}