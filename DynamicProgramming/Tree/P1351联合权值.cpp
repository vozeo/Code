#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 2e5 + 5, P = 10007;
int f[N][2], w[N], s[N][2], ans, mx;

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

void dfs(int u, int fa, int gf) {
	int v;
	if (u != fa) {
		ans = (ans + 1ll * w[u] * (f[fa][0] - w[u] + P) % P) % P;
	}
	for (Edge *e = head[u]; e; e = e->nxt) {
		if ((v = e->v) == fa)
			continue;
		f[u][0] = (f[u][0] + w[v]) % P;
		/* mx = max(mx, w[u] * w[v]); */
		if (w[v] > s[u][0])
			s[u][1] = s[u][0], s[u][0] = w[v];
		else
			s[u][1] = max(s[u][1], w[v]);
	}
	mx = max(mx, s[u][0] * s[u][1]);
	for (Edge *e = head[u]; e; e = e->nxt) {
		if ((v = e->v) == fa)
			continue;
		dfs(v, u, fa);
	}
	if (u != fa && fa != gf) {
		mx = max(mx, w[u] * w[gf]);
		ans = (ans + w[u] * w[gf] * 2) % P;
	}
}
int main() {
	int n, x, y;
	scanf("%d", &n);
	rep (i, 1, n - 1) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	rep (i, 1, n)
		scanf("%d", &w[i]);
	dfs(1, 1, 1);
	printf("%d %d\n", mx, ans);
}
