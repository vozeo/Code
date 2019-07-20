#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;
cint N = 505, M = 30005;

int S, T, maxflow, mincost, d[N], minc[N];
bool vis[N];

struct Edge *head[N];
struct Edge{
	int v, flow, cost;
	Edge *rev, *nxt;
	Edge() {}
	Edge(cint x, cint y, cint f, cint c) : v(y), flow(f), cost(c), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *ecur = epool, *pre[N];

void add(int x, int y, int f, int c) {
	new (ecur++) Edge(x, y, f, c);
	new (ecur++) Edge(y, x, 0, -c);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

bool bfs() {
	int u, v;
	memset(d, 0x3f, sizeof(d));
	memset(vis, 0, sizeof(vis));
	d[S] = 0, vis[S] = true, minc[S] = INT_MAX;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		u = q.front(), q.pop();
		vis[u] = false;
		for (Edge *e = head[u]; e; e = e->nxt)
			if (e->flow && d[v = e->v] > d[u] + e->cost) {
				d[v] = d[u] + e->cost;
				minc[v] = min(minc[u], e->flow);
				pre[v] = e;
				if (!vis[v])
					vis[v] = true, q.push(v);
			}
	}
	return d[T] != 0x3f3f3f3f;
}

void MCMF() {
	while (bfs()) {
		int u = T;
		maxflow += minc[T];
		mincost += minc[T] * d[T];
		while (u != S) {
			Edge *e = pre[u];
			e->flow -= minc[T];
			e->rev->flow += minc[T];
			u = e->rev->v;
		}	
	}
}

int main() {
	int n, m, x, y, w;
	scanf("%d%d", &n, &m);
	S = 1 + n * 2, T = S + 1;
	rep (i, 1, n) {
		scanf("%d", &w);
		add(S, i + n, 1, w);
		add(S, i, 1, 0), add(i + n, T, 1, 0);
	}
	rep (i, 1, m) {
		scanf("%d%d%d", &x, &y, &w);
		if (x > y)
			swap(x, y);
		add(x, y + n, 1, w);
	}
	MCMF();
	printf("%d\n", mincost);
	return 0;
}
