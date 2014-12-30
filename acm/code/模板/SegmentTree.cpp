//规则插入删除的线段树模板(即不能删除没有插入的线段)
//初始化仅改变树指针而已,可以不用调用,自己写一句.
//首先建树,参数是区间的左右端点,原区间采用左[1,2]格式,而不是[1,1]格式,根节点为1
//插入删除参数为当前区间指针,插入删除的线段端点
//没有写查询操作,提供区间的覆盖次数,区间的测度,独立线段数
//Tree_MAX应至少为区间宽度的2倍
//.......................................................................
const int TREE_MAX=10005;
struct SegTree
{
	int b,e;                //左右边界
	int left,right;         //左右儿子指针
	bool lb,rb;              //左，右边界是否覆盖
	int lines;              //连续线段数
	int m;                  //测度  
	int cover;              //区间覆盖次数
};


SegTree tree[TREE_MAX];
int tree_ptr;

void Init();
void Build(int f,int r);
void Insert(int cur,int f,int r);
void Delete(int cur,int f,int r);
void Update(int cur);


void Init()
{
	tree_ptr=0;
}

void Build(int f,int r)
{
	int cur;

	tree_ptr++;
	cur=tree_ptr;
	tree[cur].b=f;
	tree[cur].e=r;
	tree[cur].lb=tree[cur].rb=0;
	tree[cur].cover=0;
	tree[cur].lines=0;
	tree[cur].m=0;
	if (f+1<r)
	{
		int mid=(f+r)/2;
		tree[cur].left=tree_ptr+1;
		Build(f,mid);
		tree[cur].right=tree_ptr+1;
		Build(mid,r);
	}
}

void Insert(int cur,int f,int r)
{
	if (f<=tree[cur].b && r>=tree[cur].e)    //完全覆盖当前区间
	{
		tree[cur].cover++;
		Update(cur);                         //顺便处理叶子
		return;
	}

	int mid=(tree[cur].b+tree[cur].e)/2;

	if (f<mid)
		Insert(tree[cur].left,f,r);


	if (r>mid)
		Insert(tree[cur].right,f,r);

	Update(cur);                            //更新
}


void Delete(int cur,int f,int r)
{

	if (f<=tree[cur].b && r>=tree[cur].e)
	{
		tree[cur].cover--;
		Update(cur);                       //顺便处理叶子
		return;
	}

	int mid=(tree[cur].b+tree[cur].e)/2;

	if (f<mid)
		Delete(tree[cur].left,f,r);

	if (r>mid)
		Delete(tree[cur].right,f,r);

	Update(cur);
}



void Update(int cur)
{
	if (tree[cur].b+1<tree[cur].e)
	{
		if (tree[cur].cover)
		{
			tree[cur].lb=tree[cur].rb=1;
			tree[cur].lines=1;
			tree[cur].m=tree[cur].e-tree[cur].b;
		}
		else
		{
			tree[cur].lb=tree[tree[cur].left].lb;
			tree[cur].rb=tree[tree[cur].right].rb;
			tree[cur].lines=tree[tree[cur].left].lines+tree[tree[cur].right].lines
				-tree[tree[cur].left].rb*tree[tree[cur].right].lb;
			tree[cur].m=tree[tree[cur].left].m+tree[tree[cur].right].m;
		}
	}
	else
	{
		if (tree[cur].cover)
		{
			tree[cur].lb=tree[cur].rb=1;
			tree[cur].lines=1;
			tree[cur].m=tree[cur].e-tree[cur].b;
		}
		else
		{
			tree[cur].lb=tree[cur].rb=0;
			tree[cur].lines=0;
			tree[cur].m=0;
		}
	}
}
//.............................................................................