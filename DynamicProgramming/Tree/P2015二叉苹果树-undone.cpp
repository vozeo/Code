#include <iostream>
#include <cstdio>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 105;
int ch[N][2], s[N], f[N][N], n, m;
bool has[N];

struct Edge *head[N];
struct Edge {
	int v, w;
	Edge *nxt;
	Edge() {}
	Edge(int x, int y, int z) : v(y), w(z), nxt(head[x]) {
		head[x] = this;
	}
} epool[N << 1], *ecur = epool;

void add(int x, int y, int z) {
	new (ecur++) Edge (x, y, z);
}

void dfs(int u, int fa) {
	int v;
	for (Edge *e = head[u]; e; e = e->nxt) {
		if ((v = e->v) == fa)
			continue;
		dfs(v, u);
	}
}
/*
void dp(int u) {
	rep (i, 1, m + 1) {
		if (has[u])
			dp(ch[u][0]), dp(ch[u][1]);
		f[u][i] = max(f[u][i], f[ch[u][0]][i - 1] + s[ch[u][0]]);
		f[u][i] = max(f[u][i], f[ch[u][1]][i - 1] + s[ch[u][1]]);
		rep (j, 1, i - 3)
			f[u][i] = max(f[u][i], f[ch[u][0]][j] + f[ch[u][1]][i - j - 2] + s[ch[u][0]] + s[ch[u][1]]);
	}
}
*/

void dp(int u, int fa) {
	int v;
	for (Edge *e = head[u]; e; e = e->nxt) {
		if ((v = e->v) == fa)
			continue;
		dp(v, u);
		f[v][1] = e->w;
		rep (i, 2, m + 1)
			per (j, i, 0)
				f[u][i] = max(f[u][i], f[u][i - j] + f[v][j]);
	}
}

int main() {
	int x, y, z;
	scanf("%d%d", &n, &m);
	rep (i, 1, n - 1) {
		scanf("%d%d%d", &x, &y, &z);
		add(x, y, z), add(y, x, z);
	}
	/* dfs(1, 1); */
	dp(1, 1);
	rep (i, 1, n)
		printf("%d ", f[i][1]);
	printf("%d\n", f[1][m + 1]);
}
