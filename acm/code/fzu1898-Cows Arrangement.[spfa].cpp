#include <cstdio>
#include <memory.h>

int tests, Case;
int N, ML, MD;
int head[2000], next[8000], target[8000], total, weight[8000], mindist[2000], maxdist[2000];
int MLx[2000], MLy[2000], MDx[2000], MDy[2000], MLw[2000], MDw[2000];
int Queue[4000], QHead, QTail, QTime[2000];
bool InQ[2000];

void swap(int &a, int &b) { int c = a; a = b; b = c; }
void Initialize() {
	memset(head, 0, sizeof(head));
	memset(next, 0, sizeof(next));
	memset(target, 0, sizeof(target));
	total = 1;
}

void addedge(int u, int v, int w) {
	target[total] = v; weight[total] = w;
	next[total] = head[u]; head[u] = total ++;
}

bool SSSP() {
	memset(QTime, 0, sizeof(QTime));
	memset(InQ, 0, sizeof(InQ));
	memset(maxdist, 0x7F, sizeof(maxdist));
	maxdist[0] = 0;
	Queue[QTail = 0] = 0; QHead = 1;
	while (QHead != QTail) {
		int Now = Queue[QTail ++];
		if (QTail == 4000) QTail = 0;
		int Ptr = head[Now];
		while (Ptr) {
			if (maxdist[target[Ptr]] > maxdist[Now] + weight[Ptr]) {
				maxdist[target[Ptr]] = maxdist[Now] + weight[Ptr];
				if (!InQ[target[Ptr]]) {
					QTime[target[Ptr]] ++;
					if (QTime[target[Ptr]] == N) return false;
					InQ[target[Ptr]] = true;
					Queue[QHead ++] = target[Ptr];
					if (QHead == 4000) QHead = 0;
				}
			}
			Ptr = next[Ptr];
		}
		InQ[Now] = false;
	}
	return true;
}

void SSLP() {
	memset(InQ, 0, sizeof(InQ));
	memset(mindist, 0xFF, sizeof(mindist));
	mindist[0] = 0;
	Queue[QTail = 0] = 0; QHead = 1;
	while (QHead != QTail) {
		int Now = Queue[QTail ++];
		if (QTail == 4000) QTail = 0;
		int Ptr = head[Now];
		while (Ptr) {
			if (mindist[target[Ptr]] < mindist[Now] + weight[Ptr]) {
				mindist[target[Ptr]] = mindist[Now] + weight[Ptr];
				if (!InQ[target[Ptr]]) {
					InQ[target[Ptr]] = true;
					Queue[QHead ++] = target[Ptr];
					if (QHead == 4000) QHead = 0;
				}
			}
			Ptr = next[Ptr];
		}
		InQ[Now] = false;
	}
}

int main() {
	scanf("%d\n", &tests);
	for (Case = 1; Case <= tests; ++ Case) {
		scanf("%d %d %d", &N, &ML, &MD);
		// Max
		Initialize();
		memset(maxdist, 0, sizeof(maxdist));
		for (int i = 1; i < N; ++ i) addedge(i, i - 1, -1);
		for (int i = 0; i < ML; ++ i) {
			scanf("%d %d %d", &MLx[i], &MLy[i], &MLw[i]);
			if (MLx[i] > MLy[i]) swap(MLx[i], MLy[i]);
			addedge(MLx[i] - 1, MLy[i] - 1, MLw[i]);
		}
		for (int i = 0; i < MD; ++ i) {
			scanf("%d %d %d", &MDx[i], &MDy[i], &MDw[i]);
			if (MDx[i] > MDy[i]) swap(MDx[i], MDy[i]);
			addedge(MDy[i] - 1, MDx[i] - 1, - MDw[i]);
		}
		addedge(0, N - 1, 1e8);
		if (!SSSP()) {
			printf("Case #%d: Not Exist!\n", Case);
			continue;
		}
		Initialize();
		for (int i = 1; i < N; ++ i) addedge(i - 1, i, 1);
		for (int i = 0; i < ML; ++ i) addedge(MLy[i] - 1, MLx[i] - 1, - MLw[i]);
		for (int i = 0; i < MD; ++ i) addedge(MDx[i] - 1, MDy[i] - 1, MDw[i]);
		addedge(N - 1, 0, - 1e8);
		SSLP();
		printf("Case #%d: Exist!\n", Case);
		for (int i = 0; i < N; ++ i) printf("%d %d\n", mindist[i], maxdist[i]);
	}
}
