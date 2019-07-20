#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= t_; ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= t_; --i_)

const int N = 305;
int n, m, f[N][N];


struct Edge *head[N];
struct Edge {
	int v;
	Edge *nxt;
	Edge() {}
	Edge(int x, int y) : v(y), nxt(head[x]) { head[x] = this; }
} epool[N], *ecur = epool;

void add(int x, int y) {
	new (ecur++) Edge(x, y);
}

int dfs(int u) {
	int siz = 1, v;
	for (Edge *e = head[u]; e; e = e->nxt) {
		int s = dfs(v = e->v);
		siz += s;
		per (i, m + 1, 2)
			rep (j, 1, s)
				if (i > j)
					f[u][i] = max(f[u][i], f[u][i - j] + f[v][j]);
	}
	return siz;
}

int main() {
	int k, s;
	scanf("%d%d", &n, &m);
	rep (i, 1, n) {
		scanf("%d%d", &k, &s);
		add(k, i), f[i][1] = s;
	}
	dfs(0);
	printf("%d\n", f[0][m + 1]);
}
