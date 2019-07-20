#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)

const int N = 6005;
int fa[N], f[N][2], r[N];

struct Edge *head[N];
struct Edge{
	int v;
	Edge *nxt;
	Edge() {}
	Edge(int x, int y) : v(y), nxt(head[x]) { head[x] = this; }
} epool[N], *ecur = epool;

void dp(int u) {
	int v;
	for (Edge *e = head[u]; e; e = e->nxt) {
		dp(v = e->v);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += f[v][0];
	}
	f[u][1] += r[u];
}

void add(int x, int y) {
	new (ecur++) Edge(x, y);
}

int main() {
	int n, x, y;
	scanf("%d", &n);
	rep (i, 1, n)
		fa[i] = i;
	rep (i, 1, n)
		scanf("%d", &r[i]);
	rep (i, 1, n) {
		scanf("%d%d", &x, &y);
		fa[x] = y, add(y, x);
	}
	rep (i, 1, n)
		if (fa[i] == i) {
			dp(i);
			printf("%d\n", max(f[i][0], f[i][1]));
			return 0;
		}
}


