#include <bits/stdc++.h>
using namespace std;
#define rep(i_, s_, t_) for (int i_ = (s_); i_ <= (t_); ++i_)
#define per(i_, s_, t_) for (int i_ = (s_); i_ >= (t_); --i_)

const int N = 1005;
int has[N], fa[N], d[N], a[N], ans;

struct Edge *head[N];
struct Edge {
	int v;
	Edge *nxt;
	Edge() {}
	Edge(int x, int y) : v(y), nxt(head[x]) { head[x] = this; }
} epool[N], *ecur = epool;

void push(int u, int dep) {
	if (dep > 2)
		return;
	has[u] = 1;
	for (Edge *e = head[u]; e; e = e->nxt)
		push(e->v, dep + 1);
}

bool comp(const int x, const int y) {
	return d[x] > d[y];
}

int main() {
	int n, x, u;
	scanf("%d", &n);
	fa[1] = 1, d[1] = 1, a[1] = 1;
	rep (i, 2, n) {
		scanf("%d", &x);
		fa[i] = x, d[i] = d[x] + 1, a[i] = i;
		new (ecur++) Edge (x, i);
	}
	sort(a + 1, a + n + 1, comp);
	rep (i, 1, n)
		if (!has[a[i]]) {
			u = a[i], ans++;
			push(u = fa[fa[u]], 0);
			push(u = fa[u], 1);
			has[fa[u]] = 1;
		}
	printf("%d\n", ans);
}
