//1-D 树状数组..................................................................

int tree[MAX];  //store from [1..ptree]
int ptree;

inline int lowbit(int val)
{
	return val&(val^(val-1));
}

void modify(int pos,int delta)
{
	while (pos<=ptree)
	{
		tree[pos]+=delta;
		pos+=lowbit(pos);
	}
}

int query(int pos)
{
	int sum=0;
	while (pos>0)
	{
		sum+=tree[pos];
		pos-=lowbit(pos);
	}
	return sum;
}


void changeArea(int f,int r,int delta)
{
	if (f<=r)
	{
		modify(f,delta);
		modify(r+1,-delta);
	}
}


//1-D 树状数组......................................................



// 2D 树状数组..................................................................

vector<vector<int>>tree;
int maxx,maxy;
inline int lowbit(int val)
{
	return  val&(val^(val-1));
}

void modify(int cur_x,int cur_y,int delta)
{
	int x,y;

	for (x=cur_x;x<=maxx;x+=lowbit(x))
		for (y=cur_y;y<=maxy;y+=lowbit(y))
			tree[x][y]+=delta;
}

int query(int cur_x,int cur_y)
{
	int ans=0;
	int x,y;

	for (x=cur_x;x;x-=lowbit(x))
		for (y=cur_y;y;y-=lowbit(y))
			ans+=tree[x][y];

	return ans;
}

void changeArea(int x1,int y1,int x2,int y2,int delta)
{
	modify(x1,y1,delta);
	modify(x1,y2+1,-delta);
	modify(x2+1,y1,-delta);
	modify(x2+1,y2+1,delta);
}
//.......................................................................

