#include <cstdio>
#include <iostream>
#include <queue>
#include <climits>
#include <cstring>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)
typedef const int cint;

cint M = 100005, N = 10005;
int n, m, S, T, ans, a[105][105], d[N];
int dx[4] = {1, 1, -1, -1}, dy[4] = {1, -1, 1, -1};

struct Edge *head[N];
struct Edge {
	int v, c;
	Edge *nxt, *rev;

	Edge() {}
	Edge(cint x, cint y, cint w) : v(y), c(w), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *ecur = epool, *cur[N];

void add(int x, int y, int w) {
	new (ecur++) Edge(x, y, w);
	new (ecur++) Edge(y, x, 0);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

bool bfs() {
	memset(d, 0, sizeof(d));
	d[S] = 1;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int u = q.front(), v;
		q.pop();
		for (Edge *e = head[u]; e; e = e->nxt) {
			cur[u] = head[u];
			if (e->c && !d[v = e->v]) {
				d[v] = d[u] + 1;
				if (v == T)
					return true;
				q.push(v);
			}
		}
	}
	return false;
}

int dfs(int u, int f) {
	if (u == T || !f)
		return f;
	int r = f, v, p; // r is rest
	for (Edge *e = cur[u]; e; e = e->nxt)
		if (e->c && d[v = e->v] == d[u] + 1) {
			p = dfs(v, min(e->c, r));
			if (!p)
				d[v] = 0;
			e->c -= p;
			e->rev->c += p;
			if (!(r -= p))
				return f;
		}
	d[u] = 0;
	return f - r;
}

inline int g(int x, int y) {
	return (x - 1) * n + y;
}

int main() {
	scanf("%d%d", &n, &m);
	S = 0, T = n * m + 1;
	rep (i, 1, n)
		rep (j, 1, m) {
			scanf("%d", &a[i][j]);
			if (a[i][j] == 1)
				add(S, g(i, j), INT_MAX);
			else if (a[i][j] == 2)
				add(g(i, j), T, INT_MAX);
	}
	int x, y;
	rep (i, 1, n)
		rep (j, 1, m)
			rep (k, 0, 3) {
				x = i + dx[k], y = j + dy[k];
				if (x >= 1 && x <= n && y >= 1 && y <= m)
					add(g(i, j), g(x, y), 1);
			}
	while (bfs())
		ans += dfs(S, INT_MAX);
	printf("%d\n", ans);
	return 0;
}
