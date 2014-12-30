#include "cstdio"
#include "algorithm"
using namespace std;

int sg[32][32];
int sgProd(int x,int y);
int sgProd2(int x,int y) {
	if(x < y) swap(x , y);
	if(sg[x][y] != -1) return sg[x][y];
	if((x&(x-1)) == 0) {
		if(x == y) return sg[x][y] = (1<<x) * 3 / 2;
		return sg[x][y] = (1<<x) * (1<<y);
	}
	int ret = 1;
	for (int i = 1 ; i <= x; i <<= 1) {
		if((x&i) && (y&i)) {
			ret = sgProd((1<<i) * 3 / 2 , ret);
		} else if((x&i) || (y&i)){
			ret = sgProd(1<<i , ret);
		}
	}
	return sg[x][y] = ret;
}
int sgProd(int x,int y) {
	if(x == 0 || y == 0) return 0;
	if(x == 1 || y == 1) return x + y - 1;
	int ret = 0;
	for (int i = 0 ; 1<<i <= x ; i ++) if(x & (1<<i)) {
		for (int j = 0 ; 1<<j <= y ; j ++) if(y & (1<<j)) {
			ret ^= sgProd2(i,j);
		}
	}
	return ret;
}
int main() {
	memset(sg , -1 , sizeof(sg));
	int T;
	scanf("%d",&T);
	while(T --) {
		int n;
		scanf("%d",&n);
		int ret = 0;
		while(n --) {
			int x , y;
			scanf("%d%d",&x,&y);
			ret ^= sgProd(x,y);
		}
		puts(ret?"Have a try, lxhgww.":"Don't waste your time.");
	}
	return 0;
}