#include <bits/stdc++.h>
using namespace std;

const int M = 100005, N = 10005;
int S, T, d[N];

struct Edge *head[N];
struct Edge {
	int u, v, c;
	Edge *nxt, *rev;

	Edge() {}
	Edge(int x, int y, int w) : u(x), v(y), c(w), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *cur[N], *ecur = epool; //double it

void add(int x, int y, int w) {
	new (++ecur) Edge(x, y, w);
	ecur->rev = ecur + 1;
	new (++ecur) Edge(y, x, 0);
	ecur->rev = ecur - 1;
}

bool bfs() {
	memset(d, -1, sizeof(d));
	queue<int> q;
	q.push(S);
	d[S] = 0;
	while (!q.empty()) {
		int u = q.front(), v;
		q.pop();
		cur[u] = head[u];
		for (Edge *e = head[u]; e; e = e->nxt)
			if (e->c && d[v = e->v] == -1) {
				d[v] = d[u] + 1;
				if (v == T)
					return true;
				q.push(v);
			}
	}
	return false;
}

int dfs(int u, int f) {
	if (u == T)
		return f;
	int r = f, v, p;
	for (Edge *e = cur[u]; e && r; e = e->nxt)
		if (e->c && d[v = e->v] == d[u] + 1) {
			p = dfs(v, min(r, e->c));
			if (!p)
				d[v] = -1;
			e->c -= p;
			e->rev->c += p;
			r -= p;
		}
	return f - r; // used flow
}

int main() {
	int n, m, x, y, w, ans = 0;
	scanf("%d%d%d%d", &n, &m, &S, &T);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &w);
		add(x, y, w);
	}
	
	while(bfs())
		ans += dfs(S, INT_MAX); // if T can be arrived, dfs
	printf("%d\n", ans);
	return 0;
}
