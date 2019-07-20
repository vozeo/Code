#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;
cint N = 205, M = 4000;

int S, T, d[N];

struct Edge *head[N];
struct Edge{
	int v, c;
	Edge *rev, *nxt;
	Edge() {}
	Edge(cint x, cint y, cint w) : v(y), c(w), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *ecur = epool, *cur[N];

void add(int x, int y, int z) {
	new (ecur++) Edge(x, y, z);
	new (ecur++) Edge(y, x, 0);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

bool bfs() {
	int u, v;
	memset(d, 0, sizeof(d));
	memcpy(cur, head, sizeof(cur));
	d[S] = 1;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (Edge *e = head[u]; e; e = e->nxt)
			if (e->c && !d[v = e->v]) {
				d[v] = d[u] + 1;
				if (v == T)
					return true;
				q.push(v);
			}
	}
	return false;
}

int dfs(int u, int f) {
	if (u == T || !f)
		return f;
	int r = f, v, p;
	for (Edge *&e = cur[u]; e; e = e->nxt)
		if (e->c && d[v = e->v] == d[u] + 1) {
			p = dfs(v, min(e->c, r));
			e->c -= p;
			e->rev->c += p;
			if (!(r -= p))
				return f;
		}
	d[u] = 0;
	return f - r;
}

int main() {
	int n, m, x, y, w, ans = 0;
	double tot;
	scanf("%d%d%lf", &n, &m, &tot);
	S = 1, T = n;
	rep (i, 1, m) {
		scanf("%d%d%d", &x, &y, &w);
		add(x, y, w);
	}
	while (bfs())
		ans += dfs(S, INT_MAX);
	if (ans)
		printf("%d %d\n", ans, (int)ceil(tot / ans));
	else
		printf("Orz Ni Jinan Saint Cow!\n");
	return 0;
}
