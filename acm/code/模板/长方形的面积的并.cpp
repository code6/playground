
//.............................................................................
//长方形的面积的并(要调用 规则插入删除的线段树模板 )
//输入为长方形数组和长度
//Rec中包含数据成员x1,x2,y1,y2.
//以(x1,y1)表示长方形的左下角,
//以(x2,y2)表示长方形的右上角,
//以y轴做线段树,y值区间不宜太大,
//必要时可先做离散化,值映射,不过要改变测度的实现......
//返回长方形面积的并.

const int REC_MAX=1005;
int CombainArea(Rec data[],int N)   //N大于0,且从data[0]开始存数据
{
	struct Line
	{
		int x;
		int y1, y2;
		bool flag;        //插入或删除
		bool operator<(const Line&obj)const
		{
			return (x<obj.x || (x==obj.x && flag<obj.flag));  //这个比较很重要！！
		}
	}seg[REC_MAX*2+1];

	int lbound=data[0].y1,rbound=data[0].y2;  //左右边界
	int pl=0;
	int i;

	//get_lines
	for (i=0;i<N;i++)
	{
		lbound=min(data[i].y1,lbound);
		rbound=max(data[i].y2,rbound);
		seg[pl].x=data[i].x1;
		seg[pl+1].x=data[i].x2;
		seg[pl].y1=seg[pl+1].y1=data[i].y1;
		seg[pl].y2=seg[pl+1].y2=data[i].y2;
		seg[pl].flag=false;                  //插入
		seg[pl+1].flag=true;                 //删除
		pl+=2;
	}

	sort(seg, seg+pl);
	Init();
	Build(lbound, rbound);

	int ans=0;
	for (i=0;i<pl-1;i++)
	{
		seg[i].flag?Delete(1, seg[i].y1, seg[i].y2):Insert(1, seg[i].y1, seg[i].y2);
		ans+=(seg[i+1].x-seg[i].x)*tree[1].m;
	}

	return ans;
}
//...............................................................................




