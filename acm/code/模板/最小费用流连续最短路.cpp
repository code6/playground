/*
最小费用流连续最短路算法。
此代码为HIT 2025 Going Home的AC代码。
此代码使用时需保证网络中每条边花费均为非负，否则算法会产生错误。题目中若有负花费边，请自行利用流网络等价变换方法变换为非负花费。
在调用mincost函数结束后，即可调用getCost得到最小花费，getFlow得到最大流值。
时间复杂度O(V^2 * F)，其中V为顶点数，F为最大流流量。若为稀疏网络，dijkstra部分可采用优先队列，将O(V^2)部分降低至O(ElgV)甚至是O(E+VlgV)。 
*/
#include <cstdio>
#include <vector>
#include <cassert>
#include <algorithm>
using namespace std;

const int N = 256;
const int INF = 1 << 28;

class Edge {
public:
   int u, v, cuv, cvu, flow, cost;
   Edge(int cu, int cv, int ccu, int ccv, int cc) : u(cu), v(cv), cuv(ccu), cvu(ccv), flow(0), cost(cc) {}
   int other(int p) const { return p == u ? v : u; }
   int cap(int p) const { return p == u ? cuv-flow : cvu+flow; }
   int ecost(int) const;
   void addFlow(int p, int f) { flow += (p == u ? f : -f); }
};
int Edge::ecost(int p) const {
   if(flow == 0) return cost;
   else if(flow > 0) return p == u ? cost : -cost;
   else return p == u ? -cost : cost;
}

class Network {
private:
   vector<Edge> eg;
   vector<Edge*> net[N];
   Edge *prev[N];
   int v, s, t;
   int flow, cost, phi[N], dis[N], pre[N];
   void initNet();
   void initFlow();
   bool dijkstra();
public:
   bool build();
   int getCost() const { return cost; }
   int getFlow() const { return flow; }
   int mincost(int, int);
};
void Network::initNet() {
   for(int i = 0; i < v; i++) net[i].clear();
   for(int i = eg.size()-1; i >= 0; i--) {
      net[eg[i].u].push_back(&eg[i]);
      net[eg[i].v].push_back(&eg[i]);
   }
}
void Network::initFlow() {
   flow = cost = 0;
   memset(phi, 0, sizeof(phi));
   initNet();
}
bool Network::dijkstra() {
   for(int i = 0; i < v; i++) dis[i] = INF;
   dis[s] = 0; prev[s] = NULL; pre[s] = -1;
   bool vst[N] = { false };
   for(int i = 1; i < v; i++) {
      int md = INF, u;
      for(int j = 0; j < v; j++)
         if(!vst[j] && md > dis[j]) { md = dis[j]; u = j; }
      if(md == INF) break;
      vst[u] = true;
      for(int j = net[u].size()-1; j >= 0; j--) {
         Edge *ce = net[u][j];
         if(ce->cap(u) > 0) {
            int p = ce->other(u), cw = ce->ecost(u)-phi[u]+phi[p];
            assert(cw >= 0);
            if(dis[p] > dis[u]+cw) { dis[p] = dis[u]+cw; prev[p] = ce; pre[p] = u; }
         }
      }
   }
   return (dis[t] != INF);
}
int Network::mincost(int ss, int tt) {
   s = ss; t = tt; initFlow();
   while(dijkstra()) {
      int ex = INF;
      for(int c = t; c != s; c = pre[c]) ex <?= prev[c]->cap(pre[c]);
      for(int c = t; c != s; c = pre[c]) prev[c]->addFlow(pre[c], ex);
      flow += ex; cost += ex*(dis[t]-phi[t]);
      for(int i = 0; i < v; i++) phi[i] -= dis[i];
   }
   return cost;
}
bool Network::build() {
   int house[N], child[N], h, w, cn = 0, n = 0;
   char line[N];
   scanf("%d %d", &h, &w);
   if(w == 0) return false;
   scanf("\n");
   for(int i = 0; i < h; i++) {
      gets(line);
      for(int j = 0; line[j] != 0; j++) {
         if(line[j] == 'H') house[n++] = i * N + j;
         if(line[j] == 'm') child[cn++] = i * N + j;
      }
   }
   eg.clear(); v = 2*n+2;
   for(int i = 0; i < n; i++) {
      int cr = child[i] / N, cc = child[i] % N;
      for(int j = 0; j < n; j++) {
         int hr = house[j] / N, hc = house[j] % N;
         eg.push_back(Edge(i+2, j+n+2, 1, 0, abs(cr-hr)+abs(cc-hc)));
      }
   }
   for(int i = 0; i < n; i++) eg.push_back(Edge(0, i+2, 1, 0, 0));
   for(int i = 0; i < n; i++) eg.push_back(Edge(i+n+2, 1, 1, 0, 0));
   return true;
}

int main()
{
   Network net;
   
   //freopen("e.in", "r", stdin);
   while(net.build()) printf("%d\n", net.mincost(0, 1));
   //printf("clock = %d, tx = %d\n", clock(), tx);
   
   return 0;
}
