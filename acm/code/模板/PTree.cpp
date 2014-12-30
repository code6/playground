#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN=100000;
int Index[MAXN],Data[MAXN],Left[19][MAXN],PTree[19][MAXN];
bool cmp(int a,int b){return Data[a]<Data[b];}
void build(int h,int L,int R){
	if(L==R) return ;int i,mid=(L+R+1)>>1,p=0;
	for(i=L;i<=R;++i){
		if(PTree[h][i]<mid) {PTree[h+1][L+p]=PTree[h][i];++p;Left[h][i]=p;}
		else {PTree[h+1][mid+i-L-p]=PTree[h][i];Left[h][i]=p;}
	}
	build(h+1,L,mid-1);build(h+1,mid,R);
}
int find(int h,int ll,int rr,int L,int R,int k){
	if(L==R) return PTree[h][R];int mid,ls,rs;
	if(L==ll) ls=0;else ls=Left[h][L-1];rs=Left[h][R];mid=(ll+rr+1)>>1;
	if(rs-ls<k) return find(h+1,mid,rr,L-ll-ls+mid,R-ll-rs+mid,k-rs+ls);
	else return find(h+1,ll,mid-1,ls+ll,rs+ll-1,k);
}
int main()
{
	int i,x,y,z,n,m;
	//freopen("in.txt","r",stdin);
	scanf("%d%d",&n,&m);for(i=1;i<=n;++i) {scanf("%d",&Data[i]);Index[i]=i;}
	sort(Index+1,Index+n+1,cmp);for(i=1;i<=n;++i) PTree[1][Index[i]]=i;build(1,1,n);
	for(i=1;i<=m;++i) {scanf("%d%d%d",&x,&y,&z);printf("%d\n",Data[Index[find(1,1,n,x,y,z)]]);}
	return 0;
}