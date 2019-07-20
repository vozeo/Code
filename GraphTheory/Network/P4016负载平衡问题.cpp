#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)

typedef const int cint;
cint N = 55005, M = 200005;
int n, m, S, T, ans, cnt, sum, d[N];

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

int a[105];

int main() {
	scanf("%d", &n);
	S =  n + 1, T = S + 1;
	scanf("%d", a + 1);
	add(1, 2, a[1]);
	add(1, n, a[1]);
	rep (i, 2, n - 1) {
		scanf("%d", a + i);
		add(i, i + 1, a[i]);
		add(i - 1, i, a[i]);
	}
	scanf("%d", &a[n]);
	add(n, n - 1, a[n]);
	add(n, n + 1, a[n]);
	
	rep (i, 1, n)
		sum += a[i];
	sum /= n;
	rep (i, 1, n)
		add(S, i, a[i]), add(i, T, sum);
	while (bfs())
		ans += dfs(S, INT_MAX);
	cnt = 0;
	rep (i, 1, n)
		for (Edge *e = head[i]; e; e = e->nxt)
			if (e->v != S && e->v != T)
				cnt += abs(e->c - a[i]);
	printf("%d\n", cnt - sum * n);
	return 0;
}
