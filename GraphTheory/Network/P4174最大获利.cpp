#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)

typedef const int cint;
cint N = 55005, M = 200005;
int n, m, S, T, cnt, tot, dis, ans, d[N];

struct Edge *head[N];
struct Edge {
	int v, c;
	Edge *nxt, *rev;
	
	Edge() {}
	Edge(cint x, cint y, cint w) : v(y), c(w), nxt(head[x]) {
		head[x] = this;
	}
} epool[M << 1], *cur[N], *ecur = epool;

void add(int x, int y, int w) {
	new (ecur++) Edge(x, y, w);
	new (ecur++) Edge(y, x, 0);
	head[x]->rev = head[y];
	head[y]->rev = head[x];
}

bool bfs() {
	rep (i, 1, T)
		d[i] = 0, cur[i] = head[i];
	d[S] = 1;
	queue<int> q;
	q.push(S);
	while (!q.empty()) {
		int u = q.front(), v;
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
	int a, b, c;
	scanf("%d%d", &n, &m);
	S =  n + m + 1, T = S + 1;
	rep (i, 1, n) {
		scanf("%d", &a);
		add(i + m, T, a);
	}
	rep (i, 1, m) {
		scanf("%d%d%d", &a, &b, &c);
		cnt += c;
		add(S, i, c);
		add(i, a + m, INT_MAX);
		add(i, b + m, INT_MAX);
	}
	while (bfs())
		ans += dfs(S, INT_MAX);
	printf("%d\n", cnt - ans);
	return 0;
}
