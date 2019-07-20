#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= t_; ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= t_; --i_)

const int N = 2e6 + 5;
long long ans[N];
int siz[N], root;

struct Edge *head[N];
struct Edge {
	int v;
	Edge *nxt;
	Edge() {}
	Edge(int x, int y) : v(y), nxt(head[x]) { head[x] = this; }
} epool[N << 1], *ecur = epool;

void add(int x, int y) {
	new (ecur++) Edge(x, y);
}

void dfs1(int u, int fa) {
	int v;
	siz[u] = 1;
	for (Edge *e = head[u]; e; e = e->nxt) {
		if ((v = e->v) == fa)
			continue;
		dfs1(v, u);
		siz[u] += siz[v];
	}
}

void dfs2(int u, int fa) {
	int v;
	for (Edge *e = head[u]; e; e = e->nxt) {
		if ((v = e->v) == fa)
			continue;
		ans[v] = ans[u] - 2 * siz[v] + siz[1];
		if (ans[v] > ans[root])
			root = v;
		if (ans[v] == ans[root] && v < root)
			root = v;
		dfs2(v, u);
	}
}

int main() {
	int n, x, y;
	scanf("%d", &n);
	rep (i, 1, n - 1) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs1(1, 1);
	rep (i, 1, n)
		ans[1] += siz[i];
	root = 1;
	dfs2(1, 1);
	printf("%d\n", root);
}
