#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;
cint N = 505, M = 30005;

int SS, TT, S, T, maxflow, mincost, d[N], minc[N];
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

bool bfs(int s, int t) {
	int u, v;
	memset(d, 0x3f, sizeof(d));
	memset(vis, 0, sizeof(vis));
	d[s] = 0, vis[s] = true, minc[s] = INT_MAX;
	queue<int> q;
	q.push(s);
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
	return d[t] != 0x3f3f3f3f;
}

void MCMF(int s, int t) {
	maxflow = mincost = 0;
	while (bfs(s, t)) {
		int u = t;
		maxflow += minc[T];
		mincost += minc[T] * d[T];
		while (u != s) {
			Edge *e = pre[u];
			e->flow -= minc[T];
			e->rev->flow += minc[T];
			u = e->rev->v;
		}	
	}
}

int p[N];

int main() {
	int n, x, y, k, ans = 0;
	scanf("%d", &n);
	S = 1, T = n + 1, SS = T + 1, TT = SS + 1;
	add(T, S, INT_MAX, 0);
	rep (i, 1, n) {
		scanf("%d", &k);
		if (k)
			rep(j, 1, k) {
				scanf("%d%d", &x, &y);
				add(i, x, y - 1, 1);
				p[i]--, p[x]++;
			}
		else
			add(i, T, INT_MAX, 0);
	}
	rep (i, 1, n) {
		if (p[i] < 0)
			add(i, TT, -p[i], 0);
		if (p[i] > 0)
			add(SS, i, p[i], 0);
	}
	MCMF(SS, TT);
	ans += mincost;
	printf("%d %d\n", maxflow, ans);
	return 0;
}
