#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for(int i_ = (s_); i_ <= (t_); ++i_)

typedef const int cint;
cint N = 405, M = 2005;
int n, m, S, T, cnt, tot, dis, ans, d[N];
char a[25][25], b[25][25];

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

inline int g(int x, int y) {
	return (x - 1) * m + y;
}

void addedge(int x, int y, int w) {
	int p = g(x, y);
	if (x <= dis || x + dis > n || y <= dis || y + dis > m)
		add(p + tot, T, w);
	rep (i, 1, n)
		rep (j, 1, m)
			if (abs(x - i) + abs(y - j) <= dis && a[i][j] != '0' && p != g(i, j))
				add(p + tot, g(i, j), w);
}

int main() {
	scanf("%d%d%d", &n, &m, &dis);
	S =  2 * n * m + 1, T = S + 1, tot = m * n;
	rep (i, 1, n)
		cin >> (a[i] + 1);
	rep (i, 1, n)
		cin >> (b[i] + 1);
	rep (i, 1, n)
		rep (j, 1, m) {
			if (a[i][j] != '0')
				addedge(i, j, a[i][j] - '0');
			if (b[i][j] == 'L')
				cnt++, add(S, g(i, j), 1);
		}
	rep (i, 1, n)
		rep (j, 1, m)
			if (a[i][j] != '0')
				add(g(i, j), g(i, j) + tot, a[i][j] - '0');

	//for (Edge *e = head[19]; e; e = e->nxt)
	//	printf("%d w = %d, ", e->v, 3 - e->c);


	while (bfs())
		ans += dfs(S, INT_MAX);
	printf("%d\n", cnt - ans);
	return 0;
}
